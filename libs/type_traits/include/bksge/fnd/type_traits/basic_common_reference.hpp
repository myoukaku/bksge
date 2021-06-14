/**
 *	@file	basic_common_reference.hpp
 *
 *	@brief	basic_common_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP
#define BKSGE_FND_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP

#include <bksge/fnd/config.hpp>
#if (BKSGE_CXX_STANDARD >= 20) && BKSGE_HAS_INCLUDE(<concepts>)
#include <concepts>
#endif

#if defined(__cpp_lib_concepts) && (__cpp_lib_concepts >= 202002)

#include <type_traits>

namespace bksge
{

#define BKSGE_BASIC_COMMON_REFERENCE_NAMESPACE std

using std::basic_common_reference;

}	// namespace bksge

#else

namespace bksge
{

#define BKSGE_BASIC_COMMON_REFERENCE_NAMESPACE bksge

template <
	typename T,
	typename U,
	template <typename> class TQual,
	template <typename> class UQual
>
struct basic_common_reference
{};

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_BASIC_COMMON_REFERENCE_HPP
