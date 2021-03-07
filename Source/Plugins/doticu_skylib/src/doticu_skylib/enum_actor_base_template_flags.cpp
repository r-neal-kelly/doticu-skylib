/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/enum_actor_base_template_flags.h"

namespace doticu_skylib {

    void Actor_Base_Template_Flags_e::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_Base_Template_Flags_e::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(TRAITS));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(STATS));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(FACTIONS));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(SPELLS_AND_PERKS));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(AI_DATA));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(AI_PACKAGES));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(UNK_06));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(BASE_DATA));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(INVENTORY));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(SCRIPTS));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(DEFAULT_AI_PACKAGES));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(ATTACK_DATA));
        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_ENUM_IS_FLAGGED_STRING(KEYWORDS));

        SKYLIB_LOG(indent + "}");
    }

}
