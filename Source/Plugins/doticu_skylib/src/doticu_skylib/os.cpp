/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma comment(lib, "version.lib")

#include <ShlObj.h>

#include "psapi.h"

#include "doticu_skylib/os.h"
#include "doticu_skylib/unique.h"

namespace doticu_skylib {

    std::mutex OS_t::lock;

    Double_t OS_t::Microseconds()
    {
        LARGE_INTEGER frequency;
        LARGE_INTEGER counter;
        QueryPerformanceFrequency(&frequency);
        QueryPerformanceCounter(&counter);

        return (counter.QuadPart * 1000000.0) / frequency.QuadPart;
    }

    Double_t OS_t::Milliseconds()
    {
        return Microseconds() / 1000.0;
    }

    Double_t OS_t::Seconds()
    {
        return Milliseconds() / 1000.0;
    }

    void OS_t::Sleep(u32 milliseconds)
    {
        ::Sleep(milliseconds);
    }

    Word_t OS_t::Module_Address(maybe<const char*> module_name)
    {
        return reinterpret_cast<Word_t>(GetModuleHandle(module_name()));
    }

    size_t OS_t::Module_Size(maybe<const char*> module_name)
    {
        MODULEINFO module_info;
        memset(&module_info, 0, sizeof(module_info));
        GetModuleInformation(GetCurrentProcess(), GetModuleHandle(module_name()), &module_info, sizeof(MODULEINFO));
        return module_info.SizeOfImage;
    }

    Bool_t OS_t::Module_Version(maybe<const char*> module_name, Version_t<u16>& result)
    {
        static constexpr const char* product_version = "\\StringFileInfo\\040904B0\\ProductVersion";
        static constexpr const char* file_version = "\\StringFileInfo\\040904B0\\FileVersion";

        static auto Write_Version = [&](Version_t<u16>& version, const char* version_csv)->Bool_t
        {
            int major, minor, patch, build;
            if (sscanf_s(version_csv, "%d.%d.%d.%d", &major, &minor, &patch, &build) == 4) {
                version.major = major;
                version.minor = minor;
                version.patch = patch;
                version.build = build;
                return true;
            } else {
                return false;
            }
        };

        char file_path[MAX_PATH];
        file_path[0] = 0;
        if (GetModuleFileNameA(GetModuleHandle(module_name()), file_path, sizeof(file_path)) && file_path[0]) {
            DWORD unused = 0;
            DWORD version_size = GetFileVersionInfoSizeA(file_path, &unused);
            if (version_size > 0) {
                unique<char> version_info = new char[version_size];
                if (GetFileVersionInfoA(file_path, unused, version_size, version_info())) {
                    char* version_csv = nullptr;
                    UINT version_csv_size = 0;
                    if (VerQueryValueA(version_info(), product_version, (LPVOID*)&version_csv, &version_csv_size) &&
                        version_csv_size > 0 && version_csv && version_csv[0]) {
                        return Write_Version(result, version_csv);
                    } else {
                        version_csv = nullptr;
                        version_csv_size = 0;
                        if (VerQueryValueA(version_info(), file_version, (LPVOID*)&version_csv, &version_csv_size) &&
                            version_csv_size > 0 && version_csv && version_csv[0]) {
                            return Write_Version(result, version_csv);
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

    const std::wstring& OS_t::Documents_Path()
    {
        static std::wstring documents_path = L"";

        std::lock_guard<std::mutex> locker(lock);

        if (documents_path == L"") {
            PWSTR res = nullptr;
            HRESULT err = SHGetKnownFolderPath(FOLDERID_Documents, KF_FLAG_CREATE, 0, &res);
            SKYLIB_ASSERT(err == S_OK);
            documents_path = res;
            CoTaskMemFree(res);
        }

        return documents_path;
    }

    void OS_t::Delete_File(const std::wstring& file_name)
    {
        DeleteFileW(file_name.c_str());
    }

    void OS_t::Delete_File(std::wstring&& file_name)
    {
        Delete_File(file_name);
    }

}
