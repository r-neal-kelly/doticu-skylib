/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_array.h"
#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_object.h"
#include "doticu_skylib/virtual_function.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.h"

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

    #define DEFINE_TYPED_VARIABLE(TYPE_, NAME_)                     \
    SKYLIB_M                                                        \
        using namespace doticu_skylib;                              \
        using namespace doticu_skylib::Virtual;                     \
                                                                    \
        static const String_t name = String_t(NAME_);               \
        SKYLIB_ASSERT(name);                                        \
                                                                    \
        TYPE_* var = static_cast<TYPE_*>(Object()->Variable(name)); \
        SKYLIB_ASSERT(var);                                         \
        return var;                                                 \
    SKYLIB_W

    #define DEFINE_VARIABLE(NAME_)              DEFINE_TYPED_VARIABLE(Variable_t, NAME_)
    #define DEFINE_BOOL_VARIABLE(NAME_)         DEFINE_TYPED_VARIABLE(Bool_Variable_t, NAME_)
    #define DEFINE_INT_VARIABLE(NAME_)          DEFINE_TYPED_VARIABLE(Int_Variable_t, NAME_)
    #define DEFINE_STRING_VARIABLE(NAME_)       DEFINE_TYPED_VARIABLE(String_Variable_t, NAME_)
    #define DEFINE_ARRAY_VARIABLE(TYPE_, NAME_) DEFINE_TYPED_VARIABLE(Array_Variable_t<TYPE_>, NAME_)

    #define DEFINE_TYPED_PROPERTY(TYPE_, NAME_)                         \
    SKYLIB_M                                                            \
        using String_t = doticu_skylib::String_t;                       \
        using TYPE_ = doticu_skylib::Virtual::TYPE_;                    \
                                                                        \
        static const String_t name = String_t(NAME_);                   \
        SKYLIB_ASSERT(name);                                            \
                                                                        \
        TYPE_* prop = static_cast<TYPE_*>(Object()->Property(name));    \
        SKYLIB_ASSERT(prop);                                            \
        return prop;                                                    \
    SKYLIB_W

    #define DEFINE_PROPERTY(NAME_)          DEFINE_TYPED_PROPERTY(Variable_t, NAME_)
    #define DEFINE_STRING_PROPERTY(NAME_)   DEFINE_TYPED_PROPERTY(String_Property_t, NAME_)

    #define BIND_METHOD(VM_, CLASS_NAME_, BASE_, METHOD_NAME_, ARG_COUNT_, RETURN_, METHOD_, ...)   \
    SKYLIB_M                                                                                        \
        namespace Virtual = doticu_skylib::Virtual;                                                 \
                                                                                                    \
        auto method_ = Virtual::Forward_Method<RETURN_, BASE_, __VA_ARGS__, &BASE_::METHOD_>();     \
        VM_->Bind_Function(                                                                         \
            new NativeFunction##ARG_COUNT_ <BASE_, RETURN_, __VA_ARGS__>(                           \
                METHOD_NAME_, CLASS_NAME_, method_, reinterpret_cast<Virtual::Registry_t*>(VM_)     \
            )                                                                                       \
        );                                                                                          \
    SKYLIB_W

    #define BIND_LATENT_METHOD(VM_, CLASS_NAME_, BASE_, METHOD_NAME_, ARG_COUNT_, RETURN_, METHOD_, ...)    \
    SKYLIB_M                                                                                                \
        namespace Virtual = doticu_skylib::Virtual;                                                         \
                                                                                                            \
        auto method_ = Virtual::Forward_Latent_Method<BASE_, __VA_ARGS__, &BASE_::METHOD_>();               \
        VM_->Bind_Function(                                                                                 \
            new LatentNativeFunction##ARG_COUNT_ <BASE_, RETURN_, __VA_ARGS__>(                             \
                METHOD_NAME_, CLASS_NAME_, method_, reinterpret_cast<Virtual::Registry_t*>(VM_)             \
            )                                                                                               \
        );                                                                                                  \
    SKYLIB_W

    #define BIND_STATIC(VM_, CLASS_NAME_, STATIC_NAME_, ARG_COUNT_, RETURN_, STATIC_, ...)      \
    SKYLIB_M                                                                                    \
        namespace Virtual = doticu_skylib::Virtual;                                             \
                                                                                                \
        auto static_ = Virtual::Forward_Static<RETURN_, __VA_ARGS__, &STATIC_>();               \
        VM_->Bind_Function(                                                                     \
            new NativeFunction##ARG_COUNT_ <StaticFunctionTag, RETURN_, __VA_ARGS__>(           \
                STATIC_NAME_, CLASS_NAME_, static_, reinterpret_cast<Virtual::Registry_t*>(VM_) \
            )                                                                                   \
        );                                                                                      \
    SKYLIB_W

    #define BIND_LATENT_STATIC(VM_, CLASS_NAME_, STATIC_NAME_, ARG_COUNT_, RETURN_, STATIC_, ...)   \
    SKYLIB_M                                                                                        \
        namespace Virtual = doticu_skylib::Virtual;                                                 \
                                                                                                    \
        auto static_ = Virtual::Forward_Latent_Static<__VA_ARGS__, &STATIC_>();                     \
        VM_->Bind_Function(                                                                         \
            new LatentNativeFunction##ARG_COUNT_ <StaticFunctionTag, RETURN_, __VA_ARGS__>(         \
                STATIC_NAME_, CLASS_NAME_, static_, reinterpret_cast<Virtual::Registry_t*>(VM_)     \
            )                                                                                       \
        );                                                                                          \
    SKYLIB_W

}}
