/**
 *	@file	device_memory_fwd.hpp
 *
 *	@brief	DeviceMemory クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DEVICE_MEMORY_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DEVICE_MEMORY_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class DeviceMemory;
using DeviceMemoryUniquePtr = std::unique_ptr<DeviceMemory>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_DEVICE_MEMORY_FWD_HPP
