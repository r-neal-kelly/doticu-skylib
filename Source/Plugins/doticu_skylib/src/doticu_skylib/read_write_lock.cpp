/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/atomic.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/read_write_lock.h"

namespace doticu_skylib {

    // Any number of Lock_To_Reads can be called in succession, as long as Unlock_To_Read is called for each.
    // The same goes for Lock_To_Write and Unlock_To_Write.
    // On the same thread, Lock_To_Read can be called any number of times after Lock_To_Write.
    // On the same thread, calling Lock_To_Write after calling Lock_To_Read will deadlock the game.
    // Therefore it is simply not safe to switch from read to write on the same thread, even if you unlock read first.

    Read_Write_Lock_t::Read_Write_Lock_t()
    {
        Atomic_t::Assign(this->write_thread, 0);
        Atomic_t::Assign(this->info, 0);
    }

    Read_Write_Lock_t::Read_Write_Lock_t(Read_Write_Lock_t&& other) noexcept
    {
        Atomic_t::Assign(this->write_thread, Atomic_t::Exchange_Assign(other.write_thread, 0));
        Atomic_t::Assign(this->info, Atomic_t::Exchange_Assign(other.info, 0));
    }

    Read_Write_Lock_t& Read_Write_Lock_t::operator =(Read_Write_Lock_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            Atomic_t::Assign(this->write_thread, Atomic_t::Exchange_Assign(other.write_thread, 0));
            Atomic_t::Assign(this->info, Atomic_t::Exchange_Assign(other.info, 0));
        }
        return *this;
    }

    Read_Write_Lock_t::~Read_Write_Lock_t()
    {
        Atomic_t::Assign(this->write_thread, 0);
        Atomic_t::Assign(this->info, 0);
    }

    void Read_Write_Lock_t::Lock_To_Read()
    {
        static auto lock_to_read = reinterpret_cast
            <void(*)(Read_Write_Lock_t*)>
            (Game_t::Base_Address() + Read_Write_Lock_t::Offset_e::LOCK_TO_READ);

        lock_to_read(this);
    }

    void Read_Write_Lock_t::Unlock_To_Read()
    {
        static auto unlock_to_read = reinterpret_cast
            <void(*)(Read_Write_Lock_t*)>
            (Game_t::Base_Address() + Read_Write_Lock_t::Offset_e::UNLOCK_TO_READ);

        unlock_to_read(this);
    }

    void Read_Write_Lock_t::Lock_To_Write()
    {
        static auto lock_to_write = reinterpret_cast
            <void(*)(Read_Write_Lock_t*)>
            (Game_t::Base_Address() + Read_Write_Lock_t::Offset_e::LOCK_TO_WRITE);

        lock_to_write(this);
    }

    void Read_Write_Lock_t::Unlock_To_Write()
    {
        static auto unlock_to_write = reinterpret_cast
            <void(*)(Read_Write_Lock_t*)>
            (Game_t::Base_Address() + Read_Write_Lock_t::Offset_e::UNLOCK_TO_WRITE);

        unlock_to_write(this);
    }

    Read_Locker_t::Read_Locker_t(Read_Write_Lock_t& lock) :
        lock(&lock)
    {
        this->lock->Lock_To_Read();
    }

    Read_Locker_t::Read_Locker_t(some<Read_Write_Lock_t*> lock) :
        lock((SKYLIB_ASSERT_SOME(lock), lock))
    {
        this->lock->Lock_To_Read();
    }

    Read_Locker_t::Read_Locker_t(Read_Locker_t&& other) noexcept :
        lock(std::move(other.lock))
    {
    }

    Read_Locker_t& Read_Locker_t::operator =(Read_Locker_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->lock = std::move(other.lock);
        }
        return *this;
    }

    Read_Locker_t::~Read_Locker_t()
    {
        if (this->lock) {
            this->lock->Unlock_To_Read();
        }
    }

    Write_Locker_t::Write_Locker_t(Read_Write_Lock_t& lock) :
        lock(&lock)
    {
        this->lock->Lock_To_Write();
    }

    Write_Locker_t::Write_Locker_t(some<Read_Write_Lock_t*> lock) :
        lock((SKYLIB_ASSERT_SOME(lock), lock))
    {
        this->lock->Lock_To_Write();
    }

    Write_Locker_t::Write_Locker_t(Write_Locker_t&& other) noexcept :
        lock(std::move(other.lock))
    {
    }

    Write_Locker_t& Write_Locker_t::operator =(Write_Locker_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->lock = std::move(other.lock);
        }
        return *this;
    }

    Write_Locker_t::~Write_Locker_t()
    {
        if (this->lock) {
            this->lock->Unlock_To_Write();
        }
    }

}
