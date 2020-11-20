/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/utils.h"

namespace doticu_skylib {

    class Location_t;

    class XData_Type_e : public Enum_t<u8>
    {
    public:
        enum
        {
            LOCATION = 0x89,
        };
        using Enum_t::Enum_t;
    };

    class XData_t
    {
    public:
        template <typename Type>
        static Type*    Create();
        static void     Destroy(XData_t* xdata);

    public:
        virtual ~XData_t();                                 // 0

        virtual u8      Get_Type();                         // 1
        virtual Bool_t  Isnt_Equal(const XData_t* other);   // 2

        XData_Type_e Type();

        XData_t* next;
    };
    STATIC_ASSERT(sizeof(XData_t) == 0x10);

    class XLocation_t : public XData_t
    {
    public:
        enum : Word_t
        {
            XDATA_TYPE = XData_Type_e::LOCATION,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                V_TABLE = 0x0152C180,
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~XLocation_t();

        Location_t* location; // 10
    };
    STATIC_ASSERT(sizeof(XLocation_t) == 0x18);

}

namespace doticu_skylib {

    template <typename Type>
    Type* XData_t::Create()
    {
        Type* xdata = static_cast<Type*>(Heap_Allocate(sizeof(Type)));
        memset(xdata, 0, sizeof(Type));
        Add_V_Table(xdata, Type::Offset_e::V_TABLE);
        return xdata;
    }

}
