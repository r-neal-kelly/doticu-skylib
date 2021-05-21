/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor_base.h"
#include "doticu_skylib/association.h"
#include "doticu_skylib/relation.h"

namespace doticu_skylib {

    maybe<String_t> Relation_t::Association_String(some<Actor_Base_t*> actor_base) const
    {
        SKYLIB_ASSERT_SOME(actor_base);

        if (this->association) {
            if (this->parent == actor_base) {
                if (actor_base->Is_Female()) {
                    return this->association->female_parent;
                } else {
                    return this->association->male_parent;
                }
            } else if (this->child == actor_base) {
                if (actor_base->Is_Female()) {
                    return this->association->female_child;
                } else {
                    return this->association->male_child;
                }
            } else {
                return none<String_t>();
            }
        } else {
            return none<String_t>();
        }
    }

}
