/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/enum_dialogue_response_flags.h"
#include "doticu_skylib/enum_emotion_type.h"

namespace doticu_skylib {

    class Dialogue_Topic_t;

    class Dialogue_Response_t // ResponseData
    {
    public:
        Emotion_Type_e              emotion_type;       // 00
        u16                         emotion_percent;    // 04
        u16                         pad_06;             // 06
        Dialogue_Topic_t*           unk_08;             // 08
        u8                          response_index;     // 10
        u8                          pad_11;             // 11
        u16                         pad_12;             // 12
        u32                         pad_14;             // 14
        void*                       voice;              // 18
        Dialogue_Response_Flags_e   response_flags;     // 20
        u8                          pad_21;             // 21
        u16                         pad_22;             // 22
        u32                         pad_24;             // 24
        String_t                    response_text;      // 28
        void*                       speaker_idle;       // 30
        void*                       listener_idle;      // 38
        Dialogue_Response_t*        next;               // 40
    };
    STATIC_ASSERT(sizeof(Dialogue_Response_t) == 0x48);

}
