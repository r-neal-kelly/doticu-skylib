/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/form_list.h"

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

}
