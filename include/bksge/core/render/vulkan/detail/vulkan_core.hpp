/**
 *	@file	vulkan_core.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_CORE_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_CORE_HPP

#include <vulkan/vulkan_core.h>
#include <bksge/core/render/vulkan/detail/check_error.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <cstddef>
#include <vector>

namespace bksge
{

namespace render
{

namespace vk
{

#define BKSGE_VK_INSTANCE_FUNC(instance, funcname, ...)		\
	static auto p = reinterpret_cast<PFN_ ## funcname>(		\
		::vkGetInstanceProcAddr(instance, #funcname));		\
	if (p)	                                                \
	{	                                                    \
		p(__VA_ARGS__);						    \
	}

#define BKSGE_VK_DEVICE_FUNC(device, funcname, ...)			\
	static auto p = reinterpret_cast<PFN_ ## funcname>(		\
		::vkGetDeviceProcAddr(device, #funcname));			\
	if (p)	                                                \
	{	                                                    \
		p(__VA_ARGS__);										\
	}

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
		enabledLayerCount       = static_cast<bksge::uint32_t>(layer_names.size());
		ppEnabledLayerNames     = layer_names.data();
	}

	void SetEnabledExtensionNames(std::vector<char const*> const& extension_names)
	{
		enabledExtensionCount   = static_cast<bksge::uint32_t>(extension_names.size());
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
		enabledLayerCount       = static_cast<bksge::uint32_t>(layer_names.size());
		ppEnabledLayerNames     = layer_names.data();
	}

	void SetEnabledExtensionNames(std::vector<char const*> const& extension_names)
	{
		enabledExtensionCount   = static_cast<bksge::uint32_t>(extension_names.size());
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

	void SetQueueFamilyIndices(bksge::uint32_t const* queue_family_index)
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

	void SetQueueFamilyIndices(bksge::uint32_t const* queue_family_index)
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
		vertexAttributeDescriptionCount = static_cast<bksge::uint32_t>(vi_attribs.size());
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
		dynamicStateCount = static_cast<bksge::uint32_t>(dynamic_states.size());
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
		stageCount = static_cast<bksge::uint32_t>(stages.size());
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
		setLayoutCount = static_cast<bksge::uint32_t>(set_layouts.size());
		pSetLayouts    = set_layouts.data();
	}

	void SetPushConstantRanges(::VkPushConstantRange const* range)
	{
		pushConstantRangeCount = range ? 1 : 0;
		pPushConstantRanges    = range;
	}
};

struct SamplerCreateInfo : public ::VkSamplerCreateInfo
{
	SamplerCreateInfo()
	{
		sType                   = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
		pNext                   = nullptr;
		flags                   = 0;
		magFilter               = VK_FILTER_NEAREST;
		minFilter               = VK_FILTER_NEAREST;
		mipmapMode              = VK_SAMPLER_MIPMAP_MODE_NEAREST;
		addressModeU            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		addressModeV            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		addressModeW            = VK_SAMPLER_ADDRESS_MODE_REPEAT;
		mipLodBias              = 0;
		anisotropyEnable        = VK_FALSE;
		maxAnisotropy           = 0;
		compareEnable           = VK_FALSE;
		compareOp               = VK_COMPARE_OP_NEVER;
		minLod                  = 0;
		maxLod                  = 0;
		borderColor             = VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
		unnormalizedCoordinates = VK_FALSE;
	}
};

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
		bindingCount = static_cast<bksge::uint32_t>(bindings.size());
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
		poolSizeCount = static_cast<bksge::uint32_t>(pool_sizes.size());
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
		descriptorSetCount = static_cast<bksge::uint32_t>(set_layouts.size());
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
		attachmentCount = static_cast<bksge::uint32_t>(attachments.size());
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

	void SetPreserveAttachments(bksge::uint32_t const* preserve_attachment)
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
		attachmentCount = static_cast<bksge::uint32_t>(attachments.size());
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

struct ImageMemoryBarrier : public ::VkImageMemoryBarrier
{
	ImageMemoryBarrier()
	{
		sType               = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
		pNext               = nullptr;
		srcAccessMask       = 0;
		dstAccessMask       = 0;
		oldLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
		newLayout           = VK_IMAGE_LAYOUT_UNDEFINED;
		srcQueueFamilyIndex = 0;
		dstQueueFamilyIndex = 0;
		image               = VK_NULL_HANDLE;
		subresourceRange    = ImageSubresourceRange();
	}
};

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

	void SetQueueFamilyIndices(bksge::uint32_t const* queue_family_index)
	{
		queueFamilyIndexCount = queue_family_index ? 1 : 0;
		pQueueFamilyIndices   = queue_family_index;
	}

	template <std::size_t N>
	void SetQueueFamilyIndices(bksge::uint32_t const (&queue_family_indices)[N])
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

inline VkResult CreateInstance(
    const VkInstanceCreateInfo*                 pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkInstance*                                 pInstance)
{
	return vk::CheckError(::vkCreateInstance(pCreateInfo, pAllocator, pInstance));
}

inline void DestroyInstance(
    VkInstance                                  instance,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyInstance(instance, pAllocator);
}

inline std::vector<VkPhysicalDevice>
EnumeratePhysicalDevices(VkInstance instance)
{
	for (;;)
	{
		uint32_t count;
		vk::CheckError(::vkEnumeratePhysicalDevices(instance, &count, nullptr));

		if (count == 0)
		{
			return {};
		}

		std::vector<VkPhysicalDevice> physical_devices(count);
		auto res = ::vkEnumeratePhysicalDevices(instance, &count, physical_devices.data());
		if (res == VK_INCOMPLETE)
		{
			continue;
		}
		vk::CheckError(res);

		return physical_devices;
	}
}

inline void GetPhysicalDeviceFeatures(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceFeatures*                   pFeatures)
{
	::vkGetPhysicalDeviceFeatures(physicalDevice, pFeatures);
}

inline void GetPhysicalDeviceFormatProperties(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkFormatProperties*                         pFormatProperties)
{
	::vkGetPhysicalDeviceFormatProperties(physicalDevice, format, pFormatProperties);
}

VkResult vkGetPhysicalDeviceImageFormatProperties(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkImageType                                 type,
    VkImageTiling                               tiling,
    VkImageUsageFlags                           usage,
    VkImageCreateFlags                          flags,
    VkImageFormatProperties*                    pImageFormatProperties);

inline void GetPhysicalDeviceProperties(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceProperties*                 pProperties)
{
	::vkGetPhysicalDeviceProperties(physicalDevice, pProperties);
}

inline void GetPhysicalDeviceQueueFamilyProperties(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pQueueFamilyPropertyCount,
    VkQueueFamilyProperties*                    pQueueFamilyProperties)
{
	::vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties);
}

inline void GetPhysicalDeviceMemoryProperties(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceMemoryProperties*           pMemoryProperties)
{
	::vkGetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties);
}

PFN_vkVoidFunction vkGetInstanceProcAddr(
    VkInstance                                  instance,
    const char*                                 pName);

PFN_vkVoidFunction vkGetDeviceProcAddr(
    VkDevice                                    device,
    const char*                                 pName);

inline VkResult CreateDevice(
    VkPhysicalDevice                            physicalDevice,
    const VkDeviceCreateInfo*                   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDevice*                                   pDevice)
{
	return vk::CheckError(::vkCreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice));
}

inline void DestroyDevice(
    VkDevice                                    device,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyDevice(device, pAllocator);
}

inline std::vector<VkExtensionProperties>
EnumerateInstanceExtensionProperties(const char* pLayerName)
{
	for (;;)
	{
		uint32_t count;
		vk::CheckError(::vkEnumerateInstanceExtensionProperties(pLayerName, &count, nullptr));

		if (count == 0)
		{
			return {};
		}

		std::vector<VkExtensionProperties> extension_properties(count);
		auto res = ::vkEnumerateInstanceExtensionProperties(pLayerName, &count, extension_properties.data());
		if (res == VK_INCOMPLETE)
		{
			continue;
		}
		vk::CheckError(res);

		return extension_properties;
	}
}

inline std::vector<VkExtensionProperties>
EnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char* pLayerName)
{
	for (;;)
	{
		uint32_t count;
		vk::CheckError(::vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, &count, nullptr));

		if (count == 0)
		{
			return {};
		}

		std::vector<VkExtensionProperties> extension_properties(count);
		auto res = ::vkEnumerateDeviceExtensionProperties(physicalDevice, pLayerName, &count, extension_properties.data());
		if (res == VK_INCOMPLETE)
		{
			continue;
		}
		vk::CheckError(res);

		return extension_properties;
	}
}

inline std::vector<VkLayerProperties>
EnumerateInstanceLayerProperties(void)
{
	/*
	 * It's possible, though very rare, that the number of
	 * instance layers could change. For example, installing something
	 * could include new layers that the loader would pick up
	 * between the initial query for the count and the
	 * request for VkLayerProperties. The loader indicates that
	 * by returning a VK_INCOMPLETE status and will update the
	 * the count parameter.
	 * The count parameter will be updated with the number of
	 * entries loaded into the data pointer - in case the number
	 * of layers went down or is smaller than the size given.
	 */

	for (;;)
	{
		uint32_t count;
		vk::CheckError(::vkEnumerateInstanceLayerProperties(&count, nullptr));

		if (count == 0)
		{
			return {};
		}

		std::vector<VkLayerProperties> layer_properties(count);
		auto res = ::vkEnumerateInstanceLayerProperties(&count, layer_properties.data());
		if (res == VK_INCOMPLETE)
		{
			continue;
		}
		vk::CheckError(res);

		return layer_properties;
	}
}

inline std::vector<VkLayerProperties>
EnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice)
{
	for (;;)
	{
		uint32_t count;
		vk::CheckError(::vkEnumerateDeviceLayerProperties(physicalDevice, &count, nullptr));

		if (count == 0)
		{
			return {};
		}

		std::vector<VkLayerProperties> layer_properties(count);
		auto res = ::vkEnumerateDeviceLayerProperties(physicalDevice, &count, layer_properties.data());
		if (res == VK_INCOMPLETE)
		{
			continue;
		}
		vk::CheckError(res);

		return layer_properties;
	}
}

inline void GetDeviceQueue(
    VkDevice                                    device,
    uint32_t                                    queueFamilyIndex,
    uint32_t                                    queueIndex,
    VkQueue*                                    pQueue)
{
	::vkGetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue);
}

inline VkResult QueueSubmit(
    VkQueue                                     queue,
    uint32_t                                    submitCount,
    const VkSubmitInfo*                         pSubmits,
    VkFence                                     fence)
{
	return vk::CheckError(::vkQueueSubmit(queue, submitCount, pSubmits, fence));
}

inline VkResult QueueWaitIdle(VkQueue queue)
{
	return vk::CheckError(::vkQueueWaitIdle(queue));
}

inline VkResult DeviceWaitIdle(VkDevice device)
{
	return vk::CheckError(::vkDeviceWaitIdle(device));
}

inline VkResult AllocateMemory(
    VkDevice                                    device,
    const VkMemoryAllocateInfo*                 pAllocateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDeviceMemory*                             pMemory)
{
	return vk::CheckError(::vkAllocateMemory(device, pAllocateInfo, pAllocator, pMemory));
}

inline void FreeMemory(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkFreeMemory(device, memory, pAllocator);
}

inline VkResult MapMemory(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkDeviceSize                                offset,
    VkDeviceSize                                size,
    VkMemoryMapFlags                            flags,
    void**                                      ppData)
{
	return vk::CheckError(::vkMapMemory(device, memory, offset, size, flags, ppData));
}

inline void UnmapMemory(
    VkDevice                                    device,
    VkDeviceMemory                              memory)
{
	::vkUnmapMemory(device, memory);
}

VkResult vkFlushMappedMemoryRanges(
    VkDevice                                    device,
    uint32_t                                    memoryRangeCount,
    const VkMappedMemoryRange*                  pMemoryRanges);

VkResult vkInvalidateMappedMemoryRanges(
    VkDevice                                    device,
    uint32_t                                    memoryRangeCount,
    const VkMappedMemoryRange*                  pMemoryRanges);

void vkGetDeviceMemoryCommitment(
    VkDevice                                    device,
    VkDeviceMemory                              memory,
    VkDeviceSize*                               pCommittedMemoryInBytes);

inline VkResult BindBufferMemory(
    VkDevice                                    device,
    VkBuffer                                    buffer,
    VkDeviceMemory                              memory,
    VkDeviceSize                                memoryOffset)
{
	return vk::CheckError(::vkBindBufferMemory(device, buffer, memory, memoryOffset));
}

inline VkResult BindImageMemory(
    VkDevice                                    device,
    VkImage                                     image,
    VkDeviceMemory                              memory,
    VkDeviceSize                                memoryOffset)
{
	return vk::CheckError(::vkBindImageMemory(device, image, memory, memoryOffset));
}

inline void GetBufferMemoryRequirements(
    VkDevice                                    device,
    VkBuffer                                    buffer,
    VkMemoryRequirements*                       pMemoryRequirements)
{
	::vkGetBufferMemoryRequirements(device, buffer, pMemoryRequirements);
}

inline void GetImageMemoryRequirements(
    VkDevice                                    device,
    VkImage                                     image,
    VkMemoryRequirements*                       pMemoryRequirements)
{
	::vkGetImageMemoryRequirements(device, image, pMemoryRequirements);
}

void vkGetImageSparseMemoryRequirements(
    VkDevice                                    device,
    VkImage                                     image,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements*            pSparseMemoryRequirements);

void vkGetPhysicalDeviceSparseImageFormatProperties(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkImageType                                 type,
    VkSampleCountFlagBits                       samples,
    VkImageUsageFlags                           usage,
    VkImageTiling                               tiling,
    uint32_t*                                   pPropertyCount,
    VkSparseImageFormatProperties*              pProperties);

VkResult vkQueueBindSparse(
    VkQueue                                     queue,
    uint32_t                                    bindInfoCount,
    const VkBindSparseInfo*                     pBindInfo,
    VkFence                                     fence);

inline VkResult CreateFence(
    VkDevice                                    device,
    const VkFenceCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence)
{
	return vk::CheckError(::vkCreateFence(device, pCreateInfo, pAllocator, pFence));
}

inline void DestroyFence(
    VkDevice                                    device,
    VkFence                                     fence,
    const VkAllocationCallbacks*                pAllocator)
{
	vkDestroyFence(device, fence, pAllocator);
}

inline VkResult ResetFences(
    VkDevice                                    device,
    uint32_t                                    fenceCount,
    const VkFence*                              pFences)
{
	return vk::CheckError(::vkResetFences(device, fenceCount, pFences));
}

VkResult vkGetFenceStatus(
    VkDevice                                    device,
    VkFence                                     fence);

inline VkResult WaitForFences(
    VkDevice                                    device,
    uint32_t                                    fenceCount,
    const VkFence*                              pFences,
    VkBool32                                    waitAll,
    uint64_t                                    timeout)
{
	return vk::CheckError(::vkWaitForFences(device, fenceCount, pFences, waitAll, timeout));
}

inline VkResult CreateSemaphore(
    VkDevice                                    device,
    const VkSemaphoreCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSemaphore*                                pSemaphore)
{
	return vk::CheckError(::vkCreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore));
}

inline void DestroySemaphore(
    VkDevice                                    device,
    VkSemaphore                                 semaphore,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroySemaphore(device, semaphore, pAllocator);
}

VkResult vkCreateEvent(
    VkDevice                                    device,
    const VkEventCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkEvent*                                    pEvent);

void vkDestroyEvent(
    VkDevice                                    device,
    VkEvent                                     event,
    const VkAllocationCallbacks*                pAllocator);

VkResult vkGetEventStatus(
    VkDevice                                    device,
    VkEvent                                     event);

VkResult vkSetEvent(
    VkDevice                                    device,
    VkEvent                                     event);

VkResult vkResetEvent(
    VkDevice                                    device,
    VkEvent                                     event);

VkResult vkCreateQueryPool(
    VkDevice                                    device,
    const VkQueryPoolCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkQueryPool*                                pQueryPool);

void vkDestroyQueryPool(
    VkDevice                                    device,
    VkQueryPool                                 queryPool,
    const VkAllocationCallbacks*                pAllocator);

VkResult vkGetQueryPoolResults(
    VkDevice                                    device,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount,
    size_t                                      dataSize,
    void*                                       pData,
    VkDeviceSize                                stride,
    VkQueryResultFlags                          flags);

inline VkResult CreateBuffer(
    VkDevice                                    device,
    const VkBufferCreateInfo*                   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkBuffer*                                   pBuffer)
{
	return vk::CheckError(::vkCreateBuffer(device, pCreateInfo, pAllocator, pBuffer));
}

inline void DestroyBuffer(
    VkDevice                                    device,
    VkBuffer                                    buffer,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyBuffer(device, buffer, pAllocator);
}

VkResult vkCreateBufferView(
    VkDevice                                    device,
    const VkBufferViewCreateInfo*               pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkBufferView*                               pView);

void vkDestroyBufferView(
    VkDevice                                    device,
    VkBufferView                                bufferView,
    const VkAllocationCallbacks*                pAllocator);

inline VkResult CreateImage(
    VkDevice                                    device,
    const VkImageCreateInfo*                    pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkImage*                                    pImage)
{
	return vk::CheckError(::vkCreateImage(device, pCreateInfo, pAllocator, pImage));
}

inline void DestroyImage(
    VkDevice                                    device,
    VkImage                                     image,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyImage(device, image, pAllocator);
}

void vkGetImageSubresourceLayout(
    VkDevice                                    device,
    VkImage                                     image,
    const VkImageSubresource*                   pSubresource,
    VkSubresourceLayout*                        pLayout);

inline VkResult CreateImageView(
    VkDevice                                    device,
    const VkImageViewCreateInfo*                pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkImageView*                                pView)
{
	return vk::CheckError(::vkCreateImageView(device, pCreateInfo, pAllocator, pView));
}

inline void DestroyImageView(
    VkDevice                                    device,
    VkImageView                                 imageView,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyImageView(device, imageView, pAllocator);
}

inline VkResult CreateShaderModule(
    VkDevice                                    device,
    const VkShaderModuleCreateInfo*             pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkShaderModule*                             pShaderModule)
{
	return vk::CheckError(::vkCreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule));
}

inline void DestroyShaderModule(
    VkDevice                                    device,
    VkShaderModule                              shaderModule,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyShaderModule(device, shaderModule, pAllocator);
}

inline VkResult CreatePipelineCache(
    VkDevice                                    device,
    const VkPipelineCacheCreateInfo*            pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPipelineCache*                            pPipelineCache)
{
	return vk::CheckError(::vkCreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache));
}

inline void DestroyPipelineCache(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyPipelineCache(device, pipelineCache, pAllocator);
}

VkResult vkGetPipelineCacheData(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    size_t*                                     pDataSize,
    void*                                       pData);

VkResult vkMergePipelineCaches(
    VkDevice                                    device,
    VkPipelineCache                             dstCache,
    uint32_t                                    srcCacheCount,
    const VkPipelineCache*                      pSrcCaches);

inline VkResult CreateGraphicsPipelines(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkGraphicsPipelineCreateInfo*         pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines)
{
	return vk::CheckError(::vkCreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines));
}

VkResult vkCreateComputePipelines(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkComputePipelineCreateInfo*          pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);

inline void DestroyPipeline(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyPipeline(device, pipeline, pAllocator);
}

inline VkResult CreatePipelineLayout(
    VkDevice                                    device,
    const VkPipelineLayoutCreateInfo*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkPipelineLayout*                           pPipelineLayout)
{
	return vk::CheckError(::vkCreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout));
}

inline void DestroyPipelineLayout(
    VkDevice                                    device,
    VkPipelineLayout                            pipelineLayout,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyPipelineLayout(device, pipelineLayout, pAllocator);
}

inline VkResult CreateSampler(
    VkDevice                                    device,
    const VkSamplerCreateInfo*                  pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSampler*                                  pSampler)
{
	return vk::CheckError(::vkCreateSampler(device, pCreateInfo, pAllocator, pSampler));
}

inline void DestroySampler(
    VkDevice                                    device,
    VkSampler                                   sampler,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroySampler(device, sampler, pAllocator);
}

inline VkResult CreateDescriptorSetLayout(
    VkDevice                                    device,
    const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorSetLayout*                      pSetLayout)
{
	return vk::CheckError(::vkCreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout));
}

inline void DestroyDescriptorSetLayout(
    VkDevice                                    device,
    VkDescriptorSetLayout                       descriptorSetLayout,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator);
}

inline VkResult CreateDescriptorPool(
    VkDevice                                    device,
    const VkDescriptorPoolCreateInfo*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorPool*                           pDescriptorPool)
{
	return vk::CheckError(::vkCreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool));
}

inline void DestroyDescriptorPool(
    VkDevice                                    device,
    VkDescriptorPool                            descriptorPool,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyDescriptorPool(device, descriptorPool, pAllocator);
}

VkResult vkResetDescriptorPool(
    VkDevice                                    device,
    VkDescriptorPool                            descriptorPool,
    VkDescriptorPoolResetFlags                  flags);

inline VkResult AllocateDescriptorSets(
    VkDevice                                    device,
    const VkDescriptorSetAllocateInfo*          pAllocateInfo,
    VkDescriptorSet*                            pDescriptorSets)
{
	return vk::CheckError(::vkAllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets));
}

inline VkResult FreeDescriptorSets(
    VkDevice                                    device,
    VkDescriptorPool                            descriptorPool,
    uint32_t                                    descriptorSetCount,
    const VkDescriptorSet*                      pDescriptorSets)
{
	return vk::CheckError(::vkFreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets));
}

inline void UpdateDescriptorSets(
    VkDevice                                    device,
    uint32_t                                    descriptorWriteCount,
    const VkWriteDescriptorSet*                 pDescriptorWrites,
    uint32_t                                    descriptorCopyCount,
    const VkCopyDescriptorSet*                  pDescriptorCopies)
{
	::vkUpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies);
}

inline VkResult CreateFramebuffer(
    VkDevice                                    device,
    const VkFramebufferCreateInfo*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFramebuffer*                              pFramebuffer)
{
	return vk::CheckError(::vkCreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer));
}

inline void DestroyFramebuffer(
    VkDevice                                    device,
    VkFramebuffer                               framebuffer,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyFramebuffer(device, framebuffer, pAllocator);
}

inline VkResult CreateRenderPass(
    VkDevice                                    device,
    const VkRenderPassCreateInfo*               pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkRenderPass*                               pRenderPass)
{
	return vk::CheckError(::vkCreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass));
}

inline void DestroyRenderPass(
    VkDevice                                    device,
    VkRenderPass                                renderPass,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyRenderPass(device, renderPass, pAllocator);
}

void vkGetRenderAreaGranularity(
    VkDevice                                    device,
    VkRenderPass                                renderPass,
    VkExtent2D*                                 pGranularity);

inline VkResult CreateCommandPool(
    VkDevice                                    device,
    const VkCommandPoolCreateInfo*              pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkCommandPool*                              pCommandPool)
{
	return vk::CheckError(::vkCreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool));
}

inline void DestroyCommandPool(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroyCommandPool(device, commandPool, pAllocator);
}

VkResult vkResetCommandPool(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    VkCommandPoolResetFlags                     flags);

inline VkResult AllocateCommandBuffers(
    VkDevice                                    device,
    const VkCommandBufferAllocateInfo*          pAllocateInfo,
    VkCommandBuffer*                            pCommandBuffers)
{
	return vk::CheckError(::vkAllocateCommandBuffers(device, pAllocateInfo, pCommandBuffers));
}

inline void FreeCommandBuffers(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    uint32_t                                    commandBufferCount,
    const VkCommandBuffer*                      pCommandBuffers)
{
	::vkFreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers);
}

inline VkResult BeginCommandBuffer(
    VkCommandBuffer                             commandBuffer,
    const VkCommandBufferBeginInfo*             pBeginInfo)
{
	return vk::CheckError(::vkBeginCommandBuffer(commandBuffer, pBeginInfo));
}

inline VkResult EndCommandBuffer(
    VkCommandBuffer                             commandBuffer)
{
	return vk::CheckError(::vkEndCommandBuffer(commandBuffer));
}

VkResult vkResetCommandBuffer(
    VkCommandBuffer                             commandBuffer,
    VkCommandBufferResetFlags                   flags);

inline void CmdBindPipeline(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipeline                                  pipeline)
{
	::vkCmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline);
}

inline void CmdSetViewport(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkViewport*                           pViewports)
{
	::vkCmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports);
}

inline void CmdSetScissor(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstScissor,
    uint32_t                                    scissorCount,
    const VkRect2D*                             pScissors)
{
	::vkCmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors);
}

void vkCmdSetLineWidth(
    VkCommandBuffer                             commandBuffer,
    float                                       lineWidth);

void vkCmdSetDepthBias(
    VkCommandBuffer                             commandBuffer,
    float                                       depthBiasConstantFactor,
    float                                       depthBiasClamp,
    float                                       depthBiasSlopeFactor);

void vkCmdSetBlendConstants(
    VkCommandBuffer                             commandBuffer,
    const float                                 blendConstants[4]);

void vkCmdSetDepthBounds(
    VkCommandBuffer                             commandBuffer,
    float                                       minDepthBounds,
    float                                       maxDepthBounds);

void vkCmdSetStencilCompareMask(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    compareMask);

void vkCmdSetStencilWriteMask(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    writeMask);

void vkCmdSetStencilReference(
    VkCommandBuffer                             commandBuffer,
    VkStencilFaceFlags                          faceMask,
    uint32_t                                    reference);

inline void CmdBindDescriptorSets(
    VkCommandBuffer                             commandBuffer,
    VkPipelineBindPoint                         pipelineBindPoint,
    VkPipelineLayout                            layout,
    uint32_t                                    firstSet,
    uint32_t                                    descriptorSetCount,
    const VkDescriptorSet*                      pDescriptorSets,
    uint32_t                                    dynamicOffsetCount,
    const uint32_t*                             pDynamicOffsets)
{
	::vkCmdBindDescriptorSets(
		commandBuffer,
		pipelineBindPoint,
		layout,
		firstSet,
		descriptorSetCount,
		pDescriptorSets,
		dynamicOffsetCount,
		pDynamicOffsets);
}

inline void CmdBindIndexBuffer(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkIndexType                                 indexType)
{
	::vkCmdBindIndexBuffer(
		commandBuffer,
		buffer,
		offset,
		indexType);
}

inline void CmdBindVertexBuffers(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets)
{
	::vkCmdBindVertexBuffers(
		commandBuffer,
		firstBinding,
		bindingCount,
		pBuffers,
		pOffsets);
}

inline void CmdDraw(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    vertexCount,
    uint32_t                                    instanceCount,
    uint32_t                                    firstVertex,
    uint32_t                                    firstInstance)
{
	::vkCmdDraw(
		commandBuffer,
		vertexCount,
		instanceCount,
		firstVertex,
		firstInstance);
}

inline void CmdDrawIndexed(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    indexCount,
    uint32_t                                    instanceCount,
    uint32_t                                    firstIndex,
    int32_t                                     vertexOffset,
    uint32_t                                    firstInstance)
{
	::vkCmdDrawIndexed(
		commandBuffer,
		indexCount,
		instanceCount,
		firstIndex,
		vertexOffset,
		firstInstance);
}

void vkCmdDrawIndirect(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride);

void vkCmdDrawIndexedIndirect(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride);

void vkCmdDispatch(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ);

void vkCmdDispatchIndirect(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset);

void vkCmdCopyBuffer(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    srcBuffer,
    VkBuffer                                    dstBuffer,
    uint32_t                                    regionCount,
    const VkBufferCopy*                         pRegions);

void vkCmdCopyImage(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkImageCopy*                          pRegions);

void vkCmdBlitImage(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkImageBlit*                          pRegions,
    VkFilter                                    filter);

inline void CmdCopyBufferToImage(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    srcBuffer,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkBufferImageCopy*                    pRegions)
{
	::vkCmdCopyBufferToImage(
		commandBuffer,
		srcBuffer,
		dstImage,
		dstImageLayout,
		regionCount,
		pRegions);
}

void vkCmdCopyImageToBuffer(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkBuffer                                    dstBuffer,
    uint32_t                                    regionCount,
    const VkBufferImageCopy*                    pRegions);

void vkCmdUpdateBuffer(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                dataSize,
    const void*                                 pData);

void vkCmdFillBuffer(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                size,
    uint32_t                                    data);

void vkCmdClearColorImage(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     image,
    VkImageLayout                               imageLayout,
    const VkClearColorValue*                    pColor,
    uint32_t                                    rangeCount,
    const VkImageSubresourceRange*              pRanges);

inline void CmdClearDepthStencilImage(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     image,
    VkImageLayout                               imageLayout,
    const VkClearDepthStencilValue*             pDepthStencil,
    uint32_t                                    rangeCount,
    const VkImageSubresourceRange*              pRanges)
{
	::vkCmdClearDepthStencilImage(
		commandBuffer,
		image,
		imageLayout,
		pDepthStencil,
		rangeCount,
		pRanges);
}

void vkCmdClearAttachments(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    attachmentCount,
    const VkClearAttachment*                    pAttachments,
    uint32_t                                    rectCount,
    const VkClearRect*                          pRects);

void vkCmdResolveImage(
    VkCommandBuffer                             commandBuffer,
    VkImage                                     srcImage,
    VkImageLayout                               srcImageLayout,
    VkImage                                     dstImage,
    VkImageLayout                               dstImageLayout,
    uint32_t                                    regionCount,
    const VkImageResolve*                       pRegions);

void vkCmdSetEvent(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    VkPipelineStageFlags                        stageMask);

void vkCmdResetEvent(
    VkCommandBuffer                             commandBuffer,
    VkEvent                                     event,
    VkPipelineStageFlags                        stageMask);

void vkCmdWaitEvents(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    eventCount,
    const VkEvent*                              pEvents,
    VkPipelineStageFlags                        srcStageMask,
    VkPipelineStageFlags                        dstStageMask,
    uint32_t                                    memoryBarrierCount,
    const VkMemoryBarrier*                      pMemoryBarriers,
    uint32_t                                    bufferMemoryBarrierCount,
    const VkBufferMemoryBarrier*                pBufferMemoryBarriers,
    uint32_t                                    imageMemoryBarrierCount,
    const VkImageMemoryBarrier*                 pImageMemoryBarriers);

inline void CmdPipelineBarrier(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlags                        srcStageMask,
    VkPipelineStageFlags                        dstStageMask,
    VkDependencyFlags                           dependencyFlags,
    uint32_t                                    memoryBarrierCount,
    const VkMemoryBarrier*                      pMemoryBarriers,
    uint32_t                                    bufferMemoryBarrierCount,
    const VkBufferMemoryBarrier*                pBufferMemoryBarriers,
    uint32_t                                    imageMemoryBarrierCount,
    const VkImageMemoryBarrier*                 pImageMemoryBarriers)
{
	::vkCmdPipelineBarrier(
		commandBuffer,
		srcStageMask,
		dstStageMask,
		dependencyFlags,
		memoryBarrierCount,
		pMemoryBarriers,
		bufferMemoryBarrierCount,
		pBufferMemoryBarriers,
		imageMemoryBarrierCount,
		pImageMemoryBarriers);
}

void vkCmdBeginQuery(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    query,
    VkQueryControlFlags                         flags);

void vkCmdEndQuery(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    query);

void vkCmdResetQueryPool(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount);

void vkCmdWriteTimestamp(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlagBits                     pipelineStage,
    VkQueryPool                                 queryPool,
    uint32_t                                    query);

void vkCmdCopyQueryPoolResults(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    VkDeviceSize                                stride,
    VkQueryResultFlags                          flags);

void vkCmdPushConstants(
    VkCommandBuffer                             commandBuffer,
    VkPipelineLayout                            layout,
    VkShaderStageFlags                          stageFlags,
    uint32_t                                    offset,
    uint32_t                                    size,
    const void*                                 pValues);

inline void CmdBeginRenderPass(
    VkCommandBuffer                             commandBuffer,
    const VkRenderPassBeginInfo*                pRenderPassBegin,
    VkSubpassContents                           contents)
{
	::vkCmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents);
}

void vkCmdNextSubpass(
    VkCommandBuffer                             commandBuffer,
    VkSubpassContents                           contents);

inline void CmdEndRenderPass(
    VkCommandBuffer                             commandBuffer)
{
	::vkCmdEndRenderPass(commandBuffer);
}

void vkCmdExecuteCommands(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    commandBufferCount,
    const VkCommandBuffer*                      pCommandBuffers);

VkResult vkEnumerateInstanceVersion(
    uint32_t*                                   pApiVersion);

VkResult vkBindBufferMemory2(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindBufferMemoryInfo*               pBindInfos);

VkResult vkBindImageMemory2(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindImageMemoryInfo*                pBindInfos);

void vkGetDeviceGroupPeerMemoryFeatures(
    VkDevice                                    device,
    uint32_t                                    heapIndex,
    uint32_t                                    localDeviceIndex,
    uint32_t                                    remoteDeviceIndex,
    VkPeerMemoryFeatureFlags*                   pPeerMemoryFeatures);

void vkCmdSetDeviceMask(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    deviceMask);

void vkCmdDispatchBase(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    baseGroupX,
    uint32_t                                    baseGroupY,
    uint32_t                                    baseGroupZ,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ);

VkResult vkEnumeratePhysicalDeviceGroups(
    VkInstance                                  instance,
    uint32_t*                                   pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties*            pPhysicalDeviceGroupProperties);

void vkGetImageMemoryRequirements2(
    VkDevice                                    device,
    const VkImageMemoryRequirementsInfo2*       pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements);

void vkGetBufferMemoryRequirements2(
    VkDevice                                    device,
    const VkBufferMemoryRequirementsInfo2*      pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements);

void vkGetImageSparseMemoryRequirements2(
    VkDevice                                    device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2*           pSparseMemoryRequirements);

void vkGetPhysicalDeviceFeatures2(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceFeatures2*                  pFeatures);

void vkGetPhysicalDeviceProperties2(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceProperties2*                pProperties);

void vkGetPhysicalDeviceFormatProperties2(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkFormatProperties2*                        pFormatProperties);

VkResult vkGetPhysicalDeviceImageFormatProperties2(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2*     pImageFormatInfo,
    VkImageFormatProperties2*                   pImageFormatProperties);

void vkGetPhysicalDeviceQueueFamilyProperties2(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2*                   pQueueFamilyProperties);

void vkGetPhysicalDeviceMemoryProperties2(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceMemoryProperties2*          pMemoryProperties);

void vkGetPhysicalDeviceSparseImageFormatProperties2(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t*                                   pPropertyCount,
    VkSparseImageFormatProperties2*             pProperties);

void vkTrimCommandPool(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    VkCommandPoolTrimFlags                      flags);

void vkGetDeviceQueue2(
    VkDevice                                    device,
    const VkDeviceQueueInfo2*                   pQueueInfo,
    VkQueue*                                    pQueue);

VkResult vkCreateSamplerYcbcrConversion(
    VkDevice                                    device,
    const VkSamplerYcbcrConversionCreateInfo*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSamplerYcbcrConversion*                   pYcbcrConversion);

void vkDestroySamplerYcbcrConversion(
    VkDevice                                    device,
    VkSamplerYcbcrConversion                    ycbcrConversion,
    const VkAllocationCallbacks*                pAllocator);

VkResult vkCreateDescriptorUpdateTemplate(
    VkDevice                                    device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorUpdateTemplate*                 pDescriptorUpdateTemplate);

void vkDestroyDescriptorUpdateTemplate(
    VkDevice                                    device,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    const VkAllocationCallbacks*                pAllocator);

void vkUpdateDescriptorSetWithTemplate(
    VkDevice                                    device,
    VkDescriptorSet                             descriptorSet,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    const void*                                 pData);

void vkGetPhysicalDeviceExternalBufferProperties(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo*   pExternalBufferInfo,
    VkExternalBufferProperties*                 pExternalBufferProperties);

void vkGetPhysicalDeviceExternalFenceProperties(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo*    pExternalFenceInfo,
    VkExternalFenceProperties*                  pExternalFenceProperties);

void vkGetPhysicalDeviceExternalSemaphoreProperties(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties*              pExternalSemaphoreProperties);

void vkGetDescriptorSetLayoutSupport(
    VkDevice                                    device,
    const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
    VkDescriptorSetLayoutSupport*               pSupport);

inline void DestroySurfaceKHR(
    VkInstance                                  instance,
    VkSurfaceKHR                                surface,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroySurfaceKHR(instance, surface, pAllocator);
}

inline VkResult GetPhysicalDeviceSurfaceSupportKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    queueFamilyIndex,
    VkSurfaceKHR                                surface,
    VkBool32*                                   pSupported)
{
	return vk::CheckError(::vkGetPhysicalDeviceSurfaceSupportKHR(
		physicalDevice, queueFamilyIndex, surface, pSupported));
}

inline VkResult GetPhysicalDeviceSurfaceCapabilitiesKHR(
    VkPhysicalDevice                            physicalDevice,
    VkSurfaceKHR                                surface,
    VkSurfaceCapabilitiesKHR*                   pSurfaceCapabilities)
{
	return vk::CheckError(::vkGetPhysicalDeviceSurfaceCapabilitiesKHR(
		physicalDevice, surface, pSurfaceCapabilities));
}

inline std::vector<VkSurfaceFormatKHR>
GetPhysicalDeviceSurfaceFormatsKHR(
    VkPhysicalDevice physicalDevice,
    VkSurfaceKHR     surface)
{
	for (;;)
	{
		uint32_t count;
		vk::CheckError(::vkGetPhysicalDeviceSurfaceFormatsKHR(
			physicalDevice, surface, &count, nullptr));

		if (count == 0)
		{
			return {};
		}

		std::vector<VkSurfaceFormatKHR> surface_formats(count);
		auto res = ::vkGetPhysicalDeviceSurfaceFormatsKHR(
			physicalDevice, surface, &count, surface_formats.data());
		if (res == VK_INCOMPLETE)
		{
			continue;
		}
		vk::CheckError(res);

		return surface_formats;
	}
}

VkResult vkGetPhysicalDeviceSurfacePresentModesKHR(
    VkPhysicalDevice                            physicalDevice,
    VkSurfaceKHR                                surface,
    uint32_t*                                   pPresentModeCount,
    VkPresentModeKHR*                           pPresentModes);

inline VkResult CreateSwapchainKHR(
    VkDevice                                    device,
    const VkSwapchainCreateInfoKHR*             pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSwapchainKHR*                             pSwapchain)
{
	return vk::CheckError(::vkCreateSwapchainKHR(
		device, pCreateInfo, pAllocator, pSwapchain));
}

inline void DestroySwapchainKHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    const VkAllocationCallbacks*                pAllocator)
{
	::vkDestroySwapchainKHR(device, swapchain, pAllocator);
}

inline std::vector<::VkImage>
GetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain)
{
	bksge::uint32_t count = 0;
	vk::CheckError(::vkGetSwapchainImagesKHR(
		device, swapchain, &count, nullptr));

	std::vector<::VkImage> images(count);
	vk::CheckError(::vkGetSwapchainImagesKHR(
		device, swapchain, &count, images.data()));

	return images;
}

inline VkResult AcquireNextImageKHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint64_t                                    timeout,
    VkSemaphore                                 semaphore,
    VkFence                                     fence,
    uint32_t*                                   pImageIndex)
{
	return vk::CheckError(::vkAcquireNextImageKHR(
		device, swapchain, timeout, semaphore, fence, pImageIndex));
}

inline VkResult QueuePresentKHR(
    VkQueue                                     queue,
    const VkPresentInfoKHR*                     pPresentInfo)
{
	return vk::CheckError(::vkQueuePresentKHR(queue, pPresentInfo));
}

VkResult vkGetDeviceGroupPresentCapabilitiesKHR(
    VkDevice                                    device,
    VkDeviceGroupPresentCapabilitiesKHR*        pDeviceGroupPresentCapabilities);

VkResult vkGetDeviceGroupSurfacePresentModesKHR(
    VkDevice                                    device,
    VkSurfaceKHR                                surface,
    VkDeviceGroupPresentModeFlagsKHR*           pModes);

VkResult vkGetPhysicalDevicePresentRectanglesKHR(
    VkPhysicalDevice                            physicalDevice,
    VkSurfaceKHR                                surface,
    uint32_t*                                   pRectCount,
    VkRect2D*                                   pRects);

VkResult vkAcquireNextImage2KHR(
    VkDevice                                    device,
    const VkAcquireNextImageInfoKHR*            pAcquireInfo,
    uint32_t*                                   pImageIndex);

VkResult vkGetPhysicalDeviceDisplayPropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkDisplayPropertiesKHR*                     pProperties);

VkResult vkGetPhysicalDeviceDisplayPlanePropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkDisplayPlanePropertiesKHR*                pProperties);

VkResult vkGetDisplayPlaneSupportedDisplaysKHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t                                    planeIndex,
    uint32_t*                                   pDisplayCount,
    VkDisplayKHR*                               pDisplays);

VkResult vkGetDisplayModePropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display,
    uint32_t*                                   pPropertyCount,
    VkDisplayModePropertiesKHR*                 pProperties);

VkResult vkCreateDisplayModeKHR(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display,
    const VkDisplayModeCreateInfoKHR*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDisplayModeKHR*                           pMode);

VkResult vkGetDisplayPlaneCapabilitiesKHR(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayModeKHR                            mode,
    uint32_t                                    planeIndex,
    VkDisplayPlaneCapabilitiesKHR*              pCapabilities);

VkResult vkCreateDisplayPlaneSurfaceKHR(
    VkInstance                                  instance,
    const VkDisplaySurfaceCreateInfoKHR*        pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);

VkResult vkCreateSharedSwapchainsKHR(
    VkDevice                                    device,
    uint32_t                                    swapchainCount,
    const VkSwapchainCreateInfoKHR*             pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkSwapchainKHR*                             pSwapchains);

void vkGetPhysicalDeviceFeatures2KHR(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceFeatures2*                  pFeatures);

void vkGetPhysicalDeviceProperties2KHR(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceProperties2*                pProperties);

void vkGetPhysicalDeviceFormatProperties2KHR(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkFormatProperties2*                        pFormatProperties);

VkResult vkGetPhysicalDeviceImageFormatProperties2KHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceImageFormatInfo2*     pImageFormatInfo,
    VkImageFormatProperties2*                   pImageFormatProperties);

void vkGetPhysicalDeviceQueueFamilyProperties2KHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pQueueFamilyPropertyCount,
    VkQueueFamilyProperties2*                   pQueueFamilyProperties);

void vkGetPhysicalDeviceMemoryProperties2KHR(
    VkPhysicalDevice                            physicalDevice,
    VkPhysicalDeviceMemoryProperties2*          pMemoryProperties);

void vkGetPhysicalDeviceSparseImageFormatProperties2KHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceSparseImageFormatInfo2* pFormatInfo,
    uint32_t*                                   pPropertyCount,
    VkSparseImageFormatProperties2*             pProperties);

void vkGetDeviceGroupPeerMemoryFeaturesKHR(
    VkDevice                                    device,
    uint32_t                                    heapIndex,
    uint32_t                                    localDeviceIndex,
    uint32_t                                    remoteDeviceIndex,
    VkPeerMemoryFeatureFlags*                   pPeerMemoryFeatures);

void vkCmdSetDeviceMaskKHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    deviceMask);

void vkCmdDispatchBaseKHR(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    baseGroupX,
    uint32_t                                    baseGroupY,
    uint32_t                                    baseGroupZ,
    uint32_t                                    groupCountX,
    uint32_t                                    groupCountY,
    uint32_t                                    groupCountZ);

void vkTrimCommandPoolKHR(
    VkDevice                                    device,
    VkCommandPool                               commandPool,
    VkCommandPoolTrimFlags                      flags);

VkResult vkEnumeratePhysicalDeviceGroupsKHR(
    VkInstance                                  instance,
    uint32_t*                                   pPhysicalDeviceGroupCount,
    VkPhysicalDeviceGroupProperties*            pPhysicalDeviceGroupProperties);

void vkGetPhysicalDeviceExternalBufferPropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalBufferInfo*   pExternalBufferInfo,
    VkExternalBufferProperties*                 pExternalBufferProperties);

VkResult vkGetMemoryFdKHR(
    VkDevice                                    device,
    const VkMemoryGetFdInfoKHR*                 pGetFdInfo,
    int*                                        pFd);

VkResult vkGetMemoryFdPropertiesKHR(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    int                                         fd,
    VkMemoryFdPropertiesKHR*                    pMemoryFdProperties);

void vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalSemaphoreInfo* pExternalSemaphoreInfo,
    VkExternalSemaphoreProperties*              pExternalSemaphoreProperties);

VkResult vkImportSemaphoreFdKHR(
    VkDevice                                    device,
    const VkImportSemaphoreFdInfoKHR*           pImportSemaphoreFdInfo);

VkResult vkGetSemaphoreFdKHR(
    VkDevice                                    device,
    const VkSemaphoreGetFdInfoKHR*              pGetFdInfo,
    int*                                        pFd);

inline void CmdPushDescriptorSetKHR(
	VkDevice                                    device,
	VkCommandBuffer                             commandBuffer,
	VkPipelineBindPoint                         pipelineBindPoint,
	VkPipelineLayout                            layout,
	uint32_t                                    set,
	uint32_t                                    descriptorWriteCount,
	const VkWriteDescriptorSet*                 pDescriptorWrites)
{
	BKSGE_VK_DEVICE_FUNC(
		device,
		vkCmdPushDescriptorSetKHR,
		commandBuffer,
		pipelineBindPoint,
		layout,
		set,
		descriptorWriteCount,
		pDescriptorWrites);
}

void vkCmdPushDescriptorSetWithTemplateKHR(
    VkCommandBuffer                             commandBuffer,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    VkPipelineLayout                            layout,
    uint32_t                                    set,
    const void*                                 pData);

VkResult vkCreateDescriptorUpdateTemplateKHR(
    VkDevice                                    device,
    const VkDescriptorUpdateTemplateCreateInfo* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDescriptorUpdateTemplate*                 pDescriptorUpdateTemplate);

void vkDestroyDescriptorUpdateTemplateKHR(
    VkDevice                                    device,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    const VkAllocationCallbacks*                pAllocator);

void vkUpdateDescriptorSetWithTemplateKHR(
    VkDevice                                    device,
    VkDescriptorSet                             descriptorSet,
    VkDescriptorUpdateTemplate                  descriptorUpdateTemplate,
    const void*                                 pData);

VkResult vkCreateRenderPass2KHR(
    VkDevice                                    device,
    const VkRenderPassCreateInfo2KHR*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkRenderPass*                               pRenderPass);

void vkCmdBeginRenderPass2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkRenderPassBeginInfo*                pRenderPassBegin,
    const VkSubpassBeginInfoKHR*                pSubpassBeginInfo);

void vkCmdNextSubpass2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkSubpassBeginInfoKHR*                pSubpassBeginInfo,
    const VkSubpassEndInfoKHR*                  pSubpassEndInfo);

void vkCmdEndRenderPass2KHR(
    VkCommandBuffer                             commandBuffer,
    const VkSubpassEndInfoKHR*                  pSubpassEndInfo);

VkResult vkGetSwapchainStatusKHR(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain);

void vkGetPhysicalDeviceExternalFencePropertiesKHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceExternalFenceInfo*    pExternalFenceInfo,
    VkExternalFenceProperties*                  pExternalFenceProperties);

VkResult vkImportFenceFdKHR(
    VkDevice                                    device,
    const VkImportFenceFdInfoKHR*               pImportFenceFdInfo);

VkResult vkGetFenceFdKHR(
    VkDevice                                    device,
    const VkFenceGetFdInfoKHR*                  pGetFdInfo,
    int*                                        pFd);

VkResult vkGetPhysicalDeviceSurfaceCapabilities2KHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    VkSurfaceCapabilities2KHR*                  pSurfaceCapabilities);

VkResult vkGetPhysicalDeviceSurfaceFormats2KHR(
    VkPhysicalDevice                            physicalDevice,
    const VkPhysicalDeviceSurfaceInfo2KHR*      pSurfaceInfo,
    uint32_t*                                   pSurfaceFormatCount,
    VkSurfaceFormat2KHR*                        pSurfaceFormats);

VkResult vkGetPhysicalDeviceDisplayProperties2KHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkDisplayProperties2KHR*                    pProperties);

VkResult vkGetPhysicalDeviceDisplayPlaneProperties2KHR(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkDisplayPlaneProperties2KHR*               pProperties);

VkResult vkGetDisplayModeProperties2KHR(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display,
    uint32_t*                                   pPropertyCount,
    VkDisplayModeProperties2KHR*                pProperties);

VkResult vkGetDisplayPlaneCapabilities2KHR(
    VkPhysicalDevice                            physicalDevice,
    const VkDisplayPlaneInfo2KHR*               pDisplayPlaneInfo,
    VkDisplayPlaneCapabilities2KHR*             pCapabilities);

void vkGetImageMemoryRequirements2KHR(
    VkDevice                                    device,
    const VkImageMemoryRequirementsInfo2*       pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements);

void vkGetBufferMemoryRequirements2KHR(
    VkDevice                                    device,
    const VkBufferMemoryRequirementsInfo2*      pInfo,
    VkMemoryRequirements2*                      pMemoryRequirements);

void vkGetImageSparseMemoryRequirements2KHR(
    VkDevice                                    device,
    const VkImageSparseMemoryRequirementsInfo2* pInfo,
    uint32_t*                                   pSparseMemoryRequirementCount,
    VkSparseImageMemoryRequirements2*           pSparseMemoryRequirements);

VkResult vkCreateSamplerYcbcrConversionKHR(
    VkDevice                                    device,
    const VkSamplerYcbcrConversionCreateInfo*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSamplerYcbcrConversion*                   pYcbcrConversion);

void vkDestroySamplerYcbcrConversionKHR(
    VkDevice                                    device,
    VkSamplerYcbcrConversion                    ycbcrConversion,
    const VkAllocationCallbacks*                pAllocator);

VkResult vkBindBufferMemory2KHR(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindBufferMemoryInfo*               pBindInfos);

VkResult vkBindImageMemory2KHR(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindImageMemoryInfo*                pBindInfos);

void vkGetDescriptorSetLayoutSupportKHR(
    VkDevice                                    device,
    const VkDescriptorSetLayoutCreateInfo*      pCreateInfo,
    VkDescriptorSetLayoutSupport*               pSupport);

void vkCmdDrawIndirectCountKHR(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride);

void vkCmdDrawIndexedIndirectCountKHR(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride);

inline VkResult CreateDebugReportCallbackEXT(
	VkInstance instance,
	const VkDebugReportCallbackCreateInfoEXT* pCreateInfo,
	const VkAllocationCallbacks* pAllocator,
	VkDebugReportCallbackEXT* pCallback)
{
	BKSGE_VK_INSTANCE_FUNC(
		instance,
		vkCreateDebugReportCallbackEXT,
		instance,
		pCreateInfo,
		pAllocator,
		pCallback);
	return VK_SUCCESS;
}

inline void DestroyDebugReportCallbackEXT(
	VkInstance instance,
	VkDebugReportCallbackEXT callback,
	const VkAllocationCallbacks* pAllocator)
{
	BKSGE_VK_INSTANCE_FUNC(
		instance,
		vkDestroyDebugReportCallbackEXT,
		instance,
		callback,
		pAllocator);
}

void vkDebugReportMessageEXT(
    VkInstance                                  instance,
    VkDebugReportFlagsEXT                       flags,
    VkDebugReportObjectTypeEXT                  objectType,
    uint64_t                                    object,
    size_t                                      location,
    int32_t                                     messageCode,
    const char*                                 pLayerPrefix,
    const char*                                 pMessage);

VkResult vkDebugMarkerSetObjectTagEXT(
    VkDevice                                    device,
    const VkDebugMarkerObjectTagInfoEXT*        pTagInfo);

VkResult vkDebugMarkerSetObjectNameEXT(
    VkDevice                                    device,
    const VkDebugMarkerObjectNameInfoEXT*       pNameInfo);

void vkCmdDebugMarkerBeginEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugMarkerMarkerInfoEXT*           pMarkerInfo);

void vkCmdDebugMarkerEndEXT(
    VkCommandBuffer                             commandBuffer);

void vkCmdDebugMarkerInsertEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugMarkerMarkerInfoEXT*           pMarkerInfo);

void vkCmdBindTransformFeedbackBuffersEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstBinding,
    uint32_t                                    bindingCount,
    const VkBuffer*                             pBuffers,
    const VkDeviceSize*                         pOffsets,
    const VkDeviceSize*                         pSizes);

void vkCmdBeginTransformFeedbackEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstCounterBuffer,
    uint32_t                                    counterBufferCount,
    const VkBuffer*                             pCounterBuffers,
    const VkDeviceSize*                         pCounterBufferOffsets);

void vkCmdEndTransformFeedbackEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstCounterBuffer,
    uint32_t                                    counterBufferCount,
    const VkBuffer*                             pCounterBuffers,
    const VkDeviceSize*                         pCounterBufferOffsets);

void vkCmdBeginQueryIndexedEXT(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    query,
    VkQueryControlFlags                         flags,
    uint32_t                                    index);

void vkCmdEndQueryIndexedEXT(
    VkCommandBuffer                             commandBuffer,
    VkQueryPool                                 queryPool,
    uint32_t                                    query,
    uint32_t                                    index);

void vkCmdDrawIndirectByteCountEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    instanceCount,
    uint32_t                                    firstInstance,
    VkBuffer                                    counterBuffer,
    VkDeviceSize                                counterBufferOffset,
    uint32_t                                    counterOffset,
    uint32_t                                    vertexStride);

uint32_t vkGetImageViewHandleNVX(
    VkDevice                                    device,
    const VkImageViewHandleInfoNVX*             pInfo);

void vkCmdDrawIndirectCountAMD(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride);

void vkCmdDrawIndexedIndirectCountAMD(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride);

VkResult vkGetShaderInfoAMD(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    VkShaderStageFlagBits                       shaderStage,
    VkShaderInfoTypeAMD                         infoType,
    size_t*                                     pInfoSize,
    void*                                       pInfo);

VkResult vkGetPhysicalDeviceExternalImageFormatPropertiesNV(
    VkPhysicalDevice                            physicalDevice,
    VkFormat                                    format,
    VkImageType                                 type,
    VkImageTiling                               tiling,
    VkImageUsageFlags                           usage,
    VkImageCreateFlags                          flags,
    VkExternalMemoryHandleTypeFlagsNV           externalHandleType,
    VkExternalImageFormatPropertiesNV*          pExternalImageFormatProperties);

void vkCmdBeginConditionalRenderingEXT(
    VkCommandBuffer                             commandBuffer,
    const VkConditionalRenderingBeginInfoEXT*   pConditionalRenderingBegin);

void vkCmdEndConditionalRenderingEXT(
    VkCommandBuffer                             commandBuffer);

void vkCmdProcessCommandsNVX(
    VkCommandBuffer                             commandBuffer,
    const VkCmdProcessCommandsInfoNVX*          pProcessCommandsInfo);

void vkCmdReserveSpaceForCommandsNVX(
    VkCommandBuffer                             commandBuffer,
    const VkCmdReserveSpaceForCommandsInfoNVX*  pReserveSpaceInfo);

VkResult vkCreateIndirectCommandsLayoutNVX(
    VkDevice                                    device,
    const VkIndirectCommandsLayoutCreateInfoNVX* pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkIndirectCommandsLayoutNVX*                pIndirectCommandsLayout);

void vkDestroyIndirectCommandsLayoutNVX(
    VkDevice                                    device,
    VkIndirectCommandsLayoutNVX                 indirectCommandsLayout,
    const VkAllocationCallbacks*                pAllocator);

VkResult vkCreateObjectTableNVX(
    VkDevice                                    device,
    const VkObjectTableCreateInfoNVX*           pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkObjectTableNVX*                           pObjectTable);

void vkDestroyObjectTableNVX(
    VkDevice                                    device,
    VkObjectTableNVX                            objectTable,
    const VkAllocationCallbacks*                pAllocator);

VkResult vkRegisterObjectsNVX(
    VkDevice                                    device,
    VkObjectTableNVX                            objectTable,
    uint32_t                                    objectCount,
    const VkObjectTableEntryNVX* const*         ppObjectTableEntries,
    const uint32_t*                             pObjectIndices);

VkResult vkUnregisterObjectsNVX(
    VkDevice                                    device,
    VkObjectTableNVX                            objectTable,
    uint32_t                                    objectCount,
    const VkObjectEntryTypeNVX*                 pObjectEntryTypes,
    const uint32_t*                             pObjectIndices);

void vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX(
    VkPhysicalDevice                            physicalDevice,
    VkDeviceGeneratedCommandsFeaturesNVX*       pFeatures,
    VkDeviceGeneratedCommandsLimitsNVX*         pLimits);

void vkCmdSetViewportWScalingNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkViewportWScalingNV*                 pViewportWScalings);

VkResult vkReleaseDisplayEXT(
    VkPhysicalDevice                            physicalDevice,
    VkDisplayKHR                                display);

VkResult vkGetPhysicalDeviceSurfaceCapabilities2EXT(
    VkPhysicalDevice                            physicalDevice,
    VkSurfaceKHR                                surface,
    VkSurfaceCapabilities2EXT*                  pSurfaceCapabilities);

VkResult vkDisplayPowerControlEXT(
    VkDevice                                    device,
    VkDisplayKHR                                display,
    const VkDisplayPowerInfoEXT*                pDisplayPowerInfo);

VkResult vkRegisterDeviceEventEXT(
    VkDevice                                    device,
    const VkDeviceEventInfoEXT*                 pDeviceEventInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence);

VkResult vkRegisterDisplayEventEXT(
    VkDevice                                    device,
    VkDisplayKHR                                display,
    const VkDisplayEventInfoEXT*                pDisplayEventInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkFence*                                    pFence);

VkResult vkGetSwapchainCounterEXT(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkSurfaceCounterFlagBitsEXT                 counter,
    uint64_t*                                   pCounterValue);

VkResult vkGetRefreshCycleDurationGOOGLE(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    VkRefreshCycleDurationGOOGLE*               pDisplayTimingProperties);

VkResult vkGetPastPresentationTimingGOOGLE(
    VkDevice                                    device,
    VkSwapchainKHR                              swapchain,
    uint32_t*                                   pPresentationTimingCount,
    VkPastPresentationTimingGOOGLE*             pPresentationTimings);

void vkCmdSetDiscardRectangleEXT(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstDiscardRectangle,
    uint32_t                                    discardRectangleCount,
    const VkRect2D*                             pDiscardRectangles);

void vkSetHdrMetadataEXT(
    VkDevice                                    device,
    uint32_t                                    swapchainCount,
    const VkSwapchainKHR*                       pSwapchains,
    const VkHdrMetadataEXT*                     pMetadata);

VkResult vkSetDebugUtilsObjectNameEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectNameInfoEXT*        pNameInfo);

VkResult vkSetDebugUtilsObjectTagEXT(
    VkDevice                                    device,
    const VkDebugUtilsObjectTagInfoEXT*         pTagInfo);

void vkQueueBeginDebugUtilsLabelEXT(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo);

void vkQueueEndDebugUtilsLabelEXT(
    VkQueue                                     queue);

void vkQueueInsertDebugUtilsLabelEXT(
    VkQueue                                     queue,
    const VkDebugUtilsLabelEXT*                 pLabelInfo);

void vkCmdBeginDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo);

void vkCmdEndDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer);

void vkCmdInsertDebugUtilsLabelEXT(
    VkCommandBuffer                             commandBuffer,
    const VkDebugUtilsLabelEXT*                 pLabelInfo);

VkResult vkCreateDebugUtilsMessengerEXT(
    VkInstance                                  instance,
    const VkDebugUtilsMessengerCreateInfoEXT*   pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkDebugUtilsMessengerEXT*                   pMessenger);

void vkDestroyDebugUtilsMessengerEXT(
    VkInstance                                  instance,
    VkDebugUtilsMessengerEXT                    messenger,
    const VkAllocationCallbacks*                pAllocator);

void vkSubmitDebugUtilsMessageEXT(
    VkInstance                                  instance,
    VkDebugUtilsMessageSeverityFlagBitsEXT      messageSeverity,
    VkDebugUtilsMessageTypeFlagsEXT             messageTypes,
    const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData);

void vkCmdSetSampleLocationsEXT(
    VkCommandBuffer                             commandBuffer,
    const VkSampleLocationsInfoEXT*             pSampleLocationsInfo);

void vkGetPhysicalDeviceMultisamplePropertiesEXT(
    VkPhysicalDevice                            physicalDevice,
    VkSampleCountFlagBits                       samples,
    VkMultisamplePropertiesEXT*                 pMultisampleProperties);

VkResult vkGetImageDrmFormatModifierPropertiesEXT(
    VkDevice                                    device,
    VkImage                                     image,
    VkImageDrmFormatModifierPropertiesEXT*      pProperties);

VkResult vkCreateValidationCacheEXT(
    VkDevice                                    device,
    const VkValidationCacheCreateInfoEXT*       pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkValidationCacheEXT*                       pValidationCache);

void vkDestroyValidationCacheEXT(
    VkDevice                                    device,
    VkValidationCacheEXT                        validationCache,
    const VkAllocationCallbacks*                pAllocator);

VkResult vkMergeValidationCachesEXT(
    VkDevice                                    device,
    VkValidationCacheEXT                        dstCache,
    uint32_t                                    srcCacheCount,
    const VkValidationCacheEXT*                 pSrcCaches);

VkResult vkGetValidationCacheDataEXT(
    VkDevice                                    device,
    VkValidationCacheEXT                        validationCache,
    size_t*                                     pDataSize,
    void*                                       pData);

void vkCmdBindShadingRateImageNV(
    VkCommandBuffer                             commandBuffer,
    VkImageView                                 imageView,
    VkImageLayout                               imageLayout);

void vkCmdSetViewportShadingRatePaletteNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstViewport,
    uint32_t                                    viewportCount,
    const VkShadingRatePaletteNV*               pShadingRatePalettes);

void vkCmdSetCoarseSampleOrderNV(
    VkCommandBuffer                             commandBuffer,
    VkCoarseSampleOrderTypeNV                   sampleOrderType,
    uint32_t                                    customSampleOrderCount,
    const VkCoarseSampleOrderCustomNV*          pCustomSampleOrders);

VkResult vkCreateAccelerationStructureNV(
    VkDevice                                    device,
    const VkAccelerationStructureCreateInfoNV*  pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkAccelerationStructureNV*                  pAccelerationStructure);

void vkDestroyAccelerationStructureNV(
    VkDevice                                    device,
    VkAccelerationStructureNV                   accelerationStructure,
    const VkAllocationCallbacks*                pAllocator);

void vkGetAccelerationStructureMemoryRequirementsNV(
    VkDevice                                    device,
    const VkAccelerationStructureMemoryRequirementsInfoNV* pInfo,
    VkMemoryRequirements2KHR*                   pMemoryRequirements);

VkResult vkBindAccelerationStructureMemoryNV(
    VkDevice                                    device,
    uint32_t                                    bindInfoCount,
    const VkBindAccelerationStructureMemoryInfoNV* pBindInfos);

void vkCmdBuildAccelerationStructureNV(
    VkCommandBuffer                             commandBuffer,
    const VkAccelerationStructureInfoNV*        pInfo,
    VkBuffer                                    instanceData,
    VkDeviceSize                                instanceOffset,
    VkBool32                                    update,
    VkAccelerationStructureNV                   dst,
    VkAccelerationStructureNV                   src,
    VkBuffer                                    scratch,
    VkDeviceSize                                scratchOffset);

void vkCmdCopyAccelerationStructureNV(
    VkCommandBuffer                             commandBuffer,
    VkAccelerationStructureNV                   dst,
    VkAccelerationStructureNV                   src,
    VkCopyAccelerationStructureModeNV           mode);

void vkCmdTraceRaysNV(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    raygenShaderBindingTableBuffer,
    VkDeviceSize                                raygenShaderBindingOffset,
    VkBuffer                                    missShaderBindingTableBuffer,
    VkDeviceSize                                missShaderBindingOffset,
    VkDeviceSize                                missShaderBindingStride,
    VkBuffer                                    hitShaderBindingTableBuffer,
    VkDeviceSize                                hitShaderBindingOffset,
    VkDeviceSize                                hitShaderBindingStride,
    VkBuffer                                    callableShaderBindingTableBuffer,
    VkDeviceSize                                callableShaderBindingOffset,
    VkDeviceSize                                callableShaderBindingStride,
    uint32_t                                    width,
    uint32_t                                    height,
    uint32_t                                    depth);

VkResult vkCreateRayTracingPipelinesNV(
    VkDevice                                    device,
    VkPipelineCache                             pipelineCache,
    uint32_t                                    createInfoCount,
    const VkRayTracingPipelineCreateInfoNV*     pCreateInfos,
    const VkAllocationCallbacks*                pAllocator,
    VkPipeline*                                 pPipelines);

VkResult vkGetRayTracingShaderGroupHandlesNV(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    firstGroup,
    uint32_t                                    groupCount,
    size_t                                      dataSize,
    void*                                       pData);

VkResult vkGetAccelerationStructureHandleNV(
    VkDevice                                    device,
    VkAccelerationStructureNV                   accelerationStructure,
    size_t                                      dataSize,
    void*                                       pData);

void vkCmdWriteAccelerationStructuresPropertiesNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    accelerationStructureCount,
    const VkAccelerationStructureNV*            pAccelerationStructures,
    VkQueryType                                 queryType,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery);

VkResult vkCompileDeferredNV(
    VkDevice                                    device,
    VkPipeline                                  pipeline,
    uint32_t                                    shader);

VkResult vkGetMemoryHostPointerPropertiesEXT(
    VkDevice                                    device,
    VkExternalMemoryHandleTypeFlagBits          handleType,
    const void*                                 pHostPointer,
    VkMemoryHostPointerPropertiesEXT*           pMemoryHostPointerProperties);

void vkCmdWriteBufferMarkerAMD(
    VkCommandBuffer                             commandBuffer,
    VkPipelineStageFlagBits                     pipelineStage,
    VkBuffer                                    dstBuffer,
    VkDeviceSize                                dstOffset,
    uint32_t                                    marker);

VkResult vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pTimeDomainCount,
    VkTimeDomainEXT*                            pTimeDomains);

VkResult vkGetCalibratedTimestampsEXT(
    VkDevice                                    device,
    uint32_t                                    timestampCount,
    const VkCalibratedTimestampInfoEXT*         pTimestampInfos,
    uint64_t*                                   pTimestamps,
    uint64_t*                                   pMaxDeviation);

void vkCmdDrawMeshTasksNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    taskCount,
    uint32_t                                    firstTask);

void vkCmdDrawMeshTasksIndirectNV(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    uint32_t                                    drawCount,
    uint32_t                                    stride);

void vkCmdDrawMeshTasksIndirectCountNV(
    VkCommandBuffer                             commandBuffer,
    VkBuffer                                    buffer,
    VkDeviceSize                                offset,
    VkBuffer                                    countBuffer,
    VkDeviceSize                                countBufferOffset,
    uint32_t                                    maxDrawCount,
    uint32_t                                    stride);

void vkCmdSetExclusiveScissorNV(
    VkCommandBuffer                             commandBuffer,
    uint32_t                                    firstExclusiveScissor,
    uint32_t                                    exclusiveScissorCount,
    const VkRect2D*                             pExclusiveScissors);

void vkCmdSetCheckpointNV(
    VkCommandBuffer                             commandBuffer,
    const void*                                 pCheckpointMarker);

void vkGetQueueCheckpointDataNV(
    VkQueue                                     queue,
    uint32_t*                                   pCheckpointDataCount,
    VkCheckpointDataNV*                         pCheckpointData);

VkResult vkInitializePerformanceApiINTEL(
    VkDevice                                    device,
    const VkInitializePerformanceApiInfoINTEL*  pInitializeInfo);

void vkUninitializePerformanceApiINTEL(
    VkDevice                                    device);

VkResult vkCmdSetPerformanceMarkerINTEL(
    VkCommandBuffer                             commandBuffer,
    const VkPerformanceMarkerInfoINTEL*         pMarkerInfo);

VkResult vkCmdSetPerformanceStreamMarkerINTEL(
    VkCommandBuffer                             commandBuffer,
    const VkPerformanceStreamMarkerInfoINTEL*   pMarkerInfo);

VkResult vkCmdSetPerformanceOverrideINTEL(
    VkCommandBuffer                             commandBuffer,
    const VkPerformanceOverrideInfoINTEL*       pOverrideInfo);

VkResult vkAcquirePerformanceConfigurationINTEL(
    VkDevice                                    device,
    const VkPerformanceConfigurationAcquireInfoINTEL* pAcquireInfo,
    VkPerformanceConfigurationINTEL*            pConfiguration);

VkResult vkReleasePerformanceConfigurationINTEL(
    VkDevice                                    device,
    VkPerformanceConfigurationINTEL             configuration);

VkResult vkQueueSetPerformanceConfigurationINTEL(
    VkQueue                                     queue,
    VkPerformanceConfigurationINTEL             configuration);

VkResult vkGetPerformanceParameterINTEL(
    VkDevice                                    device,
    VkPerformanceParameterTypeINTEL             parameter,
    VkPerformanceValueINTEL*                    pValue);

void vkSetLocalDimmingAMD(
    VkDevice                                    device,
    VkSwapchainKHR                              swapChain,
    VkBool32                                    localDimmingEnable);

VkDeviceAddress vkGetBufferDeviceAddressEXT(
    VkDevice                                    device,
    const VkBufferDeviceAddressInfoEXT*         pInfo);

VkResult vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pPropertyCount,
    VkCooperativeMatrixPropertiesNV*            pProperties);

VkResult vkGetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV(
    VkPhysicalDevice                            physicalDevice,
    uint32_t*                                   pCombinationCount,
    VkFramebufferMixedSamplesCombinationNV*     pCombinations);

VkResult vkCreateHeadlessSurfaceEXT(
    VkInstance                                  instance,
    const VkHeadlessSurfaceCreateInfoEXT*       pCreateInfo,
    const VkAllocationCallbacks*                pAllocator,
    VkSurfaceKHR*                               pSurface);

void vkResetQueryPoolEXT(
    VkDevice                                    device,
    VkQueryPool                                 queryPool,
    uint32_t                                    firstQuery,
    uint32_t                                    queryCount);

#undef BKSGE_VK_INSTANCE_FUNC
#undef BKSGE_VK_DEVICE_FUNC

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_VULKAN_CORE_HPP
