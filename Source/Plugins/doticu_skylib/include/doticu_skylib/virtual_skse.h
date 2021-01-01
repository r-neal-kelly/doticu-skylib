/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "skse64/PapyrusArgs.h"

#include "doticu_skylib/string.h"

#include "doticu_skylib/active_magic_effect.h"
#include "doticu_skylib/alias_base.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/form_list.h"
#include "doticu_skylib/form_type.h"
#include "doticu_skylib/keyword.h"
#include "doticu_skylib/reference.h"

#include "doticu_skylib/virtual.h"
#include "doticu_skylib/virtual_type.h"
#include "doticu_skylib/virtual_variable.h"

#define DEFINE_SKSE_GET_TYPE_ID(TYPE_)                              \
template <>                                                         \
inline UInt64 GetTypeID<TYPE_>(VMClassRegistry*)                    \
{                                                                   \
    return doticu_skylib::Virtual::Type_e::From<TYPE_>().Mangled(); \
}
//DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Bool_t); // defined by skse
//DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Int_t); // defined by skse
//DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Float_t); // defined by skse
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::String_t);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Form_Type_e);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Active_Magic_Effect_t*);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Alias_Base_t*);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Form_t*);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Form_List_t*);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Keyword_t*);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Reference_t*);

DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Bool_t>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Int_t>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Float_t>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::String_t>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Form_Type_e>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Active_Magic_Effect_t*>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Alias_Base_t*>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Form_t*>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Form_List_t*>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Keyword_t*>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Reference_t*>);
#undef DEFINE_SKSE_GET_TYPE_ID

#define DEFINE_SKSE_UNPACK_VALUE(TYPE_)                                                         \
template <>                                                                                     \
inline void UnpackValue<TYPE_>(TYPE_* destination, VMValue* source)                             \
{                                                                                               \
    if (destination && source) {                                                                \
        reinterpret_cast<doticu_skylib::Virtual::Variable_t*>(source)->Unpack(*destination);    \
    }                                                                                           \
}
#define DEFINE_SKSE_UNPACK_POINTER(TYPE_)                                                       \
template <>                                                                                     \
inline void UnpackValue<TYPE_>(TYPE_** destination, VMValue* source)                            \
{                                                                                               \
    if (destination && source) {                                                                \
        reinterpret_cast<doticu_skylib::Virtual::Variable_t*>(source)->Unpack(*destination);    \
    }                                                                                           \
}
//DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Bool_t); // defined by skse
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Int_t);
//DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Float_t); // defined by skse
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::String_t);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Form_Type_e);
DEFINE_SKSE_UNPACK_POINTER(doticu_skylib::Active_Magic_Effect_t);
DEFINE_SKSE_UNPACK_POINTER(doticu_skylib::Alias_Base_t);
DEFINE_SKSE_UNPACK_POINTER(doticu_skylib::Form_t);
DEFINE_SKSE_UNPACK_POINTER(doticu_skylib::Form_List_t);
DEFINE_SKSE_UNPACK_POINTER(doticu_skylib::Keyword_t);
DEFINE_SKSE_UNPACK_POINTER(doticu_skylib::Reference_t);

DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Bool_t>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Int_t>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Float_t>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::String_t>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Form_Type_e>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Active_Magic_Effect_t*>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Alias_Base_t*>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Form_t*>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Form_List_t*>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Keyword_t*>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Reference_t*>);
#undef DEFINE_SKSE_UNPACK_VALUE
#undef DEFINE_SKSE_UNPACK_POINTER

#define DEFINE_SKSE_PACK_VALUE(TYPE_)                                                       \
template <>                                                                                 \
inline void PackValue<TYPE_>(VMValue* destination, TYPE_* source, VMClassRegistry*)         \
{                                                                                           \
    if (destination && source) {                                                            \
        reinterpret_cast<doticu_skylib::Virtual::Variable_t*>(destination)->Pack(*source);  \
    }                                                                                       \
}
#define DEFINE_SKSE_PACK_VECTOR_VALUE(TYPE_)                                                \
template <>                                                                                 \
inline void PackValue<TYPE_>(VMValue* destination, TYPE_* source, VMClassRegistry*)         \
{                                                                                           \
    if (destination && source) {                                                            \
        reinterpret_cast<doticu_skylib::Virtual::Variable_t*>(destination)->Pack(*source);  \
    }                                                                                       \
    source->clear();                                                                        \
}
//DEFINE_SKSE_PACK_VALUE(doticu_skylib::Bool_t); // defined by skse
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Int_t);
//DEFINE_SKSE_PACK_VALUE(doticu_skylib::Float_t); // defined by skse
DEFINE_SKSE_PACK_VALUE(doticu_skylib::String_t);
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Form_Type_e);
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Active_Magic_Effect_t*);
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Alias_Base_t*);
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Form_t*);
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Form_List_t*);
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Keyword_t*);
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Reference_t*);

DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Bool_t>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Int_t>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Float_t>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::String_t>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Form_Type_e>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Active_Magic_Effect_t*>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Alias_Base_t*>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Form_t*>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Form_List_t*>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Keyword_t*>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Reference_t*>);
#undef DEFINE_SKSE_PACK_VALUE
#undef DEFINE_SKSE_PACK_VECTOR_VALUE
