/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/component_name.h"

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/branch_type.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/read_write_lock.h"
#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Alias_Base_t;
    class Branch_t;
    class Global_t;
    class Scene_t;
    class Topic_t;
    class Quest_Objective_t;
    class Quest_Stage_t;

    namespace Virtual {

        class Callback_i;

    }

    class Quest_Flags_e : public Enum_t<u16>
    {
    public:
        enum : _TYPE_
        {
            IS_ENABLED          = 1 << 0,
            IS_COMPLETED        = 1 << 1,
            DOES_START_ENABLED  = 1 << 4,
            IS_DISPLAYED_IN_HUD = 1 << 5,
            IS_FAILED           = 1 << 6,
            DOES_RUN_ONCE       = 1 << 8,
            IS_ACTIVE           = 1 << 11,
        };
        using Enum_t::Enum_t;
    };

    class Quest_Type_e : public Enum_t<u8>
    {
    public:
        enum : u8
        {

        };
        using Enum_t::Enum_t;
    };

    class Quest_Event_e : public Enum_t<u32>
    {
    public:
        enum : u32
        {

        };
        using Enum_t::Enum_t;
    };

    class Story_Form_t : public Form_t // BGSStoryManagerTreeForm, 
    {
    public:
        virtual ~Story_Form_t(); // 00

        u32 unk_20; // 20
        u32 pad_24; // 24
    };
    STATIC_ASSERT(sizeof(Story_Form_t) == 0x28);

    class Quest_t :
        public Story_Form_t,
        public Name_c
    {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::QUEST,
            kTypeID     = FORM_TYPE,
        };

    public:
        static void     Start(const Vector_t<some<Quest_t*>> quests, maybe<Callback_i<Bool_t>*> ucallback);

        static Int_t    Compare_Any_Names(Quest_t** a, Quest_t** b);

    public:
        virtual ~Quest_t(); // 00

        Array_t<void*>                              instances;                                  // 038
        u32                                         current_instance_id;                        // 050
        u32                                         pad_054;                                    // 054
        Array_t<Alias_Base_t*>                      aliases;                                    // 058
        Set_t<Alias_ID_t>                           filled_aliases;                             // 070
        Hash_Map_t<Int_t, Int_t>                    unk_alias_map;                              // 0A0
        Read_Write_Lock_t                           aliases_lock;                               // 0D0
        Float_t                                     delay_time;                                 // 0D8
        Quest_Flags_e                               quest_flags;                                // 0DC
        s8                                          priority;                                   // 0DE
        Quest_Type_e                                quest_type;                                 // 0DF
        Quest_Event_e                               quest_event;                                // 0E0
        u32                                         pad_0E4;                                    // 0E4
        List_t<Quest_Stage_t*>*                     executed_stages;                            // 0E8 (List_t<Quest_Stage_t>* ?)
        List_t<Quest_Stage_t*>*                     waiting_stages;                             // 0F0
        List_t<Quest_Objective_t*>                  objectives;                                 // 0F8
        u64                                         objective_conditions;                       // 108
        u64                                         story_conditions;                           // 110
        Hash_Map_t<Branch_t*, Array_t<Topic_t*>*>   complex_branches[Complex_Branch_e::MAX];    // 118
        Array_t<Topic_t*>                           simple_branches[Simple_Branch_e::MAX];      // 178
        Array_t<Scene_t*>                           scenes;                                     // 208
        Array_t<Global_t*>*                         text_globals;                               // 220
        u16                                         current_stage;                              // 228
        Bool_t                                      has_run_once;                               // 22A
        u8                                          pad_22B;                                    // 22B
        u32                                         pad_22C;                                    // 22C
        Dynamic_String_t                            editor_id;                                  // 230
        void*                                       start_event;                                // 240
        void*                                       unk_248;                                    // 248
        Array_t<Reference_Handle_t>                 promoted_references;                        // 250

    public:
        Bool_t Is_Enabled();
        Bool_t Is_Completed();
        Bool_t Does_Start_Enabled();
        Bool_t Is_Displayed_In_HUD();
        Bool_t Is_Failed();
        Bool_t Does_Run_Once();
        Bool_t Is_Active();

        Bool_t Has_Filled_Alias(Alias_ID_t alias_id);

        String_t Any_Name();

        void Log_Objectives(std::string indent = "");
        void Log_Promoted_References();

    public:
        void Start(Virtual::Callback_i* vcallback = nullptr);
        void Start(Callback_i<Bool_t>* ucallback = nullptr);

        void Display_Objective(Int_t objective, Bool_t do_force, maybe<Virtual::Callback_i*> vcallback = nullptr);
        void Undisplay_Objective(Int_t objective, Bool_t do_force, maybe<Virtual::Callback_i*> vcallback = nullptr);
    };
    STATIC_ASSERT(sizeof(Quest_t) == 0x268);

}
