/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cell.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/extra_aliases.h"
#include "doticu_skylib/extra_cannot_wear.h"
#include "doticu_skylib/extra_charge.h"
#include "doticu_skylib/extra_count.h"
#include "doticu_skylib/extra_collision_layer.h"
#include "doticu_skylib/extra_container_changes.h"
#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_enchantment.h"
#include "doticu_skylib/extra_from_alias.h"
#include "doticu_skylib/extra_list.h"
#include "doticu_skylib/extra_owner.h"
#include "doticu_skylib/extra_poison.h"
#include "doticu_skylib/extra_reference_handle.h"
#include "doticu_skylib/extra_soul_level.h"
#include "doticu_skylib/extra_temper_level.h"
#include "doticu_skylib/extra_text_display.h"
#include "doticu_skylib/extra_unique_id.h"
#include "doticu_skylib/forward_list.inl"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    template <typename T>
    static void Log_References(std::string indent)
    {
        SKYLIB_LOG(indent + "Log_References");
        SKYLIB_LOG(indent + "{");

        Vector_t<some<Reference_t*>> refs = Reference_t::All_References();
        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            some<Reference_t*> ref = refs[idx];

            SKYLIB_LOG(indent + SKYLIB_TAB + "Reference_t name: %s, form_id: %s, base_form_id: %s, base_form_type: 0x%2.2X",
                       ref->Any_Name(),
                       ref->Form_ID_String(),
                       ref->base_form ? static_cast<String_t>(ref->base_form->form_id) : "(none)",
                       ref->base_form ? static_cast<Form_Type_e::value_type>(ref->base_form->form_type) : 0);
            SKYLIB_LOG(indent + SKYLIB_TAB + "{");

            Log_Extra_List<T>(indent + SKYLIB_TAB + SKYLIB_TAB, ref->x_list);

            SKYLIB_LOG(indent + SKYLIB_TAB + "}");
        }

        SKYLIB_LOG(indent + "}");
    }

    template <typename T>
    static void Log_Extra_List(std::string indent, Extra_List_t& x_list)
    {
        Read_Locker_t locker(x_list.lock);
        for (maybe<Extra_Data_t*> it = x_list.x_datas; it; it = it->next) {
            Extra_Type_e type = it->Type();
            if (type == Extra_Type_e::CONTAINER_CHANGES) {
                maybe<Container_Changes_t*> container_changes = static_cast<Extra_Container_Changes_t*>(it())->container_changes;
                if (container_changes) {
                    Log_Container_Changes<T>(indent, *container_changes);
                }
            } else if (type == T::EXTRA_TYPE) {
                static_cast<T*>(it())->Log(indent);
            }
        }
    }

    template <typename T>
    static void Log_Container_Changes(std::string indent, Container_Changes_t& container_changes)
    {
        SKYLIB_LOG(indent + "Log_Container_Changes");
        SKYLIB_LOG(indent + "{");

        if (container_changes.entries && !container_changes.entries->Is_Empty()) {
            for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &container_changes.entries->head; it; it = it->next) {
                maybe<Container_Changes_Entry_t*> entry = it->value;
                if (entry && entry->x_lists && !entry->x_lists->Is_Empty()) {
                    for (maybe<List_t<maybe<Extra_List_t*>>::Node_t*> it = &entry->x_lists->head; it; it = it->next) {
                        maybe<Extra_List_t*> x_list = it->value;
                        if (x_list) {
                            Log_Extra_List<T>(indent + SKYLIB_TAB, *x_list);
                        }
                    }
                }
            }
        }

        SKYLIB_LOG(indent + "}");
    }

    static void Log_Unique_V_Tables(std::string indent, Vector_t<Extra_Type_e>& found_types, Extra_List_t& x_list);
    static void Log_Unique_V_Tables(std::string indent, Vector_t<Extra_Type_e>& found_types, Container_Changes_t* container_changes);

    static void Log_Unique_V_Tables(std::string indent, Vector_t<Extra_Type_e>& found_types, Extra_List_t& x_list)
    {
        Read_Locker_t locker(x_list.lock);
        for (maybe<Extra_Data_t*> it = x_list.x_datas; it; it = it->next) {
            Extra_Type_e type = it->Type();
            if (!found_types.Has(type)) {
                found_types.push_back(type);
                if (type == Extra_Type_e::CONTAINER_CHANGES) {
                    Log_Unique_V_Tables(indent, found_types, static_cast<Extra_Container_Changes_t*>(it())->container_changes());
                } else {
                    SKYLIB_LOG(indent + "type: 0x%2.2X, v_table_offset: 0x%8.8X", type, Game_t::V_Table_Offset(it()));
                }
            }
        }
    }

    static void Log_Unique_V_Tables(std::string indent, Vector_t<Extra_Type_e>& found_types, Container_Changes_t* container_changes)
    {
        if (container_changes) {
            if (container_changes->entries && !container_changes->entries->Is_Empty()) {
                for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &container_changes->entries->head; it; it = it->next) {
                    maybe<Container_Changes_Entry_t*> entry = it->value;
                    if (entry && entry->x_lists && !entry->x_lists->Is_Empty()) {
                        for (maybe<List_t<maybe<Extra_List_t*>>::Node_t*> it = &entry->x_lists->head; it; it = it->next) {
                            maybe<Extra_List_t*> x_list = it->value;
                            if (x_list) {
                                Log_Unique_V_Tables(indent, found_types, *x_list);
                            }
                        }
                    }
                }
            }
        }
    }

    void Extra_Data_t::Log_V_Tables(std::string indent)
    {
        Vector_t<Extra_Type_e> found_types;
        found_types.reserve(256);

        Vector_t<some<Reference_t*>> refs = Reference_t::All_References();
        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            some<Reference_t*> ref = refs[idx];
            Log_Unique_V_Tables(indent, found_types, ref->x_list);
        }

        Vector_t<some<Cell_t*>> cells = Cell_t::All_Cells();
        for (size_t idx = 0, end = cells.size(); idx < end; idx += 1) {
            Log_Unique_V_Tables(indent, found_types, cells[idx]->x_list);
        }
    }

    void Extra_Data_t::Log_Collision_Layers(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Data_t::Log_Collision_Layers");
        SKYLIB_LOG(indent + "{");

        Log_References<Extra_Collision_Layer_t>(indent + SKYLIB_TAB);

        SKYLIB_LOG(indent + "}");
    }

    static void Log_Text_Displays(std::string indent, Extra_List_t& x_list);
    static void Log_Text_Displays(std::string indent, Container_Changes_t* container_changes);

    static void Log_Text_Displays(std::string indent, Extra_List_t& x_list)
    {
        Read_Locker_t locker(x_list.lock);
        for (maybe<Extra_Data_t*> it = x_list.x_datas; it; it = it->next) {
            if (it->Type() == Extra_Type_e::TEXT_DISPLAY) {
                static_cast<Extra_Text_Display_t*>(it())->Log(indent + SKYLIB_TAB);
            }
        }
    }

    static void Log_Text_Displays(std::string indent, Container_Changes_t* container_changes)
    {
        if (container_changes) {
            if (container_changes->entries && !container_changes->entries->Is_Empty()) {
                for (maybe<List_t<maybe<Container_Changes_Entry_t*>>::Node_t*> it = &container_changes->entries->head; it; it = it->next) {
                    maybe<Container_Changes_Entry_t*> entry = it->value;
                    if (entry && entry->x_lists && !entry->x_lists->Is_Empty()) {
                        for (maybe<List_t<maybe<Extra_List_t*>>::Node_t*> it = &entry->x_lists->head; it; it = it->next) {
                            maybe<Extra_List_t*> x_list = it->value;
                            if (x_list) {
                                Log_Text_Displays(indent, *x_list);
                            }
                        }
                    }
                }
            }
        }
    }

    void Extra_Data_t::Log_Text_Displays(std::string indent)
    {
        Vector_t<some<Reference_t*>> refs = Reference_t::All_References();
        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            some<Reference_t*> ref = refs[idx];
            doticu_skylib::Log_Text_Displays(indent, ref->x_list);
        }

        Vector_t<some<Cell_t*>> cells = Cell_t::All_Cells();
        for (size_t idx = 0, end = cells.size(); idx < end; idx += 1) {
            doticu_skylib::Log_Text_Displays(indent, cells[idx]->x_list);
        }
    }

    Extra_Type_e Extra_Data_t::Type()
    {
        return Get_Type();
    }

    Bool_t Extra_Data_t::Is_Equal(some<Extra_Data_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        return !Get_Isnt_Equal(other());
    }

    Bool_t Extra_Data_t::Isnt_Equal(some<Extra_Data_t*> other)
    {
        SKYLIB_ASSERT_SOME(other);

        return Get_Isnt_Equal(other());
    }

    maybe<Extra_Data_t*> Extra_Data_t::Copy()
    {
        Extra_Type_e type = Type();
        if (type == Extra_Type_e::CANNOT_WEAR)          return Create<Extra_Cannot_Wear_t>(*this)();
        else if (type == Extra_Type_e::CHARGE)          return Create<Extra_Charge_t>(*this)();
        else if (type == Extra_Type_e::COUNT)           return Create<Extra_Count_t>(*this)();
        else if (type == Extra_Type_e::ENCHANTMENT)     return Create<Extra_Enchantment_t>(*this)();
        else if (type == Extra_Type_e::FROM_ALIAS)      return Create<Extra_From_Alias_t>(*this)();
        else if (type == Extra_Type_e::OWNER)           return Create<Extra_Owner_t>(*this)();
        else if (type == Extra_Type_e::POISON)          return Create<Extra_Poison_t>(*this)();
        else if (type == Extra_Type_e::SOUL_LEVEL)      return Create<Extra_Soul_Level_t>(*this)();
        else if (type == Extra_Type_e::TEMPER_LEVEL)    return Create<Extra_Temper_Level_t>(*this)();
        else if (type == Extra_Type_e::TEXT_DISPLAY)    return Create<Extra_Text_Display_t>(*this)();
        else if (type == Extra_Type_e::UNIQUE_ID)       return Create<Extra_Unique_ID_t>(*this)();
        else                                            return none<Extra_Data_t*>();
    }

    void Extra_Data_t::Log(std::string indent)
    {
        Extra_Type_e type = Type();
        if (type == Extra_Type_e::ALIASES)                  static_cast<Extra_Aliases_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::CANNOT_WEAR)         static_cast<Extra_Cannot_Wear_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::CHARGE)              static_cast<Extra_Charge_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::COUNT)               static_cast<Extra_Count_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::ENCHANTMENT)         static_cast<Extra_Enchantment_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::FROM_ALIAS)          static_cast<Extra_From_Alias_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::OWNER)               static_cast<Extra_Owner_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::POISON)              static_cast<Extra_Poison_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::REFERENCE_HANDLE)    static_cast<Extra_Reference_Handle_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::SOUL_LEVEL)          static_cast<Extra_Soul_Level_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::TEMPER_LEVEL)        static_cast<Extra_Temper_Level_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::TEXT_DISPLAY)        static_cast<Extra_Text_Display_t*>(this)->Log(indent);
        else if (type == Extra_Type_e::UNIQUE_ID)           static_cast<Extra_Unique_ID_t*>(this)->Log(indent);
        else {
            SKYLIB_LOG(indent + "Extra_Data_t::Log");
            SKYLIB_LOG(indent + "{");

            SKYLIB_LOG(indent + SKYLIB_TAB + "type: %s, v_table: 0x%8.8X",
                       Extra_Type_e::To_String(type),
                       Game_t::V_Table_Offset(this));

            SKYLIB_LOG(indent + "}");
        }
    }

}
