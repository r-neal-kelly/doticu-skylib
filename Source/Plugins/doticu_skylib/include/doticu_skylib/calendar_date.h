/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/calendar_date_day.h"
#include "doticu_skylib/calendar_date_month.h"
#include "doticu_skylib/calendar_date_year.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Calendar_Date_t_data :
        public Numeric_Data_t<u32>
    {
    public:
        static constexpr value_type _NONE_          = static_cast<value_type>(-1);

        static constexpr value_type DAY_MASK        = 0x000000FF;
        static constexpr value_type MONTH_MASK      = 0x0000FF00;
        static constexpr value_type YEAR_MASK       = 0xFFFF0000;

        static constexpr value_type DAY_BIT_INDEX   = 0;
        static constexpr value_type MONTH_BIT_INDEX = 8;
        static constexpr value_type YEAR_BIT_INDEX  = 16;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return
                Day(value) != none<Calendar_Date_Day_t>() &&
                Month(value) != none<Calendar_Date_Month_t>() &&
                Year(value) != none<Calendar_Date_Year_t>();
        }

        static maybe<Calendar_Date_Day_t> Day(value_type self)
        {
            return (self & DAY_MASK) >> DAY_BIT_INDEX;
        }

        static void Day(value_type& self, value_type value)
        {
            self = ((value << DAY_BIT_INDEX) & DAY_MASK) | (self & ~DAY_MASK);
        }

        static maybe<Calendar_Date_Month_t> Month(value_type self)
        {
            return (self & MONTH_MASK) >> MONTH_BIT_INDEX;
        }

        static void Month(value_type& self, value_type value)
        {
            self = ((value << MONTH_BIT_INDEX) & MONTH_MASK) | (self & ~MONTH_MASK);
        }

        static maybe<Calendar_Date_Year_t> Year(value_type self)
        {
            return (self & YEAR_MASK) >> YEAR_BIT_INDEX;
        }

        static void Year(value_type& self, value_type value)
        {
            self = ((value << YEAR_BIT_INDEX) & YEAR_MASK) | (self & ~YEAR_MASK);
        }
    };

    class Calendar_Date_t :
        public Numeric_t<Calendar_Date_t_data>
    {
    public:
        using Numeric_t::Numeric_t;

    public:
        Calendar_Date_t() :
            Numeric_t()
        {
        }

        Calendar_Date_t(some<Calendar_Date_Month_t> month,
                        some<Calendar_Date_Day_t> day,
                        some<Calendar_Date_Year_t> year) :
            Numeric_t()
        {
            SKYLIB_ASSERT_SOME(month);
            SKYLIB_ASSERT_SOME(day);
            SKYLIB_ASSERT_SOME(year);

            Month(month);
            Day(day);
            Year(year);
        }

    public:
        some<Calendar_Date_Month_t> Month() const
        {
            maybe<Calendar_Date_Month_t> month = Numeric_t::Month(this->value);
            SKYLIB_ASSERT(month);
            return month();
        }

        Calendar_Date_t& Month(some<Calendar_Date_Month_t> month)
        {
            SKYLIB_ASSERT_SOME(month);
            Numeric_t::Month(this->value, month());
            return *this;
        }

        some<Calendar_Date_Day_t> Day() const
        {
            maybe<Calendar_Date_Day_t> day = Numeric_t::Day(this->value);
            SKYLIB_ASSERT(day);
            return day();
        }

        Calendar_Date_t& Day(some<Calendar_Date_Day_t> day)
        {
            SKYLIB_ASSERT_SOME(day);
            Numeric_t::Day(this->value, day());
            return *this;
        }

        some<Calendar_Date_Year_t> Year() const
        {
            maybe<Calendar_Date_Year_t> year = Numeric_t::Year(this->value);
            SKYLIB_ASSERT(year);
            return year();
        }

        Calendar_Date_t& Year(some<Calendar_Date_Year_t> year)
        {
            SKYLIB_ASSERT_SOME(year);
            Numeric_t::Year(this->value, year());
            return *this;
        }

        String_t As_String() const
        {
            if (Is_Valid(this->value)) {
                return
                    std::to_string(Month()() + 1) + "/" +
                    std::to_string(Day()()) + "/" +
                    std::to_string(Year()());
            } else {
                return "";
            }
        }

    public:
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
    };

    template <>
    class none<Calendar_Date_t> :
        public none_numeric<Calendar_Date_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Calendar_Date_t> :
        public maybe_numeric<Calendar_Date_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Calendar_Date_t> :
        public some_numeric<Calendar_Date_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
