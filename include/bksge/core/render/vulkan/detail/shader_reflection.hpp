/**
 *	@file	shader_reflection.hpp
 *
 *	@brief	ShaderReflection クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_REFLECTION_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_REFLECTION_HPP

#include <bksge/core/render/vulkan/detail/fwd/shader_reflection_fwd.hpp>
#include <bksge/core/render/vulkan/detail/vulkan.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint/uint32_t.hpp>
#include <vector>
#include <string>

namespace bksge
{

namespace render
{

namespace vulkan
{

struct ShaderReflectionUniform
{
	struct Member
	{
		std::string          name;
		bksge::size_t        bytes;
		bksge::uint32_t      offset;
	};

	bksge::uint32_t			set;
	bksge::uint32_t			binding;
	std::string				name;
	::VkDescriptorType		descriptor_type;
	bksge::size_t			bytes;
	::VkShaderStageFlags	stage_flags;
	std::vector<Member>	members;
};

class ShaderReflection
{
public:
	explicit ShaderReflection(
		std::vector<std::vector<unsigned int>> const& spv_list);

	~ShaderReflection();

	bksge::uint32_t GetMaxSets(void) const;

	bksge::uint32_t GetUniformCount(::VkDescriptorType descriptor_type) const;

	using Uniforms = std::vector<ShaderReflectionUniform>;

	Uniforms const& GetUniforms(void) const;

private:
	// noncopyable
	ShaderReflection(ShaderReflection const&) = delete;
	ShaderReflection& operator=(ShaderReflection const&) = delete;

private:
	bksge::uint32_t	m_max_sets = 0;
	Uniforms		m_uniforms;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/shader_reflection_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_SHADER_REFLECTION_HPP
