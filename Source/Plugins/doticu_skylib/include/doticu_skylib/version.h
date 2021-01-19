/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/math.h"
#include "doticu_skylib/traits.h"

namespace doticu_skylib {

    template <typename T, enable_if_unsigned_integral_t<T> = true>
    class Version_t
    {
    public:
        static const Version_t<T> From_MM_mm_pp_bb(u32 version)
        {
            static_assert(sizeof(T) >= sizeof(u8), "invalid T size");
            return Version_t<T>((version & 0xFF000000) >> 24,
                                (version & 0x00FF0000) >> 16,
                                (version & 0x0000FF00) >> 8,
                                (version & 0x000000FF) >> 0);
        }

        static const Version_t<T> From_MM_mm_ppp_b(u32 version)
        {
            static_assert(sizeof(T) >= sizeof(u16), "invalid T size");
            return Version_t<T>((version & 0xFF000000) >> 24,
                                (version & 0x00FF0000) >> 16,
                                (version & 0x0000FFF0) >> 4,
                                (version & 0x0000000F) >> 0);
        }

    public:
        T major;
        T minor;
        T patch;
        T build;

        Version_t(T major = 0, T minor = 0, T patch = 0, T build = 0) :
            major(major), minor(minor), patch(patch), build(build)
        {
        }

        Bool_t operator==(const Version_t<T>& other) const
        {
            return
                this->major == other.major &&
                this->minor == other.minor &&
                this->patch == other.patch &&
                this->build == other.build;
        }

        Bool_t operator!=(const Version_t<T>& other) const
        {
            return
                this->major != other.major ||
                this->minor != other.minor ||
                this->patch != other.patch ||
                this->build != other.build;
        }

        Bool_t operator<(const Version_t<T>& other) const
        {
            return
                this->major < other.major ||
                this->minor < other.minor ||
                this->patch < other.patch ||
                this->build < other.build;
        }

        Bool_t operator>(const Version_t<T>& other) const
        {
            return
                this->major > other.major ||
                this->minor > other.minor ||
                this->patch > other.patch ||
                this->build > other.build;
        }

        Bool_t operator<=(const Version_t<T>& other) const
        {
            return
                this->major <= other.major &&
                this->minor <= other.minor &&
                this->patch <= other.patch &&
                this->build <= other.build;
        }

        Bool_t operator>=(const Version_t<T>& other) const
        {
            return
                this->major >= other.major &&
                this->minor >= other.minor &&
                this->patch >= other.patch &&
                this->build >= other.build;
        }

        template <typename TT>
        operator Version_t<TT>() const
        {
            return Version_t<TT>(this->major, this->minor, this->patch, this->build);
        }
    };

}
