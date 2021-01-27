/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma comment(lib, "version.lib")

#include "doticu_skylib/cstring.h"

#include "doticu_skylib/form.h"
#include "doticu_skylib/game.h"
#include "doticu_skylib/mod.h"

namespace doticu_skylib {

    template <typename Type_t>
    class smart_ptr
    {
    public:
        Type_t* ptr;

        smart_ptr() :
            ptr(nullptr)
        {
        }

        smart_ptr(Type_t* ptr) :
            ptr(ptr)
        {
        }

        smart_ptr(const smart_ptr&) = delete;

        smart_ptr(smart_ptr&& other) noexcept :
            ptr(std::exchange(other.ptr, nullptr))
        {
        }

        ~smart_ptr()
        {
            if (ptr) {
                delete ptr;
            }
        }

        smart_ptr& operator=(const smart_ptr&) = delete;

        smart_ptr& operator=(smart_ptr&& other) noexcept
        {
            if (this != &other) {
                ptr = std::exchange(other.ptr, nullptr);
            }
        }

        operator Type_t*()
        {
            return ptr;
        }
    };

    static Bool_t Write_Version(Version_t<u16>& game_version, const char* version_csv)
    {
        int major;
        int minor;
        int patch;
        int build;
        if (sscanf_s(version_csv, "%d.%d.%d.%d", &major, &minor, &patch, &build) == 4) {
            game_version.major = major;
            game_version.minor = minor;
            game_version.patch = patch;
            game_version.build = build;
            return true;
        } else {
            return false;
        }
    }

    static Bool_t Read_Version(Version_t<u16>& game_version)
    {
        static constexpr const char* product_version = "\\StringFileInfo\\040904B0\\ProductVersion";
        static constexpr const char* file_version = "\\StringFileInfo\\040904B0\\FileVersion";

        char file_path[MAX_PATH];
        file_path[0] = 0;
        if (GetModuleFileNameA(0, file_path, sizeof(file_path)) && file_path[0]) {
            DWORD unused = 0;
            DWORD version_size = GetFileVersionInfoSizeA(file_path, &unused);
            if (version_size > 0) {
                smart_ptr<char> version_info = new char[version_size];
                if (GetFileVersionInfoA(file_path, unused, version_size, version_info)) {
                    char* version_csv = nullptr;
                    UINT version_csv_size = 0;
                    if (VerQueryValueA(version_info, product_version, (LPVOID*)&version_csv, &version_csv_size) &&
                        version_csv_size > 0 && version_csv && version_csv[0]) {
                        return Write_Version(game_version, version_csv);
                    } else {
                        version_csv = nullptr;
                        version_csv_size = 0;
                        if (VerQueryValueA(version_info, file_version, (LPVOID*)&version_csv, &version_csv_size) &&
                            version_csv_size > 0 && version_csv && version_csv[0]) {
                            return Write_Version(game_version, version_csv);
                        } else {
                            return false;
                        }
                    }
                } else {
                    return false;
                }
            } else {
                return false;
            }
        } else {
            return false;
        }
    }

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
        static Word_t base_address = reinterpret_cast<Word_t>(GetModuleHandle(0));
        SKYLIB_ASSERT(base_address);
        return base_address;
    }

    some<Byte_t*> Game_t::Base_Address_Pointer()
    {
        return reinterpret_cast<Byte_t*>(Base_Address());
    }

    const Version_t<u16>& Game_t::Version()
    {
        static const Version_t<u16> version;

        static Bool_t has_read = false;
        if (!has_read) {
            has_read = Read_Version(const_cast<Version_t<u16>&>(version));
        }

        return version;
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
        for (Index_t idx = 0, end = count; idx < end; idx += 1) {
            SKYLIB_LOG(indent + "idx: %8i, %p", idx, *(ptr + idx));
        }
    }

    Array_t<Actor_Base_t*>& Game_t::Actor_Bases()
    {
        return reinterpret_cast<Array_t<Actor_Base_t*>&>(form_caches[Form_Type_e::ACTOR_BASE]);
    }

    Array_t<Faction_t*>& Game_t::Factions()
    {
        return reinterpret_cast<Array_t<Faction_t*>&>(form_caches[Form_Type_e::FACTION]);
    }

    Array_t<Leveled_Actor_Base_t*>& Game_t::Leveled_Actor_Bases()
    {
        return reinterpret_cast<Array_t<Leveled_Actor_Base_t*>&>(form_caches[Form_Type_e::LEVELED_ACTOR_BASE]);
    }

    Array_t<Quest_t*>& Game_t::Quests()
    {
        return reinterpret_cast<Array_t<Quest_t*>&>(form_caches[Form_Type_e::QUEST]);
    }

    Array_t<Race_t*>& Game_t::Races()
    {
        return reinterpret_cast<Array_t<Race_t*>&>(form_caches[Form_Type_e::RACE]);
    }

    Array_t<Worldspace_t*>& Game_t::Worldspaces()
    {
        return reinterpret_cast<Array_t<Worldspace_t*>&>(form_caches[Form_Type_e::WORLDSPACE]);
    }

}
