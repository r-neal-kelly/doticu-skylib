/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dialogue_info.h"
#include "doticu_skylib/dialogue_topic.h"

namespace doticu_skylib {

    Bool_t Dialogue_Info_t::Is_In_Branch(some<Dialogue_Branch_t*> branch)
    {
        SKYLIB_ASSERT_SOME(branch);
        return Branch() == branch;
    }

    Bool_t Dialogue_Info_t::Is_In_Quest(some<Quest_t*> quest)
    {
        SKYLIB_ASSERT_SOME(quest);
        return Quest() == quest;
    }

    Bool_t Dialogue_Info_t::Is_In_Topic(some<Dialogue_Topic_t*> topic)
    {
        SKYLIB_ASSERT_SOME(topic);
        return Topic() == topic;
    }

    maybe<Dialogue_Branch_t*> Dialogue_Info_t::Branch()
    {
        if (this->topic) {
            return this->topic->branch;
        } else {
            return nullptr;
        }
    }

    maybe<Quest_t*> Dialogue_Info_t::Quest()
    {
        if (this->topic) {
            return this->topic->quest;
        } else {
            return nullptr;
        }
    }

    maybe<Dialogue_Topic_t*> Dialogue_Info_t::Topic()
    {
        return this->topic;
    }

}
