/**
 *	@file	texture_fwd.hpp
 *
 *	@brief	Texture クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_FWD_TEXTURE_FWD_HPP
#define BKSGE_RENDER_GL_DETAIL_FWD_TEXTURE_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

namespace gl
{

class Texture;
using TextureShared = std::shared_ptr<Texture>;
using TextureMap    = std::map<Identifier, TextureShared>;

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_DETAIL_FWD_TEXTURE_FWD_HPP
