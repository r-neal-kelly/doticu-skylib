/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/interface.h"

#include "doticu_skylib/component_leveled.h"
#include "doticu_skylib/component_model_alternates.h"

#include "doticu_skylib/animated_object.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Actor_Base_t;

    class Leveled_Actor_Base_t :
        public Animated_Object_t,
        public Leveled_c,
        public Model_Alternates_c
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::LEVELED_ACTOR_BASE,
        };

        static size_t                           Leveled_Actor_Base_Count();
        static Vector_t<Leveled_Actor_Base_t*>  Leveled_Actor_Bases();
        static void                             Leveled_Actor_Bases(Vector_t<Leveled_Actor_Base_t*>& results);

        static void                             Log_Leveled_Actor_Bases();

    public:
        virtual                 ~Leveled_Actor_Base_t();

    public:
        void                    Iterate_Actor_Bases(Iterator_i<Iterator_e, Actor_Base_t*>& iterator);

        Bool_t                  Has_Actor_Base(Actor_Base_t* actor_base);

        Vector_t<Form_t*>       Forms();
        Vector_t<Actor_Base_t*> Actor_Bases();
        void                    Actor_Bases(Vector_t<Actor_Base_t*>& results);

        String_t                Leveled_Name();
        String_t                Any_Name();
        Vector_t<String_t>      Race_Names();
        void                    Race_Names(Vector_t<String_t>& results);
        Vector_t<String_t>      Actor_Base_Names();
        void                    Actor_Base_Names(Vector_t<String_t>& results);
    };
    STATIC_ASSERT(sizeof(Leveled_Actor_Base_t) == 0x90);

}
