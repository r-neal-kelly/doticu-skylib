/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/component_active_effects.h"
#include "doticu_skylib/component_attack.h"
#include "doticu_skylib/component_biped.h"
#include "doticu_skylib/component_description.h"
#include "doticu_skylib/component_keywords.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/component_skin.h"

#include "doticu_skylib/form.h"

namespace doticu_skylib {

    class Race_t :
        public Form_t,
        public Name_c,
        public Description_c,
        public Active_Effects_c,
        public Skin_c,
        public Biped_c,
        public Keywords_c,
        public Attack_c
    {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::RACE,
            kTypeID     = FORM_TYPE,
        };

        static size_t                   Race_Count();
        static Vector_t<Race_t*>        Races();
        static Vector_t<const char*>    Race_Editor_IDs();
        static void                     Log_Races();

    public:
        virtual ~Race_t();

        String_t Any_Name();
    };
    //STATIC_ASSERT(sizeof(Race_t) == 0x0);

}
