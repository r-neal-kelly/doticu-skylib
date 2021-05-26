/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/calendar_time_hour_12.h"
#include "doticu_skylib/calendar_time_minute.h"
#include "doticu_skylib/enum_calendar_time_am_pm.h"

namespace doticu_skylib {

    class Calendar_Time_12_t_data :
        public Numeric_Data_t<u32>
    {
    public:
        static constexpr value_type _NONE_              = static_cast<value_type>(-1);

        static constexpr value_type MINUTE_MASK         = 0x000000FF;
        static constexpr value_type HOUR_MASK           = 0x0000FF00;
        static constexpr value_type AM_PM_MASK          = 0x00FF0000;

        static constexpr value_type MINUTE_BIT_INDEX    = 0;
        static constexpr value_type HOUR_BIT_INDEX      = 8;
        static constexpr value_type AM_PM_BIT_INDEX     = 16;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return
                Minute(value) != none<Calendar_Time_Minute_t>() &&
                Hour(value) != none<Calendar_Time_Hour_12_t>() &&
                AM_PM(value) != none<Calendar_Time_AM_PM_e>();
        }

        static maybe<Calendar_Time_Minute_t> Minute(value_type self)
        {
            return (self & MINUTE_MASK) >> MINUTE_BIT_INDEX;
        }

        static void Minute(value_type& self, value_type value)
        {
            self = ((value << MINUTE_BIT_INDEX) & MINUTE_MASK) | (self & ~MINUTE_MASK);
        }

        static maybe<Calendar_Time_Hour_12_t> Hour(value_type self)
        {
            return (self & HOUR_MASK) >> HOUR_BIT_INDEX;
        }

        static void Hour(value_type& self, value_type value)
        {
            self = ((value << HOUR_BIT_INDEX) & HOUR_MASK) | (self & ~HOUR_MASK);
        }

        static maybe<Calendar_Time_AM_PM_e> AM_PM(value_type self)
        {
            return (self & AM_PM_MASK) >> AM_PM_BIT_INDEX;
        }

        static void AM_PM(value_type& self, value_type value)
        {
            self = ((value << AM_PM_BIT_INDEX) & AM_PM_MASK) | (self & ~AM_PM_MASK);
        }
    };

    class Calendar_Time_12_t :
        public Numeric_t<Calendar_Time_12_t_data>
    {
    public:
        using Numeric_t::Numeric_t;

    public:
        Calendar_Time_12_t() :
            Numeric_t()
        {
        }

        Calendar_Time_12_t(some<Calendar_Time_Hour_12_t> hour,
                           some<Calendar_Time_Minute_t> minute,
                           some<Calendar_Time_AM_PM_e> am_pm) :
            Numeric_t()
        {
            SKYLIB_ASSERT_SOME(hour);
            SKYLIB_ASSERT_SOME(minute);
            SKYLIB_ASSERT_SOME(am_pm);

            Hour(hour);
            Minute(minute);
            AM_PM(am_pm);
        }

    public:
        some<Calendar_Time_Hour_12_t> Hour() const
        {
            maybe<Calendar_Time_Hour_12_t> hour = Numeric_t::Hour(this->value);
            SKYLIB_ASSERT(hour);
            return hour();
        }

        Calendar_Time_12_t& Hour(some<Calendar_Time_Hour_12_t> hour)
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

        Calendar_Time_12_t& Minute(some<Calendar_Time_Minute_t> minute)
        {
            SKYLIB_ASSERT_SOME(minute);
            Numeric_t::Minute(this->value, minute());
            return *this;
        }

        some<Calendar_Time_AM_PM_e> AM_PM() const
        {
            maybe<Calendar_Time_AM_PM_e> am_pm = Numeric_t::AM_PM(this->value);
            SKYLIB_ASSERT(am_pm);
            return am_pm();
        }

        Calendar_Time_12_t& AM_PM(some<Calendar_Time_AM_PM_e> am_pm)
        {
            SKYLIB_ASSERT_SOME(am_pm);
            Numeric_t::AM_PM(this->value, am_pm());
            return *this;
        }

        String_t As_String() const
        {
            if (Is_Valid(this->value)) {
                some<Calendar_Time_Minute_t> minute = Minute();
                return
                    std::to_string(Hour()()) + ":" +
                    (minute() > 9 ? std::to_string(minute()) : std::string("0") + std::to_string(minute())) + " " +
                    AM_PM()().As_String()();
            } else {
                return "";
            }
        }

    public:
        operator some<Calendar_Time_Hour_12_t>() const
        {
            return Hour();
        }

        operator some<Calendar_Time_Minute_t>() const
        {
            return Minute();
        }

        operator some<Calendar_Time_AM_PM_e>() const
        {
            return AM_PM();
        }
    };

    template <>
    class none<Calendar_Time_12_t> :
        public none_numeric<Calendar_Time_12_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Calendar_Time_12_t> :
        public maybe_numeric<Calendar_Time_12_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Calendar_Time_12_t> :
        public some_numeric<Calendar_Time_12_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
