/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/collections.h"
#include "doticu_skylib/dynamic_array.h"
#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/read_write_lock.h"

namespace doticu_skylib {

    class Alias_Base_t;
    class Alias_Reference_t;
    class Package_t;
    class Quest_t;

    class Extra_Aliases_t : // ExtraAliasInstanceArray
        public Extra_Data_t // 00
    {
    public:
        enum
        {
            EXTRA_TYPE = Extra_Type_e::ALIASES,
        };

    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                V_TABLE = 0x0152C9A0, // 229615
            };
            using Enum_t::Enum_t;
        };

    public:
        class Instance_t // BGSRefAliasInstanceData
        {
        public:
            maybe<Quest_t*>             quest;      // 00
            maybe<Alias_Base_t*>        alias_base; // 08
            maybe<Array_t<Package_t*>*> packages;   // 10

        public:
            void Log(std::string indent = "");
        };
        STATIC_ASSERT(sizeof(Instance_t) == 0x18);

    public:
        virtual ~Extra_Aliases_t(); // 0

    public:
        Array_t<maybe<Instance_t*>> instances;  // 10
        mutable Read_Write_Lock_t   lock;       // 28

    public:
        Bool_t                              Is_Aliased();
        Bool_t                              Is_Aliased(some<Quest_t*> quest);
        Bool_t                              Is_Aliased(some<Quest_t*> quest, Alias_ID_t alias_id);
        Bool_t                              Is_Protected();
        Bool_t                              Is_Essential();
        Bool_t                              Is_Quest_Item() const;

        Vector_t<some<Alias_Base_t*>>       Alias_Bases();
        void                                Alias_Bases(Vector_t<some<Alias_Base_t*>>& results);
        Vector_t<some<Alias_Reference_t*>>  Alias_References();
        void                                Alias_References(Vector_t<some<Alias_Reference_t*>>& results);
        Vector_t<some<Quest_t*>>            Quests();
        void                                Quests(Vector_t<some<Quest_t*>>& results);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Extra_Aliases_t) == 0x30);

}
