/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/enum_extra_type.h"

namespace doticu_skylib {

    class Extra_Data_t // BSExtraData
    {
    public:
        template <typename T>
        static some<T*> Create();
        template <typename T>
        static some<T*> Create(const Extra_Data_t& other);
        template <typename T>
        static void     Destroy(some<T*> x_data);

    public:
        static void Log_V_Tables(std::string indent = "");
        static void Log_Collision_Layers(std::string indent = "");
        static void Log_Text_Displays(std::string indent = "");

    public:
        virtual         ~Extra_Data_t();                                    // 0
        virtual u8      Get_Type()                                  = 0;    // 1
        virtual Bool_t  Get_Isnt_Equal(const Extra_Data_t* other)   = 0;    // 2

    public:
        maybe<Extra_Data_t*> next; // 08

    public:
        Extra_Type_e            Type();

        Bool_t                  Is_Equal(some<Extra_Data_t*> other);
        Bool_t                  Isnt_Equal(some<Extra_Data_t*> other);

        maybe<Extra_Data_t*>    Copy();

    public:
        void    Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Data_t) == 0x10);

}
