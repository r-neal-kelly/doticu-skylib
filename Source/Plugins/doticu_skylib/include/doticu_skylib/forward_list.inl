/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/forward_list.h"
#include "doticu_skylib/game.inl"

namespace doticu_skylib {

    /* Forward_List_t<T>::Node_t */

    template <typename T>
    inline some<typename Forward_List_t<T>::Node_t*> Forward_List_t<T>::Node_t::Create()
    {
        some<Node_t*> node = Game_t::Allocate<Node_t>();
        new (node()) Node_t();
        return node;
    }

    template <typename T>
    inline some<typename Forward_List_t<T>::Node_t*> Forward_List_t<T>::Node_t::Create(const T& value)
    {
        some<Node_t*> node = Game_t::Allocate<Node_t>();
        new (node()) Node_t(value);
        return node;
    }

    template <typename T>
    inline some<typename Forward_List_t<T>::Node_t*> Forward_List_t<T>::Node_t::Create(T&& value)
    {
        some<Node_t*> node = Game_t::Allocate<Node_t>();
        new (node()) Node_t(std::move(value));
        return node;
    }

    template <typename T>
    inline void Forward_List_t<T>::Node_t::Destroy(some<Node_t*> node)
    {
        SKYLIB_ASSERT_SOME(node);
        node->~Node_t();
        Game_t::Deallocate<Node_t>(node);
    }

    template <typename T>
    inline Forward_List_t<T>::Node_t::Node_t() :
        value(T()), next(nullptr)
    {
    }

    template <typename T>
    inline Forward_List_t<T>::Node_t::Node_t(const T& value) :
        value(value), next(nullptr)
    {
    }

    template <typename T>
    inline Forward_List_t<T>::Node_t::Node_t(T&& value) :
        value(std::move(value)), next(nullptr)
    {
    }

    template <typename T>
    inline Forward_List_t<T>::Node_t::Node_t(const Node_t& other) :
        value(other.value), next(other.next)
    {
    }

    template <typename T>
    inline Forward_List_t<T>::Node_t::Node_t(Node_t&& other) noexcept :
        value(std::exchange(other.value, T())), next(std::exchange(other.next, nullptr))
    {
    }

    template <typename T>
    inline typename Forward_List_t<T>::Node_t& Forward_List_t<T>::Node_t::operator=(const Node_t& other)
    {
        if (this != std::addressof(other)) {
            this->value = other.value;
            this->next = other.next;
        }
        return *this;
    }

    template <typename T>
    inline typename Forward_List_t<T>::Node_t& Forward_List_t<T>::Node_t::operator=(Node_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->value = std::exchange(other.value, T());
            this->next = std::exchange(other.next, nullptr);
        }
        return *this;
    }

    template <typename T>
    inline Forward_List_t<T>::Node_t::~Node_t()
    {
        this->value.~T();
        next = nullptr;
    }

    /* Forward_List_t<T> */

    template <typename T>
    inline some<Forward_List_t<T>*> Forward_List_t<T>::Create()
    {
        some<Forward_List_t*> forward_list = Game_t::Allocate<Forward_List_t>();
        new (forward_list()) Forward_List_t();
        return forward_list;
    }

    template <typename T>
    inline some<Forward_List_t<T>*> Forward_List_t<T>::Create(const T& head_value)
    {
        some<Forward_List_t*> forward_list = Game_t::Allocate<Forward_List_t>();
        new (forward_list()) Forward_List_t(head_value);
        return forward_list;
    }

    template <typename T>
    inline some<Forward_List_t<T>*> Forward_List_t<T>::Create(T&& head_value)
    {
        some<Forward_List_t*> forward_list = Game_t::Allocate<Forward_List_t>();
        new (forward_list()) Forward_List_t(std::move(head_value));
        return forward_list;
    }

    template <typename T>
    inline void Forward_List_t<T>::Destroy(some<Forward_List_t*> forward_list)
    {
        SKYLIB_ASSERT_SOME(forward_list);
        forward_list->~Forward_List_t();
        Game_t::Deallocate<Forward_List_t>(forward_list);
    }

    template <typename T>
    inline Forward_List_t<T>::Forward_List_t() :
        head(Node_t())
    {
    }

    template <typename T>
    inline Forward_List_t<T>::Forward_List_t(const T& head_value) :
        head(head_value)
    {
    }

    template <typename T>
    inline Forward_List_t<T>::Forward_List_t(T&& head_value) :
        head(std::move(head_value))
    {
    }

    template <typename T>
    inline Forward_List_t<T>::~Forward_List_t()
    {
        for (maybe<Node_t*> it = this->head.next; it; it = it->next) {
            Node_t::Destroy(it());
        }
        this->head.~Node_t();
    }

    template <typename Type_t>
    inline Bool_t Forward_List_t<Type_t>::Is_Empty()
    {
        return !head.value;
    }

    template <typename Type_t>
    inline maybe<Type_t*> Forward_List_t<Type_t>::Point(size_t index)
    {
        if (!Is_Empty()) {
            size_t idx = 0;
            for (maybe<Node_t*> node = &head; node; node = node->next, idx += 1) {
                if (idx == index) {
                    return &node->value;
                }
            }
            return none<Type_t*>();
        } else {
            return none<Type_t*>();
        }
    }

    template <typename T>
    inline Bool_t Forward_List_t<T>::Has(const T& value)
    {
        if (Is_Empty()) {
            return false;
        } else {
            for (maybe<Node_t*> it = &this->head; it; it = it->next) {
                if (it->value == value) {
                    return true;
                }
            }
            return false;
        }
    }

    template <typename T>
    inline void Forward_List_t<T>::Add(const T& value)
    {
        if (Is_Empty()) {
            head = Node_t(value);
        } else {
            some<Node_t*> new_node = Node_t::Create();
            *new_node = std::move(head);
            head = Node_t(value);
            head.next = new_node();
        }
    }

    template <typename T>
    inline Bool_t Forward_List_t<T>::Remove(const T& value)
    {
        if (Is_Empty()) {
            return false;
        } else {
            if (this->head.value == value) {
                maybe<Node_t*> next_node = this->head.next;
                this->head.~Node_t();
                if (next_node) {
                    this->head = std::move(*next_node);
                    Node_t::Destroy(next_node());
                }
                return true;
            } else {
                for (maybe<Node_t*> it = &this->head; it; it = it->next) {
                    maybe<Node_t*> next = it->next;
                    if (next && next->value == value) {
                        it->next = next->next;
                        Node_t::Destroy(next());
                        return true;
                    }
                }
                return false;
            }
        }
    }

    template <typename T>
    inline Bool_t Forward_List_t<T>::Remove(T&& value)
    {
        return Remove(value);
    }

    template <typename T>
    inline void Forward_List_t<T>::Log(std::string indent)
    {
        Forward_List_Logger_t<T>::Log(*this, indent);
    }

    template <typename T>
    inline void Forward_List_Logger_t<T*>::Log(Forward_List_t<T*>& forward_list, std::string indent)
    {
        SKYLIB_LOG(indent + "Forward_List_t::Log");
        SKYLIB_LOG(indent + "{");

        if (forward_list.Is_Empty()) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "(empty)");
        } else {
            size_t idx = 0;
            for (maybe<Forward_List_t<T*>::Node_t*> it = &forward_list.head; it; it = it->next, idx += 1) {
                SKYLIB_LOG(indent + SKYLIB_TAB + "idx: %zu", idx);
                SKYLIB_LOG(indent + SKYLIB_TAB + "value: %p", it->value);
                SKYLIB_LOG(indent + SKYLIB_TAB + "next: %p", it->next);
            }
        }

        SKYLIB_LOG(indent + "}");
    }

    template <typename T>
    inline void Forward_List_Logger_t<maybe<T*>>::Log(Forward_List_t<maybe<T*>>& forward_list, std::string indent)
    {
        Forward_List_Logger_t<T*>::Log(reinterpret_cast<Forward_List_t<T*>&>(forward_list), indent);
    }

    template <typename T>
    inline void Forward_List_Logger_t<some<T*>>::Log(Forward_List_t<some<T*>>& forward_list, std::string indent)
    {
        Forward_List_Logger_t<T*>::Log(reinterpret_cast<Forward_List_t<T*>&>(forward_list), indent);
    }

}
