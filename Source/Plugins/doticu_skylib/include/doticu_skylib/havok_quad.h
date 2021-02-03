/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

namespace doticu_skylib {

    class alignas(0x10) Havok_Quad_t // hkVector4
    {
    public:
        __m128 xyzw;
    };
    STATIC_ASSERT(sizeof(Havok_Quad_t) == 0x10);

}
