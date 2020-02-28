﻿/**
 *	@file	vector.hpp
 *
 *	@brief	std::vector のシリアライズ
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_VECTOR_HPP
#define BKSGE_FND_SERIALIZATION_VECTOR_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <vector>

namespace bksge
{

namespace serialization
{

template <typename Archive, typename T>
inline void
save(Archive& ar, std::vector<T> const& t)
{
	bksge::size_t const size = t.size();
	ar << size;
	for (bksge::size_t i = 0; i < size; ++i)
	{
		ar << t[i];
	}
}

template <typename Archive, typename T>
inline void
load(Archive& ar, std::vector<T>& t)
{
	bksge::size_t size;
	ar >> size;
	t.resize(size);
	for (bksge::size_t i = 0; i < size; ++i)
	{
		ar >> t[i];
	}
}

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_VECTOR_HPP
