/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/calendar.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/global.inl"

namespace doticu_skylib {

    Calendar_t& Calendar_t::Self()
    {
        static auto self = *reinterpret_cast
            <Calendar_t**>
            (Game_t::Base_Address() + Offset_e::SELF);

        SKYLIB_ASSERT(self);
        return *self;
    }

    u16 Calendar_t::Year() const
    {
        if (this->year) {
            return this->year->As<u16>();
        } else {
            return 0;
        }
    }

    void Calendar_t::Year(u16 value)
    {
        if (this->year) {
            this->year->As<u16>(value);
        }
    }

    u16 Calendar_t::Month() const
    {
        if (this->month) {
            return this->month->As<u16>();
        } else {
            return 0;
        }
    }

    void Calendar_t::Month(u16 value)
    {
        if (this->month) {
            this->month->As<u16>(value);
        }
    }

    u16 Calendar_t::Day() const
    {
        if (this->day) {
            return this->day->As<u16>();
        } else {
            return 0;
        }
    }

    void Calendar_t::Day(u16 value)
    {
        if (this->day) {
            this->day->As<u16>(value);
        }
    }

    u16 Calendar_t::Hour() const
    {
        if (this->hour) {
            return floorf(this->hour->As<Float_t>());
        } else {
            return 0;
        }
    }

    void Calendar_t::Hour(u16 value)
    {
        if (this->hour) {
            this->hour->As<Float_t>(static_cast<Float_t>(value) + static_cast<Float_t>(Minute()) / 60);
        }
    }

    u16 Calendar_t::Minute() const
    {
        if (this->hour) {
            return (this->hour->As<Float_t>() - static_cast<Float_t>(Hour())) * 60;
        } else {
            return 0;
        }
    }

    void Calendar_t::Minute(u16 value)
    {
        if (this->hour) {
            this->hour->As<Float_t>(static_cast<Float_t>(Hour()) + static_cast<Float_t>(value) / 100);
        }
    }

    void Calendar_t::Log(std::string indent) const
    {
        SKYLIB_LOG(indent + "Calendar_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "year: %u", Year());
        SKYLIB_LOG(indent + SKYLIB_TAB + "month: %u", Month());
        SKYLIB_LOG(indent + SKYLIB_TAB + "day: %u", Day());
        SKYLIB_LOG(indent + SKYLIB_TAB + "hour: %u", Hour());
        SKYLIB_LOG(indent + SKYLIB_TAB + "minute: %u", Minute());

        SKYLIB_LOG(indent + "}");
    }

}
