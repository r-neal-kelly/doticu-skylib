/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/extra_data.inl"
#include "doticu_skylib/extra_text_display.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/message.h"
#include "doticu_skylib/quest.h"

namespace doticu_skylib {

    Extra_Text_Display_t::Type_Or_Instance_u::Type_Or_Instance_u() :
        type(Extra_Text_Display_Type_e::DEFAULT)
    {
    }

    Extra_Text_Display_t::Type_Or_Instance_u::~Type_Or_Instance_u()
    {
        this->type = Extra_Text_Display_Type_e::DEFAULT;
    }

    some<Extra_Text_Display_t*> Extra_Text_Display_t::Create()
    {
        some<Extra_Text_Display_t*> x_text_display = Extra_Data_t::Create<Extra_Text_Display_t>();

        x_text_display->name = "";
        x_text_display->message = none<Message_t*>();
        x_text_display->owning_quest = none<Quest_t*>();
        x_text_display->type_or_instance.type = Extra_Text_Display_Type_e::DEFAULT;
        x_text_display->temper_level = Temper_Level_e::STANDARD;
        x_text_display->name_length = 0;
        x_text_display->pad_32 = 0;
        x_text_display->pad_34 = 0;

        return x_text_display;
    }

    some<Extra_Text_Display_t*> Extra_Text_Display_t::Create(String_t name)
    {
        some<Extra_Text_Display_t*> x_text_display = Create();

        x_text_display->Name(name, true);

        return x_text_display;
    }

    some<Extra_Text_Display_t*> Extra_Text_Display_t::Create(const Extra_Text_Display_t& other)
    {
        some<Extra_Text_Display_t*> x_text_display = Extra_Data_t::Create<Extra_Text_Display_t>();

        x_text_display->name = other.name;
        x_text_display->message = other.message;
        x_text_display->owning_quest = other.owning_quest;
        x_text_display->type_or_instance.type = other.type_or_instance.type;
        x_text_display->temper_level = other.temper_level;
        x_text_display->name_length = other.name_length;
        x_text_display->pad_32 = other.pad_32;
        x_text_display->pad_34 = other.pad_34;

        return x_text_display;
    }

    void Extra_Text_Display_t::Destroy(some<Extra_Text_Display_t*> x_text_display)
    {
        SKYLIB_ASSERT_SOME(x_text_display);

        Extra_Data_t::Destroy<Extra_Text_Display_t>(x_text_display);
    }

    Bool_t Extra_Text_Display_t::Is_Custom()
    {
        return this->type_or_instance.type == Extra_Text_Display_Type_e::CUSTOM;
    }

    maybe<String_t> Extra_Text_Display_t::Name()
    {
        if (Is_Custom()) {
            return this->name;
        } else {
            return none<String_t>();
        }
    }

    void Extra_Text_Display_t::Name(String_t name, Bool_t do_force)
    {
        static auto set_name = reinterpret_cast
            <void(*)(Extra_Text_Display_t*, const char*)>
            (Game_t::Base_Address() + Offset_e::SET_NAME);

        if (do_force) {
            this->message = nullptr;
            this->owning_quest = nullptr;
        }

        set_name(this, name);
    }

    void Extra_Text_Display_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Extra_Text_Display_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "name: %s", this->name ? name : "");
        if (this->message) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "message: %s", this->message->Description(this->message())());
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "message: (nullptr)");
        }
        if (this->owning_quest) {
            SKYLIB_LOG(indent + SKYLIB_TAB + "owner: %s", this->owning_quest->Any_Name());
            SKYLIB_LOG(indent + SKYLIB_TAB + "owner_instance: %i", this->type_or_instance.owning_quest_instance);
        } else {
            SKYLIB_LOG(indent + SKYLIB_TAB + "owner: (nullptr)");
            SKYLIB_LOG(indent + SKYLIB_TAB + "type: %i", this->type_or_instance.type);
        }

        SKYLIB_LOG(indent + SKYLIB_TAB + "temper_level: %s", this->temper_level.As_String()());
        SKYLIB_LOG(indent + SKYLIB_TAB + "name_length: %u", this->name_length);

        SKYLIB_LOG(indent + "}");
    }

}
