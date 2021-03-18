/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/const_keyword.h"
#include "doticu_skylib/const_mod.h"
#include "doticu_skylib/game_macros.h"
#include "doticu_skylib/keyword.h"

namespace doticu_skylib { namespace Const { namespace Keyword {

    some<Keyword_t*>    Armor_Boots()                   { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06C0ED); }
    some<Keyword_t*>    Armor_Clothing()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE8); }
    some<Keyword_t*>    Armor_Cuirass()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06C0EC); }
    some<Keyword_t*>    Armor_Gauntlets()               { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06C0EF); }
    some<Keyword_t*>    Armor_Heavy()                   { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBD2); }
    some<Keyword_t*>    Armor_Helmet()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06C0EE); }
    some<Keyword_t*>    Armor_Jewelry()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE9); }
    some<Keyword_t*>    Armor_Light()                   { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBD3); }
    some<Keyword_t*>    Armor_Shield()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0965B2); }
    some<Keyword_t*>    Clothing_Circlet()              { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10CD08); }
    some<Keyword_t*>    Clothing_Necklace()             { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10CD0A); }
    some<Keyword_t*>    Clothing_Ring()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10CD09); }
    some<Keyword_t*>    Daedric_Artifact()              { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0A8668); }
    some<Keyword_t*>    Magic_Damage_Fire()             { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01CEAD); }
    some<Keyword_t*>    Magic_Damage_Frost()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01CEAE); }
    some<Keyword_t*>    Magic_Damage_Shock()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01CEAF); }
    some<Keyword_t*>    Magic_Vampire_Drain()           { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x101BDE); }
    some<Keyword_t*>    Vampire()                       { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0A82BB); }
    some<Keyword_t*>    Vendor_Item_Animal_Hide()       { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0914EA); }
    some<Keyword_t*>    Vendor_Item_Daedric_Artifact()  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0917E8); }
    some<Keyword_t*>    Vendor_Item_Gem()               { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0914ED); }
    some<Keyword_t*>    Vendor_Item_Jewelry()           { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08F95A); }
    some<Keyword_t*>    Vendor_Item_Ore_Ingot()         { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0914EC); }
    some<Keyword_t*>    Vendor_Item_Poison()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08CDED); }
    some<Keyword_t*>    Vendor_Item_Potion()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08CDEC); }
    some<Keyword_t*>    Vendor_Item_Recipe()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0F5CB0); }
    some<Keyword_t*>    Vendor_Item_Spell_Tome()        { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0937A5); }
    some<Keyword_t*>    Vendor_Item_Staff()             { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0937A4); }
    some<Keyword_t*>    Weapon_Material_Aetherium()     { DEFINE_FORM(Const::Mod::Dawnguard(),  Keyword_t, 0x00E299); }
    some<Keyword_t*>    Weapon_Material_Daedric()       { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71F); }
    some<Keyword_t*>    Weapon_Material_Dragonbone()    { DEFINE_FORM(Const::Mod::Dawnguard(),  Keyword_t, 0x019822); }
    some<Keyword_t*>    Weapon_Material_Draugr()        { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0C5C01); }
    some<Keyword_t*>    Weapon_Material_Draugr_Honed()  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0C5C02); }
    some<Keyword_t*>    Weapon_Material_Dwarven()       { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71A); }
    some<Keyword_t*>    Weapon_Material_Ebony()         { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71E); }
    some<Keyword_t*>    Weapon_Material_Elven()         { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71B); }
    some<Keyword_t*>    Weapon_Material_Falmer()        { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0C5C03); }
    some<Keyword_t*>    Weapon_Material_Falmer_Honed()  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0C5C04); }
    some<Keyword_t*>    Weapon_Material_Glass()         { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71D); }
    some<Keyword_t*>    Weapon_Material_Imperial()      { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0C5C00); }
    some<Keyword_t*>    Weapon_Material_Iron()          { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E718); }
    some<Keyword_t*>    Weapon_Material_Nordic()        { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x026230); }
    some<Keyword_t*>    Weapon_Material_Orcish()        { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71C); }
    some<Keyword_t*>    Weapon_Material_Silver()        { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10AA1A); }
    some<Keyword_t*>    Weapon_Material_Stalhrim()      { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x02622F); }
    some<Keyword_t*>    Weapon_Material_Steel()         { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E719); }
    some<Keyword_t*>    Weapon_Material_Wood()          { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E717); }
    some<Keyword_t*>    Weapon_Type_Battleaxe()         { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06D932); }
    some<Keyword_t*>    Weapon_Type_Bow()               { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E715); }
    some<Keyword_t*>    Weapon_Type_Dagger()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E713); }
    some<Keyword_t*>    Weapon_Type_Greatsword()        { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06D931); }
    some<Keyword_t*>    Weapon_Type_Mace()              { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E714); }
    some<Keyword_t*>    Weapon_Type_Staff()             { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E716); }
    some<Keyword_t*>    Weapon_Type_Sword()             { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E711); }
    some<Keyword_t*>    Weapon_Type_Waraxe()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E712); }
    some<Keyword_t*>    Weapon_Type_Warhammer()         { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06D930); }

}}}
