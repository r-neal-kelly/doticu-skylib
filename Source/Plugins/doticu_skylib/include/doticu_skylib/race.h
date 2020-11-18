/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/xlist.h"

namespace doticu_skylib {

    class Race_t :
        public Form_t,
        public Name_Component_t,
        public Description_Component_t,
        public Active_Effects_Component_t,
        public Skin_Component_t,
        public Biped_Component_t,
        public Keyword_Component_t,
        public Attack_Component_t
    {
    public:
        enum
        {
            kTypeID = kFormType_Race,
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
