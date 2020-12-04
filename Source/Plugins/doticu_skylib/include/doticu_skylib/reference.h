/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/reference_count.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/unknown.h"
#include "doticu_skylib/extra_list.h"

namespace doticu_skylib {

    class Cell_t;
    class Location_t;
    class Quest_t;

    class Reference_t :
        public Form_t,
        public Reference_Count_t,
        public Event_Sink_t<void*>,
        public Animation_Graphs_t {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::REFERENCE,
            kTypeID     = FORM_TYPE,
        };

        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                FROM_REFERENCE_HANDLE_1 = 0x001328A0,
                GET_NAME                = 0x002961F0,
                PLACE_AT_ME             = 0x009951F0,
            };
            using Enum_t::Enum_t;
        };

        class Form_Flags_e : public Enum_t<u32>
        {
        public:
            enum : u32
            {
                IS_PERSISTENT = 1 << 10,
            };
            using Enum_t::Enum_t;
        };

        static Reference_t* Create(Form_t* base, u32 count, Reference_t* at, Bool_t force_persist, Bool_t initially_disable);
        static Reference_t* From_Handle(Reference_Handle_t reference_handle);

    public:
        virtual ~Reference_t(); // 00

        Form_t* base_form;      // 40
        f32_xyz rotation;       // 48
        f32_xyz position;       // 54
        Cell_t* parent_cell;    // 60
        void*   unk_68;         // 68
        List_x  xlist;          // 70
        u64     unk_88;         // 88
        u16     scale;          // 90
        s8      unk_92;         // 92
        Bool_t  pre_destroyed;  // 93
        u32     pad_94;         // 94

        Bool_t Is_Persistent();
        Bool_t Is_Temporary();
        Bool_t Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id);

        const char* Name();
        String_t    Any_Name();
        Location_t* Location();
        Cell_t*     Cell();

        void Select_In_Console();
        void Enable();
        void Disable();
        void Mark_For_Delete(Bool_t do_disable = true);
    };

}
