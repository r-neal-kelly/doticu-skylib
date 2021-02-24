/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/form_factory.h"
#include "doticu_skylib/game.h"

namespace doticu_skylib {

    some<Form_Factory_i*> Form_Factory_i::Form_Factory(some<Form_Type_e> form_type)
    {
        class Form_Factories_t
        {
        public:
            Form_Factory_i* factories[138];
        };

        static auto factories = reinterpret_cast
            <Form_Factories_t*>
            (Game_t::Base_Address() + Offset_e::FACTORIES);
        static Bool_t is_created = *reinterpret_cast
            <Bool_t*>
            (Game_t::Base_Address() + Offset_e::IS_CREATED);

        SKYLIB_ASSERT(is_created);
        SKYLIB_ASSERT_SOME(form_type);

        return factories->factories[form_type()];
    }

}
