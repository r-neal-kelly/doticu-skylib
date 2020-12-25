/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

#include "doticu_skylib/virtual.h"

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
