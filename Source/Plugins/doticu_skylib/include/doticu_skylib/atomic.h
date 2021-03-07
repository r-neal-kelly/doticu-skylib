/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"

namespace doticu_skylib {

    class Atomic_t
    {
    public:
        static void*    Exchange_Assign(volatile void*& a, void* b);
        static u8       Exchange_Assign(volatile u8& a, u8 b);
        static u16      Exchange_Assign(volatile u16& a, u16 b);
        static u32      Exchange_Assign(volatile u32& a, u32 b);
        static u64      Exchange_Assign(volatile u64& a, u64 b);
        static s8       Exchange_Assign(volatile s8& a, s8 b);
        static s16      Exchange_Assign(volatile s16& a, s16 b);
        static s32      Exchange_Assign(volatile s32& a, s32 b);
        static s64      Exchange_Assign(volatile s64& a, s64 b);

        static u8       Exchange_Add(volatile u8& a, u8 b);
        static u16      Exchange_Add(volatile u16& a, u16 b);
        static u32      Exchange_Add(volatile u32& a, u32 b);
        static u64      Exchange_Add(volatile u64& a, u64 b);
        static s8       Exchange_Add(volatile s8& a, s8 b);
        static s16      Exchange_Add(volatile s16& a, s16 b);
        static s32      Exchange_Add(volatile s32& a, s32 b);
        static s64      Exchange_Add(volatile s64& a, s64 b);

        static u8       Exchange_Subtract(volatile u8& a, u8 b);
        static u16      Exchange_Subtract(volatile u16& a, u16 b);
        static u32      Exchange_Subtract(volatile u32& a, u32 b);
        static u64      Exchange_Subtract(volatile u64& a, u64 b);
        static s8       Exchange_Subtract(volatile s8& a, s8 b);
        static s16      Exchange_Subtract(volatile s16& a, s16 b);
        static s32      Exchange_Subtract(volatile s32& a, s32 b);
        static s64      Exchange_Subtract(volatile s64& a, s64 b);

        static u8       Exchange_Or(volatile u8& a, u8 b);
        static u16      Exchange_Or(volatile u16& a, u16 b);
        static u32      Exchange_Or(volatile u32& a, u32 b);
        static u64      Exchange_Or(volatile u64& a, u64 b);
        static s8       Exchange_Or(volatile s8& a, s8 b);
        static s16      Exchange_Or(volatile s16& a, s16 b);
        static s32      Exchange_Or(volatile s32& a, s32 b);
        static s64      Exchange_Or(volatile s64& a, s64 b);

        static u8       Exchange_And(volatile u8& a, u8 b);
        static u16      Exchange_And(volatile u16& a, u16 b);
        static u32      Exchange_And(volatile u32& a, u32 b);
        static u64      Exchange_And(volatile u64& a, u64 b);
        static s8       Exchange_And(volatile s8& a, s8 b);
        static s16      Exchange_And(volatile s16& a, s16 b);
        static s32      Exchange_And(volatile s32& a, s32 b);
        static s64      Exchange_And(volatile s64& a, s64 b);

        static u8       Exchange_Xor(volatile u8& a, u8 b);
        static u16      Exchange_Xor(volatile u16& a, u16 b);
        static u32      Exchange_Xor(volatile u32& a, u32 b);
        static u64      Exchange_Xor(volatile u64& a, u64 b);
        static s8       Exchange_Xor(volatile s8& a, s8 b);
        static s16      Exchange_Xor(volatile s16& a, s16 b);
        static s32      Exchange_Xor(volatile s32& a, s32 b);
        static s64      Exchange_Xor(volatile s64& a, s64 b);

        static void*    Exchange_Assign_If_Equals(volatile void*& a, void* b, void* c);
        static u8       Exchange_Assign_If_Equals(volatile u8& a, u8 b, u8 c);
        static u16      Exchange_Assign_If_Equals(volatile u16& a, u16 b, u16 c);
        static u32      Exchange_Assign_If_Equals(volatile u32& a, u32 b, u32 c);
        static u64      Exchange_Assign_If_Equals(volatile u64& a, u64 b, u64 c);
        static s8       Exchange_Assign_If_Equals(volatile s8& a, s8 b, s8 c);
        static s16      Exchange_Assign_If_Equals(volatile s16& a, s16 b, s16 c);
        static s32      Exchange_Assign_If_Equals(volatile s32& a, s32 b, s32 c);
        static s64      Exchange_Assign_If_Equals(volatile s64& a, s64 b, s64 c);

        static void*    Assign(volatile void*& a, void* b);
        static u8       Assign(volatile u8& a, u8 b);
        static u16      Assign(volatile u16& a, u16 b);
        static u32      Assign(volatile u32& a, u32 b);
        static u64      Assign(volatile u64& a, u64 b);
        static s8       Assign(volatile s8& a, s8 b);
        static s16      Assign(volatile s16& a, s16 b);
        static s32      Assign(volatile s32& a, s32 b);
        static s64      Assign(volatile s64& a, s64 b);

        static u8       Add(volatile u8& a, u8 b);
        static u16      Add(volatile u16& a, u16 b);
        static u32      Add(volatile u32& a, u32 b);
        static u64      Add(volatile u64& a, u64 b);
        static s8       Add(volatile s8& a, s8 b);
        static s16      Add(volatile s16& a, s16 b);
        static s32      Add(volatile s32& a, s32 b);
        static s64      Add(volatile s64& a, s64 b);

        static u8       Subtract(volatile u8& a, u8 b);
        static u16      Subtract(volatile u16& a, u16 b);
        static u32      Subtract(volatile u32& a, u32 b);
        static u64      Subtract(volatile u64& a, u64 b);
        static s8       Subtract(volatile s8& a, s8 b);
        static s16      Subtract(volatile s16& a, s16 b);
        static s32      Subtract(volatile s32& a, s32 b);
        static s64      Subtract(volatile s64& a, s64 b);

        static u8       Or(volatile u8& a, u8 b);
        static u16      Or(volatile u16& a, u16 b);
        static u32      Or(volatile u32& a, u32 b);
        static u64      Or(volatile u64& a, u64 b);
        static s8       Or(volatile s8& a, s8 b);
        static s16      Or(volatile s16& a, s16 b);
        static s32      Or(volatile s32& a, s32 b);
        static s64      Or(volatile s64& a, s64 b);

        static u8       And(volatile u8& a, u8 b);
        static u16      And(volatile u16& a, u16 b);
        static u32      And(volatile u32& a, u32 b);
        static u64      And(volatile u64& a, u64 b);
        static s8       And(volatile s8& a, s8 b);
        static s16      And(volatile s16& a, s16 b);
        static s32      And(volatile s32& a, s32 b);
        static s64      And(volatile s64& a, s64 b);

        static u8       Xor(volatile u8& a, u8 b);
        static u16      Xor(volatile u16& a, u16 b);
        static u32      Xor(volatile u32& a, u32 b);
        static u64      Xor(volatile u64& a, u64 b);
        static s8       Xor(volatile s8& a, s8 b);
        static s16      Xor(volatile s16& a, s16 b);
        static s32      Xor(volatile s32& a, s32 b);
        static s64      Xor(volatile s64& a, s64 b);

        static void*    Access(const volatile void*& a);
        static u8       Access(const volatile u8& a);
        static u16      Access(const volatile u16& a);
        static u32      Access(const volatile u32& a);
        static u64      Access(const volatile u64& a);
        static s8       Access(const volatile s8& a);
        static s16      Access(const volatile s16& a);
        static s32      Access(const volatile s32& a);
        static s64      Access(const volatile s64& a);
    };

}
