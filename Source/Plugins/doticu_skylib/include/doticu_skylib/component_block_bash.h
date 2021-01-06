/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

#include "doticu_skylib/component_form_data.h"

namespace doticu_skylib {

    class Block_Bash_c : public Form_Data_c // BGSBlockBashData
    {
    public:
        virtual ~Block_Bash_c(); // 0

        void*   unk_08; // 08
        void*   unk_10; // 10
    };
    STATIC_ASSERT(sizeof(Block_Bash_c) == 0x18);

}
