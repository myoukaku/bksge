/**
 *	@file	iter_move.hpp
 *
 *	@brief	iter_move の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_ITER_MOVE_HPP
#define BKSGE_FND_ITERATOR_ITER_MOVE_HPP

#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_class.hpp>
#include <bksge/fnd/type_traits/is_enum.hpp>
#include <bksge/fnd/type_traits/is_lvalue_reference.hpp>
#include <bksge/fnd/type_traits/is_rvalue_reference.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace iter_move_detail
{

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

void iter_move();

struct iter_move_fn
{
	template <typename T>
	struct is_class_or_enum
		: public bksge::disjunction<bksge::is_class<T>, bksge::is_enum<T>>
	{};

	// (1) if std::remove_cvref_t<T> is a class or enumeration type and
	//        iter_move(std::forward<T>(t)) is well-formed in unevaluated context
	template <typename T>
	BKSGE_CONSTEXPR auto
	operator()(T&& t, bksge::enable_if_t<is_class_or_enum<bksge::remove_cvref_t<T>>::value>* = nullptr) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			iter_move(bksge::forward<T>(t)))

	// (2) otherwise, if *std::forward<T>(t) is well-formed and is an lvalue
	template <typename T>
	BKSGE_CONSTEXPR auto
	operator()(T&& t, bksge::enable_if_t<bksge::is_lvalue_reference<decltype(*bksge::forward<T>(t))>::value>* = nullptr) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			bksge::move(*bksge::forward<T>(t)))

	// (3) otherwise, if *std::forward<T>(t) is well-formed and is an rvalue
	template <typename T>
	BKSGE_CONSTEXPR auto
	operator()(T&& t, bksge::enable_if_t<bksge::is_rvalue_reference<decltype(*bksge::forward<T>(t))>::value>* = nullptr) const
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			*bksge::forward<T>(t))
};

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

}	// namespace iter_move_detail

// Customization point object
BKSGE_INLINE_VAR BKSGE_CONSTEXPR
auto iter_move = iter_move_detail::iter_move_fn{};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_ITER_MOVE_HPP
