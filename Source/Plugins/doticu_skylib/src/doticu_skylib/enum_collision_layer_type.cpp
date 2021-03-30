/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/enum_collision_layer_type.h"

namespace doticu_skylib {

    Bool_t Collision_Layer_Type_e_data::Is_Valid(value_type value)
    {
        return value > -1 && value < _TOTAL_;
    }

    some<const char* const*> Collision_Layer_Type_e_data::Strings()
    {
        static const char* const strings[_TOTAL_] =
        {
            SKYLIB_ENUM_TO_STRING(UNIDENTIFIED),
            SKYLIB_ENUM_TO_STRING(STATIC),
            SKYLIB_ENUM_TO_STRING(ANIMATED_STATIC),
            SKYLIB_ENUM_TO_STRING(TRANSPARENT),
            SKYLIB_ENUM_TO_STRING(CLUTTER),
            SKYLIB_ENUM_TO_STRING(WEAPON),
            SKYLIB_ENUM_TO_STRING(PROJECTILE),
            SKYLIB_ENUM_TO_STRING(SPELL),
            SKYLIB_ENUM_TO_STRING(BIPED),
            SKYLIB_ENUM_TO_STRING(TREES),
            SKYLIB_ENUM_TO_STRING(PROPS),
            SKYLIB_ENUM_TO_STRING(WATER),
            SKYLIB_ENUM_TO_STRING(TRIGGER),
            SKYLIB_ENUM_TO_STRING(TERRAIN),
            SKYLIB_ENUM_TO_STRING(TRAP),
            SKYLIB_ENUM_TO_STRING(NON_COLLIDABLE),
            SKYLIB_ENUM_TO_STRING(CLOUD_TRAP),
            SKYLIB_ENUM_TO_STRING(GROUND),
            SKYLIB_ENUM_TO_STRING(PORTAL),
            SKYLIB_ENUM_TO_STRING(SMALL_DEBRIS),
            SKYLIB_ENUM_TO_STRING(LARGE_DEBRIS),
            SKYLIB_ENUM_TO_STRING(ACOUSTIC_SPACE),
            SKYLIB_ENUM_TO_STRING(ACTOR_ZONE),
            SKYLIB_ENUM_TO_STRING(PROJECTILE_ZONE),
            SKYLIB_ENUM_TO_STRING(GAS_TRAP),
            SKYLIB_ENUM_TO_STRING(SHELL_CASING),
            SKYLIB_ENUM_TO_STRING(SMALL_TRANSPARENT),
            SKYLIB_ENUM_TO_STRING(INVISIBLE_WALL),
            SKYLIB_ENUM_TO_STRING(SMALL_ANIMATED_TRANSPARENT),
            SKYLIB_ENUM_TO_STRING(WARD),
            SKYLIB_ENUM_TO_STRING(CHARACTER_CONTROLLER),
            SKYLIB_ENUM_TO_STRING(STAIR_HELPER),
            SKYLIB_ENUM_TO_STRING(DEAD_BIPED),
            SKYLIB_ENUM_TO_STRING(NO_CHARACTER_CONTROLLER_BIPED),
            SKYLIB_ENUM_TO_STRING(AVOID_BOX),
            SKYLIB_ENUM_TO_STRING(COLLISION_BOX),
            SKYLIB_ENUM_TO_STRING(CAMERA_SPHERE),
            SKYLIB_ENUM_TO_STRING(DOOR_DETECTION),
            SKYLIB_ENUM_TO_STRING(CONE_PROJECTILE),
            SKYLIB_ENUM_TO_STRING(CAMERA),
            SKYLIB_ENUM_TO_STRING(ITEM_PICKER),
            SKYLIB_ENUM_TO_STRING(LINE_OF_SIGHT),
            SKYLIB_ENUM_TO_STRING(PATH_PICKER),
            SKYLIB_ENUM_TO_STRING(CUSTOM_PICKER_1),
            SKYLIB_ENUM_TO_STRING(CUSTOM_PICKER_2),
            SKYLIB_ENUM_TO_STRING(SPELL_EXPLOSION),
            SKYLIB_ENUM_TO_STRING(DROP_PICKER),
            SKYLIB_ENUM_TO_STRING(DEAD_ACTOR_ZONE),
            SKYLIB_ENUM_TO_STRING(FALLING_TRAP_TRIGGER),
            SKYLIB_ENUM_TO_STRING(NAVCUT),
            SKYLIB_ENUM_TO_STRING(CRITTER),
            SKYLIB_ENUM_TO_STRING(SPELL_TRIGGER),
            SKYLIB_ENUM_TO_STRING(LIVING_AND_DEAD_ACTORS),
            SKYLIB_ENUM_TO_STRING(DETECTION),
            SKYLIB_ENUM_TO_STRING(TRAP_TRIGGER),
        };

        return strings;
    }

    some<const char*> Collision_Layer_Type_e_data::To_String(value_type value)
    {
        return Enum_Type_Data_t::To_String(Strings(), "NONE", &Is_Valid, value);
    }

    Collision_Layer_Type_e_data::value_type Collision_Layer_Type_e_data::From_String(maybe<const char*> string)
    {
        return Enum_Type_Data_t::From_String(Strings(), _NONE_, _TOTAL_, string);
    }

}
