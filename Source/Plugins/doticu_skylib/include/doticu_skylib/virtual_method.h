/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusNativeFunctions.h"

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_stack_id.h"

namespace doticu_skylib { namespace Virtual {

    template <
        typename Callback_u,
        typename A = void,
        typename B = void,
        typename C = void,
        typename D = void,
        typename E = void,
        typename F = void,
        typename G = void,
        typename H = void,
        typename I = void,
        typename J = void,
        typename K = void
    > class Method_impl
    {
    public:
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J
    > class Method_impl<Callback_u, A, B, C, D, E, F, G, H, I, J>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
            parameter_types.data[1].type = Type_e::From<B>().Mangled();
            parameter_types.data[2].type = Type_e::From<C>().Mangled();
            parameter_types.data[3].type = Type_e::From<D>().Mangled();
            parameter_types.data[4].type = Type_e::From<E>().Mangled();
            parameter_types.data[5].type = Type_e::From<F>().Mangled();
            parameter_types.data[6].type = Type_e::From<G>().Mangled();
            parameter_types.data[7].type = Type_e::From<H>().Mangled();
            parameter_types.data[8].type = Type_e::From<I>().Mangled();
            parameter_types.data[9].type = Type_e::From<J>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();
            D d = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 3, args_offset))->Unpack<D>();
            E e = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 4, args_offset))->Unpack<E>();
            F f = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 5, args_offset))->Unpack<F>();
            G g = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 6, args_offset))->Unpack<G>();
            H h = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 7, args_offset))->Unpack<H>();
            I i = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 8, args_offset))->Unpack<I>();
            J j = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 9, args_offset))->Unpack<J>();

            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id, a, b, c, d, e, f, g, h, i, j));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent, a, b, c, d, e, f, g, h, i, j);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)
        {
            return_variable->Pack<Return_t>((base->*callback)(a, b, c, d, e, f, g, h, i, j));
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)
        {
            (base->*callback)(a, b, c, d, e, f, g, h, i, j);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I
    > class Method_impl<Callback_u, A, B, C, D, E, F, G, H, I>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
            parameter_types.data[1].type = Type_e::From<B>().Mangled();
            parameter_types.data[2].type = Type_e::From<C>().Mangled();
            parameter_types.data[3].type = Type_e::From<D>().Mangled();
            parameter_types.data[4].type = Type_e::From<E>().Mangled();
            parameter_types.data[5].type = Type_e::From<F>().Mangled();
            parameter_types.data[6].type = Type_e::From<G>().Mangled();
            parameter_types.data[7].type = Type_e::From<H>().Mangled();
            parameter_types.data[8].type = Type_e::From<I>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();
            D d = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 3, args_offset))->Unpack<D>();
            E e = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 4, args_offset))->Unpack<E>();
            F f = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 5, args_offset))->Unpack<F>();
            G g = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 6, args_offset))->Unpack<G>();
            H h = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 7, args_offset))->Unpack<H>();
            I i = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 8, args_offset))->Unpack<I>();

            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id, a, b, c, d, e, f, g, h, i));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent, a, b, c, d, e, f, g, h, i);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h, I i)
        {
            return_variable->Pack<Return_t>((base->*callback)(a, b, c, d, e, f, g, h, i));
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h, I i)
        {
            (base->*callback)(a, b, c, d, e, f, g, h, i);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H
    > class Method_impl<Callback_u, A, B, C, D, E, F, G, H>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
            parameter_types.data[1].type = Type_e::From<B>().Mangled();
            parameter_types.data[2].type = Type_e::From<C>().Mangled();
            parameter_types.data[3].type = Type_e::From<D>().Mangled();
            parameter_types.data[4].type = Type_e::From<E>().Mangled();
            parameter_types.data[5].type = Type_e::From<F>().Mangled();
            parameter_types.data[6].type = Type_e::From<G>().Mangled();
            parameter_types.data[7].type = Type_e::From<H>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();
            D d = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 3, args_offset))->Unpack<D>();
            E e = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 4, args_offset))->Unpack<E>();
            F f = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 5, args_offset))->Unpack<F>();
            G g = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 6, args_offset))->Unpack<G>();
            H h = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 7, args_offset))->Unpack<H>();

            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id, a, b, c, d, e, f, g, h));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent, a, b, c, d, e, f, g, h);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h)
        {
            return_variable->Pack<Return_t>((base->*callback)(a, b, c, d, e, f, g, h));
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h)
        {
            (base->*callback)(a, b, c, d, e, f, g, h);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G
    > class Method_impl<Callback_u, A, B, C, D, E, F, G>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
            parameter_types.data[1].type = Type_e::From<B>().Mangled();
            parameter_types.data[2].type = Type_e::From<C>().Mangled();
            parameter_types.data[3].type = Type_e::From<D>().Mangled();
            parameter_types.data[4].type = Type_e::From<E>().Mangled();
            parameter_types.data[5].type = Type_e::From<F>().Mangled();
            parameter_types.data[6].type = Type_e::From<G>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();
            D d = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 3, args_offset))->Unpack<D>();
            E e = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 4, args_offset))->Unpack<E>();
            F f = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 5, args_offset))->Unpack<F>();
            G g = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 6, args_offset))->Unpack<G>();

            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id, a, b, c, d, e, f, g));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent, a, b, c, d, e, f, g);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g)
        {
            return_variable->Pack<Return_t>((base->*callback)(a, b, c, d, e, f, g));
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g)
        {
            (base->*callback)(a, b, c, d, e, f, g);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E, typename F
    > class Method_impl<Callback_u, A, B, C, D, E, F>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
            parameter_types.data[1].type = Type_e::From<B>().Mangled();
            parameter_types.data[2].type = Type_e::From<C>().Mangled();
            parameter_types.data[3].type = Type_e::From<D>().Mangled();
            parameter_types.data[4].type = Type_e::From<E>().Mangled();
            parameter_types.data[5].type = Type_e::From<F>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();
            D d = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 3, args_offset))->Unpack<D>();
            E e = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 4, args_offset))->Unpack<E>();
            F f = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 5, args_offset))->Unpack<F>();

            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id, a, b, c, d, e, f));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent, a, b, c, d, e, f);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f)
        {
            return_variable->Pack<Return_t>((base->*callback)(a, b, c, d, e, f));
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f)
        {
            (base->*callback)(a, b, c, d, e, f);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E
    > class Method_impl<Callback_u, A, B, C, D, E>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
            parameter_types.data[1].type = Type_e::From<B>().Mangled();
            parameter_types.data[2].type = Type_e::From<C>().Mangled();
            parameter_types.data[3].type = Type_e::From<D>().Mangled();
            parameter_types.data[4].type = Type_e::From<E>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();
            D d = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 3, args_offset))->Unpack<D>();
            E e = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 4, args_offset))->Unpack<E>();

            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id, a, b, c, d, e));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent, a, b, c, d, e);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e)
        {
            return_variable->Pack<Return_t>((base->*callback)(a, b, c, d, e));
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d, E e)
        {
            (base->*callback)(a, b, c, d, e);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D
    > class Method_impl<Callback_u, A, B, C, D>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
            parameter_types.data[1].type = Type_e::From<B>().Mangled();
            parameter_types.data[2].type = Type_e::From<C>().Mangled();
            parameter_types.data[3].type = Type_e::From<D>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();
            D d = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 3, args_offset))->Unpack<D>();

            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id, a, b, c, d));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent, a, b, c, d);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d)
        {
            return_variable->Pack<Return_t>((base->*callback)(a, b, c, d));
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c, D d)
        {
            (base->*callback)(a, b, c, d);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C
    > class Method_impl<Callback_u, A, B, C>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
            parameter_types.data[1].type = Type_e::From<B>().Mangled();
            parameter_types.data[2].type = Type_e::From<C>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();

            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id, a, b, c));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent, a, b, c);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c)
        {
            return_variable->Pack<Return_t>((base->*callback)(a, b, c));
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b, C c)
        {
            (base->*callback)(a, b, c);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B
    > class Method_impl<Callback_u, A, B>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
            parameter_types.data[1].type = Type_e::From<B>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();

            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id, a, b));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent, a, b);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b)
        {
            return_variable->Pack<Return_t>((base->*callback)(a, b));
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a, B b)
        {
            (base->*callback)(a, b);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A
    > class Method_impl<Callback_u, A>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();

            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id, a));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent, a);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a)
        {
            return_variable->Pack<Return_t>((base->*callback)(a));
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback,
                                         A a)
        {
            (base->*callback)(a);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u
    > class Method_impl<Callback_u>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();
        }

        template <typename Return_t, typename Base_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Base_t* base, Callback_u callback)
        {
            if (is_latent) {
                return_variable->Pack<Bool_t>((base->*callback.latent)(stack_id));
            } else {
                Pack_Return<Return_t>(return_variable, base, callback.unlatent);
            }
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback)
        {
            return_variable->Pack<Return_t>((base->*callback)());
        }

        template <
            typename Return_t, typename Base_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Base_t* base, Callback_f callback)
        {
            (base->*callback)();
            return_variable->Pack<Return_t>();
        }
    };

    // Return_t needs to be the actual return, whether latent or not.
    // Latent functions must take a Stack_ID_t as the first argument.
    template <typename Return_t, typename Base_t, typename ...Ts>
    class Method_t : public NativeFunction
    {
    public:
        using Callback_f = Return_t(Base_t::*)(Ts...);
        using Latent_Callback_f = Bool_t(Base_t::*)(Stack_ID_t, Ts...);
        union Callback_u { void* data; Callback_f unlatent; Latent_Callback_f latent; };
        using Impl_t = Method_impl<Callback_u, Ts...>;

    public:
        virtual ~Method_t() = default;

        Callback_u callback;

        Method_t(const char* class_name, const char* method_name, Callback_f unlatent_callback) :
            NativeFunction(method_name, class_name, false, sizeof...(Ts))
        {
            SKYLIB_ASSERT(unlatent_callback);

            m_isLatent = 0;
            callback.unlatent = unlatent_callback;
            Impl_t::Init<Return_t>(m_retnType, m_params);
        }

        Method_t(const char* class_name, const char* method_name, Latent_Callback_f latent_callback) :
            NativeFunction(method_name, class_name, false, sizeof...(Ts))
        {
            SKYLIB_ASSERT(latent_callback);

            m_isLatent = 1;
            callback.latent = latent_callback;
            Impl_t::Init<Return_t>(m_retnType, m_params);
        }

        Bool_t Is_Static() { return unk40 > 0; }
        Bool_t Is_Latent() { return m_isLatent > 0; }

        virtual Bool_t HasCallback() override
        {
            return true;
        }

        // until we write our own base class, we have to keep the UInt32 as well as the rest of the types here.
        virtual Bool_t Run(VMValue* _base, VMClassRegistry* _registry, UInt32 stack_id, VMValue* _return, VMState* _state) override
        {
            Base_t* base = reinterpret_cast<Variable_t*>(_base)->Unpack<Base_t*>();
            if (base) {
                Impl_t::Run<Return_t>(_state, Is_Latent(), stack_id, reinterpret_cast<Variable_t*>(_return), base, callback);
                return true;
            } else {
                return false;
            }
        }
    };

}}
