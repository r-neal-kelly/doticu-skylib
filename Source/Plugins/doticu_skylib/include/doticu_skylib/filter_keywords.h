/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum_logic_gate.h"
#include "doticu_skylib/enum_operator.h"

#include "doticu_skylib/component_keywords.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/game.inl"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/filter.inl"

namespace doticu_skylib { namespace Filter {

    template <typename Filterable_t>
    class Keywords_t : public Filter_i<Filterable_t>
    {
    public:
        Keywords_t(State_c<Filterable_t>& state) :
            Filter_i<Filterable_t>(state)
        {
        }

        template <typename Filterable_a, typename Arg_a>
        class Compare_f
        {
        };

        template <>
        class Compare_f<some<Keyword_t*>, some<Keyword_t*>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Keyword_t*> filterable, some<Keyword_t*> keyword)
            {
                if (filterable() == keyword()) {
                    return Result_e::IS_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <typename Arg_a>
        class Compare_f<maybe<Keyword_t*>, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(maybe<Keyword_t*> filterable, Arg_a arg_a)
            {
                if (filterable) {
                    return Compare_f<some<Keyword_t*>, Arg_a>::Run<MODE>(filterable(), arg_a);
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <typename Arg_a>
        class Compare_f<Keyword_t*, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(Keyword_t* filterable, Arg_a arg_a)
            {
                return Compare_f<maybe<Keyword_t*>, Arg_a>::Run<MODE>(filterable, arg_a);
            }
        };

        template <>
        class Compare_f<some<Keywords_c*>, some<Keyword_t*>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Keywords_c*> filterable, some<Keyword_t*> keyword)
            {
                if (filterable->keywords) {
                    for (size_t idx = 0, end = filterable->keyword_count; idx < end; idx += 1) {
                        if (Compare_f<Keyword_t*, some<Keyword_t*>>::Run<MODE>(filterable->keywords[idx], keyword) == Result_e::IS_MATCH) {
                            return Result_e::IS_MATCH;
                        }
                    }
                    return Result_e::ISNT_MATCH;
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <>
        class Compare_f<some<Keywords_c*>, Vector_t<some<Keyword_t*>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::OR, Bool_t> = true>
            static Result_e Run(some<Keywords_c*> filterable, Vector_t<some<Keyword_t*>>& keywords)
            {
                for (size_t idx = 0, end = keywords.size(); idx < end; idx += 1) {
                    if (Compare_f<some<Keywords_c*>, some<Keyword_t*>>::Run<MODE>(filterable, keywords[idx]) == Result_e::IS_MATCH) {
                        return Result_e::IS_MATCH;
                    }
                }
                return Result_e::ISNT_MATCH;
            }

            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::AND, Bool_t> = true>
            static Result_e Run(some<Keywords_c*> filterable, Vector_t<some<Keyword_t*>>& keywords)
            {
                for (size_t idx = 0, end = keywords.size(); idx < end; idx += 1) {
                    if (Compare_f<some<Keywords_c*>, some<Keyword_t*>>::Run<MODE>(filterable, keywords[idx]) == Result_e::ISNT_MATCH) {
                        return Result_e::ISNT_MATCH;
                    }
                }
                return Result_e::IS_MATCH;
            }

            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::XOR, Bool_t> = true>
            static Result_e Run(some<Keywords_c*> filterable, Vector_t<some<Keyword_t*>>& keywords)
            {
                Bool_t did_match = false;
                for (size_t idx = 0, end = keywords.size(); idx < end; idx += 1) {
                    if (Compare_f<some<Keywords_c*>, some<Keyword_t*>>::Run<MODE>(filterable, keywords[idx]) == Result_e::IS_MATCH) {
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
        class Compare_f<maybe<Keywords_c*>, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(maybe<Keywords_c*> filterable, Arg_a arg_a)
            {
                if (filterable) {
                    return Compare_f<some<Keywords_c*>, Arg_a>::Run<MODE>(filterable(), arg_a);
                } else {
                    return Result_e::ISNT_MATCH;
                }
            }
        };

        template <typename Arg_a>
        class Compare_f<Keywords_c*, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(Keywords_c* filterable, Arg_a arg_a)
            {
                return Compare_f<maybe<Keywords_c*>, Arg_a>::Run<MODE>(filterable, arg_a);
            }
        };

        template <typename Arg_a>
        class Compare_f<some<Form_t*>, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(some<Form_t*> filterable, Arg_a arg_a)
            {
                return Compare_f<maybe<Keywords_c*>, Arg_a>::Run<MODE>(Game_t::Runtime_Cast<Form_t, Keywords_c>(filterable), arg_a);
            }
        };

        template <typename Arg_a>
        class Compare_f<maybe<Form_t*>, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(maybe<Form_t*> filterable, Arg_a arg_a)
            {
                if (filterable) {
                    return Compare_f<some<Form_t*>, Arg_a>::Run<MODE>(filterable(), arg_a);
                } else {
                    return Result_e::INVALID;
                }
            }
        };

        template <typename Arg_a>
        class Compare_f<Form_t*, Arg_a>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static Result_e Run(Form_t* filterable, Arg_a arg_a)
            {
                return Compare_f<maybe<Form_t*>, Arg_a>::Run<MODE>(filterable, arg_a);
            }
        };

        template <>
        class Compare_f<some<Reference_t*>, Vector_t<some<Keyword_t*>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::OR, Bool_t> = true>
            static Result_e Run(some<Reference_t*> filterable, Vector_t<some<Keyword_t*>>& keywords)
            {
                for (size_t idx = 0, end = keywords.size(); idx < end; idx += 1) {
                    if (filterable->Has_Keyword(keywords[idx])) {
                        return Result_e::IS_MATCH;
                    }
                }
                return Result_e::ISNT_MATCH;
            }

            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::AND, Bool_t> = true>
            static Result_e Run(some<Reference_t*> filterable, Vector_t<some<Keyword_t*>>& keywords)
            {
                for (size_t idx = 0, end = keywords.size(); idx < end; idx += 1) {
                    if (!filterable->Has_Keyword(keywords[idx])) {
                        return Result_e::ISNT_MATCH;
                    }
                }
                return Result_e::IS_MATCH;
            }

            template <const Logic_Gate_e::value_type MODE, std::enable_if_t<MODE == Logic_Gate_e::XOR, Bool_t> = true>
            static Result_e Run(some<Reference_t*> filterable, Vector_t<some<Keyword_t*>>& keywords)
            {
                Bool_t did_match = false;
                for (size_t idx = 0, end = keywords.size(); idx < end; idx += 1) {
                    if (filterable->Has_Keyword(keywords[idx])) {
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
        class Filter_f<some<Keyword_t*>>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, some<Keyword_t*> keyword, Bool_t do_negate)
            {
                SKYLIB_ASSERT_SOME(keyword);
                self->Filter<some<Keyword_t*>>
                    (do_negate, keyword, &Compare_f<Filterable_t, some<Keyword_t*>>::Run<MODE>);
            }
        };

        template <>
        class Filter_f<Vector_t<some<Keyword_t*>>&>
        {
        public:
            template <const Logic_Gate_e::value_type MODE>
            static void Run(Filter_i<Filterable_t>* self, Vector_t<some<Keyword_t*>>& keywords, Bool_t do_negate)
            {
                self->Filter<Vector_t<some<Keyword_t*>>&>
                    (do_negate, keywords, &Compare_f<Filterable_t, Vector_t<some<Keyword_t*>>&>::Run<MODE>);
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
