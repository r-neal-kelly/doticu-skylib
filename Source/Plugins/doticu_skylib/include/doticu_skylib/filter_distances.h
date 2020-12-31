/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_operator.h"

#include "doticu_skylib/reference.h"

#include "doticu_skylib/filter.inl"

namespace doticu_skylib { namespace Filter {

    template <typename Filterable_t>
    class Distances_i : public Filter_i<Filterable_t>
    {
    public:
        Distances_i(State_c<Filterable_t>& state) :
            Filter_i<Filterable_t>(state)
        {
        }

        void Filter(Float_t distance,
                    Bool_t do_negate,
                    some<Result_e(*)(Filterable_t, Float_t)> compare_f)
        {
            SKYLIB_ASSERT_SOME(compare_f);

            if (distance >= 0.0f) {
                Filter_i<Filterable_t>::Filter<Float_t>(do_negate, distance, compare_f);
            }
        }

        void Filter(Float_t distance,
                    some<Reference_t*> from,
                    Bool_t do_negate,
                    some<Result_e(*)(Filterable_t, Float_t, some<Reference_t*>)> compare_f)
        {
            SKYLIB_ASSERT_SOME(from);
            SKYLIB_ASSERT_SOME(compare_f);

            if (distance >= 0.0f) {
                Filter_i<Filterable_t>::Filter<Float_t, some<Reference_t*>>(do_negate, distance, from, compare_f);
            }
        }
    };

    template <typename Filterable_t>
    class Distances_t : public Distances_i<Filterable_t>
    {
    };

    template <>
    class Distances_t<Float_t> : public Distances_i<Float_t>
    {
    public:
        Distances_t(State_c<Filterable_t>& state) :
            Distances_i<Filterable_t>(state)
        {
        }

        template <Operator_e::value_type mode, typename Compare_a,
            std::enable_if_t<mode == Operator_e::LESS_THAN, Bool_t> = true
        > void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Distances_i::Filter(compare_a, do_negate, &Compare_LESS_THAN);
        }
        template <Operator_e::value_type mode, typename Compare_a,
            std::enable_if_t<mode == Operator_e::GREATER_THAN, Bool_t> = true
        > void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Distances_i::Filter(compare_a, do_negate, &Compare_GREATER_THAN);
        }

        static Result_e Compare_LESS_THAN(Filterable_t filterable, Float_t distance)
        {
            if (filterable < distance) {
                return Result_e::IS_MATCH;
            } else {
                return Result_e::ISNT_MATCH;
            }
        }

        static Result_e Compare_GREATER_THAN(Filterable_t filterable, Float_t distance)
        {
            if (filterable > distance) {
                return Result_e::IS_MATCH;
            } else {
                return Result_e::ISNT_MATCH;
            }
        }
    };

    template <>
    class Distances_t<some<Reference_t*>> : public Distances_i<some<Reference_t*>>
    {
    public:
        Distances_t(State_c<Filterable_t>& state) :
            Distances_i<Filterable_t>(state)
        {
        }

        template <Operator_e::value_type mode, typename Compare_a, typename Compare_b,
            std::enable_if_t<mode == Operator_e::LESS_THAN, Bool_t> = true
        > void Filter(Compare_a compare_a, Compare_b compare_b, Bool_t do_negate)
        {
            Distances_i::Filter(compare_a, compare_b, do_negate, &Compare_LESS_THAN);
        }
        template <Operator_e::value_type mode, typename Compare_a, typename Compare_b,
            std::enable_if_t<mode == Operator_e::GREATER_THAN, Bool_t> = true
        > void Filter(Compare_a compare_a, Compare_b compare_b, Bool_t do_negate)
        {
            Distances_i::Filter(compare_a, compare_b, do_negate, &Compare_GREATER_THAN);
        }

        static Result_e Compare_LESS_THAN(Filterable_t filterable, Float_t distance, some<Reference_t*> from)
        {
            return Distances_t<Float_t>::Compare_LESS_THAN(filterable->Distance_Between(from), distance);
        }

        static Result_e Compare_GREATER_THAN(Filterable_t filterable, Float_t distance, some<Reference_t*> from)
        {
            return Distances_t<Float_t>::Compare_GREATER_THAN(filterable->Distance_Between(from), distance);
        }
    };

    template <>
    class Distances_t<maybe<Reference_t*>> : public Distances_i<maybe<Reference_t*>>
    {
    public:
        Distances_t(State_c<Filterable_t>& state) :
            Distances_i<Filterable_t>(state)
        {
        }

        template <Operator_e::value_type mode, typename Compare_a, typename Compare_b,
            std::enable_if_t<mode == Operator_e::LESS_THAN, Bool_t> = true
        > void Filter(Compare_a compare_a, Compare_b compare_b, Bool_t do_negate)
        {
            Distances_i::Filter(compare_a, compare_b, do_negate, &Compare_LESS_THAN);
        }
        template <Operator_e::value_type mode, typename Compare_a, typename Compare_b,
            std::enable_if_t<mode == Operator_e::GREATER_THAN, Bool_t> = true
        > void Filter(Compare_a compare_a, Compare_b compare_b, Bool_t do_negate)
        {
            Distances_i::Filter(compare_a, compare_b, do_negate, &Compare_GREATER_THAN);
        }

        static Result_e Compare_LESS_THAN(Filterable_t filterable, Float_t distance, some<Reference_t*> from)
        {
            if (filterable && filterable->Is_Valid()) {
                return Distances_t<some<Reference_t*>>::Compare_LESS_THAN(filterable(), distance, from);
            } else {
                return Result_e::INVALID;
            }
        }

        static Result_e Compare_GREATER_THAN(Filterable_t filterable, Float_t distance, some<Reference_t*> from)
        {
            if (filterable && filterable->Is_Valid()) {
                return Distances_t<some<Reference_t*>>::Compare_GREATER_THAN(filterable(), distance, from);
            } else {
                return Result_e::INVALID;
            }
        }
    };

    template <>
    class Distances_t<Reference_t*> : public Distances_i<Reference_t*>
    {
    public:
        Distances_t(State_c<Filterable_t>& state) :
            Distances_i<Filterable_t>(state)
        {
        }

        template <Operator_e::value_type mode, typename Compare_a, typename Compare_b,
            std::enable_if_t<mode == Operator_e::LESS_THAN, Bool_t> = true
        > void Filter(Compare_a compare_a, Compare_b compare_b, Bool_t do_negate)
        {
            Distances_i::Filter(compare_a, compare_b, do_negate, &Compare_LESS_THAN);
        }
        template <Operator_e::value_type mode, typename Compare_a, typename Compare_b,
            std::enable_if_t<mode == Operator_e::GREATER_THAN, Bool_t> = true
        > void Filter(Compare_a compare_a, Compare_b compare_b, Bool_t do_negate)
        {
            Distances_i::Filter(compare_a, compare_b, do_negate, &Compare_GREATER_THAN);
        }

        static Result_e Compare_LESS_THAN(Filterable_t filterable, Float_t distance, some<Reference_t*> from)
        {
            return Distances_t<maybe<Reference_t*>>::Compare_LESS_THAN(filterable, distance, from);
        }

        static Result_e Compare_GREATER_THAN(Filterable_t filterable, Float_t distance, some<Reference_t*> from)
        {
            return Distances_t<maybe<Reference_t*>>::Compare_GREATER_THAN(filterable, distance, from);
        }
    };

}}
