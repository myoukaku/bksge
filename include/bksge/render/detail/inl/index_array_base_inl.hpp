/**
 *	@file	index_array_base_inl.hpp
 *
 *	@brief	IndexArrayBase の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_INL_INDEX_ARRAY_BASE_INL_HPP
#define BKSGE_RENDER_DETAIL_INL_INDEX_ARRAY_BASE_INL_HPP

#include <bksge/render/detail/index_array_base.hpp>
#include <bksge/render/detail/type_enum.hpp>
#include <cstddef>
#include <cstring>	// memcmp

namespace bksge
{

namespace render
{

BKSGE_INLINE
IndexArrayBase::~IndexArrayBase(void)
{}

BKSGE_INLINE bool
operator==(IndexArrayBase const& lhs, IndexArrayBase const& rhs)
{
	return
		lhs.type()	== rhs.type()	&&
		lhs.bytes()	== rhs.bytes()	&&
		lhs.count()	== rhs.count()	&&
		(std::memcmp(lhs.data(), rhs.data(), lhs.bytes()) == 0);
}

BKSGE_INLINE bool
operator!=(IndexArrayBase const& lhs, IndexArrayBase const& rhs)
{
	return !(lhs == rhs);
}

}	// namespace render

}	// namespace bksge

#endif // BKSGE_RENDER_DETAIL_INL_INDEX_ARRAY_BASE_INL_HPP
