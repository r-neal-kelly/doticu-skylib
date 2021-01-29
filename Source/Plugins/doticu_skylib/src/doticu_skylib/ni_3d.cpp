/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.inl"
#include "doticu_skylib/ni_3d.h"
#include "doticu_skylib/ni_node.h"

namespace doticu_skylib {

    maybe<NI_Node_t*> NI_3D_t::As_NI_Node()
    {
        return Game_t::Runtime_Cast<NI_3D_t, NI_Node_t>(this);
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

}
