/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/scrap_array.inl"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_utility.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib { namespace Virtual {

    void Utility_t::Wait_Out_Of_Menu(Float_t seconds, some<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Float_t seconds;

        public:
            Virtual_Arguments(Float_t seconds) :
                seconds(seconds)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Float_t>(seconds);
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "Wait",
            Virtual_Arguments(seconds),
            v_callback()
        );
    }

    void Utility_t::Wait_Out_Of_Menu(Float_t seconds, some<unique<doticu_skylib::Callback_i<>>> callback)
    {
        using Callback = some<unique<doticu_skylib::Callback_i<>>>;

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
            virtual void operator()(Virtual::Variable_t*) override
            {
                (*this->callback)();
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        Wait_Out_Of_Menu(seconds, new Virtual_Callback(std::move(callback)));
    }

    void Utility_t::Wait_Even_In_Menu(Float_t seconds, some<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Float_t seconds;

        public:
            Virtual_Arguments(Float_t seconds) :
                seconds(seconds)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Float_t>(seconds);
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "WaitMenuMode",
            Virtual_Arguments(seconds),
            v_callback()
        );
    }

    void Utility_t::Wait_Even_In_Menu(Float_t seconds, some<unique<doticu_skylib::Callback_i<>>> callback)
    {
        using Callback = some<unique<doticu_skylib::Callback_i<>>>;

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
            virtual void operator()(Virtual::Variable_t*) override
            {
                (*this->callback)();
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        Wait_Even_In_Menu(seconds, new Virtual_Callback(std::move(callback)));
    }

    void Utility_t::Wait_For_Game_Time(Float_t hours, some<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Float_t hours;

        public:
            Virtual_Arguments(Float_t hours) :
                hours(hours)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Float_t>(hours);
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "WaitGameTime",
            Virtual_Arguments(hours),
            v_callback()
        );
    }

    void Utility_t::Wait_For_Game_Time(Float_t hours, some<unique<doticu_skylib::Callback_i<>>> callback)
    {
        using Callback = some<unique<doticu_skylib::Callback_i<>>>;

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
            virtual void operator()(Virtual::Variable_t*) override
            {
                (*this->callback)();
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        Wait_For_Game_Time(hours, new Virtual_Callback(std::move(callback)));
    }

    void Utility_t::Is_In_Menu_Mode(some<Virtual::Callback_i*> v_callback)
    {
        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "IsInMenuMode",
            none<Virtual::Arguments_i*>(),
            v_callback()
        );
    }

    void Utility_t::Is_In_Menu_Mode(some<unique<doticu_skylib::Callback_i<Bool_t>>> callback)
    {
        using Callback = some<unique<doticu_skylib::Callback_i<Bool_t>>>;

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
                (*this->callback)(result ? result->As<Bool_t>() : false);
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        Is_In_Menu_Mode(new Virtual_Callback(std::move(callback)));
    }

    void Utility_t::To_Game_Time_String(Float_t days_passed, some<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            Float_t days_passed;

        public:
            Virtual_Arguments(Float_t days_passed) :
                days_passed(days_passed)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<Float_t>(this->days_passed);
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(v_callback);

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "GameTimeToString",
            Virtual_Arguments(days_passed),
            v_callback()
        );
    }

    void Utility_t::To_Game_Time_String(Float_t days_passed, some<unique<doticu_skylib::Callback_i<String_t>>> callback)
    {
        using Callback = some<unique<doticu_skylib::Callback_i<String_t>>>;

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
                (*this->callback)(result ? result->As<String_t>() : "");
            }
        };

        SKYLIB_ASSERT_SOME(callback);

        To_Game_Time_String(days_passed, new Virtual_Callback(std::move(callback)));
    }

}}
