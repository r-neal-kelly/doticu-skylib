/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/reference.h"
#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_debug.h"
#include "doticu_skylib/virtual_machine.inl"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib { namespace Virtual {

    void Debug_t::Create_Message_Box(String_t message, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            String_t message;

        public:
            Virtual_Arguments(String_t message) :
                message(message)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<String_t>(this->message);
                return true;
            }
        };

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "MessageBox",
            Virtual_Arguments(message),
            v_callback
        );
    }

    void Debug_t::Create_Message_Box(String_t message, maybe<unique<doticu_skylib::Callback_i<>>> callback)
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
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Create_Message_Box(message, new Virtual_Callback(std::move(callback)));
    }

    void Debug_t::Create_Notification(String_t note, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            String_t note;

        public:
            Virtual_Arguments(String_t note) :
                note(note)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(1);
                args->At(0).As<String_t>(this->note);
                return true;
            }
        };

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "Notification",
            Virtual_Arguments(note),
            v_callback
        );
    }

    void Debug_t::Create_Notification(String_t note, maybe<unique<doticu_skylib::Callback_i<>>> callback)
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
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Create_Notification(note, new Virtual_Callback(std::move(callback)));
    }

    void Debug_t::Send_Animation_Event(some<Reference_t*> reference,
                                       String_t event_name,
                                       maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            some<Reference_t*>  reference;
            String_t            event_name;

        public:
            Virtual_Arguments(some<Reference_t*> reference, String_t event_name) :
                reference(reference), event_name(event_name)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(2);
                args->At(0).As<Reference_t*>(this->reference());
                args->At(1).As<String_t>(this->event_name);
                return true;
            }
        };

        SKYLIB_ASSERT_SOME(reference);

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "SendAnimationEvent",
            Virtual_Arguments(reference, event_name),
            v_callback
        );
    }

    void Debug_t::Send_Animation_Event(some<Reference_t*> reference,
                                       String_t event_name,
                                       maybe<unique<doticu_skylib::Callback_i<>>> callback)
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
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        SKYLIB_ASSERT_SOME(reference);

        Send_Animation_Event(reference, event_name, new Virtual_Callback(std::move(callback)));
    }

    void Debug_t::Trace(String_t note, Int_t severity, maybe<Virtual::Callback_i*> v_callback)
    {
        class Virtual_Arguments :
            public Virtual::Arguments_t
        {
        public:
            String_t    note;
            Int_t       severity;

        public:
            Virtual_Arguments(String_t note, Int_t severity) :
                note(note), severity(severity)
            {
            }

        public:
            virtual Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* args) override
            {
                args->Resize(2);
                args->At(0).As<String_t>(this->note);
                args->At(1).As<Int_t>(this->severity);
                return true;
            }
        };

        Virtual::Machine_t::Self()->Call_Global(
            SCRIPT_NAME,
            "Trace",
            Virtual_Arguments(note, severity),
            v_callback
        );
    }

    void Debug_t::Trace(String_t note, Int_t severity, maybe<unique<doticu_skylib::Callback_i<>>> callback)
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
            virtual void operator()(Virtual::Variable_t*) override
            {
                if (this->callback) {
                    (*this->callback)();
                }
            }
        };

        Trace(note, severity, new Virtual_Callback(std::move(callback)));
    }

}}
