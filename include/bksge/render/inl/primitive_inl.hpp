/**
 *	@file	primitive_inl.hpp
 *
 *	@brief	Primitive の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_INL_PRIMITIVE_INL_HPP
#define BKSGE_RENDER_INL_PRIMITIVE_INL_HPP

#include <bksge/render/primitive.hpp>
#include <unordered_map>
#include <string>

namespace bksge
{

namespace render
{

BKSGE_INLINE
std::string to_string(Primitive const& primitive)
{
#define BKSGE_RENDER_MAKE_PRIMITIVE_KVP(x)	{ x, #x }

	static std::unordered_map<Primitive, std::string> const m =
	{
		BKSGE_RENDER_MAKE_PRIMITIVE_KVP(Primitive::kPoints),
		BKSGE_RENDER_MAKE_PRIMITIVE_KVP(Primitive::kLines),
		BKSGE_RENDER_MAKE_PRIMITIVE_KVP(Primitive::kTriangles),
	};

	return m.at(primitive);

#undef BKSGE_RENDER_MAKE_PRIMITIVE_KVP
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_INL_PRIMITIVE_INL_HPP
