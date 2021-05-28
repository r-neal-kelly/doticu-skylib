/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/havok_actor_controller.h"
#include "doticu_skylib/havok_player.h"
#include "doticu_skylib/havok_player_controller.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/quest_objective.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_input.h"
#include "doticu_skylib/virtual_utility.h"

namespace doticu_skylib {

    some<Player_t*> Player_t::Self()
    {
        return Const::Actor::Player();
    }

    maybe<Havok_Player_t*> Player_t::Havok_Player()
    {
        maybe<Havok_Player_Controller_t*> player_controller = Havok_Player_Controller();
        if (player_controller) {
            return player_controller->player_base.Player();
        } else {
            return none<Havok_Player_t*>();
        }
    }

    maybe<Havok_Player_Controller_t*> Player_t::Havok_Player_Controller()
    {
        maybe<Havok_Actor_Controller_t*> actor_controller = Havok_Actor_Controller();
        if (actor_controller) {
            return Game_t::Runtime_Cast<Havok_Actor_Controller_t, Havok_Player_Controller_t>(actor_controller());
        } else {
            return none<Havok_Player_Controller_t*>();
        }
    }

    u32 Player_t::Teammate_Count()
    {
        return teammate_count.Atomic_Count();
    }

    u32 Player_t::Increment_Teammate_Count()
    {
        return teammate_count.Increment_Atomic();
    }

    u32 Player_t::Decrement_Teammate_Count()
    {
        return teammate_count.Decrement_Atomic();
    }

    maybe<Relation_Counts_t*> Player_t::Relation_Counts(some<Faction_t*> faction)
    {
        SKYLIB_ASSERT_SOME(faction);

        maybe<Hash_Map_t<maybe<Faction_t*>, Relation_Counts_t>::Entry_t*> entry = friend_counts_map.Entry(faction);
        if (entry) {
            return &entry->second;
        } else {
            return none<Relation_Counts_t*>();
        }
    }

    void Player_t::Iterate_Player_Objectives(Iterator_i<some<Player_Objective_t*>>& iterator,
                                             Read_Locker_t& forms_locker)
    {
        for (size_t idx = 0, end = this->objectives.Count(); idx < end; idx += 1) {
            some<Player_Objective_t*> player_objective = &this->objectives[idx];
            if (iterator(player_objective) == Iterator_e::BREAK) {
                return;
            }
        }
    }

    void Player_t::Iterate_Player_Objectives(Iterator_i<some<Player_Objective_t*>>& iterator, Read_Write_Lock_t& forms_lock)
    {
        Read_Locker_t locker(forms_lock);
        Iterate_Player_Objectives(iterator, locker);
    }

    maybe<Player_Objective_t> Player_t::Highest_Displayed_Player_Objective(some<Quest_t*> quest, Read_Locker_t& forms_locker)
    {
        maybe<Player_Objective_t> result = none<Player_Objective_t>();
        for (size_t idx = 0, end = this->objectives.Count(); idx < end; idx += 1) {
            Player_Objective_t& it = this->objectives[idx];
            if (it.objective &&
                it.objective->quest == quest &&
                it.instance_id == quest->current_instance_id &&
                it.objective->Is_Displayed()) {
                if (!result.Has_Value() || result.Value().objective->index < it.objective->index) {
                    result = it;
                }
            }
        }
        return result;
    }

    maybe<Player_Objective_t> Player_t::Highest_Displayed_Player_Objective(some<Quest_t*> quest, Read_Write_Lock_t& forms_lock)
    {
        Read_Locker_t locker(forms_lock);
        return Highest_Displayed_Player_Objective(quest, locker);
    }

    Vector_t<some<Quest_Objective_t*>> Player_t::Quest_Objectives(Read_Locker_t& forms_locker)
    {
        Vector_t<some<Quest_Objective_t*>> results;
        Quest_Objectives(results, forms_locker);
        return results;
    }

    void Player_t::Quest_Objectives(Vector_t<some<Quest_Objective_t*>>& results,
                                    Read_Locker_t& forms_locker)
    {
        for (size_t idx = 0, end = this->objectives.Count(); idx < end; idx += 1) {
            maybe<Quest_Objective_t*> quest_objective = this->objectives[idx].objective;
            if (quest_objective && !results.Has(quest_objective())) {
                results.push_back(quest_objective());
            }
        }
    }

    Vector_t<some<Quest_Objective_t*>> Player_t::Quest_Objectives(Filter_i<some<Quest_Objective_t*>>& filter,
                                                                  Read_Locker_t& forms_locker)
    {
        Vector_t<some<Quest_Objective_t*>> results;
        Quest_Objectives(results, filter, forms_locker);
        return results;
    }

    void Player_t::Quest_Objectives(Vector_t<some<Quest_Objective_t*>>& results,
                                    Filter_i<some<Quest_Objective_t*>>& filter,
                                    Read_Locker_t& forms_locker)
    {
        for (size_t idx = 0, end = this->objectives.Count(); idx < end; idx += 1) {
            maybe<Quest_Objective_t*> quest_objective = this->objectives[idx].objective;
            if (quest_objective && !results.Has(quest_objective()) && filter(quest_objective())) {
                results.push_back(quest_objective());
            }
        }
    }

    void Player_t::Open_Inventory(maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Close_Menus_Callback :
            public Callback_i<Bool_t>
        {
        public:
            Callback callback;

        public:
            Close_Menus_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Bool_t) override
            {
                class Tap_Inventory_Key_Callback :
                    public Virtual::Callback_t
                {
                public:
                    Callback callback;

                public:
                    Tap_Inventory_Key_Callback(Callback callback) :
                        callback(std::move(callback))
                    {
                    }

                public:
                    virtual void operator()(Virtual::Variable_t*) override
                    {
                        class Wait_Callback :
                            public Virtual::Callback_t
                        {
                        public:
                            Callback callback;

                        public:
                            Wait_Callback(Callback callback) :
                                callback(std::move(callback))
                            {
                            }

                        public:
                            virtual void operator()(Virtual::Variable_t*) override
                            {
                                if (this->callback) {
                                    (*this->callback)();
                                }
                            }
                        };
                        Virtual::Utility_t::Wait_Out_Of_Menu(0.1f, new Wait_Callback(std::move(this->callback)));
                    }
                };
                Virtual::Input_t::Tap_Inventory_Key(new Tap_Inventory_Key_Callback(std::move(this->callback)));
            }
        };
        Virtual::Input_t::Close_Menus(new Close_Menus_Callback(std::move(callback)));
    }

    void Player_t::Log_Objectives(std::string indent)
    {
        SKYLIB_LOG(indent + "Player_t::Log_Objectives");
        SKYLIB_LOG(indent + "{");

        for (size_t idx = 0, end = objectives.Count(); idx < end; idx += 1) {
            Player_Objective_t& player_objective = objectives[idx];
            SKYLIB_LOG(indent + SKYLIB_TAB + "index: %zu", idx);
            player_objective.Log(indent + SKYLIB_TAB SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

}
