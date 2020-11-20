/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"
#include "doticu_skylib/xdata.h"

namespace doticu_skylib {

    void XData_t::Destroy(XData_t* xdata)
    {
        if (xdata) {
            xdata->~XData_t();
        }
    }

    XData_Type_e XData_t::Type()
    {
        return Get_Type();
    }

}
