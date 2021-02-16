/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/extra_list.h"
#include "doticu_skylib/forward_list.inl"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/math.h"

namespace doticu_skylib {

    Vector_t<some<Container_Changes_Entry_t*>> temp_allocations;

    some<Container_Changes_Entry_t*> Container_Changes_Entry_t::Create(some<Bound_Object_t*> object)
    {
        some<Container_Changes_Entry_t*> container_changes_entry = Game_t::Allocate<Container_Changes_Entry_t>();
        new (container_changes_entry()) Container_Changes_Entry_t(object);
        return container_changes_entry;
    }

    void Container_Changes_Entry_t::Destroy(some<Container_Changes_Entry_t*> container_changes_entry)
    {
        SKYLIB_ASSERT_SOME(container_changes_entry);
        container_changes_entry->~Container_Changes_Entry_t();
        Game_t::Deallocate<Container_Changes_Entry_t>(container_changes_entry);
    }

    Container_Changes_Entry_t::Container_Changes_Entry_t() :
        object(none<Bound_Object_t*>()), x_lists(none<List_t<maybe<Extra_List_t*>>*>()), delta(0), pad_14(0)
    {
    }

    Container_Changes_Entry_t::Container_Changes_Entry_t(some<Bound_Object_t*> object) :
        object(object()), x_lists(none<List_t<maybe<Extra_List_t*>>*>()), delta(0), pad_14(0)
    {
        SKYLIB_ASSERT(!object->Is_Leveled_Item());
    }

    Container_Changes_Entry_t::Container_Changes_Entry_t(Container_Changes_Entry_t&& other) noexcept :
        object(std::exchange(other.object, none<Bound_Object_t*>())),
        x_lists(std::exchange(other.x_lists, none<List_t<maybe<Extra_List_t*>>*>())),
        delta(std::exchange(other.delta, 0)),
        pad_14(std::exchange(other.pad_14, 0))
    {
    }

    Container_Changes_Entry_t& Container_Changes_Entry_t::operator=(Container_Changes_Entry_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->~Container_Changes_Entry_t();
            object = std::exchange(other.object, none<Bound_Object_t*>());
            x_lists = std::exchange(other.x_lists, none<List_t<maybe<Extra_List_t*>>*>());
            delta = std::exchange(other.delta, 0);
            pad_14 = std::exchange(other.pad_14, 0);
        }
        return *this;
    }

    Container_Changes_Entry_t::~Container_Changes_Entry_t()
    {
        this->object = none<Bound_Object_t*>();
        Destroy_Extra_Lists();
        this->delta = 0;
        this->pad_14 = 0;
    }

    Vector_t<some<Extra_List_t*>> Container_Changes_Entry_t::Extra_Lists()
    {
        Vector_t<some<Extra_List_t*>> results;

        if (this->x_lists && !this->x_lists->Is_Empty()) {
            for (maybe<List_t<maybe<Extra_List_t*>>::Node_t*> it = &this->x_lists->head; it; it = it->next) {
                maybe<Extra_List_t*> x_list = it->value;
                if (x_list) {
                    results.push_back(x_list());
                }
            }
        }

        return results;
    }

    s32 Container_Changes_Entry_t::Extra_Lists_Count()
    {
        s32 count = 0;
        if (this->x_lists && !this->x_lists->Is_Empty()) {
            for (maybe<List_t<maybe<Extra_List_t*>>::Node_t*> it = &this->x_lists->head; it; it = it->next) {
                maybe<Extra_List_t*> x_list = it->value;
                if (x_list) {
                    count += x_list->Count();
                    if (count < 0) {
                        return std::numeric_limits<s32>::max();
                    }
                }
            }
        }
        return count;
    }

    s32 Container_Changes_Entry_t::Minimum_Delta(Container_Entry_Count_t base_count)
    {
        return Extra_Lists_Count() + -base_count;
    }

    s32 Container_Changes_Entry_t::Maximum_Delta(Container_Entry_Count_t base_count)
    {
        return std::numeric_limits<s32>::max() + -base_count;
    }

    s32 Container_Changes_Entry_t::Delta(Container_Entry_Count_t base_count)
    {
        this->delta = Limit(this->delta, Minimum_Delta(base_count), Maximum_Delta(base_count));
        return this->delta;
    }

    s32 Container_Changes_Entry_t::Increment_Delta(Container_Entry_Count_t base_count, Container_Entry_Count_t amount)
    {
        s32 minimum_delta = Minimum_Delta(base_count);
        s32 maximum_delta = Maximum_Delta(base_count);
        s32 current_delta = Limit(this->delta, minimum_delta, maximum_delta);
        s32 new_delta = current_delta + amount;
        if (new_delta < current_delta || new_delta > maximum_delta) {
            this->delta = maximum_delta;
        } else {
            this->delta = new_delta;
        }
        return this->delta;
    }

    s32 Container_Changes_Entry_t::Decrement_Delta(Container_Entry_Count_t base_count, Container_Entry_Count_t amount)
    {
        s32 minimum_delta = Minimum_Delta(base_count);
        s32 maximum_delta = Maximum_Delta(base_count);
        s32 current_delta = Limit(this->delta, minimum_delta, maximum_delta);
        s32 new_delta = current_delta - amount;
        if (new_delta > current_delta || new_delta < minimum_delta) {
            this->delta = minimum_delta;
        } else {
            this->delta = new_delta;
        }
        return this->delta;
    }

    s32 Container_Changes_Entry_t::Add_Extra_List(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT_SOME(extra_list);
        SKYLIB_ASSERT(this->x_lists ? !this->x_lists->Has(extra_list()) : true);
        SKYLIB_ASSERT(!extra_list->Should_Be_Destroyed());

        if (!this->x_lists) {
            this->x_lists = List_t<maybe<Extra_List_t*>>::Create(extra_list())();
        } else {
            this->x_lists->Add(extra_list());
        }

        return Increment_Delta(base_count, extra_list->Count());
    }

    s32 Container_Changes_Entry_t::Remove_Extra_List(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT_SOME(extra_list);
        SKYLIB_ASSERT(this->x_lists && this->x_lists->Has(extra_list()));
        SKYLIB_ASSERT(!extra_list->Should_Be_Destroyed());

        if (this->x_lists && this->x_lists->Remove(extra_list())) {
            if (this->x_lists->Is_Empty()) {
                Destroy_Extra_Lists();
            }
            return Decrement_Delta(base_count, extra_list->Count());
        } else {
            return Delta(base_count);
        }
    }

    s32 Container_Changes_Entry_t::Destroy_Extra_List(Container_Entry_Count_t base_count, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT_SOME(extra_list);
        SKYLIB_ASSERT(this->x_lists && this->x_lists->Has(extra_list()));

        if (this->x_lists->Remove(extra_list())) {
            if (this->x_lists->Is_Empty()) {
                Destroy_Extra_Lists();
            }
            s16 x_list_count = extra_list->Count();
            Extra_List_t::Destroy(extra_list());
            return Decrement_Delta(base_count, x_list_count);
        }
    }

    s32 Container_Changes_Entry_t::Increment_Extra_List_Count(Container_Entry_Count_t base_count,
                                                              some<Extra_List_t*> extra_list,
                                                              s16 amount)
    {
        SKYLIB_ASSERT_SOME(extra_list);
        SKYLIB_ASSERT(this->x_lists && this->x_lists->Has(extra_list()));
        SKYLIB_ASSERT(!extra_list->Should_Be_Destroyed());

        if (this->x_lists && this->x_lists->Has(extra_list())) {
            s16 count = extra_list->Count();
            s16 new_count = extra_list->Increment_Count(amount);
            return Increment_Delta(base_count, new_count - count);
        } else {
            return Delta(base_count);
        }
    }

    s32 Container_Changes_Entry_t::Decrement_Extra_List_Count(Container_Entry_Count_t base_count,
                                                              some<Extra_List_t*> extra_list,
                                                              s16 amount)
    {
        SKYLIB_ASSERT_SOME(extra_list);
        SKYLIB_ASSERT(this->x_lists && this->x_lists->Has(extra_list()));
        SKYLIB_ASSERT(!extra_list->Should_Be_Destroyed());

        if (this->x_lists && this->x_lists->Has(extra_list())) {
            s16 count = extra_list->Count();
            s16 new_count = extra_list->Decrement_Count(amount);
            if (extra_list->Should_Be_Destroyed()) {
                this->x_lists->Remove(extra_list());
                Extra_List_t::Destroy(extra_list);
                if (this->x_lists->Is_Empty()) {
                    Destroy_Extra_Lists();
                }
            }
            return Decrement_Delta(base_count, count - new_count);
        } else {
            return Delta(base_count);
        }
    }

    Bool_t Container_Changes_Entry_t::Should_Be_Destroyed()
    {
        return this->delta == 0 && Extra_Lists_Count() == 0;
    }

    void Container_Changes_Entry_t::Destroy_Extra_Lists()
    {
        if (this->x_lists) {
            if (!this->x_lists->Is_Empty()) {
                for (maybe<List_t<maybe<Extra_List_t*>>::Node_t*> it = &this->x_lists->head; it; it = it->next) {
                    maybe<Extra_List_t*> x_list = it->value;
                    if (x_list) {
                        Extra_List_t::Destroy(x_list());
                        it->value = none<Extra_List_t*>();
                    }
                }
            }
            List_t<maybe<Extra_List_t*>>::Destroy(this->x_lists());
            this->x_lists = none<List_t<maybe<Extra_List_t*>>*>();
        }
    }

}
