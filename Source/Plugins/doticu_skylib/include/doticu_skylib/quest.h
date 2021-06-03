/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/component_name.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/enum_dialogue_branch_type.h"
#include "doticu_skylib/enum_dialogue_topic_type.h"
#include "doticu_skylib/enum_quest_event.h"
#include "doticu_skylib/enum_quest_flags.h"
#include "doticu_skylib/enum_quest_type.h"
#include "doticu_skylib/enum_script_type.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/interface.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/quest_objective_index.h"
#include "doticu_skylib/read_write_lock.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/string.h"
#include "doticu_skylib/unique.h"

namespace doticu_skylib {

    class Alias_Base_t;
    class Alias_Reference_t;
    class Dialogue_Branch_t;
    class Dialogue_Topic_t;
    class Form_List_t;
    class Global_t;
    class Scene_t;
    class Script_t;
    class Quest_Instance_t;
    class Quest_Instance_Alias_t;
    class Quest_Instance_Global_t;
    class Quest_Objective_t;
    class Quest_Stage_t;

    namespace Virtual {

        class Callback_i;

    }

    class Story_Form_t : public Form_t // BGSStoryManagerTreeForm, 
    {
    public:
        virtual ~Story_Form_t(); // 00

        u32 unk_20; // 20
        u32 pad_24; // 24
    };
    STATIC_ASSERT(sizeof(Story_Form_t) == 0x28);

    class Quest_t :             // TESQuest
        public Story_Form_t,    // 000
        public Name_c           // 028
    {
    public:
        enum
        {
            SCRIPT_TYPE = Script_Type_e::QUEST,
        };

        static constexpr const char* SCRIPT_NAME = "Quest";

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E13938, // 513910
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        static Vector_t<some<Quest_t*>> Quests_Static();
        static void                     Quests_Static(Vector_t<some<Quest_t*>>& results);
        static Vector_t<some<Quest_t*>> Quests_Static(Filter_i<some<Quest_t*>>& filter);
        static void                     Quests_Static(Vector_t<some<Quest_t*>>& results, Filter_i<some<Quest_t*>>& filter);

        static Vector_t<some<Quest_t*>> Quests_Dynamic();
        static void                     Quests_Dynamic(Vector_t<some<Quest_t*>>& results);
        static Vector_t<some<Quest_t*>> Quests_Dynamic(Filter_i<some<Quest_t*>>& filter);
        static void                     Quests_Dynamic(Vector_t<some<Quest_t*>>& results, Filter_i<some<Quest_t*>>& filter);

    public:
        static void     Start(const Vector_t<some<Quest_t*>> quests, maybe<Callback_i<Bool_t>*> ucallback);
        static void     Are_Running(const Vector_t<some<Quest_t*>> quests, some<unique<Callback_i<Bool_t>>> callback);
        static void     Wait_For(const Vector_t<some<Quest_t*>> quests, Float_t wait_interval, some<unique<Callback_i<>>> callback);

        static Int_t    Compare_Any_Names(Quest_t*& a, Quest_t*& b);
        static Int_t    Compare_Any_Names(some<Quest_t*>& a, some<Quest_t*>& b);

    public:
        virtual ~Quest_t(); // 00

    public:
        Array_t<maybe<Quest_Instance_t*>>                           instances;                                  // 038
        u32                                                         current_instance_id;                        // 050
        u32                                                         pad_054;                                    // 054
        Array_t<maybe<Alias_Base_t*>>                               aliases;                                    // 058
        Set_t<Alias_ID_t>                                           filled_aliases;                             // 070
        Hash_Map_t<Int_t, Int_t>                                    unk_alias_map;                              // 0A0
        Read_Write_Lock_t                                           aliases_lock;                               // 0D0
        Float_t                                                     delay_time;                                 // 0D8
        Quest_Flags_e                                               quest_flags;                                // 0DC
        s8                                                          priority;                                   // 0DE
        maybe<Quest_Type_e>                                         quest_type;                                 // 0DF
        Quest_Event_e                                               quest_event;                                // 0E0
        u32                                                         pad_0E4;                                    // 0E4
        List_t<Quest_Stage_t*>*                                     executed_stages;                            // 0E8 (List_t<Quest_Stage_t>* ?)
        List_t<Quest_Stage_t*>*                                     waiting_stages;                             // 0F0
        List_t<Quest_Objective_t*>                                  objectives;                                 // 0F8
        u64                                                         objective_conditions;                       // 108
        u64                                                         story_conditions;                           // 110
        Hash_Map_t<Dialogue_Branch_t*, Array_t<Dialogue_Topic_t*>*> branches[Dialogue_Branch_Type_e::_TOTAL_];  // 118
        Array_t<Dialogue_Topic_t*>                                  topics[Dialogue_Topic_Type_e::_TOTAL_];     // 178
        Array_t<Scene_t*>                                           scenes;                                     // 208
        Array_t<Global_t*>*                                         text_globals;                               // 220
        u16                                                         current_stage;                              // 228
        Bool_t                                                      has_run_once;                               // 22A
        u8                                                          pad_22B;                                    // 22B
        u32                                                         pad_22C;                                    // 22C
        Dynamic_String_t                                            editor_id;                                  // 230
        void*                                                       start_event;                                // 240
        void*                                                       unk_248;                                    // 248
        Array_t<Reference_Handle_t>                                 promoted_references;                        // 250

    public:
        Bool_t Is_Enabled();
        Bool_t Is_Completed();
        Bool_t Does_Start_Enabled();
        Bool_t Is_Displayed_In_HUD();
        Bool_t Is_Failed();
        Bool_t Does_Run_Once();
        Bool_t Is_Active();
        Bool_t Is_Completed_Or_Failed();

        Bool_t Has_Filled_Alias(Alias_ID_t alias_id);

        String_t Any_Name();

        maybe<Alias_Base_t*>                Index_To_Alias_Base(size_t index);
        maybe<Alias_Base_t*>                ID_To_Alias_Base(Alias_ID_t id);
        maybe<Alias_Reference_t*>           Index_To_Alias_Reference(size_t index);
        maybe<Alias_Reference_t*>           ID_To_Alias_Reference(Alias_ID_t id);

        maybe<Alias_Base_t*>                Alias_Base(some<const char*> name);
        maybe<Alias_Reference_t*>           Alias_Reference(some<const char*> name);

        Bool_t                              Has_Alias_Index(size_t index);
        Bool_t                              Has_Alias_ID(Alias_ID_t id);

        Vector_t<some<Alias_Base_t*>>       Alias_Bases();
        void                                Alias_Bases(Vector_t<some<Alias_Base_t*>>& results);
        Vector_t<some<Alias_Reference_t*>>  Alias_References();
        void                                Alias_References(Vector_t<some<Alias_Reference_t*>>& results);

        maybe<Quest_Objective_t*>           Objective(u16 objective_index);
        Vector_t<some<Quest_Objective_t*>>  Objectives();
        void                                Objectives(Vector_t<some<Quest_Objective_t*>>& results);
        maybe<Quest_Objective_Index_t>      Lowest_Objective_Index();
        maybe<Quest_Objective_Index_t>      Highest_Objective_Index();

        maybe<Quest_Instance_t*>            Instance(u32 instance_id);
        maybe<Quest_Instance_Alias_t*>      Instance_Alias(u32 instance_id, some<const char*> alias_name);
        maybe<Quest_Instance_Alias_t*>      Instance_Alias(u32 instance_id, Alias_ID_t alias_id);
        maybe<Form_t*>                      Instance_Alias_Data(u32 instance_id, some<const char*> alias_name);
        maybe<Form_t*>                      Instance_Alias_Data(u32 instance_id, Alias_ID_t alias_id);
        maybe<Quest_Instance_Global_t*>     Instance_Global(u32 instance_id, some<const char*> global_editor_id);
        maybe<Quest_Instance_Global_t*>     Instance_Global(u32 instance_id, some<Global_t*> global);

        std::string                         Replacement_Text(some<const char*> tag,
                                                             some<const char*> sub_tag,
                                                             some<const char*> value,
                                                             u32 instance_id);

    public:
        void    Is_Objective_Completed(u16 index, Bool_t value);
        void    Is_Objective_Completed(u16 index, Bool_t value, some<Script_t*> script);
        void    Is_Objective_Displayed(u16 index, Bool_t value, Bool_t do_force);
        void    Is_Objective_Displayed(u16 index, Bool_t value, Bool_t do_force, some<Script_t*> script);

    public:
        void    Start(maybe<Virtual::Callback_i*> v_callback);                  // Start
        void    Start(maybe<unique<Callback_i<Bool_t>>> callback);

        void    Is_Running(some<Virtual::Callback_i*> v_callback);              // IsRunning
        void    Is_Running(some<unique<Callback_i<Bool_t>>> callback);

        void    Do_Display_Objective(Int_t objective,
                                     Bool_t do_display,
                                     Bool_t do_force,
                                     maybe<Virtual::Callback_i*> v_callback);   // SetObjectiveDisplayed
        void    Do_Display_Objective(Int_t objective,
                                     Bool_t do_display,
                                     Bool_t do_force,
                                     maybe<unique<Callback_i<>>> callback);

        void    Unfill_Aliases(maybe<unique<Callback_i<>>> callback);

    public:
        void Log_Objectives(std::string indent = "");
        void Log_Promoted_References();
    };
    STATIC_ASSERT(sizeof(Quest_t) == 0x268);

}
