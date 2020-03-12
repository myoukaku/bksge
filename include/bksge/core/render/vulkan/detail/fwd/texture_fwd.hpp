/**
 *	@file	texture_fwd.hpp
 *
 *	@brief	Texture クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_TEXTURE_FWD_HPP
#define BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_TEXTURE_FWD_HPP

#include <bksge/core/render/detail/identifier.hpp>
#include <memory>
#include <map>

namespace bksge
{

namespace render
{

namespace vulkan
{

class Texture;
using TextureSharedPtr = std::shared_ptr<Texture>;
using TextureSharedPtrMap = std::map<Identifier, TextureSharedPtr>;

}	// namespace vulkan

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_VULKAN_DETAIL_FWD_TEXTURE_FWD_HPP
