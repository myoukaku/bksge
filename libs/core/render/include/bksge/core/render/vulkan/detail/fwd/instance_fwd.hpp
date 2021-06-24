/**
 *	@file	instance_fwd.hpp
 *
 *	@brief	Instance クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_INSTANCE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_INSTANCE_FWD_HPP

#include <bksge/fnd/memory/shared_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Instance;
using InstanceSharedPtr = bksge::shared_ptr<Instance>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_INSTANCE_FWD_HPP
