/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/forward_list.inl"

#include "doticu_skylib/cell.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/extra_collision_layer.h"
#include "doticu_skylib/extra_container_changes.h"
#include "doticu_skylib/extra_data.h"
#include "doticu_skylib/extra_text_display.h"
#include "doticu_skylib/extra_list.h"

namespace doticu_skylib {

    template <typename Extra_t>
    static void Log_References(std::string indent)
    {
        SKYLIB_LOG(indent + "Log_References");
        SKYLIB_LOG(indent + "{");

        Vector_t<some<Reference_t*>> refs = Reference_t::Loaded_References();
        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            some<Reference_t*> ref = refs[idx];

            SKYLIB_LOG(indent + SKYLIB_TAB + "Reference_t: %s, %s", ref->Any_Name(), ref->Form_ID_String());
            SKYLIB_LOG(indent + SKYLIB_TAB + "{");

            Log_Extra_List<Extra_t>(indent + SKYLIB_TAB + SKYLIB_TAB, ref->xlist);

            SKYLIB_LOG(indent + SKYLIB_TAB + "}");
        }

        SKYLIB_LOG(indent + "}");
    }

    template <typename Extra_t>
    static void Log_Extra_List(std::string indent, List_x& list_x)
    {
        Read_Locker_t locker(list_x.lock);
        for (Data_x* xdata = list_x.xdatas; xdata != nullptr; xdata = xdata->next) {
            Extra_Type_e type = xdata->Type();
            if (type == Extra_Type_e::CONTAINER_CHANGES) {
                maybe<Container_Changes_t*> container_changes = static_cast<Container_Changes_x*>(xdata)->container_changes;
                if (container_changes) {
                    Log_Container_Changes<Extra_t>(indent, *container_changes);
                }
            } else if (type == Extra_t::EXTRA_TYPE) {
                static_cast<Extra_t*>(xdata)->Log(indent);
            }
        }
    }

    template <typename Extra_t>
    static void Log_Container_Changes(std::string indent, Container_Changes_t& container_changes)
    {
        SKYLIB_LOG(indent + "Log_Container_Changes");
        SKYLIB_LOG(indent + "{");

        if (container_changes.entries && !container_changes.entries->Is_Empty()) {
            for (auto* it = &container_changes.entries->head; it; it = it->next) {
                Container_Changes_Entry_t* entry = it->value;
                if (entry && entry->xlists && !entry->xlists->Is_Empty()) {
                    for (auto* it = &entry->xlists->head; it; it = it->next) {
                        List_x* x_list = it->value;
                        if (x_list) {
                            Log_Extra_List<Extra_t>(indent + SKYLIB_TAB, *x_list);
                        }
                    }
                }
            }
        }

        SKYLIB_LOG(indent + "}");
    }

    static void Log_Unique_V_Tables(std::string indent, Vector_t<Extra_Type_e>& found_types, List_x& x_list);
    static void Log_Unique_V_Tables(std::string indent, Vector_t<Extra_Type_e>& found_types, Container_Changes_t* container_changes);

    static void Log_Unique_V_Tables(std::string indent, Vector_t<Extra_Type_e>& found_types, List_x& x_list)
    {
        Read_Locker_t locker(x_list.lock);
        for (Data_x* xdata = x_list.xdatas; xdata != nullptr; xdata = xdata->next) {
            Extra_Type_e type = xdata->Type();
            if (!found_types.Has(type)) {
                found_types.push_back(type);
                if (type == Extra_Type_e::CONTAINER_CHANGES) {
                    Log_Unique_V_Tables(indent, found_types, static_cast<Container_Changes_x*>(xdata)->container_changes);
                } else {
                    SKYLIB_LOG(indent + "type: 0x%2.2X, v_table_offset: 0x%8.8X", type, Game_t::V_Table_Offset(xdata));
                }
            }
        }
    }

    static void Log_Unique_V_Tables(std::string indent, Vector_t<Extra_Type_e>& found_types, Container_Changes_t* container_changes)
    {
        if (container_changes) {
            if (container_changes->entries && !container_changes->entries->Is_Empty()) {
                for (auto* it = &container_changes->entries->head; it; it = it->next) {
                    Container_Changes_Entry_t* entry = it->value;
                    if (entry && entry->xlists && !entry->xlists->Is_Empty()) {
                        for (auto* it = &entry->xlists->head; it; it = it->next) {
                            List_x* x_list = it->value;
                            if (x_list) {
                                Log_Unique_V_Tables(indent, found_types, *x_list);
                            }
                        }
                    }
                }
            }
        }
    }

    void Data_x::Log_V_Tables(std::string indent)
    {
        Vector_t<Extra_Type_e> found_types;
        found_types.reserve(256);

        Vector_t<some<Reference_t*>> refs = Reference_t::Loaded_References();
        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            some<Reference_t*> ref = refs[idx];
            Log_Unique_V_Tables(indent, found_types, ref->xlist);
        }

        Vector_t<Cell_t*> cells = Cell_t::Loaded_Cells();
        for (size_t idx = 0, end = cells.size(); idx < end; idx += 1) {
            maybe<Cell_t*> cell = cells[idx];
            if (cell) {
                Log_Unique_V_Tables(indent, found_types, cell->xlist);
            }
        }
    }

    void Data_x::Log_Collision_Layers(std::string indent)
    {
        SKYLIB_LOG(indent + "Data_x::Log_Collision_Layers");
        SKYLIB_LOG(indent + "{");

        Log_References<Collision_Layer_x>(indent + SKYLIB_TAB);

        SKYLIB_LOG(indent + "}");
    }

    static void Log_Text_Displays(std::string indent, List_x& x_list);
    static void Log_Text_Displays(std::string indent, Container_Changes_t* container_changes);

    static void Log_Text_Displays(std::string indent, List_x& x_list)
    {
        Read_Locker_t locker(x_list.lock);
        for (Data_x* xdata = x_list.xdatas; xdata != nullptr; xdata = xdata->next) {
            if (xdata->Type() == Extra_Type_e::TEXT_DISPLAY) {
                static_cast<Text_Display_x*>(xdata)->Log(indent + SKYLIB_TAB);
            }
        }
    }

    static void Log_Text_Displays(std::string indent, Container_Changes_t* container_changes)
    {
        if (container_changes) {
            if (container_changes->entries && !container_changes->entries->Is_Empty()) {
                for (auto* it = &container_changes->entries->head; it; it = it->next) {
                    Container_Changes_Entry_t* entry = it->value;
                    if (entry && entry->xlists && !entry->xlists->Is_Empty()) {
                        for (auto* it = &entry->xlists->head; it; it = it->next) {
                            List_x* x_list = it->value;
                            if (x_list) {
                                Log_Text_Displays(indent, *x_list);
                            }
                        }
                    }
                }
            }
        }
    }

    void Data_x::Log_Text_Displays(std::string indent)
    {
        Vector_t<some<Reference_t*>> refs = Reference_t::Loaded_References();
        for (size_t idx = 0, end = refs.size(); idx < end; idx += 1) {
            some<Reference_t*> ref = refs[idx];
            doticu_skylib::Log_Text_Displays(indent, ref->xlist);
        }

        Vector_t<Cell_t*> cells = Cell_t::Loaded_Cells();
        for (size_t idx = 0, end = cells.size(); idx < end; idx += 1) {
            maybe<Cell_t*> cell = cells[idx];
            if (cell) {
                doticu_skylib::Log_Text_Displays(indent, cell->xlist);
            }
        }
    }

    Extra_Type_e Data_x::Type()
    {
        return Get_Type();
    }

}
