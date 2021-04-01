/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/book.h"
#include "doticu_skylib/const_keywords.h"

namespace doticu_skylib {

    Book_t::Teachable_u::Teachable_u() :
        spell(none<Spell_t*>())
    {
    }

    Book_t::Teachable_u::~Teachable_u()
    {
        this->spell = none<Spell_t*>();
    }

    Bool_t Book_t::Can_Take() const
    {
        return !Cant_Take();
    }

    Bool_t Book_t::Cant_Take() const
    {
        return this->book_flags.Is_Flagged(Book_Flags_e::CANT_TAKE);
    }

    Bool_t Book_t::Can_Teach_Skill() const
    {
        return this->book_flags.Is_Flagged(Book_Flags_e::CAN_TEACH_SKILL);
    }

    Bool_t Book_t::Can_Teach_Spell() const
    {
        return this->book_flags.Is_Flagged(Book_Flags_e::CAN_TEACH_SPELL);
    }

    Bool_t Book_t::Has_Been_Read() const
    {
        return this->book_flags.Is_Flagged(Book_Flags_e::HAS_BEEN_READ);
    }

    Bool_t Book_t::Hasnt_Been_Read() const
    {
        return !Has_Been_Read();
    }

    Bool_t Book_t::Is_Skill_Book() const
    {
        return !Is_Spell_Tome() && Can_Teach_Skill();
    }

    Bool_t Book_t::Is_Spell_Tome() const
    {
        return Can_Teach_Spell();
    }

    Bool_t Book_t::Is_Recipe() const
    {
        return Component_Has_Keyword(Const::Keyword::Vendor_Item_Recipe());
    }

    DString_t Book_t::Unparsed_Text() const
    {
        return std::move(Description(this));
    }

    void Book_t::Log(std::string indent)
    {
        SKYLIB_LOG(indent + "Book_t::Log");
        SKYLIB_LOG(indent + "{");

        SKYLIB_LOG(indent + SKYLIB_TAB + "component_name: %s", Component_Name());
        SKYLIB_LOG(indent + SKYLIB_TAB + "form_id: %s", this->form_id.As_String());

        SKYLIB_LOG(indent + SKYLIB_TAB + "book_type: %u", this->book_type);

        SKYLIB_LOG(indent + SKYLIB_TAB + "cant_take: %s", Cant_Take() ? "true" : "false");

        SKYLIB_LOG(indent + SKYLIB_TAB + "can_teach_skill: %s", Can_Teach_Skill() ? "true" : "false");
        SKYLIB_LOG(indent + SKYLIB_TAB + "can_teach_spell: %s", Can_Teach_Spell() ? "true" : "false");
        SKYLIB_LOG(indent + SKYLIB_TAB + "can_teach_skill_and_spell: %s", Can_Teach_Skill() && Can_Teach_Spell() ? "true" : "false");

        SKYLIB_LOG(indent + SKYLIB_TAB + "has_been_read: %s", Has_Been_Read() ? "true" : "false");

        SKYLIB_LOG(indent + SKYLIB_TAB + "is_skill_book: %s", Is_Skill_Book() ? "true" : "false");
        SKYLIB_LOG(indent + SKYLIB_TAB + "is_spell_tome: %s", Is_Spell_Tome() ? "true" : "false");
        SKYLIB_LOG(indent + SKYLIB_TAB + "is_recipe: %s", Is_Recipe() ? "true" : "false");

        SKYLIB_LOG(indent + SKYLIB_TAB + "has_unparsed_text: %s", Unparsed_Text() ? "true" : "false");

        SKYLIB_LOG(indent + SKYLIB_TAB + "keywords:");
        Keywords_c::Log_Component_Keywords(indent + SKYLIB_TAB + SKYLIB_TAB);

        SKYLIB_LOG(indent + "}");
    }

}
