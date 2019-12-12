/**
 *	@file	primitive.hpp
 *
 *	@brief	Primitive クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_PRIMITIVE_HPP
#define BKSGE_RENDER_GL_DETAIL_PRIMITIVE_HPP

#include <bksge/render/fwd/primitive_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	Primitive を OpenGL の enum に変換
 */
class Primitive
{
public:
	explicit Primitive(bksge::Primitive primitive);

	operator ::GLenum() const;

private:
	::GLenum	m_primitive;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/primitive_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_PRIMITIVE_HPP
