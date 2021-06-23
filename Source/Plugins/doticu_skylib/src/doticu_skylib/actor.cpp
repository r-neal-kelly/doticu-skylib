/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/actor_ai.h"
#include "doticu_skylib/actor_ai_cached_values.h"
#include "doticu_skylib/actor_ai_processor.h"
#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/actor_high_ai.h"
#include "doticu_skylib/actor_middle_high_ai.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/atomic_number.inl"
#include "doticu_skylib/cell.h"
#include "doticu_skylib/const_actors.h"
#include "doticu_skylib/const_keywords.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/enum_virtual_relation.h"
#include "doticu_skylib/extra_container_changes.h"
#include "doticu_skylib/extra_factions.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/havok_actor_controller.h"
#include "doticu_skylib/havok_actor_rigid_body_controller.h"
#include "doticu_skylib/interface.inl"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/leveled_actor_base.h"
#include "doticu_skylib/location.h"
#include "doticu_skylib/math.h"
#include "doticu_skylib/misc.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/player.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/race.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/script.h"
#include "doticu_skylib/small_dynamic_array.inl"
#include "doticu_skylib/spell.h"
#include "doticu_skylib/unique.h"
#include "doticu_skylib/virtual_actor_base.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_input.h"
#include "doticu_skylib/virtual_machine.inl"
#include "doticu_skylib/virtual_utility.h"
#include "doticu_skylib/virtual_variable.inl"
#include "doticu_skylib/weapon.h"
#include "doticu_skylib/worldspace.h"

namespace doticu_skylib {

    Vector_t<some<Actor_t*>> Actor_t::All()
    {
        Vector_t<some<Actor_t*>> results;
        All(results);
        return results;
    }

    void Actor_t::All(Vector_t<some<Actor_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Actor_t*>>& results;

        public:
            Iterator(Vector_t<some<Actor_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Actor_t*> actor = form->As_Actor();
                if (actor && actor->Is_Valid()) {
                    this->results.push_back(actor());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(2048);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Actor_t*>> Actor_t::All(Filter_i<some<Actor_t*>>& filter)
    {
        Vector_t<some<Actor_t*>> results;
        All(results, filter);
        return results;
    }

    void Actor_t::All(Vector_t<some<Actor_t*>>& results, Filter_i<some<Actor_t*>>& filter)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Actor_t*>>& results;
            Filter_i<some<Actor_t*>>& filter;

        public:
            Iterator(Vector_t<some<Actor_t*>>& results, Filter_i<some<Actor_t*>>& filter) :
                results(results), filter(filter)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Actor_t*> actor = form->As_Actor();
                if (actor && actor->Is_Valid() && this->filter(actor())) {
                    this->results.push_back(actor());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(2048);

        Iterator iterator(results, filter);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Actor_t*>> Actor_t::All_Actors_In_Cells()
    {
        Vector_t<some<Actor_t*>> results;
        All_Actors_In_Cells(results);
        return results;
    }

    void Actor_t::All_Actors_In_Cells(Vector_t<some<Actor_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Actor_t*>>& results;

        public:
            Iterator(Vector_t<some<Actor_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Actor_t*> actor = form->As_Actor();
                if (actor && actor->Is_Valid() && actor->Cell(true)) {
                    this->results.push_back(actor());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(2048);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    maybe<Actor_t*> Actor_t::Create(some<Form_t*> base, Bool_t do_persist, Bool_t do_pacify)
    {
        SKYLIB_ASSERT_SOME(base);

        if (base->Is_Valid()) {
            maybe<Actor_t*> actor = static_cast<maybe<Actor_t*>>
                (Reference_t::Create(base, 1, Player_t::Self()(), do_persist, false, false));
            if (actor && actor->Is_Valid()) {
                if (do_pacify) {
                    actor->Pacify();
                }
                return actor;
            } else {
                return nullptr;
            }
        } else {
            return nullptr;
        }
    }

    maybe<Actor_t*> Actor_t::Create(some<Actor_Base_t*> base, Bool_t do_persist, Bool_t do_pacify, Bool_t do_static)
    {
        SKYLIB_ASSERT_SOME(base);

        if (do_static) {
            if (base->Is_Valid()) {
                return Create(static_cast<some<Form_t*>>(base->Base_Root()), do_persist, do_pacify);
            } else {
                return nullptr;
            }
        } else {
            return Create(static_cast<some<Form_t*>>(base), do_persist, do_pacify);
        }
    }

    maybe<Actor_t*> Actor_t::Create(some<Leveled_Actor_Base_t*> base, Bool_t do_persist, Bool_t do_pacify, Bool_t do_static)
    {
        SKYLIB_ASSERT_SOME(base);

        if (do_static) {
            if (base->Is_Valid()) {
                maybe<Actor_t*> actor = static_cast<maybe<Actor_t*>>
                    (Reference_t::Create(base, 1, Player_t::Self()(), false, true, false));
                if (actor && actor->Is_Valid()) {
                    maybe<Actor_Base_t*> actor_base = actor->Actor_Base();
                    actor->Mark_For_Delete();
                    if (actor_base) {
                        return Create(actor_base(), do_static, do_persist, do_pacify);
                    } else {
                        return nullptr;
                    }
                } else {
                    return nullptr;
                }
            } else {
                return nullptr;
            }
        } else {
            return Create(static_cast<some<Form_t*>>(base), do_persist, do_pacify);
        }
    }

    Bool_t Actor_t::Is_Unique()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Is_Unique();
        } else {
            return false;
        }
    }

    Bool_t Actor_t::Is_Generic()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Is_Generic();
        } else {
            return false;
        }
    }

    Bool_t Actor_t::Is_Child()
    {
        return Get_Is_Child();
    }

    Bool_t Actor_t::Isnt_Child()
    {
        return !Is_Child();
    }

    Bool_t Actor_t::Is_Vampire()
    {
        return Has_Keyword(Const::Keyword::Vampire());
    }

    Bool_t Actor_t::Isnt_Vampire()
    {
        return !Is_Vampire();
    }

    Bool_t Actor_t::Is_In_Combat()
    {
        return Get_Is_In_Combat();
    }

    Bool_t Actor_t::Isnt_In_Combat()
    {
        return !Is_In_Combat();
    }

    Bool_t Actor_t::Is_Owner_Of(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        return reference->Has_Owner(this);
    }

    Bool_t Actor_t::Is_Potential_Thief_Of(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        return reference->Has_Potential_Thief(this);
    }

    Bool_t Actor_t::Has_Mount()
    {
        return !!Mount();
    }

    Bool_t Actor_t::Has_Rider()
    {
        return !!Rider();
    }

    Bool_t Actor_t::Has_Actor_Base(some<Actor_Base_t*> actor_base)
    {
        SKYLIB_ASSERT_SOME(actor_base);

        maybe<Actor_Base_t*> this_actor_base = Actor_Base();
        if (this_actor_base) {
            return this_actor_base() == actor_base();
        } else {
            return false;
        }
    }

    Bool_t Actor_t::Hasnt_Actor_Base(some<Actor_Base_t*> actor_base)
    {
        SKYLIB_ASSERT_SOME(actor_base);
        return !Has_Actor_Base(actor_base);
    }

    Bool_t Actor_t::Is_In_Faction(some<Faction_t*> faction)
    {
        SKYLIB_ASSERT_SOME(faction);
        return Get_Is_In_Faction(faction());
    }

    Bool_t Actor_t::Isnt_In_Faction(some<Faction_t*> faction)
    {
        SKYLIB_ASSERT_SOME(faction);
        return !Get_Is_In_Faction(faction());
    }

    Sex_e Actor_t::Sex()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Sex();
        } else {
            return Sex_e::_NONE_;
        }
    }

    maybe<Race_t*> Actor_t::Race()
    {
        if (this->race) {
            return this->race;
        } else {
            maybe<Actor_Base_t*> actor_base = Actor_Base();
            if (actor_base) {
                return actor_base->Race();
            } else {
                return none<Race_t*>();
            }
        }
    }

    u16 Actor_t::Level() const
    {
        static auto get_level = reinterpret_cast
            <u16(*)(const Actor_t*)>
            (Game_t::Base_Address() + Offset_e::GET_LEVEL);

        return get_level(this);
    }

    maybe<Havok_Actor_Controller_t*> Actor_t::Havok_Actor_Controller()
    {
        if (this->actor_ai && this->actor_ai->middle_high_ai) {
            return this->actor_ai->middle_high_ai->havok_actor_controller;
        } else {
            return none<Havok_Actor_Controller_t*>();
        }
    }

    maybe<Havok_Actor_Rigid_Body_Controller_t*> Actor_t::Havok_Actor_Rigid_Body_Controller()
    {
        maybe<Havok_Actor_Controller_t*> actor_controller = Havok_Actor_Controller();
        if (actor_controller) {
            return Game_t::Runtime_Cast<Havok_Actor_Controller_t, Havok_Actor_Rigid_Body_Controller_t>(actor_controller());
        } else {
            return nullptr;
        }
    }

    Vector_t<Keyword_t*> Actor_t::Keywords(Bool_t include_templates)
    {
        Vector_t<Keyword_t*> results;
        Keywords(results, include_templates);
        return results;
    }

    void Actor_t::Keywords(Vector_t<Keyword_t*>& results, Bool_t include_templates)
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base && actor_base->Is_Valid()) {
            actor_base->Keywords(results, include_templates);
        }
    }

    maybe<Actor_t*> Actor_t::Mount()
    {
        return this->x_list.Reference_Interactor_A();
    }

    maybe<Actor_t*> Actor_t::Rider()
    {
        return this->x_list.Reference_Interactor_B();
    }

    maybe<Actor_Base_t*> Actor_t::Actor_Base()
    {
        if (this->base_form) {
            return this->base_form->As_Actor_Base();
        } else {
            return none<Actor_Base_t*>();
        }
    }

    void Actor_t::Actor_Base(some<Actor_Base_t*> actor_base, Bool_t do_save)
    {
        SKYLIB_ASSERT_SOME(actor_base);

        this->base_form = actor_base();

        if (do_save) {
            // not sure if this works yet.
            Flag_Form_Change(Reference_t::Form_Change_Flags_e::BASE_FORM);
        }
    }

    maybe<Actor_Base_t*> Actor_t::Actor_Base_Root()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Base_Root()();
        } else {
            return none<Actor_Base_t*>();
        }
    }

    maybe<Actor_Base_t*> Actor_t::Actor_Base_Template_Root()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Template_Root()();
        } else {
            return none<Actor_Base_t*>();
        }
    }

    maybe<Actor_Base_t*> Actor_t::Identifiable_Static_Actor_Base()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Identifiable_Static_Base();
        } else {
            return none<Actor_Base_t*>();
        }
    }

    Vector_t<Actor_Base_t*> Actor_t::Actor_Bases()
    {
        if (base_form && base_form->Is_Valid()) {
            Vector_t<Actor_Base_t*> results;
            results.reserve(4);
            Actor_Bases(results);
            return results;
        } else {
            return Vector_t<Actor_Base_t*>();
        }
    }

    void Actor_t::Actor_Bases(Vector_t<Actor_Base_t*>& results)
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base && base_form->Is_Valid()) {
            results.push_back(actor_base());
            actor_base->Templates(results);
        }
    }

    maybe<Outfit_t*> Actor_t::Base_Default_Outfit()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Default_Outfit();
        } else {
            return none<Outfit_t*>();
        }
    }

    void Actor_t::Base_Default_Outfit(maybe<Outfit_t*> outfit)
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            actor_base->Default_Outfit(outfit);
        }
    }

    maybe<Outfit_t*> Actor_t::Base_Sleep_Outfit()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Sleep_Outfit();
        } else {
            return none<Outfit_t*>();
        }
    }

    void Actor_t::Base_Sleep_Outfit(maybe<Outfit_t*> outfit)
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            actor_base->Sleep_Outfit(outfit);
        }
    }

    maybe<Voice_Type_t*> Actor_t::Base_Voice_Type()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Voice_Type();
        } else {
            return none<Voice_Type_t*>();
        }
    }

    void Actor_t::Base_Voice_Type(maybe<Voice_Type_t*> voice_type)
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            actor_base->Voice_Type(voice_type);
        }
    }

    maybe<Voice_Type_t*> Actor_t::Race_Voice_Type()
    {
        maybe<Race_t*> race = Race();
        if (race) {
            maybe<Actor_Base_t*> actor_base = Actor_Base();
            if (actor_base) {
                if (actor_base->Is_Female()) {
                    return race->voice_types[1];
                } else {
                    return race->voice_types[0];
                }
            } else {
                return race->voice_types[0]; // I think 0 is male, and 1 female, need to verify.
            }
        } else {
            return none<Voice_Type_t*>();
        }
    }

    void Actor_t::Race_Voice_Type(maybe<Voice_Type_t*> voice_type)
    {
        maybe<Race_t*> race = Race();
        if (race) {
            maybe<Actor_Base_t*> actor_base = Actor_Base();
            if (actor_base) {
                if (actor_base->Is_Female()) {
                    race->voice_types[1] = voice_type;
                } else {
                    race->voice_types[0] = voice_type;
                }
            } else {
                race->voice_types[0] = voice_type;
            }
        }
    }

    maybe<Voice_Type_t*> Actor_t::Voice_Type()
    {
        maybe<Voice_Type_t*> base_voice_type = Base_Voice_Type();
        if (base_voice_type) {
            return base_voice_type;
        } else {
            maybe<Voice_Type_t*> race_voice_type = Race_Voice_Type();
            if (race_voice_type) {
                return race_voice_type;
            } else {
                return none<Voice_Type_t*>();
            }
        }
    }

    maybe<Actor_AI_t*> Actor_t::Actor_AI()
    {
        return this->actor_ai;
    }

    maybe<Actor_High_AI_t*> Actor_t::Actor_High_AI()
    {
        if (this->actor_ai) {
            return this->actor_ai->high_ai;
        } else {
            return none<Actor_High_AI_t*>();
        }
    }

    const char* Actor_t::Base_Name()
    {
        if (base_form) {
            return static_cast<maybe<Actor_Base_t*>>(base_form)->Name();
        } else {
            return "";
        }
    }

    String_t Actor_t::Any_Name()
    {
        const char* name = Name();
        if (!name || !name[0]) {
            name = Base_Name();
            if (!name || !name[0]) {
                name = Get_Editor_ID();
                if (!name || !name[0]) {
                    return Form_ID_String();
                } else {
                    return name;
                }
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

    maybe<Raw_Faction_Rank_t> Actor_t::Faction_Rank(some<Faction_t*> faction)
    {
        SKYLIB_ASSERT_SOME(faction);

        maybe<Raw_Faction_Rank_t> rank = this->x_list.Faction_Rank(faction);
        if (rank.Has_Value()) {
            return rank;
        } else {
            return Base_Faction_Rank(faction);
        }
    }

    void Actor_t::Faction_Rank(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank)
    {
        SKYLIB_ASSERT_SOME(faction);

        this->x_list.Faction_Rank(faction, rank);
    }

    maybe<Raw_Faction_Rank_t> Actor_t::Base_Faction_Rank(some<Faction_t*> faction)
    {
        SKYLIB_ASSERT_SOME(faction);

        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Faction_Rank(faction);
        } else {
            return none<Raw_Faction_Rank_t>();
        }
    }

    void Actor_t::Base_Faction_Rank(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank)
    {
        SKYLIB_ASSERT_SOME(faction);

        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            actor_base->Faction_Rank(faction, rank);
        }
    }

    Vector_t<Faction_And_Rank_t> Actor_t::Factions_And_Ranks(Bool_t remove_negatives)
    {
        Vector_t<Faction_And_Rank_t> results;
        Factions_And_Ranks(results, remove_negatives);
        return results;
    }

    void Actor_t::Factions_And_Ranks(Vector_t<Faction_And_Rank_t>& results, Bool_t remove_negatives)
    {
        Factions_And_Ranks_t* base_factions_and_ranks = nullptr;
        Factions_And_Ranks_t* reference_factions_and_ranks = nullptr;
        size_t reserve_count = 0;

        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base && actor_base->Is_Valid()) {
            base_factions_and_ranks = &actor_base->factions_and_ranks;
            reserve_count += base_factions_and_ranks->Count();
        }

        maybe<Extra_Factions_t*> xfactions = x_list.Get<Extra_Factions_t>();
        if (xfactions) {
            reference_factions_and_ranks = &xfactions->factions_and_ranks;
            reserve_count += reference_factions_and_ranks->Count();
        }

        Vector_t<Faction_And_Rank_t> buffer;
        Vector_t<Faction_And_Rank_t>* output;
        if (remove_negatives) {
            output = &buffer;
            buffer.reserve(reserve_count);
            results.reserve(reserve_count);
        } else {
            output = &results;
            results.reserve(reserve_count);
        }

        if (base_factions_and_ranks) {
            for (size_t idx = 0, end = base_factions_and_ranks->Count(); idx < end; idx += 1) {
                Faction_And_Rank_t& faction_and_rank = base_factions_and_ranks->At(idx);
                if (faction_and_rank.Is_Valid()) {
                    maybe<size_t> output_idx = output->Index_Of(faction_and_rank, &Faction_And_Rank_t::Has_Same_Faction);
                    if (output_idx.Has_Value()) {
                        output->at(output_idx.Value()).rank = faction_and_rank.rank;
                    } else {
                        output->push_back(faction_and_rank);
                    }
                }
            }
        }

        if (reference_factions_and_ranks) {
            for (size_t idx = 0, end = reference_factions_and_ranks->Count(); idx < end; idx += 1) {
                Faction_And_Rank_t& faction_and_rank = reference_factions_and_ranks->At(idx);
                if (faction_and_rank.Is_Valid()) {
                    maybe<size_t> output_idx = output->Index_Of(faction_and_rank, &Faction_And_Rank_t::Has_Same_Faction);
                    if (output_idx.Has_Value()) {
                        output->at(output_idx.Value()).rank = faction_and_rank.rank;
                    } else {
                        output->push_back(faction_and_rank);
                    }
                }
            }
        }

        if (remove_negatives) {
            for (size_t idx = 0, end = buffer.size(); idx < end; idx += 1) {
                Faction_And_Rank_t& faction_and_rank = buffer[idx];
                if (faction_and_rank.rank > -1) {
                    results.push_back(faction_and_rank);
                }
            }
        }
    }

    maybe<Faction_t*> Actor_t::Crime_Faction()
    {
        maybe<Faction_t*> crime_faction = this->x_list.Crime_Faction();
        if (crime_faction) {
            return crime_faction;
        } else {
            return Base_Crime_Faction();
        }
    }

    void Actor_t::Crime_Faction(some<Faction_t*> crime_faction)
    {
        SKYLIB_ASSERT_SOME(crime_faction);

        this->x_list.Crime_Faction(crime_faction());
    }

    maybe<Faction_t*> Actor_t::Base_Crime_Faction()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Crime_Faction();
        } else {
            return none<Faction_t*>();
        }
    }

    void Actor_t::Base_Crime_Faction(maybe<Faction_t*> crime_faction)
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            actor_base->Crime_Faction(crime_faction);
        }
    }

    some<Relation_e> Actor_t::Base_Relation(some<Actor_Base_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Relation(other);
        } else {
            return Relation_e::_DEFAULT_;
        }
    }

    void Actor_t::Base_Relation(some<Actor_Base_t*> other, some<Relation_e> relation)
    {
        SKYLIB_ASSERT_SOME(other);
        SKYLIB_ASSERT_SOME(relation);

        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            actor_base->Relation(other, relation);
        }
    }

    Bool_t Actor_t::Is_Player_Teammate()
    {
        return this->actor_flags_1.Is_Flagged(Actor_Flags_1_e::IS_PLAYER_TEAMMATE);
    }

    void Actor_t::Is_Player_Teammate(Bool_t value)
    {
        some<Player_t*> player = Player_t::Self();
        if (this != player()) {
            if (value) {
                if (!Is_Player_Teammate()) {
                    this->actor_flags_1.Flag(Actor_Flags_1_e::IS_PLAYER_TEAMMATE);
                    player->Increment_Teammate_Count();
                }
            } else {
                if (Is_Player_Teammate()) {
                    this->actor_flags_1.Unflag(Actor_Flags_1_e::IS_PLAYER_TEAMMATE);
                    player->Decrement_Teammate_Count();
                }
            }
        }
    }

    Bool_t Actor_t::Can_Do_Favors()
    {
        return this->actor_flags_2.Is_Flagged(Actor_Flags_2_e::CAN_DO_FAVORS);
    }

    void Actor_t::Can_Do_Favors(Bool_t value)
    {
        if (value) {
            this->actor_flags_2.Flag(Actor_Flags_2_e::CAN_DO_FAVORS);
        } else {
            this->actor_flags_2.Unflag(Actor_Flags_2_e::CAN_DO_FAVORS);
        }
    }

    Bool_t Actor_t::Can_Talk_To_Player()
    {
        maybe<Bool_t> can_talk_to_player = this->x_list.Can_Talk_To_Player();
        if (can_talk_to_player.Has_Value()) {
            return can_talk_to_player.Value();
        } else {
            maybe<Race_t*> race = Race();
            if (race) {
                return race->Can_Talk_To_Player();
            } else {
                return false;
            }
        }
    }

    void Actor_t::Can_Talk_To_Player(Bool_t value)
    {
        if (Can_Talk_To_Player() != value) {
            this->x_list.Can_Talk_To_Player(value);
        }
    }

    Bool_t Actor_t::Ignores_Ally_Hits()
    {
        return this->form_flags.Is_Flagged(Form_Flags_e::IGNORES_ALLY_HITS);
    }

    void Actor_t::Ignores_Ally_Hits(Bool_t value)
    {
        if (value) {
            this->form_flags.Flag(Form_Flags_e::IGNORES_ALLY_HITS);
        } else {
            this->form_flags.Unflag(Form_Flags_e::IGNORES_ALLY_HITS);
        }
        Flag_Form_Change(Form_Change_Flags_e::FORM_FLAGS);
    }

    Bool_t Actor_t::Is_Hidden_From_Stealth_Eye()
    {
        return this->actor_flags_2.Is_Flagged(Actor_Flags_2_e::IS_HIDDEN_FROM_STEALTH_EYE);
    }

    void Actor_t::Is_Hidden_From_Stealth_Eye(Bool_t value)
    {
        if (value) {
            this->actor_flags_2.Flag(Actor_Flags_2_e::IS_HIDDEN_FROM_STEALTH_EYE);
        } else {
            this->actor_flags_2.Unflag(Actor_Flags_2_e::IS_HIDDEN_FROM_STEALTH_EYE);
        }
    }

    Bool_t Actor_t::Has_AI()
    {
        return this->actor_flags_1.Is_Flagged(Actor_Flags_1_e::DO_PROCESS_AI);
    }

    void Actor_t::Has_AI(Bool_t value)
    {
        if (value) {
            this->actor_flags_1.Flag(Actor_Flags_1_e::DO_PROCESS_AI);
        } else {
            this->actor_flags_1.Unflag(Actor_Flags_1_e::DO_PROCESS_AI);
        }
    }

    void Actor_t::Reset_AI()
    {
        Evaluate_Package(false, true);
    }

    Bool_t Actor_t::Add_Spell(some<Spell_t*> spell)
    {
        static auto add_spell = reinterpret_cast
            <Bool_t(*)(Actor_t*, Spell_t*)>
            (Game_t::Base_Address() + Offset_e::ADD_SPELL);

        SKYLIB_ASSERT_SOME(spell);

        return add_spell(this, spell());
    }

    Bool_t Actor_t::Remove_Spell(some<Spell_t*> spell)
    {
        static auto remove_spell = reinterpret_cast
            <Bool_t(*)(Actor_t*, Spell_t*)>
            (Game_t::Base_Address() + Offset_e::REMOVE_SPELL);

        SKYLIB_ASSERT_SOME(spell);

        return remove_spell(this, spell());
    }

    void Actor_t::Reset_Spell(some<Spell_t*> spell)
    {
        SKYLIB_ASSERT_SOME(spell);

        Remove_Spell(spell);
        Add_Spell(spell);
    }

    Bool_t Actor_t::Is_Ghost()
    {
        maybe<Bool_t> is_ghost = this->x_list.Is_Ghost();
        if (is_ghost.Has_Value()) {
            return is_ghost.Value();
        } else {
            maybe<Actor_Base_t*> actor_base = Actor_Base();
            if (actor_base) {
                return actor_base->Is_Ghost();
            } else {
                return false;
            }
        }
    }

    void Actor_t::Is_Ghost(Bool_t value)
    {
        if (Is_Ghost() != value) {
            this->x_list.Is_Ghost(value);
            if (this->actor_ai && this->actor_ai->cached_values) {
                this->actor_ai->cached_values->Is_Ghost(value);
            }
        }
    }

    Bool_t Actor_t::Can_Autostart_Bard_Performance()
    {
        static some<Faction_t*> bard_singer_no_autostart_faction = static_cast<Faction_t*>(Game_t::Form(0x000163FA)());
        SKYLIB_ASSERT_SOME(bard_singer_no_autostart_faction);

        return !Is_In_Faction(bard_singer_no_autostart_faction);
    }

    void Actor_t::Can_Autostart_Bard_Performance(Bool_t value)
    {
        static some<Faction_t*> bard_singer_no_autostart_faction = static_cast<Faction_t*>(Game_t::Form(0x000163FA)());
        SKYLIB_ASSERT_SOME(bard_singer_no_autostart_faction);

        Faction_Rank(bard_singer_no_autostart_faction, value ? -1 : 0);
    }

    Bool_t Actor_t::Can_Be_Resurrected()
    {
        return !this->form_flags.Is_Flagged(Form_Flags_e::STARTS_DEAD);
    }

    void Actor_t::Can_Be_Resurrected(Bool_t value)
    {
        if (value) {
            this->form_flags.Unflag(Form_Flags_e::STARTS_DEAD);
        } else {
            this->form_flags.Flag(Form_Flags_e::STARTS_DEAD);
        }
    }

    void Actor_t::Evaluate_Package(Bool_t do_immediately, Bool_t do_reset_ai)
    {
        static auto evaluate_package = reinterpret_cast
            <void(*)(Actor_t*, Bool_t, Bool_t)>
            (Game_t::Base_Address() + Offset_e::EVALUATE_PACKAGE);

        return evaluate_package(this, do_immediately, do_reset_ai);
    }

    void Actor_t::Pacify()
    {
        Set_Default_Actor_Value(Actor_Value_Type_e::AGGRESSION, 0.0f);
        Stop_Combat_And_Alarm();
        this->actor_flags_2.Unflag(Actor_Flags_2_e::IS_ANGRY_WITH_PLAYER);
        Reset_AI();
    }

    void Actor_t::Queue_NI_Node_Update(Bool_t do_update_weight)
    {
        static auto queue_ni_node_update = reinterpret_cast
            <void(*)(Actor_t*, Bool_t)>
            (Game_t::Base_Address() + Offset_e::QUEUE_NI_NODE_UPDATE);

        return queue_ni_node_update(this, do_update_weight);
    }

    void Actor_t::Reset_Actor_Value(Actor_Value_Type_e actor_value_type)
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            Set_Default_Actor_Value(actor_value_type, actor_base->Get_Default_Actor_Value(actor_value_type));
        }
    }

    void Actor_t::Stop_Combat()
    {
        Do_Stop_Combat();
    }

    void Actor_t::Stop_Combat_And_Alarm()
    {
        Actor_AI_Processor_t::Self()->Stop_Combat_And_Alarm(this, false);
    }

    void Actor_t::Update_3D(maybe<Script_t*> script)
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            Float_t weight = actor_base->Weight();
            Base_Weight(weight, script);
        }
    }

    void Actor_t::Update_Equipment()
    {
        static some<Weapon_t*> iron_sword = static_cast<Weapon_t*>(Game_t::Form(0x00012EB7)());
        SKYLIB_ASSERT(iron_sword);

        Add_Item(iron_sword, 0);
    }

    maybe<Actor_t*> Actor_t::Current_Combat_Target()
    {
        return static_cast<Actor_t*>(Reference_t::From_Handle(Atomic_t::Access(this->current_combat_target)));
    }

    Float_t Actor_t::Alpha()
    {
        return Get_Alpha();
    }

    void Actor_t::Alpha(Float_t alpha, maybe<Script_t*> script)
    {
        maybe<unique<Script_t>> temp;
        if (!script) {
            temp = Script_t::Create()();
            script = temp();
        }
        script->Command(std::string("SetActorAlpha ") + std::to_string(alpha));
        script->Execute(this);
    }

    Float_t Actor_t::Base_Weight()
    {
        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            return actor_base->Weight();
        } else {
            return 50.0f;
        }
    }

    void Actor_t::Base_Weight(Float_t weight, maybe<Script_t*> script)
    {
        maybe<unique<Script_t>> temp;
        if (!script) {
            temp = Script_t::Create()();
            script = temp();
        }
        script->Command(std::string("SetNPCWeight ") + std::to_string(weight));
        script->Execute(this);
    }

    void Actor_t::Is_Doing_Favor(Bool_t value, maybe<Script_t*> script)
    {
        maybe<unique<Script_t>> temp;
        if (!script) {
            temp = Script_t::Create()();
            script = temp();
        }
        script->Command(std::string("SetFavorState ") + (value ? "1" : "0"));
        script->Execute(this);
    }

    Bool_t Actor_t::Is_Forced_To_Sneak()
    {
        return Actor_State_t::Is_Forced_To_Sneak();
    }

    void Actor_t::Is_Forced_To_Sneak(Bool_t value, maybe<Script_t*> script)
    {
        maybe<unique<Script_t>> temp;
        if (!script) {
            temp = Script_t::Create()();
            script = temp();
        }
        script->Command(std::string("SetForceSneak ") + (value ? "1" : "0"));
        script->Execute(this);
    }

    void Actor_t::Alpha(Float_t alpha, Bool_t do_fade_in, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Float_t alpha;
            Bool_t  do_fade_in;

        public:
            Virtual_Arguments(Float_t alpha, Bool_t do_fade_in) :
                alpha(alpha), do_fade_in(do_fade_in)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(2);
                args->At(0).As<Float_t>(this->alpha);
                args->At(1).As<Bool_t>(this->do_fade_in);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Actor_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "SetAlpha",
            Virtual_Arguments(alpha, do_fade_in),
            v_callback
        );
    }

    void Actor_t::Alpha(Float_t alpha, Bool_t do_fade_in, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
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

        Alpha(alpha, do_fade_in, new Virtual_Callback(std::move(callback)));
    }

    void Actor_t::Kill(maybe<Actor_t*> killer, Bool_t do_silently, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            some<Actor_t*> killer;

        public:
            Virtual_Arguments(some<Actor_t*> killer) :
                killer(killer)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Actor_t*>(this->killer());
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Actor_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            do_silently ? "KillSilent" : "Kill",
            Virtual_Arguments(killer ? killer() : this),
            v_callback
        );
    }

    void Actor_t::Kill(maybe<Actor_t*> killer, Bool_t do_silently, Bool_t do_force, maybe<unique<Callback_i<>>> callback)
    {
        // it would be nice if we could disable alias protect/essential. we could just cache the data and switch it back.

        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            some<Actor_t*>          actor;
            maybe<Actor_Base_t*>    actor_base;
            Bool_t                  do_force;
            Bool_t                  is_protected;
            Bool_t                  is_essential;
            Bool_t                  is_invulnerable;
            Callback                callback;

        public:
            Virtual_Callback(some<Actor_t*> actor, Bool_t do_force, Callback callback) :
                actor(actor),
                actor_base(actor->Actor_Base()),
                do_force(do_force),
                is_protected(false),
                is_essential(false),
                is_invulnerable(false),
                callback(std::move(callback))
            {
                if (this->do_force && this->actor_base) {
                    this->is_protected = this->actor_base->Is_Protected();
                    this->is_essential = this->actor_base->Is_Essential();
                    this->is_invulnerable = this->actor_base->Is_Invulnerable();
                    this->actor_base->Is_Mortal(true, false);
                }
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                class Wait_Callback :
                    public Virtual::Callback_t
                {
                public:
                    some<Actor_Base_t*> actor_base;
                    Bool_t              is_protected;
                    Bool_t              is_essential;
                    Bool_t              is_invulnerable;
                    Callback            callback;

                public:
                    Wait_Callback(some<Actor_Base_t*> actor_base,
                                  Bool_t is_protected,
                                  Bool_t is_essential,
                                  Bool_t is_invulnerable,
                                  Callback callback) :
                        actor_base(actor_base),
                        is_protected(is_protected),
                        is_essential(is_essential),
                        is_invulnerable(is_invulnerable),
                        callback(std::move(callback))
                    {
                    }

                public:
                    virtual void operator ()(Virtual::Variable_t*) override
                    {
                        if (this->is_invulnerable) {
                            this->actor_base->Is_Invulnerable(true, false);
                        }
                        if (this->is_essential) {
                            this->actor_base->Is_Essential(true, false);
                        } else if (this->is_protected) {
                            this->actor_base->Is_Protected(true, false);
                        }
                        if (this->callback) {
                            (*this->callback)();
                        }
                    }
                };
                if (this->do_force && this->actor_base) {
                    Virtual::Utility_t::Wait_Even_In_Menu(
                        2.0f,
                        new Wait_Callback(this->actor_base(),
                                          this->is_protected,
                                          this->is_essential,
                                          this->is_invulnerable,
                                          std::move(this->callback))
                    );
                } else {
                    if (this->callback) {
                        (*this->callback)();
                    }
                }
            }
        };

        if (Is_Alive()) {
            Kill(killer, do_silently, new Virtual_Callback(this, do_force, std::move(callback)));
        } else {
            if (callback) {
                (*callback)();
            }
        }
    }

    void Actor_t::Open_Inventory(Bool_t allow_non_teammates, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Bool_t allow_non_teammates;

        public:
            Virtual_Arguments(Bool_t allow_non_teammates) :
                allow_non_teammates(allow_non_teammates)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Bool_t>(this->allow_non_teammates);
                return true;
            }
        };

        Virtual::Machine_t::Ready_Scriptable<Actor_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "OpenInventory",
            Virtual_Arguments(allow_non_teammates),
            v_callback
        );
    }

    void Actor_t::Open_Inventory(Bool_t allow_non_teammates, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Close_Menus_Callback :
            public Callback_i<Bool_t>
        {
        public:
            some<Actor_t*>  self;
            Bool_t          allow_non_teammates;
            Callback        callback;

        public:
            Close_Menus_Callback(some<Actor_t*> self, Bool_t allow_non_teammates, Callback callback) :
                self(self), allow_non_teammates(allow_non_teammates), callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Bool_t) override
            {
                class Open_Inventory_Callback :
                    public Virtual::Callback_t
                {
                public:
                    Callback callback;

                public:
                    Open_Inventory_Callback(Callback callback) :
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
                this->self->Open_Inventory(this->allow_non_teammates, new Open_Inventory_Callback(std::move(this->callback)));
            }
        };

        if (this == Player_t::Self()()) {
            Player_t::Open_Inventory(std::move(callback));
        } else {
            Virtual::Input_t::Close_Menus(new Close_Menus_Callback(this, allow_non_teammates, std::move(callback)));
        }
    }

    void Actor_t::Resurrect(maybe<Virtual::Callback_i*> v_callback)
    {
        Virtual::Machine_t::Ready_Scriptable<Actor_t*>(this);
        Virtual::Machine_t::Self()->Call_Method(
            this,
            SCRIPT_NAME,
            "Resurrect",
            none<Virtual::Arguments_i*>(),
            v_callback
        );
    }

    void Actor_t::Resurrect(Bool_t do_keep_inventory, Bool_t do_pacify, Bool_t do_force, maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            some<Actor_t*>              actor;
            Bool_t                      do_keep_inventory;
            Bool_t                      do_pacify;
            Bool_t                      do_force;
            Callback                    callback;
            maybe<Actor_Base_t*>        original_actor_base;
            maybe<Container_Changes_t*> container_changes;
            Bool_t                      can_be_resurrected;

        public:
            Virtual_Callback(some<Actor_t*> actor,
                             Bool_t do_keep_inventory,
                             Bool_t do_pacify,
                             Bool_t do_force,
                             Callback callback) :
                actor(actor),
                do_keep_inventory(do_keep_inventory),
                do_pacify(do_pacify),
                do_force(do_force),
                callback(std::move(callback)),
                original_actor_base(nullptr),
                container_changes(nullptr),
                can_be_resurrected(false)
            {
                if (this->do_keep_inventory) {
                    this->original_actor_base = this->actor->Actor_Base();
                    if (this->original_actor_base) {
                        some<Actor_Base_t*> copy = Actor_Base_t::Create_Temporary_Copy(this->original_actor_base());
                        copy->container_entry_count = 0;
                        copy->default_outfit = nullptr;
                        this->actor->base_form = static_cast<maybe<Form_t*>>(copy());
                    }

                    maybe<Extra_Container_Changes_t*> x_container_changes = this->actor->Maybe_Extra_Container_Changes();
                    if (x_container_changes) {
                        this->container_changes = x_container_changes->container_changes;
                        x_container_changes->container_changes = nullptr;
                    }
                }
                if (this->do_force) {
                    this->can_be_resurrected = this->actor->Can_Be_Resurrected();
                    this->actor->Can_Be_Resurrected(true);
                }
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->do_pacify) {
                    this->actor->Pacify();
                }

                if (this->do_force) {
                    this->actor->Can_Be_Resurrected(this->can_be_resurrected);
                }

                if (this->do_keep_inventory) {
                    if (this->original_actor_base) {
                        maybe<Actor_Base_t*> copy = this->actor->Actor_Base();
                        this->actor->base_form = this->original_actor_base;
                        if (copy) {
                            Actor_Base_t::Destroy(copy());
                        }
                    }

                    if (this->container_changes) {
                        some<Extra_Container_Changes_t*> x_container_changes = this->actor->Some_Extra_Container_Changes();
                        maybe<Container_Changes_t*> old_container_changes = x_container_changes->container_changes;
                        x_container_changes->container_changes = this->container_changes;
                        if (old_container_changes) {
                            Container_Changes_t::Destroy(old_container_changes());
                        }
                    }

                    this->actor->Update_Equipment(std::move(callback));
                } else {
                    if (this->callback) {
                        (*this->callback)();
                    }
                }
            }
        };

        if (Is_Dead()) {
            Resurrect(new Virtual_Callback(this, do_keep_inventory, do_pacify, do_force, std::move(callback)));
        } else {
            if (callback) {
                (*callback)();
            }
        }
    }

    void Actor_t::Stop_Bard_Performance(maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        static some<Quest_t*> bard_songs_quest = static_cast<Quest_t*>(Game_t::Form(0x00074A55)());
        static some<Quest_t*> bard_songs_instrumental_quest = static_cast<Quest_t*>(Game_t::Form(0x0006E53F)());
        SKYLIB_ASSERT_SOME(bard_songs_quest);
        SKYLIB_ASSERT_SOME(bard_songs_instrumental_quest);

        Vector_t<some<Alias_Reference_t*>> bard_aliases;
        Vector_t<some<Alias_Reference_t*>> aliases = this->x_list.Alias_References();
        for (size_t idx = 0, end = aliases.size(); idx < end; idx += 1) {
            some<Alias_Reference_t*> alias = aliases[idx];
            if ((alias->quest() == bard_songs_quest() && alias->id != 24) ||
                (alias->quest() == bard_songs_instrumental_quest())) {
                bard_aliases.push_back(alias);
            }
        }

        if (bard_aliases.size() > 0) {
            class Stop_All_Songs_Callback :
                public Virtual::Callback_t
            {
            public:
                some<Actor_t*>                      actor;
                Vector_t<some<Alias_Reference_t*>>  bard_aliases;
                Callback                            callback;

            public:
                Stop_All_Songs_Callback(some<Actor_t*> actor,
                                        Vector_t<some<Alias_Reference_t*>> bard_aliases,
                                        Callback callback) :
                    actor(actor),
                    bard_aliases(std::move(bard_aliases)),
                    callback(std::move(callback))
                {
                }

            public:
                virtual void operator ()(Virtual::Variable_t*) override
                {
                    class Unfill_Callback :
                        public doticu_skylib::Callback_i<>
                    {
                    public:
                        some<Actor_t*>  actor;
                        Callback        callback;

                    public:
                        Unfill_Callback(some<Actor_t*> actor, Callback callback) :
                            actor(actor), callback(std::move(callback))
                        {
                        }

                    public:
                        virtual void operator ()() override
                        {
                            this->actor->Reset_AI();
                            if (this->callback) {
                                (*this->callback)();
                            }
                        }
                    };

                    Alias_Reference_t::Unfill(
                        std::move(this->bard_aliases),
                        new Unfill_Callback(this->actor, std::move(this->callback))
                    );
                }
            };

            Virtual::Machine_t::Ready_Scriptable<Quest_t*>(bard_songs_quest);
            Virtual::Machine_t::Self()->Call_Method(
                bard_songs_quest(),
                "BardSongsScript",
                "StopAllSongs",
                none<Virtual::Arguments_i*>(),
                new Stop_All_Songs_Callback(this, std::move(bard_aliases), std::move(callback))
            );
        } else {
            if (callback) {
                (*callback)();
            }
        }
    }

    void Actor_t::Update_Equipment(maybe<unique<Callback_i<>>> callback)
    {
        using Callback = maybe<unique<Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            some<Actor_t*>  actor;
            Callback        callback;

        public:
            Virtual_Callback(some<Actor_t*> actor, Callback callback) :
                actor(actor), callback(std::move(callback))
            {
            }

        public:
            virtual void operator()(Virtual::Variable_t*) override
            {
                this->actor->Is_Player_Teammate(false);

                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        static some<Weapon_t*> iron_sword = static_cast<Weapon_t*>(Game_t::Form(0x00012EB7)());
        SKYLIB_ASSERT(iron_sword);

        Bool_t is_player_teammate = Is_Player_Teammate();
        if (!is_player_teammate) {
            Is_Player_Teammate(true);
        }

        Add_Item(iron_sword, 0);

        if (!is_player_teammate) {
            Virtual::Utility_t::Wait_Even_In_Menu(2.0f, new Virtual_Callback(this, std::move(callback)));
        } else {
            if (callback) {
                (*callback)();
            }
        }
    }

    void Actor_t::Log_Actor_Values(std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_t::Log_Actor_Values: %s", Any_Name());
        SKYLIB_LOG(indent + "{");

        Log_Actor_Value(Actor_Value_Type_e::HEALTH, indent + SKYLIB_TAB);
        Log_Actor_Value(Actor_Value_Type_e::MAGICKA, indent + SKYLIB_TAB);
        Log_Actor_Value(Actor_Value_Type_e::STAMINA, indent + SKYLIB_TAB);

        maybe<Actor_Base_t*> actor_base = Actor_Base();
        if (actor_base) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "actor_base:");
            actor_base->Log_Actor_Value(Actor_Value_Type_e::HEALTH, indent + SKYLIB_TAB + SKYLIB_TAB);
            actor_base->Log_Actor_Value(Actor_Value_Type_e::MAGICKA, indent + SKYLIB_TAB + SKYLIB_TAB);
            actor_base->Log_Actor_Value(Actor_Value_Type_e::STAMINA, indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "actor_base: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

    void Actor_t::Log_Added_Spells(std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_t::Log_Added_Spells: %s", Any_Name());
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "count: %zu", this->added_spells.Count());
        for (size_t idx = 0, end = this->added_spells.Count(); idx < end; idx += 1) {
            maybe<Spell_t*> added_spell = this->added_spells[idx];
            if (added_spell) {
                added_spell->Log(indent + SKYLIB_TAB);
            }
        }

        SKYLIB_LOG(indent + "}");
    }

    void Actor_t::Log_Factions_And_Ranks(std::string indent)
    {
        SKYLIB_LOG(indent + "Actor_t::Log_Factions_And_Ranks: %s", Any_Name());
        SKYLIB_LOG(indent + "{");

        Vector_t<Faction_And_Rank_t> factions_and_ranks = Factions_And_Ranks();
        for (size_t idx = 0, end = factions_and_ranks.size(); idx < end; idx += 1) {
            factions_and_ranks[idx].Log(indent + SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

    void Actor_t::Log_Magic_Target(std::string indent)
    {
        Magic_Target_t::Log(indent);
    }

}
