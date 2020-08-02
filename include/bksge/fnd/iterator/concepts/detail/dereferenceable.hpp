/**
 *	@file	dereferenceable.hpp
 *
 *	@brief	dereferenceable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_DEREFERENCEABLE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_DEREFERENCEABLE_HPP

#include <bksge/fnd/iterator/concepts/detail/can_reference.hpp>
#include <bksge/fnd/iterator/concepts/detail/is_void_pointer.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept dereferenceable =
	!bksge::detail::is_void_pointer<T>::value &&
	requires(T& t)
	{
		{ *t } -> can_reference;
	};

#else

template <typename T>
struct dereferenceable_impl
{
private:
	template <typename U, typename = bksge::enable_if_t<!bksge::detail::is_void_pointer<U>::value>>
	static auto test(int) -> detail::can_reference<decltype(*bksge::declval<U>())>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
struct dereferenceable
	: public detail::dereferenceable_impl<T>::type
{};

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_DEREFERENCEABLE_HPP
