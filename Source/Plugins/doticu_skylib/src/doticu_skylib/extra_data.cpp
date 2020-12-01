/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    void Data_x::Destroy(Data_x* xdata)
    {
        if (xdata) {
            xdata->~Data_x();
        }
    }

    Extra_Type_e Data_x::Type()
    {
        return Get_Type();
    }

}
