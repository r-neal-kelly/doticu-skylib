/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/read_write_lock.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class List_x
    {
    public:
        class Presence_t
        {
        public:
            static constexpr size_t MAX_FLAGS = 192;

        public:
            static some<Presence_t*>    Create();
            static void                 Destroy(some<Presence_t*> presence);

        public:
            Byte_t flags[24]; // 0

        public:
            Presence_t();
            Presence_t(const Presence_t& other)                 = delete;
            Presence_t(Presence_t&& other) noexcept             = delete;
            Presence_t& operator=(const Presence_t & other)     = delete;
            Presence_t& operator=(Presence_t&& other) noexcept  = delete;
            ~Presence_t();

        public:
            Bool_t  Has(Extra_Type_e type);
            void    Add(Extra_Type_e type);
            void    Remove(Extra_Type_e type);
            void    Clear();
        };
        STATIC_ASSERT(sizeof(Presence_t) == 0x18);

    public:
        static some<List_x*>    Create();
        static void             Destroy(some<List_x*> x_list);

    public:
        maybe<Data_x*>      x_datas;    // 00
        maybe<Presence_t*>  presence;   // 08
        Read_Write_Lock_t   lock;       // 10

    public:
        List_x();
        List_x(const List_x& other)                 = delete;
        List_x(List_x&& other) noexcept             = delete;
        List_x& operator=(const List_x& other)      = delete;
        List_x& operator=(List_x&& other) noexcept  = delete;
        ~List_x();

    public:
        void            Validate();

        Bool_t          Has(Extra_Type_e type);
        maybe<Data_x*>  Get(Extra_Type_e type);
        Bool_t          Add(some<Data_x*> x_data);
        Bool_t          Remove(some<Data_x*> x_data);

        template <typename Extra_t>
        Bool_t          Has();
        template <typename Extra_t>
        maybe<Extra_t*> Get();
        template <typename Extra_t>
        Bool_t          Add(some<Extra_t*> extra);
        template <typename Extra_t>
        Bool_t          Remove(some<Extra_t*> extra);
    };
    STATIC_ASSERT(sizeof(List_x) == 0x18);

}
