/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/utils.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/virtual.h"

namespace doticu_skylib {

    class Story_Form_t : public Form_t { // BGSStoryManagerTreeForm, 
    public:
        virtual ~Story_Form_t(); // 00

        u32 unk_20; // 20
        u32 pad_24; // 24
    };
    STATIC_ASSERT(sizeof(Story_Form_t) == 0x28);

    class Quest_t : public Story_Form_t, public Name_Component_t {
    public:
        enum {
            kTypeID = kFormType_Quest,
        };

        static void Start(const Vector_t<Quest_t*> quests, Callback_i<>* ucallback);

    public:
        virtual ~Quest_t(); // 00

        void Start(Virtual::Callback_i* vcallback = nullptr);
        void Start(Callback_i<Bool_t>* ucallback = nullptr);
    };

}
