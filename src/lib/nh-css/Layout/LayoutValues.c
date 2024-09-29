// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES ========================================================================================

#include "LayoutValues.h"

#include "../Main/FragmentTree.h"

#include "../Properties/Color.h"
#include "../Properties/Properties.h"
#include "../Properties/Values.h"

#include "../Common/Log.h"
#include "../Common/Macros.h"

#include "../../nh-gfx/Common/Macros.h"
#include "../../nh-dom/Interfaces/Node.h"
#include "../../nh-dom/Interfaces/Text.h"

#include "../../nh-core/Util/Array.h"

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

// HELPER ==========================================================================================

static NH_CSS_POSITION nh_css_getPositionType(
    nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    if (Value_p->Common.type != NH_CSS_VALUE_KEYWORD) {
        NH_CSS_END(NH_CSS_POSITION_STATIC)
    }

    if (!strcmp(Value_p->String.p, "static")) {
        NH_CSS_END(NH_CSS_POSITION_STATIC)
    }
    else if (!strcmp(Value_p->String.p, "relative")) {
        NH_CSS_END(NH_CSS_POSITION_RELATIVE)
    }
    else if (!strcmp(Value_p->String.p, "absolute")) {
        NH_CSS_END(NH_CSS_POSITION_ABSOLUTE)
    }
    else if (!strcmp(Value_p->String.p, "fixed")) {
        NH_CSS_END(NH_CSS_POSITION_FIXED)
    }

NH_CSS_END(NH_CSS_POSITION_STATIC)
}

static int nh_css_getLengthPercentage(
    nh_css_Fragment *Fragment_p, nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    if (Value_p->Common.type == NH_CSS_VALUE_FUNCTION) {
        // TODO
    }
    else if (Value_p->Common.type == NH_CSS_VALUE_PERCENTAGE) {
        // TODO
    }
    else if (Value_p->Common.type == NH_CSS_VALUE_PX) {
        NH_CSS_END((int)Value_p->number)
    }

NH_CSS_END(0)
}

static NH_CSS_LINE_STYLE nh_css_getLineStyle(
    nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    if (Value_p->Common.type != NH_CSS_VALUE_KEYWORD) {NH_CSS_END(NH_CSS_LINE_STYLE_NONE)}

         if (!strcmp(Value_p->String.p, "none"))   {NH_CSS_END(NH_CSS_LINE_STYLE_NONE)}
    else if (!strcmp(Value_p->String.p, "hidden")) {NH_CSS_END(NH_CSS_LINE_STYLE_HIDDEN)}
    else if (!strcmp(Value_p->String.p, "dotted")) {NH_CSS_END(NH_CSS_LINE_STYLE_DOTTED)}
    else if (!strcmp(Value_p->String.p, "dashed")) {NH_CSS_END(NH_CSS_LINE_STYLE_DASHED)}
    else if (!strcmp(Value_p->String.p, "solid"))  {NH_CSS_END(NH_CSS_LINE_STYLE_SOLID)}
    else if (!strcmp(Value_p->String.p, "double")) {NH_CSS_END(NH_CSS_LINE_STYLE_DOUBLE)}
    else if (!strcmp(Value_p->String.p, "groove")) {NH_CSS_END(NH_CSS_LINE_STYLE_GROOVE)}
    else if (!strcmp(Value_p->String.p, "ridge"))  {NH_CSS_END(NH_CSS_LINE_STYLE_RIDGE)}
    else if (!strcmp(Value_p->String.p, "inset"))  {NH_CSS_END(NH_CSS_LINE_STYLE_INSET)}
    else if (!strcmp(Value_p->String.p, "outset")) {NH_CSS_END(NH_CSS_LINE_STYLE_OUTSET)}

NH_CSS_END(NH_CSS_LINE_STYLE_NONE)
}

// FONT ============================================================================================

static int nh_css_getGenericFontFamily(
    nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    if (!strcmp(Value_p->String.p, "serif")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_SERIF)
    }
    else if (!strcmp(Value_p->String.p, "sans-serif")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_SANS_SERIF)
    }
    else if (!strcmp(Value_p->String.p, "cursive")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_CURSIVE)
    }
    else if (!strcmp(Value_p->String.p, "fantasy")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_FANTASY)
    }
    else if (!strcmp(Value_p->String.p, "monospace")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_MONOSPACE)
    }
    else if (!strcmp(Value_p->String.p, "system-ui")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_SYSTEM_UI)
    }
    else if (!strcmp(Value_p->String.p, "emoji")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_EMOJI)
    }
    else if (!strcmp(Value_p->String.p, "math")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_MATH)
    }
    else if (!strcmp(Value_p->String.p, "fangsong")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_FANGSONG)
    }
    else if (!strcmp(Value_p->String.p, "ui-serif")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_UI_SERIF)
    }
    else if (!strcmp(Value_p->String.p, "ui-sans-serif")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_UI_SANS_SERIF)
    }
    else if (!strcmp(Value_p->String.p, "ui-monospace")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_UI_MONOSPACE)
    }
    else if (!strcmp(Value_p->String.p, "ui-rounded")) {
        NH_CSS_END(NH_GFX_GENERIC_FONT_FAMILY_UI_ROUNDED)
    }

NH_CSS_END(-1)
}

static NH_API_RESULT nh_css_getFontFamilies(
    nh_css_Value *Value_p, nh_Array *Families_p)
{
NH_CSS_BEGIN()

    *Families_p = nh_core_initArray(sizeof(nh_gfx_FontFamily), 4);

    while (Value_p) 
    {
        nh_gfx_FontFamily *Family_p = nh_core_incrementArray(Families_p);
        NH_CSS_CHECK_MEM(Family_p)

        *Family_p = nh_gfx_initFontFamily(NULL);
        int generic = nh_css_getGenericFontFamily(Value_p);

        if (generic >= 0) {Family_p->generic_p[generic] = true;}
        else {Family_p->name_p = Value_p->String.p;}

        Value_p = Value_p->Common.Next_p;
    }

NH_CSS_END(NH_API_SUCCESS)
}

static nh_gfx_FontStyle nh_css_getFontStyle(
    nh_css_Value *Weight_p, nh_css_Value *Style_p)
{
NH_CSS_BEGIN()

    nh_gfx_FontStyle Style;

    Style.weight = Weight_p->number;
    Style.oblique = strstr(Style_p->String.p, "oblique") ? true : false;
    Style.italic = strstr(Style_p->String.p, "italic") ? true : false;

NH_CSS_END(Style)
}

static nh_css_BoxSizing nh_css_getBoxSizing(
    nh_css_Fragment *Fragment_p, nh_List *ComputedValues_p, NH_CSS_PROPERTY property)
{
NH_CSS_BEGIN()

    nh_css_Value *Value_p = ComputedValues_p->pp[property];

    nh_css_BoxSizing Sizing;
    Sizing.type = NH_CSS_BOX_SIZING_NONE;
    Sizing.value = 0;
    Sizing.percentage = 0.0f;

    if (Value_p->Common.type == NH_CSS_VALUE_KEYWORD) {
        if (property == NH_CSS_PROPERTY_MAX_WIDTH || property == NH_CSS_PROPERTY_MAX_HEIGHT) {
            if (!strcmp(Value_p->String.p, "none")) {
                Sizing.type = NH_CSS_BOX_SIZING_NONE; 
            }
        } 
        else if (!strcmp(Value_p->String.p, "auto")) {
            Sizing.type = NH_CSS_BOX_SIZING_AUTO; 
        }
        if (!strcmp(Value_p->String.p, "min-content")) {
            Sizing.type = NH_CSS_BOX_SIZING_MIN_CONTENT;
        }
        else if (!strcmp(Value_p->String.p, "max-content")) {
            Sizing.type = NH_CSS_BOX_SIZING_MAX_CONTENT;
        }
    }
    else if (Value_p->Common.type == NH_CSS_VALUE_PERCENTAGE) {
        Sizing.type = NH_CSS_BOX_SIZING_PERCENTAGE;
        Sizing.percentage = Value_p->number;
    }
    else if (nh_css_isLengthValue(Value_p)) {
        Sizing.type = NH_CSS_BOX_SIZING_LENGTH;
        Sizing.value = (int)Value_p->number;
    }

NH_CSS_END(Sizing)
}

// TEXT ALIGN ======================================================================================

static int nh_css_getTextAlign(
    nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    if (!Value_p) {}
    else if (!strcmp(Value_p->String.p, "start")) {
        NH_CSS_END(NH_CSS_TEXT_ALIGN_START)
    }
    else if (!strcmp(Value_p->String.p, "auto")) {
        NH_CSS_END(NH_CSS_TEXT_ALIGN_AUTO)
    }
    else if (!strcmp(Value_p->String.p, "end")) {
        NH_CSS_END(NH_CSS_TEXT_ALIGN_END)
    }
    else if (!strcmp(Value_p->String.p, "left")) {
        NH_CSS_END(NH_CSS_TEXT_ALIGN_LEFT)
    }
    else if (!strcmp(Value_p->String.p, "right")) {
        NH_CSS_END(NH_CSS_TEXT_ALIGN_RIGHT)
    }
    else if (!strcmp(Value_p->String.p, "center")) {
        NH_CSS_END(NH_CSS_TEXT_ALIGN_CENTER)
    }
    else if (!strcmp(Value_p->String.p, "justify")) {
        NH_CSS_END(NH_CSS_TEXT_ALIGN_JUSTIFY)
    }
    else if (!strcmp(Value_p->String.p, "match-parent")) {
        NH_CSS_END(NH_CSS_TEXT_ALIGN_MATCH_PARENT)
    }

NH_CSS_END(NH_CSS_TEXT_ALIGN_START)
}

// FLOAT ===========================================================================================

static int nh_css_getFloat(
    nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    if (!strcmp(Value_p->String.p, "none")) {
        NH_CSS_END(NH_CSS_FLOAT_NONE)
    }
    else if (!strcmp(Value_p->String.p, "left")) {
        NH_CSS_END(NH_CSS_FLOAT_LEFT)
    }
    else if (!strcmp(Value_p->String.p, "right")) {
        NH_CSS_END(NH_CSS_FLOAT_RIGHT)
    }

NH_CSS_END(NH_CSS_FLOAT_NONE)
}

// WORD BREAK ======================================================================================

static int nh_css_getWordBreak(
    nh_css_Value *Value_p)
{
NH_CSS_BEGIN()

    if (!strcmp(Value_p->String.p, "normal")) {
        NH_CSS_END(NH_CSS_WORD_BREAK_NORMAL)
    }
    else if (!strcmp(Value_p->String.p, "keep-all")) {
        NH_CSS_END(NH_CSS_WORD_BREAK_KEEP_ALL)
    }
    else if (!strcmp(Value_p->String.p, "break-all")) {
        NH_CSS_END(NH_CSS_WORD_BREAK_BREAK_ALL)
    }
    else if (!strcmp(Value_p->String.p, "break-word")) {
        NH_CSS_END(NH_CSS_WORD_BREAK_BREAK_WORD)
    }

NH_CSS_END(NH_CSS_WORD_BREAK_NORMAL)
}

// TEXT VALUES =====================================================================================

NH_API_RESULT nh_css_computeTextValues(
    nh_css_Fragment *Fragment_p)
{
NH_CSS_BEGIN()

    nh_css_Fragment *Parent_p = Fragment_p->Parent_p;
    while (!Parent_p->Node_p->Source_p) {Parent_p = Parent_p->Parent_p;}

    nh_List *ComputedValues_p = Parent_p->Node_p->Source_p->ComputedValues_p;

    Fragment_p->Text.Values.Color = nh_css_getColor(*((nh_css_Value*)ComputedValues_p->pp[NH_CSS_PROPERTY_COLOR]));
    Fragment_p->Text.Values.fontSize = 
        nh_css_getLengthPercentage(Fragment_p->Parent_p, ComputedValues_p->pp[NH_CSS_PROPERTY_FONT_SIZE]);

    NH_CSS_CHECK(nh_css_getFontFamilies(ComputedValues_p->pp[NH_CSS_PROPERTY_FONT_FAMILY], &Fragment_p->Text.Values.FontFamilies))
    Fragment_p->Text.Values.FontStyle = nh_css_getFontStyle(
        ComputedValues_p->pp[NH_CSS_PROPERTY_FONT_WEIGHT], ComputedValues_p->pp[NH_CSS_PROPERTY_FONT_STYLE]
    );

    NH_GFX_CHECK_2(NH_API_ERROR_BAD_STATE, nh_gfx_createText(
        &Fragment_p->Text.Values.Text, Fragment_p->Text.text_p, Fragment_p->Text.length, Fragment_p->Text.Values.fontSize, 
        &Fragment_p->Text.Values.FontFamilies, Fragment_p->Text.Values.FontStyle
    ))

    Fragment_p->Text.Values.textWidth  = nh_gfx_getTextWidth(&Fragment_p->Text.Values.Text);
    Fragment_p->Text.Values.textHeight = nh_gfx_getTextHeight(&Fragment_p->Text.Values.Text);

    Fragment_p->Text.Values.wordBreak = nh_css_getWordBreak(ComputedValues_p->pp[NH_CSS_PROPERTY_WORD_BREAK]);

NH_CSS_DIAGNOSTIC_END(NH_API_SUCCESS)
}

void nh_css_freeTextValues(
    nh_css_Fragment *Fragment_p)
{
NH_CSS_BEGIN()

    nh_gfx_freeText(&Fragment_p->Text.Values.Text);
    nh_core_freeArray(&Fragment_p->Text.Values.FontFamilies);

NH_CSS_SILENT_END()
}

// BOX VALUES ======================================================================================

static NH_API_RESULT nh_css_computeAnonymousBoxValues(
    nh_css_Fragment *Fragment_p)
{
NH_CSS_BEGIN()

    nh_css_Fragment *Ancestor_p = Fragment_p;
    while (!Ancestor_p->Node_p->Source_p) {
        Ancestor_p = Ancestor_p->Parent_p;
    }

    nh_List *ComputedValues_p = Ancestor_p->Node_p->Source_p->ComputedValues_p;
    nh_css_BoxValues *Values_p = &Fragment_p->Box.Values;

    Values_p->_float = NH_CSS_FLOAT_NONE; 
    Values_p->BackgroundColor = nh_css_getColor(*((nh_css_Value*)ComputedValues_p->pp[NH_CSS_PROPERTY_BACKGROUND_COLOR]));

    Values_p->marginTop     = 0;
    Values_p->marginRight   = 0;
    Values_p->marginBottom  = 0;
    Values_p->marginLeft    = 0;
    Values_p->paddingTop    = 0;
    Values_p->paddingRight  = 0;
    Values_p->paddingBottom = 0;
    Values_p->paddingLeft   = 0;
    Values_p->borderTop     = 0;
    Values_p->borderRight   = 0;
    Values_p->borderBottom  = 0;
    Values_p->borderLeft    = 0;

    Values_p->borderTopStyle    = NH_CSS_LINE_STYLE_NONE;
    Values_p->borderRightStyle  = NH_CSS_LINE_STYLE_NONE;
    Values_p->borderBottomStyle = NH_CSS_LINE_STYLE_NONE;
    Values_p->borderLeftStyle   = NH_CSS_LINE_STYLE_NONE;

    Values_p->textAlignAll  = nh_css_getTextAlign(ComputedValues_p->pp[NH_CSS_PROPERTY_TEXT_ALIGN_ALL]);
    Values_p->textAlignLast = nh_css_getTextAlign(ComputedValues_p->pp[NH_CSS_PROPERTY_TEXT_ALIGN_LAST]);

NH_CSS_END(NH_API_SUCCESS)
}

NH_API_RESULT nh_css_computeBoxValues(
    nh_css_Fragment *Fragment_p)
{
NH_CSS_BEGIN()

    if (!Fragment_p->Node_p->Source_p) {
        NH_CSS_END(nh_css_computeAnonymousBoxValues(Fragment_p))
    }

    nh_List *ComputedValues_p = Fragment_p->Node_p->Source_p->ComputedValues_p;
    nh_css_BoxValues *Values_p = &Fragment_p->Box.Values;

    Values_p->position = nh_css_getPositionType(ComputedValues_p->pp[NH_CSS_PROPERTY_POSITION]);
    Values_p->_float   = nh_css_getFloat(ComputedValues_p->pp[NH_CSS_PROPERTY_FLOAT]);

    Values_p->BackgroundColor = nh_css_getColor(*((nh_css_Value*)ComputedValues_p->pp[NH_CSS_PROPERTY_BACKGROUND_COLOR]));

    Values_p->Width     = nh_css_getBoxSizing(Fragment_p, ComputedValues_p, NH_CSS_PROPERTY_WIDTH);
    Values_p->Height    = nh_css_getBoxSizing(Fragment_p, ComputedValues_p, NH_CSS_PROPERTY_HEIGHT);
    Values_p->MinWidth  = nh_css_getBoxSizing(Fragment_p, ComputedValues_p, NH_CSS_PROPERTY_MIN_WIDTH);
    Values_p->MinHeight = nh_css_getBoxSizing(Fragment_p, ComputedValues_p, NH_CSS_PROPERTY_MIN_HEIGHT);
    Values_p->MaxWidth  = nh_css_getBoxSizing(Fragment_p, ComputedValues_p, NH_CSS_PROPERTY_MAX_WIDTH);
    Values_p->MaxHeight = nh_css_getBoxSizing(Fragment_p, ComputedValues_p, NH_CSS_PROPERTY_MAX_HEIGHT);

    Values_p->marginTop     = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_MARGIN_TOP]);
    Values_p->marginLeft    = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_MARGIN_LEFT]);
    Values_p->marginBottom  = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_MARGIN_BOTTOM]);
    Values_p->marginRight   = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_MARGIN_RIGHT]);
    Values_p->paddingTop    = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_PADDING_TOP]);
    Values_p->paddingLeft   = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_PADDING_LEFT]);
    Values_p->paddingBottom = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_PADDING_BOTTOM]);
    Values_p->paddingRight  = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_PADDING_RIGHT]);
    Values_p->borderTop     = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_TOP_WIDTH]);
    Values_p->borderLeft    = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_LEFT_WIDTH]);
    Values_p->borderBottom  = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_BOTTOM_WIDTH]);
    Values_p->borderRight   = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_RIGHT_WIDTH]);

    Values_p->BorderTopColor    = nh_css_getColor(*((nh_css_Value*)ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_TOP_COLOR]));
    Values_p->BorderRightColor  = nh_css_getColor(*((nh_css_Value*)ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_RIGHT_COLOR]));
    Values_p->BorderBottomColor = nh_css_getColor(*((nh_css_Value*)ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_BOTTOM_COLOR]));
    Values_p->BorderLeftColor   = nh_css_getColor(*((nh_css_Value*)ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_LEFT_COLOR]));

    Values_p->borderTopLeftRadius     = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_TOP_LEFT_RADIUS]);
    Values_p->borderTopRightRadius    = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_TOP_RIGHT_RADIUS]);
    Values_p->borderBottomLeftRadius  = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_BOTTOM_LEFT_RADIUS]);
    Values_p->borderBottomRightRadius = nh_css_getLengthPercentage(Fragment_p, ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_BOTTOM_RIGHT_RADIUS]);

    Values_p->borderTopStyle    = nh_css_getLineStyle(ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_TOP_STYLE]);
    Values_p->borderRightStyle  = nh_css_getLineStyle(ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_RIGHT_STYLE]);
    Values_p->borderBottomStyle = nh_css_getLineStyle(ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_BOTTOM_STYLE]);
    Values_p->borderLeftStyle   = nh_css_getLineStyle(ComputedValues_p->pp[NH_CSS_PROPERTY_BORDER_LEFT_STYLE]);

    Values_p->textAlignAll  = nh_css_getTextAlign(ComputedValues_p->pp[NH_CSS_PROPERTY_TEXT_ALIGN_ALL]);
    Values_p->textAlignLast = nh_css_getTextAlign(ComputedValues_p->pp[NH_CSS_PROPERTY_TEXT_ALIGN_LAST]);

NH_CSS_DIAGNOSTIC_END(NH_API_SUCCESS)
}

