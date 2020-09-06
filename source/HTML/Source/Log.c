// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2020  Dajo Frey
 * Published under LGPLv3
 */

// INCLUDE =========================================================================================

#include "../Header/Log.h"
#include "../Header/Macros.h"

#include "../../Core/Header/String.h"
#include "../../Core/Header/Memory.h"
#include "../../Core/Header/Config.h"
#include "../../Core/Header/Output.h"

#include NH_DEBUG
#include NH_DEFAULT_CHECK

#include <string.h>
#include <stdio.h>

// DEBUG ===========================================================================================

NH_RESULT Nh_HTML_logTree( // TODO multithreading
    Nh_HTML_Tree *Tree_p, NH_BOOL unformatted)
{
NH_BEGIN()

    if (Nh_getConfig()->Flags.Log.document)
    {
        Nh_String *String_p = Nh_allocateString(NULL);

        char *document_p = Nh_HTML_stringifyTree(Tree_p, unformatted);
        NH_CHECK_NULL(document_p)

        NH_CHECK((Nh_appendFormatToString(String_p, "%s\n", document_p)))

        char *chars_p = Nh_getChars(String_p);
        Nh_freeString(String_p, false);
        Nh_free(document_p);

        if (Nh_addOutput(NH_OUTPUT_CHARS, chars_p, NH_FALSE) != NH_SUCCESS) {
            Nh_free(chars_p);
            NH_END(NH_ERROR_BAD_STATE)
        }
    }

NH_END(NH_SUCCESS)
}

