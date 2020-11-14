/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/xlist.h"
#include "doticu_skylib/actor_base.h"

namespace doticu_skylib {

    class Leveled_Actor_Base_t :
        public Animated_Object_t,
        public Leveled_Component_t,
        public Model_Alternate_Textures_Component_t
    {
    public:
        enum
        {
            kTypeID = kFormType_LeveledCharacter,
        };

        static Vector_t<Leveled_Actor_Base_t*>  Leveled_Actor_Bases();
        static void                             Log_Leveled_Actor_Bases();

    public:
        virtual ~Leveled_Actor_Base_t();
    };
    STATIC_ASSERT(sizeof(Leveled_Actor_Base_t) == 0x90);

}
