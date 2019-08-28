/**
 *	@file	type_enum_inl.hpp
 *
 *	@brief	TypeEnum クラスの実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_DETAIL_INL_TYPE_ENUM_INL_HPP
#define BKSGE_RENDER_GL_DETAIL_INL_TYPE_ENUM_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/detail/type_enum.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

namespace gl
{

namespace detail
{

inline ::GLenum
GlTypeEnum(bksge::TypeEnum type)
{
	static std::unordered_map<bksge::TypeEnum, ::GLenum> const m =
	{
		{ bksge::TypeEnum::kSInt8,	GL_BYTE },
		{ bksge::TypeEnum::kUInt8,	GL_UNSIGNED_BYTE },
		{ bksge::TypeEnum::kSInt16,	GL_SHORT },
		{ bksge::TypeEnum::kUInt16,	GL_UNSIGNED_SHORT },
		{ bksge::TypeEnum::kSInt32,	GL_INT },
		{ bksge::TypeEnum::kUInt32,	GL_UNSIGNED_INT },
		{ bksge::TypeEnum::kFloat,	GL_FLOAT },
	};

	return m.at(type);
}

}	// namespace detail

BKSGE_INLINE
TypeEnum::TypeEnum(bksge::TypeEnum type_enum)
	: m_type_enum(detail::GlTypeEnum(type_enum))
{}

BKSGE_INLINE
TypeEnum::operator ::GLenum() const
{
	return m_type_enum;
}

}	// namespace gl

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_DETAIL_INL_TYPE_ENUM_INL_HPP
