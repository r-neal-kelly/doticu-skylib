/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "skse64/GameSettings.h"
#include "skse64/ScaleformLoader.h"
#include "skse64/ScaleformState.h"

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/translations.h"

namespace doticu_skylib {

    Altered_Translation_t::Altered_Translation_t(some<const wchar_t*> key) :
        key(
            (SKYLIB_ASSERT_SOME(key), key)
        ),
        value_length(
            0
        )
    {
    }

    Altered_Translation_t::Altered_Translation_t(some<const wchar_t*> key, some<const wchar_t*> value) :
        key(
            (SKYLIB_ASSERT_SOME(key), key)
        ),
        value_length(
            (SKYLIB_ASSERT_SOME(value), wcslen(value()))
        )
    {
    }

    Bool_t Altered_Translation_t::operator==(const Altered_Translation_t& other) const
    {
        return key == other.key;
    }

    std::mutex Translations_t::mutex;

    Bool_t Translations_t::Are_English()
    {
        Setting* setting = GetINISetting("sLanguage:General");
        if (setting && setting->GetType() == Setting::kType_String) {
            if (setting->data.s) {
                return CString_t::Is_Same(setting->data.s, "ENGLISH", true);
            } else {
                return true;
            }
        } else {
            return true;
        }
    }

    std::wstring Translations_t::Translation(maybe<const wchar_t*> key)
    {
        if (key) {
            std::lock_guard<std::mutex> guard(mutex);
            maybe<wchar_t*> actual_translation = Actual_Translation(key);
            if (actual_translation) {
                return actual_translation();
            } else {
                return L"";
            }
        } else {
            return L"";
        }
    }

    void Translations_t::Translation(maybe<const wchar_t*> key, maybe<const wchar_t*> value_to_copy)
    {
        if (key && value_to_copy) {
            std::lock_guard<std::mutex> guard(mutex);
            maybe<wchar_t*> translation = Actual_Translation(key);
            if (translation) {
                some<Altered_Translation_t*> altered_translation = Altered_Translation(key(), translation());
                SKYLIB_ASSERT_SOME(altered_translation);

                size_t translation_end = altered_translation->value_length + 1;
                size_t value_end = wcslen(value_to_copy()) + 1;
                size_t end = value_end > translation_end ? translation_end - 1 : value_end;
                for (size_t idx = 0; idx < end; idx += 1) {
                    translation[idx] = value_to_copy[idx];
                }
                translation[translation_end - 1] = L'\0';
            }
        }
    }

    Hash_Map_t<const wchar_t*, wchar_t*>& Translations_t::Translations()
    {
        GFxLoader* gfx_loader = GFxLoader::GetSingleton();
        SKYLIB_ASSERT(gfx_loader);

        GFxStateBag* gfx_state_bag = gfx_loader->stateBag;
        SKYLIB_ASSERT(gfx_state_bag);

        BSScaleformTranslator* translator = gfx_state_bag->GetTranslator();
        SKYLIB_ASSERT(translator);

        return reinterpret_cast<Hash_Map_t<const wchar_t*, wchar_t*>&>(translator->translations);
    }

    maybe<wchar_t*> Translations_t::Actual_Translation(maybe<const wchar_t*> key)
    {
        static Hash_Map_t<const wchar_t*, wchar_t*>& translations = Translations();

        if (key) {
            for (size_t idx = 0, end = translations.capacity; idx < end; idx += 1) {
                auto* entry = translations.entries + idx;
                if (entry && entry->chain != nullptr) {
                    if (lstrcmpiW(key(), entry->first) == 0) {
                        return entry->second;
                    }
                }
            }
            return nullptr;
        } else {
            return nullptr;
        }
    }

    some<Altered_Translation_t*> Translations_t::Altered_Translation(some<const wchar_t*> key, some<const wchar_t*> value)
    {
        static Vector_t<Altered_Translation_t> altered_translations;

        SKYLIB_ASSERT_SOME(key);
        SKYLIB_ASSERT_SOME(value);

        maybe<size_t> index = altered_translations.Index_Of(key);
        if (index.Has_Value()) {
            return &altered_translations[index.Value()];
        } else {
            Altered_Translation_t new_altered_translation(key, value);
            altered_translations.push_back(new_altered_translation);
            return &altered_translations[altered_translations.size() - 1];
        }
    }

}
