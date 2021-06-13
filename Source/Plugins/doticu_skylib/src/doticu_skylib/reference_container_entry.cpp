/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/bound_object.h"
#include "doticu_skylib/container_changes.h"
#include "doticu_skylib/container_changes_entry.h"
#include "doticu_skylib/container_entry.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/reference_container.h"
#include "doticu_skylib/reference_container_entry.h"

namespace doticu_skylib {

    some<Extra_List_t*> Reference_Container_Entry_t::Some_Extra_List(sp32 count)
    {
        return Container_Changes_Entry_t::Some_Extra_List(count);
    }

    maybe<Extra_List_t*> Reference_Container_Entry_t::Maybe_Extra_List_Copy(some<Extra_List_t*> extra_list)
    {
        return Container_Changes_Entry_t::Maybe_Extra_List_Copy(extra_list);
    }

    some<Extra_List_t*> Reference_Container_Entry_t::Some_Extra_List_Copy(some<Extra_List_t*> extra_list)
    {
        return Container_Changes_Entry_t::Some_Extra_List_Copy(extra_list);
    }

    Reference_Container_Entry_t::Reference_Container_Entry_t() :
        base_entry(none<Container_Entry_t*>()),
        reference_entry(none<Container_Changes_Entry_t*>())
    {
    }

    Reference_Container_Entry_t::Reference_Container_Entry_t(some<Container_Entry_t*> base_entry) :
        base_entry(base_entry()),
        reference_entry(none<Container_Changes_Entry_t*>())
    {
        SKYLIB_ASSERT(Is_Valid());
    }

    Reference_Container_Entry_t::Reference_Container_Entry_t(some<Container_Changes_Entry_t*> reference_entry) :
        base_entry(none<Container_Entry_t*>()),
        reference_entry(reference_entry())
    {
        SKYLIB_ASSERT(Is_Valid());
    }

    Reference_Container_Entry_t::Reference_Container_Entry_t(some<Container_Entry_t*> base_entry,
                                                             some<Container_Changes_Entry_t*> reference_entry) :
        base_entry(base_entry()),
        reference_entry(reference_entry())
    {
        SKYLIB_ASSERT(Is_Valid());
    }

    Reference_Container_Entry_t::Reference_Container_Entry_t(some<Container_Entry_t*> base_entry,
                                                             maybe<Container_Changes_Entry_t*> reference_entry) :
        base_entry(base_entry()),
        reference_entry(reference_entry)
    {
        SKYLIB_ASSERT(Is_Valid());
    }

    Reference_Container_Entry_t::Reference_Container_Entry_t(maybe<Container_Entry_t*> base_entry,
                                                             some<Container_Changes_Entry_t*> reference_entry) :
        base_entry(base_entry),
        reference_entry(reference_entry())
    {
        SKYLIB_ASSERT(Is_Valid());
    }

    Reference_Container_Entry_t::Reference_Container_Entry_t(maybe<Container_Entry_t*> base_entry,
                                                             maybe<Container_Changes_Entry_t*> reference_entry) :
        base_entry(base_entry),
        reference_entry(reference_entry)
    {
    }

    Reference_Container_Entry_t::Reference_Container_Entry_t(const Reference_Container_Entry_t& other) :
        base_entry(other.base_entry),
        reference_entry(other.reference_entry)
    {
        SKYLIB_ASSERT(Is_Valid());
    }

    Reference_Container_Entry_t::Reference_Container_Entry_t(Reference_Container_Entry_t&& other) noexcept :
        base_entry(std::exchange(other.base_entry, none<Container_Entry_t*>())),
        reference_entry(std::exchange(other.reference_entry, none<Container_Changes_Entry_t*>()))
    {
        SKYLIB_ASSERT(Is_Valid());
    }

    Reference_Container_Entry_t& Reference_Container_Entry_t::operator =(const Reference_Container_Entry_t& other)
    {
        if (std::addressof(other) != this) {
            base_entry = other.base_entry;
            reference_entry = other.reference_entry;
            SKYLIB_ASSERT(Is_Valid());
        }
        return *this;
    }

    Reference_Container_Entry_t& Reference_Container_Entry_t::operator =(Reference_Container_Entry_t&& other) noexcept
    {
        if (std::addressof(other) != this) {
            base_entry = std::exchange(other.base_entry, none<Container_Entry_t*>());
            reference_entry = std::exchange(other.reference_entry, none<Container_Changes_Entry_t*>());
            SKYLIB_ASSERT(Is_Valid());
        }
        return *this;
    }

    Reference_Container_Entry_t::~Reference_Container_Entry_t()
    {
        this->reference_entry = none<Container_Changes_Entry_t*>();
        this->base_entry = none<Container_Entry_t*>();
    }

    Bool_t Reference_Container_Entry_t::Is_Valid() const
    {
        return
            (this->base_entry && this->base_entry->bound_object) ||
            (this->reference_entry && this->reference_entry->bound_object);
    }

    Bool_t Reference_Container_Entry_t::Is_Leveled_Item()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Maybe_Leveled_Item() != none<Leveled_Item_t*>();
    }

    Bool_t Reference_Container_Entry_t::Is_Playable_Item()
    {
        SKYLIB_ASSERT(Is_Valid());

        return Some_Object()->Get_Is_Playable();
    }

    Bool_t Reference_Container_Entry_t::Has_Quest_Item() const
    {
        SKYLIB_ASSERT(Is_Valid());

        if (this->reference_entry) {
            return this->reference_entry->Has_Quest_Item();
        } else {
            return false;
        }
    }

    some<Bound_Object_t*> Reference_Container_Entry_t::Some_Object()
    {
        SKYLIB_ASSERT(Is_Valid());

        if (this->reference_entry) {
            return this->reference_entry->bound_object();
        } else {
            return this->base_entry->bound_object();
        }
    }

    maybe<Leveled_Item_t*> Reference_Container_Entry_t::Maybe_Leveled_Item()
    {
        SKYLIB_ASSERT(Is_Valid());

        if (this->base_entry && this->base_entry->bound_object) {
            return this->base_entry->bound_object->As_Leveled_Item();
        } else {
            return none<Leveled_Item_t*>();
        }
    }

    maybe<Container_Changes_Entry_t*> Reference_Container_Entry_t::Maybe_Reference_Entry()
    {
        SKYLIB_ASSERT(Is_Valid());

        return this->reference_entry;
    }

    some<Container_Changes_Entry_t*> Reference_Container_Entry_t::Some_Reference_Entry(Reference_Container_t& owner)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT(!Some_Object()->Is_Leveled_Item());

        if (!this->reference_entry) {
            owner.Has_Changed(true);
            this->reference_entry = owner.Some_Reference_Container()->Some_Entry(Some_Object())();
            SKYLIB_ASSERT_SOME(this->reference_entry);
        }
        return this->reference_entry();
    }

    Vector_t<some<Extra_List_t*>> Reference_Container_Entry_t::Some_Extra_Lists()
    {
        if (this->reference_entry) {
            return this->reference_entry->Extra_Lists();
        } else {
            return Vector_t<some<Extra_List_t*>>();
        }
    }

    sp32 Reference_Container_Entry_t::Base_Count()
    {
        SKYLIB_ASSERT(Is_Valid());

        if (this->base_entry) {
            return this->base_entry->count;
        } else {
            return 0;
        }
    }

    sp32 Reference_Container_Entry_t::Extra_Lists_Count()
    {
        SKYLIB_ASSERT(Is_Valid());

        if (this->reference_entry) {
            return this->reference_entry->Extra_Lists_Count();
        } else {
            return 0;
        }
    }

    sp32 Reference_Container_Entry_t::Non_Extra_Lists_Count()
    {
        SKYLIB_ASSERT(Is_Valid());

        sp32 base_count = Base_Count();
        if (this->reference_entry) {
            return (this->reference_entry->Delta(base_count) + base_count) - this->reference_entry->Extra_Lists_Count();
        } else {
            return base_count;
        }
    }

    sp32 Reference_Container_Entry_t::Count()
    {
        SKYLIB_ASSERT(Is_Valid());

        sp32 base_count = Base_Count();
        if (this->reference_entry) {
            return this->reference_entry->Delta(base_count) + base_count;
        } else {
            return base_count;
        }
    }

    sp32 Reference_Container_Entry_t::Increment_Count(Reference_Container_t& owner, sp32 amount)
    {
        SKYLIB_ASSERT(Is_Valid());

        sp32 base_count = Base_Count();
        owner.Has_Changed(true);
        return Some_Reference_Entry(owner)->Increment_Delta(base_count, amount) + base_count;
    }

    sp32 Reference_Container_Entry_t::Decrement_Count(Reference_Container_t& owner, sp32 amount)
    {
        SKYLIB_ASSERT(Is_Valid());

        sp32 base_count = Base_Count();
        if (base_count > 0) {
            owner.Has_Changed(true);
            return Some_Reference_Entry(owner)->Decrement_Delta(base_count, amount) + base_count;
        } else {
            maybe<Container_Changes_Entry_t*> reference_entry = Maybe_Reference_Entry();
            if (reference_entry) {
                owner.Has_Changed(true);
                return reference_entry->Decrement_Delta(base_count, amount);
            } else {
                return 0;
            }
        }
    }

    sp32 Reference_Container_Entry_t::Remove_Count_To(Reference_Container_t& owner, sp32 amount, some<Reference_t*> to)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(to);

        if (amount > 0) {
            sp32 old_count = Count();
            sp32 new_count = Decrement_Count(owner, amount);

            sp32 difference = old_count - new_count;
            if (difference > 0) {
                owner.Has_Changed(true);
                to->Add_Item(Some_Object(), none<Extra_List_t*>(), difference, none<Reference_t*>());
            }

            return new_count;
        } else {
            return Count();
        }
    }

    sp32 Reference_Container_Entry_t::Remove_Count_To(Reference_Container_t& owner, sp32 amount, Reference_Container_t& to)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT(to.Is_Valid());

        to.Has_Changed(true);
        return Remove_Count_To(owner, amount, to.Reference());
    }

    sp32 Reference_Container_Entry_t::Add(Reference_Container_t& owner, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(extra_list);

        sp32 base_count = Base_Count();
        owner.Has_Changed(true);
        return Some_Reference_Entry(owner)->Add(base_count, extra_list) + base_count;
    }

    sp32 Reference_Container_Entry_t::Add_Copy_Or_Increment(Reference_Container_t& owner, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(extra_list);

        sp32 base_count = Base_Count();
        owner.Has_Changed(true);
        return Some_Reference_Entry(owner)->Add_Copy_Or_Increment(base_count, extra_list) + base_count;
    }

    sp32 Reference_Container_Entry_t::Remove(Reference_Container_t& owner, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(this->reference_entry);
        SKYLIB_ASSERT_SOME(extra_list);

        sp32 base_count = Base_Count();
        owner.Has_Changed(true);
        return this->reference_entry->Remove(base_count, extra_list) + base_count;
    }

    sp32 Reference_Container_Entry_t::Remove_And_Destroy(Reference_Container_t& owner, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(this->reference_entry);
        SKYLIB_ASSERT_SOME(extra_list);

        sp32 base_count = Base_Count();
        owner.Has_Changed(true);
        return this->reference_entry->Remove_And_Destroy(base_count, extra_list) + base_count;
    }

    sp32 Reference_Container_Entry_t::Remove_To(Reference_Container_t& owner, some<Extra_List_t*> extra_list, some<Reference_t*> to)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(this->reference_entry);
        SKYLIB_ASSERT_SOME(extra_list);
        SKYLIB_ASSERT_SOME(to);

        sp32 base_count = Base_Count();
        owner.Has_Changed(true);
        return this->reference_entry->Remove_To(base_count, extra_list, owner.Reference(), to) + base_count;
    }

    sp32 Reference_Container_Entry_t::Remove_To(Reference_Container_t& owner, some<Extra_List_t*> extra_list, Reference_Container_t& to)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(this->reference_entry);
        SKYLIB_ASSERT_SOME(extra_list);
        SKYLIB_ASSERT(to.Is_Valid());

        to.Has_Changed(true);
        return Remove_To(owner, extra_list, to.Reference());
    }

    sp32 Reference_Container_Entry_t::Increment_Count(Reference_Container_t& owner, some<Extra_List_t*> extra_list, s16 amount)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT(this->reference_entry);
        SKYLIB_ASSERT_SOME(extra_list);

        sp32 base_count = Base_Count();
        owner.Has_Changed(true);
        return this->reference_entry->Increment_Count(base_count, extra_list, amount) + base_count;
    }

    sp32 Reference_Container_Entry_t::Decrement_Count(Reference_Container_t& owner, some<Extra_List_t*> extra_list, s16 amount)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT(this->reference_entry);
        SKYLIB_ASSERT_SOME(extra_list);

        sp32 base_count = Base_Count();
        owner.Has_Changed(true);
        return this->reference_entry->Decrement_Count(base_count, extra_list, amount) + base_count;
    }

    maybe<sp32> Reference_Container_Entry_t::Try_To_Consume(Reference_Container_t& owner, some<Extra_List_t*> extra_list)
    {
        SKYLIB_ASSERT(Is_Valid());
        SKYLIB_ASSERT_SOME(extra_list);

        if (this->reference_entry) {
            sp32 base_count = Base_Count();
            maybe<s32> reference_entry_delta = this->reference_entry->Try_To_Consume(base_count, extra_list);
            if (reference_entry_delta.Has_Value()) {
                owner.Has_Changed(true);
                return sp32(reference_entry_delta.Value() + base_count);
            } else {
                return none<sp32>();
            }
        } else {
            return none<sp32>();
        }
    }

    Reference_Container_Entry_t::operator Bool_t() const
    {
        return Is_Valid();
    }

    Bool_t Reference_Container_Entry_t::operator !() const
    {
        return !static_cast<Bool_t>(*this);
    }

    void Reference_Container_Entry_t::Log(std::string indent)
    {
        SKYLIB_ASSERT(Is_Valid());

        SKYLIB_LOG(indent + "Reference_Container_Entry_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "object: %s, %s", Some_Object()->Component_Name(), Some_Object()->Form_ID_String());
        SKYLIB_LOG(indent + SKYLIB_TAB + "base_count: %d", Base_Count());
        SKYLIB_LOG(indent + SKYLIB_TAB + "extra_lists_count: %d", Extra_Lists_Count());
        SKYLIB_LOG(indent + SKYLIB_TAB + "non_extra_lists_count: %d", Non_Extra_Lists_Count());
        SKYLIB_LOG(indent + SKYLIB_TAB + "count: %d", Count());

        if (this->reference_entry) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "reference_entry:");
            this->reference_entry->Log(indent + SKYLIB_TAB + SKYLIB_TAB);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "reference_entry: (none)");
        }

        SKYLIB_LOG(indent + "}");
    }

}
