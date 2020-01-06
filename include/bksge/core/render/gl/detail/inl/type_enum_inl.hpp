/**
 *	@file	type_enum_inl.hpp
 *
 *	@brief	TypeEnum クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_GL_DETAIL_INL_TYPE_ENUM_INL_HPP
#define BKSGE_CORE_RENDER_GL_DETAIL_INL_TYPE_ENUM_INL_HPP

#include <bksge/core/render/config.hpp>
#if BKSGE_CORE_RENDER_HAS_GL_RENDERER

#include <bksge/core/render/gl/detail/type_enum.hpp>
#include <bksge/core/render/detail/type_enum.hpp>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
ToGlTypeEnum(bksge::TypeEnum type_enum)
{
	switch (type_enum)
	{
	case bksge::TypeEnum::kSInt8:	return GL_BYTE;
	case bksge::TypeEnum::kUInt8:	return GL_UNSIGNED_BYTE;
	case bksge::TypeEnum::kSInt16:	return GL_SHORT;
	case bksge::TypeEnum::kUInt16:	return GL_UNSIGNED_SHORT;
	case bksge::TypeEnum::kSInt32:	return GL_INT;
	case bksge::TypeEnum::kUInt32:	return GL_UNSIGNED_INT;
	case bksge::TypeEnum::kFloat:	return GL_FLOAT;
	}
	return GL_BYTE;
}

}	// namespace detail

BKSGE_INLINE
TypeEnum::TypeEnum(bksge::TypeEnum type_enum)
	: m_type_enum(detail::ToGlTypeEnum(type_enum))
{}

BKSGE_INLINE
TypeEnum::operator ::GLenum() const
{
	return m_type_enum;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_CORE_RENDER_GL_DETAIL_INL_TYPE_ENUM_INL_HPP
