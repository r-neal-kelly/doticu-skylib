/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

#include "doticu_skylib/actor_state.h"
#include "doticu_skylib/actor_values.h"
#include "doticu_skylib/faction_and_rank.h"
#include "doticu_skylib/loaded_actor.h"
#include "doticu_skylib/magic_target.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/sex.h"

namespace doticu_skylib {

    class Actor_t;
    class Actor_Base_t;
    class Leveled_Actor_Base_t;

    class Actor_t :
        public Reference_t,
        public Magic_Target_t,
        public Actor_Values_t,
        public Actor_State_t,
        public Event_Sink_t<void**>,
        public Event_Sink_t<void***>,
        public Animation_Updater_i
    {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::ACTOR,
            kTypeID     = FORM_TYPE,
        };

        static Vector_t<Loaded_Actor_t> Loaded_Actors();
        static void                     Loaded_Actors(Vector_t<Loaded_Actor_t>& results);
        static void                     Log_Loaded_Actors();

        static maybe<Actor_t*> Create(some<Form_t*> base, Bool_t do_persist, Bool_t do_uncombative);
        static maybe<Actor_t*> Create(some<Actor_Base_t*> base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static);
        static maybe<Actor_t*> Create(some<Leveled_Actor_Base_t*> base, Bool_t do_persist, Bool_t do_uncombative, Bool_t do_static);

    public:
        virtual ~Actor_t(); // 00

        Byte_t unk_data[0x1D0];

        Sex_e                           Sex();
        Race_t*                         Race();
        Actor_Base_t*                   Actor_Base();
        Actor_Base_t*                   Highest_Static_Actor_Base();
        Vector_t<Actor_Base_t*>         Actor_Bases();
        void                            Actor_Bases(Vector_t<Actor_Base_t*>& results);
        Vector_t<Faction_And_Rank_t>    Factions_And_Ranks(Bool_t remove_negatives = true);
        void                            Factions_And_Ranks(Vector_t<Faction_And_Rank_t>& results, Bool_t remove_negatives = true);

        const char*                     Base_Name();
        String_t                        Any_Name();

        void                            Log_Factions_And_Ranks(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Actor_t) == 0x2B0);

}
