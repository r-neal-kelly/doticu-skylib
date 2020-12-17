/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib {

    some<Game_t*> Game_t::Self()
    {
        static auto self = *reinterpret_cast
            <Game_t**>
            (Game_t::Base_Address() + Offset_e::SELF);
        SKYLIB_ASSERT_SOME(self);
        return self;
    }

    Word_t Game_t::Base_Address()
    {
        static Word_t base_address = reinterpret_cast<Word_t>(GetModuleHandle(0));
        SKYLIB_ASSERT(base_address);
        return base_address;
    }

    some<Byte_t*> Game_t::Base_Address_Pointer()
    {
        return reinterpret_cast<Byte_t*>(Base_Address());
    }

    maybe<Form_t*> Game_t::Form(Form_ID_t form_id)
    {
        static auto get_form = reinterpret_cast
            <Form_t*(*)(Form_ID_t form_id)>
            (Game_t::Base_Address() + Offset_e::GET_FORM);
        return get_form(form_id);
    }

    maybe<Form_t*> Game_t::Form(Mod_t* mod, Lower_Form_ID_t lower_form_id)
    {
        if (mod) {
            return Form(Form_t::Form_ID(lower_form_id, mod));
        } else {
            return nullptr;
        }
    }

    Word_t Game_t::V_Table_Offset(void* instance)
    {
        return *reinterpret_cast<Word_t*>(instance) - Game_t::Base_Address();
    }

    void Game_t::Write_V_Table(void* instance, Word_t v_table_offset)
    {
        static_cast<Word_t*>(instance)[0] = Game_t::Base_Address() + v_table_offset;
    }

    void Game_t::Log_u64s(void* data, size_t count, std::string indent)
    {
        SKYLIB_ASSERT(data);

        u64* ptr = static_cast<u64*>(data);
        for (Index_t idx = 0, end = count; idx < end; idx += 1) {
            SKYLIB_LOG(indent + "idx: %8i, %p", idx, *(ptr + idx));
        }
    }

    Array_t<Actor_Base_t*>& Game_t::Actor_Bases()
    {
        return reinterpret_cast<Array_t<Actor_Base_t*>&>(form_caches[Form_Type_e::ACTOR_BASE]);
    }

    Array_t<Faction_t*>& Game_t::Factions()
    {
        return reinterpret_cast<Array_t<Faction_t*>&>(form_caches[Form_Type_e::FACTION]);
    }

    Array_t<Leveled_Actor_Base_t*>& Game_t::Leveled_Actor_Bases()
    {
        return reinterpret_cast<Array_t<Leveled_Actor_Base_t*>&>(form_caches[Form_Type_e::LEVELED_ACTOR_BASE]);
    }

    Array_t<Quest_t*>& Game_t::Quests()
    {
        return reinterpret_cast<Array_t<Quest_t*>&>(form_caches[Form_Type_e::QUEST]);
    }

    Array_t<Race_t*>& Game_t::Races()
    {
        return reinterpret_cast<Array_t<Race_t*>&>(form_caches[Form_Type_e::RACE]);
    }

    Array_t<Worldspace_t*>& Game_t::Worldspaces()
    {
        return reinterpret_cast<Array_t<Worldspace_t*>&>(form_caches[Form_Type_e::WORLDSPACE]);
    }

}
