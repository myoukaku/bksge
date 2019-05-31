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
#include <memory>

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
			break;
		case ShaderStage::kFragment:
			return VK_SHADER_STAGE_FRAGMENT_BIT;
		case ShaderStage::kTessellationControl:
			break;
		case ShaderStage::kTessellationEvaluation:
			break;
		default:
			break;
		}
		return VK_SHADER_STAGE_VERTEX_BIT;
	}

	void AddShaderStage(
		VkShaderStageFlagBits stage,
		char const* name,
		std::string const& /*source*/)
	{
		vk::PipelineShaderStageCreateInfo shader_stage;
		shader_stage.stage = stage;
		shader_stage.pName = name;

		std::vector<unsigned int> spv;// = GLSLtoSPV(stage, source);

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
