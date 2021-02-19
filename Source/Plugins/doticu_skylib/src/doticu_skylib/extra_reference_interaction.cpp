/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_reference_interaction.h"
#include "doticu_skylib/reference_interaction.h"

namespace doticu_skylib {

    maybe<Reference_t*> Extra_Reference_Interaction_t::Interactor_A()
    {
        if (this->reference_interaction) {
            return this->reference_interaction->Interactor_A();
        } else {
            return none<Reference_t*>();
        }
    }

    maybe<Reference_t*> Extra_Reference_Interaction_t::Interactor_B()
    {
        if (this->reference_interaction) {
            return this->reference_interaction->Interactor_B();
        } else {
            return none<Reference_t*>();
        }
    }

}
