// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES ========================================================================================

#include "Values.h"
#include "Properties.h"
#include "Filter.h"

#include "../Common/Log.h"
#include "../Common/Macros.h"

#include "../../nhcore/Util/Array.h"
#include "../../nhcore/System/Memory.h"
#include "../../nhcore/Util/List.h"

#include "../../nhdom/Interfaces/Node.h"
#include "../../nhencoding/Encodings/UTF8.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
	
// TYPES ===========================================================================================

const NH_BYTE *NH_CSS_TYPE_NAMES_PP[] =
{
    "undefined",
    "number",
    "em",
    "ex",
    "cap",
    "ch",
    "ic",
    "rem",
    "lh",
    "rlh",
    "vw",
    "vh",
    "vi",
    "vb",
    "vmin",
    "vmax",
    "in",
    "cm",
    "mm",
    "pt",
    "pc",
    "px",
    "q",
    "s",
    "ms",
    "hz",
    "khz",
    "dpi",
    "dpcm",
    "dppx",
    "deg",
    "grad",
    "rad",
    "turn",
    "percentage",
    "keyword",
    "function",
    "hex",
    "url",
    "count",
    "color",
    "string",
    "keyword_initial",
    "keyword_inherit",
    "keyword_unset",
    "keyword_revert",
};

// INIT =============================================================================================

nh_css_Value nh_css_initValue(
    NH_CSS_VALUE_SCOPE scope, NH_CSS_VALUE type)
{
NH_CSS_BEGIN()

    nh_css_Value Value;
    Value.Common.type     = type;
    Value.Common.Next_p   = NULL;
    Value.Common.scope    = scope;
    Value.Common.Origin_p = NULL;

NH_CSS_END(Value)
}

// IS STRING =======================================================================================

NH_BOOL nh_css_isStringValue(
    nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    if (Value_p->Common.type == NH_CSS_VALUE_KEYWORD
    ||  Value_p->Common.type == NH_CSS_VALUE_KEYWORD_INITIAL
    ||  Value_p->Common.type == NH_CSS_VALUE_KEYWORD_INHERIT
    ||  Value_p->Common.type == NH_CSS_VALUE_KEYWORD_UNSET
    ||  Value_p->Common.type == NH_CSS_VALUE_KEYWORD_REVERT
    ||  Value_p->Common.type == NH_CSS_VALUE_STRING
    ||  Value_p->Common.type == NH_CSS_VALUE_HEX
    ||  Value_p->Common.type == NH_CSS_VALUE_FUNCTION)
    {
        NH_CSS_END(NH_TRUE)
    }

NH_CSS_END(NH_FALSE)
}

static NH_BOOL nh_css_isDimensionValueType(
    NH_CSS_VALUE type)
{
NH_CSS_BEGIN()

    if (type == NH_CSS_VALUE_EM
    ||  type == NH_CSS_VALUE_EX
    ||  type == NH_CSS_VALUE_CAP
    ||  type == NH_CSS_VALUE_CH
    ||  type == NH_CSS_VALUE_IC
    ||  type == NH_CSS_VALUE_REM
    ||  type == NH_CSS_VALUE_LH
    ||  type == NH_CSS_VALUE_RLH
    ||  type == NH_CSS_VALUE_VW
    ||  type == NH_CSS_VALUE_VH
    ||  type == NH_CSS_VALUE_VI
    ||  type == NH_CSS_VALUE_VB
    ||  type == NH_CSS_VALUE_VMIN
    ||  type == NH_CSS_VALUE_VMAX
    ||  type == NH_CSS_VALUE_IN
    ||  type == NH_CSS_VALUE_CM
    ||  type == NH_CSS_VALUE_MM
    ||  type == NH_CSS_VALUE_PT
    ||  type == NH_CSS_VALUE_PC
    ||  type == NH_CSS_VALUE_PX
    ||  type == NH_CSS_VALUE_Q
    ||  type == NH_CSS_VALUE_S
    ||  type == NH_CSS_VALUE_MS
    ||  type == NH_CSS_VALUE_HZ
    ||  type == NH_CSS_VALUE_KHZ
    ||  type == NH_CSS_VALUE_DPI
    ||  type == NH_CSS_VALUE_DPCM
    ||  type == NH_CSS_VALUE_DPPX
    ||  type == NH_CSS_VALUE_DEG
    ||  type == NH_CSS_VALUE_GRAD
    ||  type == NH_CSS_VALUE_RAD
    ||  type == NH_CSS_VALUE_TURN) {
        NH_CSS_END(NH_TRUE)
    }

NH_CSS_END(NH_FALSE)
}

NH_BOOL nh_css_isLengthValue(
    nh_css_Value *Value_p)
{
NH_CSS_BEGIN()
NH_CSS_END(nh_css_isDimensionValueType(Value_p->Common.type) || (Value_p->Common.type == NH_CSS_VALUE_NUMBER && Value_p->number == 0))
}

NH_BOOL nh_css_isLengthPercentageValue(
    nh_css_Value *Value_p)
{
NH_CSS_BEGIN()
NH_CSS_END(nh_css_isLengthValue(Value_p) || Value_p->Common.type == NH_CSS_VALUE_PERCENTAGE)
}

// CONVERT =========================================================================================

static NH_CSS_RESULT nh_css_convertTokenToValue(
    nh_css_Token *Token_p, nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    switch (Token_p->type)
    {
        case NH_CSS_TOKEN_IDENT :
        {
            Value_p->Common.type = NH_CSS_VALUE_KEYWORD;
            Value_p->String = nh_encoding_encodeUTF8(Token_p->Other.Value.p, Token_p->Other.Value.length);

            for (int i = 0; i< Value_p->String.length; ++i) {
                Value_p->String.p[i] = tolower(Value_p->String.p[i]);
            }

            if (!strcmp(Value_p->String.p, "initial")) {
                Value_p->Common.type = NH_CSS_VALUE_KEYWORD_INITIAL;
            }
            else if (!strcmp(Value_p->String.p, "inherit")) {
                Value_p->Common.type = NH_CSS_VALUE_KEYWORD_INHERIT;
            }
            else if (!strcmp(Value_p->String.p, "unset")) {
                Value_p->Common.type = NH_CSS_VALUE_KEYWORD_UNSET;
            }
            else if (!strcmp(Value_p->String.p, "revert")) {
                Value_p->Common.type = NH_CSS_VALUE_KEYWORD_REVERT;
            }
         
            break;
        }
        case NH_CSS_TOKEN_STRING :
            Value_p->Common.type = NH_CSS_VALUE_STRING;
            Value_p->String = nh_encoding_encodeUTF8(Token_p->Other.Value.p, Token_p->Other.Value.length);
            break;

        case NH_CSS_TOKEN_HASH :
            Value_p->Common.type = NH_CSS_VALUE_HEX;
            Value_p->String = nh_encoding_encodeUTF8(Token_p->Other.Value.p, Token_p->Other.Value.length);
            break;

        case NH_CSS_TOKEN_FUNCTION :
            Value_p->Common.type = NH_CSS_VALUE_FUNCTION;
            Value_p->String = nh_encoding_encodeUTF8(Token_p->Other.Value.p, Token_p->Other.Value.length);
            break;

        case NH_CSS_TOKEN_URL :
            // TODO
            break;

        case NH_CSS_TOKEN_NUMBER :
            Value_p->Common.type = NH_CSS_VALUE_NUMBER;
            Value_p->number = Token_p->Number.value;
            break;

        case NH_CSS_TOKEN_PERCENTAGE :
            Value_p->Common.type = NH_CSS_VALUE_PERCENTAGE;
            Value_p->number = Token_p->Percentage.value;
            break;

        case NH_CSS_TOKEN_DIMENSION :
            if (Token_p->Dimension.Unit.length == 2) 
            {
                if (Token_p->Dimension.Unit.p[0] == 'e' && Token_p->Dimension.Unit.p[1] == 'm') {
                    Value_p->Common.type = NH_CSS_VALUE_EM;
                }
                else if (Token_p->Dimension.Unit.p[0] == 'e' && Token_p->Dimension.Unit.p[1] == 'x') {
                    Value_p->Common.type = NH_CSS_VALUE_EX;
                }
                else if (Token_p->Dimension.Unit.p[0] == 'i' && Token_p->Dimension.Unit.p[1] == 'n') {
                    Value_p->Common.type = NH_CSS_VALUE_IN;
                }
                else if (Token_p->Dimension.Unit.p[0] == 'c' && Token_p->Dimension.Unit.p[1] == 'm') {
                    Value_p->Common.type = NH_CSS_VALUE_CM;
                }
                else if (Token_p->Dimension.Unit.p[0] == 'm' && Token_p->Dimension.Unit.p[1] == 'm') {
                    Value_p->Common.type = NH_CSS_VALUE_MM;
                }
                else if (Token_p->Dimension.Unit.p[0] == 'p' && Token_p->Dimension.Unit.p[1] == 't') {
                    Value_p->Common.type = NH_CSS_VALUE_PT;
                }
                else if (Token_p->Dimension.Unit.p[0] == 'p' && Token_p->Dimension.Unit.p[1] == 'c') {
                    Value_p->Common.type = NH_CSS_VALUE_PC;
                }
                else if (Token_p->Dimension.Unit.p[0] == 'p' && Token_p->Dimension.Unit.p[1] == 'x') {
                    Value_p->Common.type = NH_CSS_VALUE_PX;
                }
                else {
                    NH_CSS_DIAGNOSTIC_END(NH_CSS_ERROR_BAD_STATE)
                }

                Value_p->number = Token_p->Dimension.value;
            }
            break;

        case NH_CSS_TOKEN_BAD_STRING           :
        case NH_CSS_TOKEN_BAD_URL              :
        case NH_CSS_TOKEN_DELIM                :
        case NH_CSS_TOKEN_AT_KEYWORD           :
        case NH_CSS_TOKEN_WHITESPACE           : 
        case NH_CSS_TOKEN_CDO                  :
        case NH_CSS_TOKEN_CDC                  :
        case NH_CSS_TOKEN_COLON                : 
        case NH_CSS_TOKEN_SEMICOLON            :
        case NH_CSS_TOKEN_COMMA                :
        case NH_CSS_TOKEN_LEFT_SQUARE_BRACKET  :
        case NH_CSS_TOKEN_RIGHT_SQUARE_BRACKET : 
        case NH_CSS_TOKEN_LEFT_PARENTHESIS     :
        case NH_CSS_TOKEN_RIGHT_PARENTHESIS    :
        case NH_CSS_TOKEN_LEFT_CURLY_BRACKET   :
        case NH_CSS_TOKEN_RIGHT_CURLY_BRACKET  :
        case NH_CSS_TOKEN_EOF                  : 
            NH_CSS_DIAGNOSTIC_END(NH_CSS_ERROR_BAD_STATE)
    }

NH_CSS_DIAGNOSTIC_END(NH_CSS_SUCCESS)
}

static NH_CSS_RESULT nh_css_convertComponentValueToValue(
    nh_css_ComponentValue *ComponentValue_p, nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    switch (ComponentValue_p->type)
    {
        case NH_CSS_COMPONENT_VALUE_PRESERVED_TOKEN :
            NH_CSS_DIAGNOSTIC_END(nh_css_convertTokenToValue(ComponentValue_p->PreservedToken.Token_p, Value_p))

        case NH_CSS_COMPONENT_VALUE_FUNCTION :
        case NH_CSS_COMPONENT_VALUE_SIMPLE_BLOCK :
            exit(0); // TODO
            break; 
    }

NH_CSS_DIAGNOSTIC_END(NH_CSS_ERROR_BAD_STATE)
}

// SPECIFIED VALUES ================================================================================

static NH_CSS_RESULT nh_css_getValue(
    nh_Array *ComponentValues_p, nh_css_Value *Value_p, nh_css_DeclaredValue *Origin_p)
{
NH_CSS_BEGIN()

    for (int i = 0; i < ComponentValues_p->length; ++i) 
    {
        Value_p->Common.Origin_p = Origin_p;

        nh_css_ComponentValue *ComponentValue_p = &((nh_css_ComponentValue*)ComponentValues_p->p)[i];
        NH_CSS_CHECK_NULL(ComponentValue_p)

        if (nh_css_convertComponentValueToValue(ComponentValue_p, Value_p) != NH_CSS_SUCCESS) {
            NH_CSS_DIAGNOSTIC_END(NH_CSS_ERROR_BAD_STATE)
        }

        if (i + 1 < ComponentValues_p->length) {
            Value_p->Common.Next_p = nh_core_allocate(sizeof(nh_css_Value));
            NH_CSS_CHECK_MEM(Value_p->Common.Next_p)
            Value_p = Value_p->Common.Next_p;
        }
    }

NH_CSS_DIAGNOSTIC_END(NH_CSS_SUCCESS)
}

static NH_CSS_RESULT nh_css_getCascadedValue(
    nh_List *OrderedList_p, nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    nh_css_DeclaredValue *CascadedValue_p = OrderedList_p->pp[0];
    NH_CSS_CHECK_NULL(CascadedValue_p)
    NH_CSS_CHECK(nh_css_getValue(&CascadedValue_p->Declaration_p->ComponentValues, Value_p, CascadedValue_p))

NH_CSS_DIAGNOSTIC_END(NH_CSS_SUCCESS)
}

static NH_CSS_RESULT nh_css_getInitialValue(
    NH_CSS_PROPERTY property, nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    nh_css_ComponentValueData *Data_p = nh_css_getInitialComponentValueData(property);
    NH_CSS_CHECK_NULL(Data_p)
    NH_CSS_CHECK(nh_css_getValue(&Data_p->ComponentValues, Value_p, NULL))

NH_CSS_DIAGNOSTIC_END(NH_CSS_SUCCESS)
}

static NH_CSS_RESULT nh_css_getDefaultValue(
    nh_dom_Node *Node_p, NH_CSS_PROPERTY property, nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    nh_webidl_Object *Parent_p = nh_dom_getParentElement(Node_p);

    if (NH_CSS_PROPERTY_INHERITED_P[property] && Parent_p) {
        nh_List *ComputedValues_p = nh_dom_getComputedPropertyValues(nh_dom_getNode(Parent_p));
        *Value_p = *((nh_css_Value*)ComputedValues_p->pp[property]);
    }
    else {
        NH_CSS_CHECK(nh_css_getInitialValue(property, Value_p))
    }

NH_CSS_DIAGNOSTIC_END(NH_CSS_SUCCESS)
}

static NH_CSS_RESULT nh_css_getSpecifiedValue(
    nh_dom_Node *Node_p, NH_CSS_PROPERTY property, nh_css_Value *Value_p, nh_css_Filter *Filter_p)
{
NH_CSS_BEGIN()

    nh_List *OrderedList_p = Filter_p->DeclaredValueLists.pp[property];

    if (OrderedList_p && OrderedList_p->size > 0) {
        NH_CSS_CHECK(nh_css_getCascadedValue(OrderedList_p, Value_p))
    }
    else {
        NH_CSS_CHECK(nh_css_getDefaultValue(Node_p, property, Value_p))
    }

NH_CSS_DIAGNOSTIC_END(NH_CSS_SUCCESS)
}

NH_CSS_RESULT nh_css_setSpecifiedValues(
    nh_css_LogContext *LogContext_p, nh_dom_Element *Element_p, nh_css_StyleSheetListObject *AuthorStyleSheets_p, 
    nh_List UserStyleSheets)
{
NH_CSS_BEGIN()

    nh_dom_Node *Node_p = nh_dom_getNode((nh_webidl_Object*)Element_p);
    if (nh_dom_getSpecifiedPropertyValues(Node_p)->length > 0) {NH_CSS_DIAGNOSTIC_END(NH_CSS_ERROR_BAD_STATE)}

    nh_Array SpecifiedValues = nh_core_initArray(sizeof(nh_css_Value), NH_CSS_PROPERTY_COUNT);
    nh_css_Filter Filter = nh_css_filterDeclarations(Element_p, AuthorStyleSheets_p, UserStyleSheets);

    if (LogContext_p) {nh_css_logFilter(LogContext_p, &Filter);}

    for (int i = 0; i < NH_CSS_PROPERTY_COUNT; ++i) 
    {
        nh_css_Value Value = nh_css_initValue(NH_CSS_VALUE_SCOPE_SPECIFIED, NH_CSS_VALUE_UNDEFINED);
        if (nh_css_getSpecifiedValue(Node_p, i, &Value, &Filter) == NH_CSS_SUCCESS) {
            nh_css_Value *Value_p = nh_core_incrementArray(&SpecifiedValues);
            *Value_p = Value;
        }
        else {NH_CSS_DIAGNOSTIC_END(NH_CSS_ERROR_BAD_STATE)}
    }

    nh_dom_setSpecifiedPropertyValues(Node_p, SpecifiedValues);

    if (LogContext_p) {nh_css_logSpecifiedValues(LogContext_p, &SpecifiedValues);}

NH_CSS_DIAGNOSTIC_END(NH_CSS_SUCCESS)
}

NH_CSS_RESULT nh_css_freeSpecifiedValues(
    nh_dom_Node *Node_p)
{
NH_CSS_BEGIN()

    nh_Array *SpecifiedValues_p = nh_dom_getSpecifiedPropertyValues(Node_p);
    NH_CSS_CHECK_NULL(SpecifiedValues_p)

    for (int i = 0; i < SpecifiedValues_p->length; ++i)
    {
        nh_css_Value *Value_p = &((nh_css_Value*)SpecifiedValues_p->p)[i];
        if (nh_css_isStringValue(Value_p)) {
            nh_encoding_freeUTF8(&Value_p->String);
        }
    }

    nh_core_freeArray(SpecifiedValues_p);

NH_CSS_DIAGNOSTIC_END(NH_CSS_SUCCESS)
}
