/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/form_list.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    Bool_t Form_List_t::Has(some<Form_t*> form)
    {
        SKYLIB_ASSERT_SOME(form);

        if (forms.entries) {
            for (Index_t idx = 0, end = forms.count; idx < end; idx += 1) {
                if (forms.entries[idx] == form()) {
                    return true;
                }
            }
        }

        if (added_form_ids && added_form_ids->entries) {
            for (Index_t idx = 0, end = added_form_ids->count; idx < end; idx += 1) {
                if (added_form_ids->entries[idx] == form->form_id) {
                    return true;
                }
            }
        }

        return false;
    }

    size_t Form_List_t::Count()
    {
        size_t count = forms.count;
        if (added_form_ids) {
            count += added_form_ids->count;
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

    void Form_List_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Form_List_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "forms");
        SKYLIB_LOG(indent + SKYLIB_TAB + "{");
        for (size_t idx = 0, end = this->forms.count; idx < end; idx += 1) {
            Form_t* form = forms.entries[idx];
            SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "form: %p", form);
        }
        SKYLIB_LOG(indent + SKYLIB_TAB + "}");

        if (this->added_form_ids) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "added_form_ids");
            SKYLIB_LOG(indent + SKYLIB_TAB + "{");
            for (size_t idx = 0, end = added_form_ids->count; idx < end; idx += 1) {
                Form_ID_t form_id = added_form_ids->entries[idx];
                SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "form_id: %8.8X", form_id);
            }
            SKYLIB_LOG(indent + SKYLIB_TAB + "}");
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "added_form_ids: (nullptr)");
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "added_form_id_count: %u", this->added_form_id_count);

        SKYLIB_LOG(indent + SKYLIB_TAB + "pad_44: %8.8X", this->pad_44);

        SKYLIB_LOG(indent + "}");
    }

}
