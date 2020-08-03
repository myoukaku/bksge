/**
 *	@file	can_reference.hpp
 *
 *	@brief	can_reference の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CAN_REFERENCE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CAN_REFERENCE_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

template <typename T>
using with_ref = T&;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept can_reference = requires { typename with_ref<T>; };

#else

template <typename T>
struct can_reference_impl
{
private:
	template <typename U, typename = with_ref<U>>
	static auto test(int) -> bksge::true_type;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using can_reference =
	typename detail::can_reference_impl<T>::type;

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_CAN_REFERENCE_HPP
