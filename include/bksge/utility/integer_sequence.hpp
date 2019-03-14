/**
 *	@file	integer_sequence.hpp
 *
 *	@brief	integer_sequence を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_UTILITY_INTEGER_SEQUENCE_HPP
#define BKSGE_UTILITY_INTEGER_SEQUENCE_HPP

#include <utility>

#if defined(__cpp_lib_integer_sequence) && (__cpp_lib_integer_sequence >= 201304)

namespace bksge
{

using std::integer_sequence;

}	// namespace bksge

#else

#include <bksge/config.hpp>
#include <cstddef>

namespace bksge
{

template <typename T, T... I>
struct integer_sequence
{
	using value_type = T;
	BKSGE_STATIC_CONSTEXPR std::size_t size() BKSGE_NOEXCEPT { return sizeof...(I); }
};

}	// namespace bksge

#endif

#endif // BKSGE_UTILITY_INTEGER_SEQUENCE_HPP
