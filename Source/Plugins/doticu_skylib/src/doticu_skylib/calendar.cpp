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

    maybe<Calendar_Now_t> Calendar_t::Now() const
    {
        maybe<Calendar_Date_t> date = Date();
        maybe<Calendar_Time_t> time = Time();

        if (date && time) {
            return Calendar_Now_t(date(), time());
        } else {
            return Calendar_Now_t::_NONE_;
        }
    }

    void Calendar_t::Now(some<Calendar_Now_t> now)
    {
        SKYLIB_ASSERT_SOME(now);

        Date(now().Date());
        Time(now().Time());
    }

    maybe<Calendar_Date_t> Calendar_t::Date() const
    {
        maybe<Calendar_Date_Month_t> month = Month();
        maybe<Calendar_Date_Day_t> day = Day();
        maybe<Calendar_Date_Year_t> year = Year();

        if (month && day && year) {
            return Calendar_Date_t(month(), day(), year());
        } else {
            return Calendar_Date_t::_NONE_;
        }
    }

    void Calendar_t::Date(some<Calendar_Date_t> date)
    {
        SKYLIB_ASSERT_SOME(date);

        Month(date().Month());
        Day(date().Day());
        Year(date().Year());
    }

    maybe<Calendar_Date_Month_t> Calendar_t::Month() const
    {
        if (this->month) {
            return this->month->As<Calendar_Date_Month_t::value_type>();
        } else {
            return Calendar_Date_Month_t::_NONE_;
        }
    }

    void Calendar_t::Month(some<Calendar_Date_Month_t> month)
    {
        SKYLIB_ASSERT_SOME(month);

        if (this->month) {
            this->month->As<Calendar_Date_Month_t::value_type>(month());
        }
    }

    maybe<Calendar_Date_Day_t> Calendar_t::Day() const
    {
        if (this->day) {
            return this->day->As<Calendar_Date_Day_t::value_type>();
        } else {
            return Calendar_Date_Day_t::_NONE_;
        }
    }

    void Calendar_t::Day(some<Calendar_Date_Day_t> day)
    {
        SKYLIB_ASSERT_SOME(day);

        if (this->day) {
            this->day->As<Calendar_Date_Day_t::value_type>(day());
        }
    }

    maybe<Calendar_Date_Year_t> Calendar_t::Year() const
    {
        if (this->year) {
            return this->year->As<Calendar_Date_Year_t::value_type>();
        } else {
            return Calendar_Date_Year_t::_NONE_;
        }
    }

    void Calendar_t::Year(some<Calendar_Date_Year_t> year)
    {
        SKYLIB_ASSERT_SOME(year);

        if (this->year) {
            this->year->As<Calendar_Date_Year_t::value_type>(year());
        }
    }

    maybe<Calendar_Time_t> Calendar_t::Time() const
    {
        maybe<Calendar_Time_24_t> time_24 = Time_24();

        if (time_24) {
            return Calendar_Time_t(some<Calendar_Time_24_t>(time_24()));
        } else {
            return Calendar_Time_t::_NONE_;
        }
    }

    void Calendar_t::Time(some<Calendar_Time_t> time)
    {
        SKYLIB_ASSERT_SOME(time);

        Time_24(time().Time_24());
    }

    maybe<Calendar_Time_24_t> Calendar_t::Time_24() const
    {
        maybe<Calendar_Time_Hour_24_t> hour_24 = Hour_24();
        maybe<Calendar_Time_Minute_t> minute = Minute();

        if (hour_24 && minute) {
            return Calendar_Time_24_t(hour_24(), minute());
        } else {
            return Calendar_Time_24_t::_NONE_;
        }
    }

    void Calendar_t::Time_24(some<Calendar_Time_24_t> time_24)
    {
        SKYLIB_ASSERT_SOME(time_24);

        Hour_24(time_24().Hour());
        Minute(time_24().Minute());
    }

    maybe<Calendar_Time_12_t> Calendar_t::Time_12() const
    {
        maybe<Calendar_Time_t> time = Time();

        if (time) {
            return time().Time_12();
        } else {
            return Calendar_Time_12_t::_NONE_;
        }
    }

    void Calendar_t::Time_12(some<Calendar_Time_12_t> time_12)
    {
        SKYLIB_ASSERT_SOME(time_12);

        Time(Calendar_Time_t(time_12));
    }

    maybe<Calendar_Time_Hour_24_t> Calendar_t::Hour_24() const
    {
        if (this->hour) {
            return static_cast<Calendar_Time_Hour_24_t::value_type>
                (floorf(this->hour->As<Float_t>()));
        } else {
            return Calendar_Time_Hour_24_t::_NONE_;
        }
    }

    void Calendar_t::Hour_24(some<Calendar_Time_Hour_24_t> hour_24)
    {
        SKYLIB_ASSERT_SOME(hour_24);

        if (this->hour) {
            this->hour->As<Float_t>(static_cast<Float_t>(hour_24()) + static_cast<Float_t>(Minute()()) / 60);
        }
    }

    maybe<Calendar_Time_Hour_12_t> Calendar_t::Hour_12() const
    {
        maybe<Calendar_Time_t> time = Time();

        if (time) {
            return time().Hour_12();
        } else {
            return Calendar_Time_Hour_12_t::_NONE_;
        }
    }

    void Calendar_t::Hour_12(some<Calendar_Time_Hour_12_t> hour_12)
    {
        SKYLIB_ASSERT_SOME(hour_12);

        maybe<Calendar_Time_t> time = Time();

        if (time) {
            Time(time().Hour_12(hour_12));
        }
    }

    maybe<Calendar_Time_Minute_t> Calendar_t::Minute() const
    {
        if (this->hour) {
            return static_cast<Calendar_Time_Minute_t::value_type>
                ((this->hour->As<Float_t>() - static_cast<Float_t>(Hour_24()())) * 60);
        } else {
            return Calendar_Time_Minute_t::_NONE_;
        }
    }

    void Calendar_t::Minute(some<Calendar_Time_Minute_t> minute)
    {
        SKYLIB_ASSERT_SOME(minute);

        if (this->hour) {
            this->hour->As<Float_t>(static_cast<Float_t>(Hour_24()()) + static_cast<Float_t>(minute()) / 60);
        }
    }

    maybe<Calendar_Time_AM_PM_e> Calendar_t::AM_PM() const
    {
        maybe<Calendar_Time_t> time = Time();

        if (time) {
            return time().AM_PM();
        } else {
            return Calendar_Time_AM_PM_e::_NONE_;
        }
    }

    void Calendar_t::AM_PM(some<Calendar_Time_AM_PM_e> am_pm)
    {
        SKYLIB_ASSERT_SOME(am_pm);

        maybe<Calendar_Time_t> time = Time();

        if (time) {
            Time(time().AM_PM(am_pm));
        }
    }

    void Calendar_t::Log_Now(std::string indent) const
    {
        SKYLIB_LOG(indent + "Calendar_t::Log_Now");
        SKYLIB_LOG(indent + "{");

        maybe<Calendar_Now_t> now = Now();
        if (now) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "now:");
            now().Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "now: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
