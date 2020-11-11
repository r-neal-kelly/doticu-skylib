/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/virtual.h"

namespace doticu_skylib {

    class Quest_t : public TESQuest {
    public:
        static void Start(const Vector_t<Quest_t*> quests, Callback_i<>* ucallback);

    public:
        void Start(Virtual::Callback_i* vcallback = nullptr);
        void Start(Callback_i<Bool_t>* ucallback = nullptr);
    };

}
