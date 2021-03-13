/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/component_destructible.h"
#include "doticu_skylib/component_model.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_preloadable.h"
#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Projectile_t :        // BGSProjectile
        public Bound_Object_t,  // 000
        public Name_c,          // 030
        public Model_c,         // 040
        public Preloadable_c,   // 068
        public Destructible_c   // 070
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::PROJECTILE,
        };

        static constexpr const char* SCRIPT_NAME = "Projectile";

    public:
        virtual ~Projectile_t(); // 0

    public:
        Byte_t data_080[0xB8]; // 080
    };
    STATIC_ASSERT(sizeof(Projectile_t) == 0x138);

}
