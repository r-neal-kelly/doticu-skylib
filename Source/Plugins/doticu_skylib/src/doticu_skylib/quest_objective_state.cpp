/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/quest_objective_state.h"

namespace doticu_skylib {

    const char* Quest_Objective_State_e::To_String(Quest_Objective_State_e quest_objective_state_e)
    {
        switch (quest_objective_state_e) {
            case (Quest_Objective_State_e::DORMANT):                    return "DORMANT";
            case (Quest_Objective_State_e::DISPLAYED):                  return "DISPLAYED";
            case (Quest_Objective_State_e::COMPLETED):                  return "COMPLETED";
            case (Quest_Objective_State_e::COMPLETED_AND_DISPLAYED):    return "COMPLETED_AND_DISPLAYED";
            case (Quest_Objective_State_e::FAILED):                     return "FAILED";
            case (Quest_Objective_State_e::FAILED_AND_DISPLAYED):       return "FAILED_AND_DISPLAYED";
            default:                                                    return "NONE";
        }
    }

}
