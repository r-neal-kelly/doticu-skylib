/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/collections.h"
#include "doticu_skylib/string.h"

#include "doticu_skylib/component_form_data.h"

#include "doticu_skylib/form_flags.h"
#include "doticu_skylib/form_id.h"
#include "doticu_skylib/form_type.h"

namespace doticu_skylib {

    class Mod_t;
    class Race_t;

    namespace Virtual {

        class Callback_i;

    }

    class Form_t : public Form_Data_c
    {
    public:
        enum
        {
            FORM_TYPE   = Form_Type_e::FORM,
            kTypeID     = FORM_TYPE,
        };

        static Bool_t           Is_Static(Form_ID_t form_id);
        static Bool_t           Is_Dynamic(Form_ID_t form_id);
        static Bool_t           Is_Heavy(Form_ID_t form_id);
        static Bool_t           Is_Light(Form_ID_t form_id);
        static Form_ID_t        Reindex(Form_ID_t form_id, Mod_t* mod);
        static Form_ID_t        Reindex(Form_ID_t form_id, u32 idx);
        //static some<Form_ID_t>  Form_ID(some<Lower_Form_ID_t> lower_form_id, some<Mod_t*> mod);
        static Form_ID_t        Form_ID(Lower_Form_ID_t lower_form_id, some<Mod_t*> mod);

    public:
        virtual             ~Form_t();                              // 00

        virtual void        _01(void) override;                     // 01
        virtual void        _02(void) override;                     // 02
        virtual void        _03(void) override;                     // 03

        virtual void        _04(void);                              // 04
        virtual void        _05(void);                              // 05
        virtual void        _06(void);                              // 06
        virtual void        _07(void);                              // 07
        virtual void        _08(void);                              // 08
        virtual void        _09(void);                              // 09
        virtual void        _0A(void);                              // 0A
        virtual void        _0B(void);                              // 0B
        virtual void        _0C(void);                              // 0C
        virtual void        _0D(void);                              // 0D
        virtual void        _0E(void);                              // 0E
        virtual void        _0F(void);                              // 0F
        virtual void        _10(void);                              // 10
        virtual void        _11(void);                              // 11
        virtual void        _12(void);                              // 12
        virtual void        _13(void);                              // 13
        virtual Mod_t*      Get_Highest_Mod();                      // 14
        virtual void        _15(void);                              // 15
        virtual void        _16(void);                              // 16
        virtual void        _17(void);                              // 17
        virtual void        _18(void);                              // 18
        virtual void        _19(void);                              // 19
        virtual void        _1A(void);                              // 1A
        virtual void        _1B(void);                              // 1B
        virtual void        _1C(void);                              // 1C
        virtual void        _1D(void);                              // 1D
        virtual void        _1E(void);                              // 1E
        virtual void        _1F(void);                              // 1F
        virtual void        _20(void);                              // 20
        virtual void        _21(void);                              // 21
        virtual void        _22(void);                              // 22
        virtual void        _23(void);                              // 23
        virtual void        _24(void);                              // 24
        virtual void        _25(void);                              // 25
        virtual void        _26(void);                              // 26
        virtual void        _27(void);                              // 27
        virtual void        _28(void);                              // 28
        virtual void        _29(void);                              // 29
        virtual void        _2A(void);                              // 2A
        virtual void        _2B(void);                              // 2B
        virtual void        _2C(void);                              // 2C
        virtual void        _2D(void);                              // 2D
        virtual void        _2E(void);                              // 2E
        virtual void        _2F(void);                              // 2F
        virtual void        _30(void);                              // 30
        virtual void        _31(void);                              // 31
        virtual const char* Get_Editor_ID();                        // 32
        virtual Bool_t      Set_Editor_ID(const char* editor_id);   // 33
        virtual void        _34(void);                              // 34
        virtual void        _35(void);                              // 35
        virtual void        _36(void);                              // 36
        virtual void        _37(void);                              // 37
        virtual void        _38(void);                              // 38
        virtual void        _39(void);                              // 39
        virtual void        _3A(void);                              // 3A

    public:
        Static_Array_t<Mod_t*>* form_mods;      // 08
        Form_Flags_e            form_flags;     // 10
        Form_ID_t               form_id;        // 14
        u16                     form_flags2;    // 18
        Form_Type_e             form_type;      // 1A
        u8                      pad_1B;         // 1B
        u32                     pad_1C;         // 1C

    public:
        Bool_t              Is_Valid();
        Bool_t              Is_Static();
        Bool_t              Is_Dynamic();
        Bool_t              Is_Heavy();
        Bool_t              Is_Light();
        Mod_t*              Indexed_Mod();
        Bool_t              Has_Indexed_Mod(const char* mod_name);

        Vector_t<Mod_t*>    Mods();

        String_t            Form_ID_String();
        Vector_t<String_t>  Mod_Names();
        void                Mod_Names(Vector_t<String_t>& results);

    public:
        void                Register_Mod_Event(String_t event_name, String_t callback_name, Virtual::Callback_i* vcallback = nullptr);
        void                Unregister_Mod_Event(String_t event_name, Virtual::Callback_i* vcallback = nullptr);
        void                Unregister_Mod_Events(Virtual::Callback_i* vcallback = nullptr);
    };
    STATIC_ASSERT(sizeof(Form_t) == 0x20);

}
