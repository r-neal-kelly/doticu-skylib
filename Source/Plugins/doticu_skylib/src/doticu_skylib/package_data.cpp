/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/package_data.h"
#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    size_t Package_Data_t::Value_Count() const
    {
        return this->value_count;
    }

    maybe<Package_Value_t*> Package_Data_t::Value(size_t index) const
    {
        if (this->values && index < this->value_count) {
            return this->values[index];
        } else {
            return none<Package_Value_t*>();
        }
    }

    void Package_Data_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Data_t::Log");
        SKYLIB_LOG(indent + "{");

        size_t value_count = Value_Count();
        if (value_count > 0) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "values:");
            for (size_t idx = 0, end = value_count; idx < end; idx += 1) {
                Value(idx)->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
            }
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "values: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
