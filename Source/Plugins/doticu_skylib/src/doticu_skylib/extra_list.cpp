/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/extra_count.h"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_factions.h"
#include "doticu_skylib/extra_ghost.h"
#include "doticu_skylib/extra_leveled_item.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/extra_outfit.h"
#include "doticu_skylib/extra_owner.h"
#include "doticu_skylib/extra_reference_handle.h"
#include "doticu_skylib/extra_reference_interaction.h"
#include "doticu_skylib/extra_talk_to_player.h"
#include "doticu_skylib/extra_worn.h"
#include "doticu_skylib/extra_worn_left.h"
#include "doticu_skylib/reference_handle.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/leveled_item.h"
#include "doticu_skylib/outfit.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    some<Extra_List_t::Presence_t*> Extra_List_t::Presence_t::Create()
    {
        some<Presence_t*> presence = Game_t::Allocate<Presence_t>();
        new (presence()) Presence_t();
        return presence;
    }

    void Extra_List_t::Presence_t::Destroy(some<Presence_t*> presence)
    {
        SKYLIB_ASSERT_SOME(presence);
        presence->~Presence_t();
        Game_t::Deallocate<Presence_t>(presence);
    }

    Extra_List_t::Presence_t::Presence_t()
    {
        Clear();
    }

    Extra_List_t::Presence_t::~Presence_t()
    {
        Clear();
    }

    Bool_t Extra_List_t::Presence_t::Has(Extra_Type_e type)
    {
        if (type < MAX_FLAGS) {
            Byte_t mask = 1 << (type % 8);
            Byte_t byte = flags[type >> 3];
            return (byte & mask) != 0;
        } else {
            return false;
        }
    }

    void Extra_List_t::Presence_t::Add(Extra_Type_e type)
    {
        if (type < MAX_FLAGS) {
            Byte_t mask = 1 << (type % 8);
            Byte_t& byte = flags[type >> 3];
            byte |= mask;
        }
    }

    void Extra_List_t::Presence_t::Remove(Extra_Type_e type)
    {
        if (type < MAX_FLAGS) {
            Byte_t mask = 1 << (type % 8);
            Byte_t& byte = flags[type >> 3];
            byte &= ~mask;
        }
    }

    void Extra_List_t::Presence_t::Clear()
    {
        Word_t* words = reinterpret_cast<Word_t*>(flags);
        words[0] = 0;
        words[1] = 0;
        words[2] = 0;
    }

    some<Extra_List_t*> Extra_List_t::Create()
    {
        some<Extra_List_t*> x_list = Game_t::Allocate<Extra_List_t>();
        new (x_list()) Extra_List_t();
        return x_list;
    }

    void Extra_List_t::Destroy(some<Extra_List_t*> x_list)
    {
        SKYLIB_ASSERT_SOME(x_list);
        x_list->~Extra_List_t();
        Game_t::Deallocate<Extra_List_t>(x_list);
    }

    Extra_List_t::Extra_List_t() :
        x_datas(none<Extra_Data_t*>()), presence(none<Presence_t*>()), lock(Read_Write_Lock_t())
    {
    }

    Extra_List_t::~Extra_List_t()
    {
        Write_Locker_t locker(this->lock);

        for (maybe<Extra_Data_t*> it = this->x_datas; it;) {
            maybe<Extra_Data_t*> next = it->next;
            Extra_Data_t::Destroy<Extra_Data_t>(it());
            it = next;
        }
        this->x_datas = none<Extra_Data_t*>();

        if (this->presence) {
            Presence_t::Destroy(this->presence());
            this->presence = none<Presence_t*>();
        }
    }

    void Extra_List_t::Validate()
    {
        Write_Locker_t locker(this->lock);

        if (this->presence) {
            this->presence->Clear();
            for (maybe<Extra_Data_t*> it = this->x_datas; it; it = it->next) {
                this->presence->Add(it->Type());
            }
        }
    }

    Bool_t Extra_List_t::Should_Be_Destroyed()
    {
        return Count() < 1;
    }

    Bool_t Extra_List_t::Can_Consume(some<Extra_List_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        Read_Locker_t this_locker(this->lock);
        Read_Locker_t other_locker(other->lock);

        for (maybe<Extra_Data_t*> other_it = other->x_datas; other_it; other_it = other_it->next) {
            Extra_Type_e other_type = other_it->Type();
            if (other_type != Extra_Type_e::COUNT) {
                Bool_t this_has_other_type = false;
                for (maybe<Extra_Data_t*> this_it = this->x_datas; this_it; this_it = this_it->next) {
                    if (this_it->Type() == other_type) {
                        this_has_other_type = true;
                        if (this_it->Isnt_Equal(other_it())) {
                            return false;
                        }
                    }
                }
                if (!this_has_other_type) {
                    return false;
                }
            }
        }

        return true;
    }

    Bool_t Extra_List_t::Try_To_Consume(some<Extra_List_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        if (Can_Consume(other)) {
            Increment_Count(other->Count());
            Destroy(other);
            return true;
        } else {
            return false;
        }
    }

    Bool_t Extra_List_t::Has(Extra_Type_e type)
    {
        Read_Locker_t locker(this->lock);

        if (this->presence) {
            return this->presence->Has(type);
        } else {
            return false;
        }
    }

    maybe<Extra_Data_t*> Extra_List_t::Get(Extra_Type_e type)
    {
        Read_Locker_t locker(this->lock);

        if (this->presence && this->presence->Has(type)) {
            for (maybe<Extra_Data_t*> it = this->x_datas; it; it = it->next) {
                if (it->Type() == type) {
                    return it;
                }
            }
            return none<Extra_Data_t*>();
        } else {
            return none<Extra_Data_t*>();
        }
    }

    Bool_t Extra_List_t::Add(some<Extra_Data_t*> x_data)
    {
        SKYLIB_ASSERT_SOME(x_data);

        Write_Locker_t locker(this->lock);

        Extra_Type_e type = x_data->Type();
        if (!this->presence) {
            this->presence = Presence_t::Create()();
            Validate();
        }
        if (!this->presence->Has(type)) {
            x_data->next = this->x_datas;
            this->x_datas = x_data();
            this->presence->Add(type);
            return true;
        } else {
            return false;
        }
    }

    Bool_t Extra_List_t::Remove(some<Extra_Data_t*> x_data)
    {
        SKYLIB_ASSERT_SOME(x_data);

        Write_Locker_t locker(this->lock);

        Extra_Type_e type = x_data->Type();
        if (this->presence && this->presence->Has(type)) {
            if (this->x_datas == x_data()) {
                this->x_datas = x_data->next;
                this->presence->Remove(type);
                return true;
            } else {
                for (maybe<Extra_Data_t*> it = this->x_datas; it; it = it->next) {
                    if (it->next == x_data()) {
                        it->next = x_data->next;
                        this->presence->Remove(type);
                        return true;
                    }
                }
                return false;
            }
        } else {
            return false;
        }
    }

    Bool_t Extra_List_t::Has_Extra_Count()                  { return Has<Extra_Count_t>(); }
    Bool_t Extra_List_t::Has_Extra_Factions()               { return Has<Extra_Factions_t>(); }
    Bool_t Extra_List_t::Has_Extra_Ghost()                  { return Has<Extra_Ghost_t>(); }
    Bool_t Extra_List_t::Has_Extra_Leveled_Item()           { return Has<Extra_Leveled_Item_t>(); }
    Bool_t Extra_List_t::Has_Extra_Outfit()                 { return Has<Extra_Outfit_t>(); }
    Bool_t Extra_List_t::Has_Extra_Owner()                  { return Has<Extra_Owner_t>(); }
    Bool_t Extra_List_t::Has_Extra_Reference_Handle()       { return Has<Extra_Reference_Handle_t>(); }
    Bool_t Extra_List_t::Has_Extra_Reference_Interaction()  { return Has<Extra_Reference_Interaction_t>(); }
    Bool_t Extra_List_t::Has_Extra_Talk_To_Player()         { return Has<Extra_Talk_To_Player_t>(); }
    Bool_t Extra_List_t::Has_Extra_Worn()                   { return Has<Extra_Worn_t>(); }
    Bool_t Extra_List_t::Has_Extra_Worn_Left()              { return Has<Extra_Worn_Left_t>(); }

    Vector_t<some<Extra_Data_t*>> Extra_List_t::Extra_Datas()
    {
        Read_Locker_t locker(this->lock);

        Vector_t<some<Extra_Data_t*>> extra_datas;

        for (maybe<Extra_Data_t*> it = this->x_datas; it; it = it->next) {
            extra_datas.push_back(it());
        }

        return extra_datas;
    }

    s16 Extra_List_t::Count()
    {
        maybe<Extra_Count_t*> x_count = Get<Extra_Count_t>();
        if (x_count) {
            return x_count->Count();
        } else {
            return 1;
        }
    }

    s16 Extra_List_t::Increment_Count(s16 amount)
    {
        if (amount > 0) {
            maybe<Extra_Count_t*> x_count = Get<Extra_Count_t>();
            if (x_count) {
                return x_count->Increment_Count(amount);
            } else {
                some<Extra_Count_t*> new_x_count = Extra_Count_t::Create(1);
                Add<Extra_Count_t>(new_x_count);
                return new_x_count->Increment_Count(amount);
            }
        } else {
            return Count();
        }
    }

    s16 Extra_List_t::Decrement_Count(s16 amount)
    {
        if (amount > 0) {
            maybe<Extra_Count_t*> x_count = Get<Extra_Count_t>();
            if (x_count) {
                return x_count->Decrement_Count(amount);
            } else {
                some<Extra_Count_t*> new_x_count = Extra_Count_t::Create(1);
                Add<Extra_Count_t>(new_x_count);
                return new_x_count->Decrement_Count(amount);
            }
        } else {
            return Count();
        }
    }

    maybe<Raw_Faction_Rank_t> Extra_List_t::Faction_Rank(some<Faction_t*> faction)
    {
        maybe<Extra_Factions_t*> x_factions = Get<Extra_Factions_t>();
        if (x_factions) {
            return x_factions->Faction_Rank(faction);
        } else {
            return none<Raw_Faction_Rank_t>();
        }
    }

    void Extra_List_t::Faction_Rank(some<Faction_t*> faction, some<Raw_Faction_Rank_t> rank)
    {
        maybe<Extra_Factions_t*> x_factions = Get<Extra_Factions_t>();
        if (x_factions) {
            x_factions->Faction_Rank(faction, rank);
        } else {
            Add<Extra_Factions_t>(Extra_Factions_t::Create(faction, rank));
        }
    }

    maybe<Faction_t*> Extra_List_t::Crime_Faction()
    {
        maybe<Extra_Factions_t*> x_factions = Get<Extra_Factions_t>();
        if (x_factions) {
            return x_factions->Crime_Faction();
        } else {
            return none<Faction_t*>();
        }
    }

    void Extra_List_t::Crime_Faction(maybe<Faction_t*> crime_faction)
    {
        maybe<Extra_Factions_t*> x_factions = Get<Extra_Factions_t>();
        if (x_factions) {
            x_factions->Crime_Faction(crime_faction);
        } else {
            Add<Extra_Factions_t>(Extra_Factions_t::Create(crime_faction));
        }
    }

    Boolean_e Extra_List_t::Is_Ghost()
    {
        maybe<Extra_Ghost_t*> x_ghost = Get<Extra_Ghost_t>();
        if (x_ghost) {
            return x_ghost->is_ghost;
        } else {
            return Boolean_e::NEITHER;
        }
    }

    void Extra_List_t::Is_Ghost(Bool_t is_ghost)
    {
        maybe<Extra_Ghost_t*> x_ghost = Get<Extra_Ghost_t>();
        if (x_ghost) {
            x_ghost->is_ghost = is_ghost;
        } else {
            Add<Extra_Ghost_t>(Extra_Ghost_t::Create(is_ghost));
        }
    }

    Bool_t Extra_List_t::Is_Leveled_Item()
    {
        return Has<Extra_Leveled_Item_t>();
    }

    maybe<Leveled_Item_t*> Extra_List_t::Leveled_Item()
    {
        maybe<Extra_Leveled_Item_t*> x_leveled_item = Get<Extra_Leveled_Item_t>();
        if (x_leveled_item) {
            if (x_leveled_item->leveled_item_form_id) {
                return Game_t::Form(x_leveled_item->leveled_item_form_id());
            } else {
                Remove<Extra_Leveled_Item_t>(x_leveled_item());
                Extra_Leveled_Item_t::Destroy(x_leveled_item());
                return none<Leveled_Item_t*>();
            }
        } else {
            return none<Leveled_Item_t*>();
        }
    }

    void Extra_List_t::Leveled_Item(maybe<Leveled_Item_t*> leveled_item)
    {
        if (leveled_item) {
            maybe<Extra_Leveled_Item_t*> x_leveled_item = Get<Extra_Leveled_Item_t>();
            if (x_leveled_item) {
                x_leveled_item->leveled_item_form_id = leveled_item->form_id;
            } else {
                Add<Extra_Leveled_Item_t>(Extra_Leveled_Item_t::Create(leveled_item()));
            }
        } else {
            maybe<Extra_Leveled_Item_t*> x_leveled_item = Get<Extra_Leveled_Item_t>();
            if (x_leveled_item) {
                Remove<Extra_Leveled_Item_t>(x_leveled_item());
                Extra_Leveled_Item_t::Destroy(x_leveled_item());
            }
        }
    }

    Bool_t Extra_List_t::Is_Outfit_Item()
    {
        return Has<Extra_Outfit_t>();
    }

    maybe<Outfit_t*> Extra_List_t::Outfit()
    {
        maybe<Extra_Outfit_t*> x_outfit = Get<Extra_Outfit_t>();
        if (x_outfit) {
            if (x_outfit->outfit_form_id) {
                return Game_t::Form(x_outfit->outfit_form_id());
            } else {
                Remove<Extra_Outfit_t>(x_outfit());
                Extra_Outfit_t::Destroy(x_outfit());
                return none<Outfit_t*>();
            }
        } else {
            return none<Outfit_t*>();
        }
    }

    void Extra_List_t::Outfit(maybe<Outfit_t*> outfit)
    {
        if (outfit) {
            maybe<Extra_Outfit_t*> x_outfit = Get<Extra_Outfit_t>();
            if (x_outfit) {
                x_outfit->outfit_form_id = outfit->form_id;
            } else {
                Add<Extra_Outfit_t>(Extra_Outfit_t::Create(outfit()));
            }
        } else {
            maybe<Extra_Outfit_t*> x_outfit = Get<Extra_Outfit_t>();
            if (x_outfit) {
                Remove<Extra_Outfit_t>(x_outfit());
                Extra_Outfit_t::Destroy(x_outfit());
            }
        }
    }

    maybe<Form_t*> Extra_List_t::Owner()
    {
        maybe<Extra_Owner_t*> x_owner = Get<Extra_Owner_t>();
        if (x_owner) {
            return x_owner->owner;
        } else {
            return none<Form_t*>();
        }
    }

    void Extra_List_t::Owner(maybe<Form_t*> form)
    {
        maybe<Extra_Owner_t*> x_owner = Get<Extra_Owner_t>();
        if (x_owner) {
            x_owner->owner = form;
        } else {
            Add<Extra_Owner_t>(Extra_Owner_t::Create(form));
        }
    }

    maybe<Faction_t*> Extra_List_t::Faction_Owner()
    {
        return static_cast<maybe<Faction_t*>>(Owner());
    }

    void Extra_List_t::Faction_Owner(maybe<Faction_t*> faction)
    {
        Owner(static_cast<maybe<Form_t*>>(faction));
    }

    maybe<Actor_Base_t*> Extra_List_t::Actor_Base_Owner()
    {
        return static_cast<maybe<Actor_Base_t*>>(Owner());
    }

    void Extra_List_t::Actor_Base_Owner(maybe<Actor_Base_t*> actor_base)
    {
        Owner(static_cast<maybe<Form_t*>>(actor_base));
    }

    Bool_t Extra_List_t::Is_Quest_Item()
    {
        maybe<Reference_t*> reference = Reference();
        if (reference) {
            return reference->Is_Quest_Item();
        } else {
            return false;
        }
    }

    maybe<Reference_t*> Extra_List_t::Reference()
    {
        maybe<Extra_Reference_Handle_t*> x_reference_handle = Get<Extra_Reference_Handle_t>();
        if (x_reference_handle) {
            return x_reference_handle->Reference();
        } else {
            return none<Reference_t*>();
        }
    }

    void Extra_List_t::Reference(some<Reference_t*> reference)
    {
        SKYLIB_ASSERT_SOME(reference);

        maybe<Extra_Reference_Handle_t*> x_reference_handle = Get<Extra_Reference_Handle_t>();
        if (x_reference_handle) {
            x_reference_handle->Reference(reference);
        } else {
            Add<Extra_Reference_Handle_t>(Extra_Reference_Handle_t::Create(reference));
        }
    }

    Reference_Handle_t Extra_List_t::Reference_Handle()
    {
        maybe<Extra_Reference_Handle_t*> x_reference_handle = Get<Extra_Reference_Handle_t>();
        if (x_reference_handle) {
            return x_reference_handle->reference_handle;
        } else {
            return 0;
        }
    }

    void Extra_List_t::Reference_Handle(Reference_Handle_t reference_handle)
    {
        maybe<Extra_Reference_Handle_t*> x_reference_handle = Get<Extra_Reference_Handle_t>();
        if (x_reference_handle) {
            x_reference_handle->reference_handle = reference_handle;
        } else {
            Add<Extra_Reference_Handle_t>(Extra_Reference_Handle_t::Create(reference_handle));
        }
    }

    maybe<Reference_t*> Extra_List_t::Reference_Interactor_A()
    {
        maybe<Extra_Reference_Interaction_t*> x_reference_interaction = Get<Extra_Reference_Interaction_t>();
        if (x_reference_interaction) {
            return x_reference_interaction->Interactor_A();
        } else {
            return none<Reference_t*>();
        }
    }

    maybe<Reference_t*> Extra_List_t::Reference_Interactor_B()
    {
        maybe<Extra_Reference_Interaction_t*> x_reference_interaction = Get<Extra_Reference_Interaction_t>();
        if (x_reference_interaction) {
            return x_reference_interaction->Interactor_B();
        } else {
            return none<Reference_t*>();
        }
    }

    Boolean_e Extra_List_t::Can_Talk_To_Player()
    {
        maybe<Extra_Talk_To_Player_t*> x_talk_to_player = Get<Extra_Talk_To_Player_t>();
        if (x_talk_to_player) {
            return x_talk_to_player->can_talk_to_player;
        } else {
            return Boolean_e::NEITHER;
        }
    }

    void Extra_List_t::Can_Talk_To_Player(Bool_t can_talk_to_player)
    {
        maybe<Extra_Talk_To_Player_t*> x_talk_to_player = Get<Extra_Talk_To_Player_t>();
        if (x_talk_to_player) {
            x_talk_to_player->can_talk_to_player = can_talk_to_player;
        } else {
            Add<Extra_Talk_To_Player_t>(Extra_Talk_To_Player_t::Create(can_talk_to_player));
        }
    }

    Bool_t Extra_List_t::Is_Worn_Item()
    {
        return Is_Worn() || Is_Worn_Left();
    }

    Bool_t Extra_List_t::Is_Worn()
    {
        return Has<Extra_Worn_t>();
    }

    void Extra_List_t::Is_Worn(Bool_t is_worn)
    {
        if (is_worn) {
            if (!Is_Worn()) {
                Add<Extra_Worn_t>(Extra_Worn_t::Create());
            }
        } else {
            maybe<Extra_Worn_t*> x_worn = Get<Extra_Worn_t>();
            if (x_worn) {
                Remove<Extra_Worn_t>(x_worn());
            }
        }
    }

    Bool_t Extra_List_t::Is_Worn_Left()
    {
        return Has<Extra_Worn_Left_t>();
    }

    void Extra_List_t::Is_Worn_Left(Bool_t is_worn_left)
    {
        if (is_worn_left) {
            if (!Is_Worn_Left()) {
                Add<Extra_Worn_Left_t>(Extra_Worn_Left_t::Create());
            }
        } else {
            maybe<Extra_Worn_Left_t*> x_worn_left = Get<Extra_Worn_Left_t>();
            if (x_worn_left) {
                Remove<Extra_Worn_Left_t>(x_worn_left());
            }
        }
    }

    void Extra_List_t::Log(std::string indent)
    {
        Read_Locker_t locker(this->lock);

        SKYLIB_LOG(indent + "Extra_List_t::Log");
        SKYLIB_LOG(indent + "{");

        for (maybe<Extra_Data_t*> it = this->x_datas; it; it = it->next) {
            it->Log(indent + SKYLIB_TAB);
        }

        SKYLIB_LOG(indent + "}");
    }

}
