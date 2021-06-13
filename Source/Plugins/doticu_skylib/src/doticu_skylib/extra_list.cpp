/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_cannot_wear.h"
#include "doticu_skylib/extra_charge.h"
#include "doticu_skylib/extra_container_changes.h"
#include "doticu_skylib/extra_count.h"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_enchantment.h"
#include "doticu_skylib/extra_factions.h"
#include "doticu_skylib/extra_from_alias.h"
#include "doticu_skylib/extra_ghost.h"
#include "doticu_skylib/extra_leveled_item.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/extra_outfit.h"
#include "doticu_skylib/extra_owner.h"
#include "doticu_skylib/extra_poison.h"
#include "doticu_skylib/extra_reference_handle.h"
#include "doticu_skylib/extra_reference_interaction.h"
#include "doticu_skylib/extra_soul_level.h"
#include "doticu_skylib/extra_talk_to_player.h"
#include "doticu_skylib/extra_temper_level.h"
#include "doticu_skylib/extra_text_display.h"
#include "doticu_skylib/extra_unique_id.h"
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

    Bool_t Extra_List_t::Presence_t::Has(Extra_Type_e type) const
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

    Bool_t Extra_List_t::Has_Equal_Extra_Data(some<Extra_Data_t*> x_data)
    {
        SKYLIB_ASSERT_SOME(x_data);

        Extra_Type_e type = x_data->Type();
        Read_Locker_t locker(this->lock);
        for (maybe<Extra_Data_t*> it = this->x_datas; it; it = it->next) {
            if (it->Type() == type) {
                return it->Is_Equal(x_data);
            }
        }
        return false;
    }

    Bool_t Extra_List_t::Has_Equal_Extra_Datas(some<Extra_List_t*> other, Filter_i<Extra_Type_e>& filter)
    {
        Read_Locker_t locker(other->lock);
        for (maybe<Extra_Data_t*> it = other->x_datas; it; it = it->next) {
            Extra_Type_e type = it->Type();
            if (filter(type)) {
                if (!Has_Equal_Extra_Data(it())) {
                    return false;
                }
            }
        }
        return true;
    }

    Bool_t Extra_List_t::Is_Equal(some<Extra_List_t*> other, Filter_i<Extra_Type_e>& filter)
    {
        return this->Has_Equal_Extra_Datas(other, filter) && other->Has_Equal_Extra_Datas(this, filter);
    }

    Bool_t Extra_List_t::Can_Consume(some<Extra_List_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        if (!Has_Extra_Reference_Handle() && !other->Has_Extra_Reference_Handle()) {
            Read_Locker_t locker(other->lock);
            for (maybe<Extra_Data_t*> it = other->x_datas; it; it = it->next) {
                if (it->Type() != Extra_Type_e::COUNT) {
                    if (!Has_Equal_Extra_Data(it())) {
                        return false;
                    }
                }
            }
            return true;
        } else {
            return false;
        }
    }

    maybe<s16> Extra_List_t::Try_To_Consume(some<Extra_List_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        if (Can_Consume(other)) {
            s16 other_count = other->Count();
            Destroy(other);
            return Increment_Count(other_count);
        } else {
            return none<s16>();
        }
    }

    Bool_t Extra_List_t::Has(Extra_Type_e type) const
    {
        Read_Locker_t locker(this->lock);

        if (this->presence) {
            return this->presence->Has(type);
        } else {
            return false;
        }
    }

    maybe<Extra_Data_t*> Extra_List_t::Get(Extra_Type_e type) const
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
            if (this->x_datas == x_data) {
                this->x_datas = x_data->next;
                this->presence->Remove(type);
                return true;
            } else {
                for (maybe<Extra_Data_t*> it = this->x_datas; it; it = it->next) {
                    if (it->next == x_data) {
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

    Bool_t  Extra_List_t::Has_Extra_Aliases()               { return Has<Extra_Aliases_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Cannot_Wear()           { return Has<Extra_Cannot_Wear_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Count()                 { return Has<Extra_Count_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Factions()              { return Has<Extra_Factions_t>(); }
    Bool_t  Extra_List_t::Has_Extra_From_Alias()            { return Has<Extra_From_Alias_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Ghost()                 { return Has<Extra_Ghost_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Leveled_Item()          { return Has<Extra_Leveled_Item_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Outfit()                { return Has<Extra_Outfit_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Owner()                 { return Has<Extra_Owner_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Reference_Handle()      { return Has<Extra_Reference_Handle_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Reference_Interaction() { return Has<Extra_Reference_Interaction_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Talk_To_Player()        { return Has<Extra_Talk_To_Player_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Unique_ID()             { return Has<Extra_Unique_ID_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Worn()                  { return Has<Extra_Worn_t>(); }
    Bool_t  Extra_List_t::Has_Extra_Worn_Left()             { return Has<Extra_Worn_Left_t>(); }

    Bool_t  Extra_List_t::Destroy_Extra_Count()             { return Remove_And_Destroy<Extra_Count_t>(); }
    Bool_t  Extra_List_t::Destroy_Extra_Text_Display()      { return Remove_And_Destroy<Extra_Text_Display_t>(); }

    Vector_t<some<Extra_Data_t*>> Extra_List_t::Extra_Datas()
    {
        Read_Locker_t locker(this->lock);

        Vector_t<some<Extra_Data_t*>> extra_datas;

        for (maybe<Extra_Data_t*> it = this->x_datas; it; it = it->next) {
            extra_datas.push_back(it());
        }

        return extra_datas;
    }

    maybe<Extra_List_t*> Extra_List_t::Copy(Filter_i<Extra_Type_e>& filter)
    {
        Vector_t<some<Extra_Data_t*>> data_copies;
        {
            Read_Locker_t locker(this->lock);
            for (maybe<Extra_Data_t*> it = this->x_datas; it; it = it->next) {
                if (filter(it->Type())) {
                    maybe<Extra_Data_t*> data_copy = it->Copy();
                    if (data_copy) {
                        data_copies.push_back(data_copy());
                    }
                }
            }
        }

        size_t data_copy_count = data_copies.size();
        if (data_copy_count > 0) {
            some<Extra_List_t*> list_copy = Create();
            for (size_t idx = 0, end = data_copy_count; idx < end; idx += 1) {
                list_copy->Add(data_copies[idx]);
            }
            return list_copy();
        } else {
            return none<Extra_List_t*>();
        }
    }

    Bool_t Extra_List_t::Is_Aliased()
    {
        maybe<Extra_Aliases_t*> x_aliases = Get<Extra_Aliases_t>();
        if (x_aliases) {
            return x_aliases->Is_Aliased();
        } else {
            return false;
        }
    }

    Bool_t Extra_List_t::Is_Aliased(some<Quest_t*> quest)
    {
        SKYLIB_ASSERT_SOME(quest);

        maybe<Extra_Aliases_t*> x_aliases = Get<Extra_Aliases_t>();
        if (x_aliases) {
            return x_aliases->Is_Aliased(quest);
        } else {
            return false;
        }
    }

    Bool_t Extra_List_t::Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id)
    {
        SKYLIB_ASSERT_SOME(quest);

        maybe<Extra_Aliases_t*> x_aliases = Get<Extra_Aliases_t>();
        if (x_aliases) {
            return x_aliases->Is_Aliased(quest, alias_id);
        } else {
            return false;
        }
    }

    Bool_t Extra_List_t::Is_Protected()
    {
        maybe<Extra_Aliases_t*> x_aliases = none<Extra_Aliases_t*>();

        maybe<Reference_t*> reference = Representative_Reference();
        if (reference) {
            x_aliases = reference->x_list.Get<Extra_Aliases_t>();
        } else {
            x_aliases = this->Get<Extra_Aliases_t>();
        }

        if (x_aliases) {
            return x_aliases->Is_Protected();
        } else {
            return false;
        }
    }

    Bool_t Extra_List_t::Is_Essential()
    {
        maybe<Extra_Aliases_t*> x_aliases = none<Extra_Aliases_t*>();

        maybe<Reference_t*> reference = Representative_Reference();
        if (reference) {
            x_aliases = reference->x_list.Get<Extra_Aliases_t>();
        } else {
            x_aliases = this->Get<Extra_Aliases_t>();
        }

        if (x_aliases) {
            return x_aliases->Is_Essential();
        } else {
            return false;
        }
    }

    Bool_t Extra_List_t::Is_Quest_Item() const
    {
        maybe<Extra_Aliases_t*> x_aliases = none<Extra_Aliases_t*>();

        maybe<Reference_t*> reference = Representative_Reference();
        if (reference) {
            x_aliases = reference->x_list.Get<Extra_Aliases_t>();
        } else {
            x_aliases = this->Get<Extra_Aliases_t>();
        }

        if (x_aliases) {
            return x_aliases->Is_Quest_Item();
        } else {
            return false;
        }
    }

    Vector_t<some<Alias_Base_t*>> Extra_List_t::Alias_Bases()
    {
        Vector_t<some<Alias_Base_t*>> results;
        Alias_Bases(results);
        return results;
    }

    void Extra_List_t::Alias_Bases(Vector_t<some<Alias_Base_t*>>& results)
    {
        maybe<Extra_Aliases_t*> x_aliases = Get<Extra_Aliases_t>();
        if (x_aliases) {
            x_aliases->Alias_Bases(results);
        }
    }

    Vector_t<some<Alias_Reference_t*>> Extra_List_t::Alias_References()
    {
        Vector_t<some<Alias_Reference_t*>> results;
        Alias_References(results);
        return results;
    }

    void Extra_List_t::Alias_References(Vector_t<some<Alias_Reference_t*>>& results)
    {
        maybe<Extra_Aliases_t*> x_aliases = Get<Extra_Aliases_t>();
        if (x_aliases) {
            x_aliases->Alias_References(results);
        }
    }

    Vector_t<some<Quest_t*>> Extra_List_t::Quests()
    {
        Vector_t<some<Quest_t*>> results;
        Quests(results);
        return results;
    }

    void Extra_List_t::Quests(Vector_t<some<Quest_t*>>& results)
    {
        maybe<Extra_Aliases_t*> x_aliases = Get<Extra_Aliases_t>();
        if (x_aliases) {
            x_aliases->Quests(results);
        }
    }

    Bool_t Extra_List_t::Cannot_Wear()
    {
        return Has_Extra_Cannot_Wear();
    }

    void Extra_List_t::Cannot_Wear(Bool_t cannot_wear)
    {
        if (cannot_wear) {
            if (!Cannot_Wear()) {
                Add<Extra_Cannot_Wear_t>(Extra_Cannot_Wear_t::Create());
            }
        } else {
            Remove_And_Destroy<Extra_Cannot_Wear_t>();
        }
    }

    Vector_t<some<Reference_t*>> Extra_List_t::Contained_References() const
    {
        Vector_t<some<Reference_t*>> results;
        Contained_References(results);
        return results;
    }

    void Extra_List_t::Contained_References(Vector_t<some<Reference_t*>>& results) const
    {
        using Entries_t = List_t<maybe<Container_Changes_Entry_t*>>;
        using X_Lists_t = List_t<maybe<Extra_List_t*>>;

        Read_Locker_t locker(this->lock);

        maybe<Extra_Container_Changes_t*> x_container = Get<Extra_Container_Changes_t>();
        if (x_container && x_container->container_changes && x_container->container_changes->entries) {
            Entries_t& entries = *x_container->container_changes->entries;
            if (!entries.Is_Empty()) {
                for (maybe<Entries_t::Node_t*> it = &entries.head; it; it = it->next) {
                    maybe<Container_Changes_Entry_t*> entry = it->value;
                    if (entry && entry->x_lists) {
                        X_Lists_t& x_lists = *entry->x_lists;
                        for (maybe<X_Lists_t::Node_t*> it = &x_lists.head; it; it = it->next) {
                            maybe<Extra_List_t*> x_list = it->value;
                            if (x_list) {
                                maybe<Reference_t*> reference = x_list->Representative_Reference();
                                if (reference) {
                                    results.push_back(reference());
                                }
                            }
                        }
                    }
                }
            }
        }
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

    void Extra_List_t::Count(s16 count)
    {
        SKYLIB_ASSERT(count > -1);
        SKYLIB_ASSERT(May_Change_Count() ? true : count == 1);

        maybe<Extra_Count_t*> x_count = Get<Extra_Count_t>();
        if (x_count) {
            if (count != 1) {
                x_count->Count(count);
            } else {
                Remove_And_Destroy<Extra_Count_t>(x_count());
            }
        } else {
            if (count != 1) {
                Add<Extra_Count_t>(Extra_Count_t::Create(count));
            }
        }
    }

    s16 Extra_List_t::Increment_Count(s16 amount)
    {
        SKYLIB_ASSERT(May_Change_Count());

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
        SKYLIB_ASSERT(May_Change_Count());

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

    Bool_t Extra_List_t::May_Change_Count()
    {
        // Extra_Unique_ID_t and Extra_From_Alias_t can be found on x_lists that have an Extra_Count_t.
        return !Has_Extra_Reference_Handle();
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

    maybe<Bool_t> Extra_List_t::Is_Ghost()
    {
        maybe<Extra_Ghost_t*> x_ghost = Get<Extra_Ghost_t>();
        if (x_ghost) {
            return x_ghost->is_ghost;
        } else {
            return none<Bool_t>();
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
                Remove_And_Destroy<Extra_Leveled_Item_t>(x_leveled_item());
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
            Remove_And_Destroy<Extra_Leveled_Item_t>();
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
                Remove_And_Destroy<Extra_Outfit_t>(x_outfit());
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
            Remove_And_Destroy<Extra_Outfit_t>();
        }
    }

    maybe<Form_Owner_t> Extra_List_t::Owner()
    {
        maybe<Extra_Owner_t*> x_owner = Get<Extra_Owner_t>();
        if (x_owner) {
            return x_owner->Form_Owner();
        } else {
            return none<Form_Owner_t>();
        }
    }

    void Extra_List_t::Owner(Form_Owner_t owner)
    {
        maybe<Extra_Owner_t*> x_owner = Get<Extra_Owner_t>();
        if (x_owner) {
            x_owner->Form_Owner(owner);
        } else {
            Add<Extra_Owner_t>(Extra_Owner_t::Create(owner));
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

    maybe<Reference_t*> Extra_List_t::Representative_Reference() const
    {
        Read_Locker_t locker(this->lock);

        maybe<Extra_Reference_Handle_t*> x_reference_handle = Get<Extra_Reference_Handle_t>();
        if (x_reference_handle) {
            return x_reference_handle->Representative_Reference();
        } else {
            return none<Reference_t*>();
        }
    }

    maybe<Reference_t*> Extra_List_t::Containing_Reference() const
    {
        Read_Locker_t locker(this->lock);

        maybe<Extra_Reference_Handle_t*> x_reference_handle = Get<Extra_Reference_Handle_t>();
        if (x_reference_handle) {
            return x_reference_handle->Containing_Reference();
        } else {
            return none<Reference_t*>();
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

    maybe<Bool_t> Extra_List_t::Can_Talk_To_Player()
    {
        maybe<Extra_Talk_To_Player_t*> x_talk_to_player = Get<Extra_Talk_To_Player_t>();
        if (x_talk_to_player) {
            return x_talk_to_player->can_talk_to_player;
        } else {
            return none<Bool_t>();
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

    maybe<String_t> Extra_List_t::Name()
    {
        maybe<Extra_Text_Display_t*> x_text_display = Get<Extra_Text_Display_t>();
        if (x_text_display) {
            return x_text_display->Name();
        } else {
            return none<String_t>();
        }
    }

    void Extra_List_t::Name(String_t name)
    {
        maybe<Extra_Text_Display_t*> x_text_display = Get<Extra_Text_Display_t>();
        if (x_text_display) {
            x_text_display->Name(name, true);
        } else {
            Add<Extra_Text_Display_t>(Extra_Text_Display_t::Create(name));
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
            Remove_And_Destroy<Extra_Worn_t>();
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
            Remove_And_Destroy<Extra_Worn_Left_t>();
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
