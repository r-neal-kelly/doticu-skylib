/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/xdata.h"
#include "doticu_skylib/xlist.h"

namespace doticu_skylib {

    XList_t::Presence_t* XList_t::Presence_t::Create()
    {
        Presence_t* presence = static_cast<Presence_t*>(Heap_Allocate(sizeof(Presence_t)));
        SKYLIB_ASSERT(presence);
        presence->Clear();
    }

    Bool_t XList_t::Presence_t::Has(XData_Type_e type)
    {
        if (type < MAX_FLAGS) {
            Byte_t mask = 1 << (type % 8);
            Byte_t byte = flags[type >> 3];
            return (byte & mask) != 0;
        } else {
            return false;
        }
    }

    void XList_t::Presence_t::Add(XData_Type_e type)
    {
        if (type < MAX_FLAGS) {
            Byte_t mask = 1 << (type % 8);
            Byte_t& byte = flags[type >> 3];
            byte |= mask;
        }
    }

    void XList_t::Presence_t::Remove(XData_Type_e type)
    {
        if (type < MAX_FLAGS) {
            Byte_t mask = 1 << (type % 8);
            Byte_t& byte = flags[type >> 3];
            byte &= ~mask;
        }
    }

    void XList_t::Presence_t::Clear()
    {
        Word_t* words = reinterpret_cast<Word_t*>(flags);
        words[0] = 0;
        words[1] = 0;
        words[2] = 0;
    }

    void XList_t::Validate()
    {
        BSWriteLocker locker(&lock);

        if (presence) {
            presence->Clear();
            for (XData_t* xdata = xdatas; xdata != nullptr; xdata = xdata->next) {
                presence->Add(xdata->Type());
            }
        }
    }

    Bool_t XList_t::Has(XData_Type_e type)
    {
        BSReadLocker locker(&lock);

        if (presence) {
            return presence->Has(type);
        } else {
            return false;
        }
    }

    XData_t* XList_t::Get(XData_Type_e type)
    {
        BSReadLocker locker(&lock);

        if (presence && Has(type)) {
            for (XData_t* xdata = xdatas; xdata != nullptr; xdata = xdata->next) {
                if (xdata->Type() == type) {
                    return xdata;
                }
            }
            return nullptr;
        } else {
            return nullptr;
        }
    }

    Bool_t XList_t::Add(XData_t* xdata)
    {
        BSWriteLocker locker(&lock);

        if (xdata) {
            XData_Type_e type = xdata->Type();
            if (!presence) {
                presence = Presence_t::Create();
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

    Bool_t XList_t::Remove(XData_t* xdata)
    {
        BSWriteLocker locker(&lock);

        if (xdata) {
            XData_Type_e type = xdata->Type();
            if (presence && presence->Has(type)) {
                if (xdatas == xdata) {
                    xdatas = xdata->next;
                    presence->Remove(type);
                    return true;
                } else {
                    for (XData_t* it = xdatas; it != nullptr; it = it->next) {
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
