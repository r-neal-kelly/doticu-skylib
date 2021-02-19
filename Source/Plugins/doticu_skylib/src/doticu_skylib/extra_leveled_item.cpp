/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_leveled_item.h"
#include "doticu_skylib/leveled_item.h"

namespace doticu_skylib {

    some<Extra_Leveled_Item_t*> Extra_Leveled_Item_t::Create(some<Leveled_Item_t*> leveled_item)
    {
        SKYLIB_ASSERT_SOME(leveled_item);

        some<Extra_Leveled_Item_t*> x_leveled_item = Extra_Data_t::Create<Extra_Leveled_Item_t>();

        x_leveled_item->leveled_item_form_id = leveled_item->form_id;
        x_leveled_item->pad_14 = 0;

        return x_leveled_item;
    }

    void Extra_Leveled_Item_t::Destroy(some<Extra_Leveled_Item_t*> x_leveled_item)
    {
        SKYLIB_ASSERT_SOME(x_leveled_item);

        Extra_Data_t::Destroy<Extra_Leveled_Item_t>(x_leveled_item);
    }

}
