/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/atomic.h"

namespace doticu_skylib {

    inline void*    Atomic_t::Exchange_Assign(volatile void*& a, void* b)                       { return _InterlockedExchangePointer((void* volatile*)&a, (void*)b); }
    inline u8       Atomic_t::Exchange_Assign(volatile u8& a, u8 b)                             { return _InterlockedExchange8((volatile char*)&a, (char)b); }
    inline u16      Atomic_t::Exchange_Assign(volatile u16& a, u16 b)                           { return _InterlockedExchange16((volatile short*)&a, (short)b); }
    inline u32      Atomic_t::Exchange_Assign(volatile u32& a, u32 b)                           { return _InterlockedExchange((volatile long*)&a, (long)b); }
    inline u64      Atomic_t::Exchange_Assign(volatile u64& a, u64 b)                           { return _InterlockedExchange64((volatile long long*)&a, (long long)b); }
    inline s8       Atomic_t::Exchange_Assign(volatile s8& a, s8 b)                             { return _InterlockedExchange8((volatile char*)&a, (char)b); }
    inline s16      Atomic_t::Exchange_Assign(volatile s16& a, s16 b)                           { return _InterlockedExchange16((volatile short*)&a, (short)b); }
    inline s32      Atomic_t::Exchange_Assign(volatile s32& a, s32 b)                           { return _InterlockedExchange((volatile long*)&a, (long)b); }
    inline s64      Atomic_t::Exchange_Assign(volatile s64& a, s64 b)                           { return _InterlockedExchange64((volatile long long*)&a, (long long)b); }

    inline u8       Atomic_t::Exchange_Add(volatile u8& a, u8 b)                                { return _InterlockedExchangeAdd8((volatile char*)&a, (char)b); }
    inline u16      Atomic_t::Exchange_Add(volatile u16& a, u16 b)                              { return _InterlockedExchangeAdd16((volatile short*)&a, (short)b); }
    inline u32      Atomic_t::Exchange_Add(volatile u32& a, u32 b)                              { return _InterlockedExchangeAdd((volatile long*)&a, (long)b); }
    inline u64      Atomic_t::Exchange_Add(volatile u64& a, u64 b)                              { return _InterlockedExchangeAdd64((volatile long long*)&a, (long long)b); }
    inline s8       Atomic_t::Exchange_Add(volatile s8& a, s8 b)                                { return _InterlockedExchangeAdd8((volatile char*)&a, (char)b); }
    inline s16      Atomic_t::Exchange_Add(volatile s16& a, s16 b)                              { return _InterlockedExchangeAdd16((volatile short*)&a, (short)b); }
    inline s32      Atomic_t::Exchange_Add(volatile s32& a, s32 b)                              { return _InterlockedExchangeAdd((volatile long*)&a, (long)b); }
    inline s64      Atomic_t::Exchange_Add(volatile s64& a, s64 b)                              { return _InterlockedExchangeAdd64((volatile long long*)&a, (long long)b); }

    inline u8       Atomic_t::Exchange_Subtract(volatile u8& a, u8 b)                           { return _InterlockedExchangeAdd8((volatile char*)&a, -(char)b); }
    inline u16      Atomic_t::Exchange_Subtract(volatile u16& a, u16 b)                         { return _InterlockedExchangeAdd16((volatile short*)&a, -(short)b); }
    inline u32      Atomic_t::Exchange_Subtract(volatile u32& a, u32 b)                         { return _InterlockedExchangeAdd((volatile long*)&a, -(long)b); }
    inline u64      Atomic_t::Exchange_Subtract(volatile u64& a, u64 b)                         { return _InterlockedExchangeAdd64((volatile long long*)&a, -(long long)b); }
    inline s8       Atomic_t::Exchange_Subtract(volatile s8& a, s8 b)                           { return _InterlockedExchangeAdd8((volatile char*)&a, -(char)b); }
    inline s16      Atomic_t::Exchange_Subtract(volatile s16& a, s16 b)                         { return _InterlockedExchangeAdd16((volatile short*)&a, -(short)b); }
    inline s32      Atomic_t::Exchange_Subtract(volatile s32& a, s32 b)                         { return _InterlockedExchangeAdd((volatile long*)&a, -(long)b); }
    inline s64      Atomic_t::Exchange_Subtract(volatile s64& a, s64 b)                         { return _InterlockedExchangeAdd64((volatile long long*)&a, -(long long)b); }

    inline u8       Atomic_t::Exchange_Or(volatile u8& a, u8 b)                                 { return _InterlockedOr8((volatile char*)&a, (char)b); }
    inline u16      Atomic_t::Exchange_Or(volatile u16& a, u16 b)                               { return _InterlockedOr16((volatile short*)&a, (short)b); }
    inline u32      Atomic_t::Exchange_Or(volatile u32& a, u32 b)                               { return _InterlockedOr((volatile long*)&a, (long)b); }
    inline u64      Atomic_t::Exchange_Or(volatile u64& a, u64 b)                               { return _InterlockedOr64((volatile long long*)&a, (long long)b); }
    inline s8       Atomic_t::Exchange_Or(volatile s8& a, s8 b)                                 { return _InterlockedOr8((volatile char*)&a, (char)b); }
    inline s16      Atomic_t::Exchange_Or(volatile s16& a, s16 b)                               { return _InterlockedOr16((volatile short*)&a, (short)b); }
    inline s32      Atomic_t::Exchange_Or(volatile s32& a, s32 b)                               { return _InterlockedOr((volatile long*)&a, (long)b); }
    inline s64      Atomic_t::Exchange_Or(volatile s64& a, s64 b)                               { return _InterlockedOr64((volatile long long*)&a, (long long)b); }

    inline u8       Atomic_t::Exchange_And(volatile u8& a, u8 b)                                { return _InterlockedAnd8((volatile char*)&a, (char)b); }
    inline u16      Atomic_t::Exchange_And(volatile u16& a, u16 b)                              { return _InterlockedAnd16((volatile short*)&a, (short)b); }
    inline u32      Atomic_t::Exchange_And(volatile u32& a, u32 b)                              { return _InterlockedAnd((volatile long*)&a, (long)b); }
    inline u64      Atomic_t::Exchange_And(volatile u64& a, u64 b)                              { return _InterlockedAnd64((volatile long long*)&a, (long long)b); }
    inline s8       Atomic_t::Exchange_And(volatile s8& a, s8 b)                                { return _InterlockedAnd8((volatile char*)&a, (char)b); }
    inline s16      Atomic_t::Exchange_And(volatile s16& a, s16 b)                              { return _InterlockedAnd16((volatile short*)&a, (short)b); }
    inline s32      Atomic_t::Exchange_And(volatile s32& a, s32 b)                              { return _InterlockedAnd((volatile long*)&a, (long)b); }
    inline s64      Atomic_t::Exchange_And(volatile s64& a, s64 b)                              { return _InterlockedAnd64((volatile long long*)&a, (long long)b); }

    inline u8       Atomic_t::Exchange_Xor(volatile u8& a, u8 b)                                { return _InterlockedXor8((volatile char*)&a, (char)b); }
    inline u16      Atomic_t::Exchange_Xor(volatile u16& a, u16 b)                              { return _InterlockedXor16((volatile short*)&a, (short)b); }
    inline u32      Atomic_t::Exchange_Xor(volatile u32& a, u32 b)                              { return _InterlockedXor((volatile long*)&a, (long)b); }
    inline u64      Atomic_t::Exchange_Xor(volatile u64& a, u64 b)                              { return _InterlockedXor64((volatile long long*)&a, (long long)b); }
    inline s8       Atomic_t::Exchange_Xor(volatile s8& a, s8 b)                                { return _InterlockedXor8((volatile char*)&a, (char)b); }
    inline s16      Atomic_t::Exchange_Xor(volatile s16& a, s16 b)                              { return _InterlockedXor16((volatile short*)&a, (short)b); }
    inline s32      Atomic_t::Exchange_Xor(volatile s32& a, s32 b)                              { return _InterlockedXor((volatile long*)&a, (long)b); }
    inline s64      Atomic_t::Exchange_Xor(volatile s64& a, s64 b)                              { return _InterlockedXor64((volatile long long*)&a, (long long)b); }

    inline void*    Atomic_t::Exchange_Assign_If_Equals(volatile void*& a, void* b, void* c)    { return _InterlockedCompareExchangePointer((void* volatile*)&a, (void*)b, (void*)c); }
    inline u8       Atomic_t::Exchange_Assign_If_Equals(volatile u8& a, u8 b, u8 c)             { return _InterlockedCompareExchange8((volatile char*)&a, (char)b, (char)c); }
    inline u16      Atomic_t::Exchange_Assign_If_Equals(volatile u16& a, u16 b, u16 c)          { return _InterlockedCompareExchange16((volatile short*)&a, (short)b, (short)c); }
    inline u32      Atomic_t::Exchange_Assign_If_Equals(volatile u32& a, u32 b, u32 c)          { return _InterlockedCompareExchange((volatile long*)&a, (long)b, (long)c); }
    inline u64      Atomic_t::Exchange_Assign_If_Equals(volatile u64& a, u64 b, u64 c)          { return _InterlockedCompareExchange64((volatile long long*)&a, (long long)b, (long long)c); }
    inline s8       Atomic_t::Exchange_Assign_If_Equals(volatile s8& a, s8 b, s8 c)             { return _InterlockedCompareExchange8((volatile char*)&a, (char)b, (char)c); }
    inline s16      Atomic_t::Exchange_Assign_If_Equals(volatile s16& a, s16 b, s16 c)          { return _InterlockedCompareExchange16((volatile short*)&a, (short)b, (short)c); }
    inline s32      Atomic_t::Exchange_Assign_If_Equals(volatile s32& a, s32 b, s32 c)          { return _InterlockedCompareExchange((volatile long*)&a, (long)b, (long)c); }
    inline s64      Atomic_t::Exchange_Assign_If_Equals(volatile s64& a, s64 b, s64 c)          { return _InterlockedCompareExchange64((volatile long long*)&a, (long long)b, (long long)c); }

    inline void*    Atomic_t::Assign(volatile void*& a, void* b)                                { return Exchange_Assign(a, b), b; }
    inline u8       Atomic_t::Assign(volatile u8& a, u8 b)                                      { return Exchange_Assign(a, b), b; }
    inline u16      Atomic_t::Assign(volatile u16& a, u16 b)                                    { return Exchange_Assign(a, b), b; }
    inline u32      Atomic_t::Assign(volatile u32& a, u32 b)                                    { return Exchange_Assign(a, b), b; }
    inline u64      Atomic_t::Assign(volatile u64& a, u64 b)                                    { return Exchange_Assign(a, b), b; }
    inline s8       Atomic_t::Assign(volatile s8& a, s8 b)                                      { return Exchange_Assign(a, b), b; }
    inline s16      Atomic_t::Assign(volatile s16& a, s16 b)                                    { return Exchange_Assign(a, b), b; }
    inline s32      Atomic_t::Assign(volatile s32& a, s32 b)                                    { return Exchange_Assign(a, b), b; }
    inline s64      Atomic_t::Assign(volatile s64& a, s64 b)                                    { return Exchange_Assign(a, b), b; }

    inline u8       Atomic_t::Add(volatile u8& a, u8 b)                                         { return Exchange_Add(a, b) + b; }
    inline u16      Atomic_t::Add(volatile u16& a, u16 b)                                       { return Exchange_Add(a, b) + b; }
    inline u32      Atomic_t::Add(volatile u32& a, u32 b)                                       { return Exchange_Add(a, b) + b; }
    inline u64      Atomic_t::Add(volatile u64& a, u64 b)                                       { return Exchange_Add(a, b) + b; }
    inline s8       Atomic_t::Add(volatile s8& a, s8 b)                                         { return Exchange_Add(a, b) + b; }
    inline s16      Atomic_t::Add(volatile s16& a, s16 b)                                       { return Exchange_Add(a, b) + b; }
    inline s32      Atomic_t::Add(volatile s32& a, s32 b)                                       { return Exchange_Add(a, b) + b; }
    inline s64      Atomic_t::Add(volatile s64& a, s64 b)                                       { return Exchange_Add(a, b) + b; }

    inline u8       Atomic_t::Subtract(volatile u8& a, u8 b)                                    { return Exchange_Subtract(a, b) - b; }
    inline u16      Atomic_t::Subtract(volatile u16& a, u16 b)                                  { return Exchange_Subtract(a, b) - b; }
    inline u32      Atomic_t::Subtract(volatile u32& a, u32 b)                                  { return Exchange_Subtract(a, b) - b; }
    inline u64      Atomic_t::Subtract(volatile u64& a, u64 b)                                  { return Exchange_Subtract(a, b) - b; }
    inline s8       Atomic_t::Subtract(volatile s8& a, s8 b)                                    { return Exchange_Subtract(a, b) - b; }
    inline s16      Atomic_t::Subtract(volatile s16& a, s16 b)                                  { return Exchange_Subtract(a, b) - b; }
    inline s32      Atomic_t::Subtract(volatile s32& a, s32 b)                                  { return Exchange_Subtract(a, b) - b; }
    inline s64      Atomic_t::Subtract(volatile s64& a, s64 b)                                  { return Exchange_Subtract(a, b) - b; }

    inline u8       Atomic_t::Or(volatile u8& a, u8 b)                                          { return Exchange_Or(a, b) | b; }
    inline u16      Atomic_t::Or(volatile u16& a, u16 b)                                        { return Exchange_Or(a, b) | b; }
    inline u32      Atomic_t::Or(volatile u32& a, u32 b)                                        { return Exchange_Or(a, b) | b; }
    inline u64      Atomic_t::Or(volatile u64& a, u64 b)                                        { return Exchange_Or(a, b) | b; }
    inline s8       Atomic_t::Or(volatile s8& a, s8 b)                                          { return Exchange_Or(a, b) | b; }
    inline s16      Atomic_t::Or(volatile s16& a, s16 b)                                        { return Exchange_Or(a, b) | b; }
    inline s32      Atomic_t::Or(volatile s32& a, s32 b)                                        { return Exchange_Or(a, b) | b; }
    inline s64      Atomic_t::Or(volatile s64& a, s64 b)                                        { return Exchange_Or(a, b) | b; }

    inline u8       Atomic_t::And(volatile u8& a, u8 b)                                         { return Exchange_And(a, b) & b; }
    inline u16      Atomic_t::And(volatile u16& a, u16 b)                                       { return Exchange_And(a, b) & b; }
    inline u32      Atomic_t::And(volatile u32& a, u32 b)                                       { return Exchange_And(a, b) & b; }
    inline u64      Atomic_t::And(volatile u64& a, u64 b)                                       { return Exchange_And(a, b) & b; }
    inline s8       Atomic_t::And(volatile s8& a, s8 b)                                         { return Exchange_And(a, b) & b; }
    inline s16      Atomic_t::And(volatile s16& a, s16 b)                                       { return Exchange_And(a, b) & b; }
    inline s32      Atomic_t::And(volatile s32& a, s32 b)                                       { return Exchange_And(a, b) & b; }
    inline s64      Atomic_t::And(volatile s64& a, s64 b)                                       { return Exchange_And(a, b) & b; }

    inline u8       Atomic_t::Xor(volatile u8& a, u8 b)                                         { return Exchange_Xor(a, b) ^ b; }
    inline u16      Atomic_t::Xor(volatile u16& a, u16 b)                                       { return Exchange_Xor(a, b) ^ b; }
    inline u32      Atomic_t::Xor(volatile u32& a, u32 b)                                       { return Exchange_Xor(a, b) ^ b; }
    inline u64      Atomic_t::Xor(volatile u64& a, u64 b)                                       { return Exchange_Xor(a, b) ^ b; }
    inline s8       Atomic_t::Xor(volatile s8& a, s8 b)                                         { return Exchange_Xor(a, b) ^ b; }
    inline s16      Atomic_t::Xor(volatile s16& a, s16 b)                                       { return Exchange_Xor(a, b) ^ b; }
    inline s32      Atomic_t::Xor(volatile s32& a, s32 b)                                       { return Exchange_Xor(a, b) ^ b; }
    inline s64      Atomic_t::Xor(volatile s64& a, s64 b)                                       { return Exchange_Xor(a, b) ^ b; }

    inline void*    Atomic_t::Access(const volatile void*& a)                                   { return Exchange_Assign_If_Equals((volatile void*&)a, 0, 0); }
    inline u8       Atomic_t::Access(const volatile u8& a)                                      { return Exchange_Assign_If_Equals((volatile u8&)a, 0, 0); }
    inline u16      Atomic_t::Access(const volatile u16& a)                                     { return Exchange_Assign_If_Equals((volatile u16&)a, 0, 0); }
    inline u32      Atomic_t::Access(const volatile u32& a)                                     { return Exchange_Assign_If_Equals((volatile u32&)a, 0, 0); }
    inline u64      Atomic_t::Access(const volatile u64& a)                                     { return Exchange_Assign_If_Equals((volatile u64&)a, 0, 0); }
    inline s8       Atomic_t::Access(const volatile s8& a)                                      { return Exchange_Assign_If_Equals((volatile s8&)a, 0, 0); }
    inline s16      Atomic_t::Access(const volatile s16& a)                                     { return Exchange_Assign_If_Equals((volatile s16&)a, 0, 0); }
    inline s32      Atomic_t::Access(const volatile s32& a)                                     { return Exchange_Assign_If_Equals((volatile s32&)a, 0, 0); }
    inline s64      Atomic_t::Access(const volatile s64& a)                                     { return Exchange_Assign_If_Equals((volatile s64&)a, 0, 0); }

}
