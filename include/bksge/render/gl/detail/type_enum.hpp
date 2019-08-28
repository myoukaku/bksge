/**
 *	@file	type_enum.hpp
 *
 *	@brief	TypeEnum クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_TYPE_ENUM_HPP
#define BKSGE_RENDER_GL_DETAIL_TYPE_ENUM_HPP

#include <bksge/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/render/gl/detail/gl_h.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

/**
 *	@brief	TypeEnum を OpenGL の enum に変換
 */
class TypeEnum
{
public:
	TypeEnum(bksge::TypeEnum type_enum);

	operator ::GLenum() const;

private:
	::GLenum	m_type_enum;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/gl/detail/inl/type_enum_inl.hpp>
#endif

#endif // BKSGE_RENDER_GL_DETAIL_TYPE_ENUM_HPP
