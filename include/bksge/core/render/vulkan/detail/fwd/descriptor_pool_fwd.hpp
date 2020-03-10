/**
 *	@file	descriptor_pool_fwd.hpp
 *
 *	@brief	DescriptorPool クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DESCRIPTOR_POOL_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DESCRIPTOR_POOL_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/shared_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DescriptorPool;
using DescriptorPoolSharedPtr = bksge::shared_ptr<DescriptorPool>;
using DescriptorPoolUniquePtr = bksge::unique_ptr<DescriptorPool>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DESCRIPTOR_POOL_FWD_HPP
