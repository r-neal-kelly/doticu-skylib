/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe.h"

#include "doticu_skylib/read_write_lock.h"

#include "doticu_skylib/extra_data.h"

namespace doticu_skylib {

    class Actor_Base_t;
    class Faction_t;
    class Form_t;
    class Outfit_t;

    class Extra_List_t // ExtraDataList
    {
    public:
        class Presence_t // PresenceBitfield
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
        static some<Extra_List_t*>  Create();
        static void                 Destroy(some<Extra_List_t*> x_list);

    public:
        maybe<Extra_Data_t*>    x_datas;    // 00
        maybe<Presence_t*>      presence;   // 08
        Read_Write_Lock_t       lock;       // 10

    public:
        Extra_List_t();
        Extra_List_t(const Extra_List_t& other)                 = delete;
        Extra_List_t(Extra_List_t&& other) noexcept             = delete;
        Extra_List_t& operator=(const Extra_List_t& other)      = delete;
        Extra_List_t& operator=(Extra_List_t&& other) noexcept  = delete;
        ~Extra_List_t();

    public:
        void                    Validate();
        Bool_t                  Should_Be_Destroyed();
        Bool_t                  Is_Quest_Item();

    public:
        Bool_t                  Has(Extra_Type_e type);
        maybe<Extra_Data_t*>    Get(Extra_Type_e type);
        Bool_t                  Add(some<Extra_Data_t*> x_data);
        Bool_t                  Remove(some<Extra_Data_t*> x_data);

        template <typename T>
        Bool_t                  Has();
        template <typename T>
        maybe<T*>               Get();
        template <typename T>
        Bool_t                  Add(some<T*> x_data);
        template <typename T>
        Bool_t                  Remove(some<T*> x_data);

    public:
        s16                     Count();
        s16                     Increment_Count(s16 amount);
        s16                     Decrement_Count(s16 amount);

    public:
        maybe<Form_t*>          Owner();
        void                    Owner(maybe<Form_t*> form);
        maybe<Faction_t*>       Faction_Owner();
        void                    Faction_Owner(maybe<Faction_t*> faction);
        maybe<Actor_Base_t*>    Actor_Base_Owner();
        void                    Actor_Base_Owner(maybe<Actor_Base_t*> actor_base);

        maybe<Outfit_t*>        Outfit();
        void                    Outfit(maybe<Outfit_t*> outfit);

    };
    STATIC_ASSERT(sizeof(Extra_List_t) == 0x18);

}
