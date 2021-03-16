/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Quest_t;

    class Extra_From_Alias_t :  // ExtraFromAlias
        public Extra_Data_t     // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::FROM_ALIAS,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152BEC0, // 229528
            };
            using Enum_t::Enum_t;
        };

    public:
        static some<Extra_From_Alias_t*>    Create();
        static some<Extra_From_Alias_t*>    Create(maybe<Quest_t*> quest, Alias_ID_t alias_id);
        static some<Extra_From_Alias_t*>    Create(const Extra_From_Alias_t& other);
        static void                         Destroy(some<Extra_From_Alias_t*> x_from_alias);

    public:
        virtual ~Extra_From_Alias_t(); // 0

    public:
        maybe<Quest_t*> quest;      // 10
        Alias_ID_t      alias_id;   // 18
        u32             pad_1C;     // 1C

    public:
        maybe<Quest_t*> Quest() const;
        void            Quest(maybe<Quest_t*> quest);
        Alias_ID_t      Alias_ID() const;
        void            Alias_ID(Alias_ID_t alias_id);

    public:
        void Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Extra_From_Alias_t) == 0x20);

}
