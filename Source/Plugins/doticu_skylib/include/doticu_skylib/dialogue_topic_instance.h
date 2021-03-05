/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Dialogue_Info_t;
    class Dialogue_Response_Instance_t;
    class Dialogue_Topic_t;
    class Quest_t;

    class Dialogue_Topic_Instance_t // Dialogue
    {
    public:
        Dynamic_String_t                                        topic_text;         // 00
        Bool_t                                                  unk_10;             // 10
        Bool_t                                                  unk_11;             // 11
        Bool_t                                                  unk_12;             // 12
        u8                                                      unk_13;             // 13
        u32                                                     unk_14;             // 14
        List_t<maybe<Dialogue_Response_Instance_t*>>            response_instances; // 18
        maybe<Quest_t*>                                         quest;              // 28
        maybe<Dialogue_Info_t*>                                 info;               // 30
        maybe<Dialogue_Topic_t*>                                topic;              // 38
        maybe<List_t<maybe<Dialogue_Response_Instance_t*>>*>    unk_40;             // 40
        u8                                                      unk_48;             // 48
        Bool_t                                                  has_not_been_said;  // 49
        u16                                                     unk_4A;             // 4A
        u32                                                     unk_4C;             // 4C
        maybe<Dialogue_Topic_t*>                                unk_50;             // 50
    };
    STATIC_ASSERT(sizeof(Dialogue_Topic_Instance_t) == 0x58);

}
