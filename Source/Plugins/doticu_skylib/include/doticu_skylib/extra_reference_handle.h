/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Actor_t;
    class Actor_Base_t;
    class Container_t;
    class Reference_t;

    class Extra_Reference_Handle_t :    // ExtraReferenceHandle
        public Extra_Data_t             // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::REFERENCE_HANDLE,
        };

    public:
        class Offset_e : public Enum_t<Word_t>
        {
        public:
            enum : value_type
            {
                V_TABLE = 0x0152C160, // 229549
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Reference_Handle_t*>  Create(Reference_Handle_t reference_handle);
        static some<Extra_Reference_Handle_t*>  Create(some<Reference_t*> reference);
        static void                             Destroy(some<Extra_Reference_Handle_t*> x_reference_handle);

    public:
        virtual ~Extra_Reference_Handle_t(); // 0

    public:
        Reference_Handle_t  reference_handle;   // 10
        u32                 pad_14;             // 14

    public:
        maybe<Reference_t*>     Reference();
        void                    Reference(some<Reference_t*> reference);
        maybe<Reference_t*>     Representative_Reference();
        maybe<Reference_t*>     Containing_Reference();

        Bool_t                  Is_Representative_Reference();  // I've only seen these on container_changes' entries' x_lists.
        Bool_t                  Is_Containing_Reference();      // I've only seen these on non-container references' x_lists.

        maybe<Actor_t*>         As_Actor();
        maybe<Actor_Base_t*>    As_Actor_Base();
        maybe<Container_t*>     As_Container();

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Reference_Handle_t) == 0x18);

}
