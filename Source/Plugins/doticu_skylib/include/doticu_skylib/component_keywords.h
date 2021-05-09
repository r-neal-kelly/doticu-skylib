/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/component_form_data.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    class Keyword_t;

    class Keywords_c :      // BGSKeywordForm
        public Form_Data_c  // 00
    {
    public:
        class Offset_e :
            public Enum_t<Word_t>
        {
        public:
            enum enum_type : value_type
            {
                RTTI = 0x01E10F28, // 513855
            };

        public:
            using Enum_t::Enum_t;
        };

    public:
        virtual             ~Keywords_c();                                      // 0

        virtual Bool_t      Get_Has_Keyword(const Keyword_t* keyword) const;    // 4
        virtual Keyword_t*  Get_Default_Keyword() const;                        // 5

    public:
        maybe<maybe<Keyword_t*>*>   keywords;       // 08
        u32                         keyword_count;  // 10
        u32                         pad_14;         // 14

    public:
        Bool_t                      Component_Has_Keyword(some<Keyword_t*> keyword) const;
        Bool_t                      Component_Has_All_Keywords(const Vector_t<some<Keyword_t*>>& keywords) const;
        Bool_t                      Component_Has_Any_Keywords(const Vector_t<some<Keyword_t*>>& keywords) const;

        Vector_t<some<Keyword_t*>>  Component_Keywords() const;
        void                        Component_Keywords(Vector_t<some<Keyword_t*>>& results) const;

    public:
        void    Log_Component_Keywords(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Keywords_c) == 0x18);

}
