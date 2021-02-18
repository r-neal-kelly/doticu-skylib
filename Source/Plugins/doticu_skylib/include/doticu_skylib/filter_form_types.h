/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_form_type.h"
#include "doticu_skylib/enum_logic_gate.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/filter.inl"

namespace doticu_skylib { namespace Filter {

    template <typename Filterable_t>
    class Form_Types_t : public Filter_i<Filterable_t>
    {
    public:
        Form_Types_t(State_c<Filterable_t>& state) :
            Filter_i<Filterable_t>(state)
        {
        }

        template <typename Filterable_a, typename Arg_a>
        class Compare_f
        {
        };

        template <>
        class Compare_f<some<Form_Type_e>, some<Form_Type_e>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Form_Type_e> filterable, some<Form_Type_e> form_type)
            {
                if (filterable() == form_type()) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <>
        class Compare_f<some<Form_Type_e>, Vector_t<some<Form_Type_e>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::OR, Bool_t> = true>
            static Result_e Run(some<Form_Type_e> filterable, Vector_t<some<Form_Type_e>>& form_types)
            {
                if (form_types.Has(filterable)) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <typename Arg_a>
        class Compare_f<maybe<Form_Type_e>, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(maybe<Form_Type_e> filterable, Arg_a arg_a)
            {
                if (filterable) {
                    return Compare_f<some<Form_Type_e>, Arg_a>::Run<MODE>(filterable(), arg_a);
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <typename Arg_a>
        class Compare_f<Form_Type_e, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(Form_Type_e filterable, Arg_a arg_a)
            {
                return Compare_f<maybe<Form_Type_e>, Arg_a>::Run<MODE>(filterable, arg_a);
            }
        };

        template <typename Formable_t, typename Arg_a>
        class Compare_f<some<Formable_t*>, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Formable_t*> filterable, Arg_a arg_a)
            {
                return Compare_f<Form_Type_e, Arg_a>::Run<MODE>(filterable->form_type, arg_a);
            }
        };

        template <typename Formable_t, typename Arg_a>
        class Compare_f<maybe<Formable_t*>, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(maybe<Formable_t*> filterable, Arg_a arg_a)
            {
                if (filterable) {
                    return Compare_f<some<Formable_t*>, Arg_a>::Run<MODE>(filterable(), arg_a);
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <typename Formable_t, typename Arg_a>
        class Compare_f<Formable_t*, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(Formable_t* filterable, Arg_a arg_a)
            {
                return Compare_f<maybe<Formable_t*>, Arg_a>::Run<MODE>(filterable, arg_a);
            }
        };

        template <typename Arg_a>
        class Filter_f
        {
        };

        template <>
        class Filter_f<some<Form_Type_e>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, some<Form_Type_e> form_type, Bool_t do_negate)
            {
                SKYLIB_ASSERT_SOME(form_type);
                self->Filter<some<Form_Type_e>>
                    (do_negate, form_type, &Compare_f<Filterable_t, some<Form_Type_e>>::Run<MODE>);
            }
        };

        template <>
        class Filter_f<Vector_t<some<Form_Type_e>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Vector_t<some<Form_Type_e>>& form_types, Bool_t do_negate)
            {
                self->Filter<Vector_t<some<Form_Type_e>>&>
                    (do_negate, form_types, &Compare_f<Filterable_t, Vector_t<some<Form_Type_e>>&>::Run<MODE>);
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
