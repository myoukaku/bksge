/**
 *	@file	glsl_to_spv_inl.hpp
 *
 *	@brief	GlslToSpv 関数の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GLSL_TO_SPV_INL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GLSL_TO_SPV_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#include <bksge/core/render/vulkan/detail/glsl_to_spv.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/core/render/vulkan/detail/spirv_h.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

namespace detail
{

inline EShLanguage
FindLanguage(::VkShaderStageFlagBits shader_type)
{
	switch (shader_type)
	{
	case VK_SHADER_STAGE_VERTEX_BIT:					return EShLangVertex;
	case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:		return EShLangTessControl;
	case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:	return EShLangTessEvaluation;
	case VK_SHADER_STAGE_GEOMETRY_BIT:					return EShLangGeometry;
	case VK_SHADER_STAGE_FRAGMENT_BIT:					return EShLangFragment;
	case VK_SHADER_STAGE_COMPUTE_BIT:					return EShLangCompute;
	default:											return EShLangVertex;
	}
}

inline void
InitResources(TBuiltInResource& resources)
{
	resources.maxLights                                   = 32;
	resources.maxClipPlanes                               = 6;
	resources.maxTextureUnits                             = 32;
	resources.maxTextureCoords                            = 32;
	resources.maxVertexAttribs                            = 64;
	resources.maxVertexUniformComponents                  = 4096;
	resources.maxVaryingFloats                            = 64;
	resources.maxVertexTextureImageUnits                  = 32;
	resources.maxCombinedTextureImageUnits                = 80;
	resources.maxTextureImageUnits                        = 32;
	resources.maxFragmentUniformComponents                = 4096;
	resources.maxDrawBuffers                              = 32;
	resources.maxVertexUniformVectors                     = 128;
	resources.maxVaryingVectors                           = 8;
	resources.maxFragmentUniformVectors                   = 16;
	resources.maxVertexOutputVectors                      = 16;
	resources.maxFragmentInputVectors                     = 15;
	resources.minProgramTexelOffset                       = -8;
	resources.maxProgramTexelOffset                       = 7;
	resources.maxClipDistances                            = 8;
	resources.maxComputeWorkGroupCountX                   = 65535;
	resources.maxComputeWorkGroupCountY                   = 65535;
	resources.maxComputeWorkGroupCountZ                   = 65535;
	resources.maxComputeWorkGroupSizeX                    = 1024;
	resources.maxComputeWorkGroupSizeY                    = 1024;
	resources.maxComputeWorkGroupSizeZ                    = 64;
	resources.maxComputeUniformComponents                 = 1024;
	resources.maxComputeTextureImageUnits                 = 16;
	resources.maxComputeImageUniforms                     = 8;
	resources.maxComputeAtomicCounters                    = 8;
	resources.maxComputeAtomicCounterBuffers              = 1;
	resources.maxVaryingComponents                        = 60;
	resources.maxVertexOutputComponents                   = 64;
	resources.maxGeometryInputComponents                  = 64;
	resources.maxGeometryOutputComponents                 = 128;
	resources.maxFragmentInputComponents                  = 128;
	resources.maxImageUnits                               = 8;
	resources.maxCombinedImageUnitsAndFragmentOutputs     = 8;
	resources.maxCombinedShaderOutputResources            = 8;
	resources.maxImageSamples                             = 0;
	resources.maxVertexImageUniforms                      = 0;
	resources.maxTessControlImageUniforms                 = 0;
	resources.maxTessEvaluationImageUniforms              = 0;
	resources.maxGeometryImageUniforms                    = 0;
	resources.maxFragmentImageUniforms                    = 8;
	resources.maxCombinedImageUniforms                    = 8;
	resources.maxGeometryTextureImageUnits                = 16;
	resources.maxGeometryOutputVertices                   = 256;
	resources.maxGeometryTotalOutputComponents            = 1024;
	resources.maxGeometryUniformComponents                = 1024;
	resources.maxGeometryVaryingComponents                = 64;
	resources.maxTessControlInputComponents               = 128;
	resources.maxTessControlOutputComponents              = 128;
	resources.maxTessControlTextureImageUnits             = 16;
	resources.maxTessControlUniformComponents             = 1024;
	resources.maxTessControlTotalOutputComponents         = 4096;
	resources.maxTessEvaluationInputComponents            = 128;
	resources.maxTessEvaluationOutputComponents           = 128;
	resources.maxTessEvaluationTextureImageUnits          = 16;
	resources.maxTessEvaluationUniformComponents          = 1024;
	resources.maxTessPatchComponents                      = 120;
	resources.maxPatchVertices                            = 32;
	resources.maxTessGenLevel                             = 64;
	resources.maxViewports                                = 16;
	resources.maxVertexAtomicCounters                     = 0;
	resources.maxTessControlAtomicCounters                = 0;
	resources.maxTessEvaluationAtomicCounters             = 0;
	resources.maxGeometryAtomicCounters                   = 0;
	resources.maxFragmentAtomicCounters                   = 8;
	resources.maxCombinedAtomicCounters                   = 8;
	resources.maxAtomicCounterBindings                    = 1;
	resources.maxVertexAtomicCounterBuffers               = 0;
	resources.maxTessControlAtomicCounterBuffers          = 0;
	resources.maxTessEvaluationAtomicCounterBuffers       = 0;
	resources.maxGeometryAtomicCounterBuffers             = 0;
	resources.maxFragmentAtomicCounterBuffers             = 1;
	resources.maxCombinedAtomicCounterBuffers             = 1;
	resources.maxAtomicCounterBufferSize                  = 16384;
	resources.maxTransformFeedbackBuffers                 = 4;
	resources.maxTransformFeedbackInterleavedComponents   = 64;
	resources.maxCullDistances                            = 8;
	resources.maxCombinedClipAndCullDistances             = 8;
	resources.maxSamples                                  = 4;
	resources.maxMeshOutputVerticesNV                     = 256;
	resources.maxMeshOutputPrimitivesNV                   = 512;
	resources.maxMeshWorkGroupSizeX_NV                    = 32;
	resources.maxMeshWorkGroupSizeY_NV                    = 1;
	resources.maxMeshWorkGroupSizeZ_NV                    = 1;
	resources.maxTaskWorkGroupSizeX_NV                    = 32;
	resources.maxTaskWorkGroupSizeY_NV                    = 1;
	resources.maxTaskWorkGroupSizeZ_NV                    = 1;
	resources.maxMeshViewCountNV                          = 4;
	resources.limits.nonInductiveForLoops                 = 1;
	resources.limits.whileLoops                           = 1;
	resources.limits.doWhileLoops                         = 1;
	resources.limits.generalUniformIndexing               = 1;
	resources.limits.generalAttributeMatrixVectorIndexing = 1;
	resources.limits.generalVaryingIndexing               = 1;
	resources.limits.generalSamplerIndexing               = 1;
	resources.limits.generalVariableIndexing              = 1;
	resources.limits.generalConstantMatrixVectorIndexing  = 1;
}

}	// namespace detail

BKSGE_INLINE bksge::vector<unsigned int>
GlslToSpv(::VkShaderStageFlagBits shader_type, const char* source)
{
	glslang::InitializeProcess();

	glslang::TProgram program;

	EShLanguage const stage = detail::FindLanguage(shader_type);
	glslang::TShader shader(stage);

	TBuiltInResource resources;
	detail::InitResources(resources);

	shader.setStrings(&source, 1);

	// Enable SPIR-V and Vulkan rules when parsing GLSL
	EShMessages const messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);
	if (!shader.parse(&resources, 100, false, messages))
	{
		puts(shader.getInfoLog());		// TODO
		puts(shader.getInfoDebugLog());	// TODO
		return {};
	}

	program.addShader(&shader);

	if (!program.link(messages))
	{
		puts(program.getInfoLog());		// TODO
		puts(program.getInfoDebugLog());// TODO
		return {};
	}

	bksge::vector<unsigned int> spirv;
	glslang::GlslangToSpv(*program.getIntermediate(stage), spirv);

	glslang::FinalizeProcess();

	return spirv;
}

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_VULKAN_RENDERER

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_INL_GLSL_TO_SPV_INL_HPP
