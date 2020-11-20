/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/xdata.h"

namespace doticu_skylib {

    class XData_t;

    class XList_t
    {
    public:
        class Presence_t
        {
        public:
            static constexpr size_t MAX_FLAGS = 192;

            static Presence_t* Create();

        public:
            Byte_t  flags[MAX_FLAGS >> 3];

            Bool_t  Has(XData_Type_e type);
            void    Add(XData_Type_e type);
            void    Remove(XData_Type_e type);
        };
        STATIC_ASSERT(sizeof(Presence_t) == 0x18);

    public:
        XData_t*        xdatas;     // 00
        Presence_t*     presence;   // 08
        BSReadWriteLock lock;       // 10

        void        Validate();

        Bool_t      Has(XData_Type_e type);
        XData_t*    Get(XData_Type_e type);
        Bool_t      Add(XData_t* xdata);
        Bool_t      Remove(XData_t* xdata);

        template <typename Type>
        Bool_t Has();
        template <typename Type>
        Type* Get();
    };
    STATIC_ASSERT(sizeof(XList_t) == 0x18);

}

namespace doticu_skylib {

    template <typename Type>
    inline Bool_t XList_t::Has()
    {
        return Has(Type::XDATA_TYPE);
    }

    template <typename Type>
    inline Type* XList_t::Get()
    {
        return static_cast<Type*>(Get(Type::XDATA_TYPE));
    }

}
