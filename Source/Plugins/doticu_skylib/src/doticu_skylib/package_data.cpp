/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/package_data.h"
#include "doticu_skylib/package_value.h"
#include "doticu_skylib/package_value_bool.h"
#include "doticu_skylib/package_value_float.h"
#include "doticu_skylib/package_value_int.h"
#include "doticu_skylib/package_value_list.h"
#include "doticu_skylib/package_value_location.h"
#include "doticu_skylib/package_value_reference.h"
#include "doticu_skylib/package_value_target.h"
#include "doticu_skylib/package_value_topic.h"

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

    Bool_t Package_Data_t::Bool(size_t index) const
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Bool_t*> bool_value = base_value->As_Bool()();
        SKYLIB_ASSERT_SOME(bool_value);

        return bool_value->Bool();
    }

    void Package_Data_t::Bool(size_t index, Bool_t value)
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Bool_t*> bool_value = base_value->As_Bool()();
        SKYLIB_ASSERT_SOME(bool_value);

        bool_value->Bool(value);
    }

    Float_t Package_Data_t::Float(size_t index) const
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Float_t*> float_value = base_value->As_Float()();
        SKYLIB_ASSERT_SOME(float_value);

        return float_value->Float();
    }

    void Package_Data_t::Float(size_t index, Float_t value)
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Float_t*> float_value = base_value->As_Float()();
        SKYLIB_ASSERT_SOME(float_value);

        float_value->Float(value);
    }

    Int_t Package_Data_t::Int(size_t index) const
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Int_t*> int_value = base_value->As_Int()();
        SKYLIB_ASSERT_SOME(int_value);

        return int_value->Int();
    }

    void Package_Data_t::Int(size_t index, Int_t value)
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Int_t*> int_value = base_value->As_Int()();
        SKYLIB_ASSERT_SOME(int_value);

        int_value->Int(value);
    }

    maybe<Package_Location_t*> Package_Data_t::Location(size_t index) const
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Location_t*> location_value = base_value->As_Location()();
        SKYLIB_ASSERT_SOME(location_value);

        return location_value->Location();
    }

    void Package_Data_t::Location(size_t index, maybe<Package_Location_t*> value)
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Location_t*> location_value = base_value->As_Location()();
        SKYLIB_ASSERT_SOME(location_value);

        location_value->Location(value);
    }

    maybe<Package_Target_t*> Package_Data_t::Reference_Target(size_t index) const
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Reference_t*> reference_value = base_value->As_Reference()();
        SKYLIB_ASSERT_SOME(reference_value);

        return reference_value->Target();
    }

    void Package_Data_t::Reference_Target(size_t index, maybe<Package_Target_t*> value)
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Reference_t*> reference_value = base_value->As_Reference()();
        SKYLIB_ASSERT_SOME(reference_value);

        reference_value->Target(value);
    }

    maybe<Package_Target_t*> Package_Data_t::Target(size_t index) const
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Target_t*> target_value = base_value->As_Target()();
        SKYLIB_ASSERT_SOME(target_value);

        return target_value->Target();
    }

    void Package_Data_t::Target(size_t index, maybe<Package_Target_t*> value)
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Target_t*> target_value = base_value->As_Target()();
        SKYLIB_ASSERT_SOME(target_value);

        target_value->Target(value);
    }

    maybe<Dialogue_Topic_t*> Package_Data_t::Topic(size_t index) const
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Topic_t*> topic_value = base_value->As_Topic()();
        SKYLIB_ASSERT_SOME(topic_value);

        return topic_value->Topic();
    }

    void Package_Data_t::Topic(size_t index, maybe<Dialogue_Topic_t*> value)
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Topic_t*> topic_value = base_value->As_Topic()();
        SKYLIB_ASSERT_SOME(topic_value);

        topic_value->Topic(value);
    }

    u32 Package_Data_t::Topic_Sub_type(size_t index) const
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Topic_t*> topic_value = base_value->As_Topic()();
        SKYLIB_ASSERT_SOME(topic_value);

        return topic_value->Sub_Type();
    }

    void Package_Data_t::Topic_Sub_type(size_t index, u32 value)
    {
        some<Package_Value_t*> base_value = Value(index)();
        SKYLIB_ASSERT_SOME(base_value);

        some<Package_Value_Topic_t*> topic_value = base_value->As_Topic()();
        SKYLIB_ASSERT_SOME(topic_value);

        topic_value->Sub_Type(value);
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
