/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/component_keywords.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/logic_gate.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/filter.inl"

namespace doticu_skylib { namespace Filter {

    template <typename Filterable_t>
    class Keywords_i : public Filter_i<Filterable_t>
    {
    public:
        Keywords_i(State_c<Filterable_t>& state) :
            Filter_i<Filterable_t>(state)
        {
        }

        void Filter(some<Keyword_t*> keyword, Bool_t do_negate, some<Result_e(*)(Filterable_t, some<Keyword_t*>)> compare_f)
        {
            SKYLIB_ASSERT_SOME(compare_f);

            if (keyword && keyword->Is_Valid()) {
                Filter_i<Filterable_t>::Filter<some<Keyword_t*>>(do_negate, keyword, compare_f);
            }
        }

        void Filter(Vector_t<some<Keyword_t*>>& keywords, Bool_t do_negate, some<Result_e(*)(Filterable_t, Vector_t<some<Keyword_t*>>&)> compare_f)
        {
            SKYLIB_ASSERT_SOME(compare_f);

            if (keywords.size() > 0) {
                Filter_i<Filterable_t>::Filter<Vector_t<some<Keyword_t*>>&>(do_negate, keywords, compare_f);
            }
        }

        void Filter(String_t keyword_name, Bool_t do_negate, some<Result_e(*)(Filterable_t, String_t)> compare_f)
        {
            SKYLIB_ASSERT_SOME(compare_f);

            if (keyword_name) {
                Filter_i<Filterable_t>::Filter<String_t>(do_negate, keyword_name, compare_f);
            }
        }
    };

    template <typename Filterable_t>
    class Keywords_t : public Keywords_i<Filterable_t>
    {
    };

    template <>
    class Keywords_t<some<Keyword_t*>> : public Keywords_i<some<Keyword_t*>>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> keyword)
        {
            if (filterable() == keyword()) {
                return Result_e::IS_MATCH;
            } else {
                return Result_e::ISNT_MATCH;
            }
        }
    };

    template <>
    class Keywords_t<maybe<Keyword_t*>> : public Keywords_i<maybe<Keyword_t*>>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> keyword)
        {
            if (filterable && filterable->Is_Valid()) {
                return Keywords_t<some<Keyword_t*>>::Compare(filterable(), keyword);
            } else {
                return Result_e::INVALID;
            }
        }
    };

    template <>
    class Keywords_t<Keyword_t*> : public Keywords_i<Keyword_t*>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> keyword)
        {
            return Keywords_t<maybe<Keyword_t*>>::Compare(filterable, keyword);
        }
    };

    template <>
    class Keywords_t<some<Keywords_c*>> : public Keywords_i<some<Keywords_c*>>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::AND, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_AND);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::OR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_OR);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::XOR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_XOR);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> compare)
        {
            if (filterable->keywords) {
                for (Index_t idx = 0, end = filterable->keyword_count; idx < end; idx += 1) {
                    if (Keywords_t<Keyword_t*>::Compare(filterable->keywords[idx], compare) == Result_e::IS_MATCH) {
                        return Result_e::IS_MATCH;
                    }
                }
                return Result_e::ISNT_MATCH;
            } else {
                return Result_e::ISNT_MATCH;
            }
        }

        static Result_e Compare_AND(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            for (Index_t idx = 0, end = compares.size(); idx < end; idx += 1) {
                if (Compare(filterable, compares[idx]) == Result_e::ISNT_MATCH) {
                    return Result_e::ISNT_MATCH;
                }
            }
            return Result_e::IS_MATCH;
        }

        static Result_e Compare_OR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            for (Index_t idx = 0, end = compares.size(); idx < end; idx += 1) {
                if (Compare(filterable, compares[idx]) == Result_e::IS_MATCH) {
                    return Result_e::IS_MATCH;
                }
            }
            return Result_e::ISNT_MATCH;
        }

        static Result_e Compare_XOR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            Bool_t did_match = false;
            for (Index_t idx = 0, end = compares.size(); idx < end; idx += 1) {
                if (Compare(filterable, compares[idx]) == Result_e::IS_MATCH) {
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

    template <>
    class Keywords_t<maybe<Keywords_c*>> : public Keywords_i<maybe<Keywords_c*>>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::AND, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_AND);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::OR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_OR);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::XOR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_XOR);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> compare)
        {
            if (filterable) {
                return Keywords_t<some<Keywords_c*>>::Compare(filterable(), compare);
            } else {
                return Result_e::INVALID;
            }
        }

        static Result_e Compare_AND(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            if (filterable) {
                return Keywords_t<some<Keywords_c*>>::Compare_AND(filterable(), compares);
            } else {
                return Result_e::INVALID;
            }
        }

        static Result_e Compare_OR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            if (filterable) {
                return Keywords_t<some<Keywords_c*>>::Compare_OR(filterable(), compares);
            } else {
                return Result_e::INVALID;
            }
        }

        static Result_e Compare_XOR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            if (filterable) {
                return Keywords_t<some<Keywords_c*>>::Compare_XOR(filterable(), compares);
            } else {
                return Result_e::INVALID;
            }
        }
    };

    template <>
    class Keywords_t<Keywords_c*> : public Keywords_i<Keywords_c*>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::AND, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_AND);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::OR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_OR);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::XOR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_XOR);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> compare)
        {
            return Keywords_t<maybe<Keywords_c*>>::Compare(filterable, compare);
        }

        static Result_e Compare_AND(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Keywords_c*>>::Compare_AND(filterable, compares);
        }

        static Result_e Compare_OR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Keywords_c*>>::Compare_OR(filterable, compares);
        }

        static Result_e Compare_XOR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Keywords_c*>>::Compare_XOR(filterable, compares);
        }
    };

    template <>
    class Keywords_t<some<Form_t*>> : public Keywords_i<some<Form_t*>>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::AND, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_AND);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::OR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_OR);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::XOR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_XOR);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> compare)
        {
            return Keywords_t<maybe<Keywords_c*>>::Compare(Game_t::Runtime_Cast<Form_t, Keywords_c>(filterable), compare);
        }

        static Result_e Compare_AND(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Keywords_c*>>::Compare_AND(Game_t::Runtime_Cast<Form_t, Keywords_c>(filterable), compares);
        }

        static Result_e Compare_OR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Keywords_c*>>::Compare_OR(Game_t::Runtime_Cast<Form_t, Keywords_c>(filterable), compares);
        }

        static Result_e Compare_XOR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Keywords_c*>>::Compare_XOR(Game_t::Runtime_Cast<Form_t, Keywords_c>(filterable), compares);
        }
    };

    template <>
    class Keywords_t<maybe<Form_t*>> : public Keywords_i<maybe<Form_t*>>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::AND, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_AND);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::OR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_OR);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::XOR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_XOR);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> compare)
        {
            if (filterable && filterable->Is_Valid()) {
                return Keywords_t<some<Form_t*>>::Compare(filterable(), compare);
            } else {
                return Result_e::INVALID;
            }
        }

        static Result_e Compare_AND(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            if (filterable && filterable->Is_Valid()) {
                return Keywords_t<some<Form_t*>>::Compare_AND(filterable(), compares);
            } else {
                return Result_e::INVALID;
            }
        }

        static Result_e Compare_OR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            if (filterable && filterable->Is_Valid()) {
                return Keywords_t<some<Form_t*>>::Compare_OR(filterable(), compares);
            } else {
                return Result_e::INVALID;
            }
        }

        static Result_e Compare_XOR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            if (filterable && filterable->Is_Valid()) {
                return Keywords_t<some<Form_t*>>::Compare_XOR(filterable(), compares);
            } else {
                return Result_e::INVALID;
            }
        }
    };

    template <>
    class Keywords_t<Form_t*> : public Keywords_i<Form_t*>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::AND, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_AND);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::OR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_OR);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::XOR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_XOR);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> compare)
        {
            return Keywords_t<maybe<Form_t*>>::Compare(filterable, compare);
        }

        static Result_e Compare_AND(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Form_t*>>::Compare_AND(filterable, compares);
        }

        static Result_e Compare_OR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Form_t*>>::Compare_OR(filterable, compares);
        }

        static Result_e Compare_XOR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Form_t*>>::Compare_XOR(filterable, compares);
        }
    };

    template <>
    class Keywords_t<some<Reference_t*>> : public Keywords_i<some<Reference_t*>>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::AND, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_AND);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::OR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_OR);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::XOR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_XOR);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> compare)
        {
            return Keywords_t<maybe<Form_t*>>::Compare(filterable->base_form, compare);
        }

        static Result_e Compare_AND(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Form_t*>>::Compare_AND(filterable->base_form, compares);
        }

        static Result_e Compare_OR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Form_t*>>::Compare_OR(filterable->base_form, compares);
        }

        static Result_e Compare_XOR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Form_t*>>::Compare_XOR(filterable->base_form, compares);
        }
    };

    template <>
    class Keywords_t<maybe<Reference_t*>> : public Keywords_i<maybe<Reference_t*>>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::AND, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_AND);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::OR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_OR);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::XOR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_XOR);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> compare)
        {
            if (filterable && filterable->Is_Valid()) {
                return Keywords_t<some<Reference_t*>>::Compare(filterable(), compare);
            } else {
                return Result_e::INVALID;
            }
        }

        static Result_e Compare_AND(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            if (filterable && filterable->Is_Valid()) {
                return Keywords_t<some<Reference_t*>>::Compare_AND(filterable(), compares);
            } else {
                return Result_e::INVALID;
            }
        }

        static Result_e Compare_OR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            if (filterable && filterable->Is_Valid()) {
                return Keywords_t<some<Reference_t*>>::Compare_OR(filterable(), compares);
            } else {
                return Result_e::INVALID;
            }
        }

        static Result_e Compare_XOR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            if (filterable && filterable->Is_Valid()) {
                return Keywords_t<some<Reference_t*>>::Compare_XOR(filterable(), compares);
            } else {
                return Result_e::INVALID;
            }
        }
    };

    template <>
    class Keywords_t<Reference_t*> : public Keywords_i<Reference_t*>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Keywords_i<Filterable_t>(state)
        {
        }

        template <typename Compare_a>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::AND, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_AND);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::OR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_OR);
        }
        template <Logic_Gate_e::value_type mode, typename Compare_a, std::enable_if_t<mode == Logic_Gate_e::XOR, Bool_t> = true>
        void Filter(Compare_a compare_a, Bool_t do_negate)
        {
            Keywords_i::Filter(compare_a, do_negate, &Compare_XOR);
        }

        static Result_e Compare(Filterable_t filterable, some<Keyword_t*> compare)
        {
            return Keywords_t<maybe<Reference_t*>>::Compare(filterable, compare);
        }

        static Result_e Compare_AND(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Reference_t*>>::Compare_AND(filterable, compares);
        }

        static Result_e Compare_OR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Reference_t*>>::Compare_OR(filterable, compares);
        }

        static Result_e Compare_XOR(Filterable_t filterable, Vector_t<some<Keyword_t*>>& compares)
        {
            return Keywords_t<maybe<Reference_t*>>::Compare_XOR(filterable, compares);
        }
    };

}}
