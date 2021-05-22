/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/player_objective.h"
#include "doticu_skylib/quest.h"
#include "doticu_skylib/quest_objective.h"

namespace doticu_skylib {

    String_t Player_Objective_t::Parse_Display_Text(some<Quest_Objective_t*> objective, u32 instance_id)
    {
        static auto Read = [](const char* src,
                              size_t& idx,
                              std::string& tag,
                              std::string& sub,
                              std::string& val)->Bool_t
        {
            SKYLIB_ASSERT(src[idx] == '<');

            size_t idx_orig = idx;

            tag = "";
            sub = "";
            val = "";

            idx += 1;
            while (src[idx] != '.' && src[idx] != '=' && src[idx] != '>') {
                if (!src[idx]) {
                    idx = idx_orig;
                    return false;
                }
                tag += src[idx];
                idx += 1;
            }

            if (src[idx] == '>') {
                idx += 1;
                return true;
            }

            if (src[idx] == '.') {
                idx += 1;
                if (src[idx] == '=') {
                    idx = idx_orig;
                    return false;
                }

                while (src[idx] != '=') {
                    if (!src[idx]) {
                        idx = idx_orig;
                        return false;
                    } else if (src[idx] == '>') {
                        idx = idx_orig;
                        return false;
                    }
                    sub += src[idx];
                    idx += 1;
                }
            }

            SKYLIB_ASSERT(src[idx] == '=');

            idx += 1;
            if (src[idx] == '>') {
                idx = idx_orig;
                return false;
            }

            while (src[idx] != '>') {
                if (!src[idx]) {
                    idx = idx_orig;
                    return false;
                }
                val += src[idx];
                idx += 1;
            }
            idx += 1;

            return true;
        };

        SKYLIB_ASSERT_SOME(objective);

        if (objective->quest && objective->display_text) {
            const char* src = objective->display_text;
            const size_t src_len = CString_t::Length(src, true);

            std::string res;
            res.reserve(src_len * 1.5f);

            std::string tag;
            tag.reserve(16);

            std::string sub;
            sub.reserve(16);

            std::string val;
            val.reserve(16);

            for (size_t idx = 0; idx < src_len;) {
                if (src[idx] == '<' && Read(src, idx, tag, sub, val)) {
                    res += objective->quest->Replacement_Text(
                        tag.c_str(),
                        sub.c_str(),
                        val.c_str(),
                        instance_id
                    );
                } else {
                    res += src[idx];
                    idx += 1;
                }
            }

            return res;
        } else {
            return "";
        }
    }

    Player_Objective_t::Player_Objective_t() :
        objective(none<Quest_Objective_t*>()), instance_id(0), state(Quest_Objective_State_e::_NONE_)
    {
    }

    Player_Objective_t::Player_Objective_t(some<Quest_Objective_t*> objective, u32 instance_id) :
        objective(objective()), instance_id(instance_id), state(objective->state)
    {
    }

    Player_Objective_t::Player_Objective_t(const Player_Objective_t& other) :
        objective(other.objective), instance_id(other.instance_id), state(objective->state)
    {
    }

    Player_Objective_t::Player_Objective_t(Player_Objective_t&& other) noexcept :
        objective(std::move(other.objective)), instance_id(std::move(other.instance_id)), state(objective->state)
    {
    }

    Player_Objective_t& Player_Objective_t::operator =(const Player_Objective_t& other)
    {
        if (this != std::addressof(other)) {
            this->objective = other.objective;
            this->instance_id = other.instance_id;
            if (this->objective) {
                this->state = this->objective->state;
            } else {
                this->state = Quest_Objective_State_e::_NONE_;
            }
        }
        return *this;
    }

    Player_Objective_t& Player_Objective_t::operator =(Player_Objective_t&& other) noexcept
    {
        if (this != std::addressof(other)) {
            this->objective = std::move(other.objective);
            this->instance_id = std::move(other.instance_id);
            if (this->objective) {
                this->state = this->objective->state;
            } else {
                this->state = Quest_Objective_State_e::_NONE_;
            }
        }
        return *this;
    }

    Player_Objective_t::~Player_Objective_t()
    {
    }

    String_t Player_Objective_t::Parse_Display_Text()
    {
        if (this->objective) {
            return Parse_Display_Text(this->objective(), this->instance_id);
        } else {
            return "";
        }
    }

    Bool_t operator ==(const Player_Objective_t& a, const Player_Objective_t& b)
    {
        return
            a.objective == b.objective &&
            a.instance_id == b.instance_id &&
            a.state == b.state;
    }

    Bool_t operator !=(const Player_Objective_t& a, const Player_Objective_t& b)
    {
        return !operator ==(a, b);
    }

    void Player_Objective_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Player_Objective_t::Log");
        SKYLIB_LOG(indent + "{");

        if (this->objective) {
            this->objective->Log(indent + SKYLIB_TAB);
        }
        SKYLIB_LOG(indent + SKYLIB_TAB + "instance_id: %u", instance_id);
        SKYLIB_LOG(indent + SKYLIB_TAB + "state: %s", state.As_String());

        SKYLIB_LOG(indent + "}");
    }

}
