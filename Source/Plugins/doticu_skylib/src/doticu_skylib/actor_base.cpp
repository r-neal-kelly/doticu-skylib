/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include <fstream>
#include <iomanip>

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/actor_head_data.h"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/const_actor_bases.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/form_factory.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/relation.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.inl"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib {

    size_t Actor_Base_t::Static_Actor_Base_Count()
    {
        return Game_t::Self()->Actor_Bases().Count();
    }

    Vector_t<some<Actor_Base_t*>> Actor_Base_t::All_Actor_Bases()
    {
        Vector_t<some<Actor_Base_t*>> results;
        All_Actor_Bases(results);
        return results;
    }

    void Actor_Base_t::All_Actor_Bases(Vector_t<some<Actor_Base_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Actor_Base_t*>>& results;

        public:
            Iterator(Vector_t<some<Actor_Base_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Actor_Base_t*> actor_base = form->As_Actor_Base();
                if (actor_base && actor_base->Is_Valid()) {
                    this->results.push_back(actor_base());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(2048);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Actor_Base_t*>> Actor_Base_t::Static_Actor_Bases()
    {
        Vector_t<some<Actor_Base_t*>> results;
        Static_Actor_Bases(results);
        return results;
    }

    void Actor_Base_t::Static_Actor_Bases(Vector_t<some<Actor_Base_t*>>& results)
    {
        auto& actor_bases = Game_t::Self()->Actor_Bases();
        results.reserve(actor_bases.Count());
        for (size_t idx = 0, end = actor_bases.Count(); idx < end; idx += 1) {
            maybe<Actor_Base_t*> actor_base = actor_bases[idx];
            if (actor_base) {
                results.push_back(actor_base());
            }
        }
    }

    Vector_t<some<Actor_Base_t*>> Actor_Base_t::Dynamic_Actor_Bases()
    {
        Vector_t<some<Actor_Base_t*>> results;
        Dynamic_Actor_Bases(results);
        return results;
    }

    void Actor_Base_t::Dynamic_Actor_Bases(Vector_t<some<Actor_Base_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Actor_Base_t*>>& results;

        public:
            Iterator(Vector_t<some<Actor_Base_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Actor_Base_t*> actor_base = form->As_Actor_Base();
                if (actor_base && actor_base->Is_Valid() && actor_base->Is_Dynamic() && !this->results.Has(actor_base())) {
                    this->results.push_back(actor_base());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(64);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    void Actor_Base_t::Log_Static_Actor_Bases()
    {
        #define TAB "    "

        Vector_t<some<Actor_Base_t*>> actor_bases = Static_Actor_Bases();
        SKYLIB_LOG("Log_Actor_Bases {");
        for (size_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
            some<Actor_Base_t*> actor_base = actor_bases[idx];
            SKYLIB_LOG(TAB "index: %6zu, actor_base: %8.8X %s", idx, actor_base->form_id, actor_base->Any_Name());
        }
        SKYLIB_LOG("}");

        #undef TAB
    }

    void Actor_Base_t::Log_Dynamic_Actor_Bases()
    {
        #define TAB "    "

        Vector_t<some<Actor_Base_t*>> actor_bases = Dynamic_Actor_Bases();
        SKYLIB_LOG("Log_Dynamic_Actor_Bases {");
        for (size_t idx = 0, end = actor_bases.size(); idx < end; idx += 1) {
            some<Actor_Base_t*> actor_base = actor_bases[idx];
            SKYLIB_LOG(TAB "index: %6zu, actor_base: %8.8X %s", idx, actor_base->form_id, actor_base->Any_Name());
            SKYLIB_ASSERT(actor_base->face_template);
            for (maybe<Actor_Base_t*> it = actor_base->face_template; it; it = it->face_template) {
                SKYLIB_LOG(TAB TAB "template: %8.8X %s", it->form_id, it->Any_Name());
            }
        }
        SKYLIB_LOG("}");

        #undef TAB
    }

    void Actor_Base_t::Stream_Actor_Bases(Vector_t<some<Actor_Base_t*>>& actor_bases, std::fstream& fstream)
    {
        static constexpr const char* SPACE  = "     ";
        static constexpr const char* TAB    = "    ";

        if (fstream && fstream.is_open()) {
            size_t actor_bases_count = actor_bases.size();
            fstream << "Printing " << std::to_string(actor_bases_count) << " actor bases." << std::endl;

            size_t index_fill =
                actor_bases_count < 10 ? 1 :
                actor_bases_count < 100 ? 2 :
                actor_bases_count < 1000 ? 3 :
                actor_bases_count < 10000 ? 4 :
                actor_bases_count < 100000 ? 5 :
                6;

            for (size_t idx = 0, end = actor_bases_count; idx < end; idx += 1) {
                some<Actor_Base_t*> actor_base = actor_bases[idx];
                SKYLIB_ASSERT_SOME(actor_base);

                String_t name = actor_base->Name();
                if (!name) {
                    name = "(none)";
                }

                const char* form_id = static_cast<const char*>(actor_base->Form_ID_String()) + 2;

                fstream << "index: "
                    << std::left
                    << std::setfill(' ')
                    << std::setw(index_fill)
                    << std::dec
                    << idx
                    << TAB;
                fstream << "form_id: "
                    << form_id
                    << TAB;
                fstream << "name: "
                    << name
                    << std::endl;
            }
        }
    }

    Int_t Actor_Base_t::Compare_Names(some<Actor_Base_t*>& a, some<Actor_Base_t*>& b)
    {
        if (!a) {
            return Comparator_e::IS_UNORDERED;
        } else if (!b) {
            return Comparator_e::IS_ORDERED;
        } else {
            Comparator_e result = Form_t::Compare_Names(
                a->Any_Name(),
                b->Any_Name()
            );
            if (result == Comparator_e::IS_EQUAL) {
                return a->form_id - b->form_id;
            } else {
                return result;
            }
        }
    }

    some<Actor_Base_t*> Actor_Base_t::Create_Temporary_Copy(some<Actor_Base_t*> source)
    {
        SKYLIB_ASSERT_SOME(source);

        static some<Form_Factory_i*> factory = Form_Factory_i::Form_Factory(some<Form_Type_e>(SCRIPT_TYPE));
        SKYLIB_ASSERT_SOME(factory);

        some<Actor_Base_t*> copy = static_cast<Actor_Base_t*>(factory->Create());
        copy->Initialize_Data();
        copy->Do_Copy(source());

        return copy;

        //return static_cast<Actor_Base_t*>(source->Do_Duplicate_Form(true, nullptr));
    }

    void Actor_Base_t::Destroy(some<Actor_Base_t*> actor_base)
    {
        SKYLIB_ASSERT_SOME(actor_base);

        // this will prevent a potential crash on game reload
        actor_base->Relation(Const::Actor_Base::Player(), Relation_e::ACQUAINTANCE);

        actor_base->~Actor_Base_t();
        Game_t::Deallocate<Actor_Base_t>(actor_base);
    }

    Bool_t Actor_Base_t::Is_Deleted()
    {
        return this->form_flags.Is_Flagged(Form_Flags_e::IS_DELETED);
    }

    Bool_t Actor_Base_t::Isnt_Deleted()
    {
        return !Is_Deleted();
    }

    Bool_t Actor_Base_t::Has_Template_FF000800()
    {
        for (maybe<Actor_Base_t*> it = face_template; it; it = it->face_template) {
            if (it->form_id == 0xFF000800) {
                return true;
            }
        }
        return false;
    }

    Sex_e Actor_Base_t::Sex()
    {
        return Is_Female() ? Sex_e::FEMALE : Sex_e::MALE;
    }

    Rarity_e Actor_Base_t::Rarity()
    {
        return Is_Unique() ? Rarity_e::UNIQUE : Rarity_e::GENERIC;
    }

    some<Relation_e> Actor_Base_t::Relation(some<Actor_Base_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        return Relation_e::Between(this, other);
    }

    void Actor_Base_t::Relation(some<Actor_Base_t*> other, some<Relation_e> relation)
    {
        SKYLIB_ASSERT_SOME(other);
        SKYLIB_ASSERT_SOME(relation);

        Relation_e::Between(this, other, relation);
    }

    maybe<Race_t*> Actor_Base_t::Race()
    {
        return this->race;
    }

    Float_t Actor_Base_t::Weight()
    {
        return this->weight;
    }

    void Actor_Base_t::Weight(Float_t weight)
    {
        this->weight = weight;
    }

    Vector_t<Keyword_t*> Actor_Base_t::Keywords(Bool_t include_templates)
    {
        Vector_t<Keyword_t*> results;
        Keywords(results, include_templates);
        return results;
    }

    void Actor_Base_t::Keywords(Vector_t<Keyword_t*>& results, Bool_t include_templates)
    {
        if (include_templates) {
            size_t reserve_count = keyword_count;
            for (maybe<Actor_Base_t*> it = face_template; it; it = it->face_template) {
                reserve_count += it->keyword_count;
            }
            results.reserve(reserve_count);
        } else {
            results.reserve(keyword_count);
        }

        if (keywords) {
            for (size_t idx = 0, end = keyword_count; idx < end; idx += 1) {
                maybe<Keyword_t*> keyword = keywords[idx];
                if (keyword && keyword->Is_Valid() && !results.Has(keyword())) {
                    results.push_back(keyword());
                }
            }
        }

        if (include_templates) {
            for (maybe<Actor_Base_t*> it = face_template; it; it = it->face_template) {
                if (it->keywords) {
                    for (size_t idx = 0, end = it->keyword_count; idx < end; idx += 1) {
                        maybe<Keyword_t*> keyword = it->keywords[idx];
                        if (keyword && keyword->Is_Valid() && !results.Has(keyword())) {
                            results.push_back(keyword());
                        }
                    }
                }
            }
        }
    }

    some<Actor_Base_t*> Actor_Base_t::Base_Root()
    {
        some<Actor_Base_t*> base = this;
        some<Actor_Base_t*> root = base;
        for (size_t idx = 0, end = 16; idx < end; idx += 1) {
            root = base->Template_Root();
            if (root->Is_Static()) {
                return root;
            } else {
                base = base->Instantiated_Base();
            }
        }
        return base->Template_Root();
    }

    some<Actor_Base_t*> Actor_Base_t::Instantiated_Base()
    {
        some<Actor_t*> actor = static_cast<Actor_t*>
            (Reference_t::Create(this, 1, nullptr, false, false, false)());
        SKYLIB_ASSERT_SOME(actor);

        maybe<Actor_Base_t*> base = actor->Actor_Base();
        actor->Mark_For_Delete();
        if (base) {
            return base();
        } else {
            return this;
        }
    }

    some<Actor_Base_t*> Actor_Base_t::Template_Root()
    {
        some<Actor_Base_t*> it = this;
        for (; it->face_template; it = it->face_template()) {
        }
        return it;
    }

    Vector_t<Actor_Base_t*> Actor_Base_t::Templates()
    {
        if (face_template) {
            Vector_t<Actor_Base_t*> results;
            results.reserve(4);
            Templates(results);
            return results;
        } else {
            return Vector_t<Actor_Base_t*>();
        }
    }

    void Actor_Base_t::Templates(Vector_t<Actor_Base_t*>& results)
    {
        for (maybe<Actor_Base_t*> it = face_template; it; it = it->face_template) {
            results.push_back(it());
        }
    }

    maybe<Actor_Base_t*> Actor_Base_t::Identifiable_Static_Base()
    {
        if (Is_Static()) {
            return this;
        } else {
            for (maybe<Actor_Base_t*> it = this->face_template; it; it = it->face_template) {
                if (it->Is_Static()) {
                    return it;
                }
            }
            return none<Actor_Base_t*>();
        }
    }

    maybe<Outfit_t*> Actor_Base_t::Default_Outfit()
    {
        return this->default_outfit;
    }

    void Actor_Base_t::Default_Outfit(maybe<Outfit_t*> default_outfit)
    {
        this->default_outfit = default_outfit;
        Flag_Form_Change(Form_Change_Flags_e::DEFAULT_OUTFIT);
    }

    maybe<Outfit_t*> Actor_Base_t::Sleep_Outfit()
    {
        return this->sleep_outfit;
    }

    void Actor_Base_t::Sleep_Outfit(maybe<Outfit_t*> sleep_outfit)
    {
        this->sleep_outfit = sleep_outfit;
        Flag_Form_Change(Form_Change_Flags_e::SLEEP_OUTFIT);
    }

    maybe<Faction_t*> Actor_Base_t::Crime_Faction()
    {
        return this->crime_faction;
    }

    void Actor_Base_t::Crime_Faction(maybe<Faction_t*> faction)
    {
        this->crime_faction = faction;
    }

    maybe<Color_t*> Actor_Base_t::Hair_Color()
    {
        if (this->head_data) {
            return this->head_data->hair_color;
        } else {
            return none<Color_t*>();
        }
    }

    void Actor_Base_t::Hair_Color(maybe<Color_t*> hair_color, Bool_t do_save)
    {
        if (this->head_data) {
            this->head_data->hair_color = hair_color;

            if (do_save) {
                // interestingly, this is saved in the save file, but one must update the actor's 3d anyway?
                Flag_Form_Change(Form_Change_Flags_e::FACE);
            }
        }
    }

    maybe<Combat_Style_t*> Actor_Base_t::Combat_Style()
    {
        return this->combat_style;
    }

    void Actor_Base_t::Combat_Style(maybe<Combat_Style_t*> combat_style)
    {
        this->combat_style = combat_style;
    }

    String_t Actor_Base_t::Any_Name()
    {
        const char* name = Name();
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

    String_t Actor_Base_t::Name()
    {
        return Name_c::Name();
    }

    void Actor_Base_t::Name(String_t name, Bool_t do_save)
    {
        Name_c::Name(name);

        if (do_save) {
            Flag_Form_Change(Form_Change_Flags_e::NAME);
        }
    }

    maybe<Relation_t*> Actor_Base_t::Relation_Static(some<Actor_Base_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        if (this != other && this->relations) {
            for (size_t idx = 0, end = this->relations->Count(); idx < end; idx += 1) {
                maybe<Relation_t*> relation = (*this->relations)[idx];
                if (relation && (relation->parent == other || relation->child == other)) {
                    return relation;
                }
            }
            return none<Relation_t*>();
        } else {
            return none<Relation_t*>();
        }
    }

    maybe<Association_t*> Actor_Base_t::Association(some<Actor_Base_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        maybe<Relation_t*> relation = Relation_Static(other);
        if (relation) {
            return relation->association;
        } else {
            return none<Association_t*>();
        }
    }

    maybe<String_t> Actor_Base_t::Association_String(some<Actor_Base_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        maybe<Relation_t*> relation = Relation_Static(other);
        if (relation) {
            return relation->Association_String(other);
        } else {
            return none<String_t>();
        }
    }

    void Actor_Base_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_Base_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s, any_name: %s",
                   this->Form_ID_String(),
                   this->Any_Name());

        SKYLIB_LOG(indent + SKYLIB_TAB + "actor_base_data_c:");
        Actor_Base_Data_c::Log(indent + SKYLIB_TAB + SKYLIB_TAB);

        if (this->face_template) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "face_template:");
            this->face_template->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "face_template: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
