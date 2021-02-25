/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/collections.h"

#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/alias_reference.h"
#include "doticu_skylib/reference.h"
#include "doticu_skylib/scrap_array.inl"

#include "doticu_skylib/virtual_arguments.h"
#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_policy.h"
#include "doticu_skylib/virtual_variable.inl"

namespace doticu_skylib {

    Bool_t Alias_Base_t::Is_Quest_Item()
    {
        return (this->alias_base_flags & Alias_Base_Flags_e::IS_QUEST_ITEM) != 0;
    }

    void Alias_Base_t::Ready_Virtual_Object()
    {
        Virtual::Machine_t* machine = Virtual::Machine_t::Self();
        Virtual::Object_t* object = nullptr;
        machine->Find_Bound_Object(this, "ReferenceAlias", &object);
        if (object == nullptr) {
            String_t class_name = "ReferenceAlias";
            machine->Create_Object2(&class_name, &object);
            if (object != nullptr) {
                machine->Object_Policy()->Bind_Object(&object, Virtual::Handle_t(this));
            }
        }
    }

    void Alias_Base_t::Fill(some<Reference_t*> reference, maybe<Virtual::Callback_i*> vcallback)
    {
        SKYLIB_ASSERT_SOME(reference);

        struct Arguments_t : public Virtual::Arguments_t
        {
            Reference_t* reference;
            Arguments_t(Reference_t* reference) :
                reference(reference)
            {
            }
            Bool_t operator()(Scrap_Array_t<Virtual::Variable_t>* variables)
            {
                variables->Resize(1);
                variables->At(0).Pack(reference);
                return true;
            }
        } varguments(reference());

        Ready_Virtual_Object();
        Virtual::Machine_t::Self()->Call_Method(
            static_cast<Alias_Reference_t*>(this),
            "ReferenceAlias",
            "ForceRefTo",
            &varguments,
            vcallback
        );
    }

    void Alias_Base_t::Unfill(maybe<Virtual::Callback_i*> vcallback)
    {
        Ready_Virtual_Object();
        Virtual::Machine_t::Self()->Call_Method(
            static_cast<Alias_Reference_t*>(this),
            "ReferenceAlias",
            "Clear",
            none<Virtual::Arguments_i*>(),
            vcallback
        );
    }

    void Alias_Base_t::Reference(some<Virtual::Callback_i*> vcallback)
    {
        SKYLIB_ASSERT_SOME(vcallback);

        Ready_Virtual_Object();
        Virtual::Machine_t::Self()->Call_Method(
            static_cast<Alias_Reference_t*>(this),
            "ReferenceAlias",
            "GetReference",
            none<Virtual::Arguments_i*>(),
            vcallback()
        );
    }

    void Alias_Base_t::Reference(some<Callback_i<Reference_t*>*> ucallback)
    {
        SKYLIB_ASSERT_SOME(ucallback);

        using UCallback_t = Callback_i<Reference_t*>;

        class VCallback_t : public Virtual::Callback_t
        {
        public:
            UCallback_t* ucallback;
            VCallback_t(UCallback_t* ucallback) :
                ucallback(ucallback)
            {
            }
            void operator()(Virtual::Variable_t* result)
            {
                if (result) {
                    ucallback->operator()(result->Unpack<Reference_t*>());
                    delete ucallback;
                } else {
                    ucallback->operator()(nullptr);
                    delete ucallback;
                }
            }
        };

        Reference(new VCallback_t(ucallback()));
    }

}
