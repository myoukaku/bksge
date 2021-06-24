/**
 *	@file	surface_fwd.hpp
 *
 *	@brief	Surface クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SURFACE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SURFACE_FWD_HPP

#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Surface;
using SurfaceUniquePtr = bksge::unique_ptr<Surface>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_SURFACE_FWD_HPP
