/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/package_value.h"

namespace doticu_skylib {

    class Dialogue_Topic_t;

    class Package_Value_Topic_t :   // BGSPackageDataTopic
        public Package_Value_t      // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E24310, // 514020
            };

        public:
            using Enum_t::Enum_t;
        };

        union Value_u
        {
            maybe<Dialogue_Topic_t*>    topic;
            u32                         sub_type;

        public:
            Value_u() :
                topic(none<Dialogue_Topic_t*>())
            {
            }

            ~Value_u()
            {
                this->topic = none<Dialogue_Topic_t*>();
            }
        };
        STATIC_ASSERT(sizeof(Value_u) == 0x8);

    public:
        virtual ~Package_Value_Topic_t(); // 0

    public:
        u64     pad_08;         // 08
        Bool_t  is_sub_type;    // 10
        u8      pad_11;         // 11
        u16     pad_12;         // 12
        u32     pad_14;         // 14
        Value_u value;          // 18

    public:
        maybe<Dialogue_Topic_t*>    Topic() const;
        void                        Topic(maybe<Dialogue_Topic_t*> value);
        u32                         Sub_Type() const;
        void                        Sub_Type(u32 value);

    public:
        operator    maybe<Dialogue_Topic_t*>() const;
        operator    u32() const;

    public:
        Package_Value_Topic_t&  operator =(maybe<Dialogue_Topic_t*> value);
        Package_Value_Topic_t&  operator =(u32 value);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Value_Topic_t) == 0x20);

}
