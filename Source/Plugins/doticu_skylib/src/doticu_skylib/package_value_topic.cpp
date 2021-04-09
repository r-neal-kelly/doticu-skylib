/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value_topic.h"

namespace doticu_skylib {

    maybe<Dialogue_Topic_t*> Package_Value_Topic_t::Topic() const
    {
        SKYLIB_ASSERT(Is_Topic());

        if (!this->is_sub_type) {
            return this->value.topic;
        } else {
            return none<Dialogue_Topic_t*>();
        }
    }

    void Package_Value_Topic_t::Topic(maybe<Dialogue_Topic_t*> value)
    {
        SKYLIB_ASSERT(Is_Topic());

        this->is_sub_type = false;
        this->value.topic = value;
    }

    u32 Package_Value_Topic_t::Sub_Type() const
    {
        SKYLIB_ASSERT(Is_Topic());

        if (this->is_sub_type) {
            return this->value.sub_type;
        } else {
            return 0;
        }
    }

    void Package_Value_Topic_t::Sub_Type(u32 value)
    {
        SKYLIB_ASSERT(Is_Topic());

        this->is_sub_type = true;
        this->value.sub_type = value;
    }

    Package_Value_Topic_t::operator maybe<Dialogue_Topic_t*>() const
    {
        return Topic();
    }

    Package_Value_Topic_t::operator u32() const
    {
        return Sub_Type();
    }

    Package_Value_Topic_t& Package_Value_Topic_t::operator =(maybe<Dialogue_Topic_t*> value)
    {
        Topic(value);
        return *this;
    }

    Package_Value_Topic_t& Package_Value_Topic_t::operator =(u32 value)
    {
        Sub_Type(value);
        return *this;
    }

    void Package_Value_Topic_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Package_Value_Topic_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "is_sub_type: %s", this->is_sub_type ? "true" : "false");
        SKYLIB_LOG(indent + SKYLIB_TAB + "topic: 0x%p", Topic());
        SKYLIB_LOG(indent + SKYLIB_TAB + "sub_type: %i", Sub_Type());

        SKYLIB_LOG(indent + "}");
    }

}
