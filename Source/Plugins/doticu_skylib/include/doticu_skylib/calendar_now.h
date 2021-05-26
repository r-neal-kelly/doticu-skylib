/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/calendar_date.h"
#include "doticu_skylib/calendar_time.h"

namespace doticu_skylib {

    class Calendar_Now_t_data :
        public Numeric_Data_t<u64>
    {
    public:
        static constexpr value_type _NONE_          = static_cast<value_type>(-1);

        static constexpr value_type TIME_MASK       = 0x00000000FFFFFFFF;
        static constexpr value_type DATE_MASK       = 0xFFFFFFFF00000000;

        static constexpr value_type TIME_BIT_INDEX  = 0;
        static constexpr value_type DATE_BIT_INDEX  = 32;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return
                Time(value) != none<Calendar_Time_t>() &&
                Date(value) != none<Calendar_Date_t>();
        }

        static maybe<Calendar_Time_t> Time(value_type self)
        {
            return (self & TIME_MASK) >> TIME_BIT_INDEX;
        }

        static void Time(value_type& self, value_type value)
        {
            self = ((value << TIME_BIT_INDEX) & TIME_MASK) | (self & ~TIME_MASK);
        }

        static maybe<Calendar_Date_t> Date(value_type self)
        {
            return (self & DATE_MASK) >> DATE_BIT_INDEX;
        }

        static void Date(value_type& self, value_type value)
        {
            self = ((value << DATE_BIT_INDEX) & DATE_MASK) | (self & ~DATE_MASK);
        }
    };

    class Calendar_Now_t :
        public Numeric_t<Calendar_Now_t_data>
    {
    public:
        using Numeric_t::Numeric_t;

    public:
        Calendar_Now_t() :
            Numeric_t()
        {
        }

        Calendar_Now_t(some<Calendar_Date_t> date,
                       some<Calendar_Time_t> time) :
            Numeric_t()
        {
            SKYLIB_ASSERT_SOME(date);
            SKYLIB_ASSERT_SOME(time);

            Date(date);
            Time(time);
        }

    public:
        some<Calendar_Date_t> Date() const
        {
            maybe<Calendar_Date_t> date = Numeric_t::Date(this->value);
            SKYLIB_ASSERT(date);
            return date();
        }

        Calendar_Now_t& Date(some<Calendar_Date_t> date)
        {
            SKYLIB_ASSERT_SOME(date);
            Numeric_t::Date(this->value, date());
            return *this;
        }

        some<Calendar_Date_Month_t> Month() const
        {
            return Date().Month();
        }

        Calendar_Now_t& Month(some<Calendar_Date_Month_t> month)
        {
            SKYLIB_ASSERT_SOME(month);
            return Date(Date().Month(month));
        }

        some<Calendar_Date_Day_t> Day() const
        {
            return Date().Day();
        }

        Calendar_Now_t& Day(some<Calendar_Date_Day_t> day)
        {
            SKYLIB_ASSERT_SOME(day);
            return Date(Date().Day(day));
        }

        some<Calendar_Date_Year_t> Year() const
        {
            return Date().Year();
        }

        Calendar_Now_t& Year(some<Calendar_Date_Year_t> year)
        {
            SKYLIB_ASSERT_SOME(year);
            return Date(Date().Year(year));
        }

        some<Calendar_Time_t> Time() const
        {
            maybe<Calendar_Time_t> time = Numeric_t::Time(this->value);
            SKYLIB_ASSERT(time);
            return time();
        }

        Calendar_Now_t& Time(some<Calendar_Time_t> time)
        {
            SKYLIB_ASSERT_SOME(time);
            Numeric_t::Time(this->value, time());
            return *this;
        }

        some<Calendar_Time_24_t> Time_24() const
        {
            return Time().Time_24();
        }

        Calendar_Now_t& Time_24(some<Calendar_Time_24_t> time_24)
        {
            SKYLIB_ASSERT_SOME(time_24);
            return Time(Time().Time_24(time_24));
        }

        some<Calendar_Time_12_t> Time_12() const
        {
            return Time().Time_12();
        }

        Calendar_Now_t& Time_12(some<Calendar_Time_12_t> time_12)
        {
            SKYLIB_ASSERT_SOME(time_12);
            return Time(Time().Time_12(time_12));
        }

        some<Calendar_Time_Hour_24_t> Hour_24() const
        {
            return Time().Hour_24();
        }

        Calendar_Now_t& Hour_24(some<Calendar_Time_Hour_24_t> hour_24)
        {
            SKYLIB_ASSERT_SOME(hour_24);
            return Time(Time().Hour_24(hour_24));
        }

        some<Calendar_Time_Hour_12_t> Hour_12() const
        {
            return Time().Hour_12();
        }

        Calendar_Now_t& Hour_12(some<Calendar_Time_Hour_12_t> hour_12)
        {
            SKYLIB_ASSERT_SOME(hour_12);
            return Time(Time().Hour_12(hour_12));
        }

        some<Calendar_Time_Minute_t> Minute() const
        {
            return Time().Minute();
        }

        Calendar_Now_t& Minute(some<Calendar_Time_Minute_t> minute)
        {
            SKYLIB_ASSERT_SOME(minute);
            return Time(Time().Minute(minute));
        }

        some<Calendar_Time_AM_PM_e> AM_PM() const
        {
            return Time().AM_PM();
        }

        Calendar_Now_t& AM_PM(some<Calendar_Time_AM_PM_e> am_pm)
        {
            SKYLIB_ASSERT_SOME(am_pm);
            return Time(Time().AM_PM(am_pm));
        }

        String_t As_String() const
        {
            if (Is_Valid(this->value)) {
                return Date().As_String() + " " + Time_12().As_String();
            } else {
                return "";
            }
        }

    public:
        operator some<Calendar_Date_t>() const
        {
            return Date();
        }

        operator some<Calendar_Date_Month_t>() const
        {
            return Month();
        }

        operator some<Calendar_Date_Day_t>() const
        {
            return Day();
        }

        operator some<Calendar_Date_Year_t>() const
        {
            return Year();
        }

        operator some<Calendar_Time_t>() const
        {
            return Time();
        }

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

    public:
        void Log(std::string indent = "") const
        {
            SKYLIB_LOG(indent + "Calendar_Now_t::Log");
            SKYLIB_LOG(indent + "{");

            if (Is_Valid(this->value)) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "%s", As_String());
            }

            SKYLIB_LOG(indent + "}");
        }
    };

    template <>
    class none<Calendar_Now_t> :
        public none_numeric<Calendar_Now_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Calendar_Now_t> :
        public maybe_numeric<Calendar_Now_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Calendar_Now_t> :
        public some_numeric<Calendar_Now_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
