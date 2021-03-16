/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/form_id.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Actor_t;
    class Reference_t;

    class Extra_Unique_ID_t :   // ExtraUniqueID
        public Extra_Data_t     // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::UNIQUE_ID,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152CBA0, // 229631
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_Unique_ID_t*> Create();
        static some<Extra_Unique_ID_t*> Create(Form_ID_t form_id, u16 unique_id);
        static some<Extra_Unique_ID_t*> Create(const Extra_Unique_ID_t& other); // maybe delete
        static void                     Destroy(some<Extra_Unique_ID_t*> x_unique_id);

    public:
        virtual ~Extra_Unique_ID_t(); // 0

    public:
        Form_ID_t   form_id;    // 10 (must be a reference based on a component container)
        u16         unique_id;  // 14
        u16         pad_16;     // 16

    public:
        Form_ID_t           Form_ID() const;
        void                Form_ID(Form_ID_t form_id);
        u16                 Unique_ID() const;
        void                Unique_ID(u16 unique_id);
        maybe<Form_t*>      Form() const;
        void                Form(maybe<Form_t*> form);
        maybe<Reference_t*> Reference() const;
        void                Reference(maybe<Reference_t*> reference);
        maybe<Actor_t*>     Actor() const;
        void                Actor(maybe<Actor_t*> actor);

    public:
        void Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Extra_Unique_ID_t) == 0x18);

}
