/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/form_owner.h"

namespace doticu_skylib {

    class Extra_Owner_t :   // ExtraOwnership
        public Extra_Data_t // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::OWNER,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152BF80, // 229534
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Owner_t*> Create();
        static some<Extra_Owner_t*> Create(Form_Owner_t form_owner);
        static some<Extra_Owner_t*> Create(const Extra_Owner_t& other);
        static void                 Destroy(some<Extra_Owner_t*> x_count);

    public:
        virtual ~Extra_Owner_t(); // 0

    public:
        Form_Owner_t    form_owner; // 10

    public:
        Form_Owner_t    Form_Owner();
        void            Form_Owner(Form_Owner_t form_owner);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Extra_Owner_t) == 0x18);

}
