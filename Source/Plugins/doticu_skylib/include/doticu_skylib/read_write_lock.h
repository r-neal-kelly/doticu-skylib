/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Read_Write_Lock_t
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                LOCK_TO_READ        = 0x00C072D0, // 66976
                UNLOCK_TO_READ      = 0x00C07590, // 66982
                LOCK_TO_WRITE       = 0x00C07350, // 66977
                UNLOCK_TO_WRITE     = 0x00C075A0, // 66983
            };

        public:
            using Enum_t::Enum_t;
        };

        class Mask_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                INFO_LOCK_COUNT_MASK    = 0x0FFFFFFF,
                INFO_IS_WRITING_MASK    = 0x80000000,
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        volatile u32    write_thread;   // 0
        volatile u32    info;           // 4

    public:
        Read_Write_Lock_t();
        Read_Write_Lock_t(const Read_Write_Lock_t& other) = delete;
        Read_Write_Lock_t(Read_Write_Lock_t&& other) noexcept;
        Read_Write_Lock_t& operator =(const Read_Write_Lock_t& other) = delete;
        Read_Write_Lock_t& operator =(Read_Write_Lock_t&& other) noexcept;
        ~Read_Write_Lock_t();

    public:
        void Lock_To_Read();
        void Unlock_To_Read();

        void Lock_To_Write();
        void Unlock_To_Write();
    };

    class Locker_i
    {
    public:
    };

    class Read_Locker_t :
        public Locker_i
    {
    private:
        some<Read_Write_Lock_t*>    lock;

    public:
        Read_Locker_t() = delete;
        Read_Locker_t(Read_Write_Lock_t& lock);
        Read_Locker_t(some<Read_Write_Lock_t*> lock);
        Read_Locker_t(const Read_Locker_t& other) = delete;
        Read_Locker_t(Read_Locker_t&& other) noexcept;
        Read_Locker_t& operator =(const Read_Locker_t& other) = delete;
        Read_Locker_t& operator =(Read_Locker_t&& other) noexcept;
        ~Read_Locker_t();
    };

    class Write_Locker_t :
        public Locker_i
    {
    private:
        some<Read_Write_Lock_t*>    lock;

    public:
        Write_Locker_t() = delete;
        Write_Locker_t(Read_Write_Lock_t& lock);
        Write_Locker_t(some<Read_Write_Lock_t*> lock);
        Write_Locker_t(const Write_Locker_t& other) = delete;
        Write_Locker_t(Write_Locker_t&& other) noexcept;
        Write_Locker_t& operator =(const Write_Locker_t& other) = delete;
        Write_Locker_t& operator =(Write_Locker_t&& other) noexcept;
        ~Write_Locker_t();
    };

}
