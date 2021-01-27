/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/maybe_numeric.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/mod_index.h"
#include "doticu_skylib/form_index.h"

namespace doticu_skylib {

    using Raw_Form_ID_t = u32;

    class Form_t;
    class Mod_t;

    class Form_ID_t
    {
    public:
        using value_type = Raw_Form_ID_t;
        
    public:
        static constexpr value_type NONE_VALUE = 0;

    protected:
        value_type value;

    public:
        Form_ID_t();
        Form_ID_t(value_type value);
        Form_ID_t(some<Heavy_Mod_Index_t> mod_index, some<Heavy_Form_Index_t> form_index);
        Form_ID_t(some<Light_Mod_Index_t> mod_index, some<Light_Form_Index_t> form_index);
        Form_ID_t(some<Mod_t*> mod, Raw_Form_Index_t raw_form_index);

    public:
        Bool_t Is_Static() const;
        Bool_t Is_Dynamic() const;

        Bool_t Is_Heavy() const;
        Bool_t Is_Light() const;

        Bool_t Has_Mod(some<Heavy_Mod_Index_t> heavy_mod_index) const;
        Bool_t Has_Mod(some<Light_Mod_Index_t> light_mod_index) const;
        Bool_t Has_Mod(some<Mod_t*> mod) const;

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
        maybe<Mod_t*>   Mod();
        Bool_t          Mod(maybe<Mod_t*> mod); // sets to dynamic mod (0xFF) if none

        maybe<Form_t*>  Form();
        Bool_t          Form(some<Form_t*> form);

    public:
        operator            value_type() const;
        explicit operator   Bool_t() const;
        Bool_t operator     !() const;
        operator            String_t() const;
    };

    template <>
    Bool_t Is_Equal(const none<Form_ID_t>& a, const Form_ID_t& b);

    template <>
    class none<Form_ID_t> : public none_numeric<Form_ID_t>
    {
    public:
        none() : none_numeric(Form_ID_t::NONE_VALUE) {}
    };

    template <>
    class maybe<Form_ID_t> : public maybe_numeric<Form_ID_t>
    {
    public:
        using maybe_numeric::maybe_numeric;
    };

    template <>
    class some<Form_ID_t> : public some_numeric<Form_ID_t>
    {
    public:
        using some_numeric::some_numeric;
    };

}
