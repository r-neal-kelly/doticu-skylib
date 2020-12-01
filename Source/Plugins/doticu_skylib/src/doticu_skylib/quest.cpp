/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/quest.h"

#include "doticu_skylib/virtual_callback.h"
#include "doticu_skylib/virtual_machine.h"
#include "doticu_skylib/virtual_variable.h"

namespace doticu_skylib {

    void Quest_t::Start(const Vector_t<Quest_t*> quests, Callback_i<>* ucallback)
    {
        using UCallback_t = Callback_i<>;
        SKYLIB_ASSERT(ucallback);

        struct VCallback : public Virtual::Callback_t {
            const Vector_t<Quest_t*> quests;
            size_t index;
            UCallback_t* ucallback;
            VCallback(const Vector_t<Quest_t*> quests, size_t index, UCallback_t* ucallback) :
                quests(quests), index(index), ucallback(ucallback)
            {
            }
            void operator()(Virtual::Variable_t* result)
            {
                if (index < quests.size()) {
                    Quest_t* quest = quests[index];
                    if (quest) {
                        quest->Start(new VCallback(quests, index + 1, ucallback));
                    } else {
                        ucallback->operator()();
                        delete ucallback;
                    }
                } else {
                    ucallback->operator()();
                    delete ucallback;
                }
            }
        };

        size_t index = 0;
        Quest_t* quest = quests[index];
        if (quest) {
            quest->Start(new VCallback(quests, index + 1, ucallback));
        } else {
            ucallback->operator()();
            delete ucallback;
        }
    }

    void Quest_t::Start(Virtual::Callback_i* vcallback)
    {
        Virtual::Machine_t::Self()->Call_Method(
            this,
            "Quest",
            "Start",
            nullptr,
            &vcallback
        );
    }

    void Quest_t::Start(Callback_i<Bool_t>* ucallback)
    {
        using UCallback_t = Callback_i<Bool_t>;

        struct VCallback : public Virtual::Callback_t {
            UCallback_t* ucallback;
            VCallback(UCallback_t* ucallback) :
                ucallback(ucallback)
            {
            }
            void operator()(Virtual::Variable_t* result)
            {
                if (ucallback) {
                    Bool_t did_start = result ? result->Bool() : false;
                    ucallback->operator()(did_start);
                    delete ucallback;
                }
            }
        };
        Start(new VCallback(ucallback));
    }

}
