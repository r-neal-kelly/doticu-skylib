/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/component_icon.h"

namespace doticu_skylib {

    class Message_Icon_c : public Form_Data_c // BGSMessageIcon
    {
    public:
        virtual ~Message_Icon_c(); // 0

        Icon_c message_icon; // 8
    };
    STATIC_ASSERT(sizeof(Message_Icon_c) == 0x18);

}
