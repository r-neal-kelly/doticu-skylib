/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_package_flags.h"
#include "doticu_skylib/enum_package_interrupt_flags.h"
#include "doticu_skylib/enum_package_interrupt_type.h"
#include "doticu_skylib/enum_package_procedure_type.h"
#include "doticu_skylib/enum_preferred_speed.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/package_schedule.h"

namespace doticu_skylib {

    class Actor_t;
    class Combat_Style_t;
    class Package_Data_t;
    class Package_Location_t;
    class Package_Target_t;
    class Quest_t;

    class Package_t :   // TESPackage
        public Form_t   // 00
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::PACKAGE,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E13808, // 513902
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual         ~Package_t();                                                                                           // 00

        virtual Bool_t  Is_Actor_At_Location(Actor_t* actor, Bool_t unk_1, Float_t unk_2, Bool_t unk_3);                        // 3B
        virtual Bool_t  Is_Actor_At_Location_2(Actor_t* actor_1, Actor_t* actor_2, Bool_t unk_1, Float_t unk_2, Bool_t unk_3);  // 3C
        virtual Bool_t  Is_Actor_At_Target(Actor_t* actor, s32 unk_1);                                                          // 3D
        virtual Bool_t  Is_Target_At_Location(Actor_t* actor, s32 unk_1);                                                       // 3E
        virtual Bool_t  Is_Package_Owner(Actor_t* actor);                                                                       // 3F

    public:
        Package_Flags_e             package_flags;          // 20
        Package_Procedure_Type_e    procedure_type;         // 24
        Package_Interrupt_Type_e    interrupt_type;         // 25
        Preferred_Speed_e           preferred_speed;        // 26
        u8                          pad_27;                 // 27
        Package_Interrupt_Flags_e   interrupt_flags;        // 28
        u16                         unk_flags;              // 2A
        u32                         pad_2C;                 // 2C
        maybe<Package_Data_t*>      data;                   // 30
        maybe<Package_Location_t*>  location;               // 38
        maybe<Package_Target_t*>    target;                 // 40
        void*                       idles;                  // 48
        Package_Schedule_t          schedule;               // 50
        u32                         pad_5C;                 // 5C
        void*                       conditions;             // 60
        maybe<Combat_Style_t*>      combat_style;           // 68
        maybe<Quest_t*>             owning_quest;           // 70
        Byte_t                      on_begin_event[0x20];   // 78
        Byte_t                      on_end_event[0x20];     // 98
        Byte_t                      on_change_event[0x20];  // B8
        Package_Procedure_Type_e    procedure_type_2;       // D8
        u8                          pad_D9;                 // D9
        u16                         pad_DA;                 // DA
        u32                         ref_count;              // DC

    public:
        void    Log_Data(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_t) == 0xE0);

}
