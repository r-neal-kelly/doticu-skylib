/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/calendar_time_hour_24.h"
#include "doticu_skylib/calendar_time_minute.h"

namespace doticu_skylib {

    class Calendar_Time_24_t_data :
        public Numeric_Data_t<u16>
    {
    public:
        static constexpr value_type _NONE_              = static_cast<value_type>(-1);

        static constexpr value_type MINUTE_MASK         = 0x00FF;
        static constexpr value_type HOUR_MASK           = 0xFF00;

        static constexpr value_type MINUTE_BIT_INDEX    = 0;
        static constexpr value_type HOUR_BIT_INDEX      = 8;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return
                Minute(value) != none<Calendar_Time_Minute_t>() &&
                Hour(value) != none<Calendar_Time_Hour_24_t>();
        }

        static maybe<Calendar_Time_Minute_t> Minute(value_type self)
        {
            return (self & MINUTE_MASK) >> MINUTE_BIT_INDEX;
        }

        static void Minute(value_type& self, value_type value)
        {
            self = ((value << MINUTE_BIT_INDEX) & MINUTE_MASK) | (self & ~MINUTE_MASK);
        }

        static maybe<Calendar_Time_Hour_24_t> Hour(value_type self)
        {
            return (self & HOUR_MASK) >> HOUR_BIT_INDEX;
        }

        static void Hour(value_type& self, value_type value)
        {
            self = ((value << HOUR_BIT_INDEX) & HOUR_MASK) | (self & ~HOUR_MASK);
        }
    };

    class Calendar_Time_24_t :
        public Numeric_t<Calendar_Time_24_t_data>
    {
    public:
        using Numeric_t::Numeric_t;

    public:
        Calendar_Time_24_t() :
            Numeric_t()
        {
        }

        Calendar_Time_24_t(some<Calendar_Time_Hour_24_t> hour,
                           some<Calendar_Time_Minute_t> minute) :
            Numeric_t()
        {
            SKYLIB_ASSERT_SOME(hour);
            SKYLIB_ASSERT_SOME(minute);

            Hour(hour);
            Minute(minute);
        }

    public:
        some<Calendar_Time_Hour_24_t> Hour() const
        {
            maybe<Calendar_Time_Hour_24_t> hour = Numeric_t::Hour(this->value);
            SKYLIB_ASSERT(hour);
            return hour();
        }

        Calendar_Time_24_t& Hour(some<Calendar_Time_Hour_24_t> hour)
        {
            SKYLIB_ASSERT_SOME(hour);
            Numeric_t::Hour(this->value, hour());
            return *this;
        }

        some<Calendar_Time_Minute_t> Minute() const
        {
            maybe<Calendar_Time_Minute_t> minute = Numeric_t::Minute(this->value);
            SKYLIB_ASSERT(minute);
            return minute();
        }

        Calendar_Time_24_t& Minute(some<Calendar_Time_Minute_t> minute)
        {
            SKYLIB_ASSERT_SOME(minute);
            Numeric_t::Minute(this->value, minute());
            return *this;
        }

    public:
        operator some<Calendar_Time_Hour_24_t>() const
        {
            return Hour();
        }

        operator some<Calendar_Time_Minute_t>() const
        {
            return Minute();
        }
    };

    template <>
    class none<Calendar_Time_24_t> :
        public none_numeric<Calendar_Time_24_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Calendar_Time_24_t> :
        public maybe_numeric<Calendar_Time_24_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Calendar_Time_24_t> :
        public some_numeric<Calendar_Time_24_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
