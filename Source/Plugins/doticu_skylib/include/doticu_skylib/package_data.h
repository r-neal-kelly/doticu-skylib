/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Dialogue_Topic_t;
    class Package_t;
    class Package_Location_t;
    class Package_Target_t;
    class Package_Value_t;

    class Package_Data_t    // TESPackageData
    {
    public:
        virtual ~Package_Data_t(); // 0

    public:
        maybe<maybe<Package_Value_t*>*> values;             // 08
        void*                           unk_10;             // 10 Variable Size, probably an array/hashmap (** ptr to ptrs), repeats more among like packages
        u16                             value_count;        // 18
        u8                              marker;             // 1A XNAM
        u8                              unk_1B;             // 1B
        Bool_t                          unk_1C;             // 1C
        u8                              pad_1D;             // 1D
        u16                             pad_1E;             // 1E
        void*                           shared_20;          // 20 (connected with template. procedures or inputs)
        void*                           shared_28;          // 28 (connected with template. procedures or inputs)
        maybe<Package_t*>               package_template;   // 30
        u16                             version;            // 38
        u16                             unk_3A;             // 3A
        Bool_t                          unk_3C;             // 3C
        u8                              pad_3D;             // 3D
        u16                             pad_3E;             // 3E

    public:
        size_t                      Value_Count() const;
        maybe<Package_Value_t*>     Value(size_t index) const;

        Bool_t                      Bool(size_t index) const;
        void                        Bool(size_t index, Bool_t value);

        Float_t                     Float(size_t index) const;
        void                        Float(size_t index, Float_t value);

        Int_t                       Int(size_t index) const;
        void                        Int(size_t index, Int_t value);

        maybe<Package_Location_t*>  Location(size_t index) const;
        void                        Location(size_t index, maybe<Package_Location_t*> value);

        maybe<Package_Target_t*>    Reference_Target(size_t index) const;
        void                        Reference_Target(size_t index, maybe<Package_Target_t*> value);

        maybe<Package_Target_t*>    Target(size_t index) const;
        void                        Target(size_t index, maybe<Package_Target_t*> value);

        maybe<Dialogue_Topic_t*>    Topic(size_t index) const;
        void                        Topic(size_t index, maybe<Dialogue_Topic_t*> value);
        u32                         Topic_Sub_type(size_t index) const;
        void                        Topic_Sub_type(size_t index, u32 value);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Data_t) == 0x40);

}
