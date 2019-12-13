/**
 *	@file	primitive.hpp
 *
 *	@brief	Primitive クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_PRIMITIVE_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_PRIMITIVE_HPP

#include <bksge/core/render/fwd/primitive_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

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

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/primitive_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_PRIMITIVE_HPP
