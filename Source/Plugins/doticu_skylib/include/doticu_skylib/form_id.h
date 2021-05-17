/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/form_index.h"
#include "doticu_skylib/mod_index.h"
#include "doticu_skylib/string.h"

namespace doticu_skylib {

    class Form_t;
    class Mod_t;

    using Raw_Form_ID_t = u32;

    class Form_ID_t_data :
        public Numeric_Data_t<Raw_Form_ID_t>
    {
    public:
        static constexpr value_type _NONE_ = 0;

    public:
        static Bool_t Is_Valid(value_type value)
        {
            return value != _NONE_;
        }
    };

    class Form_ID_t :
        public Numeric_t<Form_ID_t_data>
    {
    public:
        using Numeric_t::Numeric_t;

    public:
        Form_ID_t() = default;
        Form_ID_t(some<Heavy_Mod_Index_t> mod_index, some<Heavy_Form_Index_t> form_index);
        Form_ID_t(some<Light_Mod_Index_t> mod_index, some<Light_Form_Index_t> form_index);
        Form_ID_t(some<Mod_t*> mod, Raw_Form_Index_t raw_form_index);

    public:
        Bool_t  Is_Static() const;
        Bool_t  Is_Dynamic() const;

        Bool_t  Is_Heavy() const;
        Bool_t  Is_Light() const;

        Bool_t  Has_Mod(some<Heavy_Mod_Index_t> heavy_mod_index) const;
        Bool_t  Has_Mod(some<Light_Mod_Index_t> light_mod_index) const;
        Bool_t  Has_Mod(some<Mod_t*> mod) const;

    public:
        maybe<Heavy_Mod_Index_t>    Heavy_Mod_Index() const;
        Bool_t                      Heavy_Mod_Index(some<Heavy_Mod_Index_t> mod_index);

        maybe<Light_Mod_Index_t>    Light_Mod_Index() const;
        Bool_t                      Light_Mod_Index(some<Light_Mod_Index_t> mod_index);

        maybe<Heavy_Form_Index_t>   Heavy_Form_Index() const;
        Bool_t                      Heavy_Form_Index(some<Heavy_Form_Index_t> form_index);

        maybe<Light_Form_Index_t>   Light_Form_Index() const;
        Bool_t                      Light_Form_Index(some<Light_Form_Index_t> form_index);

    public:
        maybe<Mod_t*>   Mod() const;
        Bool_t          Mod(maybe<Mod_t*> mod); // sets to dynamic mod (0xFF) if none

        maybe<Form_t*>  Form() const;
        Bool_t          Form(some<Form_t*> form);

    public:
        String_t    As_String() const;

    public:
        operator    String_t() const;
    };

    template <>
    class none<Form_ID_t> :
        public none_numeric<Form_ID_t>
    {
    public:
        using none_numeric::none_numeric;
    };

    template <>
    class maybe<Form_ID_t> :
        public maybe_numeric<Form_ID_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Form_ID_t> :
        public some_numeric<Form_ID_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
