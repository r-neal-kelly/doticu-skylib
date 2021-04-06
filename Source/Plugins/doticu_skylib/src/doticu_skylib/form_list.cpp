/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/form_list.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    Bool_t Form_List_t::Has(some<Form_t*> form)
    {
        SKYLIB_ASSERT_SOME(form);

        for (size_t idx = 0, end = this->static_forms.Count(); idx < end; idx += 1) {
            if (this->static_forms[idx] == form()) {
                return true;
            }
        }

        if (this->dynamic_form_ids) {
            for (size_t idx = 0, end = this->dynamic_form_ids->Count(); idx < end; idx += 1) {
                if (this->dynamic_form_ids->At(idx) == form->form_id) {
                    return true;
                }
            }
        }

        return false;
    }

    size_t Form_List_t::Count()
    {
        size_t count = this->static_forms.Count();
        if (this->dynamic_form_ids) {
            count += this->dynamic_form_ids->Count();
        }
        return count;
    }

    void Form_List_t::Add_Form(some<Form_t*> form)
    {
        static auto add_form = reinterpret_cast
            <void(*)(Form_List_t*, Form_t*)>
            (Game_t::Base_Address() + Offset_e::ADD_FORM);

        SKYLIB_ASSERT_SOME(form);
        add_form(this, form());
    }

    void Form_List_t::Remove_Added_Form(some<Form_t*> form)
    {
        static auto remove_added_form = reinterpret_cast
            <void(*)(Form_List_t*, Form_t*)>
            (Game_t::Base_Address() + Offset_e::REMOVE_ADDED_FORM);

        SKYLIB_ASSERT_SOME(form);
        remove_added_form(this, form());
    }

    void Form_List_t::Revert()
    {
        static auto revert = reinterpret_cast
            <void(*)(Form_List_t*)>
            (Game_t::Base_Address() + Offset_e::REVERT);

        revert(this);
    }

    maybe<Form_t*> Form_List_t::At(size_t index)
    {
        if (index < this->static_forms.Count()) {
            return this->static_forms[index];
        } else {
            return Game_t::Form(Dynamic_At(index));
        }
    }

    maybe<Form_t*>& Form_List_t::Static_At(size_t index)
    {
        SKYLIB_ASSERT(index < this->static_forms.Count());
        return this->static_forms[index];
    }

    Form_ID_t& Form_List_t::Dynamic_At(size_t index)
    {
        SKYLIB_ASSERT(this->dynamic_form_ids && index < this->dynamic_form_ids->Count());
        return this->dynamic_form_ids->At(index);
    }

    maybe<Form_t*>& Form_List_t::operator [](size_t index)
    {
        return Static_At(index);
    }

    maybe<Form_t*> Form_List_t::operator ()(size_t index)
    {
        return At(index);
    }

    void Form_List_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Form_List_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "static_forms");
        SKYLIB_LOG(indent + SKYLIB_TAB + "{");
        for (size_t idx = 0, end = this->static_forms.Count(); idx < end; idx += 1) {
            maybe<Form_t*> form = this->static_forms[idx];
            if (form) {
                SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "form: %p", form);
            } else {
                SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "form: (none)");
            }
        }
        SKYLIB_LOG(indent + SKYLIB_TAB + "}");

        if (this->dynamic_form_ids) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "dynamic_form_ids");
            SKYLIB_LOG(indent + SKYLIB_TAB + "{");
            for (size_t idx = 0, end = this->dynamic_form_ids->Count(); idx < end; idx += 1) {
                Form_ID_t form_id = this->dynamic_form_ids->At(idx);
                SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "form_id: %8.8X", form_id);
            }
            SKYLIB_LOG(indent + SKYLIB_TAB + "}");
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "dynamic_form_ids: (nullptr)");
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "dynamic_form_id_count: %u", this->dynamic_form_id_count);

        SKYLIB_LOG(indent + SKYLIB_TAB + "pad_44: %8.8X", this->pad_44);

        SKYLIB_LOG(indent + "}");
    }

}
