/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/form.h"
#include "doticu_skylib/form_id.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib {

    Form_ID_t::Form_ID_t(some<Heavy_Mod_Index_t> mod_index, some<Heavy_Form_Index_t> form_index) :
        Form_ID_t()
    {
        SKYLIB_ASSERT_SOME(mod_index);
        SKYLIB_ASSERT_SOME(form_index);

        this->value =
            ((static_cast<value_type>(mod_index()) & 0x000000FF) << 24) |
            (static_cast<value_type>(form_index()) & 0x00FFFFFF);
    }

    Form_ID_t::Form_ID_t(some<Light_Mod_Index_t> mod_index, some<Light_Form_Index_t> form_index) :
        Form_ID_t()
    {
        SKYLIB_ASSERT_SOME(mod_index);
        SKYLIB_ASSERT_SOME(form_index);

        this->value =
            static_cast<value_type>(0xFE000000) |
            ((static_cast<value_type>(mod_index()) & 0x00000FFF) << 12) |
            (static_cast<value_type>(form_index()) & 0x00000FFF);
    }

    Form_ID_t::Form_ID_t(some<Mod_t*> mod, Raw_Form_Index_t raw_form_index) :
        Form_ID_t()
    {
        SKYLIB_ASSERT_SOME(mod);

        maybe<Heavy_Mod_Index_t> heavy_mod_index = mod->Heavy_Mod_Index();
        if (heavy_mod_index) {
            maybe<Heavy_Form_Index_t> heavy_form_index(raw_form_index);
            if (heavy_form_index) {
                this->value = Form_ID_t(heavy_mod_index.some(), heavy_form_index.some());
            } else {
                this->value = _NONE_;
            }
        } else {
            maybe<Light_Mod_Index_t> light_mod_index = mod->Light_Mod_Index();
            if (light_mod_index) {
                maybe<Light_Form_Index_t> light_form_index(raw_form_index);
                if (light_form_index) {
                    this->value = Form_ID_t(light_mod_index.some(), light_form_index.some());
                } else {
                    this->value = _NONE_;
                }
            } else {
                this->value = _NONE_;
            }
        }
    }

    Bool_t Form_ID_t::Is_Static() const
    {
        return !Is_Dynamic();
    }

    Bool_t Form_ID_t::Is_Dynamic() const
    {
        return (this->value & 0xFF000000) == 0xFF000000;
    }

    Bool_t Form_ID_t::Is_Heavy() const
    {
        return !Is_Light();
    }

    Bool_t Form_ID_t::Is_Light() const
    {
        return (this->value & 0xFF000000) == 0xFE000000;
    }

    Bool_t Form_ID_t::Has_Mod(some<Heavy_Mod_Index_t> heavy_mod_index) const
    {
        SKYLIB_ASSERT_SOME(heavy_mod_index);

        return heavy_mod_index() == Heavy_Mod_Index()();
    }

    Bool_t Form_ID_t::Has_Mod(some<Light_Mod_Index_t> light_mod_index) const
    {
        SKYLIB_ASSERT_SOME(light_mod_index);

        return light_mod_index() == Light_Mod_Index()();
    }

    Bool_t Form_ID_t::Has_Mod(some<Mod_t*> mod) const
    {
        SKYLIB_ASSERT_SOME(mod);

        maybe<Heavy_Mod_Index_t> heavy_mod_index = mod->Heavy_Mod_Index();
        if (heavy_mod_index) {
            return Has_Mod(heavy_mod_index.some());
        } else {
            maybe<Light_Mod_Index_t> light_mod_index = mod->Light_Mod_Index();
            if (light_mod_index) {
                return Has_Mod(light_mod_index.some());
            } else {
                return false;
            }
        }
    }

    maybe<Heavy_Mod_Index_t> Form_ID_t::Heavy_Mod_Index() const
    {
        if (Is_Heavy()) {
            return Heavy_Mod_Index_t((this->value & 0xFF000000) >> 24);
        } else {
            return none<Heavy_Mod_Index_t>();
        }
    }

    Bool_t Form_ID_t::Heavy_Mod_Index(some<Heavy_Mod_Index_t> mod_index)
    {
        SKYLIB_ASSERT_SOME(mod_index);

        if (Is_Heavy()) {
            this->value |= (static_cast<value_type>(mod_index()) & 0x000000FF) << 24;
            return true;
        } else {
            return false;
        }
    }

    maybe<Light_Mod_Index_t> Form_ID_t::Light_Mod_Index() const
    {
        if (Is_Light()) {
            return Light_Mod_Index_t((this->value & 0x00FFF000) >> 12);
        } else {
            return none<Light_Mod_Index_t>();
        }
    }

    Bool_t Form_ID_t::Light_Mod_Index(some<Light_Mod_Index_t> mod_index)
    {
        SKYLIB_ASSERT_SOME(mod_index);

        if (Is_Light()) {
            this->value |= (static_cast<value_type>(mod_index()) & 0x00000FFF) << 12;
            return true;
        } else {
            return false;
        }
    }

    maybe<Heavy_Form_Index_t> Form_ID_t::Heavy_Form_Index() const
    {
        if (Is_Heavy()) {
            return Heavy_Form_Index_t(this->value & 0x00FFFFFF);
        } else {
            return none<Heavy_Form_Index_t>();
        }
    }

    Bool_t Form_ID_t::Heavy_Form_Index(some<Heavy_Form_Index_t> form_index)
    {
        SKYLIB_ASSERT_SOME(form_index);

        if (Is_Heavy()) {
            this->value |= static_cast<value_type>(form_index()) & 0x00FFFFFF;
            return true;
        } else {
            return false;
        }
    }

    maybe<Light_Form_Index_t> Form_ID_t::Light_Form_Index() const
    {
        if (Is_Light()) {
            return Light_Form_Index_t(this->value & 0x00000FFF);
        } else {
            return none<Light_Form_Index_t>();
        }
    }

    Bool_t Form_ID_t::Light_Form_Index(some<Light_Form_Index_t> form_index)
    {
        SKYLIB_ASSERT_SOME(form_index);

        if (Is_Light()) {
            this->value |= static_cast<value_type>(form_index()) & 0x00000FFF;
            return true;
        } else {
            return false;
        }
    }

    maybe<Mod_t*> Form_ID_t::Mod() const
    {
        if (Is_Static()) {
            maybe<Heavy_Mod_Index_t> heavy_mod_index = Heavy_Mod_Index();
            if (heavy_mod_index) {
                Array_t<maybe<Mod_t*>>& heavy_mods = Mod_t::Active_Heavy_Mods_2();
                if (heavy_mod_index() < heavy_mods.Count()) {
                    return heavy_mods[heavy_mod_index()];
                } else {
                    return nullptr;
                }
            } else {
                maybe<Light_Mod_Index_t> light_mod_index = Light_Mod_Index();
                if (light_mod_index) {
                    Array_t<maybe<Mod_t*>>& light_mods = Mod_t::Active_Light_Mods_2();
                    if (light_mod_index() < light_mods.Count()) {
                        return light_mods[light_mod_index()];
                    } else {
                        return nullptr;
                    }
                } else {
                    return nullptr;
                }
            }
        } else {
            return nullptr;
        }
    }

    Bool_t Form_ID_t::Mod(maybe<Mod_t*> mod)
    {
        if (mod) {
            maybe<Heavy_Mod_Index_t> heavy_mod_index = mod->Heavy_Mod_Index();
            if (heavy_mod_index) {
                return Heavy_Mod_Index(heavy_mod_index());
            } else {
                maybe<Light_Mod_Index_t> light_mod_index = mod->Light_Mod_Index();
                if (light_mod_index) {
                    return Light_Mod_Index(light_mod_index());
                } else {
                    return false;
                }
            }
        } else {
            return Heavy_Mod_Index(Heavy_Mod_Index_t(0xFF));
        }
    }

    maybe<Form_t*> Form_ID_t::Form() const
    {
        return Game_t::Form(*this);
    }

    Bool_t Form_ID_t::Form(some<Form_t*> form)
    {
        SKYLIB_ASSERT_SOME(form);

        maybe<Heavy_Form_Index_t> heavy_form_index = form->Heavy_Form_Index();
        if (heavy_form_index) {
            return Heavy_Form_Index(heavy_form_index());
        } else {
            maybe<Light_Form_Index_t> light_form_index = form->Light_Form_Index();
            if (light_form_index) {
                return Light_Form_Index(light_form_index());
            } else {
                return false;
            }
        }
    }

    String_t Form_ID_t::As_String() const
    {
        static const char hex_values[16] =
        {
            '0', '1', '2', '3', '4', '5', '6', '7',
            '8', '9', 'A', 'B', 'C', 'D', 'E', 'F',
        };

        char result[11] =
        {
            '0', 'x',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            '\0'
        };

        result[2] = hex_values[(this->value & 0xF0000000) >> 28];
        result[3] = hex_values[(this->value & 0x0F000000) >> 24];
        result[4] = hex_values[(this->value & 0x00F00000) >> 20];
        result[5] = hex_values[(this->value & 0x000F0000) >> 16];
        result[6] = hex_values[(this->value & 0x0000F000) >> 12];
        result[7] = hex_values[(this->value & 0x00000F00) >> 8];
        result[8] = hex_values[(this->value & 0x000000F0) >> 4];
        result[9] = hex_values[(this->value & 0x0000000F) >> 0];

        return result;
    }

    Form_ID_t::operator String_t() const
    {
        return As_String();
    }

}
