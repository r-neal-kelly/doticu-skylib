/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_package_value_type.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Package_Value_Bool_t;
    class Package_Value_Float_t;
    class Package_Value_Int_t;
    class Package_Value_List_t;
    class Package_Value_Location_t;
    class Package_Value_Reference_t;
    class Package_Value_Target_t;
    class Package_Value_Topic_t;

    class Package_Value_t   // IPackageData, BGSNamedPackageData
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E22C00, // 514008
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual ~Package_Value_t(); // 0

    public:
        Package_Value_Type_e                        Type() const;

        Bool_t                                      Is_Bool() const;
        Bool_t                                      Is_Float() const;
        Bool_t                                      Is_Int() const;
        Bool_t                                      Is_List() const;
        Bool_t                                      Is_Location() const;
        Bool_t                                      Is_Reference() const;
        Bool_t                                      Is_Target() const;
        Bool_t                                      Is_Topic() const;

        maybe<Package_Value_Bool_t*>                As_Bool() const;
        maybe<Package_Value_Float_t*>               As_Float() const;
        maybe<Package_Value_Int_t*>                 As_Int() const;
        maybe<Package_Value_List_t*>                As_List() const;
        maybe<Package_Value_Location_t*>            As_Location() const;
        maybe<Package_Value_Reference_t*>           As_Reference() const;
        maybe<Package_Value_Target_t*>              As_Target() const;
        maybe<Package_Value_Topic_t*>               As_Topic() const;

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Value_t) == 0x08);

}
