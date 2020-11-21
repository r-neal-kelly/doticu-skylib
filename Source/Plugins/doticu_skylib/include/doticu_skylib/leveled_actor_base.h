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

        static size_t                           Leveled_Actor_Base_Count();
        static Vector_t<Leveled_Actor_Base_t*>  Leveled_Actor_Bases();
        static void                             Leveled_Actor_Bases(Vector_t<Leveled_Actor_Base_t*>& results);
        static void                             Log_Leveled_Actor_Bases();

    public:
        virtual                 ~Leveled_Actor_Base_t();

    public:
        void                    Iterate_Actor_Bases(Iterator_i<Iterator_e, Actor_Base_t*>& iterator);

        Vector_t<Form_t*>       Forms();
        Vector_t<Actor_Base_t*> Actor_Bases();
        void                    Actor_Bases(Vector_t<Actor_Base_t*>& results);

        String_t                Leveled_Name();
        String_t                Any_Name();
        Vector_t<String_t>      Race_Names();
        Vector_t<String_t>      Actor_Base_Names();
    };
    STATIC_ASSERT(sizeof(Leveled_Actor_Base_t) == 0x90);

}
