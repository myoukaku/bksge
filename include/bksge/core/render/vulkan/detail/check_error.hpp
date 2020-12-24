/**
 *	@file	check_error.hpp
 *
 *	@brief	CheckError 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_CHECK_ERROR_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_CHECK_ERROR_HPP

#include <bksge/fnd/string/string.hpp>
#include <vulkan/vulkan_core.h>
#include <stdexcept>

namespace bksge
{

namespace render
{

namespace vk
{

bksge::string to_string(::VkResult res);

class ResultException : public std::runtime_error
{
public:
	explicit ResultException(::VkResult res);
};

::VkResult CheckError(::VkResult res);

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/vulkan/detail/inl/check_error_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_CHECK_ERROR_HPP
