// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2020  Dajo Frey
 * Published under LGPLv3
 */

// INCLUDE ========================================================================================

#include "../Header/Document.h"
#include "../Header/HTMLElement.h"
#include "../Header/HTMLCanvasElement.h"
#include "../Header/HTMLCollection.h"
#include "../Header/Macros.h"

#include "../../Header/Variable.h"

#include "../../../Core/Header/Tab.h"
#include "../../../Core/Header/Memory.h"

#include "../../../CSS/Header/Associate.h"

#include <string.h>
#include <ctype.h>

#include NH_UTILS
#include NH_CUSTOM_CHECK
#include NH_JS_DEBUG_FUNCTION

// DECLARE =========================================================================================

static NH_RESULT Nh_JS_createDocumentElement(
    Nh_JS_Script *Script_p, Nh_JS_Object **Object_pp, Nh_HTML_Node *Node_p, Nh_JS_Object *Parent_p
);
static void Nh_JS_destroyDocumentData(
    Nh_JS_Document *Document_p
);
static NH_RESULT Nh_JS_createFlatTree(
    Nh_JS_Document *Document_p, Nh_JS_Object *Object_p
);

// API =============================================================================================

Nh_JS_Result Nh_JS_Document_Document(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_activeElement(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_adoptNode(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_anchors(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_applets(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_baseURI(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_body(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_close(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_cookie(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_charset(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_characterSet(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_createAttribute(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_createComment(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_createDocumentFragment(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_createElement(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_createEvent(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_createTextNode(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_defaultView(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_designMode(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_doctype(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_documentElement(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

    if (aCount == 0) // get
    {
        Nh_JS_Document *Document_p = Function_p->Inherit_p->data_p;
        NH_END(Nh_JS_getResult(NH_JS_TYPE_OBJECT, false, Document_p->Tree.Root_p))
    }

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_documentMode(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_documentURI(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_domain(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_domConfig(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_embeds(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_execCommand(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_forms(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_fullscreenElement(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_fullscreenEnabled(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_getElementById(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

    if (aCount == 1 && Arguments_p[0].type == NH_JS_TYPE_STRING)
    {
        Nh_JS_Document *Document_p = Function_p->Inherit_p->data_p;

        for (int i = 0; i < Document_p->Tree.Flat.count; ++i) 
        {
            Nh_JS_Object *Object_p = Nh_getListItem(&Document_p->Tree.Flat, i);
            if (Nh_JS_getObject(Object_p, NH_JS_OBJECT_HTML_ELEMENT) != NULL) 
            {
                Nh_JS_HTMLElement *Element_p = Nh_JS_getObject(Object_p, NH_JS_OBJECT_HTML_ELEMENT)->data_p;
                if (Element_p->Node_p->Computed.Attributes.id_p != NULL 
                && !strcmp(Element_p->Node_p->Computed.Attributes.id_p, Arguments_p[0].data_p)) {
                    NH_END(Nh_JS_getResult(NH_JS_TYPE_OBJECT, false, Object_p)) 
                }
            }
        }
    }

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_getElementsByClassName(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_getElementsByName(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_getElementsByTagName(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

    if (aCount == 1 && Arguments_p[0].type == NH_JS_TYPE_STRING)
    {
        Nh_JS_Document *Document_p = Function_p->Inherit_p->data_p;

        char *str_p = Nh_allocate(sizeof(char) * (strlen(Arguments_p[0].data_p) + 1));
        NH_CHECK_NULL(Nh_JS_getNULLResult(), str_p)

        for (int i = 0; i < strlen(Arguments_p[0].data_p); ++i) {
            str_p[i] = tolower(((char*)Arguments_p[0].data_p)[i]);
        }
        str_p[strlen(Arguments_p[0].data_p)] = '\0';

        Nh_List Elements;
        NH_INIT_LIST(Elements)

        for (int i = 0; i < Document_p->Tree.Flat.count; ++i) 
        {
            Nh_JS_Object *Object_p = Nh_getListItem(&Document_p->Tree.Flat, i);
            if (Object_p->type == NH_JS_OBJECT_HTML_ELEMENT) {
                Nh_HTML_Node *Node_p = ((Nh_JS_HTMLElement*)Object_p->data_p)->Node_p;
                if (Node_p != NULL && !strcmp(NH_HTML_TAGS_PP[Node_p->tag], str_p)) {
                    NH_CHECK(Nh_JS_getNULLResult(), Nh_addListItem(&Elements, Object_p))
                }
            }
        }

        Nh_JS_Object *Element_p;
        NH_CHECK(Nh_JS_getNULLResult(), Nh_JS_createHTMLCollectionObject(
            Script_p, &Element_p, Elements, str_p, Function_p->Inherit_p
        )) 

        NH_END(Nh_JS_getResult(NH_JS_TYPE_OBJECT, true, Element_p))
    }

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_hasFocus(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_head(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_images(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_implementation(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_importNode(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_inputEncoding(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_lastModified(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_links(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_normalize(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_normalizeDocument(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_open(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_querySelector(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_querySelectorAll(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_readyState(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_referrer(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_removeEventListener(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_renameNode(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_scripts(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_strictErrorChecking(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_title(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_url(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_write(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

Nh_JS_Result Nh_JS_Document_writeln(
    Nh_JS_Script *Script_p, Nh_JS_Object *Function_p, int aCount, Nh_JS_Result *Arguments_p)
{
NH_BEGIN()

NH_END(Nh_JS_getNULLResult())
}

// INTERNAL ========================================================================================

#include NH_DEFAULT_CHECK
#include NH_JS_DEBUG

NH_RESULT Nh_JS_createDocumentObject(
    Nh_JS_Script *Script_p, Nh_JS_Object **Object_pp)
{
NH_BEGIN()

    NH_CHECK(Nh_JS_createObject(Script_p, NH_JS_OBJECT_DOCUMENT, Object_pp))

    (*Object_pp)->data_p = Nh_allocate(sizeof(Nh_JS_Document));
    NH_CHECK_MEM((*Object_pp)->data_p)

    Nh_JS_Document *Document_p = (*Object_pp)->data_p;
    NH_INIT_LIST(Document_p->Tree.Flat)

    NH_CHECK(Nh_JS_createDocumentElement(
        Script_p, &Document_p->Tree.Root_p, Script_p->Run.Tab_p->Document.Tree.Root_p, NULL
    ))
    NH_CHECK(Nh_JS_createFlatTree(Document_p, Document_p->Tree.Root_p))

NH_END(NH_SUCCESS)
}

void Nh_JS_destroyDocumentObject(
    Nh_JS_Object *Object_p)
{
NH_BEGIN()

    Nh_JS_destroyDocumentData(Object_p->data_p);
    Nh_free(Object_p->data_p);
    Nh_JS_destroyObject(Object_p);

NH_SILENT_END()
}

NH_RESULT Nh_JS_updateDocumentObject(
    Nh_JS_Script *Script_p)
{
NH_BEGIN()

    Nh_JS_Document *Document_p = Script_p->DOM.Objects.Document_p->data_p;
    Nh_JS_destroyDocumentData(Document_p);

    NH_CHECK(Nh_JS_createDocumentElement(
        Script_p, &Document_p->Tree.Root_p, Script_p->Run.Tab_p->Document.Tree.Root_p, NULL
    ))
    NH_CHECK(Nh_JS_createFlatTree(Document_p, Document_p->Tree.Root_p))

    for (int i = 0; i < Script_p->Run.Tab_p->Document.Scripts.count; ++i) {
        NH_CHECK(Nh_JS_updateScriptVariables(Nh_getListItem(&Script_p->Run.Tab_p->Document.Scripts, i)))
    }

NH_END(NH_SUCCESS)
}

static NH_RESULT Nh_JS_createDocumentElement(
    Nh_JS_Script *Script_p, Nh_JS_Object **Object_pp, Nh_HTML_Node *Node_p, Nh_JS_Object *Parent_p)
{
NH_BEGIN()

    switch (Node_p->tag)
    {
        case NH_HTML_TAG_CANVAS :
            NH_CHECK(Nh_JS_createHTMLCanvasElementObject(Script_p, Object_pp, Node_p, Parent_p)) break;

        default :
            NH_CHECK(Nh_JS_createHTMLElementObject(Script_p, Object_pp, Node_p, Parent_p))
    }

    for (int i = 0; i < Node_p->Children.Unformatted.count; ++i) 
    {
        Nh_JS_Object *Child_p;
        NH_CHECK(Nh_JS_createDocumentElement(Script_p, &Child_p, Nh_getListItem(&Node_p->Children.Unformatted, i), *Object_pp))
    }

NH_END(NH_SUCCESS)
}

static void Nh_JS_destroyDocumentData(
    Nh_JS_Document *Document_p)
{
NH_BEGIN()

    Nh_JS_destroyHTMLElementObject(Document_p->Tree.Root_p);
    Nh_destroyList(&Document_p->Tree.Flat, false);

NH_SILENT_END()
}

static NH_RESULT Nh_JS_createFlatTree(
    Nh_JS_Document *Document_p, Nh_JS_Object *Object_p)
{
NH_BEGIN()

    NH_CHECK(Nh_addListItem(&Document_p->Tree.Flat, Object_p))

    for (int i = 0; i < ((Nh_JS_HTMLElement*)Object_p->data_p)->Children.count; ++i) {
        NH_CHECK(Nh_JS_createFlatTree(Document_p, Nh_getListItem(&((Nh_JS_HTMLElement*)Object_p->data_p)->Children, i)))
    }

NH_END(NH_SUCCESS)
}

