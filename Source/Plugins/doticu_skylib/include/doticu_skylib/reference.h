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
    class Worldspace_t;

    class Reference_t :
        public Form_t,
        public Reference_Count_t,
        public Event_Sink_t<void*>,
        public Animation_Graphs_t
    {
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
                CREATE_REFERENCE_HANDLE     = 0x001320F0,
                LOOKUP_REFERENCE_HANDLE_1   = 0x001328A0,
                INVALID_REFERENCE_HANDLE    = 0x01EBEABC,

                GET_NAME                    = 0x002961F0,
                GET_WORLDSPACE              = 0x00299750,

                PLACE_AT_ME                 = 0x009951F0,
                MOVE_TO_OFFSET              = 0x009AE5C0,
            };
            using Enum_t::Enum_t;
        };

        class Form_Flags_e : public Enum_t<u32>
        {
        public:
            enum : u32
            {
                IS_PERSISTENT   = 1 << 10,
                IS_DISABLED     = 1 << 11,
            };
            using Enum_t::Enum_t;
        };

        static Reference_t*         Create(Form_t* base, u32 count, Reference_t* at, Bool_t force_persist, Bool_t initially_disable);
        static Reference_t*         From_Handle(Reference_Handle_t reference_handle);
        static Reference_Handle_t   Invalid_Handle(); // this should go on Reference_Handle_t, but I need to be careful that we don't use it with virtual functions from Skyrim types

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

        Bool_t Is_Enabled();
        Bool_t Is_Disabled();
        Bool_t Is_Persistent();
        Bool_t Is_Temporary();
        Bool_t Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id);

        const char*         Name();
        String_t            Any_Name();
        Location_t*         Location();
        Cell_t*             Cell();
        Worldspace_t*       Worldspace();

        Reference_Handle_t  To_Handle();

        void Move_To_Offset(some<Reference_t*> target,
                            maybe<Cell_t*> target_cell,
                            maybe<Worldspace_t*> target_worldspace,
                            f32_xyz& offset,
                            f32_xyz& rotation);
        void Move_To_Offset(some<Reference_t*> target, f32_xyz& offset, f32_xyz& rotation);
        void Move_To_Orbit(some<Reference_t*> origin, Float_t radius, Float_t degree);

        void Select_In_Console();

        
        void Enable();
        void Disable();

        void Mark_For_Delete(Bool_t do_disable = true);
    };

}
