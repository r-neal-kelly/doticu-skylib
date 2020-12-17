/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/read_write_lock.h"

namespace doticu_skylib {

    Read_Write_Lock_t::Read_Write_Lock_t() :
        thread(0), lock(0)
    {
    }

    void Read_Write_Lock_t::Lock_For_Read()
    {
        static auto self = reinterpret_cast
            <void(*)(Read_Write_Lock_t*)>
            (Game_t::Base_Address() + Read_Write_Lock_t::Offset_e::LOCK_FOR_READ);

        self(this);
    }

    void Read_Write_Lock_t::Unlock_For_Read()
    {
        static auto self = reinterpret_cast
            <void(*)(Read_Write_Lock_t*)>
            (Game_t::Base_Address() + Read_Write_Lock_t::Offset_e::UNLOCK_FOR_READ);

        self(this);
    }

    void Read_Write_Lock_t::Lock_For_Write()
    {
        static auto self = reinterpret_cast
            <void(*)(Read_Write_Lock_t*)>
            (Game_t::Base_Address() + Read_Write_Lock_t::Offset_e::LOCK_FOR_WRITE);

        self(this);
    }

    void Read_Write_Lock_t::Unlock_For_Write()
    {
        static auto self = reinterpret_cast
            <void(*)(Read_Write_Lock_t*)>
            (Game_t::Base_Address() + Read_Write_Lock_t::Offset_e::UNLOCK_FOR_WRITE);

        self(this);
    }

    Read_Locker_t::Read_Locker_t(Read_Write_Lock_t& lock) :
        lock(lock)
    {
        lock.Lock_For_Read();
    }

    Read_Locker_t::~Read_Locker_t()
    {
        lock.Unlock_For_Read();
    }

    Write_Locker_t::Write_Locker_t(Read_Write_Lock_t& lock) :
        lock(lock)
    {
        lock.Lock_For_Write();
    }

    Write_Locker_t::~Write_Locker_t()
    {
        lock.Unlock_For_Write();
    }

}
