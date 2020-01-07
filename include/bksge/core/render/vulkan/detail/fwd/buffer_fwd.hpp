/**
 *	@file	buffer_fwd.hpp
 *
 *	@brief	Buffer クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_BUFFER_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_BUFFER_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Buffer;
using BufferUniquePtr = std::unique_ptr<Buffer>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_BUFFER_FWD_HPP
