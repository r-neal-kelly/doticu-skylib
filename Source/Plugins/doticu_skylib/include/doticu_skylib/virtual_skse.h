/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include "doticu_skylib/string.h"

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
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Keyword_t*);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Reference_t*);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Bool_t>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Int_t>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::Float_t>);
DEFINE_SKSE_GET_TYPE_ID(doticu_skylib::Vector_t<doticu_skylib::String_t>);
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
//DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Bool_t); // defined by skse
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Int_t);
//DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Float_t); // defined by skse
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::String_t);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Keyword_t*);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Reference_t*);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Bool_t>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Int_t>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Float_t>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::String_t>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Keyword_t*>);
DEFINE_SKSE_UNPACK_VALUE(doticu_skylib::Vector_t<doticu_skylib::Reference_t*>);
#undef DEFINE_SKSE_UNPACK_VALUE

#define DEFINE_SKSE_PACK_VALUE(TYPE_)                                                       \
template <>                                                                                 \
inline void PackValue<TYPE_>(VMValue* destination, TYPE_* source, VMClassRegistry*)         \
{                                                                                           \
    if (destination && source) {                                                            \
        reinterpret_cast<doticu_skylib::Virtual::Variable_t*>(destination)->Pack(*source);  \
    }                                                                                       \
}
//DEFINE_SKSE_PACK_VALUE(doticu_skylib::Bool_t); // defined by skse
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Int_t);
//DEFINE_SKSE_PACK_VALUE(doticu_skylib::Float_t); // defined by skse
DEFINE_SKSE_PACK_VALUE(doticu_skylib::String_t);
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Keyword_t*);
DEFINE_SKSE_PACK_VALUE(doticu_skylib::Reference_t*);
#undef DEFINE_SKSE_PACK_VALUE

#define DEFINE_SKSE_PACK_VECTOR_VALUE(TYPE_)                                                \
template <>                                                                                 \
inline void PackValue<TYPE_>(VMValue* destination, TYPE_* source, VMClassRegistry*)         \
{                                                                                           \
    if (destination && source) {                                                            \
        reinterpret_cast<doticu_skylib::Virtual::Variable_t*>(destination)->Pack(*source);  \
    }                                                                                       \
    source->clear();                                                                        \
}
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Bool_t>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Int_t>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Float_t>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::String_t>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Keyword_t*>);
DEFINE_SKSE_PACK_VECTOR_VALUE(doticu_skylib::Vector_t<doticu_skylib::Reference_t*>);
#undef DEFINE_SKSE_PACK_VECTOR_VALUE
