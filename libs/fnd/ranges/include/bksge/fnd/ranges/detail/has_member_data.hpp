/**
 *	@file	has_member_data.hpp
 *
 *	@brief	has_member_data の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_DATA_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_DATA_HPP

#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/is_pointer.hpp>
#include <bksge/fnd/type_traits/remove_pointer.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept pointer_to_object =
	bksge::is_pointer<T>::value &&
	bksge::is_object<bksge::remove_pointer_t<T>>::value;

template <typename T>
concept has_member_data =
	bksge::is_lvalue_reference<T>::value &&
	requires(T t) { { t.data() } -> pointer_to_object; };

#else

template <typename T>
struct has_member_data_impl
{
private:
	template <typename U, typename P = decltype(std::declval<U&>().data())>
	static auto test(int) -> bksge::conjunction<
		bksge::is_lvalue_reference<U>,
		bksge::is_pointer<P>,
		bksge::is_object<bksge::remove_pointer_t<P>>
	>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_member_data = typename has_member_data_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_MEMBER_DATA_HPP
