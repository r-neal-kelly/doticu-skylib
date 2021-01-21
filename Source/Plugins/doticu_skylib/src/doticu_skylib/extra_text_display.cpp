/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/message.h"
#include "doticu_skylib/quest.h"

#include "doticu_skylib/extra_text_display.h"

namespace doticu_skylib {

    void Text_Display_x::Name(some<const char*> name, Bool_t do_force)
    {
        static auto set_name = reinterpret_cast
            <void(*)(Text_Display_x*, const char*)>
            (Game_t::Base_Address() + Offset_e::SET_NAME);

        SKYLIB_ASSERT_SOME(name);

        if (do_force) {
            this->message = nullptr;
            this->owner = nullptr;
        }
        set_name(this, name());
    }

    void Text_Display_x::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Text_Display_x::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "name: %s", this->name ? name.data : "");
        if (this->message) {
            DString_t message_dstring = this->message->Description(this->message);
            SKYLIB_LOG(indent + SKYLIB_TAB + "message: %s", message_dstring ? message_dstring.data : "");
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "message: (nullptr)");
        }
        if (this->owner) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "owner: %s", this->owner->Any_Name().data);
            SKYLIB_LOG(indent + SKYLIB_TAB + "owner_instance: %i", this->conditional.owner_instance);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "owner: (nullptr)");
            SKYLIB_LOG(indent + SKYLIB_TAB + "type: %i", this->conditional.type);
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "temper_health: %f", this->temper_health);
        SKYLIB_LOG(indent + SKYLIB_TAB + "custom_length: %u", this->custom_length);

        SKYLIB_LOG(indent + "}");
    }

}
