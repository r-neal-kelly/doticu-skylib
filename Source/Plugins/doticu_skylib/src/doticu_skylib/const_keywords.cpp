/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/const_keywords.h"
#include "doticu_skylib/const_mods.h"
#include "doticu_skylib/game_macros.h"
#include "doticu_skylib/keyword.h"

namespace doticu_skylib { namespace Const { namespace Keyword {

    some<Keyword_t*>    Armor_Material_Blades()                 { DEFINE_FORM(Const::Mod::Update(),     Keyword_t, 0x0009C0); }
    some<Keyword_t*>    Armor_Material_Bonemold_Heavy()         { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x024101); }
    some<Keyword_t*>    Armor_Material_Bonemold_Light()         { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x024100); }
    some<Keyword_t*>    Armor_Material_Chitin_Heavy()           { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x024103); }
    some<Keyword_t*>    Armor_Material_Chitin_Light()           { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x024102); }
    some<Keyword_t*>    Armor_Material_Daedric()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBD4); }
    some<Keyword_t*>    Armor_Material_Dark_Brotherhood()       { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10FD62); }
    some<Keyword_t*>    Armor_Material_Dawnguard()              { DEFINE_FORM(Const::Mod::Dawnguard(),  Keyword_t, 0x012CCD); }
    some<Keyword_t*>    Armor_Material_Dragonplate()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBD5); }
    some<Keyword_t*>    Armor_Material_Dragonscale()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBD6); }
    some<Keyword_t*>    Armor_Material_Dwarven()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBD7); }
    some<Keyword_t*>    Armor_Material_Ebony()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBD8); }
    some<Keyword_t*>    Armor_Material_Elven()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBD9); }
    some<Keyword_t*>    Armor_Material_Elven_Gilded()           { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBDA); }
    some<Keyword_t*>    Armor_Material_Falmer()                 { DEFINE_FORM(Const::Mod::Update(),     Keyword_t, 0x0009BD); }
    some<Keyword_t*>    Armor_Material_Falmer_Hardened()        { DEFINE_FORM(Const::Mod::Dawnguard(),  Keyword_t, 0x012CCE); }
    some<Keyword_t*>    Armor_Material_Falmer_Heavy()           { DEFINE_FORM(Const::Mod::Dawnguard(),  Keyword_t, 0x012CCF); }
    some<Keyword_t*>    Armor_Material_Falmer_Heavy_Original()  { DEFINE_FORM(Const::Mod::Dawnguard(),  Keyword_t, 0x012CD0); }
    some<Keyword_t*>    Armor_Material_Forsworn()               { DEFINE_FORM(Const::Mod::Update(),     Keyword_t, 0x0009B9); }
    some<Keyword_t*>    Armor_Material_Forsworn_MS02()          { DEFINE_FORM(Const::Mod::Update(),     Keyword_t, 0x0009BA); }
    some<Keyword_t*>    Armor_Material_Glass()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBDC); }
    some<Keyword_t*>    Armor_Material_Hide()                   { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBDD); }
    some<Keyword_t*>    Armor_Material_Hunter()                 { DEFINE_FORM(Const::Mod::Dawnguard(),  Keyword_t, 0x0050C4); }
    some<Keyword_t*>    Armor_Material_Imperial_Heavy()         { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE2); }
    some<Keyword_t*>    Armor_Material_Imperial_Light()         { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE0); }
    some<Keyword_t*>    Armor_Material_Imperial_Studded()       { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE1); }
    some<Keyword_t*>    Armor_Material_Iron()                   { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE3); }
    some<Keyword_t*>    Armor_Material_Iron_Banded()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE4); }
    some<Keyword_t*>    Armor_Material_Leather()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBDB); }
    some<Keyword_t*>    Armor_Material_Morag_Tong()             { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x03A328); }
    some<Keyword_t*>    Armor_Material_Nightingale()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10FD61); }
    some<Keyword_t*>    Armor_Material_Nordic_Heavy()           { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x024105); }
    some<Keyword_t*>    Armor_Material_Nordic_Light()           { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x024104); }
    some<Keyword_t*>    Armor_Material_Orcish()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE5); }
    some<Keyword_t*>    Armor_Material_Penitus()                { DEFINE_FORM(Const::Mod::Update(),     Keyword_t, 0x0009BB); }
    some<Keyword_t*>    Armor_Material_Scaled()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBDE); }
    some<Keyword_t*>    Armor_Material_Stalhrim_Heavy()         { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x024106); }
    some<Keyword_t*>    Armor_Material_Stalhrim_Light()         { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x024107); }
    some<Keyword_t*>    Armor_Material_Steel()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE6); }
    some<Keyword_t*>    Armor_Material_Steel_Plate()            { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE7); }
    some<Keyword_t*>    Armor_Material_Stormcloak()             { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0AC13A); }
    some<Keyword_t*>    Armor_Material_Stormcloak_Bear()        { DEFINE_FORM(Const::Mod::Update(),     Keyword_t, 0x0009BE); }
    some<Keyword_t*>    Armor_Material_Studded()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBDF); }
    some<Keyword_t*>    Armor_Material_Thieves_Guild()          { DEFINE_FORM(Const::Mod::Update(),     Keyword_t, 0x0009BC); }
    some<Keyword_t*>    Armor_Material_Thieves_Guild_Leader()   { DEFINE_FORM(Const::Mod::Update(),     Keyword_t, 0x0009BF); }
    some<Keyword_t*>    Armor_Material_Vampire()                { DEFINE_FORM(Const::Mod::Dawnguard(),  Keyword_t, 0x01463E); }
    some<Keyword_t*>    Armor_Type_Boots()                      { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06C0ED); }
    some<Keyword_t*>    Armor_Type_Clothing()                   { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE8); }
    some<Keyword_t*>    Armor_Type_Cuirass()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06C0EC); }
    some<Keyword_t*>    Armor_Type_Gauntlets()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06C0EF); }
    some<Keyword_t*>    Armor_Type_Heavy()                      { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBD2); }
    some<Keyword_t*>    Armor_Type_Helmet()                     { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06C0EE); }
    some<Keyword_t*>    Armor_Type_Jewelry()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBE9); }
    some<Keyword_t*>    Armor_Type_Light()                      { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06BBD3); }
    some<Keyword_t*>    Armor_Type_Shield()                     { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0965B2); }
    some<Keyword_t*>    Clothing_Type_Body()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0A8657); }
    some<Keyword_t*>    Clothing_Type_Circlet()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10CD08); }
    some<Keyword_t*>    Clothing_Type_Feet()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10CD12); }
    some<Keyword_t*>    Clothing_Type_Hands()                   { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10CD13); }
    some<Keyword_t*>    Clothing_Type_Head()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10CD11); }
    some<Keyword_t*>    Clothing_Type_Necklace()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10CD0A); }
    some<Keyword_t*>    Clothing_Type_Poor()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0A865C); }
    some<Keyword_t*>    Clothing_Type_Rich()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0A865D); }
    some<Keyword_t*>    Clothing_Type_Ring()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10CD09); }
    some<Keyword_t*>    Crafting_Material_Aetherium()           { DEFINE_FORM(Const::Mod::Dawnguard(),  Keyword_t, 0x00E299); }
    some<Keyword_t*>    Daedric_Artifact()                      { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0A8668); }
    some<Keyword_t*>    Jewelry_Type_Expensive()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0A8664); }
    some<Keyword_t*>    Magic_Damage_Fire()                     { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01CEAD); }
    some<Keyword_t*>    Magic_Damage_Frost()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01CEAE); }
    some<Keyword_t*>    Magic_Damage_Shock()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01CEAF); }
    some<Keyword_t*>    Magic_Vampire_Drain()                   { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x101BDE); }
    some<Keyword_t*>    Vampire()                               { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0A82BB); }
    some<Keyword_t*>    Vendor_Item_Animal_Hide()               { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0914EA); }
    some<Keyword_t*>    Vendor_Item_Animal_Part()               { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0914EB); }
    some<Keyword_t*>    Vendor_Item_Armor()                     { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08F959); }
    some<Keyword_t*>    Vendor_Item_Arrow()                     { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0917E7); }
    some<Keyword_t*>    Vendor_Item_Book()                      { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0937A2); }
    some<Keyword_t*>    Vendor_Item_Clothing()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08F95B); }
    some<Keyword_t*>    Vendor_Item_Clutter()                   { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0914E9); }
    some<Keyword_t*>    Vendor_Item_Daedric_Artifact()          { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0917E8); }
    some<Keyword_t*>    Vendor_Item_Firewood()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0BECD7); }
    some<Keyword_t*>    Vendor_Item_Food()                      { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08CDEA); }
    some<Keyword_t*>    Vendor_Item_Food_Raw()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0A0E56); }
    some<Keyword_t*>    Vendor_Item_Gem()                       { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0914ED); }
    some<Keyword_t*>    Vendor_Item_Ingredient()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08CDEB); }
    some<Keyword_t*>    Vendor_Item_Jewelry()                   { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08F95A); }
    some<Keyword_t*>    Vendor_Item_Key()                       { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0914EF); }
    some<Keyword_t*>    Vendor_Item_Ore_Or_Ingot()              { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0914EC); }
    some<Keyword_t*>    Vendor_Item_Poison()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08CDED); }
    some<Keyword_t*>    Vendor_Item_Potion()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08CDEC); }
    some<Keyword_t*>    Vendor_Item_Recipe()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0F5CB0); }
    some<Keyword_t*>    Vendor_Item_Scroll()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0A0E57); }
    some<Keyword_t*>    Vendor_Item_Soul_Gem()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0937A3); }
    some<Keyword_t*>    Vendor_Item_Spell_Tome()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0937A5); }
    some<Keyword_t*>    Vendor_Item_Staff()                     { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0937A4); }
    some<Keyword_t*>    Vendor_Item_Tool()                      { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0914EE); }
    some<Keyword_t*>    Vendor_Item_Weapon()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x08F958); }
    some<Keyword_t*>    Weapon_Material_Daedric()               { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71F); }
    some<Keyword_t*>    Weapon_Material_Dragonbone()            { DEFINE_FORM(Const::Mod::Dawnguard(),  Keyword_t, 0x019822); }
    some<Keyword_t*>    Weapon_Material_Draugr()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0C5C01); }
    some<Keyword_t*>    Weapon_Material_Draugr_Honed()          { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0C5C02); }
    some<Keyword_t*>    Weapon_Material_Dwarven()               { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71A); }
    some<Keyword_t*>    Weapon_Material_Ebony()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71E); }
    some<Keyword_t*>    Weapon_Material_Elven()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71B); }
    some<Keyword_t*>    Weapon_Material_Falmer()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0C5C03); }
    some<Keyword_t*>    Weapon_Material_Falmer_Honed()          { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0C5C04); }
    some<Keyword_t*>    Weapon_Material_Glass()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71D); }
    some<Keyword_t*>    Weapon_Material_Imperial()              { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x0C5C00); }
    some<Keyword_t*>    Weapon_Material_Iron()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E718); }
    some<Keyword_t*>    Weapon_Material_Nordic()                { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x026230); }
    some<Keyword_t*>    Weapon_Material_Orcish()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E71C); }
    some<Keyword_t*>    Weapon_Material_Silver()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x10AA1A); }
    some<Keyword_t*>    Weapon_Material_Stalhrim()              { DEFINE_FORM(Const::Mod::Dragonborn(), Keyword_t, 0x02622F); }
    some<Keyword_t*>    Weapon_Material_Steel()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E719); }
    some<Keyword_t*>    Weapon_Material_Wood()                  { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E717); }
    some<Keyword_t*>    Weapon_Type_Battleaxe()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06D932); }
    some<Keyword_t*>    Weapon_Type_Bow()                       { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E715); }
    some<Keyword_t*>    Weapon_Type_Dagger()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E713); }
    some<Keyword_t*>    Weapon_Type_Greatsword()                { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06D931); }
    some<Keyword_t*>    Weapon_Type_Mace()                      { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E714); }
    some<Keyword_t*>    Weapon_Type_Staff()                     { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E716); }
    some<Keyword_t*>    Weapon_Type_Sword()                     { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E711); }
    some<Keyword_t*>    Weapon_Type_Waraxe()                    { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x01E712); }
    some<Keyword_t*>    Weapon_Type_Warhammer()                 { DEFINE_FORM(Const::Mod::Skyrim(),     Keyword_t, 0x06D930); }

}}}
