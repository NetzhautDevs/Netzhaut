// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES ========================================================================================

#include "Tokenizer.h"

#include "../System/Memory.h"
#include "../Common/Macros.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>

// HELPER ==========================================================================================

static bool nh_core_isASCIIUpperAlpha(
    char codepoint)
{
NH_CORE_BEGIN()
NH_CORE_END(codepoint >= 0x41 && codepoint <= 0x5A)
}

static bool nh_core_isASCIILowerAlpha(
    char codepoint)
{
NH_CORE_BEGIN()
NH_CORE_END(codepoint >= 0x61 && codepoint <= 0x7A)
}

static bool nh_core_isASCIINumber(
    char codepoint)
{
NH_CORE_BEGIN()
NH_CORE_END(codepoint >= 0x30 && codepoint <= 0x39)
}

static bool nh_core_isASCIIAlpha(
    char codepoint)
{
NH_CORE_BEGIN()
NH_CORE_END(nh_core_isASCIIUpperAlpha(codepoint) || nh_core_isASCIILowerAlpha(codepoint))
}

static bool nh_core_isBracket(
    char codepoint)
{
NH_CORE_BEGIN()
NH_CORE_END(codepoint == '(' || codepoint == ')' || codepoint == '{' || codepoint == '}' || codepoint == '[' || codepoint == ']')
}

static bool nh_core_isTokenBegin(
    char codepoint)
{
NH_CORE_BEGIN()

    if (nh_core_isASCIIAlpha(codepoint) || nh_core_isASCIINumber(codepoint) || nh_core_isBracket(codepoint) 
    || codepoint == ',' 
    || codepoint == '"' 
    || codepoint == ':' 
    || codepoint == ';') 

    {NH_CORE_END(true)}

NH_CORE_END(false)
}

// TOKENIZE ========================================================================================

static char *nh_core_tokenizeString(
    nh_ConfigToken *Token_p, char *bytes_p)
{
NH_CORE_BEGIN()

    char *string_p = malloc(1);
    unsigned int stringLength = 0;

    char *stringBegin_p = bytes_p;

    bool escape = false;
    while (*bytes_p && (*bytes_p != '"' || escape)) {
        escape = escape ? false : *bytes_p == 0x5C;
        if (!escape && *bytes_p != '\n') {
            string_p = realloc(string_p, stringLength + 1);
            string_p[stringLength++] = *bytes_p;
        }
        bytes_p++;
    }
    if (!*bytes_p) {NH_CORE_END(NULL)}

    *bytes_p = 0;

    string_p = realloc(string_p, stringLength + 1);
    string_p[stringLength] = 0;

    Token_p->string_p = string_p;

    *bytes_p = '"';

NH_CORE_END(&bytes_p[1])
}

static char *nh_core_getConfigToken(
    nh_ConfigToken *Token_p, char *bytes_p) 
{
NH_CORE_BEGIN()

    if (!*bytes_p) {NH_CORE_END(NULL)}

    Token_p->type     = NH_CONFIG_TOKEN_UNDEFINED;
    Token_p->string_p = NULL;

    while (*bytes_p && !nh_core_isTokenBegin(*bytes_p)) {
        if (bytes_p[0] == '/' && bytes_p[1] == '/') {
            while (*bytes_p && *bytes_p != '\n') {bytes_p++;}
        }
        bytes_p++;
    }
    if (!*bytes_p) {NH_CORE_END(NULL)}

    char *tokenBegin_p = bytes_p;

    switch (*tokenBegin_p) 
    {
        case '(' : Token_p->type = NH_CONFIG_TOKEN_ROUND_BRACKET_LEFT; break;
        case ')' : Token_p->type = NH_CONFIG_TOKEN_ROUND_BRACKET_RIGHT; break;
        case '{' : Token_p->type = NH_CONFIG_TOKEN_CURLY_BRACKET_LEFT; break;
        case '}' : Token_p->type = NH_CONFIG_TOKEN_CURLY_BRACKET_RIGHT; break;
        case '[' : Token_p->type = NH_CONFIG_TOKEN_ANGLE_BRACKET_LEFT; break;
        case ']' : Token_p->type = NH_CONFIG_TOKEN_ANGLE_BRACKET_RIGHT; break;
        case ',' : Token_p->type = NH_CONFIG_TOKEN_COMMA; break;
        case ':' : Token_p->type = NH_CONFIG_TOKEN_COLON; break;
        case ';' : Token_p->type = NH_CONFIG_TOKEN_SEMICOLON; break;
        case '"' :
            Token_p->type = NH_CONFIG_TOKEN_STRING;
            NH_CORE_END(nh_core_tokenizeString(Token_p, &bytes_p[1]))
            break;
    }
    
    if (Token_p->type != NH_CONFIG_TOKEN_UNDEFINED) {
        NH_CORE_END(&bytes_p[1])
    }

    while (*bytes_p && (nh_core_isASCIIAlpha(*bytes_p) || nh_core_isASCIINumber(*bytes_p) 
        || *bytes_p == '_' || *bytes_p == '.' || *bytes_p == '-')) {bytes_p++;}
    if (!*bytes_p) {NH_CORE_END(NULL)}

    char tmp = *bytes_p;
    *bytes_p = 0;    

    Token_p->type = NH_CONFIG_TOKEN_IDENTIFIER;
    Token_p->string_p = malloc(strlen(tokenBegin_p) + 1);
    strcpy(Token_p->string_p, tokenBegin_p);

    *bytes_p = tmp;

NH_CORE_END(bytes_p)
}

static void nh_core_getConfigTokens(
    nh_ConfigToken *Tokens_p, char *bytes_p, unsigned int *tokens_p) 
{
NH_CORE_BEGIN()

    unsigned int tokens = 0;

    while (bytes_p)
    {
        nh_ConfigToken Token;
        bytes_p = nh_core_getConfigToken(&Token, bytes_p);
        if (Tokens_p) {
            Tokens_p[tokens] = Token;
        } else if (Token.string_p) {
            free(Token.string_p);
        }
        tokens++;
    }

    if (Tokens_p) {
        Tokens_p[tokens - 1].type = NH_CONFIG_TOKEN_EOF;        
    }

    if (tokens_p) {*tokens_p = tokens;}

NH_CORE_SILENT_END()
}

NH_API_RESULT nh_core_tokenizeConfig(
    nh_ConfigTokenizer *Tokenizer_p, char *data_p, int length) 
{
NH_CORE_BEGIN()

    NH_CORE_CHECK_NULL(data_p)
    NH_CORE_CHECK_NULL(Tokenizer_p)
    Tokenizer_p->tokens = 0;
    Tokenizer_p->Tokens_p = NULL;

    char *bytes_p = nh_core_allocate(length + 1);
    NH_CORE_CHECK_NULL(bytes_p)
    memset(bytes_p, 0, length + 1);
    memcpy(bytes_p, data_p, length);

    unsigned int tokens = 0;
    nh_core_getConfigTokens(NULL, bytes_p, &tokens);

    nh_ConfigToken *Tokens_p = malloc(sizeof(nh_ConfigToken) * tokens);
    for (int i = 0; i < tokens; ++i) {
        Tokens_p[i].string_p = NULL;
    }
    nh_core_getConfigTokens(Tokens_p, bytes_p, NULL);

    nh_core_free(bytes_p);

    Tokenizer_p->tokens   = tokens;
    Tokenizer_p->Tokens_p = Tokens_p;

NH_CORE_END(NH_API_SUCCESS)
}

void nh_core_freeConfigTokenizer(
    nh_ConfigTokenizer *Tokenizer_p)
{
NH_CORE_BEGIN()

    for (int i = 0; i < Tokenizer_p->tokens; ++i) {
        if (Tokenizer_p->Tokens_p[i].string_p) {free(Tokenizer_p->Tokens_p[i].string_p);}
    }

    free(Tokenizer_p->Tokens_p);
    Tokenizer_p->tokens = 0;

NH_CORE_SILENT_END()
}

