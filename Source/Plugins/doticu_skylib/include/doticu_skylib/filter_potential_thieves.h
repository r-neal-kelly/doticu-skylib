/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_logic_gate.h"

#include "doticu_skylib/actor.h"

#include "doticu_skylib/filter.inl"

namespace doticu_skylib { namespace Filter {

    template <typename Filterable_t>
    class Potential_Thieves_t : public Filter_i<Filterable_t>
    {
    public:
        Potential_Thieves_t(State_c<Filterable_t>& state) :
            Filter_i<Filterable_t>(state)
        {
        }

        template <typename Filterable_a, typename Arg_a>
        class Compare_f
        {
        };

        template <>
        class Compare_f<some<Reference_t*>, some<Actor_t*>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Reference_t*> filterable, some<Actor_t*> actor)
            {
                if (filterable->Has_Potential_Thief(actor)) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <>
        class Compare_f<some<Reference_t*>, Vector_t<some<Actor_t*>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::OR, Bool_t> = true>
            static Result_e Run(some<Reference_t*> filterable, Vector_t<some<Actor_t*>>& actors)
            {
                for (size_t idx = 0, end = actors.size(); idx < end; idx += 1) {
                    if (Compare_f<some<Reference_t*>, some<Actor_t*>>::Run<MODE>(filterable, actors[idx]) == Result_e::IS_MATCH) {
                        return Result_e::IS_MATCH;
                    }
                }
                return Result_e::ISNT_MATCH;
            }

            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::AND, Bool_t> = true>
            static Result_e Run(some<Reference_t*> filterable, Vector_t<some<Actor_t*>>& actors)
            {
                for (size_t idx = 0, end = actors.size(); idx < end; idx += 1) {
                    if (Compare_f<some<Reference_t*>, some<Actor_t*>>::Run<MODE>(filterable, actors[idx]) == Result_e::ISNT_MATCH) {
                        return Result_e::ISNT_MATCH;
                    }
                }
                return Result_e::IS_MATCH;
            }

            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::XOR, Bool_t> = true>
            static Result_e Run(some<Reference_t*> filterable, Vector_t<some<Actor_t*>>& actors)
            {
                Bool_t did_match = false;
                for (size_t idx = 0, end = actors.size(); idx < end; idx += 1) {
                    if (Compare_f<some<Reference_t*>, some<Actor_t*>>::Run<MODE>(filterable, actors[idx]) == Result_e::IS_MATCH) {
                        if (did_match) {
                            return Result_e::ISNT_MATCH;
                        } else {
                            did_match = true;
                        }
                    }
                }
                if (did_match) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
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
        class Filter_f<some<Actor_t*>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, some<Actor_t*> actor, Bool_t do_negate)
            {
                SKYLIB_ASSERT_SOME(actor);
                self->Filter<some<Actor_t*>>
                    (do_negate, actor, &Compare_f<Filterable_t, some<Actor_t*>>::Run<MODE>);
            }
        };

        template <>
        class Filter_f<Vector_t<some<Actor_t*>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Vector_t<some<Actor_t*>>& actors, Bool_t do_negate)
            {
                self->Filter<Vector_t<some<Actor_t*>>&>
                    (do_negate, actors, &Compare_f<Filterable_t, Vector_t<some<Actor_t*>>&>::Run<MODE>);
            }
        };

        template <typename Arg_a>
        void OR(Arg_a arg_a)
        {
            Filter_f<Arg_a>::Run<Logic_Gate_e::OR>(this, arg_a, false);
        }

        template <typename Arg_a>
        void AND(Arg_a arg_a)
        {
            Filter_f<Arg_a>::Run<Logic_Gate_e::AND>(this, arg_a, false);
        }

        template <typename Arg_a>
        void XOR(Arg_a arg_a)
        {
            Filter_f<Arg_a>::Run<Logic_Gate_e::XOR>(this, arg_a, false);
        }

        template <typename Arg_a>
        void NOR(Arg_a arg_a)
        {
            Filter_f<Arg_a>::Run<Logic_Gate_e::OR>(this, arg_a, true);
        }

        template <typename Arg_a>
        void NAND(Arg_a arg_a)
        {
            Filter_f<Arg_a>::Run<Logic_Gate_e::AND>(this, arg_a, true);
        }

        template <typename Arg_a>
        void XNOR(Arg_a arg_a)
        {
            Filter_f<Arg_a>::Run<Logic_Gate_e::XOR>(this, arg_a, true);
        }
    };

}}
