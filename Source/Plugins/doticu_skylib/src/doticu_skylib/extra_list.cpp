/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"

#include "doticu_skylib/extra_list.h"

namespace doticu_skylib {

    some<List_x::Presence_t*> List_x::Presence_t::Create()
    {
        some<Presence_t*> presence = Game_t::Allocate<Presence_t>();
        presence->Clear();
        return presence;
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

    void List_x::Validate()
    {
        Write_Locker_t locker(lock);

        if (presence) {
            presence->Clear();
            for (Data_x* xdata = xdatas; xdata != nullptr; xdata = xdata->next) {
                presence->Add(xdata->Type());
            }
        }
    }

    Bool_t List_x::Has(Extra_Type_e type)
    {
        Read_Locker_t locker(lock);

        if (presence) {
            return presence->Has(type);
        } else {
            return false;
        }
    }

    Data_x* List_x::Get(Extra_Type_e type)
    {
        Read_Locker_t locker(lock);

        if (presence && Has(type)) {
            for (Data_x* xdata = xdatas; xdata != nullptr; xdata = xdata->next) {
                if (xdata->Type() == type) {
                    return xdata;
                }
            }
            return nullptr;
        } else {
            return nullptr;
        }
    }

    Bool_t List_x::Add(Data_x* xdata)
    {
        Write_Locker_t locker(lock);

        if (xdata) {
            Extra_Type_e type = xdata->Type();
            if (!presence) {
                presence = Presence_t::Create()();
                Validate();
            }
            if (!presence->Has(type)) {
                xdata->next = xdatas;
                xdatas = xdata;
                presence->Add(type);
                return true;
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

    Bool_t List_x::Remove(Data_x* xdata)
    {
        Write_Locker_t locker(lock);

        if (xdata) {
            Extra_Type_e type = xdata->Type();
            if (presence && presence->Has(type)) {
                if (xdatas == xdata) {
                    xdatas = xdata->next;
                    presence->Remove(type);
                    return true;
                } else {
                    for (Data_x* it = xdatas; it != nullptr; it = it->next) {
                        if (it->next == xdata) {
                            it->next = xdata->next;
                            presence->Remove(type);
                            return true;
                        }
                    }
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

}
