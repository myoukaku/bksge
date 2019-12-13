/**
 *	@file	type_enum.hpp
 *
 *	@brief	TypeEnum クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_TYPE_ENUM_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_TYPE_ENUM_HPP

#include <bksge/core/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/core/render/gl/detail/gl_h.hpp>

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
	explicit TypeEnum(bksge::TypeEnum type_enum);

	operator ::GLenum() const;

private:
	::GLenum	m_type_enum;
};

}	// namespace gl

}	// namespace render

}	// namespace bksge

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/gl/detail/inl/type_enum_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_GL_DETAIL_TYPE_ENUM_HPP
