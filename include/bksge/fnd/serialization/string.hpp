/**
 *	@file	string.hpp
 *
 *	@brief	std::string のシリアライズ
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SERIALIZATION_STRING_HPP
#define BKSGE_FND_SERIALIZATION_STRING_HPP

#include <string>
#include <cstddef>

namespace bksge
{

namespace serialization
{

template <typename Archive, typename CharT>
inline void
save(Archive& ar, std::basic_string<CharT> const& t)
{
	std::size_t const size = t.size();
	ar << size;
	for (std::size_t i = 0; i < size; ++i)
	{
		ar << t[i];
	}
}

template <typename Archive, typename CharT>
inline void
load(Archive& ar, std::basic_string<CharT>& t)
{
	std::size_t size;
	ar >> size;
	t.resize(size);
	for (std::size_t i = 0; i < size; ++i)
	{
		ar >> t[i];
	}
}

}	// namespace serialization

}	// namespace bksge

#endif // BKSGE_FND_SERIALIZATION_STRING_HPP
