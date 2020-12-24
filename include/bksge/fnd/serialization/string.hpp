/**
 *	@file	string.hpp
 *
 *	@brief	std::string のシリアライズ
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_STRING_HPP
#define BKSGE_FND_SERIALIZATION_STRING_HPP

#include <bksge/fnd/string/basic_string.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace serialization
{

template <typename Archive, typename CharT>
inline void
save(Archive& ar, bksge::basic_string<CharT> const& t)
{
	bksge::size_t const size = t.size();
	ar << size;
	for (bksge::size_t i = 0; i < size; ++i)
	{
		ar << t[i];
	}
}

template <typename Archive, typename CharT>
inline void
load(Archive& ar, bksge::basic_string<CharT>& t)
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

#endif // BKSGE_FND_SERIALIZATION_STRING_HPP
