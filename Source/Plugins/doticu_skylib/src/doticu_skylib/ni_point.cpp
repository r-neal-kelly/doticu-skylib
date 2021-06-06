/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ni_point.h"

namespace doticu_skylib {

    NI_Point_3_t::NI_Point_3_t() :
        x(0.0),
        y(0.0),
        z(0.0)
    {
    }

    NI_Point_3_t::NI_Point_3_t(const NI_Point_3_t& other) :
        x(other.x),
        y(other.y),
        z(other.z)
    {
    }

    NI_Point_3_t::NI_Point_3_t(NI_Point_3_t&& other) noexcept :
        x(std::move(other.x)),
        y(std::move(other.y)),
        z(std::move(other.z))
    {
    }

    NI_Point_3_t& NI_Point_3_t::operator =(const NI_Point_3_t& other)
    {
        if (this != std::addressof(other)) {
            this->x = other.x;
            this->y = other.y;
            this->z = other.z;
        }
        return *this;
    }

    NI_Point_3_t& NI_Point_3_t::operator =(NI_Point_3_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->x = std::move(other.x);
            this->y = std::move(other.y);
            this->z = std::move(other.z);
        }
        return *this;
    }

    NI_Point_3_t::~NI_Point_3_t()
    {
    }

    void NI_Point_3_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "NI_Point_3_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "x: %16.8f", this->x);
        SKYLIB_LOG(indent + SKYLIB_TAB + "y: %16.8f", this->y);
        SKYLIB_LOG(indent + SKYLIB_TAB + "z: %16.8f", this->z);

        SKYLIB_LOG(indent + "}");
    }

}
