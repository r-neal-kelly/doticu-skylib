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

    class Reference_Counter_t {
        virtual ~Reference_Counter_t();

        u32 unk_08; // 08
        u32 unk_0C; // 0C
    };
    STATIC_ASSERT(sizeof(Reference_Counter_t) == 0x10);

    class Animation_Graphs_t {
        virtual ~Animation_Graphs_t();
    };
    STATIC_ASSERT(sizeof(Animation_Graphs_t) == 0x8);

    class Reference_t;
    class Loaded_Reference_t {
    public:
        Reference_t* reference;
        Cell_t* cell;

        Loaded_Reference_t(Reference_t* reference, Cell_t* cell) :
            reference(reference), cell(cell)
        {
        }
    };
    STATIC_ASSERT(sizeof(Loaded_Reference_t) == 0x10);

    class Reference_t :
        public Form_t,
        public Reference_Counter_t,
        public Event_Sink_t<void*>,
        public Animation_Graphs_t {
    public:
        enum class Offset_e : Word_t {
            GET_NAME    = 0x002961F0,
        };

        enum {
            kTypeID = kFormType_Reference,
        };

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
        const char* Base_Name();
    };
    STATIC_ASSERT(sizeof(Reference_t) == 0x98);

}
