/**
 *	@file	vulkan_h.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_H_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_H_HPP

#include <bksge/fnd/config.hpp>

#if defined(BKSGE_PLATFORM_WIN32)
#define VK_USE_PLATFORM_WIN32_KHR
#define NOMINMAX
#include <bksge/core/detail/win32.hpp>
#endif

#include <vulkan/vulkan.h>
#include <vector>

namespace bksge
{

namespace render
{

namespace vk
{

struct ApplicationInfo : public ::VkApplicationInfo
{
	ApplicationInfo()
	{
		sType              = VK_STRUCTURE_TYPE_APPLICATION_INFO;
		pNext              = nullptr;
		pApplicationName   = nullptr;
		applicationVersion = 0;
		pEngineName        = nullptr;
		engineVersion      = 0;
		apiVersion         = 0;
	}
};

struct InstanceCreateInfo : public ::VkInstanceCreateInfo
{
	InstanceCreateInfo()
	{
		sType                   = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
		pNext                   = nullptr;
		flags                   = 0;
		pApplicationInfo        = nullptr;
		enabledLayerCount       = 0;
		ppEnabledLayerNames     = nullptr;
		enabledExtensionCount   = 0;
		ppEnabledExtensionNames = nullptr;
	}

	void SetEnabledLayerNames(std::vector<char const*> const& layer_names)
	{
		enabledLayerCount       = static_cast<std::uint32_t>(layer_names.size());
		ppEnabledLayerNames     = layer_names.data();
	}

	void SetEnabledExtensionNames(std::vector<char const*> const& extension_names)
	{
		enabledExtensionCount   = static_cast<std::uint32_t>(extension_names.size());
		ppEnabledExtensionNames = extension_names.data();
	}
};

//struct AllocationCallbacks
//{
//	void* pUserData;
//	PFN_vkAllocationFunction                pfnAllocation;
//	PFN_vkReallocationFunction              pfnReallocation;
//	PFN_vkFreeFunction                      pfnFree;
//	PFN_vkInternalAllocationNotification    pfnInternalAllocation;
//	PFN_vkInternalFreeNotification          pfnInternalFree;
//};
//
//struct PhysicalDeviceFeatures
//{
//	VkBool32    robustBufferAccess;
//	VkBool32    fullDrawIndexUint32;
//	VkBool32    imageCubeArray;
//	VkBool32    independentBlend;
//	VkBool32    geometryShader;
//	VkBool32    tessellationShader;
//	VkBool32    sampleRateShading;
//	VkBool32    dualSrcBlend;
//	VkBool32    logicOp;
//	VkBool32    multiDrawIndirect;
//	VkBool32    drawIndirectFirstInstance;
//	VkBool32    depthClamp;
//	VkBool32    depthBiasClamp;
//	VkBool32    fillModeNonSolid;
//	VkBool32    depthBounds;
//	VkBool32    wideLines;
//	VkBool32    largePoints;
//	VkBool32    alphaToOne;
//	VkBool32    multiViewport;
//	VkBool32    samplerAnisotropy;
//	VkBool32    textureCompressionETC2;
//	VkBool32    textureCompressionASTC_LDR;
//	VkBool32    textureCompressionBC;
//	VkBool32    occlusionQueryPrecise;
//	VkBool32    pipelineStatisticsQuery;
//	VkBool32    vertexPipelineStoresAndAtomics;
//	VkBool32    fragmentStoresAndAtomics;
//	VkBool32    shaderTessellationAndGeometryPointSize;
//	VkBool32    shaderImageGatherExtended;
//	VkBool32    shaderStorageImageExtendedFormats;
//	VkBool32    shaderStorageImageMultisample;
//	VkBool32    shaderStorageImageReadWithoutFormat;
//	VkBool32    shaderStorageImageWriteWithoutFormat;
//	VkBool32    shaderUniformBufferArrayDynamicIndexing;
//	VkBool32    shaderSampledImageArrayDynamicIndexing;
//	VkBool32    shaderStorageBufferArrayDynamicIndexing;
//	VkBool32    shaderStorageImageArrayDynamicIndexing;
//	VkBool32    shaderClipDistance;
//	VkBool32    shaderCullDistance;
//	VkBool32    shaderFloat64;
//	VkBool32    shaderInt64;
//	VkBool32    shaderInt16;
//	VkBool32    shaderResourceResidency;
//	VkBool32    shaderResourceMinLod;
//	VkBool32    sparseBinding;
//	VkBool32    sparseResidencyBuffer;
//	VkBool32    sparseResidencyImage2D;
//	VkBool32    sparseResidencyImage3D;
//	VkBool32    sparseResidency2Samples;
//	VkBool32    sparseResidency4Samples;
//	VkBool32    sparseResidency8Samples;
//	VkBool32    sparseResidency16Samples;
//	VkBool32    sparseResidencyAliased;
//	VkBool32    variableMultisampleRate;
//	VkBool32    inheritedQueries;
//};
//
//struct FormatProperties
//{
//	VkFormatFeatureFlags    linearTilingFeatures;
//	VkFormatFeatureFlags    optimalTilingFeatures;
//	VkFormatFeatureFlags    bufferFeatures;
//};
//
//struct Extent3D
//{
//	uint32_t    width;
//	uint32_t    height;
//	uint32_t    depth;
//};
//
//struct ImageFormatProperties
//{
//	VkExtent3D            maxExtent;
//	uint32_t              maxMipLevels;
//	uint32_t              maxArrayLayers;
//	VkSampleCountFlags    sampleCounts;
//	VkDeviceSize          maxResourceSize;
//};
//
//struct PhysicalDeviceLimits
//{
//	uint32_t              maxImageDimension1D;
//	uint32_t              maxImageDimension2D;
//	uint32_t              maxImageDimension3D;
//	uint32_t              maxImageDimensionCube;
//	uint32_t              maxImageArrayLayers;
//	uint32_t              maxTexelBufferElements;
//	uint32_t              maxUniformBufferRange;
//	uint32_t              maxStorageBufferRange;
//	uint32_t              maxPushConstantsSize;
//	uint32_t              maxMemoryAllocationCount;
//	uint32_t              maxSamplerAllocationCount;
//	VkDeviceSize          bufferImageGranularity;
//	VkDeviceSize          sparseAddressSpaceSize;
//	uint32_t              maxBoundDescriptorSets;
//	uint32_t              maxPerStageDescriptorSamplers;
//	uint32_t              maxPerStageDescriptorUniformBuffers;
//	uint32_t              maxPerStageDescriptorStorageBuffers;
//	uint32_t              maxPerStageDescriptorSampledImages;
//	uint32_t              maxPerStageDescriptorStorageImages;
//	uint32_t              maxPerStageDescriptorInputAttachments;
//	uint32_t              maxPerStageResources;
//	uint32_t              maxDescriptorSetSamplers;
//	uint32_t              maxDescriptorSetUniformBuffers;
//	uint32_t              maxDescriptorSetUniformBuffersDynamic;
//	uint32_t              maxDescriptorSetStorageBuffers;
//	uint32_t              maxDescriptorSetStorageBuffersDynamic;
//	uint32_t              maxDescriptorSetSampledImages;
//	uint32_t              maxDescriptorSetStorageImages;
//	uint32_t              maxDescriptorSetInputAttachments;
//	uint32_t              maxVertexInputAttributes;
//	uint32_t              maxVertexInputBindings;
//	uint32_t              maxVertexInputAttributeOffset;
//	uint32_t              maxVertexInputBindingStride;
//	uint32_t              maxVertexOutputComponents;
//	uint32_t              maxTessellationGenerationLevel;
//	uint32_t              maxTessellationPatchSize;
//	uint32_t              maxTessellationControlPerVertexInputComponents;
//	uint32_t              maxTessellationControlPerVertexOutputComponents;
//	uint32_t              maxTessellationControlPerPatchOutputComponents;
//	uint32_t              maxTessellationControlTotalOutputComponents;
//	uint32_t              maxTessellationEvaluationInputComponents;
//	uint32_t              maxTessellationEvaluationOutputComponents;
//	uint32_t              maxGeometryShaderInvocations;
//	uint32_t              maxGeometryInputComponents;
//	uint32_t              maxGeometryOutputComponents;
//	uint32_t              maxGeometryOutputVertices;
//	uint32_t              maxGeometryTotalOutputComponents;
//	uint32_t              maxFragmentInputComponents;
//	uint32_t              maxFragmentOutputAttachments;
//	uint32_t              maxFragmentDualSrcAttachments;
//	uint32_t              maxFragmentCombinedOutputResources;
//	uint32_t              maxComputeSharedMemorySize;
//	uint32_t              maxComputeWorkGroupCount[3];
//	uint32_t              maxComputeWorkGroupInvocations;
//	uint32_t              maxComputeWorkGroupSize[3];
//	uint32_t              subPixelPrecisionBits;
//	uint32_t              subTexelPrecisionBits;
//	uint32_t              mipmapPrecisionBits;
//	uint32_t              maxDrawIndexedIndexValue;
//	uint32_t              maxDrawIndirectCount;
//	float                 maxSamplerLodBias;
//	float                 maxSamplerAnisotropy;
//	uint32_t              maxViewports;
//	uint32_t              maxViewportDimensions[2];
//	float                 viewportBoundsRange[2];
//	uint32_t              viewportSubPixelBits;
//	size_t                minMemoryMapAlignment;
//	VkDeviceSize          minTexelBufferOffsetAlignment;
//	VkDeviceSize          minUniformBufferOffsetAlignment;
//	VkDeviceSize          minStorageBufferOffsetAlignment;
//	int32_t               minTexelOffset;
//	uint32_t              maxTexelOffset;
//	int32_t               minTexelGatherOffset;
//	uint32_t              maxTexelGatherOffset;
//	float                 minInterpolationOffset;
//	float                 maxInterpolationOffset;
//	uint32_t              subPixelInterpolationOffsetBits;
//	uint32_t              maxFramebufferWidth;
//	uint32_t              maxFramebufferHeight;
//	uint32_t              maxFramebufferLayers;
//	VkSampleCountFlags    framebufferColorSampleCounts;
//	VkSampleCountFlags    framebufferDepthSampleCounts;
//	VkSampleCountFlags    framebufferStencilSampleCounts;
//	VkSampleCountFlags    framebufferNoAttachmentsSampleCounts;
//	uint32_t              maxColorAttachments;
//	VkSampleCountFlags    sampledImageColorSampleCounts;
//	VkSampleCountFlags    sampledImageIntegerSampleCounts;
//	VkSampleCountFlags    sampledImageDepthSampleCounts;
//	VkSampleCountFlags    sampledImageStencilSampleCounts;
//	VkSampleCountFlags    storageImageSampleCounts;
//	uint32_t              maxSampleMaskWords;
//	VkBool32              timestampComputeAndGraphics;
//	float                 timestampPeriod;
//	uint32_t              maxClipDistances;
//	uint32_t              maxCullDistances;
//	uint32_t              maxCombinedClipAndCullDistances;
//	uint32_t              discreteQueuePriorities;
//	float                 pointSizeRange[2];
//	float                 lineWidthRange[2];
//	float                 pointSizeGranularity;
//	float                 lineWidthGranularity;
//	VkBool32              strictLines;
//	VkBool32              standardSampleLocations;
//	VkDeviceSize          optimalBufferCopyOffsetAlignment;
//	VkDeviceSize          optimalBufferCopyRowPitchAlignment;
//	VkDeviceSize          nonCoherentAtomSize;
//};
//
//struct PhysicalDeviceSparseProperties
//{
//	VkBool32    residencyStandard2DBlockShape;
//	VkBool32    residencyStandard2DMultisampleBlockShape;
//	VkBool32    residencyStandard3DBlockShape;
//	VkBool32    residencyAlignedMipSize;
//	VkBool32    residencyNonResidentStrict;
//};
//
//struct PhysicalDeviceProperties
//{
//	uint32_t                            apiVersion;
//	uint32_t                            driverVersion;
//	uint32_t                            vendorID;
//	uint32_t                            deviceID;
//	VkPhysicalDeviceType                deviceType;
//	char                                deviceName[VK_MAX_PHYSICAL_DEVICE_NAME_SIZE];
//	uint8_t                             pipelineCacheUUID[VK_UUID_SIZE];
//	VkPhysicalDeviceLimits              limits;
//	VkPhysicalDeviceSparseProperties    sparseProperties;
//};
//
//struct QueueFamilyProperties
//{
//	VkQueueFlags    queueFlags;
//	uint32_t        queueCount;
//	uint32_t        timestampValidBits;
//	VkExtent3D      minImageTransferGranularity;
//};
//
//struct MemoryType
//{
//	VkMemoryPropertyFlags    propertyFlags;
//	uint32_t                 heapIndex;
//};
//
//struct MemoryHeap
//{
//	VkDeviceSize         size;
//	VkMemoryHeapFlags    flags;
//};
//
//struct PhysicalDeviceMemoryProperties
//{
//	uint32_t        memoryTypeCount;
//	VkMemoryType    memoryTypes[VK_MAX_MEMORY_TYPES];
//	uint32_t        memoryHeapCount;
//	VkMemoryHeap    memoryHeaps[VK_MAX_MEMORY_HEAPS];
//};

struct DeviceQueueCreateInfo : public ::VkDeviceQueueCreateInfo
{
	DeviceQueueCreateInfo()
	{
		sType            = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		pNext            = nullptr;
		flags            = 0;
		queueFamilyIndex = 0;
		queueCount       = 0;
		pQueuePriorities = nullptr;
	}
};

struct DeviceCreateInfo : public ::VkDeviceCreateInfo
{
	DeviceCreateInfo()
	{
		sType                   = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
		pNext                   = nullptr;
		flags                   = 0;
		queueCreateInfoCount    = 0;
		pQueueCreateInfos       = nullptr;
		enabledLayerCount       = 0;
		ppEnabledLayerNames     = nullptr;
		enabledExtensionCount   = 0;
		ppEnabledExtensionNames = nullptr;
		pEnabledFeatures        = nullptr;
	}

	void SetQueueCreateInfos(::VkDeviceQueueCreateInfo const* queue_create_info)
	{
		queueCreateInfoCount   = queue_create_info ? 1 : 0;
		pQueueCreateInfos      = queue_create_info;
	}

	void SetEnabledLayerNames(std::vector<char const*> const& layer_names)
	{
		enabledLayerCount       = static_cast<std::uint32_t>(layer_names.size());
		ppEnabledLayerNames     = layer_names.data();
	}

	void SetEnabledExtensionNames(std::vector<char const*> const& extension_names)
	{
		enabledExtensionCount   = static_cast<std::uint32_t>(extension_names.size());
		ppEnabledExtensionNames = extension_names.data();
	}
};

//struct ExtensionProperties
//{
//	char        extensionName[VK_MAX_EXTENSION_NAME_SIZE];
//	uint32_t    specVersion;
//};
//
//struct LayerProperties
//{
//	char        layerName[VK_MAX_EXTENSION_NAME_SIZE];
//	uint32_t    specVersion;
//	uint32_t    implementationVersion;
//	char        description[VK_MAX_DESCRIPTION_SIZE];
//};

struct SubmitInfo : public ::VkSubmitInfo
{
	SubmitInfo()
	{
		sType                = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		pNext                = nullptr;
		waitSemaphoreCount   = 0;
		pWaitSemaphores      = nullptr;
		pWaitDstStageMask    = nullptr;
		commandBufferCount   = 0;
		pCommandBuffers      = nullptr;
		signalSemaphoreCount = 0;
		pSignalSemaphores    = nullptr;
	}

	void SetWaitSemaphores(::VkSemaphore const* wait_semaphore)
	{
		waitSemaphoreCount   = wait_semaphore ? 1 : 0;
		pWaitSemaphores      = wait_semaphore;
	}

	void SetCommandBuffers(::VkCommandBuffer const* command_buffer)
	{
		commandBufferCount   = command_buffer ? 1 : 0;
		pCommandBuffers      = command_buffer;
	}

	void SetSignalSemaphores(::VkSemaphore const* signal_semaphore)
	{
		signalSemaphoreCount = signal_semaphore ? 1 : 0;
		pSignalSemaphores    = signal_semaphore;
	}
};

struct MemoryAllocateInfo : public ::VkMemoryAllocateInfo
{
	MemoryAllocateInfo()
	{
		sType           = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		pNext           = nullptr;
		allocationSize  = 0;
		memoryTypeIndex = 0;
	}
};

//struct MappedMemoryRange
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkDeviceMemory     memory;
//	VkDeviceSize       offset;
//	VkDeviceSize       size;
//};
//
//struct MemoryRequirements
//{
//	VkDeviceSize    size;
//	VkDeviceSize    alignment;
//	uint32_t        memoryTypeBits;
//};
//
//struct SparseImageFormatProperties
//{
//	VkImageAspectFlags          aspectMask;
//	VkExtent3D                  imageGranularity;
//	VkSparseImageFormatFlags    flags;
//};
//
//struct SparseImageMemoryRequirements
//{
//	VkSparseImageFormatProperties    formatProperties;
//	uint32_t                         imageMipTailFirstLod;
//	VkDeviceSize                     imageMipTailSize;
//	VkDeviceSize                     imageMipTailOffset;
//	VkDeviceSize                     imageMipTailStride;
//};
//
//struct SparseMemoryBind
//{
//	VkDeviceSize               resourceOffset;
//	VkDeviceSize               size;
//	VkDeviceMemory             memory;
//	VkDeviceSize               memoryOffset;
//	VkSparseMemoryBindFlags    flags;
//};
//
//struct SparseBufferMemoryBindInfo
//{
//	VkBuffer                     buffer;
//	uint32_t                     bindCount;
//	const VkSparseMemoryBind* pBinds;
//};
//
//struct SparseImageOpaqueMemoryBindInfo
//{
//	VkImage                      image;
//	uint32_t                     bindCount;
//	const VkSparseMemoryBind* pBinds;
//};
//
//struct ImageSubresource
//{
//	VkImageAspectFlags    aspectMask;
//	uint32_t              mipLevel;
//	uint32_t              arrayLayer;
//};
//
//struct Offset3D
//{
//	int32_t    x;
//	int32_t    y;
//	int32_t    z;
//};
//
//struct SparseImageMemoryBind
//{
//	VkImageSubresource         subresource;
//	VkOffset3D                 offset;
//	VkExtent3D                 extent;
//	VkDeviceMemory             memory;
//	VkDeviceSize               memoryOffset;
//	VkSparseMemoryBindFlags    flags;
//};
//
//struct SparseImageMemoryBindInfo
//{
//	VkImage                           image;
//	uint32_t                          bindCount;
//	const VkSparseImageMemoryBind* pBinds;
//};
//
//struct BindSparseInfo
//{
//	VkStructureType                             sType;
//	const void* pNext;
//	uint32_t                                    waitSemaphoreCount;
//	const VkSemaphore* pWaitSemaphores;
//	uint32_t                                    bufferBindCount;
//	const VkSparseBufferMemoryBindInfo* pBufferBinds;
//	uint32_t                                    imageOpaqueBindCount;
//	const VkSparseImageOpaqueMemoryBindInfo* pImageOpaqueBinds;
//	uint32_t                                    imageBindCount;
//	const VkSparseImageMemoryBindInfo* pImageBinds;
//	uint32_t                                    signalSemaphoreCount;
//	const VkSemaphore* pSignalSemaphores;
//};

struct FenceCreateInfo : public ::VkFenceCreateInfo
{
	FenceCreateInfo()
	{
		sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
		pNext = nullptr;
		flags = 0;
	}
};

struct SemaphoreCreateInfo : public ::VkSemaphoreCreateInfo
{
	SemaphoreCreateInfo()
	{
		sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
		pNext = nullptr;
		flags = 0;
	}
};

//struct EventCreateInfo
//{
//	VkStructureType       sType;
//	const void* pNext;
//	VkEventCreateFlags    flags;
//};
//
//struct QueryPoolCreateInfo
//{
//	VkStructureType                  sType;
//	const void* pNext;
//	VkQueryPoolCreateFlags           flags;
//	VkQueryType                      queryType;
//	uint32_t                         queryCount;
//	VkQueryPipelineStatisticFlags    pipelineStatistics;
//};

struct BufferCreateInfo : public ::VkBufferCreateInfo
{
	BufferCreateInfo()
	{
		sType                 = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		pNext                 = nullptr;
		flags                 = 0;
		size                  = 0;
		usage                 = 0;
		sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
		queueFamilyIndexCount = 0;
		pQueueFamilyIndices   = nullptr;
	}

	void SetQueueFamilyIndices(std::uint32_t const* queue_family_index)
	{
		queueFamilyIndexCount = queue_family_index ? 1 : 0;
		pQueueFamilyIndices   = queue_family_index;
	}
};

//struct BufferViewCreateInfo
//{
//	VkStructureType            sType;
//	const void* pNext;
//	VkBufferViewCreateFlags    flags;
//	VkBuffer                   buffer;
//	VkFormat                   format;
//	VkDeviceSize               offset;
//	VkDeviceSize               range;
//};

struct ImageCreateInfo : public ::VkImageCreateInfo
{
	ImageCreateInfo()
	{
		sType                 = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
		pNext                 = nullptr;
		flags                 = 0;
		imageType             = VK_IMAGE_TYPE_1D;
		format                = VK_FORMAT_UNDEFINED;
		extent.width          = 0;
		extent.height         = 0;
		extent.depth          = 0;
		mipLevels             = 0;
		arrayLayers           = 0;
		samples               = VK_SAMPLE_COUNT_1_BIT;
		tiling                = VK_IMAGE_TILING_OPTIMAL;
		usage                 = 0;
		sharingMode           = VK_SHARING_MODE_EXCLUSIVE;
		queueFamilyIndexCount = 0;
		pQueueFamilyIndices   = nullptr;
		initialLayout         = VK_IMAGE_LAYOUT_UNDEFINED;
	}

	void SetQueueFamilyIndices(std::uint32_t const* queue_family_index)
	{
		queueFamilyIndexCount = queue_family_index ? 1 : 0;
		pQueueFamilyIndices   = queue_family_index;
	}
};

//struct SubresourceLayout
//{
//	VkDeviceSize    offset;
//	VkDeviceSize    size;
//	VkDeviceSize    rowPitch;
//	VkDeviceSize    arrayPitch;
//	VkDeviceSize    depthPitch;
//};

struct ComponentMapping : public ::VkComponentMapping
{
	ComponentMapping()
	{
		r = VK_COMPONENT_SWIZZLE_IDENTITY;
		g = VK_COMPONENT_SWIZZLE_IDENTITY;
		b = VK_COMPONENT_SWIZZLE_IDENTITY;
		a = VK_COMPONENT_SWIZZLE_IDENTITY;
	}
};

struct ImageSubresourceRange : public ::VkImageSubresourceRange
{
	ImageSubresourceRange()
	{
		aspectMask     = 0;
		baseMipLevel   = 0;
		levelCount     = 0;
		baseArrayLayer = 0;
		layerCount     = 0;
	}
};

struct ImageViewCreateInfo : public ::VkImageViewCreateInfo
{
	ImageViewCreateInfo()
	{
		sType            = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
		pNext            = nullptr;
		flags            = 0;
		image            = VK_NULL_HANDLE;
		viewType         = VK_IMAGE_VIEW_TYPE_1D;
		format           = VK_FORMAT_UNDEFINED;
		components       = ComponentMapping();
		subresourceRange = ImageSubresourceRange();
	}
};

struct ShaderModuleCreateInfo : public ::VkShaderModuleCreateInfo
{
	ShaderModuleCreateInfo()
	{
		sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		pNext    = nullptr;
		flags    = 0;
		codeSize = 0;
		pCode    = nullptr;
	}
};

struct PipelineCacheCreateInfo : public ::VkPipelineCacheCreateInfo
{
	PipelineCacheCreateInfo()
	{
		sType           = VK_STRUCTURE_TYPE_PIPELINE_CACHE_CREATE_INFO;
		pNext           = nullptr;
		flags           = 0;
		initialDataSize = 0;
		pInitialData    = nullptr;
	}
};

//struct SpecializationMapEntry
//{
//	uint32_t    constantID;
//	uint32_t    offset;
//	size_t      size;
//};
//
//struct SpecializationInfo
//{
//	uint32_t                           mapEntryCount;
//	const VkSpecializationMapEntry* pMapEntries;
//	size_t                             dataSize;
//	const void* pData;
//};

struct PipelineShaderStageCreateInfo : public ::VkPipelineShaderStageCreateInfo
{
	PipelineShaderStageCreateInfo()
	{
		sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		pNext               = nullptr;
		flags               = 0;
		stage               = VkShaderStageFlagBits(0);
		module              = VK_NULL_HANDLE;
		pName               = nullptr;
		pSpecializationInfo = nullptr;
	}
};

//struct VertexInputBindingDescription
//{
//	uint32_t             binding;
//	uint32_t             stride;
//	VkVertexInputRate    inputRate;
//};
//
//struct VertexInputAttributeDescription
//{
//	uint32_t    location;
//	uint32_t    binding;
//	VkFormat    format;
//	uint32_t    offset;
//};

struct PipelineVertexInputStateCreateInfo : public ::VkPipelineVertexInputStateCreateInfo
{
	PipelineVertexInputStateCreateInfo()
	{
		sType                           = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
		pNext                           = nullptr;
		flags                           = 0;
		vertexBindingDescriptionCount   = 0;
		pVertexBindingDescriptions      = nullptr;
		vertexAttributeDescriptionCount = 0;
		pVertexAttributeDescriptions    = nullptr;
	}

	void SetVertexBindingDescription(::VkVertexInputBindingDescription const* vi_binding)
	{
		vertexBindingDescriptionCount   = vi_binding ? 1 : 0;
		pVertexBindingDescriptions      = vi_binding;
	}

	void SetVertexAttributeDescriptions(
		std::vector<::VkVertexInputAttributeDescription> const& vi_attribs)
	{
		vertexAttributeDescriptionCount = static_cast<std::uint32_t>(vi_attribs.size());
		pVertexAttributeDescriptions    = vi_attribs.data();
	}
};

struct PipelineInputAssemblyStateCreateInfo : public ::VkPipelineInputAssemblyStateCreateInfo
{
	PipelineInputAssemblyStateCreateInfo()
	{
		sType                  = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		pNext                  = nullptr;
		flags                  = 0;
		topology               = VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
		primitiveRestartEnable = VK_FALSE;
	}
};

//struct PipelineTessellationStateCreateInfo
//{
//	VkStructureType                           sType;
//	const void* pNext;
//	VkPipelineTessellationStateCreateFlags    flags;
//	uint32_t                                  patchControlPoints;
//};
//
//struct Viewport
//{
//	float    x;
//	float    y;
//	float    width;
//	float    height;
//	float    minDepth;
//	float    maxDepth;
//};

struct Offset2D : public ::VkOffset2D
{
	Offset2D()
	{
		x = 0;
		y = 0;
	}
};

struct Extent2D : public ::VkExtent2D
{
	Extent2D()
	{
		width  = 0;
		height = 0;
	}
};

struct Rect2D : public ::VkRect2D
{
	Rect2D()
	{
		offset = Offset2D();
		extent = Extent2D();
	}
};

struct PipelineViewportStateCreateInfo : public ::VkPipelineViewportStateCreateInfo
{
	PipelineViewportStateCreateInfo()
	{
		sType         = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		pNext         = nullptr;
		flags         = 0;
		viewportCount = 0;
		pViewports    = nullptr;
		scissorCount  = 0;
		pScissors     = nullptr;
	}
};

struct PipelineRasterizationStateCreateInfo : public ::VkPipelineRasterizationStateCreateInfo
{
	PipelineRasterizationStateCreateInfo()
	{
		sType                   = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		pNext                   = nullptr;
		flags                   = 0;
		depthClampEnable        = VK_FALSE;
		rasterizerDiscardEnable = VK_FALSE;
		polygonMode             = VK_POLYGON_MODE_FILL;
		cullMode                = 0;
		frontFace               = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		depthBiasEnable         = VK_FALSE;
		depthBiasConstantFactor = 0.0f;
		depthBiasClamp          = 0.0f;
		depthBiasSlopeFactor    = 0.0f;
		lineWidth               = 0.0f;
	}
};

struct PipelineMultisampleStateCreateInfo : public ::VkPipelineMultisampleStateCreateInfo
{
	PipelineMultisampleStateCreateInfo()
	{
		sType                 = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		pNext                 = nullptr;
		flags                 = 0;
		rasterizationSamples  = VK_SAMPLE_COUNT_1_BIT;
		sampleShadingEnable   = VK_FALSE;
		minSampleShading      = 0.0f;
		pSampleMask           = nullptr;
		alphaToCoverageEnable = VK_FALSE;
		alphaToOneEnable      = VK_FALSE;
	}
};

struct StencilOpState : public ::VkStencilOpState
{
	StencilOpState()
	{
		failOp      = VK_STENCIL_OP_KEEP;
		passOp      = VK_STENCIL_OP_KEEP;
		depthFailOp = VK_STENCIL_OP_KEEP;
		compareOp   = VK_COMPARE_OP_NEVER;
		compareMask = 0;
		writeMask   = 0;
		reference   = 0;
	}
};

struct PipelineDepthStencilStateCreateInfo : public ::VkPipelineDepthStencilStateCreateInfo
{
	PipelineDepthStencilStateCreateInfo()
	{
		sType                 = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
		pNext                 = nullptr;
		flags                 = 0;
		depthTestEnable       = VK_FALSE;
		depthWriteEnable      = VK_FALSE;
		depthCompareOp        = VK_COMPARE_OP_NEVER;
		depthBoundsTestEnable = VK_FALSE;
		stencilTestEnable     = VK_FALSE;
		front                 = StencilOpState();
		back                  = StencilOpState();
		minDepthBounds        = 0.0f;
		maxDepthBounds        = 0.0f;
	}
};

//struct PipelineColorBlendAttachmentState
//{
//	VkBool32                 blendEnable;
//	VkBlendFactor            srcColorBlendFactor;
//	VkBlendFactor            dstColorBlendFactor;
//	VkBlendOp                colorBlendOp;
//	VkBlendFactor            srcAlphaBlendFactor;
//	VkBlendFactor            dstAlphaBlendFactor;
//	VkBlendOp                alphaBlendOp;
//	VkColorComponentFlags    colorWriteMask;
//};

struct PipelineColorBlendStateCreateInfo : public ::VkPipelineColorBlendStateCreateInfo
{
	PipelineColorBlendStateCreateInfo()
	{
		sType             = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		pNext             = nullptr;
		flags             = 0;
		logicOpEnable     = VK_FALSE;
		logicOp           = VK_LOGIC_OP_CLEAR;
		attachmentCount   = 0;
		pAttachments      = nullptr;
		blendConstants[0] = 0.0f;
		blendConstants[1] = 0.0f;
		blendConstants[2] = 0.0f;
		blendConstants[3] = 0.0f;
	}

	void SetAttachment(::VkPipelineColorBlendAttachmentState const* att_state)
	{
		attachmentCount   = att_state ? 1 : 0;
		pAttachments      = att_state;
	}

	void SetBlendConstants(float r, float g, float b, float a)
	{
		blendConstants[0] = r;
		blendConstants[1] = g;
		blendConstants[2] = b;
		blendConstants[3] = a;
	}
};

struct PipelineDynamicStateCreateInfo : public ::VkPipelineDynamicStateCreateInfo
{
	PipelineDynamicStateCreateInfo()
	{
		sType             = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		pNext             = nullptr;
		flags             = 0;
		dynamicStateCount = 0;
		pDynamicStates    = nullptr;
	}

	void SetDynamicStates(std::vector<::VkDynamicState> const& dynamic_states)
	{
		dynamicStateCount = static_cast<std::uint32_t>(dynamic_states.size());
		pDynamicStates    = dynamic_states.data();
	}
};

struct GraphicsPipelineCreateInfo : public ::VkGraphicsPipelineCreateInfo
{
	GraphicsPipelineCreateInfo()
	{
		sType               = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pNext               = nullptr;
		flags               = 0;
		stageCount          = 0;
		pStages             = nullptr;
		pVertexInputState   = nullptr;
		pInputAssemblyState = nullptr;
		pTessellationState  = nullptr;
		pViewportState      = nullptr;
		pRasterizationState = nullptr;
		pMultisampleState   = nullptr;
		pDepthStencilState  = nullptr;
		pColorBlendState    = nullptr;
		pDynamicState       = nullptr;
		layout              = VK_NULL_HANDLE;
		renderPass          = VK_NULL_HANDLE;
		subpass             = 0;
		basePipelineHandle  = VK_NULL_HANDLE;
		basePipelineIndex   = 0;
	}

	void SetStages(std::vector<::VkPipelineShaderStageCreateInfo> const& stages)
	{
		stageCount = static_cast<std::uint32_t>(stages.size());
		pStages    = stages.data();
	}
};

//struct ComputePipelineCreateInfo
//{
//	VkStructureType                    sType;
//	const void* pNext;
//	VkPipelineCreateFlags              flags;
//	VkPipelineShaderStageCreateInfo    stage;
//	VkPipelineLayout                   layout;
//	VkPipeline                         basePipelineHandle;
//	int32_t                            basePipelineIndex;
//};
//
//struct PushConstantRange
//{
//	VkShaderStageFlags    stageFlags;
//	uint32_t              offset;
//	uint32_t              size;
//};

struct PipelineLayoutCreateInfo : public ::VkPipelineLayoutCreateInfo
{
	PipelineLayoutCreateInfo()
	{
		sType                  = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pNext                  = nullptr;
		flags                  = 0;
		setLayoutCount         = 0;
		pSetLayouts            = nullptr;
		pushConstantRangeCount = 0;
		pPushConstantRanges    = nullptr;
	}

	void SetSetLayouts(std::vector<::VkDescriptorSetLayout> const& set_layouts)
	{
		setLayoutCount = static_cast<std::uint32_t>(set_layouts.size());
		pSetLayouts    = set_layouts.data();
	}

	void SetPushConstantRanges(::VkPushConstantRange const* range)
	{
		pushConstantRangeCount = range ? 1 : 0;
		pPushConstantRanges    = range;
	}
};

//struct SamplerCreateInfo
//{
//	VkStructureType         sType;
//	const void* pNext;
//	VkSamplerCreateFlags    flags;
//	VkFilter                magFilter;
//	VkFilter                minFilter;
//	VkSamplerMipmapMode     mipmapMode;
//	VkSamplerAddressMode    addressModeU;
//	VkSamplerAddressMode    addressModeV;
//	VkSamplerAddressMode    addressModeW;
//	float                   mipLodBias;
//	VkBool32                anisotropyEnable;
//	float                   maxAnisotropy;
//	VkBool32                compareEnable;
//	VkCompareOp             compareOp;
//	float                   minLod;
//	float                   maxLod;
//	VkBorderColor           borderColor;
//	VkBool32                unnormalizedCoordinates;
//};
//
//struct DescriptorSetLayoutBinding
//{
//	uint32_t              binding;
//	VkDescriptorType      descriptorType;
//	uint32_t              descriptorCount;
//	VkShaderStageFlags    stageFlags;
//	const VkSampler* pImmutableSamplers;
//};

struct DescriptorSetLayoutCreateInfo : public ::VkDescriptorSetLayoutCreateInfo
{
	DescriptorSetLayoutCreateInfo()
	{
		sType        = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		pNext        = nullptr;
		flags        = 0;
		bindingCount = 0;
		pBindings    = nullptr;
	}

	void SetBindings(std::vector<::VkDescriptorSetLayoutBinding> const& bindings)
	{
		bindingCount = static_cast<std::uint32_t>(bindings.size());
		pBindings    = bindings.data();
	}
};

//struct DescriptorPoolSize
//{
//	VkDescriptorType    type;
//	uint32_t            descriptorCount;
//};

struct DescriptorPoolCreateInfo : public ::VkDescriptorPoolCreateInfo
{
	DescriptorPoolCreateInfo()
	{
		sType         = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
		pNext         = nullptr;
		flags         = 0;
		maxSets       = 0;
		poolSizeCount = 0;
		pPoolSizes    = nullptr;
	}

	void SetPoolSizes(std::vector<::VkDescriptorPoolSize> const& pool_sizes)
	{
		poolSizeCount = static_cast<std::uint32_t>(pool_sizes.size());
		pPoolSizes    = pool_sizes.data();
	}
};

struct DescriptorSetAllocateInfo : public ::VkDescriptorSetAllocateInfo
{
	DescriptorSetAllocateInfo()
	{
		sType              = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
		pNext              = nullptr;
		descriptorPool     = VK_NULL_HANDLE;
		descriptorSetCount = 0;
		pSetLayouts        = nullptr;
	}

	void SetSetLayouts(std::vector<::VkDescriptorSetLayout> const& set_layouts)
	{
		descriptorSetCount = static_cast<std::uint32_t>(set_layouts.size());
		pSetLayouts        = set_layouts.data();
	}
};

//struct DescriptorImageInfo
//{
//	VkSampler        sampler;
//	VkImageView      imageView;
//	VkImageLayout    imageLayout;
//};
//
//struct DescriptorBufferInfo
//{
//	VkBuffer        buffer;
//	VkDeviceSize    offset;
//	VkDeviceSize    range;
//};

struct WriteDescriptorSet : public ::VkWriteDescriptorSet
{
	WriteDescriptorSet()
	{
		sType            = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
		pNext            = nullptr;
		dstSet           = VK_NULL_HANDLE;
		dstBinding       = 0;
		dstArrayElement  = 0;
		descriptorCount  = 0;
		descriptorType   = VK_DESCRIPTOR_TYPE_SAMPLER;
		pImageInfo       = nullptr;
		pBufferInfo      = nullptr;
		pTexelBufferView = nullptr;
	}
};

//struct CopyDescriptorSet
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkDescriptorSet    srcSet;
//	uint32_t           srcBinding;
//	uint32_t           srcArrayElement;
//	VkDescriptorSet    dstSet;
//	uint32_t           dstBinding;
//	uint32_t           dstArrayElement;
//	uint32_t           descriptorCount;
//};

struct FramebufferCreateInfo : public ::VkFramebufferCreateInfo
{
	FramebufferCreateInfo()
	{
		sType           = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
		pNext           = nullptr;
		flags           = 0;
		renderPass      = VK_NULL_HANDLE;
		attachmentCount = 0;
		pAttachments    = nullptr;
		width           = 0;
		height          = 0;
		layers          = 0;
	}

	void SetAttachments(std::vector<::VkImageView> const& attachments)
	{
		attachmentCount = static_cast<std::uint32_t>(attachments.size());
		pAttachments    = attachments.data();
	}

	void SetExtent(::VkExtent2D const& extent)
	{
		width  = extent.width;
		height = extent.height;
	}
};

//struct AttachmentDescription
//{
//	VkAttachmentDescriptionFlags    flags;
//	VkFormat                        format;
//	VkSampleCountFlagBits           samples;
//	VkAttachmentLoadOp              loadOp;
//	VkAttachmentStoreOp             storeOp;
//	VkAttachmentLoadOp              stencilLoadOp;
//	VkAttachmentStoreOp             stencilStoreOp;
//	VkImageLayout                   initialLayout;
//	VkImageLayout                   finalLayout;
//};
//
//struct AttachmentReference
//{
//	uint32_t         attachment;
//	VkImageLayout    layout;
//};

struct SubpassDescription : public ::VkSubpassDescription
{
	SubpassDescription()
	{
		flags                   = 0;
		pipelineBindPoint       = VK_PIPELINE_BIND_POINT_GRAPHICS;
		inputAttachmentCount    = 0;
		pInputAttachments       = nullptr;
		colorAttachmentCount    = 0;
		pColorAttachments       = nullptr;
		pResolveAttachments     = nullptr;
		pDepthStencilAttachment = nullptr;
		preserveAttachmentCount = 0;
		pPreserveAttachments    = nullptr;
	}

	void SetInputAttachments(::VkAttachmentReference const* input_attachment)
	{
		inputAttachmentCount = input_attachment ? 1 : 0;
		pInputAttachments    = input_attachment;
	}

	void SetColorAttachments(::VkAttachmentReference const* color_attachment)
	{
		colorAttachmentCount = color_attachment ? 1 : 0;
		pColorAttachments    = color_attachment;
	}

	void SetResolveAttachments(::VkAttachmentReference const* resolve_attachments)
	{
		pResolveAttachments = resolve_attachments;
	}

	void SetDepthStencilAttachment(::VkAttachmentReference const* depth_stencil_attachment)
	{
		pDepthStencilAttachment = depth_stencil_attachment;
	}

	void SetPreserveAttachments(std::uint32_t const* preserve_attachment)
	{
		preserveAttachmentCount = preserve_attachment ? 1 : 0;
		pPreserveAttachments    = preserve_attachment;
	}
};

struct SubpassDependency : public ::VkSubpassDependency
{
	SubpassDependency()
	{
		srcSubpass      = 0;
		dstSubpass      = 0;
		srcStageMask    = 0;
		dstStageMask    = 0;
		srcAccessMask   = 0;
		dstAccessMask   = 0;
		dependencyFlags = 0;
	}
};

struct RenderPassCreateInfo : public ::VkRenderPassCreateInfo
{
	RenderPassCreateInfo()
	{
		sType           = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
		pNext           = nullptr;
		flags           = 0;
		attachmentCount = 0;
		pAttachments    = nullptr;
		subpassCount    = 0;
		pSubpasses      = nullptr;
		dependencyCount = 0;
		pDependencies   = nullptr;
	}

	void SetAttachments(std::vector<::VkAttachmentDescription> const& attachments)
	{
		attachmentCount = static_cast<std::uint32_t>(attachments.size());
		pAttachments    = attachments.data();
	}

	void SetSubpasses(::VkSubpassDescription const* subpass)
	{
		subpassCount = subpass ? 1 : 0;
		pSubpasses   = subpass;
	}

	void SetDependencies(::VkSubpassDependency const* dependency)
	{
		dependencyCount = dependency ? 1 : 0;
		pDependencies   = dependency;
	}
};

struct CommandPoolCreateInfo : public ::VkCommandPoolCreateInfo
{
	CommandPoolCreateInfo()
	{
		sType            = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
		pNext            = nullptr;
		flags            = 0;
		queueFamilyIndex = 0;
	}
};

struct CommandBufferAllocateInfo : public ::VkCommandBufferAllocateInfo
{
	CommandBufferAllocateInfo()
	{
		sType              = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		pNext              = nullptr;
		commandPool        = VK_NULL_HANDLE;
		level              = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		commandBufferCount = 0;
	}
};

//struct CommandBufferInheritanceInfo
//{
//	VkStructureType                  sType;
//	const void* pNext;
//	VkRenderPass                     renderPass;
//	uint32_t                         subpass;
//	VkFramebuffer                    framebuffer;
//	VkBool32                         occlusionQueryEnable;
//	VkQueryControlFlags              queryFlags;
//	VkQueryPipelineStatisticFlags    pipelineStatistics;
//};

struct CommandBufferBeginInfo : public ::VkCommandBufferBeginInfo
{
	CommandBufferBeginInfo()
	{
		sType            = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		pNext            = nullptr;
		flags            = 0;
		pInheritanceInfo = nullptr;
	}
};

//struct BufferCopy
//{
//	VkDeviceSize    srcOffset;
//	VkDeviceSize    dstOffset;
//	VkDeviceSize    size;
//};
//
//struct ImageSubresourceLayers
//{
//	VkImageAspectFlags    aspectMask;
//	uint32_t              mipLevel;
//	uint32_t              baseArrayLayer;
//	uint32_t              layerCount;
//};
//
//struct ImageCopy
//{
//	VkImageSubresourceLayers    srcSubresource;
//	VkOffset3D                  srcOffset;
//	VkImageSubresourceLayers    dstSubresource;
//	VkOffset3D                  dstOffset;
//	VkExtent3D                  extent;
//};
//
//struct ImageBlit
//{
//	VkImageSubresourceLayers    srcSubresource;
//	VkOffset3D                  srcOffsets[2];
//	VkImageSubresourceLayers    dstSubresource;
//	VkOffset3D                  dstOffsets[2];
//};
//
//struct BufferImageCopy
//{
//	VkDeviceSize                bufferOffset;
//	uint32_t                    bufferRowLength;
//	uint32_t                    bufferImageHeight;
//	VkImageSubresourceLayers    imageSubresource;
//	VkOffset3D                  imageOffset;
//	VkExtent3D                  imageExtent;
//};
//
//struct ClearDepthStencilValue
//{
//	float       depth;
//	uint32_t    stencil;
//};
//
//struct ClearAttachment
//{
//	VkImageAspectFlags    aspectMask;
//	uint32_t              colorAttachment;
//	VkClearValue          clearValue;
//};
//
//struct ClearRect
//{
//	VkRect2D    rect;
//	uint32_t    baseArrayLayer;
//	uint32_t    layerCount;
//};
//
//struct ImageResolve
//{
//	VkImageSubresourceLayers    srcSubresource;
//	VkOffset3D                  srcOffset;
//	VkImageSubresourceLayers    dstSubresource;
//	VkOffset3D                  dstOffset;
//	VkExtent3D                  extent;
//};
//
//struct MemoryBarrier
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkAccessFlags      srcAccessMask;
//	VkAccessFlags      dstAccessMask;
//};
//
//struct BufferMemoryBarrier
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkAccessFlags      srcAccessMask;
//	VkAccessFlags      dstAccessMask;
//	uint32_t           srcQueueFamilyIndex;
//	uint32_t           dstQueueFamilyIndex;
//	VkBuffer           buffer;
//	VkDeviceSize       offset;
//	VkDeviceSize       size;
//};
//
//struct ImageMemoryBarrier
//{
//	VkStructureType            sType;
//	const void* pNext;
//	VkAccessFlags              srcAccessMask;
//	VkAccessFlags              dstAccessMask;
//	VkImageLayout              oldLayout;
//	VkImageLayout              newLayout;
//	uint32_t                   srcQueueFamilyIndex;
//	uint32_t                   dstQueueFamilyIndex;
//	VkImage                    image;
//	VkImageSubresourceRange    subresourceRange;
//};

struct RenderPassBeginInfo : public ::VkRenderPassBeginInfo
{
	RenderPassBeginInfo()
	{
		sType           = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		pNext           = nullptr;
		renderPass      = VK_NULL_HANDLE;
		framebuffer     = VK_NULL_HANDLE;
		renderArea      = Rect2D();
		clearValueCount = 0;
		pClearValues    = nullptr;
	}

	template <std::size_t N>
	void SetClearValues(::VkClearValue const (&clear_values)[N])
	{
		clearValueCount     = N;
		pClearValues        = clear_values;
	}
};

//struct DispatchIndirectCommand
//{
//	uint32_t    x;
//	uint32_t    y;
//	uint32_t    z;
//};
//
//struct DrawIndexedIndirectCommand
//{
//	uint32_t    indexCount;
//	uint32_t    instanceCount;
//	uint32_t    firstIndex;
//	int32_t     vertexOffset;
//	uint32_t    firstInstance;
//};
//
//struct DrawIndirectCommand
//{
//	uint32_t    vertexCount;
//	uint32_t    instanceCount;
//	uint32_t    firstVertex;
//	uint32_t    firstInstance;
//};
//
//struct BaseOutStructure
//{
//	VkStructureType               sType;
//	struct VkBaseOutStructure* pNext;
//};
//
//struct BaseInStructure
//{
//	VkStructureType                    sType;
//	const struct VkBaseInStructure* pNext;
//};
//
//struct PhysicalDeviceSubgroupProperties
//{
//	VkStructureType           sType;
//	void* pNext;
//	uint32_t                  subgroupSize;
//	VkShaderStageFlags        supportedStages;
//	VkSubgroupFeatureFlags    supportedOperations;
//	VkBool32                  quadOperationsInAllStages;
//};
//
//struct BindBufferMemoryInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBuffer           buffer;
//	VkDeviceMemory     memory;
//	VkDeviceSize       memoryOffset;
//};
//
//struct BindImageMemoryInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkImage            image;
//	VkDeviceMemory     memory;
//	VkDeviceSize       memoryOffset;
//};
//
//struct PhysicalDevice16BitStorageFeatures
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           storageBuffer16BitAccess;
//	VkBool32           uniformAndStorageBuffer16BitAccess;
//	VkBool32           storagePushConstant16;
//	VkBool32           storageInputOutput16;
//};
//
//struct MemoryDedicatedRequirements
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           prefersDedicatedAllocation;
//	VkBool32           requiresDedicatedAllocation;
//};
//
//struct MemoryDedicatedAllocateInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkImage            image;
//	VkBuffer           buffer;
//};
//
//struct MemoryAllocateFlagsInfo
//{
//	VkStructureType          sType;
//	const void* pNext;
//	VkMemoryAllocateFlags    flags;
//	uint32_t                 deviceMask;
//};
//
//struct DeviceGroupRenderPassBeginInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           deviceMask;
//	uint32_t           deviceRenderAreaCount;
//	const VkRect2D* pDeviceRenderAreas;
//};
//
//struct DeviceGroupCommandBufferBeginInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           deviceMask;
//};
//
//struct DeviceGroupSubmitInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           waitSemaphoreCount;
//	const uint32_t* pWaitSemaphoreDeviceIndices;
//	uint32_t           commandBufferCount;
//	const uint32_t* pCommandBufferDeviceMasks;
//	uint32_t           signalSemaphoreCount;
//	const uint32_t* pSignalSemaphoreDeviceIndices;
//};
//
//struct DeviceGroupBindSparseInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           resourceDeviceIndex;
//	uint32_t           memoryDeviceIndex;
//};
//
//struct BindBufferMemoryDeviceGroupInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           deviceIndexCount;
//	const uint32_t* pDeviceIndices;
//};
//
//struct BindImageMemoryDeviceGroupInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           deviceIndexCount;
//	const uint32_t* pDeviceIndices;
//	uint32_t           splitInstanceBindRegionCount;
//	const VkRect2D* pSplitInstanceBindRegions;
//};
//
//struct PhysicalDeviceGroupProperties
//{
//	VkStructureType     sType;
//	void* pNext;
//	uint32_t            physicalDeviceCount;
//	VkPhysicalDevice    physicalDevices[VK_MAX_DEVICE_GROUP_SIZE];
//	VkBool32            subsetAllocation;
//};
//
//struct DeviceGroupDeviceCreateInfo
//{
//	VkStructureType            sType;
//	const void* pNext;
//	uint32_t                   physicalDeviceCount;
//	const VkPhysicalDevice* pPhysicalDevices;
//};
//
//struct BufferMemoryRequirementsInfo2
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBuffer           buffer;
//};
//
//struct ImageMemoryRequirementsInfo2
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkImage            image;
//};
//
//struct ImageSparseMemoryRequirementsInfo2
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkImage            image;
//};
//
//struct MemoryRequirements2
//{
//	VkStructureType         sType;
//	void* pNext;
//	VkMemoryRequirements    memoryRequirements;
//};
//
//struct SparseImageMemoryRequirements2
//{
//	VkStructureType                    sType;
//	void* pNext;
//	VkSparseImageMemoryRequirements    memoryRequirements;
//};
//
//struct PhysicalDeviceFeatures2
//{
//	VkStructureType             sType;
//	void* pNext;
//	VkPhysicalDeviceFeatures    features;
//};
//
//struct PhysicalDeviceProperties2
//{
//	VkStructureType               sType;
//	void* pNext;
//	VkPhysicalDeviceProperties    properties;
//};
//
//struct FormatProperties2
//{
//	VkStructureType       sType;
//	void* pNext;
//	VkFormatProperties    formatProperties;
//};
//
//struct ImageFormatProperties2
//{
//	VkStructureType            sType;
//	void* pNext;
//	VkImageFormatProperties    imageFormatProperties;
//};
//
//struct PhysicalDeviceImageFormatInfo2
//{
//	VkStructureType       sType;
//	const void* pNext;
//	VkFormat              format;
//	VkImageType           type;
//	VkImageTiling         tiling;
//	VkImageUsageFlags     usage;
//	VkImageCreateFlags    flags;
//};
//
//struct QueueFamilyProperties2
//{
//	VkStructureType            sType;
//	void* pNext;
//	VkQueueFamilyProperties    queueFamilyProperties;
//};
//
//struct PhysicalDeviceMemoryProperties2
//{
//	VkStructureType                     sType;
//	void* pNext;
//	VkPhysicalDeviceMemoryProperties    memoryProperties;
//};
//
//struct SparseImageFormatProperties2
//{
//	VkStructureType                  sType;
//	void* pNext;
//	VkSparseImageFormatProperties    properties;
//};
//
//struct PhysicalDeviceSparseImageFormatInfo2
//{
//	VkStructureType          sType;
//	const void* pNext;
//	VkFormat                 format;
//	VkImageType              type;
//	VkSampleCountFlagBits    samples;
//	VkImageUsageFlags        usage;
//	VkImageTiling            tiling;
//};
//
//struct PhysicalDevicePointClippingProperties
//{
//	VkStructureType            sType;
//	void* pNext;
//	VkPointClippingBehavior    pointClippingBehavior;
//};
//
//struct InputAttachmentAspectReference
//{
//	uint32_t              subpass;
//	uint32_t              inputAttachmentIndex;
//	VkImageAspectFlags    aspectMask;
//};
//
//struct RenderPassInputAttachmentAspectCreateInfo
//{
//	VkStructureType                            sType;
//	const void* pNext;
//	uint32_t                                   aspectReferenceCount;
//	const VkInputAttachmentAspectReference* pAspectReferences;
//};
//
//struct ImageViewUsageCreateInfo
//{
//	VkStructureType      sType;
//	const void* pNext;
//	VkImageUsageFlags    usage;
//};
//
//struct PipelineTessellationDomainOriginStateCreateInfo
//{
//	VkStructureType               sType;
//	const void* pNext;
//	VkTessellationDomainOrigin    domainOrigin;
//};
//
//struct RenderPassMultiviewCreateInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           subpassCount;
//	const uint32_t* pViewMasks;
//	uint32_t           dependencyCount;
//	const int32_t* pViewOffsets;
//	uint32_t           correlationMaskCount;
//	const uint32_t* pCorrelationMasks;
//};
//
//struct PhysicalDeviceMultiviewFeatures
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           multiview;
//	VkBool32           multiviewGeometryShader;
//	VkBool32           multiviewTessellationShader;
//};
//
//struct PhysicalDeviceMultiviewProperties
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           maxMultiviewViewCount;
//	uint32_t           maxMultiviewInstanceIndex;
//};
//
//struct PhysicalDeviceVariablePointersFeatures
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           variablePointersStorageBuffer;
//	VkBool32           variablePointers;
//};
//
//struct PhysicalDeviceProtectedMemoryFeatures
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           protectedMemory;
//};
//
//struct PhysicalDeviceProtectedMemoryProperties
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           protectedNoFault;
//};
//
//struct DeviceQueueInfo2
//{
//	VkStructureType             sType;
//	const void* pNext;
//	VkDeviceQueueCreateFlags    flags;
//	uint32_t                    queueFamilyIndex;
//	uint32_t                    queueIndex;
//};
//
//struct ProtectedSubmitInfo
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBool32           protectedSubmit;
//};
//
//struct SamplerYcbcrConversionCreateInfo
//{
//	VkStructureType                  sType;
//	const void* pNext;
//	VkFormat                         format;
//	VkSamplerYcbcrModelConversion    ycbcrModel;
//	VkSamplerYcbcrRange              ycbcrRange;
//	VkComponentMapping               components;
//	VkChromaLocation                 xChromaOffset;
//	VkChromaLocation                 yChromaOffset;
//	VkFilter                         chromaFilter;
//	VkBool32                         forceExplicitReconstruction;
//};
//
//struct SamplerYcbcrConversionInfo
//{
//	VkStructureType             sType;
//	const void* pNext;
//	VkSamplerYcbcrConversion    conversion;
//};
//
//struct BindImagePlaneMemoryInfo
//{
//	VkStructureType          sType;
//	const void* pNext;
//	VkImageAspectFlagBits    planeAspect;
//};
//
//struct ImagePlaneMemoryRequirementsInfo
//{
//	VkStructureType          sType;
//	const void* pNext;
//	VkImageAspectFlagBits    planeAspect;
//};
//
//struct PhysicalDeviceSamplerYcbcrConversionFeatures
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           samplerYcbcrConversion;
//};
//
//struct SamplerYcbcrConversionImageFormatProperties
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           combinedImageSamplerDescriptorCount;
//};
//
//struct DescriptorUpdateTemplateEntry
//{
//	uint32_t            dstBinding;
//	uint32_t            dstArrayElement;
//	uint32_t            descriptorCount;
//	VkDescriptorType    descriptorType;
//	size_t              offset;
//	size_t              stride;
//};
//
//struct DescriptorUpdateTemplateCreateInfo
//{
//	VkStructureType                           sType;
//	const void* pNext;
//	VkDescriptorUpdateTemplateCreateFlags     flags;
//	uint32_t                                  descriptorUpdateEntryCount;
//	const VkDescriptorUpdateTemplateEntry* pDescriptorUpdateEntries;
//	VkDescriptorUpdateTemplateType            templateType;
//	VkDescriptorSetLayout                     descriptorSetLayout;
//	VkPipelineBindPoint                       pipelineBindPoint;
//	VkPipelineLayout                          pipelineLayout;
//	uint32_t                                  set;
//};
//
//struct ExternalMemoryProperties
//{
//	VkExternalMemoryFeatureFlags       externalMemoryFeatures;
//	VkExternalMemoryHandleTypeFlags    exportFromImportedHandleTypes;
//	VkExternalMemoryHandleTypeFlags    compatibleHandleTypes;
//};
//
//struct PhysicalDeviceExternalImageFormatInfo
//{
//	VkStructureType                       sType;
//	const void* pNext;
//	VkExternalMemoryHandleTypeFlagBits    handleType;
//};
//
//struct ExternalImageFormatProperties
//{
//	VkStructureType               sType;
//	void* pNext;
//	VkExternalMemoryProperties    externalMemoryProperties;
//};
//
//struct PhysicalDeviceExternalBufferInfo
//{
//	VkStructureType                       sType;
//	const void* pNext;
//	VkBufferCreateFlags                   flags;
//	VkBufferUsageFlags                    usage;
//	VkExternalMemoryHandleTypeFlagBits    handleType;
//};
//
//struct ExternalBufferProperties
//{
//	VkStructureType               sType;
//	void* pNext;
//	VkExternalMemoryProperties    externalMemoryProperties;
//};
//
//struct PhysicalDeviceIDProperties
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint8_t            deviceUUID[VK_UUID_SIZE];
//	uint8_t            driverUUID[VK_UUID_SIZE];
//	uint8_t            deviceLUID[VK_LUID_SIZE];
//	uint32_t           deviceNodeMask;
//	VkBool32           deviceLUIDValid;
//};
//
//struct ExternalMemoryImageCreateInfo
//{
//	VkStructureType                    sType;
//	const void* pNext;
//	VkExternalMemoryHandleTypeFlags    handleTypes;
//};
//
//struct ExternalMemoryBufferCreateInfo
//{
//	VkStructureType                    sType;
//	const void* pNext;
//	VkExternalMemoryHandleTypeFlags    handleTypes;
//};
//
//struct ExportMemoryAllocateInfo
//{
//	VkStructureType                    sType;
//	const void* pNext;
//	VkExternalMemoryHandleTypeFlags    handleTypes;
//};
//
//struct PhysicalDeviceExternalFenceInfo
//{
//	VkStructureType                      sType;
//	const void* pNext;
//	VkExternalFenceHandleTypeFlagBits    handleType;
//};
//
//struct ExternalFenceProperties
//{
//	VkStructureType                   sType;
//	void* pNext;
//	VkExternalFenceHandleTypeFlags    exportFromImportedHandleTypes;
//	VkExternalFenceHandleTypeFlags    compatibleHandleTypes;
//	VkExternalFenceFeatureFlags       externalFenceFeatures;
//};
//
//struct ExportFenceCreateInfo
//{
//	VkStructureType                   sType;
//	const void* pNext;
//	VkExternalFenceHandleTypeFlags    handleTypes;
//};
//
//struct ExportSemaphoreCreateInfo
//{
//	VkStructureType                       sType;
//	const void* pNext;
//	VkExternalSemaphoreHandleTypeFlags    handleTypes;
//};
//
//struct PhysicalDeviceExternalSemaphoreInfo
//{
//	VkStructureType                          sType;
//	const void* pNext;
//	VkExternalSemaphoreHandleTypeFlagBits    handleType;
//};
//
//struct ExternalSemaphoreProperties
//{
//	VkStructureType                       sType;
//	void* pNext;
//	VkExternalSemaphoreHandleTypeFlags    exportFromImportedHandleTypes;
//	VkExternalSemaphoreHandleTypeFlags    compatibleHandleTypes;
//	VkExternalSemaphoreFeatureFlags       externalSemaphoreFeatures;
//};
//
//struct PhysicalDeviceMaintenance3Properties
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           maxPerSetDescriptors;
//	VkDeviceSize       maxMemoryAllocationSize;
//};
//
//struct DescriptorSetLayoutSupport
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           supported;
//};
//
//struct PhysicalDeviceShaderDrawParametersFeatures
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           shaderDrawParameters;
//};
//
//struct SurfaceCapabilitiesKHR
//{
//	uint32_t                         minImageCount;
//	uint32_t                         maxImageCount;
//	VkExtent2D                       currentExtent;
//	VkExtent2D                       minImageExtent;
//	VkExtent2D                       maxImageExtent;
//	uint32_t                         maxImageArrayLayers;
//	VkSurfaceTransformFlagsKHR       supportedTransforms;
//	VkSurfaceTransformFlagBitsKHR    currentTransform;
//	VkCompositeAlphaFlagsKHR         supportedCompositeAlpha;
//	VkImageUsageFlags                supportedUsageFlags;
//};
//
//struct SurfaceFormatKHR
//{
//	VkFormat           format;
//	VkColorSpaceKHR    colorSpace;
//};

struct SwapchainCreateInfoKHR : public ::VkSwapchainCreateInfoKHR
{
	SwapchainCreateInfoKHR()
	{
		sType                 = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
		pNext                 = nullptr;
		flags                 = 0;
		surface               = VK_NULL_HANDLE;
		minImageCount         = 0;
		imageFormat           = VK_FORMAT_UNDEFINED;
		imageColorSpace       = VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
		imageExtent           = Extent2D();
		imageArrayLayers      = 0;
		imageUsage            = 0;
		imageSharingMode      = VK_SHARING_MODE_EXCLUSIVE;
		queueFamilyIndexCount = 0;
		pQueueFamilyIndices   = nullptr;
		preTransform          = VkSurfaceTransformFlagBitsKHR(0);
		compositeAlpha        = VkCompositeAlphaFlagBitsKHR(0);
		presentMode           = VK_PRESENT_MODE_IMMEDIATE_KHR;
		clipped               = VK_FALSE;
		oldSwapchain          = VK_NULL_HANDLE;
	}

	void SetQueueFamilyIndices(std::uint32_t const* queue_family_index)
	{
		queueFamilyIndexCount = queue_family_index ? 1 : 0;
		pQueueFamilyIndices   = queue_family_index;
	}

	template <std::size_t N>
	void SetQueueFamilyIndices(std::uint32_t const (&queue_family_indices)[N])
	{
		queueFamilyIndexCount = N;
		pQueueFamilyIndices   = queue_family_indices;
	}
};

struct PresentInfoKHR : public ::VkPresentInfoKHR
{
	PresentInfoKHR()
	{
		sType              = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
		pNext              = nullptr;
		waitSemaphoreCount = 0;
		pWaitSemaphores    = nullptr;
		swapchainCount     = 0;
		pSwapchains        = nullptr;
		pImageIndices      = nullptr;
		pResults           = nullptr;
	}

	void SetWaitSemaphores(::VkSemaphore const* wait_semaphore)
	{
		waitSemaphoreCount = wait_semaphore ? 1 : 0;
		pWaitSemaphores    = wait_semaphore;
	}

	void SetSwapchains(::VkSwapchainKHR const* swapchain)
	{
		swapchainCount = swapchain ? 1 : 0;
		pSwapchains    = swapchain;
	}
};

//struct ImageSwapchainCreateInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkSwapchainKHR     swapchain;
//};
//
//struct BindImageMemorySwapchainInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkSwapchainKHR     swapchain;
//	uint32_t           imageIndex;
//};
//
//struct AcquireNextImageInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkSwapchainKHR     swapchain;
//	uint64_t           timeout;
//	VkSemaphore        semaphore;
//	VkFence            fence;
//	uint32_t           deviceMask;
//};
//
//struct DeviceGroupPresentCapabilitiesKHR
//{
//	VkStructureType                     sType;
//	const void* pNext;
//	uint32_t                            presentMask[VK_MAX_DEVICE_GROUP_SIZE];
//	VkDeviceGroupPresentModeFlagsKHR    modes;
//};
//
//struct DeviceGroupPresentInfoKHR
//{
//	VkStructureType                        sType;
//	const void* pNext;
//	uint32_t                               swapchainCount;
//	const uint32_t* pDeviceMasks;
//	VkDeviceGroupPresentModeFlagBitsKHR    mode;
//};
//
//struct DeviceGroupSwapchainCreateInfoKHR
//{
//	VkStructureType                     sType;
//	const void* pNext;
//	VkDeviceGroupPresentModeFlagsKHR    modes;
//};
//
//struct DisplayPropertiesKHR
//{
//	VkDisplayKHR                  display;
//	const char* displayName;
//	VkExtent2D                    physicalDimensions;
//	VkExtent2D                    physicalResolution;
//	VkSurfaceTransformFlagsKHR    supportedTransforms;
//	VkBool32                      planeReorderPossible;
//	VkBool32                      persistentContent;
//};
//
//struct DisplayModeParametersKHR
//{
//	VkExtent2D    visibleRegion;
//	uint32_t      refreshRate;
//};
//
//struct DisplayModePropertiesKHR
//{
//	VkDisplayModeKHR              displayMode;
//	VkDisplayModeParametersKHR    parameters;
//};
//
//struct DisplayModeCreateInfoKHR
//{
//	VkStructureType                sType;
//	const void* pNext;
//	VkDisplayModeCreateFlagsKHR    flags;
//	VkDisplayModeParametersKHR     parameters;
//};
//
//struct DisplayPlaneCapabilitiesKHR
//{
//	VkDisplayPlaneAlphaFlagsKHR    supportedAlpha;
//	VkOffset2D                     minSrcPosition;
//	VkOffset2D                     maxSrcPosition;
//	VkExtent2D                     minSrcExtent;
//	VkExtent2D                     maxSrcExtent;
//	VkOffset2D                     minDstPosition;
//	VkOffset2D                     maxDstPosition;
//	VkExtent2D                     minDstExtent;
//	VkExtent2D                     maxDstExtent;
//};
//
//struct DisplayPlanePropertiesKHR
//{
//	VkDisplayKHR    currentDisplay;
//	uint32_t        currentStackIndex;
//};
//
//struct DisplaySurfaceCreateInfoKHR
//{
//	VkStructureType                   sType;
//	const void* pNext;
//	VkDisplaySurfaceCreateFlagsKHR    flags;
//	VkDisplayModeKHR                  displayMode;
//	uint32_t                          planeIndex;
//	uint32_t                          planeStackIndex;
//	VkSurfaceTransformFlagBitsKHR     transform;
//	float                             globalAlpha;
//	VkDisplayPlaneAlphaFlagBitsKHR    alphaMode;
//	VkExtent2D                        imageExtent;
//};
//
//struct DisplayPresentInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkRect2D           srcRect;
//	VkRect2D           dstRect;
//	VkBool32           persistent;
//};
//
//struct ImportMemoryFdInfoKHR
//{
//	VkStructureType                       sType;
//	const void* pNext;
//	VkExternalMemoryHandleTypeFlagBits    handleType;
//	int                                   fd;
//};
//
//struct MemoryFdPropertiesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           memoryTypeBits;
//};
//
//struct MemoryGetFdInfoKHR
//{
//	VkStructureType                       sType;
//	const void* pNext;
//	VkDeviceMemory                        memory;
//	VkExternalMemoryHandleTypeFlagBits    handleType;
//};
//
//struct ImportSemaphoreFdInfoKHR
//{
//	VkStructureType                          sType;
//	const void* pNext;
//	VkSemaphore                              semaphore;
//	VkSemaphoreImportFlags                   flags;
//	VkExternalSemaphoreHandleTypeFlagBits    handleType;
//	int                                      fd;
//};
//
//struct SemaphoreGetFdInfoKHR
//{
//	VkStructureType                          sType;
//	const void* pNext;
//	VkSemaphore                              semaphore;
//	VkExternalSemaphoreHandleTypeFlagBits    handleType;
//};
//
//struct PhysicalDevicePushDescriptorPropertiesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           maxPushDescriptors;
//};
//
//struct PhysicalDeviceShaderFloat16Int8FeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           shaderFloat16;
//	VkBool32           shaderInt8;
//};
//
//struct RectLayerKHR
//{
//	VkOffset2D    offset;
//	VkExtent2D    extent;
//	uint32_t      layer;
//};
//
//struct PresentRegionKHR
//{
//	uint32_t                 rectangleCount;
//	const VkRectLayerKHR* pRectangles;
//};
//
//struct PresentRegionsKHR
//{
//	VkStructureType              sType;
//	const void* pNext;
//	uint32_t                     swapchainCount;
//	const VkPresentRegionKHR* pRegions;
//};
//
//struct PhysicalDeviceImagelessFramebufferFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           imagelessFramebuffer;
//};
//
//struct FramebufferAttachmentImageInfoKHR
//{
//	VkStructureType       sType;
//	const void* pNext;
//	VkImageCreateFlags    flags;
//	VkImageUsageFlags     usage;
//	uint32_t              width;
//	uint32_t              height;
//	uint32_t              layerCount;
//	uint32_t              viewFormatCount;
//	const VkFormat* pViewFormats;
//};
//
//struct FramebufferAttachmentsCreateInfoKHR
//{
//	VkStructureType                               sType;
//	const void* pNext;
//	uint32_t                                      attachmentImageInfoCount;
//	const VkFramebufferAttachmentImageInfoKHR* pAttachmentImageInfos;
//};
//
//struct RenderPassAttachmentBeginInfoKHR
//{
//	VkStructureType       sType;
//	const void* pNext;
//	uint32_t              attachmentCount;
//	const VkImageView* pAttachments;
//};
//
//struct AttachmentDescription2KHR
//{
//	VkStructureType                 sType;
//	const void* pNext;
//	VkAttachmentDescriptionFlags    flags;
//	VkFormat                        format;
//	VkSampleCountFlagBits           samples;
//	VkAttachmentLoadOp              loadOp;
//	VkAttachmentStoreOp             storeOp;
//	VkAttachmentLoadOp              stencilLoadOp;
//	VkAttachmentStoreOp             stencilStoreOp;
//	VkImageLayout                   initialLayout;
//	VkImageLayout                   finalLayout;
//};
//
//struct AttachmentReference2KHR
//{
//	VkStructureType       sType;
//	const void* pNext;
//	uint32_t              attachment;
//	VkImageLayout         layout;
//	VkImageAspectFlags    aspectMask;
//};
//
//struct SubpassDescription2KHR
//{
//	VkStructureType                     sType;
//	const void* pNext;
//	VkSubpassDescriptionFlags           flags;
//	VkPipelineBindPoint                 pipelineBindPoint;
//	uint32_t                            viewMask;
//	uint32_t                            inputAttachmentCount;
//	const VkAttachmentReference2KHR* pInputAttachments;
//	uint32_t                            colorAttachmentCount;
//	const VkAttachmentReference2KHR* pColorAttachments;
//	const VkAttachmentReference2KHR* pResolveAttachments;
//	const VkAttachmentReference2KHR* pDepthStencilAttachment;
//	uint32_t                            preserveAttachmentCount;
//	const uint32_t* pPreserveAttachments;
//};
//
//struct SubpassDependency2KHR
//{
//	VkStructureType         sType;
//	const void* pNext;
//	uint32_t                srcSubpass;
//	uint32_t                dstSubpass;
//	VkPipelineStageFlags    srcStageMask;
//	VkPipelineStageFlags    dstStageMask;
//	VkAccessFlags           srcAccessMask;
//	VkAccessFlags           dstAccessMask;
//	VkDependencyFlags       dependencyFlags;
//	int32_t                 viewOffset;
//};
//
//struct RenderPassCreateInfo2KHR
//{
//	VkStructureType                       sType;
//	const void* pNext;
//	VkRenderPassCreateFlags               flags;
//	uint32_t                              attachmentCount;
//	const VkAttachmentDescription2KHR* pAttachments;
//	uint32_t                              subpassCount;
//	const VkSubpassDescription2KHR* pSubpasses;
//	uint32_t                              dependencyCount;
//	const VkSubpassDependency2KHR* pDependencies;
//	uint32_t                              correlatedViewMaskCount;
//	const uint32_t* pCorrelatedViewMasks;
//};
//
//struct SubpassBeginInfoKHR
//{
//	VkStructureType      sType;
//	const void* pNext;
//	VkSubpassContents    contents;
//};
//
//struct SubpassEndInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//};
//
//struct SharedPresentSurfaceCapabilitiesKHR
//{
//	VkStructureType      sType;
//	void* pNext;
//	VkImageUsageFlags    sharedPresentSupportedUsageFlags;
//};
//
//struct ImportFenceFdInfoKHR
//{
//	VkStructureType                      sType;
//	const void* pNext;
//	VkFence                              fence;
//	VkFenceImportFlags                   flags;
//	VkExternalFenceHandleTypeFlagBits    handleType;
//	int                                  fd;
//};
//
//struct FenceGetFdInfoKHR
//{
//	VkStructureType                      sType;
//	const void* pNext;
//	VkFence                              fence;
//	VkExternalFenceHandleTypeFlagBits    handleType;
//};
//
//struct PhysicalDevicePerformanceQueryFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           performanceCounterQueryPools;
//	VkBool32           performanceCounterMultipleQueryPools;
//};
//
//struct PhysicalDevicePerformanceQueryPropertiesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           allowCommandBufferQueryCopies;
//};
//
//struct PerformanceCounterKHR
//{
//	VkStructureType                   sType;
//	const void* pNext;
//	VkPerformanceCounterUnitKHR       unit;
//	VkPerformanceCounterScopeKHR      scope;
//	VkPerformanceCounterStorageKHR    storage;
//	uint8_t                           uuid[VK_UUID_SIZE];
//};
//
//struct PerformanceCounterDescriptionKHR
//{
//	VkStructureType                            sType;
//	const void* pNext;
//	VkPerformanceCounterDescriptionFlagsKHR    flags;
//	char                                       name[VK_MAX_DESCRIPTION_SIZE];
//	char                                       category[VK_MAX_DESCRIPTION_SIZE];
//	char                                       description[VK_MAX_DESCRIPTION_SIZE];
//};
//
//struct QueryPoolPerformanceCreateInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           queueFamilyIndex;
//	uint32_t           counterIndexCount;
//	const uint32_t* pCounterIndices;
//};
//
//struct AcquireProfilingLockInfoKHR
//{
//	VkStructureType                   sType;
//	const void* pNext;
//	VkAcquireProfilingLockFlagsKHR    flags;
//	uint64_t                          timeout;
//};
//
//struct PerformanceQuerySubmitInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           counterPassIndex;
//};
//
//struct PhysicalDeviceSurfaceInfo2KHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkSurfaceKHR       surface;
//};
//
//struct SurfaceCapabilities2KHR
//{
//	VkStructureType             sType;
//	void* pNext;
//	VkSurfaceCapabilitiesKHR    surfaceCapabilities;
//};
//
//struct SurfaceFormat2KHR
//{
//	VkStructureType       sType;
//	void* pNext;
//	VkSurfaceFormatKHR    surfaceFormat;
//};
//
//struct DisplayProperties2KHR
//{
//	VkStructureType           sType;
//	void* pNext;
//	VkDisplayPropertiesKHR    displayProperties;
//};
//
//struct DisplayPlaneProperties2KHR
//{
//	VkStructureType                sType;
//	void* pNext;
//	VkDisplayPlanePropertiesKHR    displayPlaneProperties;
//};
//
//struct DisplayModeProperties2KHR
//{
//	VkStructureType               sType;
//	void* pNext;
//	VkDisplayModePropertiesKHR    displayModeProperties;
//};
//
//struct DisplayPlaneInfo2KHR
//{
//	VkStructureType     sType;
//	const void* pNext;
//	VkDisplayModeKHR    mode;
//	uint32_t            planeIndex;
//};
//
//struct DisplayPlaneCapabilities2KHR
//{
//	VkStructureType                  sType;
//	void* pNext;
//	VkDisplayPlaneCapabilitiesKHR    capabilities;
//};
//
//struct ImageFormatListCreateInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           viewFormatCount;
//	const VkFormat* pViewFormats;
//};
//
//struct PhysicalDeviceShaderSubgroupExtendedTypesFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           shaderSubgroupExtendedTypes;
//};
//
//struct PhysicalDevice8BitStorageFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           storageBuffer8BitAccess;
//	VkBool32           uniformAndStorageBuffer8BitAccess;
//	VkBool32           storagePushConstant8;
//};
//
//struct PhysicalDeviceShaderAtomicInt64FeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           shaderBufferInt64Atomics;
//	VkBool32           shaderSharedInt64Atomics;
//};
//
//struct PhysicalDeviceShaderClockFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           shaderSubgroupClock;
//	VkBool32           shaderDeviceClock;
//};
//
//struct ConformanceVersionKHR
//{
//	uint8_t    major;
//	uint8_t    minor;
//	uint8_t    subminor;
//	uint8_t    patch;
//};
//
//struct PhysicalDeviceDriverPropertiesKHR
//{
//	VkStructureType            sType;
//	void* pNext;
//	VkDriverIdKHR              driverID;
//	char                       driverName[VK_MAX_DRIVER_NAME_SIZE_KHR];
//	char                       driverInfo[VK_MAX_DRIVER_INFO_SIZE_KHR];
//	VkConformanceVersionKHR    conformanceVersion;
//};
//
//struct PhysicalDeviceFloatControlsPropertiesKHR
//{
//	VkStructureType                         sType;
//	void* pNext;
//	VkShaderFloatControlsIndependenceKHR    denormBehaviorIndependence;
//	VkShaderFloatControlsIndependenceKHR    roundingModeIndependence;
//	VkBool32                                shaderSignedZeroInfNanPreserveFloat16;
//	VkBool32                                shaderSignedZeroInfNanPreserveFloat32;
//	VkBool32                                shaderSignedZeroInfNanPreserveFloat64;
//	VkBool32                                shaderDenormPreserveFloat16;
//	VkBool32                                shaderDenormPreserveFloat32;
//	VkBool32                                shaderDenormPreserveFloat64;
//	VkBool32                                shaderDenormFlushToZeroFloat16;
//	VkBool32                                shaderDenormFlushToZeroFloat32;
//	VkBool32                                shaderDenormFlushToZeroFloat64;
//	VkBool32                                shaderRoundingModeRTEFloat16;
//	VkBool32                                shaderRoundingModeRTEFloat32;
//	VkBool32                                shaderRoundingModeRTEFloat64;
//	VkBool32                                shaderRoundingModeRTZFloat16;
//	VkBool32                                shaderRoundingModeRTZFloat32;
//	VkBool32                                shaderRoundingModeRTZFloat64;
//};
//
//struct SubpassDescriptionDepthStencilResolveKHR
//{
//	VkStructureType                     sType;
//	const void* pNext;
//	VkResolveModeFlagBitsKHR            depthResolveMode;
//	VkResolveModeFlagBitsKHR            stencilResolveMode;
//	const VkAttachmentReference2KHR* pDepthStencilResolveAttachment;
//};
//
//struct PhysicalDeviceDepthStencilResolvePropertiesKHR
//{
//	VkStructureType          sType;
//	void* pNext;
//	VkResolveModeFlagsKHR    supportedDepthResolveModes;
//	VkResolveModeFlagsKHR    supportedStencilResolveModes;
//	VkBool32                 independentResolveNone;
//	VkBool32                 independentResolve;
//};
//
//struct PhysicalDeviceTimelineSemaphoreFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           timelineSemaphore;
//};
//
//struct PhysicalDeviceTimelineSemaphorePropertiesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint64_t           maxTimelineSemaphoreValueDifference;
//};
//
//struct SemaphoreTypeCreateInfoKHR
//{
//	VkStructureType       sType;
//	const void* pNext;
//	VkSemaphoreTypeKHR    semaphoreType;
//	uint64_t              initialValue;
//};
//
//struct TimelineSemaphoreSubmitInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           waitSemaphoreValueCount;
//	const uint64_t* pWaitSemaphoreValues;
//	uint32_t           signalSemaphoreValueCount;
//	const uint64_t* pSignalSemaphoreValues;
//};
//
//struct SemaphoreWaitInfoKHR
//{
//	VkStructureType            sType;
//	const void* pNext;
//	VkSemaphoreWaitFlagsKHR    flags;
//	uint32_t                   semaphoreCount;
//	const VkSemaphore* pSemaphores;
//	const uint64_t* pValues;
//};
//
//struct SemaphoreSignalInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkSemaphore        semaphore;
//	uint64_t           value;
//};
//
//struct PhysicalDeviceVulkanMemoryModelFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           vulkanMemoryModel;
//	VkBool32           vulkanMemoryModelDeviceScope;
//	VkBool32           vulkanMemoryModelAvailabilityVisibilityChains;
//};
//
//struct SurfaceProtectedCapabilitiesKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBool32           supportsProtected;
//};
//
//struct PhysicalDeviceSeparateDepthStencilLayoutsFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           separateDepthStencilLayouts;
//};
//
//struct AttachmentReferenceStencilLayoutKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkImageLayout      stencilLayout;
//};
//
//struct AttachmentDescriptionStencilLayoutKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkImageLayout      stencilInitialLayout;
//	VkImageLayout      stencilFinalLayout;
//};
//
//struct PhysicalDeviceUniformBufferStandardLayoutFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           uniformBufferStandardLayout;
//};
//
//struct PhysicalDeviceBufferDeviceAddressFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           bufferDeviceAddress;
//	VkBool32           bufferDeviceAddressCaptureReplay;
//	VkBool32           bufferDeviceAddressMultiDevice;
//};
//
//struct BufferDeviceAddressInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBuffer           buffer;
//};
//
//struct BufferOpaqueCaptureAddressCreateInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint64_t           opaqueCaptureAddress;
//};
//
//struct MemoryOpaqueCaptureAddressAllocateInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint64_t           opaqueCaptureAddress;
//};
//
//struct DeviceMemoryOpaqueCaptureAddressInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkDeviceMemory     memory;
//};
//
//struct PhysicalDevicePipelineExecutablePropertiesFeaturesKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           pipelineExecutableInfo;
//};
//
//struct PipelineInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkPipeline         pipeline;
//};
//
//struct PipelineExecutablePropertiesKHR
//{
//	VkStructureType       sType;
//	void* pNext;
//	VkShaderStageFlags    stages;
//	char                  name[VK_MAX_DESCRIPTION_SIZE];
//	char                  description[VK_MAX_DESCRIPTION_SIZE];
//	uint32_t              subgroupSize;
//};
//
//struct PipelineExecutableInfoKHR
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkPipeline         pipeline;
//	uint32_t           executableIndex;
//};
//
//struct PipelineExecutableStatisticKHR
//{
//	VkStructureType                           sType;
//	void* pNext;
//	char                                      name[VK_MAX_DESCRIPTION_SIZE];
//	char                                      description[VK_MAX_DESCRIPTION_SIZE];
//	VkPipelineExecutableStatisticFormatKHR    format;
//	VkPipelineExecutableStatisticValueKHR     value;
//};
//
//struct PipelineExecutableInternalRepresentationKHR
//{
//	VkStructureType    sType;
//	void* pNext;
//	char               name[VK_MAX_DESCRIPTION_SIZE];
//	char               description[VK_MAX_DESCRIPTION_SIZE];
//	VkBool32           isText;
//	size_t             dataSize;
//	void* pData;
//};

struct DebugReportCallbackCreateInfoEXT : public ::VkDebugReportCallbackCreateInfoEXT
{
	DebugReportCallbackCreateInfoEXT()
	{
		sType       = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
		pNext       = nullptr;
		flags       = 0;
		pfnCallback = nullptr;
		pUserData   = nullptr;
	}
};

//struct PipelineRasterizationStateRasterizationOrderAMD
//{
//	VkStructureType            sType;
//	const void* pNext;
//	VkRasterizationOrderAMD    rasterizationOrder;
//};
//
//struct DebugMarkerObjectNameInfoEXT
//{
//	VkStructureType               sType;
//	const void* pNext;
//	VkDebugReportObjectTypeEXT    objectType;
//	uint64_t                      object;
//	const char* pObjectName;
//};
//
//struct DebugMarkerObjectTagInfoEXT
//{
//	VkStructureType               sType;
//	const void* pNext;
//	VkDebugReportObjectTypeEXT    objectType;
//	uint64_t                      object;
//	uint64_t                      tagName;
//	size_t                        tagSize;
//	const void* pTag;
//};
//
//struct DebugMarkerMarkerInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	const char* pMarkerName;
//	float              color[4];
//};
//
//struct DedicatedAllocationImageCreateInfoNV
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBool32           dedicatedAllocation;
//};
//
//struct DedicatedAllocationBufferCreateInfoNV
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBool32           dedicatedAllocation;
//};
//
//struct DedicatedAllocationMemoryAllocateInfoNV
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkImage            image;
//	VkBuffer           buffer;
//};
//
//struct PhysicalDeviceTransformFeedbackFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           transformFeedback;
//	VkBool32           geometryStreams;
//};
//
//struct PhysicalDeviceTransformFeedbackPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           maxTransformFeedbackStreams;
//	uint32_t           maxTransformFeedbackBuffers;
//	VkDeviceSize       maxTransformFeedbackBufferSize;
//	uint32_t           maxTransformFeedbackStreamDataSize;
//	uint32_t           maxTransformFeedbackBufferDataSize;
//	uint32_t           maxTransformFeedbackBufferDataStride;
//	VkBool32           transformFeedbackQueries;
//	VkBool32           transformFeedbackStreamsLinesTriangles;
//	VkBool32           transformFeedbackRasterizationStreamSelect;
//	VkBool32           transformFeedbackDraw;
//};
//
//struct PipelineRasterizationStateStreamCreateInfoEXT
//{
//	VkStructureType                                     sType;
//	const void* pNext;
//	VkPipelineRasterizationStateStreamCreateFlagsEXT    flags;
//	uint32_t                                            rasterizationStream;
//};
//
//struct ImageViewHandleInfoNVX
//{
//	VkStructureType     sType;
//	const void* pNext;
//	VkImageView         imageView;
//	VkDescriptorType    descriptorType;
//	VkSampler           sampler;
//};
//
//struct TextureLODGatherFormatPropertiesAMD
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           supportsTextureGatherLODBiasAMD;
//};
//
//struct ShaderResourceUsageAMD
//{
//	uint32_t    numUsedVgprs;
//	uint32_t    numUsedSgprs;
//	uint32_t    ldsSizePerLocalWorkGroup;
//	size_t      ldsUsageSizeInBytes;
//	size_t      scratchMemUsageInBytes;
//};
//
//struct ShaderStatisticsInfoAMD
//{
//	VkShaderStageFlags          shaderStageMask;
//	VkShaderResourceUsageAMD    resourceUsage;
//	uint32_t                    numPhysicalVgprs;
//	uint32_t                    numPhysicalSgprs;
//	uint32_t                    numAvailableVgprs;
//	uint32_t                    numAvailableSgprs;
//	uint32_t                    computeWorkGroupSize[3];
//};
//
//struct PhysicalDeviceCornerSampledImageFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           cornerSampledImage;
//};
//
//struct ExternalImageFormatPropertiesNV
//{
//	VkImageFormatProperties              imageFormatProperties;
//	VkExternalMemoryFeatureFlagsNV       externalMemoryFeatures;
//	VkExternalMemoryHandleTypeFlagsNV    exportFromImportedHandleTypes;
//	VkExternalMemoryHandleTypeFlagsNV    compatibleHandleTypes;
//};
//
//struct ExternalMemoryImageCreateInfoNV
//{
//	VkStructureType                      sType;
//	const void* pNext;
//	VkExternalMemoryHandleTypeFlagsNV    handleTypes;
//};
//
//struct ExportMemoryAllocateInfoNV
//{
//	VkStructureType                      sType;
//	const void* pNext;
//	VkExternalMemoryHandleTypeFlagsNV    handleTypes;
//};
//
//struct ValidationFlagsEXT
//{
//	VkStructureType                sType;
//	const void* pNext;
//	uint32_t                       disabledValidationCheckCount;
//	const VkValidationCheckEXT* pDisabledValidationChecks;
//};
//
//struct PhysicalDeviceTextureCompressionASTCHDRFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           textureCompressionASTC_HDR;
//};
//
//struct ImageViewASTCDecodeModeEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkFormat           decodeMode;
//};
//
//struct PhysicalDeviceASTCDecodeFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           decodeModeSharedExponent;
//};
//
//struct ConditionalRenderingBeginInfoEXT
//{
//	VkStructureType                   sType;
//	const void* pNext;
//	VkBuffer                          buffer;
//	VkDeviceSize                      offset;
//	VkConditionalRenderingFlagsEXT    flags;
//};
//
//struct PhysicalDeviceConditionalRenderingFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           conditionalRendering;
//	VkBool32           inheritedConditionalRendering;
//};
//
//struct CommandBufferInheritanceConditionalRenderingInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBool32           conditionalRenderingEnable;
//};
//
//struct DeviceGeneratedCommandsFeaturesNVX
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBool32           computeBindingPointSupport;
//};
//
//struct DeviceGeneratedCommandsLimitsNVX
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           maxIndirectCommandsLayoutTokenCount;
//	uint32_t           maxObjectEntryCounts;
//	uint32_t           minSequenceCountBufferOffsetAlignment;
//	uint32_t           minSequenceIndexBufferOffsetAlignment;
//	uint32_t           minCommandsTokenBufferOffsetAlignment;
//};
//
//struct IndirectCommandsTokenNVX
//{
//	VkIndirectCommandsTokenTypeNVX    tokenType;
//	VkBuffer                          buffer;
//	VkDeviceSize                      offset;
//};
//
//struct IndirectCommandsLayoutTokenNVX
//{
//	VkIndirectCommandsTokenTypeNVX    tokenType;
//	uint32_t                          bindingUnit;
//	uint32_t                          dynamicCount;
//	uint32_t                          divisor;
//};
//
//struct IndirectCommandsLayoutCreateInfoNVX
//{
//	VkStructureType                            sType;
//	const void* pNext;
//	VkPipelineBindPoint                        pipelineBindPoint;
//	VkIndirectCommandsLayoutUsageFlagsNVX      flags;
//	uint32_t                                   tokenCount;
//	const VkIndirectCommandsLayoutTokenNVX* pTokens;
//};
//
//struct CmdProcessCommandsInfoNVX
//{
//	VkStructureType                      sType;
//	const void* pNext;
//	VkObjectTableNVX                     objectTable;
//	VkIndirectCommandsLayoutNVX          indirectCommandsLayout;
//	uint32_t                             indirectCommandsTokenCount;
//	const VkIndirectCommandsTokenNVX* pIndirectCommandsTokens;
//	uint32_t                             maxSequencesCount;
//	VkCommandBuffer                      targetCommandBuffer;
//	VkBuffer                             sequencesCountBuffer;
//	VkDeviceSize                         sequencesCountOffset;
//	VkBuffer                             sequencesIndexBuffer;
//	VkDeviceSize                         sequencesIndexOffset;
//};
//
//struct CmdReserveSpaceForCommandsInfoNVX
//{
//	VkStructureType                sType;
//	const void* pNext;
//	VkObjectTableNVX               objectTable;
//	VkIndirectCommandsLayoutNVX    indirectCommandsLayout;
//	uint32_t                       maxSequencesCount;
//};
//
//struct ObjectTableCreateInfoNVX
//{
//	VkStructureType                      sType;
//	const void* pNext;
//	uint32_t                             objectCount;
//	const VkObjectEntryTypeNVX* pObjectEntryTypes;
//	const uint32_t* pObjectEntryCounts;
//	const VkObjectEntryUsageFlagsNVX* pObjectEntryUsageFlags;
//	uint32_t                             maxUniformBuffersPerDescriptor;
//	uint32_t                             maxStorageBuffersPerDescriptor;
//	uint32_t                             maxStorageImagesPerDescriptor;
//	uint32_t                             maxSampledImagesPerDescriptor;
//	uint32_t                             maxPipelineLayouts;
//};
//
//struct ObjectTableEntryNVX
//{
//	VkObjectEntryTypeNVX          type;
//	VkObjectEntryUsageFlagsNVX    flags;
//};
//
//struct ObjectTablePipelineEntryNVX
//{
//	VkObjectEntryTypeNVX          type;
//	VkObjectEntryUsageFlagsNVX    flags;
//	VkPipeline                    pipeline;
//};
//
//struct ObjectTableDescriptorSetEntryNVX
//{
//	VkObjectEntryTypeNVX          type;
//	VkObjectEntryUsageFlagsNVX    flags;
//	VkPipelineLayout              pipelineLayout;
//	VkDescriptorSet               descriptorSet;
//};
//
//struct ObjectTableVertexBufferEntryNVX
//{
//	VkObjectEntryTypeNVX          type;
//	VkObjectEntryUsageFlagsNVX    flags;
//	VkBuffer                      buffer;
//};
//
//struct ObjectTableIndexBufferEntryNVX
//{
//	VkObjectEntryTypeNVX          type;
//	VkObjectEntryUsageFlagsNVX    flags;
//	VkBuffer                      buffer;
//	VkIndexType                   indexType;
//};
//
//struct ObjectTablePushConstantEntryNVX
//{
//	VkObjectEntryTypeNVX          type;
//	VkObjectEntryUsageFlagsNVX    flags;
//	VkPipelineLayout              pipelineLayout;
//	VkShaderStageFlags            stageFlags;
//};
//
//struct ViewportWScalingNV
//{
//	float    xcoeff;
//	float    ycoeff;
//};
//
//struct PipelineViewportWScalingStateCreateInfoNV
//{
//	VkStructureType                sType;
//	const void* pNext;
//	VkBool32                       viewportWScalingEnable;
//	uint32_t                       viewportCount;
//	const VkViewportWScalingNV* pViewportWScalings;
//};
//
//struct SurfaceCapabilities2EXT
//{
//	VkStructureType                  sType;
//	void* pNext;
//	uint32_t                         minImageCount;
//	uint32_t                         maxImageCount;
//	VkExtent2D                       currentExtent;
//	VkExtent2D                       minImageExtent;
//	VkExtent2D                       maxImageExtent;
//	uint32_t                         maxImageArrayLayers;
//	VkSurfaceTransformFlagsKHR       supportedTransforms;
//	VkSurfaceTransformFlagBitsKHR    currentTransform;
//	VkCompositeAlphaFlagsKHR         supportedCompositeAlpha;
//	VkImageUsageFlags                supportedUsageFlags;
//	VkSurfaceCounterFlagsEXT         supportedSurfaceCounters;
//};
//
//struct DisplayPowerInfoEXT
//{
//	VkStructureType           sType;
//	const void* pNext;
//	VkDisplayPowerStateEXT    powerState;
//};
//
//struct DeviceEventInfoEXT
//{
//	VkStructureType         sType;
//	const void* pNext;
//	VkDeviceEventTypeEXT    deviceEvent;
//};
//
//struct DisplayEventInfoEXT
//{
//	VkStructureType          sType;
//	const void* pNext;
//	VkDisplayEventTypeEXT    displayEvent;
//};
//
//struct SwapchainCounterCreateInfoEXT
//{
//	VkStructureType             sType;
//	const void* pNext;
//	VkSurfaceCounterFlagsEXT    surfaceCounters;
//};
//
//struct RefreshCycleDurationGOOGLE
//{
//	uint64_t    refreshDuration;
//};
//
//struct PastPresentationTimingGOOGLE
//{
//	uint32_t    presentID;
//	uint64_t    desiredPresentTime;
//	uint64_t    actualPresentTime;
//	uint64_t    earliestPresentTime;
//	uint64_t    presentMargin;
//};
//
//struct PresentTimeGOOGLE
//{
//	uint32_t    presentID;
//	uint64_t    desiredPresentTime;
//};
//
//struct PresentTimesInfoGOOGLE
//{
//	VkStructureType               sType;
//	const void* pNext;
//	uint32_t                      swapchainCount;
//	const VkPresentTimeGOOGLE* pTimes;
//};
//
//struct PhysicalDeviceMultiviewPerViewAttributesPropertiesNVX
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           perViewPositionAllComponents;
//};
//
//struct ViewportSwizzleNV
//{
//	VkViewportCoordinateSwizzleNV    x;
//	VkViewportCoordinateSwizzleNV    y;
//	VkViewportCoordinateSwizzleNV    z;
//	VkViewportCoordinateSwizzleNV    w;
//};
//
//struct PipelineViewportSwizzleStateCreateInfoNV
//{
//	VkStructureType                                sType;
//	const void* pNext;
//	VkPipelineViewportSwizzleStateCreateFlagsNV    flags;
//	uint32_t                                       viewportCount;
//	const VkViewportSwizzleNV* pViewportSwizzles;
//};
//
//struct PhysicalDeviceDiscardRectanglePropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           maxDiscardRectangles;
//};
//
//struct PipelineDiscardRectangleStateCreateInfoEXT
//{
//	VkStructureType                                  sType;
//	const void* pNext;
//	VkPipelineDiscardRectangleStateCreateFlagsEXT    flags;
//	VkDiscardRectangleModeEXT                        discardRectangleMode;
//	uint32_t                                         discardRectangleCount;
//	const VkRect2D* pDiscardRectangles;
//};
//
//struct PhysicalDeviceConservativeRasterizationPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	float              primitiveOverestimationSize;
//	float              maxExtraPrimitiveOverestimationSize;
//	float              extraPrimitiveOverestimationSizeGranularity;
//	VkBool32           primitiveUnderestimation;
//	VkBool32           conservativePointAndLineRasterization;
//	VkBool32           degenerateTrianglesRasterized;
//	VkBool32           degenerateLinesRasterized;
//	VkBool32           fullyCoveredFragmentShaderInputVariable;
//	VkBool32           conservativeRasterizationPostDepthCoverage;
//};
//
//struct PipelineRasterizationConservativeStateCreateInfoEXT
//{
//	VkStructureType                                           sType;
//	const void* pNext;
//	VkPipelineRasterizationConservativeStateCreateFlagsEXT    flags;
//	VkConservativeRasterizationModeEXT                        conservativeRasterizationMode;
//	float                                                     extraPrimitiveOverestimationSize;
//};
//
//struct PhysicalDeviceDepthClipEnableFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           depthClipEnable;
//};
//
//struct PipelineRasterizationDepthClipStateCreateInfoEXT
//{
//	VkStructureType                                        sType;
//	const void* pNext;
//	VkPipelineRasterizationDepthClipStateCreateFlagsEXT    flags;
//	VkBool32                                               depthClipEnable;
//};
//
//struct XYColorEXT
//{
//	float    x;
//	float    y;
//};
//
//struct HdrMetadataEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkXYColorEXT       displayPrimaryRed;
//	VkXYColorEXT       displayPrimaryGreen;
//	VkXYColorEXT       displayPrimaryBlue;
//	VkXYColorEXT       whitePoint;
//	float              maxLuminance;
//	float              minLuminance;
//	float              maxContentLightLevel;
//	float              maxFrameAverageLightLevel;
//};
//
//struct DebugUtilsObjectNameInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkObjectType       objectType;
//	uint64_t           objectHandle;
//	const char* pObjectName;
//};
//
//struct DebugUtilsObjectTagInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkObjectType       objectType;
//	uint64_t           objectHandle;
//	uint64_t           tagName;
//	size_t             tagSize;
//	const void* pTag;
//};
//
//struct DebugUtilsLabelEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	const char* pLabelName;
//	float              color[4];
//};
//
//struct DebugUtilsMessengerCallbackDataEXT
//{
//	VkStructureType                              sType;
//	const void* pNext;
//	VkDebugUtilsMessengerCallbackDataFlagsEXT    flags;
//	const char* pMessageIdName;
//	int32_t                                      messageIdNumber;
//	const char* pMessage;
//	uint32_t                                     queueLabelCount;
//	const VkDebugUtilsLabelEXT* pQueueLabels;
//	uint32_t                                     cmdBufLabelCount;
//	const VkDebugUtilsLabelEXT* pCmdBufLabels;
//	uint32_t                                     objectCount;
//	const VkDebugUtilsObjectNameInfoEXT* pObjects;
//};
//
//struct DebugUtilsMessengerCreateInfoEXT
//{
//	VkStructureType                         sType;
//	const void* pNext;
//	VkDebugUtilsMessengerCreateFlagsEXT     flags;
//	VkDebugUtilsMessageSeverityFlagsEXT     messageSeverity;
//	VkDebugUtilsMessageTypeFlagsEXT         messageType;
//	PFN_vkDebugUtilsMessengerCallbackEXT    pfnUserCallback;
//	void* pUserData;
//};
//
//struct SamplerReductionModeCreateInfoEXT
//{
//	VkStructureType              sType;
//	const void* pNext;
//	VkSamplerReductionModeEXT    reductionMode;
//};
//
//struct PhysicalDeviceSamplerFilterMinmaxPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           filterMinmaxSingleComponentFormats;
//	VkBool32           filterMinmaxImageComponentMapping;
//};
//
//struct PhysicalDeviceInlineUniformBlockFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           inlineUniformBlock;
//	VkBool32           descriptorBindingInlineUniformBlockUpdateAfterBind;
//};
//
//struct PhysicalDeviceInlineUniformBlockPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           maxInlineUniformBlockSize;
//	uint32_t           maxPerStageDescriptorInlineUniformBlocks;
//	uint32_t           maxPerStageDescriptorUpdateAfterBindInlineUniformBlocks;
//	uint32_t           maxDescriptorSetInlineUniformBlocks;
//	uint32_t           maxDescriptorSetUpdateAfterBindInlineUniformBlocks;
//};
//
//struct WriteDescriptorSetInlineUniformBlockEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           dataSize;
//	const void* pData;
//};
//
//struct DescriptorPoolInlineUniformBlockCreateInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           maxInlineUniformBlockBindings;
//};
//
//struct SampleLocationEXT
//{
//	float    x;
//	float    y;
//};
//
//struct SampleLocationsInfoEXT
//{
//	VkStructureType               sType;
//	const void* pNext;
//	VkSampleCountFlagBits         sampleLocationsPerPixel;
//	VkExtent2D                    sampleLocationGridSize;
//	uint32_t                      sampleLocationsCount;
//	const VkSampleLocationEXT* pSampleLocations;
//};
//
//struct AttachmentSampleLocationsEXT
//{
//	uint32_t                    attachmentIndex;
//	VkSampleLocationsInfoEXT    sampleLocationsInfo;
//};
//
//struct SubpassSampleLocationsEXT
//{
//	uint32_t                    subpassIndex;
//	VkSampleLocationsInfoEXT    sampleLocationsInfo;
//};
//
//struct RenderPassSampleLocationsBeginInfoEXT
//{
//	VkStructureType                          sType;
//	const void* pNext;
//	uint32_t                                 attachmentInitialSampleLocationsCount;
//	const VkAttachmentSampleLocationsEXT* pAttachmentInitialSampleLocations;
//	uint32_t                                 postSubpassSampleLocationsCount;
//	const VkSubpassSampleLocationsEXT* pPostSubpassSampleLocations;
//};
//
//struct PipelineSampleLocationsStateCreateInfoEXT
//{
//	VkStructureType             sType;
//	const void* pNext;
//	VkBool32                    sampleLocationsEnable;
//	VkSampleLocationsInfoEXT    sampleLocationsInfo;
//};
//
//struct PhysicalDeviceSampleLocationsPropertiesEXT
//{
//	VkStructureType       sType;
//	void* pNext;
//	VkSampleCountFlags    sampleLocationSampleCounts;
//	VkExtent2D            maxSampleLocationGridSize;
//	float                 sampleLocationCoordinateRange[2];
//	uint32_t              sampleLocationSubPixelBits;
//	VkBool32              variableSampleLocations;
//};
//
//struct MultisamplePropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkExtent2D         maxSampleLocationGridSize;
//};
//
//struct PhysicalDeviceBlendOperationAdvancedFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           advancedBlendCoherentOperations;
//};
//
//struct PhysicalDeviceBlendOperationAdvancedPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           advancedBlendMaxColorAttachments;
//	VkBool32           advancedBlendIndependentBlend;
//	VkBool32           advancedBlendNonPremultipliedSrcColor;
//	VkBool32           advancedBlendNonPremultipliedDstColor;
//	VkBool32           advancedBlendCorrelatedOverlap;
//	VkBool32           advancedBlendAllOperations;
//};
//
//struct PipelineColorBlendAdvancedStateCreateInfoEXT
//{
//	VkStructureType      sType;
//	const void* pNext;
//	VkBool32             srcPremultiplied;
//	VkBool32             dstPremultiplied;
//	VkBlendOverlapEXT    blendOverlap;
//};
//
//struct PipelineCoverageToColorStateCreateInfoNV
//{
//	VkStructureType                                sType;
//	const void* pNext;
//	VkPipelineCoverageToColorStateCreateFlagsNV    flags;
//	VkBool32                                       coverageToColorEnable;
//	uint32_t                                       coverageToColorLocation;
//};
//
//struct PipelineCoverageModulationStateCreateInfoNV
//{
//	VkStructureType                                   sType;
//	const void* pNext;
//	VkPipelineCoverageModulationStateCreateFlagsNV    flags;
//	VkCoverageModulationModeNV                        coverageModulationMode;
//	VkBool32                                          coverageModulationTableEnable;
//	uint32_t                                          coverageModulationTableCount;
//	const float* pCoverageModulationTable;
//};
//
//struct PhysicalDeviceShaderSMBuiltinsPropertiesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           shaderSMCount;
//	uint32_t           shaderWarpsPerSM;
//};
//
//struct PhysicalDeviceShaderSMBuiltinsFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           shaderSMBuiltins;
//};
//
//struct DrmFormatModifierPropertiesEXT
//{
//	uint64_t                drmFormatModifier;
//	uint32_t                drmFormatModifierPlaneCount;
//	VkFormatFeatureFlags    drmFormatModifierTilingFeatures;
//};
//
//struct DrmFormatModifierPropertiesListEXT
//{
//	VkStructureType                      sType;
//	void* pNext;
//	uint32_t                             drmFormatModifierCount;
//	VkDrmFormatModifierPropertiesEXT* pDrmFormatModifierProperties;
//};
//
//struct PhysicalDeviceImageDrmFormatModifierInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint64_t           drmFormatModifier;
//	VkSharingMode      sharingMode;
//	uint32_t           queueFamilyIndexCount;
//	const uint32_t* pQueueFamilyIndices;
//};
//
//struct ImageDrmFormatModifierListCreateInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           drmFormatModifierCount;
//	const uint64_t* pDrmFormatModifiers;
//};
//
//struct ImageDrmFormatModifierExplicitCreateInfoEXT
//{
//	VkStructureType               sType;
//	const void* pNext;
//	uint64_t                      drmFormatModifier;
//	uint32_t                      drmFormatModifierPlaneCount;
//	const VkSubresourceLayout* pPlaneLayouts;
//};
//
//struct ImageDrmFormatModifierPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint64_t           drmFormatModifier;
//};
//
//struct ValidationCacheCreateInfoEXT
//{
//	VkStructureType                    sType;
//	const void* pNext;
//	VkValidationCacheCreateFlagsEXT    flags;
//	size_t                             initialDataSize;
//	const void* pInitialData;
//};
//
//struct ShaderModuleValidationCacheCreateInfoEXT
//{
//	VkStructureType         sType;
//	const void* pNext;
//	VkValidationCacheEXT    validationCache;
//};
//
//struct DescriptorSetLayoutBindingFlagsCreateInfoEXT
//{
//	VkStructureType                       sType;
//	const void* pNext;
//	uint32_t                              bindingCount;
//	const VkDescriptorBindingFlagsEXT* pBindingFlags;
//};
//
//struct PhysicalDeviceDescriptorIndexingFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           shaderInputAttachmentArrayDynamicIndexing;
//	VkBool32           shaderUniformTexelBufferArrayDynamicIndexing;
//	VkBool32           shaderStorageTexelBufferArrayDynamicIndexing;
//	VkBool32           shaderUniformBufferArrayNonUniformIndexing;
//	VkBool32           shaderSampledImageArrayNonUniformIndexing;
//	VkBool32           shaderStorageBufferArrayNonUniformIndexing;
//	VkBool32           shaderStorageImageArrayNonUniformIndexing;
//	VkBool32           shaderInputAttachmentArrayNonUniformIndexing;
//	VkBool32           shaderUniformTexelBufferArrayNonUniformIndexing;
//	VkBool32           shaderStorageTexelBufferArrayNonUniformIndexing;
//	VkBool32           descriptorBindingUniformBufferUpdateAfterBind;
//	VkBool32           descriptorBindingSampledImageUpdateAfterBind;
//	VkBool32           descriptorBindingStorageImageUpdateAfterBind;
//	VkBool32           descriptorBindingStorageBufferUpdateAfterBind;
//	VkBool32           descriptorBindingUniformTexelBufferUpdateAfterBind;
//	VkBool32           descriptorBindingStorageTexelBufferUpdateAfterBind;
//	VkBool32           descriptorBindingUpdateUnusedWhilePending;
//	VkBool32           descriptorBindingPartiallyBound;
//	VkBool32           descriptorBindingVariableDescriptorCount;
//	VkBool32           runtimeDescriptorArray;
//};
//
//struct PhysicalDeviceDescriptorIndexingPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           maxUpdateAfterBindDescriptorsInAllPools;
//	VkBool32           shaderUniformBufferArrayNonUniformIndexingNative;
//	VkBool32           shaderSampledImageArrayNonUniformIndexingNative;
//	VkBool32           shaderStorageBufferArrayNonUniformIndexingNative;
//	VkBool32           shaderStorageImageArrayNonUniformIndexingNative;
//	VkBool32           shaderInputAttachmentArrayNonUniformIndexingNative;
//	VkBool32           robustBufferAccessUpdateAfterBind;
//	VkBool32           quadDivergentImplicitLod;
//	uint32_t           maxPerStageDescriptorUpdateAfterBindSamplers;
//	uint32_t           maxPerStageDescriptorUpdateAfterBindUniformBuffers;
//	uint32_t           maxPerStageDescriptorUpdateAfterBindStorageBuffers;
//	uint32_t           maxPerStageDescriptorUpdateAfterBindSampledImages;
//	uint32_t           maxPerStageDescriptorUpdateAfterBindStorageImages;
//	uint32_t           maxPerStageDescriptorUpdateAfterBindInputAttachments;
//	uint32_t           maxPerStageUpdateAfterBindResources;
//	uint32_t           maxDescriptorSetUpdateAfterBindSamplers;
//	uint32_t           maxDescriptorSetUpdateAfterBindUniformBuffers;
//	uint32_t           maxDescriptorSetUpdateAfterBindUniformBuffersDynamic;
//	uint32_t           maxDescriptorSetUpdateAfterBindStorageBuffers;
//	uint32_t           maxDescriptorSetUpdateAfterBindStorageBuffersDynamic;
//	uint32_t           maxDescriptorSetUpdateAfterBindSampledImages;
//	uint32_t           maxDescriptorSetUpdateAfterBindStorageImages;
//	uint32_t           maxDescriptorSetUpdateAfterBindInputAttachments;
//};
//
//struct DescriptorSetVariableDescriptorCountAllocateInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           descriptorSetCount;
//	const uint32_t* pDescriptorCounts;
//};
//
//struct DescriptorSetVariableDescriptorCountLayoutSupportEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           maxVariableDescriptorCount;
//};
//
//struct ShadingRatePaletteNV
//{
//	uint32_t                              shadingRatePaletteEntryCount;
//	const VkShadingRatePaletteEntryNV* pShadingRatePaletteEntries;
//};
//
//struct PipelineViewportShadingRateImageStateCreateInfoNV
//{
//	VkStructureType                  sType;
//	const void* pNext;
//	VkBool32                         shadingRateImageEnable;
//	uint32_t                         viewportCount;
//	const VkShadingRatePaletteNV* pShadingRatePalettes;
//};
//
//struct PhysicalDeviceShadingRateImageFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           shadingRateImage;
//	VkBool32           shadingRateCoarseSampleOrder;
//};
//
//struct PhysicalDeviceShadingRateImagePropertiesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkExtent2D         shadingRateTexelSize;
//	uint32_t           shadingRatePaletteSize;
//	uint32_t           shadingRateMaxCoarseSamples;
//};
//
//struct CoarseSampleLocationNV
//{
//	uint32_t    pixelX;
//	uint32_t    pixelY;
//	uint32_t    sample;
//};
//
//struct CoarseSampleOrderCustomNV
//{
//	VkShadingRatePaletteEntryNV        shadingRate;
//	uint32_t                           sampleCount;
//	uint32_t                           sampleLocationCount;
//	const VkCoarseSampleLocationNV* pSampleLocations;
//};
//
//struct PipelineViewportCoarseSampleOrderStateCreateInfoNV
//{
//	VkStructureType                       sType;
//	const void* pNext;
//	VkCoarseSampleOrderTypeNV             sampleOrderType;
//	uint32_t                              customSampleOrderCount;
//	const VkCoarseSampleOrderCustomNV* pCustomSampleOrders;
//};
//
//struct RayTracingShaderGroupCreateInfoNV
//{
//	VkStructureType                  sType;
//	const void* pNext;
//	VkRayTracingShaderGroupTypeNV    type;
//	uint32_t                         generalShader;
//	uint32_t                         closestHitShader;
//	uint32_t                         anyHitShader;
//	uint32_t                         intersectionShader;
//};
//
//struct RayTracingPipelineCreateInfoNV
//{
//	VkStructureType                               sType;
//	const void* pNext;
//	VkPipelineCreateFlags                         flags;
//	uint32_t                                      stageCount;
//	const VkPipelineShaderStageCreateInfo* pStages;
//	uint32_t                                      groupCount;
//	const VkRayTracingShaderGroupCreateInfoNV* pGroups;
//	uint32_t                                      maxRecursionDepth;
//	VkPipelineLayout                              layout;
//	VkPipeline                                    basePipelineHandle;
//	int32_t                                       basePipelineIndex;
//};
//
//struct GeometryTrianglesNV
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBuffer           vertexData;
//	VkDeviceSize       vertexOffset;
//	uint32_t           vertexCount;
//	VkDeviceSize       vertexStride;
//	VkFormat           vertexFormat;
//	VkBuffer           indexData;
//	VkDeviceSize       indexOffset;
//	uint32_t           indexCount;
//	VkIndexType        indexType;
//	VkBuffer           transformData;
//	VkDeviceSize       transformOffset;
//};
//
//struct GeometryAABBNV
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBuffer           aabbData;
//	uint32_t           numAABBs;
//	uint32_t           stride;
//	VkDeviceSize       offset;
//};
//
//struct GeometryDataNV
//{
//	VkGeometryTrianglesNV    triangles;
//	VkGeometryAABBNV         aabbs;
//};
//
//struct GeometryNV
//{
//	VkStructureType      sType;
//	const void* pNext;
//	VkGeometryTypeNV     geometryType;
//	VkGeometryDataNV     geometry;
//	VkGeometryFlagsNV    flags;
//};
//
//struct AccelerationStructureInfoNV
//{
//	VkStructureType                        sType;
//	const void* pNext;
//	VkAccelerationStructureTypeNV          type;
//	VkBuildAccelerationStructureFlagsNV    flags;
//	uint32_t                               instanceCount;
//	uint32_t                               geometryCount;
//	const VkGeometryNV* pGeometries;
//};
//
//struct AccelerationStructureCreateInfoNV
//{
//	VkStructureType                  sType;
//	const void* pNext;
//	VkDeviceSize                     compactedSize;
//	VkAccelerationStructureInfoNV    info;
//};
//
//struct BindAccelerationStructureMemoryInfoNV
//{
//	VkStructureType              sType;
//	const void* pNext;
//	VkAccelerationStructureNV    accelerationStructure;
//	VkDeviceMemory               memory;
//	VkDeviceSize                 memoryOffset;
//	uint32_t                     deviceIndexCount;
//	const uint32_t* pDeviceIndices;
//};
//
//struct WriteDescriptorSetAccelerationStructureNV
//{
//	VkStructureType                     sType;
//	const void* pNext;
//	uint32_t                            accelerationStructureCount;
//	const VkAccelerationStructureNV* pAccelerationStructures;
//};
//
//struct AccelerationStructureMemoryRequirementsInfoNV
//{
//	VkStructureType                                    sType;
//	const void* pNext;
//	VkAccelerationStructureMemoryRequirementsTypeNV    type;
//	VkAccelerationStructureNV                          accelerationStructure;
//};
//
//struct PhysicalDeviceRayTracingPropertiesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           shaderGroupHandleSize;
//	uint32_t           maxRecursionDepth;
//	uint32_t           maxShaderGroupStride;
//	uint32_t           shaderGroupBaseAlignment;
//	uint64_t           maxGeometryCount;
//	uint64_t           maxInstanceCount;
//	uint64_t           maxTriangleCount;
//	uint32_t           maxDescriptorSetAccelerationStructures;
//};
//
//struct PhysicalDeviceRepresentativeFragmentTestFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           representativeFragmentTest;
//};
//
//struct PipelineRepresentativeFragmentTestStateCreateInfoNV
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBool32           representativeFragmentTestEnable;
//};
//
//struct PhysicalDeviceImageViewImageFormatInfoEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkImageViewType    imageViewType;
//};
//
//struct FilterCubicImageViewImageFormatPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           filterCubic;
//	VkBool32           filterCubicMinmax;
//};
//
//struct DeviceQueueGlobalPriorityCreateInfoEXT
//{
//	VkStructureType             sType;
//	const void* pNext;
//	VkQueueGlobalPriorityEXT    globalPriority;
//};
//
//struct ImportMemoryHostPointerInfoEXT
//{
//	VkStructureType                       sType;
//	const void* pNext;
//	VkExternalMemoryHandleTypeFlagBits    handleType;
//	void* pHostPointer;
//};
//
//struct MemoryHostPointerPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           memoryTypeBits;
//};
//
//struct PhysicalDeviceExternalMemoryHostPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkDeviceSize       minImportedHostPointerAlignment;
//};
//
//struct PipelineCompilerControlCreateInfoAMD
//{
//	VkStructureType                      sType;
//	const void* pNext;
//	VkPipelineCompilerControlFlagsAMD    compilerControlFlags;
//};
//
//struct CalibratedTimestampInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkTimeDomainEXT    timeDomain;
//};
//
//struct PhysicalDeviceShaderCorePropertiesAMD
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           shaderEngineCount;
//	uint32_t           shaderArraysPerEngineCount;
//	uint32_t           computeUnitsPerShaderArray;
//	uint32_t           simdPerComputeUnit;
//	uint32_t           wavefrontsPerSimd;
//	uint32_t           wavefrontSize;
//	uint32_t           sgprsPerSimd;
//	uint32_t           minSgprAllocation;
//	uint32_t           maxSgprAllocation;
//	uint32_t           sgprAllocationGranularity;
//	uint32_t           vgprsPerSimd;
//	uint32_t           minVgprAllocation;
//	uint32_t           maxVgprAllocation;
//	uint32_t           vgprAllocationGranularity;
//};
//
//struct DeviceMemoryOverallocationCreateInfoAMD
//{
//	VkStructureType                      sType;
//	const void* pNext;
//	VkMemoryOverallocationBehaviorAMD    overallocationBehavior;
//};
//
//struct PhysicalDeviceVertexAttributeDivisorPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           maxVertexAttribDivisor;
//};
//
//struct VertexInputBindingDivisorDescriptionEXT
//{
//	uint32_t    binding;
//	uint32_t    divisor;
//};
//
//struct PipelineVertexInputDivisorStateCreateInfoEXT
//{
//	VkStructureType                                     sType;
//	const void* pNext;
//	uint32_t                                            vertexBindingDivisorCount;
//	const VkVertexInputBindingDivisorDescriptionEXT* pVertexBindingDivisors;
//};
//
//struct PhysicalDeviceVertexAttributeDivisorFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           vertexAttributeInstanceRateDivisor;
//	VkBool32           vertexAttributeInstanceRateZeroDivisor;
//};
//
//struct PipelineCreationFeedbackEXT
//{
//	VkPipelineCreationFeedbackFlagsEXT    flags;
//	uint64_t                              duration;
//};
//
//struct PipelineCreationFeedbackCreateInfoEXT
//{
//	VkStructureType                   sType;
//	const void* pNext;
//	VkPipelineCreationFeedbackEXT* pPipelineCreationFeedback;
//	uint32_t                          pipelineStageCreationFeedbackCount;
//	VkPipelineCreationFeedbackEXT* pPipelineStageCreationFeedbacks;
//};
//
//struct PhysicalDeviceComputeShaderDerivativesFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           computeDerivativeGroupQuads;
//	VkBool32           computeDerivativeGroupLinear;
//};
//
//struct PhysicalDeviceMeshShaderFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           taskShader;
//	VkBool32           meshShader;
//};
//
//struct PhysicalDeviceMeshShaderPropertiesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           maxDrawMeshTasksCount;
//	uint32_t           maxTaskWorkGroupInvocations;
//	uint32_t           maxTaskWorkGroupSize[3];
//	uint32_t           maxTaskTotalMemorySize;
//	uint32_t           maxTaskOutputCount;
//	uint32_t           maxMeshWorkGroupInvocations;
//	uint32_t           maxMeshWorkGroupSize[3];
//	uint32_t           maxMeshTotalMemorySize;
//	uint32_t           maxMeshOutputVertices;
//	uint32_t           maxMeshOutputPrimitives;
//	uint32_t           maxMeshMultiviewViewCount;
//	uint32_t           meshOutputPerVertexGranularity;
//	uint32_t           meshOutputPerPrimitiveGranularity;
//};
//
//struct DrawMeshTasksIndirectCommandNV
//{
//	uint32_t    taskCount;
//	uint32_t    firstTask;
//};
//
//struct PhysicalDeviceFragmentShaderBarycentricFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           fragmentShaderBarycentric;
//};
//
//struct PhysicalDeviceShaderImageFootprintFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           imageFootprint;
//};
//
//struct PipelineViewportExclusiveScissorStateCreateInfoNV
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           exclusiveScissorCount;
//	const VkRect2D* pExclusiveScissors;
//};
//
//struct PhysicalDeviceExclusiveScissorFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           exclusiveScissor;
//};
//
//struct QueueFamilyCheckpointPropertiesNV
//{
//	VkStructureType         sType;
//	void* pNext;
//	VkPipelineStageFlags    checkpointExecutionStageMask;
//};
//
//struct CheckpointDataNV
//{
//	VkStructureType            sType;
//	void* pNext;
//	VkPipelineStageFlagBits    stage;
//	void* pCheckpointMarker;
//};
//
//struct PhysicalDeviceShaderIntegerFunctions2FeaturesINTEL
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           shaderIntegerFunctions2;
//};
//
//struct PerformanceValueINTEL
//{
//	VkPerformanceValueTypeINTEL    type;
//	VkPerformanceValueDataINTEL    data;
//};
//
//struct InitializePerformanceApiInfoINTEL
//{
//	VkStructureType    sType;
//	const void* pNext;
//	void* pUserData;
//};
//
//struct QueryPoolCreateInfoINTEL
//{
//	VkStructureType                 sType;
//	const void* pNext;
//	VkQueryPoolSamplingModeINTEL    performanceCountersSampling;
//};
//
//struct PerformanceMarkerInfoINTEL
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint64_t           marker;
//};
//
//struct PerformanceStreamMarkerInfoINTEL
//{
//	VkStructureType    sType;
//	const void* pNext;
//	uint32_t           marker;
//};
//
//struct PerformanceOverrideInfoINTEL
//{
//	VkStructureType                   sType;
//	const void* pNext;
//	VkPerformanceOverrideTypeINTEL    type;
//	VkBool32                          enable;
//	uint64_t                          parameter;
//};
//
//struct PerformanceConfigurationAcquireInfoINTEL
//{
//	VkStructureType                        sType;
//	const void* pNext;
//	VkPerformanceConfigurationTypeINTEL    type;
//};
//
//struct PhysicalDevicePCIBusInfoPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           pciDomain;
//	uint32_t           pciBus;
//	uint32_t           pciDevice;
//	uint32_t           pciFunction;
//};
//
//struct DisplayNativeHdrSurfaceCapabilitiesAMD
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           localDimmingSupport;
//};
//
//struct SwapchainDisplayNativeHdrCreateInfoAMD
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkBool32           localDimmingEnable;
//};
//
//struct PhysicalDeviceFragmentDensityMapFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           fragmentDensityMap;
//	VkBool32           fragmentDensityMapDynamic;
//	VkBool32           fragmentDensityMapNonSubsampledImages;
//};
//
//struct PhysicalDeviceFragmentDensityMapPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkExtent2D         minFragmentDensityTexelSize;
//	VkExtent2D         maxFragmentDensityTexelSize;
//	VkBool32           fragmentDensityInvocations;
//};
//
//struct RenderPassFragmentDensityMapCreateInfoEXT
//{
//	VkStructureType          sType;
//	const void* pNext;
//	VkAttachmentReference    fragmentDensityMapAttachment;
//};
//
//struct PhysicalDeviceScalarBlockLayoutFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           scalarBlockLayout;
//};
//
//struct PhysicalDeviceSubgroupSizeControlFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           subgroupSizeControl;
//	VkBool32           computeFullSubgroups;
//};
//
//struct PhysicalDeviceSubgroupSizeControlPropertiesEXT
//{
//	VkStructureType       sType;
//	void* pNext;
//	uint32_t              minSubgroupSize;
//	uint32_t              maxSubgroupSize;
//	uint32_t              maxComputeWorkgroupSubgroups;
//	VkShaderStageFlags    requiredSubgroupSizeStages;
//};
//
//struct PipelineShaderStageRequiredSubgroupSizeCreateInfoEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           requiredSubgroupSize;
//};
//
//struct PhysicalDeviceShaderCoreProperties2AMD
//{
//	VkStructureType                   sType;
//	void* pNext;
//	VkShaderCorePropertiesFlagsAMD    shaderCoreFeatures;
//	uint32_t                          activeComputeUnitCount;
//};
//
//struct PhysicalDeviceCoherentMemoryFeaturesAMD
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           deviceCoherentMemory;
//};
//
//struct PhysicalDeviceMemoryBudgetPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkDeviceSize       heapBudget[VK_MAX_MEMORY_HEAPS];
//	VkDeviceSize       heapUsage[VK_MAX_MEMORY_HEAPS];
//};
//
//struct PhysicalDeviceMemoryPriorityFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           memoryPriority;
//};
//
//struct MemoryPriorityAllocateInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	float              priority;
//};
//
//struct PhysicalDeviceDedicatedAllocationImageAliasingFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           dedicatedAllocationImageAliasing;
//};
//
//struct PhysicalDeviceBufferDeviceAddressFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           bufferDeviceAddress;
//	VkBool32           bufferDeviceAddressCaptureReplay;
//	VkBool32           bufferDeviceAddressMultiDevice;
//};
//
//struct BufferDeviceAddressCreateInfoEXT
//{
//	VkStructureType    sType;
//	const void* pNext;
//	VkDeviceAddress    deviceAddress;
//};
//
//struct PhysicalDeviceToolPropertiesEXT
//{
//	VkStructureType          sType;
//	void* pNext;
//	char                     name[VK_MAX_EXTENSION_NAME_SIZE];
//	char                     version[VK_MAX_EXTENSION_NAME_SIZE];
//	VkToolPurposeFlagsEXT    purposes;
//	char                     description[VK_MAX_DESCRIPTION_SIZE];
//	char                     layer[VK_MAX_EXTENSION_NAME_SIZE];
//};
//
//struct ImageStencilUsageCreateInfoEXT
//{
//	VkStructureType      sType;
//	const void* pNext;
//	VkImageUsageFlags    stencilUsage;
//};
//
//struct ValidationFeaturesEXT
//{
//	VkStructureType                         sType;
//	const void* pNext;
//	uint32_t                                enabledValidationFeatureCount;
//	const VkValidationFeatureEnableEXT* pEnabledValidationFeatures;
//	uint32_t                                disabledValidationFeatureCount;
//	const VkValidationFeatureDisableEXT* pDisabledValidationFeatures;
//};
//
//struct CooperativeMatrixPropertiesNV
//{
//	VkStructureType      sType;
//	void* pNext;
//	uint32_t             MSize;
//	uint32_t             NSize;
//	uint32_t             KSize;
//	VkComponentTypeNV    AType;
//	VkComponentTypeNV    BType;
//	VkComponentTypeNV    CType;
//	VkComponentTypeNV    DType;
//	VkScopeNV            scope;
//};
//
//struct PhysicalDeviceCooperativeMatrixFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           cooperativeMatrix;
//	VkBool32           cooperativeMatrixRobustBufferAccess;
//};
//
//struct PhysicalDeviceCooperativeMatrixPropertiesNV
//{
//	VkStructureType       sType;
//	void* pNext;
//	VkShaderStageFlags    cooperativeMatrixSupportedStages;
//};
//
//struct PhysicalDeviceCoverageReductionModeFeaturesNV
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           coverageReductionMode;
//};
//
//struct PipelineCoverageReductionStateCreateInfoNV
//{
//	VkStructureType                                  sType;
//	const void* pNext;
//	VkPipelineCoverageReductionStateCreateFlagsNV    flags;
//	VkCoverageReductionModeNV                        coverageReductionMode;
//};
//
//struct FramebufferMixedSamplesCombinationNV
//{
//	VkStructureType              sType;
//	void* pNext;
//	VkCoverageReductionModeNV    coverageReductionMode;
//	VkSampleCountFlagBits        rasterizationSamples;
//	VkSampleCountFlags           depthStencilSamples;
//	VkSampleCountFlags           colorSamples;
//};
//
//struct PhysicalDeviceFragmentShaderInterlockFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           fragmentShaderSampleInterlock;
//	VkBool32           fragmentShaderPixelInterlock;
//	VkBool32           fragmentShaderShadingRateInterlock;
//};
//
//struct PhysicalDeviceYcbcrImageArraysFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           ycbcrImageArrays;
//};
//
//struct HeadlessSurfaceCreateInfoEXT
//{
//	VkStructureType                    sType;
//	const void* pNext;
//	VkHeadlessSurfaceCreateFlagsEXT    flags;
//};
//
//struct PhysicalDeviceLineRasterizationFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           rectangularLines;
//	VkBool32           bresenhamLines;
//	VkBool32           smoothLines;
//	VkBool32           stippledRectangularLines;
//	VkBool32           stippledBresenhamLines;
//	VkBool32           stippledSmoothLines;
//};
//
//struct PhysicalDeviceLineRasterizationPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	uint32_t           lineSubPixelPrecisionBits;
//};
//
//struct PipelineRasterizationLineStateCreateInfoEXT
//{
//	VkStructureType               sType;
//	const void* pNext;
//	VkLineRasterizationModeEXT    lineRasterizationMode;
//	VkBool32                      stippledLineEnable;
//	uint32_t                      lineStippleFactor;
//	uint16_t                      lineStipplePattern;
//};
//
//struct PhysicalDeviceHostQueryResetFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           hostQueryReset;
//};
//
//struct PhysicalDeviceIndexTypeUint8FeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           indexTypeUint8;
//};
//
//struct PhysicalDeviceShaderDemoteToHelperInvocationFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           shaderDemoteToHelperInvocation;
//};
//
//struct PhysicalDeviceTexelBufferAlignmentFeaturesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkBool32           texelBufferAlignment;
//};
//
//struct PhysicalDeviceTexelBufferAlignmentPropertiesEXT
//{
//	VkStructureType    sType;
//	void* pNext;
//	VkDeviceSize       storageTexelBufferOffsetAlignmentBytes;
//	VkBool32           storageTexelBufferOffsetSingleTexelAlignment;
//	VkDeviceSize       uniformTexelBufferOffsetAlignmentBytes;
//	VkBool32           uniformTexelBufferOffsetSingleTexelAlignment;
//};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_H_HPP
