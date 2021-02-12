/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"

#include "doticu_skylib/extra_count.h"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_list.inl"

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

    Bool_t Extra_List_t::Should_Be_Deleted()
    {
        return Count() < 1;
    }

}
