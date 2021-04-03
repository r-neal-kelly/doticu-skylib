/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dispelled_magic.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/magic_target.h"
#include "doticu_skylib/spell.h"

namespace doticu_skylib {

    Bool_t Magic_Target_t::Has_Magic_Effect(some<Magic_Effect_t*> magic_effect)
    {
        static auto has_magic_effect = reinterpret_cast
            <Bool_t(*)(Magic_Target_t*, Magic_Effect_t*)>
            (Game_t::Base_Address() + Offset_e::HAS_MAGIC_EFFECT);

        SKYLIB_ASSERT_SOME(magic_effect);

        return has_magic_effect(this, magic_effect());
    }

    Bool_t Magic_Target_t::Has_Magic_Effects(Vector_t<some<Magic_Effect_t*>>& magic_effects)
    {
        for (size_t idx = 0, end = magic_effects.size(); idx < end; idx += 1) {
            if (!Has_Magic_Effect(magic_effects[idx])) {
                return false;
            }
        }
        return true;
    }

    Bool_t Magic_Target_t::Has_Magic_Effects(Vector_t<some<Magic_Effect_t*>>&& magic_effects)
    {
        return Has_Magic_Effects(magic_effects);
    }

    Bool_t Magic_Target_t::Has_Magic_Effects(some<Spell_t*> spell)
    {
        SKYLIB_ASSERT_SOME(spell);

        return Has_Magic_Effects(spell->Magic_Effects());
    }

    void Magic_Target_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Magic_Target_t::Log");
        SKYLIB_LOG(indent + "{");

        if (this->dispelled_magics) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "dispelled_magics:");
            maybe<Dispelled_Magic_t*> dispelled_magic = this->dispelled_magics;
            while (dispelled_magic) {
                dispelled_magic->Log(indent + SKYLIB_TAB);
                dispelled_magic = dispelled_magic->next;
            }
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "dispelled_magics: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
