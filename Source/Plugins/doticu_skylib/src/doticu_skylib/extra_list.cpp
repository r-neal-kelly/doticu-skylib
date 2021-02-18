/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/extra_count.h"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_leveled_item.h"
#include "doticu_skylib/extra_list.inl"
#include "doticu_skylib/extra_outfit.h"
#include "doticu_skylib/extra_owner.h"
#include "doticu_skylib/faction.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/leveled_item.h"
#include "doticu_skylib/outfit.h"

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

    /*Bool_t Extra_List_t::Is_Quest_Item()
    {
        static_assert(false, "incomplete.");
    }*/

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

        if (this->presence && Has(type)) {
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
