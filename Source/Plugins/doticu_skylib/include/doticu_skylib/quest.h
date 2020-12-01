/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/interface.h"

#include "doticu_skylib/component_name.h"

#include "doticu_skylib/form.h"

namespace doticu_skylib {

    namespace Virtual {

        class Callback_i;

    }

    class Story_Form_t : public Form_t // BGSStoryManagerTreeForm, 
    {
    public:
        virtual ~Story_Form_t(); // 00

        u32 unk_20; // 20
        u32 pad_24; // 24
    };
    STATIC_ASSERT(sizeof(Story_Form_t) == 0x28);

    class Quest_t :
        public Story_Form_t,
        public Name_c
    {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::QUEST,
            kTypeID     = FORM_TYPE,
        };

        static void Start(const Vector_t<Quest_t*> quests, Callback_i<>* ucallback);

    public:
        virtual ~Quest_t(); // 00

        void Start(Virtual::Callback_i* vcallback = nullptr);
        void Start(Callback_i<Bool_t>* ucallback = nullptr);
    };

}
