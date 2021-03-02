/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/game.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_game.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib { namespace Virtual {

    some<Game_t*> Game_t::Self()
    {
        static auto self = *reinterpret_cast
            <Game_t**>
            (doticu_skylib::Game_t::Base_Address() + Offset_e::SELF);

        SKYLIB_ASSERT(self);
        return self;
    }

    void Game_t::Force_First_Person(maybe<Virtual::Callback_i*> v_callback)
    {
        Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "ForceFirstPerson",
            none<Virtual::Arguments_i*>(),
            v_callback
        );
    }

    void Game_t::Force_First_Person(maybe<unique<doticu_skylib::Callback_i<>>> callback)
    {
        using Callback = maybe<unique<doticu_skylib::Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator () (Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Force_First_Person(new Virtual_Callback(std::move(callback)));
    }

    void Game_t::Force_Third_Person(maybe<Virtual::Callback_i*> v_callback)
    {
        Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "ForceThirdPerson",
            none<Virtual::Arguments_i*>(),
            v_callback
        );
    }

    void Game_t::Force_Third_Person(maybe<unique<doticu_skylib::Callback_i<>>> callback)
    {
        using Callback = maybe<unique<doticu_skylib::Callback_i<>>>;

        class Virtual_Callback :
            public Virtual::Callback_t
        {
        public:
            Callback callback;

        public:
            Virtual_Callback(Callback callback) :
                callback(std::move(callback))
            {
            }

        public:
            virtual void operator () (Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Force_Third_Person(new Virtual_Callback(std::move(callback)));
    }

}}
