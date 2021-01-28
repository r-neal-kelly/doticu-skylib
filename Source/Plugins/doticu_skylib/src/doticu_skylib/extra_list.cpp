/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_list.h"

namespace doticu_skylib {

    some<List_x::Presence_t*> List_x::Presence_t::Create()
    {
        some<Presence_t*> presence = Game_t::Allocate<Presence_t>();
        new (presence()) Presence_t();
        return presence;
    }

    void List_x::Presence_t::Destroy(some<Presence_t*> presence)
    {
        SKYLIB_ASSERT_SOME(presence);
        presence->~Presence_t();
        Game_t::Deallocate<Presence_t>(presence);
    }

    List_x::Presence_t::Presence_t()
    {
        Clear();
    }

    List_x::Presence_t::~Presence_t()
    {
        Clear();
    }

    Bool_t List_x::Presence_t::Has(Extra_Type_e type)
    {
        if (type < MAX_FLAGS) {
            Byte_t mask = 1 << (type % 8);
            Byte_t byte = flags[type >> 3];
            return (byte & mask) != 0;
        } else {
            return false;
        }
    }

    void List_x::Presence_t::Add(Extra_Type_e type)
    {
        if (type < MAX_FLAGS) {
            Byte_t mask = 1 << (type % 8);
            Byte_t& byte = flags[type >> 3];
            byte |= mask;
        }
    }

    void List_x::Presence_t::Remove(Extra_Type_e type)
    {
        if (type < MAX_FLAGS) {
            Byte_t mask = 1 << (type % 8);
            Byte_t& byte = flags[type >> 3];
            byte &= ~mask;
        }
    }

    void List_x::Presence_t::Clear()
    {
        Word_t* words = reinterpret_cast<Word_t*>(flags);
        words[0] = 0;
        words[1] = 0;
        words[2] = 0;
    }

    some<List_x*> List_x::Create()
    {
        some<List_x*> x_list = Game_t::Allocate<List_x>();
        new (x_list()) List_x();
        return x_list;
    }

    void List_x::Destroy(some<List_x*> x_list)
    {
        SKYLIB_ASSERT_SOME(x_list);
        x_list->~List_x();
        Game_t::Deallocate<List_x>(x_list);
    }

    List_x::List_x() :
        x_datas(none<Data_x*>()), presence(none<Presence_t*>()), lock(Read_Write_Lock_t())
    {
    }

    List_x::~List_x()
    {
        Write_Locker_t locker(this->lock);

        for (maybe<Data_x*> it = this->x_datas; it;) {
            maybe<Data_x*> next = it->next;
            Data_x::Destroy<Data_x>(it());
            it = next;
        }
        this->x_datas = none<Data_x*>();

        if (this->presence) {
            Presence_t::Destroy(this->presence());
            this->presence = none<Presence_t*>();
        }
    }

    void List_x::Validate()
    {
        Write_Locker_t locker(this->lock);

        if (this->presence) {
            this->presence->Clear();
            for (maybe<Data_x*> it = this->x_datas; it; it = it->next) {
                this->presence->Add(it->Type());
            }
        }
    }

    Bool_t List_x::Has(Extra_Type_e type)
    {
        Read_Locker_t locker(this->lock);

        if (this->presence) {
            return this->presence->Has(type);
        } else {
            return false;
        }
    }

    maybe<Data_x*> List_x::Get(Extra_Type_e type)
    {
        Read_Locker_t locker(this->lock);

        if (this->presence && Has(type)) {
            for (maybe<Data_x*> it = this->x_datas; it; it = it->next) {
                if (it->Type() == type) {
                    return it;
                }
            }
            return none<Data_x*>();
        } else {
            return none<Data_x*>();
        }
    }

    Bool_t List_x::Add(some<Data_x*> x_data)
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

    Bool_t List_x::Remove(some<Data_x*> x_data)
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
                for (maybe<Data_x*> it = this->x_datas; it; it = it->next) {
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

}
