/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_logic_gate.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/form_list.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/filter.inl"

namespace doticu_skylib { namespace Filter {

    template <typename Filterable_t>
    class Bases_t : public Filter_i<Filterable_t>
    {
    public:
        Bases_t(State_c<Filterable_t>& state) :
            Filter_i<Filterable_t>(state)
        {
        }

        template <typename Filterable_a, typename Bases_a>
        class Compare_f
        {
        };

        template <>
        class Compare_f<some<Form_t*>, Vector_t<some<Form_t*>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Form_t*> filterable, Vector_t<some<Form_t*>>& bases)
            {
                if (bases.Has(filterable)) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <>
        class Compare_f<some<Form_t*>, some<Form_List_t*>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Form_t*> filterable, some<Form_List_t*> bases)
            {
                if (bases->Has(filterable)) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <typename Bases_a>
        class Compare_f<maybe<Form_t*>, Bases_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(maybe<Form_t*> filterable, Bases_a bases)
            {
                if (filterable) {
                    return Compare_f<some<Form_t*>, Bases_a>::Run<MODE>(filterable(), bases);
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <typename Bases_a>
        class Compare_f<Form_t*, Bases_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(Form_t* filterable, Bases_a bases)
            {
                return Compare_f<maybe<Form_t*>, Bases_a>::Run<MODE>(filterable, bases);
            }
        };

        template <typename Bases_a>
        class Compare_f<some<Reference_t*>, Bases_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Reference_t*> filterable, Bases_a bases)
            {
                return Compare_f<Form_t*, Bases_a>::Run<MODE>(filterable->base_form(), bases);
            }
        };

        template <typename Bases_a>
        class Compare_f<maybe<Reference_t*>, Bases_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(maybe<Reference_t*> filterable, Bases_a bases)
            {
                if (filterable) {
                    return Compare_f<some<Reference_t*>, Bases_a>::Run<MODE>(filterable(), bases);
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <typename Bases_a>
        class Compare_f<Reference_t*, Bases_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(Reference_t* filterable, Bases_a bases)
            {
                return Compare_f<maybe<Reference_t*>, Bases_a>::Run<MODE>(filterable, bases);
            }
        };

        template <typename Bases_a>
        class Filter_f
        {
        };

        template <>
        class Filter_f<Vector_t<some<Form_t*>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Vector_t<some<Form_t*>>& bases, Bool_t do_negate)
            {
                self->Filter<Vector_t<some<Form_t*>>&>
                    (do_negate, bases, &Compare_f<Filterable_t, Vector_t<some<Form_t*>>&>::Run<MODE>);
            }
        };

        template <>
        class Filter_f<some<Form_List_t*>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, some<Form_List_t*> bases, Bool_t do_negate)
            {
                SKYLIB_ASSERT_SOME(bases);
                self->Filter<some<Form_List_t*>>
                    (do_negate, bases, &Compare_f<Filterable_t, some<Form_List_t*>>::Run<MODE>);
            }
        };

        template <>
        class Filter_f<maybe<Form_List_t*>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, maybe<Form_List_t*> bases, Bool_t do_negate)
            {
                if (bases && bases->Is_Valid()) {
                    Filter_f<some<Form_List_t*>>::Run<MODE>(self, bases(), do_negate);
                } else {
                    Vector_t<some<Form_t*>> empty_bases;
                    Filter_f<Vector_t<some<Form_t*>>&>::Run<MODE>(self, empty_bases, do_negate);
                }
            }
        };

        template <>
        class Filter_f<Form_List_t*>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Form_List_t* bases, Bool_t do_negate)
            {
                Filter_f<maybe<Form_List_t*>>::Run<MODE>(self, bases, do_negate);
            }
        };

        template <typename Bases_a>
        void OR(Bases_a bases, Bool_t do_negate)
        {
            Filter_f<Bases_a>::Run<Logic_Gate_e::OR>(this, bases, do_negate);
        }
    };

}}
