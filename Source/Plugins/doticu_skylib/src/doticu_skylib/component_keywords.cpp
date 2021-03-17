/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/component_keywords.h"

namespace doticu_skylib {

    Bool_t Keywords_c::Component_Has_Keyword(some<Keyword_t*> keyword) const
    {
        SKYLIB_ASSERT_SOME(keyword);

        return Get_Has_Keyword(keyword());
    }

}
