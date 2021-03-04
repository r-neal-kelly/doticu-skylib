/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"
#include "doticu_skylib/ni_3d.h"
#include "doticu_skylib/ni_extra.h"
#include "doticu_skylib/ni_node.h"
#include "doticu_skylib/reference.h"

namespace doticu_skylib {

    Vector_t<some<NI_3D_t*>> NI_3D_t::Children()
    {
        Vector_t<some<NI_3D_t*>> results;
        Children(results);
        return results;
    }

    void NI_3D_t::Children(Vector_t<some<NI_3D_t*>>& results)
    {
        maybe<NI_Node_t*> ni_node = As_NI_Node();
        if (ni_node) {
            ni_node->Children(results);
        }
    }

    Vector_t<some<NI_Collidable_t*>> NI_3D_t::Collidables()
    {
        Vector_t<some<NI_Collidable_t*>> results;
        results.reserve(8);
        Collidables(results);
        return results;
    }

    void NI_3D_t::Collidables(Vector_t<some<NI_Collidable_t*>>& results)
    {
        if (this->collidable && !results.Has(this->collidable())) {
            results.push_back(this->collidable());
        }

        maybe<NI_Node_t*> ni_node = As_NI_Node();
        if (ni_node) {
            for (size_t idx = 0, end = ni_node->children.count; idx < end; idx += 1) {
                maybe<NI_3D_t*> child = ni_node->children.entries[idx];
                if (child) {
                    child->Collidables(results);
                }
            }
        }
    }

    void NI_3D_t::Update(NI_Update_t& ni_update)
    {
        static auto update = reinterpret_cast
            <void(*)(NI_3D_t*, NI_Update_t&)>
            (Game_t::Base_Address() + Offset_e::UPDATE);

        update(this, ni_update);
    }

    String_t NI_3D_t::Name()
    {
        return this->extras_name;
    }

    void NI_3D_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "NI_3D_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "name: %s", Name());

        if (this->reference) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "reference: %s", reference->Any_Name());
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "reference: (none)");
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "local_transform:");
        this->local_transform.Log(indent + SKYLIB_TAB + SKYLIB_TAB);

        SKYLIB_LOG(indent + SKYLIB_TAB + "world_transform:");
        this->world_transform.Log(indent + SKYLIB_TAB + SKYLIB_TAB);

        SKYLIB_LOG(indent + SKYLIB_TAB + "previous_world_transform:");
        this->previous_world_transform.Log(indent + SKYLIB_TAB + SKYLIB_TAB);

        Vector_t<some<NI_Extra_t*>> extras = Extras();
        if (extras.size() > 0) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "extras:");
            for (size_t idx = 0, end = extras.size(); idx < end; idx += 1) {
                some<NI_Extra_t*> extra = extras[idx];
                extra->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
            }
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "extras: (none)");
        }

        Vector_t<some<NI_3D_t*>> children = Children();
        if (children.size() > 0) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "children:");
            for (size_t idx = 0, end = children.size(); idx < end; idx += 1) {
                some<NI_3D_t*> child = children[idx];
                child->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
            }
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "children: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
