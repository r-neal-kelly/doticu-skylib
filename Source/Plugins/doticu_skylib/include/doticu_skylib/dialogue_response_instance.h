/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/enum_emotion_type.h"

namespace doticu_skylib {

    class Dialogue_Response_Instance_t // DialogueResponse
    {
    public:
        Dynamic_String_t    unk_00;             // 00
        Emotion_Type_e      emotion_type;       // 10
        u16                 emotion_percent;    // 14
        u16                 pad_16;             // 16
        String_t            response_text;      // 18
        void*               speaker_idle;       // 20
        void*               listener_idle;      // 28
        void*               voice;              // 30
        Bool_t              has_emotion;        // 38
        Bool_t              has_lip_file;       // 39
        u16                 pad_3A;             // 3A
        u32                 pad_3C;             // 3C
    };
    STATIC_ASSERT(sizeof(Dialogue_Response_Instance_t) == 0x40);

}
