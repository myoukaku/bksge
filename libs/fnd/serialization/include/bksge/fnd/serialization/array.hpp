﻿/**
 *	@file	array.hpp
 *
 *	@brief	bksge::array のシリアライズ
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_ARRAY_HPP
#define BKSGE_FND_SERIALIZATION_ARRAY_HPP

#include <bksge/fnd/array/array.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace serialization
{

template <typename Archive, typename T, bksge::size_t N>
inline void
save(Archive& ar, bksge::array<T, N> const& t)
{
	for (bksge::size_t i = 0; i < N; ++i)
	{
		ar << t[i];
	}
}

template <typename Archive, typename T, bksge::size_t N>
inline void
load(Archive& ar, bksge::array<T, N>& t)
{
	for (bksge::size_t i = 0; i < N; ++i)
	{
		ar >> t[i];
	}
}

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_ARRAY_HPP
