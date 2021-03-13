/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/message.h"
#include "doticu_skylib/quest.h"

#include "doticu_skylib/extra_text_display.h"

namespace doticu_skylib {

    void Extra_Text_Display_t::Name(some<const char*> name, Bool_t do_force)
    {
        static auto set_name = reinterpret_cast
            <void(*)(Extra_Text_Display_t*, const char*)>
            (Game_t::Base_Address() + Offset_e::SET_NAME);

        SKYLIB_ASSERT_SOME(name);

        if (do_force) {
            this->message = nullptr;
            this->owner = nullptr;
        }
        set_name(this, name());
    }

    void Extra_Text_Display_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Text_Display_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "name: %s", this->name ? name.data : "");
        if (this->message) {
            DString_t message_dstring = this->message->Description(this->message());
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

        SKYLIB_LOG(indent + SKYLIB_TAB + "temper_level: %s", this->temper_level.As_String()());
        SKYLIB_LOG(indent + SKYLIB_TAB + "name_length: %u", this->name_length);

        SKYLIB_LOG(indent + "}");
    }

}
