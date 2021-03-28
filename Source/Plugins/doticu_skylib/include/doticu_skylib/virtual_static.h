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
    > class Static_impl
    {
    public:
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I, typename J
    > class Static_impl<Callback_u, A, B, C, D, E, F, G, H, I, J>
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

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
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
                return_variable->Pack<Bool_t>(callback.latent(stack_id, a, b, c, d, e, f, g, h, i, j));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent, a, b, c, d, e, f, g, h, i, j);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)
        {
            return_variable->Pack<Return_t>(callback(a, b, c, d, e, f, g, h, i, j));
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h, I i, J j)
        {
            callback(a, b, c, d, e, f, g, h, i, j);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H, typename I
    > class Static_impl<Callback_u, A, B, C, D, E, F, G, H, I>
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

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
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
                return_variable->Pack<Bool_t>(callback.latent(stack_id, a, b, c, d, e, f, g, h, i));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent, a, b, c, d, e, f, g, h, i);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h, I i)
        {
            return_variable->Pack<Return_t>(callback(a, b, c, d, e, f, g, h, i));
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h, I i)
        {
            callback(a, b, c, d, e, f, g, h, i);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G, typename H
    > class Static_impl<Callback_u, A, B, C, D, E, F, G, H>
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

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
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
                return_variable->Pack<Bool_t>(callback.latent(stack_id, a, b, c, d, e, f, g, h));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent, a, b, c, d, e, f, g, h);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h)
        {
            return_variable->Pack<Return_t>(callback(a, b, c, d, e, f, g, h));
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g, H h)
        {
            callback(a, b, c, d, e, f, g, h);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E, typename F, typename G
    > class Static_impl<Callback_u, A, B, C, D, E, F, G>
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

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
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
                return_variable->Pack<Bool_t>(callback.latent(stack_id, a, b, c, d, e, f, g));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent, a, b, c, d, e, f, g);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g)
        {
            return_variable->Pack<Return_t>(callback(a, b, c, d, e, f, g));
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f, G g)
        {
            callback(a, b, c, d, e, f, g);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E, typename F
    > class Static_impl<Callback_u, A, B, C, D, E, F>
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

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();
            D d = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 3, args_offset))->Unpack<D>();
            E e = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 4, args_offset))->Unpack<E>();
            F f = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 5, args_offset))->Unpack<F>();

            if (is_latent) {
                return_variable->Pack<Bool_t>(callback.latent(stack_id, a, b, c, d, e, f));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent, a, b, c, d, e, f);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f)
        {
            return_variable->Pack<Return_t>(callback(a, b, c, d, e, f));
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e, F f)
        {
            callback(a, b, c, d, e, f);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D, typename E
    > class Static_impl<Callback_u, A, B, C, D, E>
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

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();
            D d = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 3, args_offset))->Unpack<D>();
            E e = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 4, args_offset))->Unpack<E>();

            if (is_latent) {
                return_variable->Pack<Bool_t>(callback.latent(stack_id, a, b, c, d, e));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent, a, b, c, d, e);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e)
        {
            return_variable->Pack<Return_t>(callback(a, b, c, d, e));
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d, E e)
        {
            callback(a, b, c, d, e);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C, typename D
    > class Static_impl<Callback_u, A, B, C, D>
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

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();
            D d = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 3, args_offset))->Unpack<D>();

            if (is_latent) {
                return_variable->Pack<Bool_t>(callback.latent(stack_id, a, b, c, d));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent, a, b, c, d);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d)
        {
            return_variable->Pack<Return_t>(callback(a, b, c, d));
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c, D d)
        {
            callback(a, b, c, d);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B, typename C
    > class Static_impl<Callback_u, A, B, C>
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

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();
            C c = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 2, args_offset))->Unpack<C>();

            if (is_latent) {
                return_variable->Pack<Bool_t>(callback.latent(stack_id, a, b, c));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent, a, b, c);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c)
        {
            return_variable->Pack<Return_t>(callback(a, b, c));
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b, C c)
        {
            callback(a, b, c);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A, typename B
    > class Static_impl<Callback_u, A, B>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
            parameter_types.data[1].type = Type_e::From<B>().Mangled();
        }

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();
            B b = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 1, args_offset))->Unpack<B>();

            if (is_latent) {
                return_variable->Pack<Bool_t>(callback.latent(stack_id, a, b));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent, a, b);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b)
        {
            return_variable->Pack<Return_t>(callback(a, b));
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a, B b)
        {
            callback(a, b);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u,
        typename A
    > class Static_impl<Callback_u, A>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();

            parameter_types.data[0].type = Type_e::From<A>().Mangled();
        }

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
        {
            u32 args_offset = CALL_MEMBER_FN(_state->argList, GetOffset)(_state);

            A a = reinterpret_cast<Variable_t*>(CALL_MEMBER_FN(_state->argList, Get)(_state, 0, args_offset))->Unpack<A>();

            if (is_latent) {
                return_variable->Pack<Bool_t>(callback.latent(stack_id, a));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent, a);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a)
        {
            return_variable->Pack<Return_t>(callback(a));
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback,
                                         A a)
        {
            callback(a);
            return_variable->Pack<Return_t>();
        }
    };

    template <
        typename Callback_u
    > class Static_impl<Callback_u>
    {
    public:
        template <typename Return_t>
        static inline void Init(u64& return_type, NativeFunctionBase::ParameterInfo& parameter_types)
        {
            return_type = Type_e::From<Return_t>().Mangled();
        }

        template <typename Return_t>
        static inline void Run(VMState* _state, Bool_t is_latent, Raw_Stack_ID_t stack_id, Variable_t* return_variable, Callback_u callback)
        {
            if (is_latent) {
                return_variable->Pack<Bool_t>(callback.latent(stack_id));
            } else {
                Pack_Return<Return_t>(return_variable, callback.unlatent);
            }
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<!std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback)
        {
            return_variable->Pack<Return_t>(callback());
        }

        template <
            typename Return_t, typename Callback_f,
            std::enable_if_t<std::is_void<Return_t>::value, Bool_t> = true
        > static inline void Pack_Return(Variable_t* return_variable, Callback_f callback)
        {
            callback();
            return_variable->Pack<Return_t>();
        }
    };

    // Return_t needs to be the actual return, whether latent or not.
    // Latent functions must take a Stack_ID_t as the first argument.
    template <typename Return_t, typename ...Ts>
    class Static_t : public NativeFunction
    {
    public:
        using Callback_f = Return_t(*)(Ts...);
        using Latent_Callback_f = Bool_t(*)(Stack_ID_t, Ts...);
        union Callback_u { void* data; Callback_f unlatent; Latent_Callback_f latent; };
        using Impl_t = Static_impl<Callback_u, Ts...>;

    public:
        virtual ~Static_t() = default;

        Callback_u callback;

        Static_t(const char* class_name, const char* method_name, Callback_f unlatent_callback) :
            NativeFunction(method_name, class_name, true, sizeof...(Ts))
        {
            SKYLIB_ASSERT(unlatent_callback);

            m_isLatent = 0;
            callback.unlatent = unlatent_callback;
            Impl_t::Init<Return_t>(m_retnType, m_params);
        }

        Static_t(const char* class_name, const char* method_name, Latent_Callback_f latent_callback) :
            NativeFunction(method_name, class_name, true, sizeof...(Ts))
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
            Impl_t::Run<Return_t>(_state, Is_Latent(), stack_id, reinterpret_cast<Variable_t*>(_return), callback);
            return true;
        }
    };

}}
