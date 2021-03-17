/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/book.h"

namespace doticu_skylib {

    Book_t::Teachable_u::Teachable_u() :
        spell(none<Spell_t*>())
    {
    }

    Book_t::Teachable_u::~Teachable_u()
    {
        this->spell = none<Spell_t*>();
    }

    Bool_t Book_t::Is_Codex()
    {
        return this->book_type.Is_Flagged(Book_Type_e::CODEX);
    }

    Bool_t Book_t::Is_Note_Or_Scroll()
    {
        return this->book_type.Is_Flagged(Book_Type_e::NOTE_OR_SCROLL);
    }

    Bool_t Book_t::Can_Teach_Skill()
    {
        return !Can_Teach_Spell() && this->book_type.Is_Flagged(Book_Flags_e::TEACHES_SKILL);
    }

    Bool_t Book_t::Can_Teach_Spell()
    {
        return this->book_type.Is_Flagged(Book_Flags_e::TEACHES_SPELL);
    }

    DString_t Book_t::Unparsed_Text()
    {
        return Description(this);
    }

    void Book_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Book_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "is_codex: %s", Is_Codex() ? "true" : "false");
        SKYLIB_LOG(indent + SKYLIB_TAB + "is_note_or_scroll: %s", Is_Note_Or_Scroll() ? "true" : "false");

        SKYLIB_LOG(indent + SKYLIB_TAB + "can_teach_skill: %s", Can_Teach_Skill() ? "true" : "false");
        SKYLIB_LOG(indent + SKYLIB_TAB + "can_teach_spell: %s", Can_Teach_Spell() ? "true" : "false");

        SKYLIB_LOG(indent + SKYLIB_TAB + "unparsed_text: %s", Unparsed_Text());

        SKYLIB_LOG(indent + "}");
    }

}
