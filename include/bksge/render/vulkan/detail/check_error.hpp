/**
 *	@file	check_error.hpp
 *
 *	@brief	CheckError 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_VULKAN_DETAIL_CHECK_ERROR_HPP
#define BKSGE_RENDER_VULKAN_DETAIL_CHECK_ERROR_HPP

#include <bksge/render/vulkan/detail/vulkan_h.hpp>
#include <stdexcept>
#include <string>

namespace bksge
{

namespace render
{

namespace vk
{

std::string to_string(::VkResult res);

class ResultException : public std::runtime_error
{
public:
	explicit ResultException(::VkResult res);
};

::VkResult CheckError(::VkResult res);

}	// namespace vk

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/vulkan/detail/inl/check_error_inl.hpp>
#endif

#endif // BKSGE_RENDER_VULKAN_DETAIL_CHECK_ERROR_HPP
