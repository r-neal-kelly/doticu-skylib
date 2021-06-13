/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/sp32.h"

namespace doticu_skylib {

    class Bound_Object_t;
    class Container_Entry_t;
    class Container_Changes_Entry_t;
    class Extra_List_t;
    class Leveled_Item_t;
    class Reference_Container_t;

    class Reference_Container_Entry_t
    {
    public:
        static some<Extra_List_t*>  Some_Extra_List(sp32 count);
        static maybe<Extra_List_t*> Maybe_Extra_List_Copy(some<Extra_List_t*> extra_list);
        static some<Extra_List_t*>  Some_Extra_List_Copy(some<Extra_List_t*> extra_list);

    public:
        maybe<Container_Entry_t*>           base_entry;
        maybe<Container_Changes_Entry_t*>   reference_entry;

    public:
        Reference_Container_Entry_t();
        Reference_Container_Entry_t(some<Container_Entry_t*> base_entry);
        Reference_Container_Entry_t(some<Container_Changes_Entry_t*> reference_entry);
        Reference_Container_Entry_t(some<Container_Entry_t*> base_entry, some<Container_Changes_Entry_t*> reference_entry);
        Reference_Container_Entry_t(some<Container_Entry_t*> base_entry, maybe<Container_Changes_Entry_t*> reference_entry);
        Reference_Container_Entry_t(maybe<Container_Entry_t*> base_entry, some<Container_Changes_Entry_t*> reference_entry);
        Reference_Container_Entry_t(maybe<Container_Entry_t*> base_entry, maybe<Container_Changes_Entry_t*> reference_entry);
        Reference_Container_Entry_t(const Reference_Container_Entry_t& other);
        Reference_Container_Entry_t(Reference_Container_Entry_t&& other) noexcept;
        Reference_Container_Entry_t& operator =(const Reference_Container_Entry_t& other);
        Reference_Container_Entry_t& operator =(Reference_Container_Entry_t&& other) noexcept;
        ~Reference_Container_Entry_t();

    public:
        Bool_t  Is_Valid() const;
        Bool_t  Is_Leveled_Item();
        Bool_t  Is_Playable_Item();
        Bool_t  Has_Quest_Item() const;

    public:
        some<Bound_Object_t*>               Some_Object();
        maybe<Leveled_Item_t*>              Maybe_Leveled_Item();
        maybe<Container_Changes_Entry_t*>   Maybe_Reference_Entry();
        some<Container_Changes_Entry_t*>    Some_Reference_Entry(Reference_Container_t& owner);
        Vector_t<some<Extra_List_t*>>       Some_Extra_Lists();

    public:
        sp32    Base_Count();
        sp32    Extra_Lists_Count();
        sp32    Non_Extra_Lists_Count();
        sp32    Count();

    public:
        sp32    Increment_Count(Reference_Container_t& owner, sp32 amount);
        sp32    Decrement_Count(Reference_Container_t& owner, sp32 amount);
        sp32    Remove_Count_To(Reference_Container_t& owner, sp32 amount, some<Reference_t*> to);
        sp32    Remove_Count_To(Reference_Container_t& owner, sp32 amount, Reference_Container_t& to);

    public:
        sp32        Add(Reference_Container_t& owner, some<Extra_List_t*> extra_list);
        sp32        Add_Copy_Or_Increment(Reference_Container_t& owner, some<Extra_List_t*> extra_list);
        sp32        Remove(Reference_Container_t& owner, some<Extra_List_t*> extra_list);
        sp32        Remove_And_Destroy(Reference_Container_t& owner, some<Extra_List_t*> extra_list);
        sp32        Remove_To(Reference_Container_t& owner, some<Extra_List_t*> extra_list, some<Reference_t*> to);
        sp32        Remove_To(Reference_Container_t& owner, some<Extra_List_t*> extra_list, Reference_Container_t& to);
        sp32        Increment_Count(Reference_Container_t& owner, some<Extra_List_t*> extra_list, s16 amount);
        sp32        Decrement_Count(Reference_Container_t& owner, some<Extra_List_t*> extra_list, s16 amount);
        maybe<sp32> Try_To_Consume(Reference_Container_t& owner, some<Extra_List_t*> extra_list);

    public:
        explicit operator   Bool_t() const;

    public:
        Bool_t  operator !() const;

    public:
        void Log(std::string indent = "");
    };

    template <>
    class none<Reference_Container_Entry_t>
    {
    public:
        using value_type = Reference_Container_Entry_t;

    public:
        none()
        {
        }

        none(const none& other)
        {
        }

        none(none&& other) noexcept
        {
        }

        none& operator =(const none& other)
        {
            return *this;
        }

        none& operator =(none&& other) noexcept
        {
            return *this;
        }

        ~none()
        {
        }

    public:
        explicit operator Bool_t() const
        {
            return false;
        }

    public:
        Bool_t operator !() const
        {
            return true;
        }
    };

    template <>
    class maybe<Reference_Container_Entry_t> :
        public Reference_Container_Entry_t
    {
    public:
        using value_type = Reference_Container_Entry_t;

    public:
        using Reference_Container_Entry_t::Reference_Container_Entry_t;

        maybe() = default;

        maybe(const none<value_type>& other) :
            Reference_Container_Entry_t()
        {
        }

        maybe(none<value_type>&& other) noexcept :
            Reference_Container_Entry_t()
        {
        }

        maybe(const value_type& other) :
            value_type(other)
        {
        }

        maybe(value_type&& other) noexcept :
            value_type(std::move(other))
        {
        }

        maybe& operator =(const value_type& other)
        {
            if (this != std::addressof(other)) {
                value_type::operator =(other);
            }
            return *this;
        }

        maybe& operator =(value_type&& other) noexcept
        {
            if (this != std::addressof(other)) {
                value_type::operator =(std::move(other));
            }
            return *this;
        }

        ~maybe() = default;
    };

    template <>
    class some<Reference_Container_Entry_t> :
        public Reference_Container_Entry_t
    {
    public:
        using value_type = Reference_Container_Entry_t;

    public:
        using Reference_Container_Entry_t::Reference_Container_Entry_t;

        some() = delete;

        some(maybe<Container_Entry_t*>, maybe<Container_Changes_Entry_t*>) = delete;

        some(const value_type& other) :
            value_type(other)
        {
        }

        some(value_type&& other) noexcept :
            value_type(std::move(other))
        {
        }

        some& operator =(const value_type& other)
        {
            if (this != std::addressof(other)) {
                value_type::operator =(other);
            }
            return *this;
        }

        some& operator =(value_type&& other) noexcept
        {
            if (this != std::addressof(other)) {
                value_type::operator =(std::move(other));
            }
            return *this;
        }

        ~some() = default;
    };

}
