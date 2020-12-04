/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Leveled_Actor_Base_t;

    class Actor_Base_Leveleds_t
    {
    public:
        some<Actor_Base_t*>                     actor_base;
        Vector_t<some<Leveled_Actor_Base_t*>>   leveleds;

        Actor_Base_Leveleds_t(some<Actor_Base_t*> actor_base) :
            actor_base(actor_base)
        {
            SKYLIB_ASSERT_SOME(actor_base);
        }

        size_t Count()
        {
            return leveleds.size();
        }

        void Push(some<Leveled_Actor_Base_t*> leveled_actor_base)
        {
            if (!leveleds.Has(leveled_actor_base)) {
                leveleds.push_back(leveled_actor_base);
            }
        }

        Bool_t operator==(const Actor_Base_Leveleds_t& other)
        {
            SKYLIB_ASSERT_SOME(other.actor_base);
            return actor_base == other.actor_base;
        }

        Bool_t operator==(const some<Actor_Base_t*> other)
        {
            SKYLIB_ASSERT_SOME(other);
            return actor_base == other;
        }

        some<Leveled_Actor_Base_t*>& operator[](some<Index_t> index)
        {
            SKYLIB_ASSERT_SOME(index && index() < Count());
            return leveleds[index()];
        }
    };

}
