/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/collections.h"

#include "doticu_skylib/game.h"
#include "doticu_skylib/memory_virtual_heap.h"

namespace doticu_skylib {

    void Memory_Virtual_Heap_t::Log_Instances_In_Words(Vector_t<some<Word_t*>>& instances,
                                                       size_t instance_word_count,
                                                       Bool_t do_reverse,
                                                       std::string indent)
    {
        EnterCriticalSection(&this->critical_section);

        SKYLIB_LOG(indent + "Memory_Virtual_Heap_t::Log_Instances");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "instance_count: %zu", instances.size());
        SKYLIB_LOG(indent + SKYLIB_TAB);

        Word_t first_exe_address = Game_t::Base_Address();
        Word_t last_exe_address = first_exe_address + Game_t::Base_Address_Size();

        for (size_t idx = 0, end = instances.size(); idx < end; idx += 1) {
            some<Word_t*> instance_ptr = instances[idx];
            SKYLIB_LOG(indent + SKYLIB_TAB + "instance_idx: %zu, at: %p", idx, instance_ptr());

            for (size_t idx = 0, end = instance_word_count, offset = 0x0; idx < end; idx += 1, offset += sizeof(Word_t)) {
                Word_t* ptr;
                if (do_reverse) {
                    ptr = instance_ptr() - idx;
                } else {
                    ptr = instance_ptr() + idx;
                }
                if (ptr >= reinterpret_cast<Word_t*>(this->data()) &&
                    ptr < reinterpret_cast<Word_t*>(this->data() + this->current_size)) {
                    Word_t word = *ptr;
                    if (word >= first_exe_address && word < last_exe_address) {
                        Vector_t<some<Word_t**>> word_instances = Instances_Of(ptr);
                        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "%p : %X <-------exe_offset: 0x%8.8X, instance_count %zu",
                                   word, offset, word - first_exe_address, word_instances.size());
                    } else {
                        SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "%p : %X", word, offset);
                    }
                } else {
                    SKYLIB_LOG(indent + SKYLIB_TAB + SKYLIB_TAB + "exceeded heap.");
                }
            }
        }

        SKYLIB_LOG(indent + "}");

        LeaveCriticalSection(&this->critical_section);
    }

}
