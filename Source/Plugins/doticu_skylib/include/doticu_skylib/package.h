/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_package_flags.h"
#include "doticu_skylib/enum_package_interrupt.h"
#include "doticu_skylib/enum_package_interrupts.h"
#include "doticu_skylib/enum_package_procedure.h"
#include "doticu_skylib/enum_preferred_speed.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/package_schedule.h"
#include "doticu_skylib/enum_script_type.h"

namespace doticu_skylib {

    class Actor_t;
    class Combat_Style_t;
    class Package_Data_t;
    class Package_Location_t;
    class Package_Target_t;
    class Quest_t;

    class Package_t : public Form_t
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::PACKAGE,
        };

    public:
        virtual ~Package_t();

        virtual Bool_t Is_Actor_At_Location(Actor_t* actor, Bool_t arg_2, Float_t arg_3, Bool_t arg_4);
        virtual Bool_t Is_Actor_At_Location_2(Actor_t* actor_1, Actor_t* actor_2, Bool_t arg_3, Float_t arg_4, Bool_t arg_5);
        virtual Bool_t Is_Actor_At_Target(Actor_t* actor, s32 arg_2);
        virtual Bool_t Is_Target_At_Location(Actor_t* actor, s32 arg_2);
        virtual Bool_t Is_Package_Owner(Actor_t* actor);

    public:
        Package_Flags_e         package_flags;          // 20
        Package_Procedure_e     procedure_type;         // 24
        Package_Interrupt_e     interrupt_type;         // 25
        Preferred_Speed_e       preferred_speed;        // 26
        u8                      pad_27;                 // 27
        Package_Interrupts_e    interrupt_flags;        // 28
        u16                     other_flags;            // 2A
        u32                     pad_2C;                 // 2C
        Package_Data_t*         data;                   // 30
        Package_Location_t*     location;               // 38
        Package_Target_t*       target;                 // 40
        void*                   idles;                  // 48
        Package_Schedule_t      schedule;               // 50
        u32                     pad_5C;                 // 5C
        void*                   conditions;             // 60
        Combat_Style_t*         combat_style;           // 68
        Quest_t*                quest;                  // 70
        Byte_t                  on_begin_event[0x20];   // 78
        Byte_t                  on_end_event[0x20];     // 98
        Byte_t                  on_change_event[0x20];  // B8
        Package_Procedure_e     procedure_type_2;       // D8
        u8                      pad_D9;                 // D9
        u16                     pad_DA;                 // DA
        u32                     ref_count;              // DC

    public:
        Bool_t  Is_Flagged(Package_Flags_e flag);
        Bool_t  Is_Flagged(Package_Interrupts_e flag);

        void    Flag(Package_Flags_e flag, Bool_t value);
        void    Flag(Package_Interrupts_e flag, Bool_t value);
    };
    STATIC_ASSERT(sizeof(Package_t) == 0xE0);

}
