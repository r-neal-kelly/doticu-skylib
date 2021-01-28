/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"

namespace doticu_skylib {

    class Read_Write_Lock_t
    {
    public:
        class Offset_e : Enum_t<Word_t>
        {
        public:
            enum : Word_t
            {
                LOCK_FOR_READ       = 0x00C072D0, // 66976
                UNLOCK_FOR_READ     = 0x00C07590, // 66982
                LOCK_FOR_WRITE      = 0x00C07350, // 66977
                UNLOCK_FOR_WRITE    = 0x00C075A0, // 66983
            };
            using Enum_t::Enum_t;
        };

    public:
        volatile u32 thread;    // 0
        volatile u32 lock;      // 4

    public:
        Read_Write_Lock_t();

        void Lock_For_Read();
        void Unlock_For_Read();

        void Lock_For_Write();
        void Unlock_For_Write();
    };

    class Read_Locker_t
    {
    public:
        Read_Locker_t() = delete;
        Read_Locker_t(Read_Write_Lock_t& lock);
        Read_Locker_t(const Read_Write_Lock_t&) = delete;
        Read_Locker_t(Read_Write_Lock_t&&) noexcept = delete;
        ~Read_Locker_t();

        Read_Locker_t& operator=(const Read_Write_Lock_t&) = delete;
        Read_Locker_t& operator=(Read_Write_Lock_t&&) = delete;

    private:
        Read_Write_Lock_t& lock;
    };

    class Write_Locker_t
    {
    public:
        Write_Locker_t() = delete;
        Write_Locker_t(Read_Write_Lock_t& lock);
        Write_Locker_t(const Read_Write_Lock_t&) = delete;
        Write_Locker_t(Read_Write_Lock_t&&) noexcept = delete;
        ~Write_Locker_t();

        Write_Locker_t& operator=(const Read_Write_Lock_t&) = delete;
        Write_Locker_t& operator=(Read_Write_Lock_t&&) = delete;

    private:
        Read_Write_Lock_t& lock;
    };

}
