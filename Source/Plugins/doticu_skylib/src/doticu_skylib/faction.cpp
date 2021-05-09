/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/enum_comparator.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/form_list.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib {

    Vector_t<const char*>   Faction_t::editor_ids;
    std::mutex              Faction_t::editor_ids_mutex;

    void Faction_t::Init_Editor_IDs()
    {
        static Bool_t has_initialized = false;

        std::lock_guard<std::mutex> guard(editor_ids_mutex);
        if (!has_initialized) {
            auto& factions = Game_t::Self()->Factions();
            for (size_t idx = 0, end = factions.Count(); idx < end; idx += 1) {
                maybe<Faction_t*> faction = factions[idx];
                if (faction) {
                    if (faction->Is_Valid()) {
                        Mod_t* highest_mod = faction->Get_Highest_Mod();
                        if (highest_mod) {
                            const char* editor_id = highest_mod->Allocate_Editor_ID("FACT", faction->form_id);
                            if (editor_id && editor_id[0]) {
                                faction->editor_id_index = editor_ids.size();
                                editor_ids.push_back(editor_id);
                            } else {
                                faction->editor_id_index = 0xFFFFFFFF;
                            }
                        } else {
                            faction->editor_id_index = 0xFFFFFFFF;
                        }
                    } else {
                        faction->editor_id_index = 0xFFFFFFFF;
                    }
                }
            }
            has_initialized = true;
        }
    }

    size_t Faction_t::Faction_Count()
    {
        return Game_t::Self()->Factions().Count();
    }

    Vector_t<Faction_t*> Faction_t::Factions()
    {
        Vector_t<Faction_t*> results;
        Factions(results);
        return results;
    }

    void Faction_t::Factions(Vector_t<Faction_t*>& results)
    {
        auto& factions = Game_t::Self()->Factions();
        results.reserve(factions.Count());

        for (size_t idx = 0, end = factions.Count(); idx < end; idx += 1) {
            maybe<Faction_t*> faction = factions[idx];
            if (faction && faction->Is_Valid()) {
                results.push_back(faction());
            }
        }
    }

    Int_t Faction_t::Compare_Editor_Or_Form_IDs(Faction_t** a, Faction_t** b)
    {
        if (!a || !*a) {
            return Comparator_e::IS_UNORDERED;
        } else if (!b || !*b) {
            return Comparator_e::IS_ORDERED;
        } else {
            Comparator_e result = Form_t::Compare_Names(
                (*a)->Editor_Or_Form_ID(),
                (*b)->Editor_Or_Form_ID()
            );
            if (result == Comparator_e::IS_EQUAL) {
                return (*a)->form_id - (*b)->form_id;
            } else {
                return result;
            }
        }
    }

    String_t Faction_t::Any_Name()
    {
        const char* name = Name();
        if (name && name[0]) {
            return name;
        } else {
            name = Editor_ID();
            if (name && name[0]) {
                return name;
            } else {
                return Form_ID_String();
            }
        }
    }

    const char* Faction_t::Editor_ID()
    {
        Init_Editor_IDs();

        if (editor_id_index != 0xFFFFFFFF && editor_id_index < editor_ids.size()) {
            return editor_ids[editor_id_index];
        } else {
            return "";
        }
    }

    String_t Faction_t::Editor_Or_Form_ID()
    {
        const char* name = Editor_ID();
        if (name && name[0]) {
            return name;
        } else {
            return Form_ID_String();
        }
    }

    void Faction_t::Reaction_Type(some<Faction_t*> other, some<Reaction_Type_e> reaction_type)
    {
        static auto set_reaction_type = reinterpret_cast
            <void(*)(Faction_t*, Faction_t*, s32)>
            (Game_t::Base_Address() + Offset_e::SET_REACTION_TYPE);

        SKYLIB_ASSERT_SOME(other);
        SKYLIB_ASSERT_SOME(reaction_type);

        set_reaction_type(this, other(), reaction_type());
    }

    void Faction_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Faction_t::Log");
        SKYLIB_LOG(indent + "{");

        if (Is_Valid()) {
            const char* name = Name();
            if (name && name[0]) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "name: %s", name);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "name: (none)");
            }

            String_t editor_id = Editor_ID();
            if (editor_id) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "editor_id: %s", editor_id);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "editor_id: (none)");
            }

            SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s", Form_ID_String());

            if (this->unk_crime_form_list) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "unk_crime_form_list:");
                this->unk_crime_form_list->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "unk_crime_form_list: (none)");
            }

            this->faction_flags.Log(indent + SKYLIB_TAB);

            SKYLIB_LOG(indent + SKYLIB_TAB + "do_arrest: %s", this->do_arrest ? "true" : "false");
            SKYLIB_LOG(indent + SKYLIB_TAB + "do_arrest_on_sight: %s", this->do_arrest_on_sight ? "true" : "false");

            SKYLIB_LOG(indent + SKYLIB_TAB + "murder_gold: %u", this->murder_gold);
            SKYLIB_LOG(indent + SKYLIB_TAB + "assault_gold: %u", this->assault_gold);
            SKYLIB_LOG(indent + SKYLIB_TAB + "trespass_gold: %u", this->trespass_gold);
            SKYLIB_LOG(indent + SKYLIB_TAB + "pickpocket_gold: %u", this->pickpocket_gold);
            SKYLIB_LOG(indent + SKYLIB_TAB + "steal_gold_mult: %f", this->steal_gold_mult);
            SKYLIB_LOG(indent + SKYLIB_TAB + "escape_gold: %u", this->escape_gold);
            SKYLIB_LOG(indent + SKYLIB_TAB + "werewolf_gold: %u", this->werewolf_gold);

            SKYLIB_LOG(indent + SKYLIB_TAB + "reactions:");
            Component_Reactions_Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

    void Faction_t::Log_Basic(std::string indent)
    {
        SKYLIB_LOG(indent + "Faction_t::Log_Basic");
        SKYLIB_LOG(indent + "{");

        if (Is_Valid()) {
            const char* name = Name();
            if (name && name[0]) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "name: %s", name);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "name: (none)");
            }

            String_t editor_id = Editor_ID();
            if (editor_id) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "editor_id: %s", editor_id);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + "editor_id: (none)");
            }

            SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s", Form_ID_String());
        }

        SKYLIB_LOG(indent + "}");
    }

}
