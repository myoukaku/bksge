/**
 *	@file	variant.hpp
 *
 *	@brief	variant の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_VARIANT_HPP
#define BKSGE_FND_VARIANT_VARIANT_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_HAS_STD_VARIANT)

namespace bksge
{

using std::variant;

}	// namespace bksge

#else

#include <bksge/fnd/variant/fwd/variant_fwd.hpp>
#include <bksge/fnd/variant/variant_alternative.hpp>
#include <bksge/fnd/variant/detail/access.hpp>
#include <bksge/fnd/variant/detail/best_match_t.hpp>
#include <bksge/fnd/variant/detail/dependent_type.hpp>
#include <bksge/fnd/variant/detail/find_unambiguous_index_sfinae.hpp>
#include <bksge/fnd/variant/detail/sfinae_assign_base.hpp>
#include <bksge/fnd/variant/detail/sfinae_ctor_base.hpp>
#include <bksge/fnd/variant/detail/variant_impl.hpp>
#include <bksge/fnd/variant/detail/visitation.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <initializer_list>

BKSGE_WARNING_PUSH();

#if (defined(BKSGE_GCC) && (BKSGE_GCC >= 90000))
BKSGE_WARNING_DISABLE_GCC("-Wdeprecated-copy");
#endif

namespace bksge
{

template <typename... Types>
class variant
	: private variant_detail::sfinae_ctor_base<
		bksge::conjunction<
			bksge::is_copy_constructible<Types>...
		>::value,
		bksge::conjunction<
			bksge::is_move_constructible<Types>...
		>::value
	>
	, private variant_detail::sfinae_assign_base<
		bksge::conjunction<
			bksge::is_copy_constructible<Types>...,
			bksge::is_copy_assignable<Types>...
		>::value,
		bksge::conjunction<
			bksge::is_move_constructible<Types>...,
			bksge::is_move_assignable<Types>...
		>::value
	>
{
private:
	static_assert(0 < sizeof...(Types),
		"variant must consist of at least one alternative.");

	static_assert(bksge::conjunction<bksge::negation<bksge::is_array<Types>>...>::value,
		"variant can not have an array type as an alternative.");

	static_assert(bksge::conjunction<bksge::negation<bksge::is_reference<Types>>...>::value,
		"variant can not have a reference type as an alternative.");

	static_assert(bksge::conjunction<bksge::negation<bksge::is_void<Types>>...>::value,
		"variant can not have a void type as an alternative.");

	using first_type = variant_alternative_t<0, variant>;

public:
	template <
		bool Dummy = true,
		typename = bksge::enable_if_t<
			variant_detail::dependent_type<
				bksge::is_default_constructible<first_type>, Dummy
			>::value
		>
	>
	BKSGE_CONSTEXPR variant()
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_default_constructible<first_type>::value)
		: m_impl(bksge::in_place_index_t<0>{}) {}

	variant(variant const&) = default;
	variant(variant&&) = default;

	template <
		typename Arg,
		typename A = bksge::remove_cvref_t<Arg>,
		typename = bksge::enable_if_t<!bksge::is_same<A, variant>::value>,
		typename = bksge::enable_if_t<!bksge::is_in_place_type<A>::value>,
		typename = bksge::enable_if_t<!bksge::is_in_place_index<A>::value>,
		typename T = variant_detail::best_match_t<Arg, Types...>,
		std::size_t I = variant_detail::find_unambiguous_index_sfinae<T, Types...>::value,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Arg>::value>
	>
	BKSGE_CONSTEXPR variant(Arg&& arg)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_constructible<T, Arg>::value))
		: m_impl(bksge::in_place_index_t<I>{}, bksge::forward<Arg>(arg)) {}

	template <
		std::size_t I, typename... Args,
		typename = bksge::enable_if_t<(I < sizeof...(Types))>,
		typename T = variant_alternative_t<I, variant<Types...>>,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Args...>::value>
	>
	explicit BKSGE_CONSTEXPR
	variant(bksge::in_place_index_t<I>, Args&&... args)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_constructible<T, Args...>::value))
		: m_impl(bksge::in_place_index_t<I>{}, bksge::forward<Args>(args)...) {}

	template <
		std::size_t I,
		typename U,
		typename... Args,
		typename = bksge::enable_if_t<(I < sizeof...(Types))>,
		typename T = variant_alternative_t<I, variant<Types...>>,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, std::initializer_list<U>&, Args...>::value
		>
	>
	explicit BKSGE_CONSTEXPR
	variant(bksge::in_place_index_t<I>, std::initializer_list<U> il, Args&&... args)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value))
		: m_impl(bksge::in_place_index_t<I>{}, il, bksge::forward<Args>(args)...) {}

	template <
		typename T,
		typename... Args,
		std::size_t I = variant_detail::find_unambiguous_index_sfinae<T, Types...>::value,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Args...>::value>
	>
	explicit BKSGE_CONSTEXPR
	variant(bksge::in_place_type_t<T>, Args&&... args)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_constructible<T, Args...>::value))
		: m_impl(bksge::in_place_index_t<I>{}, bksge::forward<Args>(args)...) {}

	template <
		typename T,
		typename U,
		typename... Args,
		std::size_t I = variant_detail::find_unambiguous_index_sfinae<T, Types...>::value,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, std::initializer_list<U>&, Args...>::value
		>
	>
	explicit BKSGE_CONSTEXPR
	variant(bksge::in_place_type_t<T>, std::initializer_list<U> il, Args&&... args)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_constructible<T, std::initializer_list<U>&, Args...>::value))
		: m_impl(bksge::in_place_index_t<I>{}, il, bksge::forward<Args>(args)...) {}

	~variant() = default;

	variant& operator=(variant const&) = default;
	variant& operator=(variant&&) = default;

	template <
		typename Arg,
		typename = bksge::enable_if_t<
			!bksge::is_same<bksge::remove_cvref_t<Arg>, variant>::value
		>,
		typename T = variant_detail::best_match_t<Arg, Types...>,
		std::size_t I = variant_detail::find_unambiguous_index_sfinae<T, Types...>::value,
		typename = bksge::enable_if_t<
			bksge::is_assignable<T&, Arg>::value &&
			bksge::is_constructible<T, Arg>::value
		>
	>
	variant& operator=(Arg&& arg)
		BKSGE_NOEXCEPT_IF((
			bksge::is_nothrow_assignable<T&, Arg>::value &&
			bksge::is_nothrow_constructible<T, Arg>::value))
	{
		m_impl.template assign_impl<I>(bksge::forward<Arg>(arg));
		return *this;
	}

	template <
		std::size_t I,
		typename... Args,
		typename = bksge::enable_if_t<(I < sizeof...(Types))>,
		typename T = variant_alternative_t<I, variant<Types...>>,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Args...>::value>
	>
	T& emplace(Args&&... args)
	{
		return m_impl.template emplace_impl<I>(bksge::forward<Args>(args)...);
	}

	template <
		std::size_t I,
		typename U,
		typename... Args,
		typename = bksge::enable_if_t<(I < sizeof...(Types))>,
		typename T = variant_alternative_t<I, variant<Types...>>,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, std::initializer_list<U>&, Args...>::value
		>
	>
	T& emplace(std::initializer_list<U> il, Args&&... args)
	{
		return m_impl.template emplace_impl<I>(il, bksge::forward<Args>(args)...);
	}

	template <
		typename T,
		typename... Args,
		std::size_t I = variant_detail::find_unambiguous_index_sfinae<T, Types...>::value,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Args...>::value>
	>
	T& emplace(Args&&... args)
	{
		return m_impl.template emplace_impl<I>(bksge::forward<Args>(args)...);
	}

	template <
		typename T,
		typename U,
		typename... Args,
		std::size_t I = variant_detail::find_unambiguous_index_sfinae<T, Types...>::value,
		typename = bksge::enable_if_t<
			bksge::is_constructible<T, std::initializer_list<U>&, Args...>::value
		>
	>
	T& emplace(std::initializer_list<U> il, Args&&... args)
	{
		return m_impl.template emplace_impl<I>(il, bksge::forward<Args>(args)...);
	}

	BKSGE_CONSTEXPR bool valueless_by_exception() const BKSGE_NOEXCEPT
	{
		return m_impl.valueless_by_exception();
	}

	BKSGE_CONSTEXPR std::size_t index() const BKSGE_NOEXCEPT
	{
		return m_impl.index();
	}

	template <
		bool Dummy = true,
		typename = bksge::enable_if_t<
			variant_detail::dependent_type<bksge::conjunction<
				bksge::is_move_constructible<Types>...,
				bksge::is_swappable<Types>...
			>, Dummy>::value
		>
	>
	void swap(variant& that)
		BKSGE_NOEXCEPT_IF((
			bksge::conjunction<
				bksge::is_nothrow_move_constructible<Types>...,
				bksge::is_nothrow_swappable<Types>...
			>::value))
	{
		m_impl.swap_impl(that.m_impl);
	}

private:
	variant_detail::variant_impl<Types...> m_impl;

	friend struct variant_detail::access::variant_t;
	friend struct variant_detail::visitation::variant_t;
};

template <typename... Types>
BKSGE_CONSTEXPR bool
operator==(variant<Types...> const& lhs, variant<Types...> const& rhs);

template <typename... Types>
BKSGE_CONSTEXPR bool
operator!=(variant<Types...> const& lhs, variant<Types...> const& rhs);

template <typename... Types>
BKSGE_CONSTEXPR bool
operator<(variant<Types...> const& lhs, variant<Types...> const& rhs);

template <typename... Types>
BKSGE_CONSTEXPR bool
operator>(variant<Types...> const& lhs, variant<Types...> const& rhs);

template <typename... Types>
BKSGE_CONSTEXPR bool
operator<=(variant<Types...> const& lhs, variant<Types...> const& rhs);

template <typename... Types>
BKSGE_CONSTEXPR bool
operator>=(variant<Types...> const& lhs, variant<Types...> const& rhs);

template <typename... Types>
inline auto
swap(variant<Types...>& lhs, variant<Types...>& rhs)
	BKSGE_NOEXCEPT_IF_EXPR(lhs.swap(rhs))
	-> decltype(lhs.swap(rhs))
{
	lhs.swap(rhs);
}

}	// namespace bksge

#include <bksge/fnd/variant/detail/enable_hash_helper.hpp>
#include <bksge/fnd/functional/hash_combine.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <functional>

namespace std
{

template <typename... Types>
struct hash<
	bksge::variant_detail::enable_hash_helper<
		bksge::variant<Types...>,
		bksge::remove_const_t<Types>...
	>
>
{
private:
	using argument_type = bksge::variant<Types...>;
	using result_type = std::size_t;

	struct Visitor
	{
		template <typename T>
		std::size_t operator()(T const& alt) const
		{
			using alt_type = bksge::remove_cvref_t<T>;
			using value_type = bksge::remove_const_t<
				typename alt_type::value_type>;
			return std::hash<value_type>{}(alt.m_value);
		}
	};

public:
	result_type operator()(argument_type const& v) const
	{
		using bksge::variant_detail::visitation::variant_t;
		std::size_t res =
			v.valueless_by_exception() ?
				299792458 : // Random value chosen by the universe upon creation
				variant_t::visit_alt(Visitor{}, v);
		return bksge::hash_combine(res, std::hash<std::size_t>{}(v.index()));
	}
};

}	// namespace std

BKSGE_WARNING_POP();

#include <bksge/fnd/variant/inl/variant_inl.hpp>

#endif

#endif // BKSGE_FND_VARIANT_VARIANT_HPP
