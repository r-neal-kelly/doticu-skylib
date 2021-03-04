/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/ni_matrix.h"

namespace doticu_skylib {

    void NI_Matrix_3_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "NI_Matrix_3_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "[ %16.8f, %16.8f, %16.8f ]",
                   this->matrix[0][0], this->matrix[0][1], this->matrix[0][2]);
        SKYLIB_LOG(indent + SKYLIB_TAB + "[ %16.8f, %16.8f, %16.8f ]",
                   this->matrix[1][0], this->matrix[1][1], this->matrix[1][2]);
        SKYLIB_LOG(indent + SKYLIB_TAB + "[ %16.8f, %16.8f, %16.8f ]",
                   this->matrix[2][0], this->matrix[2][1], this->matrix[2][2]);

        SKYLIB_LOG(indent + "}");
    }

}
