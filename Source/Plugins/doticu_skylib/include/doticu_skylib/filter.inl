/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib { namespace Filter {

    class Result_e : public Binary_e
    {
    public:
        enum : value_type
        {
            INVALID     = Binary_e::NONE,
            IS_MATCH    = Binary_e::A,
            ISNT_MATCH  = Binary_e::B,
        };
        using Binary_e::Binary_e;
    };

    template <typename Filterable_t>
    class State_c
    {
    public:
        Vector_t<Filterable_t>* read;
        Vector_t<Filterable_t>* write;
        Vector_t<Filterable_t>* temp;

        State_c(Vector_t<Filterable_t>* read, Vector_t<Filterable_t>* write) :
            read(read), write(write), temp(nullptr)
        {
        }

        void Swap()
        {
            temp = read;
            read = write;
            write = temp;
            write->clear();
        }

        Vector_t<Filterable_t>* Results()
        {
            return read;
        }
    };

    template <typename Filterable_tt>
    class Filter_i
    {
    public:
        using Filterable_t = Filterable_tt;

        State_c<Filterable_t>& state;
        Filter_i(State_c<Filterable_t>& state) :
            state(state)
        {
        }

        void Filter(Bool_t do_negate,
                    some<Result_e(*)(Filterable_t)> compare_f)
        {
            SKYLIB_ASSERT_SOME(compare_f);

            if (do_negate) {
                for (size_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                    Filterable_t filterable = state.read->at(idx);
                    if (compare_f()(filterable) == Result_e::ISNT_MATCH) {
                        state.write->push_back(filterable);
                    }
                }
            } else {
                for (size_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                    Filterable_t filterable = state.read->at(idx);
                    if (compare_f()(filterable) == Result_e::IS_MATCH) {
                        state.write->push_back(filterable);
                    }
                }
            }
            state.Swap();
        }

        template <typename Compare_a>
        void Filter(Bool_t do_negate,
                    Compare_a compare_a,
                    some<Result_e(*)(Filterable_t, Compare_a)> compare_f)
        {
            SKYLIB_ASSERT_SOME(compare_f);

            if (do_negate) {
                for (size_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                    Filterable_t filterable = state.read->at(idx);
                    if (compare_f()(filterable, compare_a) == Result_e::ISNT_MATCH) {
                        state.write->push_back(filterable);
                    }
                }
            } else {
                for (size_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                    Filterable_t filterable = state.read->at(idx);
                    if (compare_f()(filterable, compare_a) == Result_e::IS_MATCH) {
                        state.write->push_back(filterable);
                    }
                }
            }
            state.Swap();
        }

        template <typename Compare_a, typename Compare_b>
        void Filter(Bool_t do_negate,
                    Compare_a compare_a, Compare_b compare_b,
                    some<Result_e(*)(Filterable_t, Compare_a, Compare_b)> compare_f)
        {
            SKYLIB_ASSERT_SOME(compare_f);

            if (do_negate) {
                for (size_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                    Filterable_t filterable = state.read->at(idx);
                    if (compare_f()(filterable, compare_a, compare_b) == Result_e::ISNT_MATCH) {
                        state.write->push_back(filterable);
                    }
                }
            } else {
                for (size_t idx = 0, end = state.read->size(); idx < end; idx += 1) {
                    Filterable_t filterable = state.read->at(idx);
                    if (compare_f()(filterable, compare_a, compare_b) == Result_e::IS_MATCH) {
                        state.write->push_back(filterable);
                    }
                }
            }
            state.Swap();
        }
    };

}}
