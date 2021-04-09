/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/ai_location_handle.h"
#include "doticu_skylib/alias_id.h"
#include "doticu_skylib/enum_form_type.h"
#include "doticu_skylib/enum_package_location_type.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/reference_handle.h"

namespace doticu_skylib {

    class Cell_t;
    class Form_t;
    class Object_t;
    class Reference_t;

    class Package_Location_t:       // PackageLocation
        public AI_Location_Handle_t // 00
    {
    public:
        union Location_u
        {
        public:
            Alias_ID_t              alias_id;
            maybe<Cell_t*>          cell;
            maybe<Form_Type_e>      form_type;
            maybe<Form_t*>          linked_form;
            maybe<Object_t*>        object;
            Reference_Handle_t      reference_handle;
            u32                     unknown_10;
            u8                      unknown_11;

        public:
            Location_u();
            ~Location_u();
        };
        STATIC_ASSERT(sizeof(Location_u) == 0x08);

    public:
        virtual ~Package_Location_t();

    public:
        Package_Location_Type_e location_type;  // 08
        u8                      pad_09;         // 09
        u16                     pad_0A;         // 0A
        u32                     radius;         // 0C
        Location_u              location;       // 10

    public:
        Alias_ID_t          Alias_ID() const;
        void                Alias_ID(Alias_ID_t alias_id);

        maybe<Cell_t*>      Cell() const;
        void                Cell(maybe<Cell_t*> cell);

        maybe<Form_Type_e>  Form_Type() const;
        void                Form_Type(maybe<Form_Type_e> form_type);

        maybe<Form_t*>      Linked_Form() const;
        void                Linked_Form(maybe<Form_t*> linked_form);

        maybe<Object_t*>    Object() const;
        void                Object(maybe<Object_t*> object);

        u32                 Radius() const;
        void                Radius(u32 radius);

        maybe<Reference_t*> Reference() const;
        void                Reference(maybe<Reference_t*> reference);

    public:
        void    Log(std::string indent = "") const;
    };
    STATIC_ASSERT(sizeof(Package_Location_t) == 0x18);

}
