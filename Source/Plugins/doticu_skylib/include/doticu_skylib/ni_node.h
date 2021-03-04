/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"

#include "doticu_skylib/ni_3d.h"

namespace doticu_skylib {

    class NI_Node_t :   // NiNode
        public NI_3D_t  // 00
    {
    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                RTTI = 0x01E149C8, // 684841
            };
            using Enum_t::Enum_t;
        };

    public:
        virtual ~NI_Node_t(); // 00

    public:
        Short_Array_t<maybe<NI_3D_t*>> children; // 110

    public:
        Vector_t<some<NI_3D_t*>>    Children();
        void                        Children(Vector_t<some<NI_3D_t*>>& results);
    };
    STATIC_ASSERT(sizeof(NI_Node_t) == 0x128);

}
