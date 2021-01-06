/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form.h"
#include "doticu_skylib/script_type.h"

namespace doticu_skylib {

    class Effect_Shader_t : public Form_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::EFFECT_SHADER,
        };

    public:
        virtual ~Effect_Shader_t(); // 0

        Byte_t unk_20[0x200]; // 20
    };
    STATIC_ASSERT(sizeof(Effect_Shader_t) == 0x220);

}
