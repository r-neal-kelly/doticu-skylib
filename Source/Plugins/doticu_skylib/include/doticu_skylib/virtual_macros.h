/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/utils.h"
#include "doticu_skylib/virtual_class.h"
#include "doticu_skylib/virtual_object.h"
#include "doticu_skylib/virtual_function.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    #define DEFINE_CLASS_NAME(NAME_)                \
    M                                               \
        using String_t = doticu_skylib::String_t;   \
                                                    \
        static const String_t class_name = NAME_;   \
        SKYLIB_ASSERT(class_name);                  \
        return class_name;                          \
    W

    #define DEFINE_CLASS()                                              \
    M                                                                   \
        using Class_t = doticu_skylib::Virtual::Class_t;                \
                                                                        \
        static Class_t* class_ = Class_t::Fetch(Class_Name(), false);   \
        SKYLIB_ASSERT(class_);                                          \
        return class_;                                                  \
    W

    #define DEFINE_OBJECT()                                             \
    M                                                                   \
        using Object_t = doticu_skylib::Virtual::Object_t;              \
                                                                        \
        Object_t* object = Object_t::Fetch(this, Class_Name(), true);   \
        SKYLIB_ASSERT(object);                                          \
        return object;                                                  \
    W

    #define DEFINE_TYPED_VARIABLE(TYPE_, NAME_)                     \
    M                                                               \
        using String_t = doticu_skylib::String_t;                   \
        using TYPE_ = doticu_skylib::Virtual::TYPE_;                \
                                                                    \
        static const String_t name = String_t(NAME_);               \
        SKYLIB_ASSERT(name);                                        \
                                                                    \
        TYPE_* var = static_cast<TYPE_*>(Object()->Variable(name)); \
        SKYLIB_ASSERT(var);                                         \
        return var;                                                 \
    W

    #define DEFINE_VARIABLE(NAME_)          DEFINE_TYPED_VARIABLE(Variable_t, NAME_)
    #define DEFINE_BOOL_VARIABLE(NAME_)     DEFINE_TYPED_VARIABLE(Bool_Variable_t, NAME_)
    #define DEFINE_INT_VARIABLE(NAME_)      DEFINE_TYPED_VARIABLE(Int_Variable_t, NAME_)
    #define DEFINE_STRING_VARIABLE(NAME_)   DEFINE_TYPED_VARIABLE(String_Variable_t, NAME_)

    #define DEFINE_TYPED_PROPERTY(TYPE_, NAME_)                         \
    M                                                                   \
        using String_t = doticu_skylib::String_t;                       \
        using TYPE_ = doticu_skylib::Virtual::TYPE_;                    \
                                                                        \
        static const String_t name = String_t(NAME_);                   \
        SKYLIB_ASSERT(name);                                            \
                                                                        \
        TYPE_* prop = static_cast<TYPE_*>(Object()->Property(name));    \
        SKYLIB_ASSERT(prop);                                            \
        return prop;                                                    \
    W

    #define DEFINE_PROPERTY(NAME_)          DEFINE_TYPED_PROPERTY(Variable_t, NAME_)
    #define DEFINE_STRING_PROPERTY(NAME_)   DEFINE_TYPED_PROPERTY(String_Property_t, NAME_)

    #define BIND_METHOD(VM_, STR_CLASS_, TYPE_, STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)     \
    M                                                                                           \
        namespace Virtual = doticu_skylib::Virtual;                                             \
                                                                                                \
        auto METHOD_ = Virtual::Forward<RETURN_, TYPE_, __VA_ARGS__, &TYPE_::METHOD_>();        \
        VM_->Bind_Function(                                                                     \
            new NativeFunction##ARG_NUM_ <TYPE_, RETURN_, __VA_ARGS__>(                         \
                STR_FUNC_, STR_CLASS_, METHOD_, reinterpret_cast<Virtual::Registry_t*>(VM_)     \
            )                                                                                   \
        );                                                                                      \
    W

    #define BIND_LATENT_METHOD(VM_, STR_CLASS_, TYPE_, STR_FUNC_, ARG_NUM_, RETURN_, METHOD_, ...)      \
    M                                                                                                   \
        namespace Virtual = doticu_skylib::Virtual;                                                     \
                                                                                                        \
        auto METHOD_ = Virtual::Forward_Latent<TYPE_, __VA_ARGS__, &TYPE_::METHOD_>();                  \
        VM_->Bind_Function(                                                                             \
            new LatentNativeFunction##ARG_NUM_ <TYPE_, RETURN_, __VA_ARGS__>(                           \
                STR_FUNC_, STR_CLASS_, METHOD_, reinterpret_cast<Virtual::Registry_t*>(VM_)             \
            )                                                                                           \
        );                                                                                              \
    W

    #define BIND_GLOBAL

    #define BIND_LATENT_GLOBAL

}}
