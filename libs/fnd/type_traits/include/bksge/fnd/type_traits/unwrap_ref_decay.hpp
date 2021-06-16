/**
 *	@file	unwrap_ref_decay.hpp
 *
 *	@brief	unwrap_ref_decay の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TYPE_TRAITS_UNWRAP_REF_DECAY_HPP
#define BKSGE_FND_TYPE_TRAITS_UNWRAP_REF_DECAY_HPP

#include <type_traits>

#if 0//defined(__cpp_lib_unwrap_ref) && (__cpp_lib_unwrap_ref >= 201811)

namespace bksge
{

using std::unwrap_ref_decay;
using std::unwrap_ref_decay_t;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/unwrap_reference.hpp>
#include <bksge/fnd/type_traits/decay.hpp>

namespace bksge
{

template <typename T>
struct unwrap_ref_decay { using type = bksge::unwrap_reference_t<bksge::decay_t<T>>; };

template <typename T>
using unwrap_ref_decay_t = typename unwrap_ref_decay<T>::type;

}	// namespace bksge

#endif

#endif // BKSGE_FND_TYPE_TRAITS_UNWRAP_REF_DECAY_HPP
