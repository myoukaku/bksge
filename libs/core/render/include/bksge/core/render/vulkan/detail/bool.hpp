/**
 *	@file	bool.hpp
 *
 *	@brief	Bool クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_BOOL_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_BOOL_HPP

#include <bksge/core/render/vulkan/detail/vulkan.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

/**
 *	@brief
 */
class Bool
{
public:
	explicit Bool(bool b);

	operator ::VkBool32() const;

private:
	::VkBool32	m_bool;
};

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/bool_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_BOOL_HPP
