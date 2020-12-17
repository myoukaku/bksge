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
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <string>

namespace bksge
{

namespace render
{

#define BKSGE_CORE_RENDER_TYPEENUM_FOREACH(F)	\
	F(TypeEnum::kSInt8);			\
	F(TypeEnum::kUInt8);			\
	F(TypeEnum::kSInt16);			\
	F(TypeEnum::kUInt16);			\
	F(TypeEnum::kSInt32);			\
	F(TypeEnum::kUInt32);			\
	F(TypeEnum::kFloat);

BKSGE_INLINE
std::size_t GetSizeOf(TypeEnum type_enum)
{
#define BKSGE_CORE_RENDER_TYPEENUM_CASE(x)	case x: return sizeof(EnumToType<x>::type)

	switch (type_enum)
	{
	BKSGE_CORE_RENDER_TYPEENUM_FOREACH(BKSGE_CORE_RENDER_TYPEENUM_CASE)
	}

	return 0;

#undef BKSGE_CORE_RENDER_TYPEENUM_CASE
}

BKSGE_INLINE
std::string to_string(TypeEnum const& type_enum)
{
#define BKSGE_CORE_RENDER_TYPEENUM_CASE(x)	case x: return #x

	switch (type_enum)
	{
	BKSGE_CORE_RENDER_TYPEENUM_FOREACH(BKSGE_CORE_RENDER_TYPEENUM_CASE)
	};

	return "";

#undef BKSGE_CORE_RENDER_TYPEENUM_CASE
}

#undef BKSGE_CORE_RENDER_TYPEENUM_FOREACH

}	// namespace render

}	// namespace bksge

#endif // BKSGE_CORE_RENDER_DETAIL_INL_TYPE_ENUM_INL_HPP
