/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    template <typename T>
    class Forward_List_t // tList, BSSimpleList
    {
    public:
        class Node_t
        {
        public:
            static some<Node_t*>    Create();
            static some<Node_t*>    Create(const T& value);
            static some<Node_t*>    Create(T&& value);
            static void             Destroy(some<Node_t*> node);

        public:
            T               value;  // 0
            maybe<Node_t*>  next;   // ?

        public:
            Node_t();
            Node_t(const T& value);
            Node_t(T&& value);
            Node_t(const Node_t& other);
            Node_t(Node_t&& other) noexcept;
            Node_t& operator=(const Node_t& other);
            Node_t& operator=(Node_t&& other) noexcept;
            ~Node_t();
        };

    public:
        static some<Forward_List_t*>    Create();
        static some<Forward_List_t*>    Create(const T& head_value);
        static some<Forward_List_t*>    Create(T&& head_value);
        static void                     Destroy(some<Forward_List_t*> forward_list);

    public:
        Node_t head; // 0

    public:
        Forward_List_t();
        Forward_List_t(const T& head_value);
        Forward_List_t(T&& head_value);
        Forward_List_t(const Forward_List_t& other)                 = delete;
        Forward_List_t(Forward_List_t&& other) noexcept             = delete;
        Forward_List_t& operator=(const Forward_List_t& other)      = delete;
        Forward_List_t& operator=(Forward_List_t&& other) noexcept  = delete;
        ~Forward_List_t();

    public:
        Bool_t      Is_Empty();
        maybe<T*>   Point(size_t index);
        Bool_t      Has(const T& value);
        void        Add(const T& value);
        Bool_t      Remove(const T& value);
        Bool_t      Remove(T&& value);

    public:
        void Log(std::string indent = "");
    };
    STATIC_ASSERT(sizeof(Forward_List_t<void*>) == 0x10);

    template <typename T>
    class Forward_List_Logger_t
    {
    public:
        static void Log(Forward_List_t<T>& forward_list, std::string indent = "") = delete;
    };

    template <typename T>
    class Forward_List_Logger_t<T*>
    {
    public:
        static void Log(Forward_List_t<T*>& forward_list, std::string indent = "");
    };

    template <typename T>
    class Forward_List_Logger_t<maybe<T*>>
    {
    public:
        static void Log(Forward_List_t<maybe<T*>>& forward_list, std::string indent = "");
    };

    template <typename T>
    class Forward_List_Logger_t<some<T*>>
    {
    public:
        static void Log(Forward_List_t<some<T*>>& forward_list, std::string indent = "");
    };

    template <typename T>
    using List_t = Forward_List_t<T>;

}
