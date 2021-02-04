/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_collision_layer_type.h"
#include "doticu_skylib/enum_logic_gate.h"

#include "doticu_skylib/reference.h"

#include "doticu_skylib/filter.inl"

namespace doticu_skylib { namespace Filter {

    template <typename Filterable_t>
    class Collision_Layer_Types_t : public Filter_i<Filterable_t>
    {
    public:
        Collision_Layer_Types_t(State_c<Filterable_t>& state) :
            Filter_i<Filterable_t>(state)
        {
        }

        template <typename Filterable_a, typename Arg_a>
        class Compare_f
        {
        };

        template <>
        class Compare_f<some<Collision_Layer_Type_e>, some<Collision_Layer_Type_e>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Collision_Layer_Type_e> filterable, some<Collision_Layer_Type_e> collision_layer_type)
            {
                if (filterable() == collision_layer_type()) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <typename Arg_a>
        class Compare_f<maybe<Collision_Layer_Type_e>, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(maybe<Collision_Layer_Type_e> filterable, Arg_a arg_a)
            {
                if (filterable) {
                    return Compare_f::<some<Collision_Layer_Type_e>, Arg_a>::Run<MODE>(filterable(), arg_a);
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <typename Arg_a>
        class Compare_f<Collision_Layer_Type_e, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(Collision_Layer_Type_e filterable, Arg_a arg_a)
            {
                return Compare_f::<maybe<Collision_Layer_Type_e>, Arg_a>::Run<MODE>(filterable, arg_a);
            }
        };

        template <typename Arg_a>
        class Compare_f<some<Reference_t*>, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Reference_t*> filterable, Arg_a arg_a)
            {
                return Compare_f<maybe<Collision_Layer_Type_e>, Arg_a>::Run<MODE>(filterable->Collision_Layer_Type(), arg_a);
            }
        };

        template <>
        class Compare_f<some<Reference_t*>, Vector_t<some<Collision_Layer_Type_e>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::OR, Bool_t> = true>
            static Result_e Run(some<Reference_t*> filterable, Vector_t<some<Collision_Layer_Type_e>>& collision_layer_types)
            {
                maybe<Collision_Layer_Type_e> reference_collision_layer_type = filterable->Collision_Layer_Type();
                if (reference_collision_layer_type) {
                    for (size_t idx = 0, end = collision_layer_types.size(); idx < end; idx += 1) {
                        if (collision_layer_types[idx] == reference_collision_layer_type()) {
                            return Result_e::IS_MATCH;
                        }
                    }
                    return Result_e::ISNT_MATCH;
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <typename Arg_a>
        class Compare_f<maybe<Reference_t*>, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(maybe<Reference_t*> filterable, Arg_a arg_a)
            {
                if (filterable) {
                    return Compare_f<some<Reference_t*>, Arg_a>::Run<MODE>(filterable(), arg_a);
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <typename Arg_a>
        class Compare_f<Reference_t*, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(Reference_t* filterable, Arg_a arg_a)
            {
                return Compare_f<maybe<Reference_t*>, Arg_a>::Run<MODE>(filterable, arg_a);
            }
        };

        template <typename Arg_a>
        class Filter_f
        {
        };

        template <>
        class Filter_f<some<Collision_Layer_Type_e>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, some<Collision_Layer_Type_e> collision_layer_type, Bool_t do_negate)
            {
                SKYLIB_ASSERT_SOME(collision_layer_type);
                self->Filter<some<Collision_Layer_Type_e>>
                    (do_negate, collision_layer_type, &Compare_f<Filterable_t, some<Collision_Layer_Type_e>>::Run<MODE>);
            }
        };

        template <>
        class Filter_f<Vector_t<some<Collision_Layer_Type_e>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Vector_t<some<Collision_Layer_Type_e>>& collision_layer_types, Bool_t do_negate)
            {
                self->Filter<Vector_t<some<Collision_Layer_Type_e>>&>
                    (do_negate, collision_layer_types, &Compare_f<Filterable_t, Vector_t<some<Collision_Layer_Type_e>>&>::Run<MODE>);
            }
        };

        template <typename Arg_a>
        void OR(Arg_a arg_a)
        {
            Filter_f<Arg_a>::Run<Logic_Gate_e::OR>(this, arg_a, false);
        }

        template <typename Arg_a>
        void NOR(Arg_a arg_a)
        {
            Filter_f<Arg_a>::Run<Logic_Gate_e::OR>(this, arg_a, true);
        }
    };

}}
