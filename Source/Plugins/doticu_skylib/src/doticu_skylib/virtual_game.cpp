/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/actor.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/reference.h"
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

    void Game_t::Current_Crosshair_Reference(some<Virtual::Callback_i*> v_callback)
    {
        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "GetCurrentCrosshairRef",
            none<Virtual::Arguments_i*>(),
            v_callback()
        );
    }

    void Game_t::Current_Crosshair_Reference(some<unique<doticu_skylib::Callback_i<maybe<Reference_t*>>>> callback)
    {
        using Callback = some<unique<doticu_skylib::Callback_i<maybe<Reference_t*>>>>;

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
            virtual void operator()(Virtual::Variable_t* result) override
            {
                (*this->callback)(result ? result->As<Reference_t*>() : nullptr);
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        Current_Crosshair_Reference(new Virtual_Callback(std::move(callback)));
    }

    void Game_t::Find_Closest_Actor(Float_t origin_x,
                                    Float_t origin_y,
                                    Float_t origin_z,
                                    Float_t radius,
                                    some<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Float_t origin_x;
            Float_t origin_y;
            Float_t origin_z;
            Float_t radius;

        public:
            Virtual_Arguments(Float_t origin_x, Float_t origin_y, Float_t origin_z, Float_t radius) :
                origin_x(origin_x), origin_y(origin_y), origin_z(origin_z), radius(radius)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(4);
                args->At(0).As<Float_t>(this->origin_x);
                args->At(1).As<Float_t>(this->origin_y);
                args->At(2).As<Float_t>(this->origin_z);
                args->At(3).As<Float_t>(this->radius);
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "FindClosestActor",
            Virtual_Arguments(origin_x, origin_y, origin_z, radius),
            v_callback()
        );
    }

    void Game_t::Find_Closest_Actor(Float_t origin_x,
                                    Float_t origin_y,
                                    Float_t origin_z,
                                    Float_t radius,
                                    some<unique<doticu_skylib::Callback_i<maybe<Actor_t*>>>> callback)
    {
        using Callback = some<unique<doticu_skylib::Callback_i<maybe<Actor_t*>>>>;

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
            virtual void operator()(Virtual::Variable_t* result) override
            {
                (*this->callback)(result ? result->As<Actor_t*>() : nullptr);
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        Find_Closest_Actor(origin_x, origin_y, origin_z, radius, new Virtual_Callback(std::move(callback)));
    }

    void Game_t::Find_Closest_Actor_From(some<Reference_t*> origin,
                                         Float_t radius,
                                         some<Virtual::Callback_i*> v_callback)
    {
        SKYLIB_ASSERT_SOME(origin);
        SKYLIB_ASSERT_SOME(v_callback);

        Find_Closest_Actor(origin->position.x, origin->position.y, origin->position.z, radius, v_callback);
    }

    void Game_t::Find_Closest_Actor_From(some<Reference_t*> origin,
                                         Float_t radius,
                                         some<unique<doticu_skylib::Callback_i<maybe<Actor_t*>>>> callback)
    {
        SKYLIB_ASSERT_SOME(origin);
        SKYLIB_ASSERT_SOME(callback);

        Find_Closest_Actor(origin->position.x, origin->position.y, origin->position.z, radius, std::move(callback));
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
