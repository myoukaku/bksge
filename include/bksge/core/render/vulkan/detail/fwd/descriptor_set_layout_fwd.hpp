/**
 *	@file	descriptor_set_layout_fwd.hpp
 *
 *	@brief	DescriptorSetLayout クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DESCRIPTOR_SET_LAYOUT_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DESCRIPTOR_SET_LAYOUT_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DescriptorSetLayout;
using DescriptorSetLayoutUniquePtr = std::unique_ptr<DescriptorSetLayout>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DESCRIPTOR_SET_LAYOUT_FWD_HPP
