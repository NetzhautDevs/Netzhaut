// LICENSE NOTICE ==================================================================================

/**
 * Netzhaut - Web Browser Engine
 * Copyright (C) 2022  Dajo Frey
 * Published under GNU LGPL. See Netzhaut/LICENSE.LGPL file.
 */

// INCLUDES =======================================================================================

#include "Helper.h"
#include "Vulkan.h"

#include "../Common/Macros.h"

#include <string.h>

// BUFFER ==========================================================================================

NH_API_RESULT nh_vk_createBuffer(
    nh_vk_Driver *Driver_p, nh_vk_BufferInfo *BufferInfo_p, nh_vk_Buffer *Buffer_p)
{
NH_GFX_BEGIN()

    NH_GFX_CHECK_VULKAN(Driver_p->Functions.vkCreateBuffer(Driver_p->Device, BufferInfo_p->Info_p, VK_NULL_HANDLE, &Buffer_p->Buffer))

    nh_vk_DeviceMemoryInfo Info = 
    {
        .deviceMemoryType = NH_VK_DEVICE_MEMORY_BUFFER,
        .memoryProperties = BufferInfo_p->memoryProperties,  
        .bindSource_p     = &Buffer_p->Buffer
    };

    NH_GFX_CHECK(nh_vk_createDeviceMemory(Driver_p, &Info, &Buffer_p->DeviceMemory))

    if (BufferInfo_p->mapMemory) { 
        nh_vk_mapDeviceMemory(
            Driver_p, &Buffer_p->DeviceMemory, BufferInfo_p->data_p, 
            (size_t) BufferInfo_p->Info_p->size, 0
        );
    }
    
    nh_vk_bindDeviceMemory(Driver_p, &Buffer_p->DeviceMemory, &Info);

    if (BufferInfo_p->createInfo) { 
        Buffer_p->DescriptorBufferInfo.buffer = Buffer_p->Buffer;
        Buffer_p->DescriptorBufferInfo.offset = 0;
        Buffer_p->DescriptorBufferInfo.range  = VK_WHOLE_SIZE;
    }

NH_GFX_DIAGNOSTIC_END(NH_API_SUCCESS)
}

NH_API_RESULT nh_vk_destroyBuffer(
    nh_vk_Driver *Driver_p, nh_vk_Buffer *Buffer_p)
{
NH_GFX_BEGIN();

    Driver_p->Functions.vkDestroyBuffer(Driver_p->Device, Buffer_p->Buffer, VK_NULL_HANDLE);
    Driver_p->Functions.vkFreeMemory(Driver_p->Device, Buffer_p->DeviceMemory, VK_NULL_HANDLE); 

NH_GFX_DIAGNOSTIC_END(NH_API_SUCCESS);
}

// DESCRIPTOR SET ==================================================================================

NH_API_RESULT nh_vk_createDescriptorSet(
    nh_vk_Driver *Driver_p, VkDescriptorSetAllocateInfo *DescriptorSetAllocateInfo_p, VkDescriptorSetLayoutCreateInfo *DescriptorSetLayoutInfo_p, 
    nh_vk_DescriptorSet *DescriptorSet_p)
{
NH_GFX_BEGIN()

    NH_GFX_CHECK_VULKAN(Driver_p->Functions.vkCreateDescriptorSetLayout(Driver_p->Device, DescriptorSetLayoutInfo_p, VK_NULL_HANDLE, &DescriptorSet_p->Layout))

    DescriptorSetAllocateInfo_p->pSetLayouts = &DescriptorSet_p->Layout;
    DescriptorSetAllocateInfo_p->descriptorSetCount = 1;

    NH_GFX_CHECK_VULKAN(Driver_p->Functions.vkAllocateDescriptorSets(Driver_p->Device, DescriptorSetAllocateInfo_p, &DescriptorSet_p->DescriptorSet))

NH_GFX_DIAGNOSTIC_END(NH_API_SUCCESS)
}

NH_API_RESULT nh_vk_destroyDescriptorSet(
    nh_vk_Driver *Driver_p, nh_vk_DescriptorSet *DescriptorSet_p, VkDescriptorPool *DescriptorPool_p)
{
NH_GFX_BEGIN()

    Driver_p->Functions.vkDestroyDescriptorSetLayout(
        Driver_p->Device, DescriptorSet_p->Layout, VK_NULL_HANDLE
    );
    Driver_p->Functions.vkFreeDescriptorSets(
        Driver_p->Device, *DescriptorPool_p, 1, &DescriptorSet_p->DescriptorSet
    );

NH_GFX_DIAGNOSTIC_END(NH_API_SUCCESS)
}

// MEMORY ==========================================================================================

NH_API_RESULT nh_vk_createDeviceMemory(
    nh_vk_Driver *Driver_p, nh_vk_DeviceMemoryInfo *Info_p, VkDeviceMemory *DeviceMemory_p)
{
NH_GFX_BEGIN()

    VkMemoryRequirements memoryRequirements;
    if (Info_p->deviceMemoryType == NH_VK_DEVICE_MEMORY_IMAGE)
    {
        VkImage *VkImage_p = (VkImage*) Info_p->bindSource_p;
        Driver_p->Functions.vkGetImageMemoryRequirements(
            Driver_p->Device, 
            *VkImage_p, 
            &memoryRequirements
        );
    }
    else if (Info_p->deviceMemoryType == NH_VK_DEVICE_MEMORY_BUFFER)
    {
        VkBuffer *VkBuffer_p = (VkBuffer*) Info_p->bindSource_p;
        Driver_p->Functions.vkGetBufferMemoryRequirements(
            Driver_p->Device, 
            *VkBuffer_p, 
            &memoryRequirements
         );
    }
    else {NH_GFX_DIAGNOSTIC_END(NH_API_ERROR_BAD_STATE)}
    
    int i;
    nh_vk_findMemoryType(Driver_p, memoryRequirements.memoryTypeBits, Info_p->memoryProperties, &i);
    
    VkMemoryAllocateInfo memoryInfo = 
    { 
        .sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO,
        .pNext           = VK_NULL_HANDLE,
        .allocationSize  = memoryRequirements.size,
        .memoryTypeIndex = i
    };
   
#define CREATION_FAILED Driver_p->Functions.vkAllocateMemory(Driver_p->Device, &memoryInfo, VK_NULL_HANDLE, DeviceMemory_p) != VK_SUCCESS 
    if (CREATION_FAILED) {
        NH_GFX_DIAGNOSTIC_END(NH_API_ERROR_BAD_STATE)
    }

NH_GFX_DIAGNOSTIC_END(NH_API_SUCCESS);
}

NH_API_RESULT nh_vk_bindDeviceMemory(
    nh_vk_Driver *Driver_p, VkDeviceMemory *DeviceMemory_p, nh_vk_DeviceMemoryInfo *Info_p)
{
NH_GFX_BEGIN()

    NH_GFX_CHECK_NULL(Info_p->bindSource_p) 

    if (Info_p->deviceMemoryType == NH_VK_DEVICE_MEMORY_IMAGE)
    { 
        VkImage *VkImage_p = (VkImage*) Info_p->bindSource_p;
        Driver_p->Functions.vkBindImageMemory(
            Driver_p->Device, 
            *VkImage_p, 
            *DeviceMemory_p, 
            0
        ); 
    }    
    else if (Info_p->deviceMemoryType == NH_VK_DEVICE_MEMORY_BUFFER)
    {
        VkBuffer *VkBuffer_p = (VkBuffer*) Info_p->bindSource_p;
        Driver_p->Functions.vkBindBufferMemory(
            Driver_p->Device, 
            *VkBuffer_p, 
            *DeviceMemory_p, 
            0
        ); 
    }
    
NH_GFX_DIAGNOSTIC_END(NH_API_SUCCESS)
}

NH_API_RESULT nh_vk_mapDeviceMemory(
    nh_vk_Driver *Driver_p, VkDeviceMemory *DeviceMemory_p, const void *data_p, size_t bufferSize, 
    size_t offset)
{
NH_GFX_BEGIN();
    
    if (bufferSize <= 0) {NH_GFX_DIAGNOSTIC_END(NH_API_ERROR_BAD_STATE)}

    void *memory_p;
    Driver_p->Functions.vkMapMemory(Driver_p->Device, *DeviceMemory_p, offset, bufferSize, 0, &memory_p); 
    memcpy(memory_p, data_p, bufferSize);
    Driver_p->Functions.vkUnmapMemory(Driver_p->Device, *DeviceMemory_p);

NH_GFX_DIAGNOSTIC_END(NH_API_SUCCESS);
}

NH_API_RESULT nh_vk_findMemoryType(
    nh_vk_Driver *Driver_p, int typeFilter, VkMemoryPropertyFlags properties, uint32_t *result_p) 
{
NH_GFX_BEGIN();

    *result_p = -1;
    VkPhysicalDeviceMemoryProperties memoryProperties;
    
    NH_VULKAN.Host.Functions.vkGetPhysicalDeviceMemoryProperties(Driver_p->PhysicalDevice, &memoryProperties);
    
    for (uint32_t i = 0; i < memoryProperties.memoryTypeCount; i++) 
    { 
        if ((typeFilter & (1 << i)) && (memoryProperties.memoryTypes[i].propertyFlags & properties) == properties) {
            *result_p = i;
        }
    }

NH_GFX_DIAGNOSTIC_END(NH_API_SUCCESS);
}

// SHADER MODULE ===================================================================================

NH_API_RESULT nh_vk_createShaderModule(
    nh_vk_Driver *Driver_p, const uint32_t *code, size_t size, VkShaderModule *ShaderModule_p)
{
NH_GFX_BEGIN()

    VkShaderModuleCreateInfo shaderCreateInfo = 
    {
        .sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO,
        .pNext    = VK_NULL_HANDLE,
        .flags    = 0,
        .codeSize = size,
        .pCode    = code,
    };
    Driver_p->Functions.vkCreateShaderModule(Driver_p->Device, &shaderCreateInfo, VK_NULL_HANDLE, ShaderModule_p);

NH_GFX_DIAGNOSTIC_END(NH_API_SUCCESS)
}

// PIPELINE ========================================================================================

NH_API_RESULT nh_vk_createPipeline(
    nh_vk_Driver *Driver_p, NH_VK_PIPELINE type, VkPipelineLayoutCreateInfo *PipelineLayoutCreateInfo_p, 
    void *pipelineInfo_p, nh_vk_Pipeline *Pipeline_p)
{
NH_GFX_BEGIN()

    if (Driver_p->Functions.vkCreatePipelineLayout(Driver_p->Device, PipelineLayoutCreateInfo_p, VK_NULL_HANDLE, &Pipeline_p->PipelineLayout) != VK_SUCCESS) {
        NH_GFX_DIAGNOSTIC_END(NH_API_ERROR_BAD_STATE)
    }
   
    if (type == NH_VK_PIPELINE_GRAPHICS) 
    {
        VkGraphicsPipelineCreateInfo *info_p = (VkGraphicsPipelineCreateInfo*) pipelineInfo_p;
        info_p->layout = Pipeline_p->PipelineLayout;
        if (Driver_p->Functions.vkCreateGraphicsPipelines(Driver_p->Device, VK_NULL_HANDLE, 1, info_p, 
            VK_NULL_HANDLE, &Pipeline_p->Pipeline) != VK_SUCCESS) 
        {
            NH_GFX_DIAGNOSTIC_END(NH_API_ERROR_BAD_STATE)
        }
    }

    if (type == NH_VK_PIPELINE_COMPUTE) 
    {
        VkComputePipelineCreateInfo *info_p = (VkComputePipelineCreateInfo*) pipelineInfo_p;
        info_p->layout = Pipeline_p->PipelineLayout;
        if (Driver_p->Functions.vkCreateComputePipelines(Driver_p->Device, VK_NULL_HANDLE, 1, info_p, 
            VK_NULL_HANDLE, &Pipeline_p->Pipeline) != VK_SUCCESS) 
        {
            NH_GFX_DIAGNOSTIC_END(NH_API_ERROR_BAD_STATE)
        }
    }

NH_GFX_DIAGNOSTIC_END(NH_API_SUCCESS)
}

void nh_vk_destroyPipeline(
    nh_vk_Driver *Driver_p, nh_vk_Pipeline *Pipeline_p)
{
NH_GFX_BEGIN()

    Driver_p->Functions.vkDestroyPipeline(Driver_p->Device, Pipeline_p->Pipeline, VK_NULL_HANDLE);
    Driver_p->Functions.vkDestroyPipelineLayout(Driver_p->Device, Pipeline_p->PipelineLayout, VK_NULL_HANDLE);
 
NH_GFX_SILENT_END()
}

void nh_vk_prepareDefaultPipelineInfo(
    nh_vk_PipelineInfo *Info_p)
{
NH_GFX_BEGIN()

// viewport
    Info_p->dynamic_p[0] = VK_DYNAMIC_STATE_VIEWPORT;
    Info_p->dynamic_p[1] = VK_DYNAMIC_STATE_SCISSOR;

    VkPipelineDynamicStateCreateInfo DynamicState = 
    {
        .sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO,
        .dynamicStateCount = 2,
        .pDynamicStates    = Info_p->dynamic_p,
    };
    Info_p->DynamicState = DynamicState; 

    Info_p->Viewport.x        = 0.0f;
    Info_p->Viewport.y        = 0.0f;
    Info_p->Viewport.width    = 0.0f;
    Info_p->Viewport.height   = 0.0f;    
    Info_p->Viewport.minDepth = 0.0f;
    Info_p->Viewport.maxDepth = 1.0f;
    
    VkExtent2D Extent2D = 
    { 
        .width = 0.0f, 
        .height = 0.0f
    };
    VkOffset2D Offset2D = 
    { 
        .x = 0, 
        .y = 0
    };
    Info_p->Scissor.offset = Offset2D;
    Info_p->Scissor.extent = Extent2D;

    VkPipelineViewportStateCreateInfo ViewportState = 
    {
        .sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO,
        .viewportCount = 1,
        .pViewports    = &Info_p->Viewport,
        .scissorCount  = 1,
        .pScissors     = &Info_p->Scissor,
    };
    Info_p->ViewportState = ViewportState;

// other
    VkStencilOpState OpState = {};

    VkPipelineDepthStencilStateCreateInfo DepthStencilState = 
    {
        .sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO,
        .depthTestEnable       = VK_TRUE,
        .depthWriteEnable      = VK_TRUE,
        .depthCompareOp        = VK_COMPARE_OP_LESS,
        .depthBoundsTestEnable = VK_FALSE,
        .minDepthBounds        = 0.0f,
        .maxDepthBounds        = 1.0f,
        .stencilTestEnable     = VK_FALSE,
        .front                 = OpState,
        .back                  = OpState,
    };
    Info_p->DepthStencilState = DepthStencilState;

    VkPipelineRasterizationStateCreateInfo RasterizationState = 
    {
        .sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO,
        .depthClampEnable        = VK_FALSE,
        .rasterizerDiscardEnable = VK_FALSE,
        .polygonMode             = VK_POLYGON_MODE_FILL,
        .lineWidth               = 1.0f,
        .cullMode                = VK_CULL_MODE_NONE,
        .frontFace               = VK_FRONT_FACE_COUNTER_CLOCKWISE,
        .depthBiasEnable         = VK_FALSE
    };
    Info_p->RasterizationState = RasterizationState;

    VkPipelineColorBlendAttachmentState ColorBlendAttachment = 
    {
        .blendEnable         = VK_TRUE,
        .srcColorBlendFactor = VK_BLEND_FACTOR_ONE,
        .dstColorBlendFactor = VK_BLEND_FACTOR_ONE_MINUS_SRC_ALPHA,
        .colorBlendOp        = VK_BLEND_OP_ADD,
        .srcAlphaBlendFactor = VK_BLEND_FACTOR_ZERO,
        .dstAlphaBlendFactor = VK_BLEND_FACTOR_ONE,
        .alphaBlendOp        = VK_BLEND_OP_ADD,
        .colorWriteMask      = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT
    };
    Info_p->ColorBlendAttachment = ColorBlendAttachment;
    
    VkPipelineColorBlendStateCreateInfo ColorBlendState = 
    {
        .sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO,
        .logicOpEnable     = VK_FALSE,
        .logicOp           = VK_LOGIC_OP_COPY,
        .attachmentCount   = 1,
        .pAttachments      = &Info_p->ColorBlendAttachment, 
        .blendConstants[0] = 0.0f,
        .blendConstants[1] = 0.0f,
        .blendConstants[2] = 0.0f,
        .blendConstants[3] = 0.0f,
    };
    Info_p->ColorBlendState = ColorBlendState;

    VkPipelineMultisampleStateCreateInfo MultisampleState = 
    {
        .sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO,
        .sampleShadingEnable = VK_FALSE,
        .rasterizationSamples = VK_SAMPLE_COUNT_1_BIT,
    };
    Info_p->MultisampleState = MultisampleState;

NH_GFX_SILENT_END()
}

