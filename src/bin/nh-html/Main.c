/**
 * Netzhaut - Web Browser 
 * Copyright (C) 2022  Dajo Frey
 * This file is published under MIT.
 */

#include "nh-api/nh-api.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/** 
 * Routine of opening a webpage using cli. 
 */
int main(
    int argc, char **argv_pp) 
{
    if (argc < 2 || argc > 3) {
        puts("Invalid argument count. Exiting.");
        return 1;
    }

    if (nh_api_initialize(NULL, argc > 2 ? argv_pp[2] : NULL, argc > 2 ? strlen(argv_pp[2]) : 0) != NH_API_SUCCESS) {
        puts("API initialization failed. Exiting.\n");
        return 1;
    }

    long size;
    void *document_p = nh_api_getFileData(argv_pp[1], &size);

    if (!document_p || !size) {
        puts("Getting file data failed. Exiting.");
        return 1;
    }

    nh_api_Window *Window_p = nh_api_createWindow(NULL, nh_api_getSurfaceRequirements());
    if (!Window_p) {
        puts("Creating window failed. Exiting.");
        return 1;
    }

    nh_api_Surface *Surface_p = nh_api_createSurface(Window_p, NH_API_GRAPHICS_BACKEND_VULKAN);
    if (!Surface_p) {
        puts("Creating surface failed. Exiting.");
        return 1;
    }

    nh_api_PixelSize Size;
    Size.width = 700;
    Size.height = 700;

    nh_api_PixelPosition Position;
    Position.x = 0;
    Position.y = 0;

    nh_api_Viewport *Viewport_p = nh_api_createViewport(Surface_p, Position, Size);
    if (!Viewport_p) {
        puts("Creating viewport failed. Exiting.");
        return 1;
    }

    nh_api_DocumentContext *DocumentContext_p = nh_api_createDocumentContext(false);
    if (!DocumentContext_p) {
        puts("Creating document context failed. Exiting.");
        return 1;
    }

    nh_api_LayoutEngine *LayoutEngine_p = nh_api_createLayoutEngine(DocumentContext_p);
    if (!LayoutEngine_p) {
        puts("Creating layout engine failed. Exiting.");
        return 1;
    }

    nh_api_Renderer *Renderer_p = nh_api_createRenderer(LayoutEngine_p);
    if (!Renderer_p) {
        puts("Creating renderer failed. Exiting.");
        return 1;
    }

    if (nh_api_addViewport(Renderer_p, Viewport_p)) {
        puts("Adding viewport to renderer failed. Exiting.");
        return 1;
    }
    if (nh_api_loadBytes(DocumentContext_p, document_p, size)) {
        puts("Loading bytes into document failed. Exiting.");
        return 1;
    }

    while (1) {
        int result = nh_api_run();
        if (result == -1) {
            puts("Encountered workload error. Exiting.");
            break;
        } else if (result == 0) {
            // idle
            usleep(10000);
        }
        if (!nh_api_keepRunning()) {break;}
    }

    nh_api_terminate();
}
