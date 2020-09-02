/**
 *	@file	iter_move.hpp
 *
 *	@brief	iter_move の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_RANGES_ITER_MOVE_HPP
#define BKSGE_FND_ITERATOR_RANGES_ITER_MOVE_HPP

#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/concepts/detail/dereferenceable.hpp>
#include <bksge/fnd/iterator/concepts/detail/is_void_pointer.hpp>
#include <bksge/fnd/concepts/detail/class_or_enum.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
//#include <bksge/fnd/type_traits/is_rvalue_reference.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace bksge
{

namespace ranges
{

namespace iter_move_detail
{

void iter_move();

struct iter_move_fn
{
private:
	// (1) if std::remove_cvref_t<T> is a class or enumeration type and
	//        iter_move(std::forward<T>(t)) is well-formed in unevaluated context
	template <typename T
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<bksge::detail::class_or_enum<bksge::remove_reference_t<T>>::value>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires bksge::detail::class_or_enum<bksge::remove_reference_t<T>>
#endif
	static BKSGE_CONSTEXPR auto impl(bksge::detail::overload_priority<2>, T&& t)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(iter_move(bksge::forward<T>(t)))

	// (2) otherwise, if *std::forward<T>(t) is well-formed and is an lvalue
	template <typename T
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
		, typename = bksge::enable_if_t<bksge::is_lvalue_reference<bksge::iter_reference_t<T>>::value>
#endif
	>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	requires bksge::is_lvalue_reference<bksge::iter_reference_t<T>>::value
#endif
	static BKSGE_CONSTEXPR auto impl(bksge::detail::overload_priority<1>, T&& t)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(bksge::move(*bksge::forward<T>(t)))

	// (3) otherwise, if *std::forward<T>(t) is well-formed and is an rvalue
	template <typename T
		, typename = bksge::enable_if_t<!bksge::detail::is_void_pointer<T>::value>
	>
//	requires bksge::is_rvalue_reference<bksge::iter_reference_t<T>>::value
	static BKSGE_CONSTEXPR auto impl(bksge::detail::overload_priority<0>, T&& t)
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(*bksge::forward<T>(t))

public:
	template <typename T>
	BKSGE_CONSTEXPR auto operator()(T&& t) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			impl(bksge::detail::overload_priority<2>{}, bksge::forward<T>(t)))
};

}	// namespace iter_move_detail

inline namespace cpo
{

// Customization point object
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
iter_move_detail::iter_move_fn iter_move{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif // BKSGE_FND_ITERATOR_RANGES_ITER_MOVE_HPP
