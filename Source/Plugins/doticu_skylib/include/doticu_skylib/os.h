/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#pragma once

#include <mutex>

#include "doticu_skylib/interface.h"
#include "doticu_skylib/intrinsic.h"
#include "doticu_skylib/maybe.h"
#include "doticu_skylib/version.h"

namespace doticu_skylib {

    class OS_t
    {
    public:
        static std::mutex lock;

    public:
        static Double_t Microseconds();
        static Double_t Milliseconds();
        static Double_t Seconds();

        static void     Sleep(u32 milliseconds);

        static Word_t   Module_Address(maybe<const char*> module_name);
        static size_t   Module_Size(maybe<const char*> module_name);
        static Bool_t   Module_Version(maybe<const char*> module_name, Version_t<u16>& result);

    public:
        static const std::wstring&  Documents_Path();

        static void Delete_File(const std::wstring& file_name);
        static void Delete_File(std::wstring&& file_name);

    public:
        #pragma optimize("", off)
        template <typename Return>
        static Double_t Stress_Test_Milliseconds(size_t trial_count, Functor_i<Return>& functor)
        {
            Double_t total_time = 0.0;
            for (size_t idx = 0, end = trial_count; idx < end; idx += 1) {
                Double_t start_time = Milliseconds();
                functor();
                total_time += Milliseconds() - start_time;
            }
            return total_time / trial_count;
        }
        #pragma optimize("", on)
    };

}
