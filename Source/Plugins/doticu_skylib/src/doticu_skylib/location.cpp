/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/const_keywords.h"
#include "doticu_skylib/dynamic_array.inl"
#include "doticu_skylib/game.h"
#include "doticu_skylib/location.h"

namespace doticu_skylib {

    Vector_t<some<Location_t*>> Location_t::Locations_Dynamic()
    {
        Vector_t<some<Location_t*>> results;
        Locations_Dynamic(results);
        return results;
    }

    void Location_t::Locations_Dynamic(Vector_t<some<Location_t*>>& results)
    {
        class Iterator :
            public Iterator_i<some<Form_t*>>
        {
        public:
            Vector_t<some<Location_t*>>& results;

        public:
            Iterator(Vector_t<some<Location_t*>>& results) :
                results(results)
            {
            }

        public:
            virtual Iterator_e operator ()(some<Form_t*> form) override
            {
                maybe<Location_t*> location = form->As_Location();
                if (location && location->Is_Valid()) {
                    this->results.push_back(location());
                }
                return Iterator_e::CONTINUE;
            }
        };

        results.reserve(Game_t::Self()->Locations().Count() + 64);

        Iterator iterator(results);

        Game_t::Iterate_Forms(iterator);
    }

    Vector_t<some<Location_t*>> Location_t::Locations_Static()
    {
        Vector_t<some<Location_t*>> results;
        Locations_Static(results);
        return results;
    }

    void Location_t::Locations_Static(Vector_t<some<Location_t*>>& results)
    {
        Array_t<maybe<Location_t*>>& locations = Game_t::Self()->Locations();

        size_t location_count = locations.Count();
        results.reserve(location_count);

        for (size_t idx = 0, end = location_count; idx < end; idx += 1) {
            maybe<Location_t*> location = locations[idx];
            if (location && location->Is_Valid() && !results.Has(location())) {
                results.push_back(location());
            }
        }
    }

    const Vector_t<some<Keyword_t*>>& Location_t::Civilized_Types()
    {
        static Vector_t<some<Keyword_t*>> types =
        {
            Const::Keyword::Location_Type_Dwelling(),
            Const::Keyword::Location_Type_Habitation(),
            Const::Keyword::Location_Type_Habitation_With_Inn(),

            Const::Keyword::Location_Type_Settlement(),
            Const::Keyword::Location_Type_City(),
            Const::Keyword::Location_Type_Town(),
            Const::Keyword::Location_Type_Orc_Stronghold(),
            Const::Keyword::Location_Type_Guild(),
            Const::Keyword::Location_Type_Inn(),
            Const::Keyword::Location_Type_Farm(),
            Const::Keyword::Location_Type_Mine(),
            Const::Keyword::Location_Type_House(),
            Const::Keyword::Location_Type_Store(),
            Const::Keyword::Location_Type_Lumber_Mill(),
            Const::Keyword::Location_Type_Player_House(),
            Const::Keyword::Location_Type_Homestead(),
            Const::Keyword::Location_Type_Homestead_With_Shrine(),
            Const::Keyword::Location_Type_Castle(),
            Const::Keyword::Location_Type_Barracks(),
            Const::Keyword::Location_Type_Cemetery(),
            Const::Keyword::Location_Type_Temple(),
            Const::Keyword::Location_Type_Jail(),
            Const::Keyword::Location_Type_Stewards_Dwelling(),
        };

        return types;
    }

    const Vector_t<some<Keyword_t*>>& Location_t::Common_Civilized_Types()
    {
        static Vector_t<some<Keyword_t*>> types =
        {
            Const::Keyword::Location_Type_Dwelling(),
            Const::Keyword::Location_Type_Habitation(),
            Const::Keyword::Location_Type_Habitation_With_Inn(),
        };

        return types;
    }

    const Vector_t<some<Keyword_t*>>& Location_t::Uncommon_Civilized_Types()
    {
        static Vector_t<some<Keyword_t*>> types =
        {
            Const::Keyword::Location_Type_Settlement(),
            Const::Keyword::Location_Type_City(),
            Const::Keyword::Location_Type_Town(),
            Const::Keyword::Location_Type_Orc_Stronghold(),
            Const::Keyword::Location_Type_Guild(),
            Const::Keyword::Location_Type_Inn(),
            Const::Keyword::Location_Type_Farm(),
            Const::Keyword::Location_Type_Mine(),
            Const::Keyword::Location_Type_House(),
            Const::Keyword::Location_Type_Store(),
            Const::Keyword::Location_Type_Lumber_Mill(),
            Const::Keyword::Location_Type_Player_House(),
            Const::Keyword::Location_Type_Homestead(),
            Const::Keyword::Location_Type_Homestead_With_Shrine(),
            Const::Keyword::Location_Type_Castle(),
            Const::Keyword::Location_Type_Barracks(),
            Const::Keyword::Location_Type_Cemetery(),
            Const::Keyword::Location_Type_Temple(),
            Const::Keyword::Location_Type_Jail(),
            Const::Keyword::Location_Type_Stewards_Dwelling(),
        };

        return types;
    }

    const Vector_t<some<Keyword_t*>>& Location_t::Dangerous_Types()
    {
        static Vector_t<some<Keyword_t*>> types =
        {
            Const::Keyword::Location_Type_Dungeon(),

            Const::Keyword::Location_Type_Clearable(),
            Const::Keyword::Location_Type_Animal_Den(),
            Const::Keyword::Location_Type_Ash_Spawn_Lair(),
            Const::Keyword::Location_Type_Bandit_Camp(),
            Const::Keyword::Location_Type_Dragon_Lair(),
            Const::Keyword::Location_Type_Dragon_Priest_Lair(),
            Const::Keyword::Location_Type_Draugr_Crypt(),
            Const::Keyword::Location_Type_Dwarven_Automaton_Ruin(),
            Const::Keyword::Location_Type_Falmer_Hive(),
            Const::Keyword::Location_Type_Forsworn_Camp(),
            Const::Keyword::Location_Type_Giant_Camp(),
            Const::Keyword::Location_Type_Hagraven_Nest(),
            Const::Keyword::Location_Type_Military_Camp(),
            Const::Keyword::Location_Type_Military_Fort(),
            Const::Keyword::Location_Type_Riekling_Camp(),
            Const::Keyword::Location_Type_Ship(),
            Const::Keyword::Location_Type_Shipwreck(),
            Const::Keyword::Location_Type_Spriggan_Grove(),
            Const::Keyword::Location_Type_Vampire_Lair(),
            Const::Keyword::Location_Type_Warlock_Lair(),
            Const::Keyword::Location_Type_Werebear_Lair(),
            Const::Keyword::Location_Type_Werewolf_Lair(),
            Const::Keyword::Location_Set_Cave(),
            Const::Keyword::Location_Set_Cave_Ice(),
            Const::Keyword::Location_Set_Dwarven_Ruin(),
            Const::Keyword::Location_Set_Military_Camp(),
            Const::Keyword::Location_Set_Military_Fort(),
            Const::Keyword::Location_Set_Nordic_Ruin(),
        };

        return types;
    }

    const Vector_t<some<Keyword_t*>>& Location_t::Common_Dangerous_Types()
    {
        static Vector_t<some<Keyword_t*>> types =
        {
            Const::Keyword::Location_Type_Dungeon(),
        };

        return types;
    }

    const Vector_t<some<Keyword_t*>>& Location_t::Uncommon_Dangerous_Types()
    {
        static Vector_t<some<Keyword_t*>> types =
        {
            Const::Keyword::Location_Type_Clearable(),
            Const::Keyword::Location_Type_Animal_Den(),
            Const::Keyword::Location_Type_Ash_Spawn_Lair(),
            Const::Keyword::Location_Type_Bandit_Camp(),
            Const::Keyword::Location_Type_Dragon_Lair(),
            Const::Keyword::Location_Type_Dragon_Priest_Lair(),
            Const::Keyword::Location_Type_Draugr_Crypt(),
            Const::Keyword::Location_Type_Dwarven_Automaton_Ruin(),
            Const::Keyword::Location_Type_Falmer_Hive(),
            Const::Keyword::Location_Type_Forsworn_Camp(),
            Const::Keyword::Location_Type_Giant_Camp(),
            Const::Keyword::Location_Type_Hagraven_Nest(),
            Const::Keyword::Location_Type_Military_Camp(),
            Const::Keyword::Location_Type_Military_Fort(),
            Const::Keyword::Location_Type_Riekling_Camp(),
            Const::Keyword::Location_Type_Ship(),
            Const::Keyword::Location_Type_Shipwreck(),
            Const::Keyword::Location_Type_Spriggan_Grove(),
            Const::Keyword::Location_Type_Vampire_Lair(),
            Const::Keyword::Location_Type_Warlock_Lair(),
            Const::Keyword::Location_Type_Werebear_Lair(),
            Const::Keyword::Location_Type_Werewolf_Lair(),
            Const::Keyword::Location_Set_Cave(),
            Const::Keyword::Location_Set_Cave_Ice(),
            Const::Keyword::Location_Set_Dwarven_Ruin(),
            Const::Keyword::Location_Set_Military_Camp(),
            Const::Keyword::Location_Set_Military_Fort(),
            Const::Keyword::Location_Set_Nordic_Ruin(),
        };

        return types;
    }

    Bool_t Location_t::Is_Inn() const
    {
        return Has_Or_Inherits_Keyword(Const::Keyword::Location_Type_Inn());
    }

    Bool_t Location_t::Is_Likely_City_Or_Town() const
    {
        return
            Has_Or_Inherits_Keyword(Const::Keyword::Location_Type_City()) ||
            Has_Or_Inherits_Keyword(Const::Keyword::Location_Type_Town()) ||
            Has_Or_Inherits_Keyword(Const::Keyword::Location_Type_Habitation_With_Inn());
    }

    Bool_t Location_t::Is_Likely_Civilized() const
    {
        if (Has_Or_Inherits_Any_Keywords(Common_Civilized_Types())) {
            return true;
        } else if (Has_Or_Inherits_Any_Keywords(Common_Dangerous_Types())) {
            return false;
        } else if (Has_Or_Inherits_Any_Keywords(Uncommon_Civilized_Types())) {
            return true;
        } else {
            return false;
        }
    }

    Bool_t Location_t::Is_Likely_Dangerous() const
    {
        if (Has_Or_Inherits_Any_Keywords(Common_Civilized_Types())) {
            return false;
        } else if (Has_Or_Inherits_Any_Keywords(Dangerous_Types())) {
            return true;
        } else {
            return false;
        }
    }

    Bool_t Location_t::Is_Likely_Home() const
    {
        return
            Has_Or_Inherits_Keyword(Const::Keyword::Location_Type_House()) ||
            Has_Or_Inherits_Keyword(Const::Keyword::Location_Type_Player_House()) ||
            Has_Or_Inherits_Keyword(Const::Keyword::Location_Type_Homestead()) ||
            Has_Or_Inherits_Keyword(Const::Keyword::Location_Type_Homestead_With_Shrine());
    }

    String_t Location_t::Any_Name()
    {
        const char* name = Name();
        if (!name || !name[0]) {
            name = Get_Editor_ID();
            if (!name || !name[0]) {
                return Form_ID_String();
            } else {
                return name;
            }
        } else {
            return name;
        }
    }

    Vector_t<some<Location_t*>> Location_t::Parents() const
    {
        Vector_t<some<Location_t*>> results;
        Parents(results);
        return results;
    }

    void Location_t::Parents(Vector_t<some<Location_t*>>& results) const
    {
        for (maybe<Location_t*> parent = this->parent_location; parent; parent = parent->parent_location) {
            if (!results.Has(parent())) {
                results.push_back(parent());
            }
        }
    }

    Bool_t Location_t::Has_Keyword(some<Keyword_t*> keyword) const
    {
        return Component_Has_Keyword(keyword);
    }

    Bool_t Location_t::Inherits_Keyword(some<Keyword_t*> keyword) const
    {
        for (maybe<Location_t*> parent = this->parent_location; parent; parent = parent->parent_location) {
            if (parent->Component_Has_Keyword(keyword)) {
                return true;
            }
        }
        return false;
    }

    Bool_t Location_t::Has_Or_Inherits_Keyword(some<Keyword_t*> keyword) const
    {
        return Has_Keyword(keyword) || Inherits_Keyword(keyword);
    }

    Bool_t Location_t::Has_Any_Keywords(const Vector_t<some<Keyword_t*>> keywords) const
    {
        return Component_Has_Any_Keywords(keywords);
    }

    Bool_t Location_t::Inherits_Any_Keywords(const Vector_t<some<Keyword_t*>> keywords) const
    {
        for (maybe<Location_t*> parent = this->parent_location; parent; parent = parent->parent_location) {
            if (parent->Component_Has_Any_Keywords(keywords)) {
                return true;
            }
        }
        return false;
    }

    Bool_t Location_t::Has_Or_Inherits_Any_Keywords(const Vector_t<some<Keyword_t*>> keywords) const
    {
        return Has_Any_Keywords(keywords) || Inherits_Any_Keywords(keywords);
    }

}
