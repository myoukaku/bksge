/**
 *	@file	gl_texture_fwd.hpp
 *
 *	@brief	GlTexture クラスの前方宣言
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_FWD_GL_TEXTURE_FWD_HPP
#define BKSGE_RENDER_GL_FWD_GL_TEXTURE_FWD_HPP

#include <bksge/render/detail/identifier.hpp>
#include <map>
#include <memory>

namespace bksge
{

namespace render
{

class GlTexture;
using GlTextureShared = std::shared_ptr<GlTexture>;
using GlTextureMap    = std::map<Identifier, GlTextureShared>;

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_GL_FWD_GL_TEXTURE_FWD_HPP
