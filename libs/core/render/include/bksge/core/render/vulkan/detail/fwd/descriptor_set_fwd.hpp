/**
 *	@file	descriptor_set_fwd.hpp
 *
 *	@brief	DescriptorSet クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DESCRIPTOR_SET_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DESCRIPTOR_SET_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DescriptorSet;
using DescriptorSetUniquePtr = bksge::unique_ptr<DescriptorSet>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DESCRIPTOR_SET_FWD_HPP
