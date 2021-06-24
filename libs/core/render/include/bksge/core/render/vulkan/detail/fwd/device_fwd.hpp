/**
 *	@file	device_fwd.hpp
 *
 *	@brief	Device クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DEVICE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DEVICE_FWD_HPP

#include <bksge/fnd/memory/shared_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Device;
using DeviceSharedPtr = bksge::shared_ptr<Device>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DEVICE_FWD_HPP
