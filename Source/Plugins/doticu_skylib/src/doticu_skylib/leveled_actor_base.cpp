/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/race.h"

namespace doticu_skylib {

    size_t Leveled_Actor_Base_t::Leveled_Actor_Base_Count()
    {
        return Game_t::Data()->arrLVLN.count;
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
        auto& leveled_actor_bases = Game_t::Data()->arrLVLN;
        for (Index_t idx = 0, end = leveled_actor_bases.count; idx < end; idx += 1) {
            Leveled_Actor_Base_t* leveled_actor_base =
                reinterpret_cast<Leveled_Actor_Base_t*>(leveled_actor_bases.entries[idx]);
            if (leveled_actor_base) {
                results.push_back(leveled_actor_base);
            }
        }
    }

    void Leveled_Actor_Base_t::Log_Leveled_Actor_Bases()
    {
        #define TAB "    "

        Vector_t<Leveled_Actor_Base_t*> leveled_actor_bases = Leveled_Actor_Bases();
        _MESSAGE("Log_Leveled_Actor_Bases {");
        for (size_t idx = 0, end = leveled_actor_bases.size(); idx < end; idx += 1) {
            Leveled_Actor_Base_t* leveled_actor_base = leveled_actor_bases[idx];
            _MESSAGE(TAB "index: %6zu, leveled_actor_base: %8.8X", idx, leveled_actor_base->form_id);
        }
        _MESSAGE("}");

        #undef TAB
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
        for (Index_t idx = 0, end = leveled_entry_count; idx < end; idx += 1) {
            Leveled_Component_t::Entry_t& leveled_entry = leveled_entries[idx];
            Form_t* form = leveled_entry.form;
            if (form) {
                if (form->form_type == Form_Type_e::LEVELED_ACTOR_BASE) {
                    static_cast<Leveled_Actor_Base_t*>(form)->Actor_Bases(results);
                } else if (form->form_type == Form_Type_e::ACTOR_BASE) {
                    Actor_Base_t* actor_base = static_cast<Actor_Base_t*>(form);
                    if (!results.Has(actor_base)) {
                        results.push_back(actor_base);
                    }
                }
            }
        }
    }

    String_t Leveled_Actor_Base_t::Leveled_Name()
    {
        static constexpr size_t MAX_NAME_CHARS = 36;
        char name_chars[MAX_NAME_CHARS + 1];

        Vector_t<Actor_Base_t*> actor_bases = Actor_Bases();
        size_t actor_base_count = actor_bases.size();

        Bool_t is_too_long = false;
        size_t name_char_idx = 0;
        for (Index_t idx = 0, end = actor_base_count; idx < end && name_char_idx < MAX_NAME_CHARS; idx += 1) {
            Actor_Base_t* actor_base = actor_bases[idx];
            if (actor_base) {
                String_t name = actor_base->Any_Name();
                size_t name_length = CString_t::Length(name, false);
                for (Index_t idx = 0, end = name_length; idx < end; idx += 1, name_char_idx += 1) {
                    if (name_char_idx < MAX_NAME_CHARS) {
                        name_chars[name_char_idx] = name.data[idx];
                    } else {
                        is_too_long = true;
                        break;
                    }
                }
                if (idx + 1 < end) {
                    if (name_char_idx + 1 < MAX_NAME_CHARS) {
                        name_chars[name_char_idx] = ',';
                        name_char_idx += 1;
                        name_chars[name_char_idx] = ' ';
                        name_char_idx += 1;
                    } else {
                        is_too_long = true;
                        break;
                    }
                }
            }
        }
        name_chars[name_char_idx] = 0;

        if (is_too_long) {
            return std::string(static_cast<char*>(name_chars)) + "... " + std::to_string(actor_base_count);
        } else {
            return std::string(static_cast<char*>(name_chars)) + " " + std::to_string(actor_base_count);
        }
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

        Vector_t<Actor_Base_t*> actor_bases = Actor_Bases();
        for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
            Actor_Base_t* actor_base = actor_bases[idx];
            if (actor_base) {
                Race_t* race = actor_base->Race();
                if (race) {
                    String_t race_name = race->Get_Editor_ID();
                    if (!results.Has(race_name)) {
                        results.push_back(race_name);
                    }
                }
            }
        }

        return results;
    }

    Vector_t<String_t> Leveled_Actor_Base_t::Actor_Base_Names()
    {
        Vector_t<String_t> results;

        Vector_t<Actor_Base_t*> actor_bases = Actor_Bases();
        for (Index_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
            Actor_Base_t* actor_base = actor_bases[idx];
            if (actor_base) {
                String_t name = actor_base->Any_Name();
                if (!results.Has(name)) {
                    results.push_back(name);
                }
            }
        }

        return results;
    }

}
