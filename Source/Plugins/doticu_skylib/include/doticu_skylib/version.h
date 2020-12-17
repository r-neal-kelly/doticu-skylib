/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/math.h"

namespace doticu_skylib {

    template <typename Type_t>
    class Version_t
    {
    public:
        Type_t major;
        Type_t minor;
        Type_t patch;
        Type_t build;

        Version_t(Type_t major = 0, Type_t minor = 0, Type_t patch = 0, Type_t build = 0) :
            major(major), minor(minor), patch(patch), build(build)
        {
        }

        Bool_t operator==(const Version_t<Type_t>& other) const
        {
            return
                major == other.major &&
                minor == other.minor &&
                patch == other.patch &&
                build == other.build;
        }

        Bool_t operator<(const Version_t<Type_t>& other) const
        {
            if (major != other.major) {
                return major < other.major;
            } else if (minor != other.minor) {
                return minor < other.minor;
            } else if (patch != other.patch) {
                return patch < other.patch;
            } else if (build != other.build) {
                return build < other.build;
            } else {
                return false;
            }
        }

        Bool_t operator>(const Version_t<Type_t>& other) const
        {
            return other < *this;
        }
    };

}
