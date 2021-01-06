/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_operator.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/filter.inl"

namespace doticu_skylib { namespace Filter {

    template <typename Filterable_t>
    class Deleted_t : public Filter_i<Filterable_t>
    {
    public:
        Deleted_t(State_c<Filterable_t>& state) :
            Filter_i<Filterable_t>(state)
        {
        }

        template <typename Filterable_a, typename Arg_a = void>
        class Compare_f
        {
        };

        template <>
        class Compare_f<some<Reference_t*>, void>
        {
        public:
            template <const Operator_e::value_type MODE, std::enable_if_t<MODE == Operator_e::EQUAL_TO, Bool_t> = true>
            static Result_e Run(some<Reference_t*> filterable)
            {
                if (filterable->Is_Deleted()) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <>
        class Compare_f<maybe<Reference_t*>, void>
        {
        public:
            template <const Operator_e::value_type MODE>
            static Result_e Run(maybe<Reference_t*> filterable)
            {
                if (filterable) {
                    return Compare_f<some<Reference_t*>>::Run<MODE>(filterable());
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <>
        class Compare_f<Reference_t*, void>
        {
        public:
            template <const Operator_e::value_type MODE>
            static Result_e Run(Reference_t* filterable)
            {
                return Compare_f<maybe<Reference_t*>>::Run<MODE>(filterable);
            }
        };

        template <typename Arg_a = void>
        class Filter_f
        {
        };

        template <>
        class Filter_f<void>
        {
        public:
            template <const Operator_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Bool_t do_negate)
            {
                self->Filter
                    (do_negate, &Compare_f<Filterable_t>::Run<MODE>);
            }
        };

        void EQUAL_TO()
        {
            Filter_f<void>::Run<Operator_e::EQUAL_TO>(this, false);
        }

        void NOT_EQUAL_TO()
        {
            Filter_f<void>::Run<Operator_e::EQUAL_TO>(this, true);
        }
    };

}}
