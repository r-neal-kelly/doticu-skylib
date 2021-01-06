/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_operator.h"

#include "doticu_skylib/player.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/filter.inl"

namespace doticu_skylib { namespace Filter {

    template <typename Filterable_t>
    class Distances_t : public Filter_i<Filterable_t>
    {
    public:
        Distances_t(State_c<Filterable_t>& state) :
            Filter_i<Filterable_t>(state)
        {
        }

        template <typename Filterable_a, typename Distance_a, typename From_a>
        class Compare_f
        {
        };

        template <>
        class Compare_f<Float_t, Float_t, void>
        {
        public:
            template <const Operator_e::value_type MODE, std::enable_if_t<MODE == Operator_e::LESS_THAN, Bool_t> = true>
            static Result_e Run(Float_t filterable, Float_t distance)
            {
                if (filterable < distance) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }

            template <const Operator_e::value_type MODE, std::enable_if_t<MODE == Operator_e::GREATER_THAN, Bool_t> = true>
            static Result_e Run(Float_t filterable, Float_t distance)
            {
                if (filterable > distance) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <typename Distance_a>
        class Compare_f<some<Reference_t*>, Distance_a, some<Reference_t*>>
        {
        public:
            template <const Operator_e::value_type MODE>
            static Result_e Run(some<Reference_t*> filterable, Distance_a distance, some<Reference_t*> from)
            {
                return Compare_f<Float_t, Distance_a, void>::Run<MODE>(filterable->Distance_Between(from), distance);
            }
        };

        template <typename Distance_a, typename From_a>
        class Compare_f<maybe<Reference_t*>, Distance_a, From_a>
        {
        public:
            template <const Operator_e::value_type MODE>
            static Result_e Run(maybe<Reference_t*> filterable, Distance_a distance, From_a from)
            {
                if (filterable) {
                    return Compare_f<some<Reference_t*>, Distance_a, From_a>::Run<MODE>(filterable(), distance, from);
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <typename Distance_a, typename From_a>
        class Compare_f<Reference_t*, Distance_a, From_a>
        {
        public:
            template <const Operator_e::value_type MODE>
            static Result_e Run(Reference_t* filterable, Distance_a distance, From_a from)
            {
                return Compare_f<maybe<Reference_t*>, Distance_a, From_a>::Run<MODE>(filterable, distance, from);
            }
        };

        template <typename Distance_a, typename From_a>
        class Filter_f
        {
        };

        template <>
        class Filter_f<Float_t, void>
        {
        public:
            template <const Operator_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Float_t distance, Bool_t do_negate)
            {
                if (distance < 0.0f) {
                    distance = 0.0f;
                }

                self->Filter<Float_t>
                    (do_negate, distance, &Compare_f<Filterable_t, Float_t, void>::Run<MODE>);
            }
        };

        template <>
        class Filter_f<Float_t, some<Reference_t*>>
        {
        public:
            template <const Operator_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Float_t distance, some<Reference_t*> from, Bool_t do_negate)
            {
                if (distance < 0.0f) {
                    distance = 0.0f;
                }

                SKYLIB_ASSERT_SOME(from);

                self->Filter<Float_t, some<Reference_t*>>
                    (do_negate, distance, from, &Compare_f<Filterable_t, Float_t, some<Reference_t*>>::Run<MODE>);
            }
        };

        template <typename Distance_a>
        class Filter_f<Distance_a, maybe<Reference_t*>>
        {
        public:
            template <const Operator_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Distance_a distance, maybe<Reference_t*> from, Bool_t do_negate)
            {
                if (from && from->Is_Valid()) {
                    Filter_f<Distance_a, some<Reference_t*>>::Run<MODE>(self, distance, from(), do_negate);
                } else {
                    some<Reference_t*> player = static_cast<some<Reference_t*>>(Player_t::Self());
                    Filter_f<Distance_a, some<Reference_t*>>::Run<MODE>(self, distance, player, do_negate);
                }
            }
        };

        template <typename Distance_a>
        class Filter_f<Distance_a, Reference_t*>
        {
        public:
            template <const Operator_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Distance_a distance, Reference_t* from, Bool_t do_negate)
            {
                Filter_f<Distance_a, maybe<Reference_t*>>::Run<MODE>(self, distance, from, do_negate);
            }
        };

        template <typename Distance_a>
        void LESS_THAN(Distance_a distance, Bool_t do_negate)
        {
            Filter_f<Distance_a, void>::Run<Operator_e::LESS_THAN>(this, distance, do_negate);
        }

        template <typename Distance_a, typename From_a>
        void LESS_THAN(Distance_a distance, From_a from, Bool_t do_negate)
        {
            Filter_f<Distance_a, From_a>::Run<Operator_e::LESS_THAN>(this, distance, from, do_negate);
        }

        template <typename Distance_a>
        void GREATER_THAN(Distance_a distance, Bool_t do_negate)
        {
            Filter_f<Distance_a, void>::Run<Operator_e::GREATER_THAN>(this, distance, do_negate);
        }

        template <typename Distance_a, typename From_a>
        void GREATER_THAN(Distance_a distance, From_a from, Bool_t do_negate)
        {
            Filter_f<Distance_a, From_a>::Run<Operator_e::GREATER_THAN>(this, distance, from, do_negate);
        }
    };

}}
