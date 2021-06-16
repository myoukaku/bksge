/**
 *	@file	vector.hpp
 *
 *	@brief	bksge::vector のシリアライズ
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_VECTOR_HPP
#define BKSGE_FND_SERIALIZATION_VECTOR_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/vector.hpp>

namespace bksge
{

namespace serialization
{

template <typename Archive, typename T>
inline void
save(Archive& ar, bksge::vector<T> const& t)
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
load(Archive& ar, bksge::vector<T>& t)
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
