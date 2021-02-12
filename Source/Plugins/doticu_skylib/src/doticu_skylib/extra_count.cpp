/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_count.h"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/math.h"

namespace doticu_skylib {

    some<Extra_Count_t*> Extra_Count_t::Create(s16 count)
    {
        some<Extra_Count_t*> x_count = Extra_Data_t::Create<Extra_Count_t>();
        x_count->Count(count);
        return x_count;
    }

    void Extra_Count_t::Destroy(some<Extra_Count_t*> x_count)
    {
        SKYLIB_ASSERT_SOME(x_count);
        Extra_Data_t::Destroy<Extra_Count_t>(x_count);
    }

    s16 Extra_Count_t::Count()
    {
        if (this->count < 0) {
            this->count = std::numeric_limits<s16>::max();
        }
        return this->count;
    }

    void Extra_Count_t::Count(s16 count)
    {
        if (count < 0) {
            this->count = 0;
        } else {
            this->count = count;
        }
    }

    s16 Extra_Count_t::Increment_Count(s16 amount)
    {
        if (amount > 0) {
            s16 new_count = Count() + amount;
            if (new_count < 0) {
                this->count = std::numeric_limits<s16>::max();
            } else {
                this->count = new_count;
            }
        }
        return this->count;
    }

    s16 Extra_Count_t::Decrement_Count(s16 amount)
    {
        if (amount > 0) {
            s16 new_count = Count() - amount;
            if (new_count < 0) {
                this->count = 0;
            } else {
                this->count = new_count;
            }
        }
        return this->count;
    }

}
