/**
 *	@file	gl_type_enum_inl.hpp
 *
 *	@brief	ToGlTypeEnum の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_GL_INL_GL_TYPE_ENUM_INL_HPP
#define BKSGE_RENDER_GL_INL_GL_TYPE_ENUM_INL_HPP

#include <bksge/render/config.hpp>
#if BKSGE_RENDER_HAS_GL_RENDERER

#include <bksge/render/gl/gl_type_enum.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <unordered_map>

namespace bksge
{

namespace render
{

BKSGE_INLINE
GLenum ToGlTypeEnum(TypeEnum type)
{
	static std::unordered_map<TypeEnum, GLenum> const m =
	{
		{ TypeEnum::kSInt8,		GL_BYTE },
		{ TypeEnum::kUInt8,		GL_UNSIGNED_BYTE },
		{ TypeEnum::kSInt16,	GL_SHORT },
		{ TypeEnum::kUInt16,	GL_UNSIGNED_SHORT },
		{ TypeEnum::kSInt32,	GL_INT },
		{ TypeEnum::kUInt32,	GL_UNSIGNED_INT },
		{ TypeEnum::kFloat,		GL_FLOAT },
	};

	return m.at(type);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_HAS_GL_RENDERER

#endif // BKSGE_RENDER_GL_INL_GL_TYPE_ENUM_INL_HPP
