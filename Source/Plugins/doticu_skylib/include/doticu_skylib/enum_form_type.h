/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/enum.h"
#include "doticu_skylib/maybe.h"

namespace doticu_skylib {

    using Raw_Form_Type_t = u8;

    class Raw_Form_Type_e :
        public Enum_Base_t<Raw_Form_Type_t>
    {
    public:
        enum enum_type : Raw_Form_Type_t
        {
            _NONE_                  = static_cast<Raw_Form_Type_t>(-1),

            FORM                    = 0x00,
            // 0x01 TES4
            // 0x02 GRUP
            // 0x03 GMST
            KEYWORD                 = 0x04, // KYWD
            LOCATION_REFERENCE_TYPE = 0X05, // LCRT
            // 0x06 AACT
            TEXTURE_SET             = 0x07, // TXST
            MENU_ICON               = 0x08, // MICN
            GLOBAL                  = 0x09, // GLOB
            // 0x0A CLAS
            FACTION                 = 0x0B, // FACT
            // 0x0C HDPT
            // 0x0D EYES
            RACE                    = 0x0E, // RACE
            // 0x0F SOUN
            // 0x10 ASPC
            // 0x11 SKIL
            MAGIC_EFFECT            = 0x12, // MGEF
            SCRIPT                  = 0x13, // SCPT
            // 0x14 LTEX
            ENCHANTMENT             = 0x15, // ENCH
            SPELL                   = 0x16, // SPEL
            SCROLL                  = 0x17, // SCRL
            ACTIVATOR               = 0x18, // ACTI
            // 0x19 TACT
            ARMOR                   = 0x1A, // ARMO
            BOOK                    = 0x1B, // BOOK
            CONTAINER               = 0x1C, // CONT
            // 0x1D DOOR
            INGREDIENT              = 0x1E, // INGR
            LIGHT                   = 0x1F, // LIGH
            MISC                    = 0x20, // MISC
            // 0x21 APPA
            STATIC                  = 0x22, // STAT
            // 0x23 SCOL
            // 0x24 MSTT
            // 0x25 GRAS
            // 0x26 TREE
            FLORA                   = 0x27, // FLOR
            FURNITURE               = 0x28, // FURN
            WEAPON                  = 0x29, // WEAP
            AMMO                    = 0x2A, // AMMO
            ACTOR_BASE              = 0x2B, // NPC_
            LEVELED_ACTOR_BASE      = 0x2C, // LVLN
            KEY                     = 0x2D, // KEYM
            POTION                  = 0x2E, // ALCH
            // 0x2F IDLM
            // 0x30 NOTE
            // 0x31 COBJ
            PROJECTILE              = 0x32, // PROJ
            // 0x33 HAZD
            SOUL_GEM                = 0x34, // SLGM
            LEVELED_ITEM            = 0x35, // LVLI
            // 0x36 WTHR
            // 0x37 CLMT
            // 0x38 SPGD
            // 0x39 RFCT
            // 0x3A REGN
            // 0x3B NAVI
            CELL                    = 0x3C, // CELL
            REFERENCE               = 0x3D, // REFR
            ACTOR                   = 0x3E, // ACHR
            // 0x3F PMIS
            // 0x40 PARW
            // 0x41 PGRE
            // 0x42 PBEA
            // 0x43 PFLA
            // 0x44 PCON
            // 0x45 PBAR
            // 0x46 PHZD
            WORLDSPACE              = 0x47, // WRLD
            // 0x48 LAND
            // 0x49 NAVM
            // 0x4A TLOD
            DIALOGUE_TOPIC          = 0x4B, // DIAL
            DIALOGUE_INFO           = 0x4C, // INFO
            QUEST                   = 0x4D, // QUST
            // 0x4E IDLE
            PACKAGE                 = 0x4F, // PACK
            COMBAT_STYLE            = 0x50, // CSTY
            // 0x51 LSCR
            // 0x52 LVSP
            // 0x53 ANIO
            // 0x54 WATR
            EFFECT_SHADER           = 0x55, // EFSH
            // 0x56 TOFT
            // 0x57 EXPL
            // 0x58 DEBR
            // 0x59 IMGS
            // 0x5A IMAD
            FORM_LIST               = 0x5B, // FLST
            PERK                    = 0x5C, // PERK
            // 0x5D BPTD
            // 0x5E ADDN
            // 0x5F AVIF
            // 0x60 CAMS
            // 0x61 CPTH
            VOICE_TYPE              = 0x62, // VTYP
            // 0x63 MATT
            // 0x64 IPCT
            // 0x65 IPDS
            // 0x66 ARMA
            ENCOUNTER_ZONE          = 0x67, // ECZN
            LOCATION                = 0x68, // LCTN
            MESSAGE                 = 0x69, // MESG
            // 0x6A RGDL
            // 0x6B DOBJ
            // 0x6C LGTM
            // 0x6D MUSC
            // 0x6E FSTP
            // 0x6F FSTS
            // 0x70 SMBN
            // 0x71 SMQN
            // 0x72 SMEN
            DIALOGUE_BRANCH         = 0x73, // DLBR
            // 0x74 MUST
            // 0x75 DLVW
            // 0x76 WOOP
            // 0x77 SHOU
            // 0x78 EQUP
            RELATION                = 0x79, // RELA
            // 0x7A SCEN
            ASSOCIATION             = 0x7B, // ASTP
            OUTFIT                  = 0x7C, // OTFT
            // 0x7D ARTO
            // 0x7E MATO
            // 0x7F MOVT
            // 0x80 SNDR
            // 0x81 DUAL
            // 0x82 SNCT
            // 0x83 SOPM
            // 0x84 COLL
            COLOR                   = 0x85, // CLFM
            // 0x86 REVB
            // 0x87 LENS
            // 0x88 LSPR
            // 0x89 VOLI

            _TOTAL_                 = 0x8A,
        };

    public:
        static some<const char* const*> Strings();
        static some<const char*>        To_String(Raw_Form_Type_t raw_form_type);
        static Raw_Form_Type_t          From_String(maybe<const char*> raw_form_type);
    };

    class Form_Type_e :
        public Raw_Form_Type_e,
        public Enum_t<Raw_Form_Type_t>
    {
    public:
        using Enum_t::Enum_t;

    public:
        some<const char*> As_String() const;
    };
    STATIC_ASSERT(sizeof(Form_Type_e) == 0x1);

    template <>
    class none<Form_Type_e>
    {
    public:
        using value_type = Form_Type_e;

    private:
        Form_Type_e value;

    public:
        none() : value(Form_Type_e::_TOTAL_) {}

        Form_Type_e operator()() { return value; }
        Form_Type_e operator()() const { return value; }

        friend Bool_t operator==(const none<Form_Type_e>& a, const Form_Type_e b) { return b < Form_Type_e::FORM || b >= Form_Type_e::_TOTAL_; }
        friend Bool_t operator==(const Form_Type_e a, const none<Form_Type_e>& b) { return a < Form_Type_e::FORM || a >= Form_Type_e::_TOTAL_; }
        friend Bool_t operator==(const none<Form_Type_e>&& a, const Form_Type_e b) { return b < Form_Type_e::FORM || b >= Form_Type_e::_TOTAL_; }
        friend Bool_t operator==(const Form_Type_e a, const none<Form_Type_e>&& b) { return a < Form_Type_e::FORM || a >= Form_Type_e::_TOTAL_; }
        friend Bool_t operator!=(const none<Form_Type_e>& a, const Form_Type_e b) { return !(a == b); }
        friend Bool_t operator!=(const Form_Type_e a, const none<Form_Type_e>& b) { return !(a == b); }
        friend Bool_t operator!=(const none<Form_Type_e>&& a, const Form_Type_e b) { return !(a == b); }
        friend Bool_t operator!=(const Form_Type_e a, const none<Form_Type_e>&& b) { return !(a == b); }
    };

    template <>
    class maybe<Form_Type_e>
    {
    public:
        using value_type = Form_Type_e;

    private:
        Form_Type_e value;

    public:
        maybe() : value(none<Form_Type_e>()()) {}
        maybe(Form_Type_e value) : value(value) {}
        maybe(const none<Form_Type_e> other) : value(other()) {}
        maybe(const maybe<Form_Type_e>& other) : value(other.value) {}
        maybe(maybe<Form_Type_e>&& other) noexcept : value(std::exchange(other.value, none<Form_Type_e>()())) {}

        maybe<Form_Type_e>& operator=(const maybe<Form_Type_e>& other)
        {
            if (this != std::addressof(other)) {
                value = other.value;
            }
            return *this;
        }
        maybe<Form_Type_e>& operator=(maybe<Form_Type_e>&& other)
        {
            if (this != std::addressof(other)) {
                value = std::exchange(other.value, none<Form_Type_e>()());
            }
            return *this;
        }

        Form_Type_e operator()() { return value; }
        Form_Type_e operator()() const { return value; }

        Bool_t operator==(const maybe<Form_Type_e>& other) { return value == other(); }
        Bool_t operator==(const maybe<Form_Type_e>& other) const { return value == other(); }
        Bool_t operator!=(const maybe<Form_Type_e>& other) { return !operator==(other); }
        Bool_t operator!=(const maybe<Form_Type_e>& other) const { return !operator==(other); }

        explicit operator Bool_t() { return value != none<Form_Type_e>(); }
        explicit operator Bool_t() const { return value != none<Form_Type_e>(); }

        Bool_t operator !() { return !static_cast<Bool_t>(*this); }
        Bool_t operator !() const { return !static_cast<Bool_t>(*this); }

        template <typename TT>
        operator maybe<TT>() { return static_cast<TT>(value); }
        template <typename TT>
        operator maybe<TT>() const { return static_cast<TT>(value); }
    };

    template <>
    class some<Form_Type_e>
    {
    public:
        using value_type = Form_Type_e;

    private:
        Form_Type_e value;

    public:
        some() = delete;
        some(Form_Type_e value) : value(value) {}
        some(const some<Form_Type_e>& other) : value(other.value) {}
        some(some<Form_Type_e>&& other) noexcept : value(std::exchange(other.value, none<Form_Type_e>()())) {}

        some<Form_Type_e>& operator=(const some<Form_Type_e>& other)
        {
            if (this != std::addressof(other)) {
                value = other.value;
            }
            return *this;
        }
        some<Form_Type_e>& operator=(some<Form_Type_e>&& other) noexcept
        {
            if (this != std::addressof(other)) {
                value = std::exchange(other.value, none<Form_Type_e>()());
            }
            return *this;
        }

        Form_Type_e operator()() { return value; }
        Form_Type_e operator()() const { return value; }

        Bool_t operator==(const some<Form_Type_e>& other) { return value == other(); }
        Bool_t operator==(const some<Form_Type_e>& other) const { return value == other(); }
        Bool_t operator!=(const some<Form_Type_e>& other) { return !operator==(other); }
        Bool_t operator!=(const some<Form_Type_e>& other) const { return !operator==(other); }

        explicit operator Bool_t() { return value != none<Form_Type_e>(); }
        explicit operator Bool_t() const { return value != none<Form_Type_e>(); }

        Bool_t operator !() { return !static_cast<Bool_t>(*this); }
        Bool_t operator !() const { return !static_cast<Bool_t>(*this); }

        template <typename TT>
        operator some<TT>() { return static_cast<TT>(value); }
        template <typename TT>
        operator some<TT>() const { return static_cast<TT>(value); }
    };

}
