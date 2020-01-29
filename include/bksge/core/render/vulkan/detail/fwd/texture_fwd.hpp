/**
 *	@file	texture_fwd.hpp
 *
 *	@brief	Texture クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_TEXTURE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_TEXTURE_FWD_HPP

#include <memory>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Texture;
using TextureUniquePtr = std::unique_ptr<Texture>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_TEXTURE_FWD_HPP
