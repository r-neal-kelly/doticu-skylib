/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_array.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_object.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_method.h"
#include "doticu_skylib/virtual_static.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib { namespace Virtual {

    #define DEFINE_CLASS_NAME(NAME_)                \
    SKYLIB_M                                        \
        using String_t = doticu_skylib::String_t;   \
                                                    \
        static const String_t class_name = NAME_;   \
        SKYLIB_ASSERT(class_name);                  \
        return class_name;                          \
    SKYLIB_W

    #define DEFINE_CLASS()                                              \
    SKYLIB_M                                                            \
        using Class_t = doticu_skylib::Virtual::Class_t;                \
                                                                        \
        static Class_t* class_ = Class_t::Fetch(Class_Name(), false);   \
        SKYLIB_ASSERT(class_);                                          \
        return class_;                                                  \
    SKYLIB_W

    #define DEFINE_OBJECT()                                             \
    SKYLIB_M                                                            \
        using Object_t = doticu_skylib::Virtual::Object_t;              \
                                                                        \
        Object_t* object = Object_t::Fetch(this, Class_Name(), true);   \
        SKYLIB_ASSERT(object);                                          \
        return object;                                                  \
    SKYLIB_W

    #define DEFINE_VARIABLE_POINTER(TYPE_, NAME_)                   \
    SKYLIB_M                                                        \
        using namespace doticu_skylib;                              \
        using namespace doticu_skylib::Virtual;                     \
                                                                    \
        static const String_t name = String_t(NAME_);               \
        SKYLIB_ASSERT(name);                                        \
                                                                    \
        Variable_tt<TYPE_>* var = static_cast<Variable_tt<TYPE_>*>  \
            (Object()->Variable(name));                             \
        return var;                                                 \
    SKYLIB_W

    #define DEFINE_VARIABLE_REFERENCE(TYPE_, NAME_)                 \
    SKYLIB_M                                                        \
        using namespace doticu_skylib;                              \
        using namespace doticu_skylib::Virtual;                     \
                                                                    \
        static const String_t name = String_t(NAME_);               \
        SKYLIB_ASSERT(name);                                        \
                                                                    \
        Variable_tt<TYPE_>* var = static_cast<Variable_tt<TYPE_>*>  \
            (Object()->Variable(name));                             \
        SKYLIB_ASSERT(var);                                         \
        return *var;                                                \
    SKYLIB_W

    #define BIND_METHOD(MACHINE_, CLASS_NAME_, BASE_TYPE_, METHOD_NAME_, RETURN_, METHOD_, ...)     \
    SKYLIB_M                                                                                        \
        namespace V = doticu_skylib::Virtual;                                                       \
        MACHINE_->Bind_Function(reinterpret_cast<V::Function_i*>(                                   \
            new V::Method_t<RETURN_, BASE_TYPE_, __VA_ARGS__>(CLASS_NAME_, METHOD_NAME_, &METHOD_)  \
        ));                                                                                         \
    SKYLIB_W

    #define BIND_STATIC(MACHINE_, CLASS_NAME_, STATIC_NAME_, RETURN_, STATIC_, ...)     \
    SKYLIB_M                                                                            \
        namespace V = doticu_skylib::Virtual;                                           \
        MACHINE_->Bind_Function(reinterpret_cast<V::Function_i*>(                       \
            new V::Static_t<RETURN_, __VA_ARGS__>(CLASS_NAME_, STATIC_NAME_, &STATIC_)  \
        ));                                                                             \
    SKYLIB_W

}}
