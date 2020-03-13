/**
 *	@file	type_enum_inl.hpp
 *
 *	@brief	TypeEnum の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_INL_TYPE_ENUM_INL_HPP
#define BKSGE_CORE_RENDER_DETAIL_INL_TYPE_ENUM_INL_HPP

#include <bksge/core/render/detail/type_enum.hpp>
#include <cstddef>
#include <string>
#include <unordered_map>

namespace bksge
{

namespace render
{

#define BKSGE_FOREACH_TYPEENUM(F)	\
	F(TypeEnum::kSInt8),			\
	F(TypeEnum::kUInt8),			\
	F(TypeEnum::kSInt16),			\
	F(TypeEnum::kUInt16),			\
	F(TypeEnum::kSInt32),			\
	F(TypeEnum::kUInt32),			\
	F(TypeEnum::kFloat)

BKSGE_INLINE
std::size_t GetSizeOf(TypeEnum type_enum)
{
#define BKSGE_MAKE_TYPEENUM_PAIR(x)	{ x, sizeof(EnumToType<x>::type) }

	static std::unordered_map<TypeEnum, std::size_t> const m =
	{
		BKSGE_FOREACH_TYPEENUM(BKSGE_MAKE_TYPEENUM_PAIR)
	};

	return m.at(type_enum);

#undef BKSGE_MAKE_TYPEENUM_PAIR
}

BKSGE_INLINE
std::string to_string(TypeEnum const& type_enum)
{
#define BKSGE_MAKE_TYPEENUM_PAIR(x)	{ x, #x }

	static std::unordered_map<TypeEnum, std::string> const m =
	{
		BKSGE_FOREACH_TYPEENUM(BKSGE_MAKE_TYPEENUM_PAIR)
	};

	return m.at(type_enum);

#undef BKSGE_MAKE_TYPEENUM_PAIR
}

#undef BKSGE_FOREACH_TYPEENUM

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_INL_TYPE_ENUM_INL_HPP
