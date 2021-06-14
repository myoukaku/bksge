/**
 *	@file	tuple.hpp
 *
 *	@brief	tuple クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_TUPLE_HPP
#define BKSGE_FND_TUPLE_TUPLE_HPP

#include <bksge/fnd/tuple/config.hpp>

#if defined(BKSGE_USE_STD_TUPLE)

namespace bksge
{

using std::tuple;

}	// namespace bksge

#else

#include <bksge/fnd/tuple/fwd/tuple_fwd.hpp>
#include <bksge/fnd/tuple/detail/tuple_cmp.hpp>
#include <bksge/fnd/tuple/detail/tuple_impl.hpp>
#include <bksge/fnd/compare/common_comparison_category.hpp>
#include <bksge/fnd/compare/detail/synth3way.hpp>
#include <bksge/fnd/memory/allocator_arg.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/index_sequence_for.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/pair.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/array.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

template <typename... Types>
class tuple : public tuple_detail::tuple_impl_t<Types...>
{
private:
	using Inherited = tuple_detail::tuple_impl_t<Types...>;

	template <typename>
	struct AlwaysTrue : public bksge::true_type{};

	template <typename>
	struct IsDefaultConstructible
		: public bksge::conjunction<bksge::is_default_constructible<Types>...>{};

	struct IsImplicitlyDefaultConstructible
		: public bksge::conjunction<bksge::is_implicitly_default_constructible<Types>...>{};

	struct IsNothrowDefaultConstructible
		: public bksge::conjunction<bksge::is_nothrow_default_constructible<Types>...>{};

	template <bool, typename... UTypes>
	struct IsConstructibleImpl
		: public bksge::conjunction<bksge::is_constructible<Types, UTypes>...>{};

	template <typename... UTypes>
	struct IsConstructibleImpl<false, UTypes...>
		: public bksge::false_type{};

	template <typename... UTypes>
	struct IsConstructible
		: public IsConstructibleImpl<sizeof...(Types) == sizeof...(UTypes), UTypes...>{};

	template <typename... UTypes>
	struct IsImplicitlyConstructible
		: public bksge::conjunction<bksge::is_convertible<UTypes, Types>...>{};

	template <typename... UTypes>
	struct IsNothrowConstructible
		: public bksge::conjunction<bksge::is_nothrow_constructible<Types, UTypes>...>{};

	template <typename... UTypes>
	struct IsConvertCopyConstructible
		: public bksge::disjunction<
			bksge::bool_constant<sizeof...(Types) != 1>,
			bksge::conjunction<
				bksge::negation<bksge::is_convertible<tuple<UTypes> const&, Types>>...,
				bksge::negation<bksge::is_constructible<Types, tuple<UTypes> const&>>...,
				bksge::negation<bksge::is_same<Types, UTypes>>...
			>
		>{};

	template <typename... UTypes>
	struct IsConvertMoveConstructible
		: public bksge::disjunction<
			bksge::bool_constant<sizeof...(Types) != 1>,
			bksge::conjunction<
				bksge::negation<bksge::is_convertible<tuple<UTypes>, Types>>...,
				bksge::negation<bksge::is_constructible<Types, tuple<UTypes>>>...,
				bksge::negation<bksge::is_same<Types, UTypes>>...
			>
		>{};

	template <bool, typename... UTypes>
	struct IsAssignableImpl
		: public bksge::conjunction<bksge::is_assignable<Types&, UTypes>...>{};

	template <typename... UTypes>
	struct IsAssignableImpl<false, UTypes...>
		: public bksge::false_type{};

	template <typename... UTypes>
	struct IsAssignable
		: public IsAssignableImpl<sizeof...(Types) == sizeof...(UTypes), UTypes...>{};

	template <typename... UTypes>
	struct IsNothrowAssignable
		: public bksge::conjunction<bksge::is_nothrow_assignable<Types&, UTypes>...>{};

public:
#if defined(BKSGE_HAS_CXX20_CONDITIONAL_EXPLICIT)

	// (1) Default constructor
	template <typename Dummy = void,
		bksge::enable_if_t<IsDefaultConstructible<Dummy>::value>* = nullptr>
	explicit(!IsImplicitlyDefaultConstructible::value) BKSGE_CONSTEXPR
	tuple() BKSGE_NOEXCEPT_IF((IsNothrowDefaultConstructible::value))
		: Inherited() {}

	// (2) Direct constructor
	template <typename Dummy = void,
		bksge::enable_if_t<bksge::conjunction<AlwaysTrue<Dummy>,
			IsConstructible<Types const&...>
		>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<Types const&...>::value) BKSGE_CONSTEXPR
	tuple(Types const&... args)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<Types const&...>::value))
		: Inherited(args...) {}

	// (3) Converting constructor
	template <typename... UTypes,
		bksge::enable_if_t<IsConstructible<UTypes&&...>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<UTypes&&...>::value) BKSGE_CONSTEXPR
	tuple(UTypes&&... args)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<UTypes&&...>::value))
		: Inherited(bksge::forward<UTypes>(args)...) {}

	// (4) Converting copy-constructor
	template <typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes const&...>,
			IsConvertCopyConstructible<UTypes...>
		>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<UTypes const&...>::value) BKSGE_CONSTEXPR
	tuple(tuple<UTypes...> const& other)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<UTypes const&...>::value))
		: Inherited(static_cast<tuple_detail::tuple_impl_t<UTypes...> const&>(other)) {}

	// (5) Converting move-constructor
	template <typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes&&...>,
			IsConvertMoveConstructible<UTypes...>
		>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<UTypes&&...>::value) BKSGE_CONSTEXPR
	tuple(tuple<UTypes...>&& other)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<UTypes&&...>::value))
		: Inherited(static_cast<tuple_detail::tuple_impl_t<UTypes...>&&>(other)) {}

	// (6) Pair copy constructor
	template <typename U1, typename U2,
		bksge::enable_if_t<IsConstructible<U1 const&, U2 const&>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<U1 const&, U2 const&>::value) BKSGE_CONSTEXPR
	tuple(bksge::pair<U1, U2> const& in)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<U1 const&, U2 const&>::value))
		: Inherited(in.first, in.second) {}

	// (7) Pair move constructor
	template <typename U1, typename U2,
		bksge::enable_if_t<IsConstructible<U1&&, U2&&>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<U1&&, U2&&>::value) BKSGE_CONSTEXPR
	tuple(bksge::pair<U1, U2>&& in)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<U1&&, U2&&>::value))
		: Inherited(bksge::forward<U1>(in.first), bksge::forward<U2>(in.second)) {}

	// Allocator-extended constructors.

	// (10) Default constructor
	template <typename Alloc,
		bksge::enable_if_t<IsDefaultConstructible<Alloc>::value>* = nullptr>
	explicit(!IsImplicitlyDefaultConstructible::value) BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a)
		: Inherited(tag, a) {}

	// (11) Direct constructor
	template <typename Alloc,
		bksge::enable_if_t<bksge::conjunction<AlwaysTrue<Alloc>,
			IsConstructible<Types const&...>
		>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<Types const&...>::value) BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, Types const&... args)
		: Inherited(tag, a, args...) {}

	// (12) Converting constructor
	template <typename Alloc, typename... UTypes,
		bksge::enable_if_t<IsConstructible<UTypes&&...>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<UTypes&&...>::value) BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, UTypes&&... args)
		: Inherited(tag, a, bksge::forward<UTypes>(args)...) {}

	// (13) Converting copy-constructor
	template <typename Alloc, typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes const&...>,
			IsConvertCopyConstructible<UTypes...>
		>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<UTypes const&...>::value) BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, tuple<UTypes...> const& other)
		: Inherited(tag, a, static_cast<tuple_detail::tuple_impl_t<UTypes...> const&>(other)) {}

	// (14) Converting move-constructor
	template <typename Alloc, typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes&&...>,
			IsConvertMoveConstructible<UTypes...>
		>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<UTypes&&...>::value) BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, tuple<UTypes...>&& other)
		: Inherited(tag, a, static_cast<tuple_detail::tuple_impl_t<UTypes...>&&>(other)) {}

	// (15) Pair copy constructor
	template <typename Alloc, typename U1, typename U2,
		bksge::enable_if_t<IsConstructible<U1 const&, U2 const&>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<U1 const&, U2 const&>::value) BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, bksge::pair<U1, U2> const& in)
		: Inherited(tag, a, in.first, in.second) {}

	// (16) Pair move constructor
	template <typename Alloc, typename U1, typename U2,
		bksge::enable_if_t<IsConstructible<U1&&, U2&&>::value>* = nullptr>
	explicit(!IsImplicitlyConstructible<U1&&, U2&&>::value) BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, bksge::pair<U1, U2>&& in)
		: Inherited(tag, a, bksge::forward<U1>(in.first), bksge::forward<U2>(in.second)) {}

#else

	// (1) Default constructor
	template <typename Dummy = void,
		bksge::enable_if_t<bksge::conjunction<
			IsDefaultConstructible<Dummy>,
			IsImplicitlyDefaultConstructible
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple() BKSGE_NOEXCEPT_IF((IsNothrowDefaultConstructible::value))
		: Inherited() {}

	template <typename Dummy = void,
		bksge::enable_if_t<bksge::conjunction<
			IsDefaultConstructible<Dummy>,
			bksge::negation<IsImplicitlyDefaultConstructible>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple() BKSGE_NOEXCEPT_IF((IsNothrowDefaultConstructible::value))
		: Inherited() {}

	// (2) Direct constructor
	template <typename Dummy = void,
		bksge::enable_if_t<bksge::conjunction<AlwaysTrue<Dummy>,
			IsConstructible<Types const&...>,
			IsImplicitlyConstructible<Types const&...>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(Types const&... args)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<Types const&...>::value))
		: Inherited(args...) {}

	template <typename Dummy = void,
		bksge::enable_if_t<bksge::conjunction<AlwaysTrue<Dummy>,
			IsConstructible<Types const&...>,
			bksge::negation<IsImplicitlyConstructible<Types const&...>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(Types const&... args)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<Types const&...>::value))
		: Inherited(args...) {}

	// (3) Converting constructor
	template <typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes&&...>,
			IsImplicitlyConstructible<UTypes&&...>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(UTypes&&... args)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<UTypes&&...>::value))
		: Inherited(bksge::forward<UTypes>(args)...) {}

	template <typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes&&...>,
			bksge::negation<IsImplicitlyConstructible<UTypes&&...>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(UTypes&&... args)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<UTypes&&...>::value))
		: Inherited(bksge::forward<UTypes>(args)...) {}

	// (4) Converting copy-constructor
	template <typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes const&...>,
			IsConvertCopyConstructible<UTypes...>,
			IsImplicitlyConstructible<UTypes const&...>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(tuple<UTypes...> const& other)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<UTypes const&...>::value))
		: Inherited(static_cast<tuple_detail::tuple_impl_t<UTypes...> const&>(other)) {}

	template <typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes const&...>,
			IsConvertCopyConstructible<UTypes...>,
			bksge::negation<IsImplicitlyConstructible<UTypes const&...>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(tuple<UTypes...> const& other)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<UTypes const&...>::value))
		: Inherited(static_cast<tuple_detail::tuple_impl_t<UTypes...> const&>(other)) {}

	// (5) Converting move-constructor
	template <typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes&&...>,
			IsConvertMoveConstructible<UTypes...>,
			IsImplicitlyConstructible<UTypes&&...>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(tuple<UTypes...>&& other)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<UTypes&&...>::value))
		: Inherited(static_cast<tuple_detail::tuple_impl_t<UTypes...>&&>(other)) {}

	template <typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes&&...>,
			IsConvertMoveConstructible<UTypes...>,
			bksge::negation<IsImplicitlyConstructible<UTypes&&...>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(tuple<UTypes...>&& other)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<UTypes&&...>::value))
		: Inherited(static_cast<tuple_detail::tuple_impl_t<UTypes...>&&>(other)) {}

	// (6) Pair copy constructor
	template <typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<U1 const&, U2 const&>,
			IsImplicitlyConstructible<U1 const&, U2 const&>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(bksge::pair<U1, U2> const& in)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<U1 const&, U2 const&>::value))
		: Inherited(in.first, in.second) {}

	template <typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<U1 const&, U2 const&>,
			bksge::negation<IsImplicitlyConstructible<U1 const&, U2 const&>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(bksge::pair<U1, U2> const& in)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<U1 const&, U2 const&>::value))
		: Inherited(in.first, in.second) {}

	// (7) Pair move constructor
	template <typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<U1&&, U2&&>,
			IsImplicitlyConstructible<U1&&, U2&&>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(bksge::pair<U1, U2>&& in)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<U1&&, U2&&>::value))
		: Inherited(bksge::forward<U1>(in.first), bksge::forward<U2>(in.second)) {}

	template <typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<U1&&, U2&&>,
			bksge::negation<IsImplicitlyConstructible<U1&&, U2&&>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(bksge::pair<U1, U2>&& in)
		BKSGE_NOEXCEPT_IF((IsNothrowConstructible<U1&&, U2&&>::value))
		: Inherited(bksge::forward<U1>(in.first), bksge::forward<U2>(in.second)) {}

	// Allocator-extended constructors.

	// (10) Default constructor
	template <typename Alloc,
		bksge::enable_if_t<bksge::conjunction<
			IsDefaultConstructible<Alloc>,
			IsImplicitlyDefaultConstructible
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a)
		: Inherited(tag, a) {}

	template <typename Alloc,
		bksge::enable_if_t<bksge::conjunction<
			IsDefaultConstructible<Alloc>,
			bksge::negation<IsImplicitlyDefaultConstructible>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a)
		: Inherited(tag, a) {}

	// (11) Direct constructor
	template <typename Alloc,
		bksge::enable_if_t<bksge::conjunction<AlwaysTrue<Alloc>,
			IsConstructible<Types const&...>,
			IsImplicitlyConstructible<Types const&...>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, Types const&... args)
		: Inherited(tag, a, args...) {}

	template <typename Alloc,
		bksge::enable_if_t<bksge::conjunction<AlwaysTrue<Alloc>,
			IsConstructible<Types const&...>,
			bksge::negation<IsImplicitlyConstructible<Types const&...>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, Types const&... args)
		: Inherited(tag, a, args...) {}

	// (12) Converting constructor
	template <typename Alloc, typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes&&...>,
			IsImplicitlyConstructible<UTypes&&...>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, UTypes&&... args)
		: Inherited(tag, a, bksge::forward<UTypes>(args)...) {}

	template <typename Alloc, typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes&&...>,
			bksge::negation<IsImplicitlyConstructible<UTypes&&...>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, UTypes&&... args)
		: Inherited(tag, a, bksge::forward<UTypes>(args)...) {}

	// (13) Converting copy-constructor
	template <typename Alloc, typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes const&...>,
			IsConvertCopyConstructible<UTypes...>,
			IsImplicitlyConstructible<UTypes const&...>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, tuple<UTypes...> const& other)
		: Inherited(tag, a, static_cast<tuple_detail::tuple_impl_t<UTypes...> const&>(other)) {}

	template <typename Alloc, typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes const&...>,
			IsConvertCopyConstructible<UTypes...>,
			bksge::negation<IsImplicitlyConstructible<UTypes const&...>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, tuple<UTypes...> const& other)
		: Inherited(tag, a, static_cast<tuple_detail::tuple_impl_t<UTypes...> const&>(other)) {}

	// (14) Converting move-constructor
	template <typename Alloc, typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes&&...>,
			IsConvertMoveConstructible<UTypes...>,
			IsImplicitlyConstructible<UTypes&&...>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, tuple<UTypes...>&& other)
		: Inherited(tag, a, static_cast<tuple_detail::tuple_impl_t<UTypes...>&&>(other)) {}

	template <typename Alloc, typename... UTypes,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<UTypes&&...>,
			IsConvertMoveConstructible<UTypes...>,
			bksge::negation<IsImplicitlyConstructible<UTypes&&...>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, tuple<UTypes...>&& other)
		: Inherited(tag, a, static_cast<tuple_detail::tuple_impl_t<UTypes...>&&>(other)) {}

	// (15) Pair copy constructor
	template <typename Alloc, typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<U1 const&, U2 const&>,
			IsImplicitlyConstructible<U1 const&, U2 const&>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, bksge::pair<U1, U2> const& in)
		: Inherited(tag, a, in.first, in.second) {}

	template <typename Alloc, typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<U1 const&, U2 const&>,
			bksge::negation<IsImplicitlyConstructible<U1 const&, U2 const&>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, bksge::pair<U1, U2> const& in)
		: Inherited(tag, a, in.first, in.second) {}

	// (16) Pair move constructor
	template <typename Alloc, typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<U1&&, U2&&>,
			IsImplicitlyConstructible<U1&&, U2&&>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, bksge::pair<U1, U2>&& in)
		: Inherited(tag, a, bksge::forward<U1>(in.first), bksge::forward<U2>(in.second)) {}

	template <typename Alloc, typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			IsConstructible<U1&&, U2&&>,
			bksge::negation<IsImplicitlyConstructible<U1&&, U2&&>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, bksge::pair<U1, U2>&& in)
		: Inherited(tag, a, bksge::forward<U1>(in.first), bksge::forward<U2>(in.second)) {}

#endif

	// (8) Implicitly-defined copy constructor
	// TODO
	// is_copy_constructible<Ti>::value must be true for all i,
	// otherwise the program is ill-formed (since C++20).
	BKSGE_CONSTEXPR tuple(tuple const&) = default;

	// (9) Implicitly-defined move constructor
	// TODO
	// is_move_constructible<Ti>::value must be true for all i,
	// otherwise this overload does not participate in overload resolution (since C++20).
	BKSGE_CONSTEXPR tuple(tuple&&) = default;

	// (17) Copy constructor
	template <typename Alloc>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, tuple const& other)
		: Inherited(tag, a, static_cast<Inherited const&>(other))
	{
		// is_copy_constructible<Ti>::value must be true for all i,
		// otherwise the program is ill-formed (since C++20).
		static_assert(bksge::conjunction<
			bksge::is_copy_constructible<Types>...>::value, "");
	}

	// (18) Move constructor
	// is_move_constructible<Ti>::value must be true for all i,
	// otherwise this overload does not participate in overload resolution (since C++20).
	template <typename Alloc,
		bksge::enable_if_t<bksge::conjunction<AlwaysTrue<Alloc>,
			bksge::is_move_constructible<Types>...
		>::value>* = nullptr>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t tag, Alloc const& a, tuple&& other)
		: Inherited(tag, a, static_cast<Inherited&&>(other)) {}

private:
	struct nonesuch
	{
		nonesuch() = delete;
		~nonesuch() = delete;
		nonesuch(nonesuch const&) = delete;
		void operator=(nonesuch const&) = delete;
	};

public:
	// tuple assignment

	BKSGE_CXX14_CONSTEXPR tuple&
	operator=(bksge::conditional_t<
		IsAssignable<Types const&...>::value,
		tuple const&,
		nonesuch const&> in)
		BKSGE_NOEXCEPT_IF((IsNothrowAssignable<Types const&...>::value))
	{
		this->assign(in);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR tuple&
	operator=(bksge::conditional_t<
		IsAssignable<Types...>::value,
		tuple&&,
		nonesuch&&> in)
		BKSGE_NOEXCEPT_IF((IsNothrowAssignable<Types...>::value))
	{
		this->assign(bksge::move(in));
		return *this;
	}

	template <typename... UTypes>
	BKSGE_CXX14_CONSTEXPR
	bksge::enable_if_t<IsAssignable<UTypes const&...>::value, tuple&>
	operator=(tuple<UTypes...> const& in)
		BKSGE_NOEXCEPT_IF((IsNothrowAssignable<UTypes const&...>::value))
	{
		this->assign(in);
		return *this;
	}

	template <typename... UTypes>
	BKSGE_CXX14_CONSTEXPR
	bksge::enable_if_t<IsAssignable<UTypes...>::value, tuple&>
	operator=(tuple<UTypes...>&& in)
		BKSGE_NOEXCEPT_IF((IsNothrowAssignable<UTypes...>::value))
	{
		this->assign(bksge::move(in));
		return *this;
	}

	template <typename U1, typename U2>
	BKSGE_CXX14_CONSTEXPR
	bksge::enable_if_t<IsAssignable<U1 const&, U2 const&>::value, tuple&>
	operator=(bksge::pair<U1, U2> const& in)
		BKSGE_NOEXCEPT_IF((IsNothrowAssignable<U1 const&, U2 const&>::value))
	{
		this->head(*this) = in.first;
		this->tail(*this).head(*this) = in.second;
		return *this;
	}

	template <typename U1, typename U2>
	BKSGE_CXX14_CONSTEXPR
	bksge::enable_if_t<IsAssignable<U1, U2>::value, tuple&>
	operator=(bksge::pair<U1, U2>&& in)
		BKSGE_NOEXCEPT_IF((IsNothrowAssignable<U1, U2>::value))
	{
		this->head(*this) = bksge::forward<U1>(in.first);
		this->tail(*this).head(*this) = bksge::forward<U2>(in.second);
		return *this;
	}

	// tuple swap
	BKSGE_CXX14_CONSTEXPR
	void swap(tuple& in)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_swappable<Types>...>::value))
	{
		Inherited::swap(in);
	}
};

template <>
class tuple<>
{
public:
	// We need the default since we're going to define no-op
	// allocator constructors.
	BKSGE_CONSTEXPR tuple() = default;

	// No-op allocator constructors.
	template <typename Alloc>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t, Alloc const&) BKSGE_NOEXCEPT {}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	tuple(bksge::allocator_arg_t, Alloc const&, tuple const&) BKSGE_NOEXCEPT {}

	BKSGE_CXX14_CONSTEXPR
	void swap(tuple&) BKSGE_NOEXCEPT {}
};


#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename... UTypes>
tuple(UTypes...) -> tuple<UTypes...>;

template <typename T1, typename T2>
tuple(bksge::pair<T1, T2>) -> tuple<T1, T2>;

template <typename Alloc, typename... UTypes>
tuple(bksge::allocator_arg_t, Alloc, UTypes...) -> tuple<UTypes...>;

template <typename Alloc, typename T1, typename T2>
tuple(bksge::allocator_arg_t, Alloc, bksge::pair<T1, T2>) -> tuple<T1, T2>;

template <typename Alloc, typename... UTypes>
tuple(bksge::allocator_arg_t, Alloc, tuple<UTypes...>) -> tuple<UTypes...>;

#endif

template <typename... TTypes, typename... UTypes>
inline BKSGE_CONSTEXPR bool
operator==(tuple<TTypes...> const& lhs, tuple<UTypes...> const& rhs)
{
	static_assert(sizeof...(TTypes) == sizeof...(UTypes),
		"tuple objects can only be compared if they have equal sizes.");
	return tuple_detail::tuple_cmp_eq(lhs, rhs, bksge::index_sequence_for<TTypes...>());
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename... TTypes, typename... UTypes>
inline BKSGE_CONSTEXPR
bksge::common_comparison_category_t<bksge::detail::synth3way_t<TTypes, UTypes>...>
operator<=>(tuple<TTypes...> const& lhs, tuple<UTypes...> const& rhs)
{
	using Cat = bksge::common_comparison_category_t<bksge::detail::synth3way_t<TTypes, UTypes>...>;
	return tuple_detail::tuple_cmp_3way<Cat>(lhs, rhs, bksge::index_sequence_for<TTypes...>());
}

#else

template <typename... TTypes, typename... UTypes>
inline BKSGE_CONSTEXPR bool
operator<(tuple<TTypes...> const& lhs, tuple<UTypes...> const& rhs)
{
	static_assert(sizeof...(TTypes) == sizeof...(UTypes),
		"tuple objects can only be compared if they have equal sizes.");
	return tuple_detail::tuple_cmp_less(lhs, rhs, bksge::index_sequence_for<TTypes...>());
}

template <typename... TTypes, typename... UTypes>
inline BKSGE_CONSTEXPR bool
operator!=(tuple<TTypes...> const& lhs, tuple<UTypes...> const& rhs)
{
	return !(lhs == rhs);
}

template <typename... TTypes, typename... UTypes>
inline BKSGE_CONSTEXPR bool
operator>(tuple<TTypes...> const& lhs, tuple<UTypes...> const& rhs)
{
	return rhs < lhs;
}

template <typename... TTypes, typename... UTypes>
inline BKSGE_CONSTEXPR bool
operator<=(tuple<TTypes...> const& lhs, tuple<UTypes...> const& rhs)
{
	return !(rhs < lhs);
}

template <typename... TTypes, typename... UTypes>
inline BKSGE_CONSTEXPR bool
operator>=(tuple<TTypes...> const& lhs, tuple<UTypes...> const& rhs)
{
	return !(lhs < rhs);
}

#endif	// defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename... Types>
inline BKSGE_CXX14_CONSTEXPR
bksge::enable_if_t<bksge::conjunction<bksge::is_swappable<Types>...>::value>
swap(tuple<Types...>& lhs, tuple<Types...>& rhs)
BKSGE_NOEXCEPT_IF_EXPR((lhs.swap(rhs)))
{
	lhs.swap(rhs);
}

template <typename... Types>
BKSGE_CXX14_CONSTEXPR
bksge::enable_if_t<!bksge::conjunction<bksge::is_swappable<Types>...>::value>
swap(tuple<Types...>&, tuple<Types...>&) = delete;

}	// namespace bksge

#include <bksge/fnd/memory/uses_allocator.hpp>

namespace BKSGE_USES_ALLOCATOR_NAMESPACE
{

template <typename... Types, typename Alloc>
struct uses_allocator<bksge::tuple<Types...>, Alloc> : public bksge::true_type {};

}	// namespace BKSGE_USES_ALLOCATOR_NAMESPACE

#endif

#endif // BKSGE_FND_TUPLE_TUPLE_HPP
