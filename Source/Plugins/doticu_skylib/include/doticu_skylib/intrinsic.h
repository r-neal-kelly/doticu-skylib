/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <vector>

#include "common/ITypes.h"

#include "skse64/GameData.h"
#include "skse64/GameObjects.h"
#include "skse64/GameTypes.h"

namespace doticu_skylib {

    typedef UInt8           u8;
    typedef UInt16          u16;
    typedef UInt32          u32;
    typedef UInt64          u64;
    typedef SInt8           s8;
    typedef SInt16          s16;
    typedef SInt32          s32;
    typedef SInt64          s64;
    typedef float           f32;
    typedef double          f64;

    typedef UInt8           Byte_t;
    typedef size_t          Word_t;
    typedef SInt64          Index_t;

    typedef bool            Bool_t;
    typedef SInt32          Int_t;
    typedef float           Float_t;

    typedef ModInfo         Mod_t;
    typedef u32             Form_ID_t;
    typedef u32             Lower_Form_ID_t;
    typedef u8              Form_Type_t;

    typedef TESObjectMISC   Misc_t;
    typedef TESObjectSTAT   Static_t;
    typedef TESObjectWEAP   Weapon_t;
    typedef TESObjectARMO   Armor_t;

    typedef TESFaction      Faction_t;
    typedef BGSOutfit       Outfit_t;

    typedef TESRace         Race_t;
    typedef Character       Character_t;
    typedef PlayerCharacter Player_Character_t;

    typedef UInt32          Reference_Handle_t;

    typedef DataHandler     Game_Data_t;
    typedef TESFile         File_t;

    typedef BGSLocation     Location_t;

    template <typename Type, typename Allocator = std::allocator<Type>>
    using Vector_t = std::vector<Type, Allocator>;

    template <typename ...Arguments>
    struct Callback_i {
        virtual ~Callback_i() = default;
        virtual void operator()(Arguments...) = 0;
    };

    template <typename ...Arguments>
    struct Iterator_i {
        virtual ~Iterator_i() = default;
        virtual void operator()(Arguments...) = 0;
    };

}

#include "doticu_skylib/string.h"
