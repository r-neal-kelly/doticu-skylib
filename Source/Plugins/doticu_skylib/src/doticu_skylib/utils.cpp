/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/utils.h"

namespace doticu_skylib {

    Word_t CString_t::Length(const char* sub, Bool_t with_null)
    {
        Word_t idx = 0;
        for (; idx < MAX_LENGTH; idx += 1) {
            if (sub[idx] == 0) {
                return idx;
            }
        }
        if (with_null) {
            return idx + 1;
        } else {
            return idx;
        }
    }

    Bool_t CString_t::Is_Same(const char* sub, const char* obj, Bool_t caseless)
    {
        if (caseless) {
            return _stricmp(sub, obj) == 0;
        } else {
            return strcmp(sub, obj) == 0;
        }
    }

    Bool_t CString_t::Starts_With(const char* sub, const char* obj, Bool_t caseless)
    {
        if (!sub || !obj) {
            return false;
        } else if (sub[0] == 0 && obj[0] == 0) {
            return true;
        } else if (sub[0] == 0 || obj[0] == 0) {
            return false;
        } else {
            const char* sub_it = sub;
            const char* obj_it = obj;
            char sub_c = *sub_it;
            char obj_c = *obj_it;
            if (caseless) {
                while (obj_c != 0) {
                    if (sub_c == 0 || tolower(sub_c) != tolower(obj_c)) {
                        return false;
                    }
                    sub_it += 1;
                    obj_it += 1;
                    sub_c = *sub_it;
                    obj_c = *obj_it;
                }
                return true;
            } else {
                while (obj_c != 0) {
                    if (sub_c == 0 || sub_c != obj_c) {
                        return false;
                    }
                    sub_it += 1;
                    obj_it += 1;
                    sub_c = *sub_it;
                    obj_c = *obj_it;
                }
                return true;
            }
        }
    }

    Bool_t CString_t::Starts_With(const char* sub, const char obj, Bool_t caseless)
    {
        if (sub) {
            if (caseless) {
                return tolower(sub[0]) == tolower(obj);
            } else {
                return sub[0] == obj;
            }
        } else {
            return false;
        }
    }

    Bool_t CString_t::Ends_With(const char* sub, const char* obj, Bool_t caseless)
    {
        if (!sub || !obj) {
            return false;
        } else if (sub[0] == 0 && obj[0] == 0) {
            return true;
        } else if (sub[0] == 0 || obj[0] == 0) {
            return false;
        } else {
            const char* sub_it = sub + Length(sub) + 1;
            const char* obj_it = obj + Length(obj) + 1;
            if (caseless) {
                while (sub_it != sub && obj_it != obj) {
                    sub_it -= 1;
                    obj_it -= 1;
                    if (tolower(*sub_it) != tolower(*obj_it)) {
                        return false;
                    }
                }
                return true;
            } else {
                while (sub_it != sub && obj_it != obj) {
                    sub_it -= 1;
                    obj_it -= 1;
                    if (*sub_it != *obj_it) {
                        return false;
                    }
                }
                return true;
            }
        }
    }

    Bool_t CString_t::Ends_With(const char* sub, const char obj, Bool_t caseless)
    {
        if (sub) {
            if (caseless) {
                return tolower(sub[Length(sub)]) == tolower(obj);
            } else {
                return sub[Length(sub)] == obj;
            }
        } else {
            return false;
        }
    }

    Bool_t CString_t::Contains(const char* sub, const char* obj, Bool_t caseless)
    {
        if (sub && obj) {
            for (Word_t idx = 0; sub[idx] != 0; idx += 1) {
                if (Starts_With(sub + idx, obj, caseless)) {
                    return true;
                }
            }
            return false;
        } else {
            return false;
        }
    }

}
