/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/calendar.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/global.inl"
#include "doticu_skylib/math.h"

namespace doticu_skylib {

    Calendar_t& Calendar_t::Self()
    {
        static auto self = *reinterpret_cast
            <Calendar_t**>
            (Game_t::Base_Address() + Offset_e::SELF);

        SKYLIB_ASSERT(self);
        return *self;
    }

    maybe<Calendar_Now_t> Calendar_t::Days_Passed_Now(Float_t days_passed, Bool_t do_replicate_bugs)
    {
        if (days_passed >= 0.0f) {
            static const size_t DAYS_PER_MONTH[12]
            {
                31, // MORNING_STAR
                28, // SUNS_DAWN
                31, // FIRST_SEED
                30, // RAINS_HAND
                31, // SECOND_SEED
                30, // MID_YEAR
                31, // SUNS_HEIGHT
                31, // LAST_SEED
                30, // HEARTH_FIRE
                31, // FROST_FALL
                30, // SUNS_DUSK
                31, // EVENING_STAR
            };

            /*
                this is a bug in the vanilla GameTimeToString.
                their code produces the left and is zero indexed, ours on the right which is one indexed.
                the repeat changes as the current date in game changes. It always repeats the next day.

                current date: 9/1/201
                13.000000, 07/29/0201 00:00 ----- 8/30/201 12:00 AM
                14.000000, 07/30/0201 00:00 ----- 8/31/201 12:00 AM
                15.000000, 08/00/0201 00:00 ----- 9/1/201 12:00 AM
                16.000000, 08/00/0201 00:00 ----- 9/2/201 12:00 AM <--------- this is a repeat of the previous day in their code
                17.000000, 08/01/0201 00:00 ----- 9/3/201 12:00 AM
                18.000000, 08/02/0201 00:00 ----- 9/4/201 12:00 AM
                19.000000, 08/03/0201 00:00 ----- 9/5/201 12:00 AM
                20.000000, 08/04/0201 00:00 ----- 9/6/201 12:00 AM

                to fix it, we need to also take into account when the day starts in their buggy code (4:00 PM)
            */
            if (do_replicate_bugs) {
                Calendar_t& calendar = Self();
                if (calendar.days_passed && days_passed >= floor(calendar.days_passed->value) + (16.0f / 24.0f)) {
                    days_passed -= 1.0f;
                }
            }

            size_t relative_days = floor(days_passed);
            size_t relative_year = floor(relative_days / DAYS_PER_YEAR);
            relative_days -= relative_year * DAYS_PER_YEAR;

            size_t absolute_year = DEFAULT_YEAR + relative_year;
            size_t absolute_month = DEFAULT_MONTH;
            size_t absolute_day = DEFAULT_DAY;
            if (absolute_day + relative_days <= DAYS_PER_MONTH[absolute_month]) {
                absolute_day += relative_days;
            } else {
                relative_days -= DAYS_PER_MONTH[absolute_month] - absolute_day;
                absolute_month += 1;
                absolute_day = 1;
                while (relative_days > 0) {
                    if (relative_days > DAYS_PER_MONTH[absolute_month]) {
                        relative_days -= DAYS_PER_MONTH[absolute_month];
                        if (absolute_month == 11) {
                            absolute_year += 1;
                            absolute_month = 0;
                        } else {
                            absolute_month += 1;
                        }
                    } else {
                        absolute_day = relative_days;
                        relative_days = 0;
                    }
                }
            }

            Float_t absolute_hours = ((days_passed - floor(days_passed)) * 24);
            Float_t absolute_minutes = (absolute_hours - floor(absolute_hours)) * 60;
            // nope, it does not appear to take into account the 8 hour default difference, so we don't either.

            // believe it or not, in their buggy code, the days starts and ends at 4:00 PM, not 12:00 AM. bizarre!
            // of course the calendar itself starts where you would expect, but in GameTimeToString it does not
            if (do_replicate_bugs && absolute_hours >= 16.0f) {
                if (absolute_day + 1 > DAYS_PER_MONTH[absolute_month]) {
                    absolute_day = 1;
                    if (absolute_month + 1 > 11) {
                        absolute_month = 0;
                        absolute_year += 1;
                    } else {
                        absolute_month += 1;
                    }
                } else {
                    absolute_day += 1;
                }
            }

            Calendar_Date_Year_t year = absolute_year;
            Calendar_Date_Month_t month = absolute_month;
            Calendar_Date_Day_t day = absolute_day;
            Calendar_Time_Hour_24_t hour_24 = absolute_hours;
            Calendar_Time_Minute_t minute = absolute_minutes;
            if (year && month && day && hour_24 && minute) {
                some<Calendar_Date_t> date(month(), day(), year());
                some<Calendar_Time_24_t> time_24(hour_24(), minute());
                some<Calendar_Time_t> time(time_24);
                return Calendar_Now_t(date, time);
            } else {
                return none<Calendar_Now_t>();
            }
        } else {
            return none<Calendar_Now_t>();
        }
    }

    maybe<Calendar_Date_Weekday_e> Calendar_t::Days_Passed_Weekday(Float_t days_passed)
    {
        if (days_passed >= 0.0f) {
            return static_cast<size_t>(floor(days_passed)) % 7;
        } else {
            return none<Calendar_Date_Weekday_e>();
        }
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

        Date(now.Date());
        Time(now.Time());
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

        Month(date.Month());
        Day(date.Day());
        Year(date.Year());
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

        Time_24(time.Time_24());
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

        Hour_24(time_24.Hour());
        Minute(time_24.Minute());
    }

    maybe<Calendar_Time_12_t> Calendar_t::Time_12() const
    {
        maybe<Calendar_Time_t> time = Time();

        if (time) {
            return time.Time_12();
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
            return time.Hour_12();
        } else {
            return Calendar_Time_Hour_12_t::_NONE_;
        }
    }

    void Calendar_t::Hour_12(some<Calendar_Time_Hour_12_t> hour_12)
    {
        SKYLIB_ASSERT_SOME(hour_12);

        maybe<Calendar_Time_t> time = Time();

        if (time) {
            Time(time.Hour_12(hour_12));
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
            return time.AM_PM();
        } else {
            return Calendar_Time_AM_PM_e::_NONE_;
        }
    }

    void Calendar_t::AM_PM(some<Calendar_Time_AM_PM_e> am_pm)
    {
        SKYLIB_ASSERT_SOME(am_pm);

        maybe<Calendar_Time_t> time = Time();

        if (time) {
            Time(time.AM_PM(am_pm));
        }
    }

    maybe<Calendar_Now_t> Calendar_t::Days_Passed_Now() const
    {
        if (this->days_passed) {
            return Days_Passed_Now(this->days_passed->Float(), false);
        } else {
            return none<Calendar_Now_t>();
        }
    }

    maybe<Calendar_Date_Weekday_e> Calendar_t::Days_Passed_Weekday() const
    {
        if (this->days_passed) {
            return Days_Passed_Weekday(this->days_passed->Float());
        } else {
            return none<Calendar_Date_Weekday_e>();
        }
    }

    void Calendar_t::Log_Now(std::string indent) const
    {
        SKYLIB_LOG(indent + "Calendar_t::Log_Now");
        SKYLIB_LOG(indent + "{");

        maybe<Calendar_Now_t> now = Now();
        if (now) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "now:");
            now.Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "now: (none)");
        }

        maybe<Calendar_Now_t> days_passed_now = Days_Passed_Now();
        if (days_passed_now) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "days_passed_now:");
            days_passed_now.Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "days_passed_now: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
