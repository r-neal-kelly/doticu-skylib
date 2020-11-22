/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/utils.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/xlist.h"

namespace doticu_skylib {

    class Cell_t;
    class Form_t;
    class Location_t;

    class Reference_Count_t {
    public:
        virtual ~Reference_Count_t();

        volatile u32    reference_count;    // 08
        u32             pad_0C;             // 0C

        Int_t Reference_Count();
        Int_t Increment_Reference();
        Int_t Decrement_Reference();
    };
    STATIC_ASSERT(sizeof(Reference_Count_t) == 0x10);

    class Animation_Graphs_t {
    public:
        virtual ~Animation_Graphs_t();
    };
    STATIC_ASSERT(sizeof(Animation_Graphs_t) == 0x8);

    class Reference_t;
    class Loaded_Reference_t {
    public:
        Reference_t*    reference;
        Cell_t*         cell;

        Loaded_Reference_t() :
            reference(nullptr), cell(nullptr)
        {
        }

        Loaded_Reference_t(Reference_t* reference, Cell_t* cell) :
            reference(reference), cell(cell)
        {
        }

        Loaded_Reference_t(const Loaded_Reference_t& other) :
            reference(other.reference), cell(other.cell)
        {
        }
    };
    STATIC_ASSERT(sizeof(Loaded_Reference_t) == 0x10);

    class Reference_t :
        public Form_t,
        public Reference_Count_t,
        public Event_Sink_t<void*>,
        public Animation_Graphs_t {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                GET_NAME    = 0x002961F0,
                PLACE_AT_ME = 0x009951F0,
            };
            using Enum_t::Enum_t;
        };

        enum
        {
            kTypeID = kFormType_Reference,
        };

        static Reference_t* Create(Form_t* base, u32 count, Reference_t* at, Bool_t force_persist, Bool_t initially_disable);

    public:
        virtual ~Reference_t(); // 00

        Form_t* base_form;      // 40
        XYZ_t   rotation;       // 48
        XYZ_t   position;       // 54
        Cell_t* parent_cell;    // 60
        void*   unk_68;         // 68
        XList_t xlist;          // 70
        u64     unk_88;         // 88
        u16     scale;          // 90
        s8      unk_92;         // 92
        Bool_t  pre_destroyed;  // 93
        u32     pad_94;         // 94

        const char* Name();
        String_t    Any_Name();
        Location_t* Location();
        Cell_t*     Cell();
    };
    STATIC_ASSERT(sizeof(Reference_t) == 0x98);

}
