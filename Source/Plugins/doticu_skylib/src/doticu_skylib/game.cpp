/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"
#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/game_ini.h"
#include "doticu_skylib/mod.h"
#include "doticu_skylib/os.h"

namespace doticu_skylib {

    std::mutex Game_t::lock;

    some<Game_t*> Game_t::Self()
    {
        static auto self = *reinterpret_cast
            <Game_t**>
            (Game_t::Base_Address() + Offset_e::SELF);

        SKYLIB_ASSERT(self);
        return self;
    }

    Word_t Game_t::Base_Address()
    {
        static Word_t base_address = OS_t::Module_Address(none<const char*>());
        SKYLIB_ASSERT(base_address);
        return base_address;
    }

    some<Byte_t*> Game_t::Base_Address_Pointer()
    {
        return reinterpret_cast<Byte_t*>(Base_Address());
    }

    size_t Game_t::Base_Address_Size()
    {
        static size_t base_address_size = OS_t::Module_Size(none<const char*>());
        SKYLIB_ASSERT(base_address_size);
        return base_address_size;
    }

    const Version_t<u16>& Game_t::Version()
    {
        static Version_t<u16> version;
        static Bool_t has_read = false;
        if (!has_read) {
            has_read = OS_t::Module_Version(none<const char*>(), version);
        }
        return version;
    }

    const std::wstring Game_t::Save_Path()
    {
        std::wstring save_path = OS_t::Documents_Path() + L"\\My Games\\Skyrim Special Edition";

        Setting* setting = GetINISetting("sLocalSavePath:General");
        if (setting && setting->GetType() == Setting::kType_String && setting->data.s && setting->data.s[0]) {
            std::wstring local = CString_t::To<std::wstring>(setting->data.s);

            if (local[0] != L'\\' && local[0] != L'/') {
                save_path += L"\\";
            }

            size_t last = local.length() - 1;
            if (local[last] == L'\\' || local[last] == L'/') {
                local.erase(last);
            }

            save_path += local;
        } else {
            save_path += L"\\Saves";
        }

        return save_path;
    }

    const std::wstring Game_t::Save_File_Path(some<const wchar_t*> file_name, some<const wchar_t*> extension)
    {
        return Save_Path() + L"\\" + file_name() + L"." + extension();
    }

    const std::wstring Game_t::Save_File_Path(some<const char*> file_name, some<const char*> extension)
    {
        return Save_Path() + L"\\" + CString_t::To<std::wstring>(file_name()) + L"." + CString_t::To<std::wstring>(extension());
    }

    Word_t Game_t::V_Table_Offset(const void* instance)
    {
        return *reinterpret_cast<const Word_t*>(instance) - Game_t::Base_Address();
    }

    void Game_t::Write_V_Table(void* instance, Word_t v_table_offset)
    {
        static_cast<Word_t*>(instance)[0] = Game_t::Base_Address() + v_table_offset;
    }

    void Game_t::Log_u64s(void* data, size_t count, std::string indent)
    {
        SKYLIB_ASSERT(data);

        u64* ptr = static_cast<u64*>(data);
        for (size_t idx = 0, end = count; idx < end; idx += 1) {
            SKYLIB_LOG(indent + "idx: %8i, %p", idx, *(ptr + idx));
        }
    }

    Hash_Map_t<Form_ID_t, maybe<Form_t*>>& Game_t::Form_IDs_To_Forms()
    {
        static auto form_ids_to_forms = *reinterpret_cast
            <Hash_Map_t<Form_ID_t, maybe<Form_t*>>**>
            (Game_t::Base_Address() + Offset_e::FORM_IDS_TO_FORMS);

        SKYLIB_ASSERT(form_ids_to_forms);

        return *form_ids_to_forms;
    }

    Read_Write_Lock_t& Game_t::Form_IDs_To_Forms_Lock()
    {
        static auto form_ids_to_forms_lock = reinterpret_cast
            <Read_Write_Lock_t*>
            (Game_t::Base_Address() + Offset_e::FORM_IDS_TO_FORMS_LOCK);

        return *form_ids_to_forms_lock;
    }

    Hash_Map_t<String_t, maybe<Form_t*>>& Game_t::Editor_IDs_To_Forms()
    {
        static auto editor_ids_to_forms = *reinterpret_cast
            <Hash_Map_t<String_t, maybe<Form_t*>>**>
            (Game_t::Base_Address() + Offset_e::EDITOR_IDS_TO_FORMS);

        SKYLIB_ASSERT(editor_ids_to_forms);

        return *editor_ids_to_forms;
    }

    Read_Write_Lock_t& Game_t::Editor_IDs_To_Forms_Lock()
    {
        static auto editor_ids_to_forms_lock = reinterpret_cast
            <Read_Write_Lock_t*>
            (Game_t::Base_Address() + Offset_e::EDITOR_IDS_TO_FORMS_LOCK);

        return *editor_ids_to_forms_lock;
    }

    Bool_t Game_t::Has_Form(some<Form_ID_t> form_id, Read_Locker_t& locker)
    {
        SKYLIB_ASSERT_SOME(form_id);

        Hash_Map_t<Form_ID_t, maybe<Form_t*>>& form_ids_to_forms = Form_IDs_To_Forms();
        auto* entry = form_ids_to_forms.Entry(form_id);
        return entry && entry->second;
    }

    Bool_t Game_t::Has_Form(some<Form_t*> form, Read_Locker_t& locker)
    {
        SKYLIB_ASSERT_SOME(form);

        Hash_Map_t<Form_ID_t, maybe<Form_t*>>& form_ids_to_forms = Form_IDs_To_Forms();
        auto* entry = form_ids_to_forms.Entry(form->form_id);
        return entry && entry->second == form;
    }

    maybe<Form_t*> Game_t::Form(Raw_Form_ID_t raw_form_id)
    {
        static auto get_form = reinterpret_cast
            <Form_t*(*)(Raw_Form_ID_t)>
            (Game_t::Base_Address() + Offset_e::GET_FORM);

        if (raw_form_id != none<Form_ID_t>()) {
            return get_form(raw_form_id);
        } else {
            return nullptr;
        }
    }

    maybe<Form_t*> Game_t::Form(some<Mod_t*> mod, Raw_Form_Index_t raw_form_index)
    {
        SKYLIB_ASSERT_SOME(mod);

        return Form(Form_ID_t(mod, raw_form_index));
    }

    Vector_t<some<Form_t*>> Game_t::Forms()
    {
        Vector_t<some<Form_t*>> results;
        Forms(results);
        return results;
    }

    Vector_t<some<Form_t*>> Game_t::Forms(Filter_i<some<Form_t*>>& filter)
    {
        Vector_t<some<Form_t*>> results;
        Forms(results, filter);
        return results;
    }

    void Game_t::Forms(Vector_t<some<Form_t*>>& results)
    {
        Hash_Map_t<Form_ID_t, maybe<Form_t*>>& form_ids_to_forms = Form_IDs_To_Forms();
        Read_Write_Lock_t& form_ids_to_forms_lock = Form_IDs_To_Forms_Lock();
        Read_Locker_t locker(form_ids_to_forms_lock);

        for (size_t idx = 0, end = form_ids_to_forms.capacity; idx < end; idx += 1) {
            Hash_Map_t<Form_ID_t, maybe<Form_t*>>::Entry_t& entry = form_ids_to_forms.entries[idx];
            if (entry.chain && entry.second) {
                results.push_back(entry.second());
            }
        }
    }

    void Game_t::Forms(Vector_t<some<Form_t*>>& results, Filter_i<some<Form_t*>>& filter)
    {
        Hash_Map_t<Form_ID_t, maybe<Form_t*>>& form_ids_to_forms = Form_IDs_To_Forms();
        Read_Write_Lock_t& form_ids_to_forms_lock = Form_IDs_To_Forms_Lock();
        Read_Locker_t locker(form_ids_to_forms_lock);

        for (size_t idx = 0, end = form_ids_to_forms.capacity; idx < end; idx += 1) {
            Hash_Map_t<Form_ID_t, maybe<Form_t*>>::Entry_t& entry = form_ids_to_forms.entries[idx];
            if (entry.chain && entry.second && filter(entry.second())) {
                results.push_back(entry.second());
            }
        }
    }

    void Game_t::Iterate_Forms(Iterator_i<some<Form_t*>>& iterator)
    {
        Hash_Map_t<Form_ID_t, maybe<Form_t*>>& form_ids_to_forms = Form_IDs_To_Forms();
        Read_Write_Lock_t& form_ids_to_forms_lock = Form_IDs_To_Forms_Lock();
        Read_Locker_t locker(form_ids_to_forms_lock);

        for (size_t idx = 0, end = form_ids_to_forms.capacity; idx < end; idx += 1) {
            Hash_Map_t<Form_ID_t, maybe<Form_t*>>::Entry_t& entry = form_ids_to_forms.entries[idx];
            if (entry.chain && entry.second) {
                if (iterator(entry.second()) == Iterator_e::BREAK) {
                    return;
                }
            }
        }
    }

    void Game_t::Iterate_Forms_Periodically(Iterator_i<some<Form_t*>>& iterator, std::chrono::nanoseconds interval)
    {
        Hash_Map_t<Form_ID_t, maybe<Form_t*>>& form_ids_to_forms = Form_IDs_To_Forms();
        Read_Write_Lock_t& form_ids_to_forms_lock = Form_IDs_To_Forms_Lock();

        for (size_t idx = 0; ; idx += 1) {
            {
                Read_Locker_t locker(form_ids_to_forms_lock);
                if (idx < form_ids_to_forms.capacity) {
                    Hash_Map_t<Form_ID_t, maybe<Form_t*>>::Entry_t& entry = form_ids_to_forms.entries[idx];
                    if (entry.chain && entry.second) {
                        if (iterator(entry.second()) == Iterator_e::BREAK) {
                            return;
                        }
                    }
                } else {
                    return;
                }
            }
            if (interval.count() > 0) {
                std::this_thread::sleep_for(interval);
            }
        }
    }

    Array_t<maybe<Actor_Base_t*>>& Game_t::Actor_Bases()
    {
        return reinterpret_cast<Array_t<maybe<Actor_Base_t*>>&>(form_caches[Form_Type_e::ACTOR_BASE]);
    }

    Array_t<maybe<Faction_t*>>& Game_t::Factions()
    {
        return reinterpret_cast<Array_t<maybe<Faction_t*>>&>(form_caches[Form_Type_e::FACTION]);
    }

    Array_t<maybe<Leveled_Actor_Base_t*>>& Game_t::Leveled_Actor_Bases()
    {
        return reinterpret_cast<Array_t<maybe<Leveled_Actor_Base_t*>>&>(form_caches[Form_Type_e::LEVELED_ACTOR_BASE]);
    }

    Array_t<maybe<Location_t*>>& Game_t::Locations()
    {
        return reinterpret_cast<Array_t<maybe<Location_t*>>&>(form_caches[Form_Type_e::LOCATION]);
    }

    Array_t<maybe<Quest_t*>>& Game_t::Quests()
    {
        return reinterpret_cast<Array_t<maybe<Quest_t*>>&>(form_caches[Form_Type_e::QUEST]);
    }

    Array_t<maybe<Race_t*>>& Game_t::Races()
    {
        return reinterpret_cast<Array_t<maybe<Race_t*>>&>(form_caches[Form_Type_e::RACE]);
    }

    Array_t<maybe<Worldspace_t*>>& Game_t::Worldspaces()
    {
        return reinterpret_cast<Array_t<maybe<Worldspace_t*>>&>(form_caches[Form_Type_e::WORLDSPACE]);
    }

}
