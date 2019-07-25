/**
 *	@file	shader_stage.hpp
 *
 *	@brief	ShaderStages クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_SHADER_STAGE_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_SHADER_STAGE_HPP

#include <bksge/render/vulkan/detail/vulkan.hpp>
#include <bksge/render/vulkan/detail/device.hpp>
#include <bksge/render/shader.hpp>
#include <SPIRV/GlslangToSpv.h>
#include <memory>
#include <string>
#include <vector>

namespace bksge
{

namespace render
{

namespace vk
{

struct PipelineShaderStageCreateInfo : public ::VkPipelineShaderStageCreateInfo
{
	PipelineShaderStageCreateInfo(void)
	{
		sType               = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		pNext               = nullptr;
		flags               = 0;
		stage               = VK_SHADER_STAGE_VERTEX_BIT;
		module              = VK_NULL_HANDLE;
		pName               = nullptr;
		pSpecializationInfo = nullptr;
	}
};

struct ShaderModuleCreateInfo : public ::VkShaderModuleCreateInfo
{
	ShaderModuleCreateInfo(void)
	{
		sType    = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		pNext    = nullptr;
		flags    = 0;
		codeSize = 0;
		pCode    = nullptr;
	}
};

class ShaderStages
{
public:
	explicit ShaderStages(
		std::shared_ptr<vk::Device> const& device,
		Shader const& shader)
		: m_device(device)
	{
		for (auto&& it : shader)
		{
			auto const& stage = it.first;
			auto const& source = it.second;

			AddShaderStage(ToVkShaderStage(stage), "main", source);
		}
	}

	~ShaderStages()
	{
		for (auto&& shader_stage : m_shader_stages)
		{
			vk::DestroyShaderModule(*m_device, shader_stage.module, nullptr);
		}
	}

	vk::PipelineShaderStageCreateInfo const* GetPtr() const
	{
		return m_shader_stages.data();
	}

	std::uint32_t GetCount() const
	{
		return static_cast<std::uint32_t>(m_shader_stages.size());
	}

private:
	static VkShaderStageFlagBits ToVkShaderStage(bksge::ShaderStage stage)
	{
		switch (stage)
		{
		case ShaderStage::kVertex:
			return VK_SHADER_STAGE_VERTEX_BIT;
		case ShaderStage::kGeometry:
			return VK_SHADER_STAGE_GEOMETRY_BIT;
		case ShaderStage::kFragment:
			return VK_SHADER_STAGE_FRAGMENT_BIT;
		case ShaderStage::kTessellationControl:
			return VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
		case ShaderStage::kTessellationEvaluation:
			return VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
		default:
			break;
		}
		return VK_SHADER_STAGE_VERTEX_BIT;
	}

	static EShLanguage FindLanguage(VkShaderStageFlagBits shader_type)
	{
		switch (shader_type)
		{
		case VK_SHADER_STAGE_VERTEX_BIT:
			return EShLangVertex;
		case VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT:
			return EShLangTessControl;
		case VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT:
			return EShLangTessEvaluation;
		case VK_SHADER_STAGE_GEOMETRY_BIT:
			return EShLangGeometry;
		case VK_SHADER_STAGE_FRAGMENT_BIT:
			return EShLangFragment;
		case VK_SHADER_STAGE_COMPUTE_BIT:
			return EShLangCompute;
		default:
			return EShLangVertex;
		}
	}

	static void init_resources(TBuiltInResource& Resources)
	{
		Resources.maxLights = 32;
		Resources.maxClipPlanes = 6;
		Resources.maxTextureUnits = 32;
		Resources.maxTextureCoords = 32;
		Resources.maxVertexAttribs = 64;
		Resources.maxVertexUniformComponents = 4096;
		Resources.maxVaryingFloats = 64;
		Resources.maxVertexTextureImageUnits = 32;
		Resources.maxCombinedTextureImageUnits = 80;
		Resources.maxTextureImageUnits = 32;
		Resources.maxFragmentUniformComponents = 4096;
		Resources.maxDrawBuffers = 32;
		Resources.maxVertexUniformVectors = 128;
		Resources.maxVaryingVectors = 8;
		Resources.maxFragmentUniformVectors = 16;
		Resources.maxVertexOutputVectors = 16;
		Resources.maxFragmentInputVectors = 15;
		Resources.minProgramTexelOffset = -8;
		Resources.maxProgramTexelOffset = 7;
		Resources.maxClipDistances = 8;
		Resources.maxComputeWorkGroupCountX = 65535;
		Resources.maxComputeWorkGroupCountY = 65535;
		Resources.maxComputeWorkGroupCountZ = 65535;
		Resources.maxComputeWorkGroupSizeX = 1024;
		Resources.maxComputeWorkGroupSizeY = 1024;
		Resources.maxComputeWorkGroupSizeZ = 64;
		Resources.maxComputeUniformComponents = 1024;
		Resources.maxComputeTextureImageUnits = 16;
		Resources.maxComputeImageUniforms = 8;
		Resources.maxComputeAtomicCounters = 8;
		Resources.maxComputeAtomicCounterBuffers = 1;
		Resources.maxVaryingComponents = 60;
		Resources.maxVertexOutputComponents = 64;
		Resources.maxGeometryInputComponents = 64;
		Resources.maxGeometryOutputComponents = 128;
		Resources.maxFragmentInputComponents = 128;
		Resources.maxImageUnits = 8;
		Resources.maxCombinedImageUnitsAndFragmentOutputs = 8;
		Resources.maxCombinedShaderOutputResources = 8;
		Resources.maxImageSamples = 0;
		Resources.maxVertexImageUniforms = 0;
		Resources.maxTessControlImageUniforms = 0;
		Resources.maxTessEvaluationImageUniforms = 0;
		Resources.maxGeometryImageUniforms = 0;
		Resources.maxFragmentImageUniforms = 8;
		Resources.maxCombinedImageUniforms = 8;
		Resources.maxGeometryTextureImageUnits = 16;
		Resources.maxGeometryOutputVertices = 256;
		Resources.maxGeometryTotalOutputComponents = 1024;
		Resources.maxGeometryUniformComponents = 1024;
		Resources.maxGeometryVaryingComponents = 64;
		Resources.maxTessControlInputComponents = 128;
		Resources.maxTessControlOutputComponents = 128;
		Resources.maxTessControlTextureImageUnits = 16;
		Resources.maxTessControlUniformComponents = 1024;
		Resources.maxTessControlTotalOutputComponents = 4096;
		Resources.maxTessEvaluationInputComponents = 128;
		Resources.maxTessEvaluationOutputComponents = 128;
		Resources.maxTessEvaluationTextureImageUnits = 16;
		Resources.maxTessEvaluationUniformComponents = 1024;
		Resources.maxTessPatchComponents = 120;
		Resources.maxPatchVertices = 32;
		Resources.maxTessGenLevel = 64;
		Resources.maxViewports = 16;
		Resources.maxVertexAtomicCounters = 0;
		Resources.maxTessControlAtomicCounters = 0;
		Resources.maxTessEvaluationAtomicCounters = 0;
		Resources.maxGeometryAtomicCounters = 0;
		Resources.maxFragmentAtomicCounters = 8;
		Resources.maxCombinedAtomicCounters = 8;
		Resources.maxAtomicCounterBindings = 1;
		Resources.maxVertexAtomicCounterBuffers = 0;
		Resources.maxTessControlAtomicCounterBuffers = 0;
		Resources.maxTessEvaluationAtomicCounterBuffers = 0;
		Resources.maxGeometryAtomicCounterBuffers = 0;
		Resources.maxFragmentAtomicCounterBuffers = 1;
		Resources.maxCombinedAtomicCounterBuffers = 1;
		Resources.maxAtomicCounterBufferSize = 16384;
		Resources.maxTransformFeedbackBuffers = 4;
		Resources.maxTransformFeedbackInterleavedComponents = 64;
		Resources.maxCullDistances = 8;
		Resources.maxCombinedClipAndCullDistances = 8;
		Resources.maxSamples = 4;
		Resources.maxMeshOutputVerticesNV = 256;
		Resources.maxMeshOutputPrimitivesNV = 512;
		Resources.maxMeshWorkGroupSizeX_NV = 32;
		Resources.maxMeshWorkGroupSizeY_NV = 1;
		Resources.maxMeshWorkGroupSizeZ_NV = 1;
		Resources.maxTaskWorkGroupSizeX_NV = 32;
		Resources.maxTaskWorkGroupSizeY_NV = 1;
		Resources.maxTaskWorkGroupSizeZ_NV = 1;
		Resources.maxMeshViewCountNV = 4;
		Resources.limits.nonInductiveForLoops = 1;
		Resources.limits.whileLoops = 1;
		Resources.limits.doWhileLoops = 1;
		Resources.limits.generalUniformIndexing = 1;
		Resources.limits.generalAttributeMatrixVectorIndexing = 1;
		Resources.limits.generalVaryingIndexing = 1;
		Resources.limits.generalSamplerIndexing = 1;
		Resources.limits.generalVariableIndexing = 1;
		Resources.limits.generalConstantMatrixVectorIndexing = 1;
	}

	static std::vector<unsigned int>
		GLSLtoSPV(VkShaderStageFlagBits shader_type, const char* pshader)
	{
		glslang::InitializeProcess();

		EShLanguage stage = FindLanguage(shader_type);
		glslang::TShader shader(stage);
		glslang::TProgram program;
		const char* shaderStrings[1];
		TBuiltInResource Resources ={};
		init_resources(Resources);

		// Enable SPIR-V and Vulkan rules when parsing GLSL
		EShMessages messages = (EShMessages)(EShMsgSpvRules | EShMsgVulkanRules);

		shaderStrings[0] = pshader;
		shader.setStrings(shaderStrings, 1);

		if (!shader.parse(&Resources, 100, false, messages))
		{
			puts(shader.getInfoLog());	// TODO
			puts(shader.getInfoDebugLog());	// TODO
			return {};
		}

		program.addShader(&shader);

		//
		// Program-level processing...
		//

		if (!program.link(messages))
		{
			puts(shader.getInfoLog());	// TODO
			puts(shader.getInfoDebugLog());	// TODO
			fflush(stdout);
			return {};
		}

		std::vector<unsigned int> spirv;
		glslang::GlslangToSpv(*program.getIntermediate(stage), spirv);

		glslang::FinalizeProcess();

		return spirv;
	}

	void AddShaderStage(
		VkShaderStageFlagBits stage,
		char const* name,
		std::string const& source)
	{
		vk::PipelineShaderStageCreateInfo shader_stage;
		shader_stage.stage = stage;
		shader_stage.pName = name;

		std::vector<unsigned int> spv = GLSLtoSPV(stage, source.c_str());

		vk::ShaderModuleCreateInfo module_create_info;
		module_create_info.codeSize = spv.size() * sizeof(unsigned int);
		module_create_info.pCode    = spv.data();

		vk::CreateShaderModule(*m_device, &module_create_info, nullptr, &shader_stage.module);

		m_shader_stages.push_back(shader_stage);
	}

private:
	std::vector<vk::PipelineShaderStageCreateInfo>	m_shader_stages;
	std::shared_ptr<vk::Device>						m_device;
};

}	// namespace vk

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_VULKAN_DETAIL_SHADER_STAGE_HPP
