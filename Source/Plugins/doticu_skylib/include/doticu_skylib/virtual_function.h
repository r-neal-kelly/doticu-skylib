/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_type.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib { namespace Virtual {

    class Machine_t;

    template <
        typename Return_t, typename Base_t,
        Return_t(Base_t::* method)()
    > auto Forward_Method()
    {
        return [](Base_t* base)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)();
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A,
        Return_t(Base_t::* method)(A)
    > auto Forward_Method()
    {
        return [](Base_t* base, A a)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(a);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B,
        Return_t(Base_t::* method)(A, B)
    > auto Forward_Method()
    {
        return [](Base_t* base, A a, B b)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(a, b);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C,
        Return_t(Base_t::* method)(A, B, C)
    > auto Forward_Method()
    {
        return [](Base_t* base, A a, B b, C c)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(a, b, c);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D,
        Return_t(Base_t::* method)(A, B, C, D)
    > auto Forward_Method()
    {
        return [](Base_t* base, A a, B b, C c, D d)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(a, b, c, d);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E,
        Return_t(Base_t::* method)(A, B, C, D, E)
    > auto Forward_Method()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(a, b, c, d, e);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F,
        Return_t(Base_t::* method)(A, B, C, D, E, F)
    > auto Forward_Method()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e, F f)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(a, b, c, d, e, f);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G,
        Return_t(Base_t::* method)(A, B, C, D, E, F, G)
    > auto Forward_Method()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e, F f, G g)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(a, b, c, d, e, f, g);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H,
        Return_t(Base_t::* method)(A, B, C, D, E, F, G, H)
    > auto Forward_Method()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e, F f, G g, H h)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(a, b, c, d, e, f, g, h);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I,
        Return_t(Base_t::* method)(A, B, C, D, E, F, G, H, I)
    > auto Forward_Method()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e, F f, G g, H h, I i)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(a, b, c, d, e, f, g, h, i);
        };
    }

    template <
        typename Return_t, typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J,
        Return_t(Base_t::* method)(A, B, C, D, E, F, G, H, I, J)
    > auto Forward_Method()
    {
        return [](Base_t* base, A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)->Return_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(a, b, c, d, e, f, g, h, i, j);
        };
    }

    template <
        typename Base_t,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id);
        };
    }

    template <
        typename Base_t,
        typename A,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t, A)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base, A a)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id,
                                   a);
        };
    }

    template <
        typename Base_t,
        typename A, typename B,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t, A, B)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base, A a, B b)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id,
                                   a, b);
        };
    }

    template <
        typename Base_t,
        typename A, typename B, typename C,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t, A, B, C)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base, A a, B b, C c)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id,
                                   a, b, c);
        };
    }

    template <
        typename Base_t,
        typename A, typename B, typename C, typename D,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t, A, B, C, D)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base, A a, B b, C c, D d)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id,
                                   a, b, c, d);
        };
    }

    template <
        typename Base_t,
        typename A, typename B, typename C, typename D, typename E,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t, A, B, C, D, E)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base, A a, B b, C c, D d, E e)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id,
                                   a, b, c, d, e);
        };
    }

    template <
        typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t, A, B, C, D, E, F)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base, A a, B b, C c, D d, E e, F f)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id,
                                   a, b, c, d, e, f);
        };
    }

    template <
        typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t, A, B, C, D, E, F, G)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base, A a, B b, C c, D d, E e, F f, G g)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id,
                                   a, b, c, d, e, f, g);
        };
    }

    template <
        typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t, A, B, C, D, E, F, G, H)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base, A a, B b, C c, D d, E e, F f, G g, H h)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id,
                                   a, b, c, d, e, f, g, h);
        };
    }

    template <
        typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t, A, B, C, D, E, F, G, H, I)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base, A a, B b, C c, D d, E e, F f, G g, H h, I i)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id,
                                   a, b, c, d, e, f, g, h, i);
        };
    }

    template <
        typename Base_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J,
        Bool_t(Base_t::* method)(Machine_t*, Stack_ID_t, A, B, C, D, E, F, G, H, I, J)
    > auto Forward_Latent_Method()
    {
        return [](Registry_t* registry, UInt32 stack_id, Base_t* base, A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)->Bool_t
        {
            SKYLIB_ASSERT(base);
            return (base->*method)(reinterpret_cast<Machine_t*>(registry), stack_id,
                                   a, b, c, d, e, f, g, h, i, j);
        };
    }

    template <
        typename Return_t,
        Return_t(*static_)()
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*)->Return_t
        {
            return static_();
        };
    }

    template <
        typename Return_t,
        typename A,
        Return_t(*static_)(A)
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*, A a)->Return_t
        {
            return static_(a);
        };
    }

    template <
        typename Return_t,
        typename A, typename B,
        Return_t(*static_)(A, B)
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*, A a, B b)->Return_t
        {
            return static_(a, b);
        };
    }

    template <
        typename Return_t,
        typename A, typename B, typename C,
        Return_t(*static_)(A, B, C)
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*, A a, B b, C c)->Return_t
        {
            return static_(a, b, c);
        };
    }

    template <
        typename Return_t,
        typename A, typename B, typename C, typename D,
        Return_t(*static_)(A, B, C, D)
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*, A a, B b, C c, D d)->Return_t
        {
            return static_(a, b, c, d);
        };
    }

    template <
        typename Return_t,
        typename A, typename B, typename C, typename D, typename E,
        Return_t(*static_)(A, B, C, D, E)
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*, A a, B b, C c, D d, E e)->Return_t
        {
            return static_(a, b, c, d, e);
        };
    }

    template <
        typename Return_t,
        typename A, typename B, typename C, typename D, typename E, typename F,
        Return_t(*static_)(A, B, C, D, E, F)
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*, A a, B b, C c, D d, E e, F f)->Return_t
        {
            return static_(a, b, c, d, e, f);
        };
    }

    template <
        typename Return_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G,
        Return_t(*static_)(A, B, C, D, E, F, G)
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*, A a, B b, C c, D d, E e, F f, G g)->Return_t
        {
            return static_(a, b, c, d, e, f, g);
        };
    }

    template <
        typename Return_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H,
        Return_t(*static_)(A, B, C, D, E, F, G, H)
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*, A a, B b, C c, D d, E e, F f, G g, H h)->Return_t
        {
            return static_(a, b, c, d, e, f, g, h);
        };
    }

    template <
        typename Return_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I,
        Return_t(*static_)(A, B, C, D, E, F, G, H, I)
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*, A a, B b, C c, D d, E e, F f, G g, H h, I i)->Return_t
        {
            return static_(a, b, c, d, e, f, g, h, i);
        };
    }

    template <
        typename Return_t,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J,
        Return_t(*static_)(A, B, C, D, E, F, G, H, I, J)
    > auto Forward_Static()
    {
        return [](StaticFunctionTag*, A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)->Return_t
        {
            return static_(a, b, c, d, e, f, g, h, i, j);
        };
    }

    template <
        Bool_t(*static_)(Machine_t*, Stack_ID_t)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id);
        };
    }

    template <
        typename A,
        Bool_t(*static_)(Machine_t*, Stack_ID_t, A)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*, A a)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id,
                           a);
        };
    }

    template <
        typename A, typename B,
        Bool_t(*static_)(Machine_t*, Stack_ID_t, A, B)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*, A a, B b)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id,
                           a, b);
        };
    }

    template <
        typename A, typename B, typename C,
        Bool_t(*static_)(Machine_t*, Stack_ID_t, A, B, C)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*, A a, B b, C c)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id,
                           a, b, c);
        };
    }

    template <
        typename A, typename B, typename C, typename D,
        Bool_t(*static_)(Machine_t*, Stack_ID_t, A, B, C, D)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*, A a, B b, C c, D d)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id,
                           a, b, c, d);
        };
    }

    template <
        typename A, typename B, typename C, typename D, typename E,
        Bool_t(*static_)(Machine_t*, Stack_ID_t, A, B, C, D, E)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*, A a, B b, C c, D d, E e)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id,
                           a, b, c, d, e);
        };
    }

    template <
        typename A, typename B, typename C, typename D, typename E, typename F,
        Bool_t(*static_)(Machine_t*, Stack_ID_t, A, B, C, D, E, F)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*, A a, B b, C c, D d, E e, F f)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id,
                           a, b, c, d, e, f);
        };
    }

    template <
        typename A, typename B, typename C, typename D, typename E, typename F, typename G,
        Bool_t(*static_)(Machine_t*, Stack_ID_t, A, B, C, D, E, F, G)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*, A a, B b, C c, D d, E e, F f, G g)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id,
                           a, b, c, d, e, f, g);
        };
    }

    template <
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H,
        Bool_t(*static_)(Machine_t*, Stack_ID_t, A, B, C, D, E, F, G, H)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*, A a, B b, C c, D d, E e, F f, G g, H h)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id,
                           a, b, c, d, e, f, g, h);
        };
    }

    template <
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I,
        Bool_t(*static_)(Machine_t*, Stack_ID_t, A, B, C, D, E, F, G, H, I)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*, A a, B b, C c, D d, E e, F f, G g, H h, I i)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id,
                           a, b, c, d, e, f, g, h, i);
        };
    }

    template <
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J,
        Bool_t(*static_)(Machine_t*, Stack_ID_t, A, B, C, D, E, F, G, H, I, J)
    > auto Forward_Latent_Static()
    {
        return [](Registry_t* registry, UInt32 stack_id, StaticFunctionTag*, A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)->Bool_t
        {
            return static_(reinterpret_cast<Machine_t*>(registry), stack_id,
                           a, b, c, d, e, f, g, h, i, j);
        };
    }

}}

template <>
inline UInt64 GetTypeID<doticu_skylib::String_t>(VMClassRegistry* registry)
{
    return static_cast<UInt64>(doticu_skylib::Virtual::Type_e::STRING);
}

template <>
inline void PackValue<doticu_skylib::String_t>(VMValue* destination, doticu_skylib::String_t* source, VMClassRegistry* registry)
{
    destination->SetString(source->data);
}

template <>
inline void UnpackValue<doticu_skylib::String_t>(doticu_skylib::String_t* destination, VMValue* source)
{
    using Type_e = doticu_skylib::Virtual::Type_e;
    using Variable_t = doticu_skylib::Virtual::Variable_t;

    Variable_t* source_variable = reinterpret_cast<Variable_t*>(source);
    if (source_variable->type == Type_e::STRING) {
        destination->Value(source_variable->String());
    } else {
        destination->Value("");
    }
}

template <>
inline void PackValue<doticu_skylib::Int_t>(VMValue* destination, doticu_skylib::Int_t* source, VMClassRegistry* registry)
{
    destination->SetInt(*source);
}

template <>
inline void UnpackValue<doticu_skylib::Int_t>(doticu_skylib::Int_t* destination, VMValue* source)
{
    if (source->type == VMValue::kType_Int) {
        *destination = source->data.u;
    } else if (source->type == VMValue::kType_Float) {
        *destination = source->data.f;
    } else if (source->type == VMValue::kType_Bool) {
        *destination = source->data.b;
    } else {
        *destination = 0;
    }
}

#include "doticu_skylib/keyword.h"
#include "doticu_skylib/reference.h"

template <>
inline UInt64 GetTypeID<doticu_skylib::Vector_t<doticu_skylib::Int_t>>(VMClassRegistry*)
{
    return doticu_skylib::Virtual::Type_e::INT_ARRAY;
}

template <>
inline UInt64 GetTypeID<doticu_skylib::Vector_t<doticu_skylib::Keyword_t*>>(VMClassRegistry*)
{
    return doticu_skylib::Virtual::Type_e(doticu_skylib::Keyword_t::SCRIPT_TYPE).As_Array().mangled;
}

template <>
inline UInt64 GetTypeID<doticu_skylib::Vector_t<doticu_skylib::Reference_t*>>(VMClassRegistry*)
{
    return doticu_skylib::Virtual::Type_e(doticu_skylib::Reference_t::SCRIPT_TYPE).As_Array().mangled;
}

template <typename T>
inline void PackValue(VMValue* destination, doticu_skylib::Vector_t<T*>* source, VMClassRegistry* registry)
{
    PackValue(destination, reinterpret_cast<VMResultArray<T*>*>(source), registry);
}

#define DEFINE_UNPACK_VECTOR(TYPE_)                                                                                     \
template <>                                                                                                             \
inline void UnpackValue<doticu_skylib::Vector_t<TYPE_>>(doticu_skylib::Vector_t<TYPE_>* destination, VMValue* source)   \
{                                                                                                                       \
    if (destination && source) {                                                                                        \
        reinterpret_cast<doticu_skylib::Virtual::Variable_t*>(source)->Unpack_Array(*destination);                      \
    }                                                                                                                   \
}

DEFINE_UNPACK_VECTOR(doticu_skylib::Int_t);
DEFINE_UNPACK_VECTOR(doticu_skylib::Keyword_t*);
DEFINE_UNPACK_VECTOR(doticu_skylib::Reference_t*);

#undef DEFINE_UNPACK_VECTOR
