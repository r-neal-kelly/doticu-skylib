/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/enum_global_type.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Global_t : public Form_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::GLOBAL,
        };

    public:
        virtual ~Global_t();

    public:
        Dynamic_String_t    editor_id;  // 20
        Global_Type_e       type;       // 30
        u8                  pad_31;     // 31
        u16                 pad_32;     // 32
        Float_t             value;      // 34

    public:
        Bool_t  Bool();
        void    Bool(Bool_t value);

        Int_t   Int();
        void    Int(Int_t value);

        Float_t Float();
        void    Float(Float_t value);

        Int_t   Percent();
        void    Percent(Int_t value);

        std::string Float_String(size_t precision);

        template <typename Type_t>
        Type_t  As();
        template <typename Type_t>
        void    As(Type_t value);
    };
    STATIC_ASSERT(sizeof(Global_t) == 0x38);

}
