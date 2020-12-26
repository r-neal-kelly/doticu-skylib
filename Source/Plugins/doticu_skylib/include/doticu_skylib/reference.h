/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/reference_count.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/script_type.h"
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
            SCRIPT_TYPE = Script_Type_e::REFERENCE,
            kTypeID     = SCRIPT_TYPE,
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

        static Reference_t*         Create(some<Form_t*> base, u32 count, some<Reference_t*> at, Bool_t force_persist, Bool_t initially_disable);
        static Reference_t*         From_Handle(Reference_Handle_t reference_handle);
        static Reference_Handle_t   Invalid_Handle(); // this should go on Reference_Handle_t, but I need to be careful that we don't use it with virtual functions from Skyrim types

    public:
        virtual         ~Reference_t();                             // 00

        virtual void    _3B(void);                                  // 3B
        virtual void    _3C(void);                                  // 3C
        virtual void    _3D(void);                                  // 3D
        virtual void    _3E(void);                                  // 3E
        virtual void    _3F(void);                                  // 3F
        virtual void    _40(void);                                  // 40
        virtual void    _41(void);                                  // 41
        virtual void    _42(void);                                  // 42
        virtual void    _43(void);                                  // 43
        virtual void    _44(void);                                  // 44
        virtual void    _45(void);                                  // 45
        virtual void    _46(void);                                  // 46
        virtual void    _47(void);                                  // 47
        virtual void    _48(void);                                  // 48
        virtual void    _49(void);                                  // 49
        virtual void    _4A(void);                                  // 4A
        virtual void    _4B(void);                                  // 4B
        virtual void    _4C(void);                                  // 4C
        virtual void    _4D(void);                                  // 4D
        virtual void    _4E(void);                                  // 4E
        virtual void    _4F(void);                                  // 4F
        virtual void    _50(void);                                  // 50
        virtual void    _51(void);                                  // 51
        virtual void    _52(void);                                  // 52
        virtual void    _53(void);                                  // 53
        virtual void    _54(void);                                  // 54
        virtual void    _55(void);                                  // 55
        virtual void    _56(void);                                  // 56
        virtual void    _57(void);                                  // 57
        virtual void    _58(void);                                  // 58
        virtual void    _59(void);                                  // 59
        virtual void    _5A(void);                                  // 5A
        virtual void    _5B(void);                                  // 5B
        virtual void    _5C(void);                                  // 5C
        virtual void    _5D(void);                                  // 5D
        virtual void    _5E(void);                                  // 5E
        virtual void    _5F(void);                                  // 5F
        virtual void    _60(void);                                  // 60
        virtual void    _61(void);                                  // 61
        virtual void    _62(void);                                  // 62
        virtual void    _63(void);                                  // 63
        virtual void    _64(void);                                  // 64
        virtual void    _65(void);                                  // 65
        virtual void    _66(void);                                  // 66
        virtual void    _67(void);                                  // 67
        virtual void    _68(void);                                  // 68
        virtual void    _69(void);                                  // 69
        virtual void    _6A(void);                                  // 6A
        virtual void    _6B(void);                                  // 6B
        virtual void    _6C(void);                                  // 6C
        virtual void    _6D(void);                                  // 6D
        virtual void    _6E(void);                                  // 6E
        virtual void    _6F(void);                                  // 6F
        virtual void    _70(void);                                  // 70
        virtual void    _71(void);                                  // 71
        virtual void    _72(void);                                  // 72
        virtual void    _73(void);                                  // 73
        virtual void    _74(void);                                  // 74
        virtual void    _75(void);                                  // 75
        virtual void    _76(void);                                  // 76
        virtual void    _77(void);                                  // 77
        virtual void    _78(void);                                  // 78
        virtual void    _79(void);                                  // 79
        virtual void    _7A(void);                                  // 7A
        virtual void    _7B(void);                                  // 7B
        virtual void    _7C(void);                                  // 7C
        virtual void    _7D(void);                                  // 7D
        virtual void    _7E(void);                                  // 7E
        virtual void    _7F(void);                                  // 7F
        virtual void    _80(void);                                  // 80
        virtual void    _81(void);                                  // 81
        virtual void    _82(void);                                  // 82
        virtual void    _83(void);                                  // 83
        virtual void    _84(void);                                  // 84
        virtual void    _85(void);                                  // 85
        virtual void    _86(void);                                  // 86
        virtual void    _87(void);                                  // 87
        virtual void    _88(void);                                  // 88
        virtual void    _89(void);                                  // 89
        virtual void    _8A(void);                                  // 8A
        virtual void    _8B(void);                                  // 8B
        virtual void    _8C(void);                                  // 8C
        virtual void    _8D(void);                                  // 8D
        virtual void    _8E(void);                                  // 8E
        virtual void    _8F(void);                                  // 8F
        virtual void    _90(void);                                  // 90
        virtual void    _91(void);                                  // 91
        virtual void    _92(void);                                  // 92
        virtual void    _93(void);                                  // 93
        virtual void    _94(void);                                  // 94
        virtual void    _95(void);                                  // 95
        virtual void    _96(void);                                  // 96
        virtual void    _97(void);                                  // 97
        virtual void    _98(void);                                  // 98
        virtual Bool_t  Is_Dead(Bool_t is_not_essential);           // 99 (not sure about the bool...)
        virtual void    _9A(void);                                  // 9A
        virtual void    _9B(void);                                  // 9B
        virtual void    _9C(void);                                  // 9C
        virtual void    _9D(void);                                  // 9D
        virtual void    _9E(void);                                  // 9E
        virtual void    _9F(void);                                  // 9F
        virtual void    _A0(void);                                  // A0
        virtual void    _A1(void);                                  // A1

    public:
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

    public:
        Bool_t Is_Enabled();
        Bool_t Is_Disabled();
        Bool_t Is_Persistent();
        Bool_t Is_Temporary();
        Bool_t Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id);

        const char*                     Name();
        String_t                        Any_Name();
        Location_t*                     Location();
        Cell_t*                         Cell();
        maybe<Worldspace_t*>            Worldspace(Bool_t do_check_locations = true);
        Vector_t<some<Worldspace_t*>>   Worldspaces();
        void                            Worldspaces(Vector_t<some<Worldspace_t*>>& results);

        Vector_t<Location_t*>   Locations();
        void                    Locations(Vector_t<Location_t*>& results);
        Vector_t<Quest_t*>      Quests();
        void                    Quests(Vector_t<Quest_t*>& results);

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
