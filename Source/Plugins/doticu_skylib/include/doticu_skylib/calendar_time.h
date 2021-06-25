/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/calendar_time_12.h"
#include "doticu_skylib/calendar_time_24.h"

namespace doticu_skylib {

    class Calendar_Time_t_data :
        public Numeric_Data_t<u32>
    {
    public:
        static constexpr value_type _NONE_  = static_cast<value_type>(-1);

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return Calendar_Time_24_t(value) != none<Calendar_Time_24_t>();
        }

        static some<Calendar_Time_24_t> From_12_To_24(some<Calendar_Time_12_t> time_12)
        {
            SKYLIB_ASSERT_SOME(time_12);

            Calendar_Time_Hour_12_t::value_type hour = time_12.Hour()();
            if (hour == 12) {
                hour = 0;
            }
            if (time_12.AM_PM() == Calendar_Time_AM_PM_e::PM) {
                hour += 12;
            }
            return Calendar_Time_24_t(hour, time_12.Minute());
        }

        static some<Calendar_Time_12_t> From_24_To_12(some<Calendar_Time_24_t> time_24)
        {
            SKYLIB_ASSERT_SOME(time_24);

            Calendar_Time_Hour_24_t::value_type hour = time_24.Hour()();
            Calendar_Time_AM_PM_e am_pm;
            if (hour < 12) {
                am_pm = Calendar_Time_AM_PM_e::AM;
            } else {
                hour -= 12;
                am_pm = Calendar_Time_AM_PM_e::PM;
            }
            if (hour == 0) {
                hour = 12;
            }
            return Calendar_Time_12_t(hour, time_24.Minute(), am_pm);
        }
    };

    class Calendar_Time_t :
        public Numeric_t<Calendar_Time_t_data>
    {
    public:
        using Numeric_t::Numeric_t;

    public:
        Calendar_Time_t() :
            Numeric_t()
        {
        }

        Calendar_Time_t(some<Calendar_Time_24_t> time_24) :
            Numeric_t()
        {
            SKYLIB_ASSERT_SOME(time_24);
            Time_24(time_24);
        }

        Calendar_Time_t(some<Calendar_Time_12_t> time_12) :
            Numeric_t()
        {
            SKYLIB_ASSERT_SOME(time_12);
            Time_12(time_12);
        }

    public:
        some<Calendar_Time_24_t> Time_24() const
        {
            some<Calendar_Time_24_t> time_24 = this->value;
            SKYLIB_ASSERT_SOME(time_24);
            return time_24;
        }

        Calendar_Time_t& Time_24(some<Calendar_Time_24_t> time_24)
        {
            SKYLIB_ASSERT_SOME(time_24);
            this->value = time_24();
            return *this;
        }

        some<Calendar_Time_12_t> Time_12() const
        {
            some<Calendar_Time_12_t> time_12 = From_24_To_12(this->value);
            SKYLIB_ASSERT_SOME(time_12);
            return time_12;
        }

        Calendar_Time_t& Time_12(some<Calendar_Time_12_t> time_12)
        {
            SKYLIB_ASSERT_SOME(time_12);
            this->value = From_12_To_24(time_12)();
            return *this;
        }

        some<Calendar_Time_Hour_24_t> Hour_24() const
        {
            return Time_24().Hour();
        }

        Calendar_Time_t& Hour_24(some<Calendar_Time_Hour_24_t> hour_24)
        {
            SKYLIB_ASSERT_SOME(hour_24);
            return Time_24(Time_24().Hour(hour_24));
        }

        some<Calendar_Time_Hour_12_t> Hour_12() const
        {
            return Time_12().Hour();
        }

        Calendar_Time_t& Hour_12(some<Calendar_Time_Hour_12_t> hour_12)
        {
            SKYLIB_ASSERT_SOME(hour_12);
            return Time_12(Time_12().Hour(hour_12));
        }

        some<Calendar_Time_Minute_t> Minute() const
        {
            return Time_24().Minute();
        }

        Calendar_Time_t& Minute(some<Calendar_Time_Minute_t> minute)
        {
            SKYLIB_ASSERT_SOME(minute);
            return Time_24(Time_24().Minute(minute));
        }

        some<Calendar_Time_AM_PM_e> AM_PM() const
        {
            return Time_12().AM_PM();
        }

        Calendar_Time_t& AM_PM(some<Calendar_Time_AM_PM_e> am_pm)
        {
            SKYLIB_ASSERT_SOME(am_pm);
            return Time_12(Time_12().AM_PM(am_pm));
        }

        u16 In_Minutes() const
        {
            return Hour_24()() * 60 + Minute()();
        }

    public:
        operator some<Calendar_Time_24_t>() const
        {
            return Time_24();
        }

        operator some<Calendar_Time_12_t>() const
        {
            return Time_12();
        }

        operator some<Calendar_Time_Hour_24_t>() const
        {
            return Hour_24();
        }

        operator some<Calendar_Time_Hour_12_t>() const
        {
            return Hour_12();
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
    class none<Calendar_Time_t> :
        public none_numeric<Calendar_Time_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Calendar_Time_t> :
        public maybe_numeric<Calendar_Time_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Calendar_Time_t> :
        public some_numeric<Calendar_Time_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
