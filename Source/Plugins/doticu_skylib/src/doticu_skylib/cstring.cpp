/*
    Copyright © 2020 r-neal-kelly, aka doticu
*/

#include "doticu_skylib/cstring.h"

namespace doticu_skylib {

    size_t CString_t::Length(const char* sub, Bool_t with_null)
    {
        size_t idx = 0;
        for (; sub[idx]; idx += 1) {
        }
        if (with_null) {
            return idx + 1;
        } else {
            return idx;
        }
    }

    Bool_t CString_t::Is_Same(const char* sub, const char* obj, Bool_t caseless)
    {
        if (sub && obj) {
            if (caseless) {
                return _stricmp(sub, obj) == 0;
            } else {
                return strcmp(sub, obj) == 0;
            }
        } else {
            return false;
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

    Bool_t CString_t::Is_Length_Less_Than(const char* sub, Word_t length, Bool_t with_null)
    {
        if (sub) {
            Word_t idx = 0;
            for (; idx < length; idx += 1) {
                if (sub[idx] == 0) {
                    if (with_null) {
                        return idx + 1 < length;
                    } else {
                        return true;
                    }
                }
            }
            return false;
        } else {
            return false;
        }
    }

    Bool_t CString_t::Is_Length_Greater_Than(const char* sub, Word_t length, Bool_t with_null)
    {
        if (sub) {
            Word_t idx = 0;
            for (; idx <= length; idx += 1) {
                if (sub[idx] == 0) {
                    if (with_null) {
                        return idx + 1 > length;
                    } else {
                        return false;
                    }
                }
            }
            return true;
        } else {
            return false;
        }
    }

    const char* CString_t::Seek_After(const char* sub, const char obj, size_t max_chars)
    {
        if (sub) {
            size_t chars = 0;
            while (*sub && *sub == obj && chars < max_chars) {
                sub += 1;
                chars += 1;
            }
            return sub;
        } else {
            return nullptr;
        }
    }

}
