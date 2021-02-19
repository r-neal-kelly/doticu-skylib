/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/reference.h"
#include "doticu_skylib/reference_interaction.h"

namespace doticu_skylib {

    maybe<Reference_t*> Reference_Interaction_t::Interactor_A()
    {
        return Reference_t::From_Handle(this->interactor_handle_a);
    }

    maybe<Reference_t*> Reference_Interaction_t::Interactor_B()
    {
        return Reference_t::From_Handle(this->interactor_handle_b);
    }

}
