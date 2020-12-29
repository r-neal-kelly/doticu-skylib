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
#include "doticu_skylib/virtual_function.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_skse.h"
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

    #define BIND_METHOD(VM_, CLASS_NAME_, BASE_, METHOD_NAME_, ARG_COUNT_, RETURN_, METHOD_, ...)   \
    SKYLIB_M                                                                                        \
        namespace Virtual = doticu_skylib::Virtual;                                                 \
                                                                                                    \
        auto method_ = Virtual::Forward_Method<RETURN_, BASE_, __VA_ARGS__, &BASE_::METHOD_>();     \
        VM_->Bind_Function(reinterpret_cast<Virtual::Function_i*>(                                  \
            new NativeFunction##ARG_COUNT_ <BASE_, RETURN_, __VA_ARGS__>(                           \
                METHOD_NAME_, CLASS_NAME_, method_, reinterpret_cast<VMClassRegistry*>(VM_)         \
            )                                                                                       \
        ));                                                                                         \
    SKYLIB_W

    #define BIND_LATENT_METHOD(VM_, CLASS_NAME_, BASE_, METHOD_NAME_, ARG_COUNT_, RETURN_, METHOD_, ...)    \
    SKYLIB_M                                                                                                \
        namespace Virtual = doticu_skylib::Virtual;                                                         \
                                                                                                            \
        auto method_ = Virtual::Forward_Latent_Method<BASE_, __VA_ARGS__, &BASE_::METHOD_>();               \
        VM_->Bind_Function(reinterpret_cast<Virtual::Function_i*>(                                          \
            new LatentNativeFunction##ARG_COUNT_ <BASE_, RETURN_, __VA_ARGS__>(                             \
                METHOD_NAME_, CLASS_NAME_, method_, reinterpret_cast<VMClassRegistry*>(VM_)                 \
            )                                                                                               \
        ));                                                                                                 \
    SKYLIB_W

    #define BIND_STATIC(VM_, CLASS_NAME_, STATIC_NAME_, ARG_COUNT_, RETURN_, STATIC_, ...)  \
    SKYLIB_M                                                                                \
        namespace Virtual = doticu_skylib::Virtual;                                         \
                                                                                            \
        auto static_ = Virtual::Forward_Static<RETURN_, __VA_ARGS__, &STATIC_>();           \
        VM_->Bind_Function(reinterpret_cast<Virtual::Function_i*>(                          \
            new NativeFunction##ARG_COUNT_ <StaticFunctionTag, RETURN_, __VA_ARGS__>(       \
                STATIC_NAME_, CLASS_NAME_, static_, reinterpret_cast<VMClassRegistry*>(VM_) \
            )                                                                               \
        ));                                                                                 \
    SKYLIB_W

    #define BIND_LATENT_STATIC(VM_, CLASS_NAME_, STATIC_NAME_, ARG_COUNT_, RETURN_, STATIC_, ...)   \
    SKYLIB_M                                                                                        \
        namespace Virtual = doticu_skylib::Virtual;                                                 \
                                                                                                    \
        auto static_ = Virtual::Forward_Latent_Static<__VA_ARGS__, &STATIC_>();                     \
        VM_->Bind_Function(reinterpret_cast<Virtual::Function_i*>(                                  \
            new LatentNativeFunction##ARG_COUNT_ <StaticFunctionTag, RETURN_, __VA_ARGS__>(         \
                STATIC_NAME_, CLASS_NAME_, static_, reinterpret_cast<VMClassRegistry*>(VM_)         \
            )                                                                                       \
        ));                                                                                         \
    SKYLIB_W

}}
