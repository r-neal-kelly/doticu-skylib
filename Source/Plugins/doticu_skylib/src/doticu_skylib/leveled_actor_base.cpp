/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/game.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/leveled_entry.h"
#include "doticu_skylib/race.h"

namespace doticu_skylib {

    size_t Leveled_Actor_Base_t::Leveled_Actor_Base_Count()
    {
        return Game_t::Self()->Leveled_Actor_Bases().Count();
    }

    Vector_t<Leveled_Actor_Base_t*> Leveled_Actor_Base_t::Leveled_Actor_Bases()
    {
        Vector_t<Leveled_Actor_Base_t*> results;
        results.reserve(Leveled_Actor_Base_Count());
        Leveled_Actor_Bases(results);
        return results;
    }

    void Leveled_Actor_Base_t::Leveled_Actor_Bases(Vector_t<Leveled_Actor_Base_t*>& results)
    {
        auto& leveled_actor_bases = Game_t::Self()->Leveled_Actor_Bases();
        for (size_t idx = 0, end = leveled_actor_bases.Count(); idx < end; idx += 1) {
            maybe<Leveled_Actor_Base_t*> leveled_actor_base = leveled_actor_bases[idx];
            if (leveled_actor_base) {
                results.push_back(leveled_actor_base());
            }
        }
    }

    void Leveled_Actor_Base_t::Log_Leveled_Actor_Bases()
    {
        #define TAB "    "

        Vector_t<Leveled_Actor_Base_t*> leveled_actor_bases = Leveled_Actor_Bases();
        SKYLIB_LOG("Log_Leveled_Actor_Bases {");
        for (size_t idx = 0, end = leveled_actor_bases.size(); idx < end; idx += 1) {
            Leveled_Actor_Base_t* leveled_actor_base = leveled_actor_bases[idx];
            SKYLIB_LOG(TAB "index: %6zu, leveled_actor_base: %8.8X", idx, leveled_actor_base->form_id);
        }
        SKYLIB_LOG("}");

        #undef TAB
    }

    void Leveled_Actor_Base_t::Iterate_Actor_Bases(Iterator_i<Actor_Base_t*>& iterator)
    {
        if (Is_Valid()) {
            Vector_t<Leveled_Actor_Base_t*> leveled_bases_backup;
            {
                Stack_Array_t<Leveled_Actor_Base_t*, 256> leveled_bases;
                leveled_bases.Push(this);
                for (size_t idx = 0; idx < leveled_bases.count; idx += 1) {
                    Leveled_Actor_Base_t* leveled_base = leveled_bases[idx];
                    for (size_t idx = 0, end = leveled_base->leveled_entry_count; idx < end; idx += 1) {
                        Form_t* form = leveled_base->leveled_entries[idx].object;
                        if (form && form->Is_Valid()) {
                            if (form->form_type == Form_Type_e::LEVELED_ACTOR_BASE) {
                                Leveled_Actor_Base_t* leveled_base = static_cast<Leveled_Actor_Base_t*>(form);
                                if (!leveled_bases.Has(leveled_base)) {
                                    if (leveled_bases.Has_Space()) {
                                        leveled_bases.Push(leveled_base);
                                    } else if (!leveled_bases_backup.Has(leveled_base)) {
                                        leveled_bases_backup.push_back(leveled_base);
                                    }
                                }
                            } else if (form->form_type == Form_Type_e::ACTOR_BASE) {
                                if (iterator(static_cast<Actor_Base_t*>(form)) == Iterator_e::BREAK) {
                                    return;
                                }
                            }
                        }
                    }
                }
            }
            {
                for (size_t idx = 0; idx < leveled_bases_backup.size(); idx += 1) {
                    Leveled_Actor_Base_t* leveled_base = leveled_bases_backup[idx];
                    for (size_t idx = 0, end = leveled_base->leveled_entry_count; idx < end; idx += 1) {
                        Form_t* form = leveled_base->leveled_entries[idx].object;
                        if (form && form->Is_Valid()) {
                            if (form->form_type == Form_Type_e::LEVELED_ACTOR_BASE) {
                                Leveled_Actor_Base_t* leveled_base = static_cast<Leveled_Actor_Base_t*>(form);
                                if (!leveled_bases_backup.Has(leveled_base)) {
                                    leveled_bases_backup.push_back(leveled_base);
                                }
                            } else if (form->form_type == Form_Type_e::ACTOR_BASE) {
                                if (iterator(static_cast<Actor_Base_t*>(form)) == Iterator_e::BREAK) {
                                    return;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    Bool_t Leveled_Actor_Base_t::Has_Actor_Base(Actor_Base_t* actor_base)
    {
        class Iterator_t :
            public Iterator_i<Actor_Base_t*>
        {
        public:
            Actor_Base_t* base_to_compare;
            Bool_t result;

            Iterator_t(Actor_Base_t* base_to_compare) :
                base_to_compare(base_to_compare), result(false)
            {
            }

            Iterator_e operator ()(Actor_Base_t* actor_base)
            {
                if (actor_base == base_to_compare) {
                    result = true;
                    return Iterator_e::BREAK;
                } else {
                    return Iterator_e::CONTINUE;
                }
            }

            Bool_t Result()
            {
                return result;
            }
        } iterator(actor_base);

        Iterate_Actor_Bases(iterator);

        return iterator.Result();
    }

    Vector_t<Actor_Base_t*> Leveled_Actor_Base_t::Actor_Bases()
    {
        Vector_t<Actor_Base_t*> actor_bases;
        actor_bases.reserve(leveled_entry_count);
        Actor_Bases(actor_bases);
        return std::move(actor_bases);
    }

    void Leveled_Actor_Base_t::Actor_Bases(Vector_t<Actor_Base_t*>& results)
    {
        class Iterator_t :
            public Iterator_i<Actor_Base_t*>
        {
        public:
            Vector_t<Actor_Base_t*>& results;
            Iterator_t(Vector_t<Actor_Base_t*>& results) :
                results(results)
            {
            }

            Iterator_e operator ()(Actor_Base_t* actor_base)
            {
                if (!results.Has(actor_base)) {
                    results.push_back(actor_base);
                }
                return Iterator_e::CONTINUE;
            }
        } iterator(results);
        Iterate_Actor_Bases(iterator);
    }

    String_t Leveled_Actor_Base_t::Leveled_Name()
    {
        constexpr size_t MAX_CHARS = 32;

        Vector_t<String_t> names;
        names.reserve(16);

        class Iterator_t :
            public Iterator_i<Actor_Base_t*>
        {
        public:
            Vector_t<Actor_Base_t*> actor_bases;
            Vector_t<String_t>& names;
            size_t char_count;
            size_t char_difference;
            Iterator_t(Vector_t<String_t>& names) :
                names(names), char_count(0), char_difference(0)
            {
                actor_bases.reserve(16);
            }

            size_t Actor_Base_Count()
            {
                return actor_bases.size();
            }

            size_t Char_Difference()
            {
                return char_difference;
            }

            Iterator_e operator() (Actor_Base_t* actor_base)
            {
                if (!actor_bases.Has(actor_base)) {
                    actor_bases.push_back(actor_base);
                    if (char_count < MAX_CHARS) {
                        String_t name = actor_base->Any_Name();
                        if (name && !names.Has(name)) {
                            names.push_back(name);
                            size_t name_char_count = CString_t::Length(name, false);
                            char_count += name_char_count;
                            if (char_count > MAX_CHARS) {
                                char_difference = name_char_count - (char_count - MAX_CHARS);
                            }
                        }
                    }
                }
                return Iterator_e::CONTINUE;
            }
        } iterator(names);
        Iterate_Actor_Bases(iterator);

        std::string leveled_name = "";
        size_t name_count = names.size();
        if (name_count > 0) {
            for (size_t idx = 0, end = name_count - 1; idx < end; idx += 1) {
                leveled_name += names[idx] + ", ";
            }
            size_t char_difference = iterator.Char_Difference();
            if (char_difference > 0) {
                if (char_difference > MAX_CHARS) {
                    char_difference = MAX_CHARS;
                }
                char remaining_chars[MAX_CHARS + 1];
                String_t name = names[name_count - 1];
                size_t idx = 0, end = char_difference;
                for (; idx < end; idx += 1) {
                    remaining_chars[idx] = name[idx];
                }
                remaining_chars[idx] = 0;
                leveled_name += std::string(remaining_chars) + "... " + std::to_string(iterator.Actor_Base_Count());
            } else {
                leveled_name += names[name_count - 1] + " " + std::to_string(iterator.Actor_Base_Count());
            }
        } else {
            leveled_name += std::to_string(iterator.Actor_Base_Count());
        }

        return leveled_name;
    }

    String_t Leveled_Actor_Base_t::Any_Name()
    {
        const char* name = Leveled_Name();
        if (!name || !name[0]) {
            name = Get_Editor_ID();
            if (!name || !name[0]) {
                return Form_ID_String();
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

    Vector_t<String_t> Leveled_Actor_Base_t::Race_Names()
    {
        Vector_t<String_t> results;
        Race_Names(results);
        return results;
    }

    void Leveled_Actor_Base_t::Race_Names(Vector_t<String_t>& results)
    {
        class Iterator_t :
            public Iterator_i<Actor_Base_t*>
        {
        public:
            Vector_t<String_t>& results;
            Iterator_t(Vector_t<String_t>& results) :
                results(results)
            {
            }

            Iterator_e operator ()(Actor_Base_t* actor_base)
            {
                maybe<Race_t*> race = actor_base->Race();
                if (race) {
                    String_t race_name = race->Get_Editor_ID();
                    if (!results.Has(race_name)) {
                        results.push_back(race_name);
                    }
                }
                return Iterator_e::CONTINUE;
            }
        } iterator(results);
        Iterate_Actor_Bases(iterator);
    }

    Vector_t<String_t> Leveled_Actor_Base_t::Actor_Base_Names()
    {
        Vector_t<String_t> results;
        Actor_Base_Names(results);
        return results;
    }

    void Leveled_Actor_Base_t::Actor_Base_Names(Vector_t<String_t>& results)
    {
        class Iterator_t :
            public Iterator_i<Actor_Base_t*>
        {
        public:
            Vector_t<String_t>& results;
            Iterator_t(Vector_t<String_t>& results) :
                results(results)
            {
            }

            Iterator_e operator ()(Actor_Base_t* actor_base)
            {
                String_t name = actor_base->Any_Name();
                if (!results.Has(name)) {
                    results.push_back(name);
                }
                return Iterator_e::CONTINUE;
            }
        } iterator(results);
        Iterate_Actor_Bases(iterator);
    }

}
