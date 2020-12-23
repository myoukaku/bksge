/**
 *	@file	pair.hpp
 *
 *	@brief	pair を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_UTILITY_PAIR_HPP
#define BKSGE_FND_UTILITY_PAIR_HPP

#include <bksge/fnd/utility/config.hpp>

#if defined(BKSGE_USE_STD_PAIR)

#include <bksge/fnd/tuple/get.hpp>
#include <utility>

namespace bksge
{

using std::pair;
using std::make_pair;
using std::piecewise_construct;
using std::piecewise_construct_t;

}	// namespace bksge

#else

#include <bksge/fnd/compare/common_comparison_category.hpp>
#include <bksge/fnd/compare/detail/synth3way.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_copy_assignable.hpp>
#include <bksge/fnd/type_traits/is_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_implicitly_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_copy_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/unwrap_ref_decay.hpp>
#include <bksge/fnd/tuple/fwd/tuple_fwd.hpp>
#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

struct nonesuch
{
	nonesuch() = delete;
	~nonesuch() = delete;
	nonesuch(nonesuch const&) = delete;
	void operator=(nonesuch const&) = delete;
};

}	// namespace detail

/// Tag type for piecewise construction of std::pair objects.
struct piecewise_construct_t { explicit piecewise_construct_t() = default; };

/// Tag for piecewise construction of std::pair objects.
BKSGE_INLINE_VAR BKSGE_CONSTEXPR piecewise_construct_t piecewise_construct {};

template <typename T1, typename T2>
struct pair
{
	using first_type  = T1;
	using second_type = T2;

	T1 first;
	T2 second;

	// (1) Default constructor
	template <
		typename U1 = T1,
		typename U2 = T2,
		bksge::enable_if_t<bksge::conjunction<
			bksge::is_default_constructible<U1>,
			bksge::is_default_constructible<U2>,
			bksge::is_implicitly_default_constructible<U1>,
			bksge::is_implicitly_default_constructible<U2>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR pair()
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_default_constructible<U1>,
			bksge::is_nothrow_default_constructible<U2>>::value))
		: first(), second() {}

	template <
		typename U1 = T1,
		typename U2 = T2,
		bksge::enable_if_t<bksge::conjunction<
			bksge::is_default_constructible<U1>,
			bksge::is_default_constructible<U2>,
			bksge::negation<bksge::conjunction<
				bksge::is_implicitly_default_constructible<U1>,
				bksge::is_implicitly_default_constructible<U2>
			>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR pair()
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_default_constructible<U1>,
			bksge::is_nothrow_default_constructible<U2>>::value))
		: first(), second() {}

	// (2) Direct constructor
	template <
		typename U1 = T1,
		typename U2 = T2,
		bksge::enable_if_t<bksge::conjunction<
			bksge::is_copy_constructible<U1>,
			bksge::is_copy_constructible<U2>,
			bksge::is_convertible<U1 const&, U1>,
			bksge::is_convertible<U2 const&, U2>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR pair(T1 const& a, T2 const& b)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_copy_constructible<U1>,
			bksge::is_nothrow_copy_constructible<U2>>::value))
		: first(a), second(b) {}

	template <
		typename U1 = T1,
		typename U2 = T2,
		bksge::enable_if_t<bksge::conjunction<
			bksge::is_copy_constructible<U1>,
			bksge::is_copy_constructible<U2>,
			bksge::negation<bksge::conjunction<
				bksge::is_convertible<U1 const&, U1>,
				bksge::is_convertible<U2 const&, U2>
			>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR pair(T1 const& a, T2 const& b)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_copy_constructible<U1>,
			bksge::is_nothrow_copy_constructible<U2>>::value))
		: first(a), second(b) {}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);	// conversion from '' to '', possible loss of data

	// (3) Converting constructor
	template <typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			bksge::is_constructible<T1, U1&&>,
			bksge::is_constructible<T2, U2&&>,
			bksge::is_convertible<U1&&, T1>,
			bksge::is_convertible<U2&&, T2>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR pair(U1&& x, U2&& y)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_constructible<T1, U1&&>,
			bksge::is_nothrow_constructible<T2, U2&&>>::value))
		: first (bksge::forward<U1>(x))
		, second(bksge::forward<U2>(y)) {}

BKSGE_WARNING_POP();

	template <typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			bksge::is_constructible<T1, U1&&>,
			bksge::is_constructible<T2, U2&&>,
			bksge::negation<bksge::conjunction<
				bksge::is_convertible<U1&&, T1>,
				bksge::is_convertible<U2&&, T2>
			>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR pair(U1&& x, U2&& y)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_constructible<T1, U1&&>,
			bksge::is_nothrow_constructible<T2, U2&&>>::value))
		: first (bksge::forward<U1>(x))
		, second(bksge::forward<U2>(y)) {}

	// (4) Construct from pair<U1, U2> const&
	template <
		typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			bksge::is_constructible<T1, U1 const&>,
			bksge::is_constructible<T2, U2 const&>,
			bksge::is_convertible<U1 const&, T1>,
			bksge::is_convertible<U2 const&, T2>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR pair(pair<U1, U2> const& p)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_constructible<T1, U1 const&>,
			bksge::is_nothrow_constructible<T2, U2 const&>>::value))
		: first(p.first), second(p.second) {}

	template <
		typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			bksge::is_constructible<T1, U1 const&>,
			bksge::is_constructible<T2, U2 const&>,
			bksge::negation<bksge::conjunction<
				bksge::is_convertible<U1 const&, T1>,
				bksge::is_convertible<U2 const&, T2>
			>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR pair(pair<U1, U2> const& p)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_constructible<T1, U1 const&>,
			bksge::is_nothrow_constructible<T2, U2 const&>>::value))
		: first(p.first), second(p.second) {}

	// (5) Construct from pair<U1, U2>&&
	template <typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			bksge::is_constructible<T1, U1&&>,
			bksge::is_constructible<T2, U2&&>,
			bksge::is_convertible<U1&&, T1>,
			bksge::is_convertible<U2&&, T2>
		>::value>* = nullptr>
	BKSGE_CONSTEXPR pair(pair<U1, U2>&& p)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_constructible<T1, U1&&>,
			bksge::is_nothrow_constructible<T2, U2&&>>::value))
		: first (bksge::forward<U1>(p.first))
		, second(bksge::forward<U2>(p.second)) {}

	template <typename U1, typename U2,
		bksge::enable_if_t<bksge::conjunction<
			bksge::is_constructible<T1, U1&&>,
			bksge::is_constructible<T2, U2&&>,
			bksge::negation<bksge::conjunction<
				bksge::is_convertible<U1&&, T1>,
				bksge::is_convertible<U2&&, T2>
			>>
		>::value>* = nullptr>
	explicit BKSGE_CONSTEXPR pair(pair<U1, U2>&& p)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_constructible<T1, U1&&>,
			bksge::is_nothrow_constructible<T2, U2&&>>::value))
		: first (bksge::forward<U1>(p.first))
		, second(bksge::forward<U2>(p.second)) {}

	// (6) Piecewise constructor
	template <typename... Args1, typename... Args2>
	BKSGE_CONSTEXPR
	pair(piecewise_construct_t, bksge::tuple<Args1...> first, bksge::tuple<Args2...> second)
		: pair(first, second,
			bksge::make_index_sequence<sizeof...(Args1)>{},
			bksge::make_index_sequence<sizeof...(Args2)>{})
	{}

	// (7) Copy constructor
	BKSGE_CONSTEXPR pair(pair const&) = default;

	// (8) Move constructor
	BKSGE_CONSTEXPR pair(pair&&) = default;

	BKSGE_CXX14_CONSTEXPR
	pair&
	operator=(
		bksge::conditional_t<
			bksge::conjunction<
				bksge::is_copy_assignable<T1>,
				bksge::is_copy_assignable<T2>
			>::value,
			pair const&,
			detail::nonesuch const&> p)
	{
		first  = p.first;
		second = p.second;
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR
	pair&
	operator=(
		bksge::conditional_t<
			bksge::conjunction<
				bksge::is_move_assignable<T1>,
				bksge::is_move_assignable<T2>
			>::value,
			pair&&,
			detail::nonesuch&&> p)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_move_assignable<T1>,
			bksge::is_nothrow_move_assignable<T2>>::value))
	{
		first  = bksge::forward<first_type>(p.first);
		second = bksge::forward<second_type>(p.second);
		return *this;
	}

	template <typename U1, typename U2>
	BKSGE_CXX14_CONSTEXPR
	bksge::enable_if_t<bksge::conjunction<
		bksge::is_assignable<T1&, U1 const&>,
		bksge::is_assignable<T2&, U2 const&>>::value,
		pair&>
	operator=(pair<U1, U2> const& p)
	{
		first  = p.first;
		second = p.second;
		return *this;
	}

	template <typename U1, typename U2>
	BKSGE_CXX14_CONSTEXPR
	bksge::enable_if_t<bksge::conjunction<
		bksge::is_assignable<T1&, U1&&>,
		bksge::is_assignable<T2&, U2&&>>::value,
		pair&>
	operator=(pair<U1, U2>&& p)
	{
		first  = bksge::forward<U1>(p.first);
		second = bksge::forward<U2>(p.second);
		return *this;
	}

	/// Swap the first members and then the second members.
	BKSGE_CXX14_CONSTEXPR void
	swap(pair& p)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_swappable<T1>,
			bksge::is_nothrow_swappable<T2>
		>::value))
	{
		using bksge::swap;
		swap(first, p.first);
		swap(second, p.second);
	}

private:
	template <
		typename... Args1, bksge::size_t... Indices1,
		typename... Args2, bksge::size_t... Indices2>
	constexpr
	pair(
		bksge::tuple<Args1...>& tuple1,
		bksge::tuple<Args2...>& tuple2,
		bksge::index_sequence<Indices1...>,
		bksge::index_sequence<Indices2...>);
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename T1, typename T2>
pair(T1, T2) -> pair<T1, T2>;

#endif

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR bool
operator==(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return x.first == y.first && x.second == y.second;
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename T1, typename T2>
BKSGE_CONSTEXPR bksge::common_comparison_category_t<
	bksge::detail::synth3way_t<T1>,
	bksge::detail::synth3way_t<T2>>
operator<=>(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	if (auto c = bksge::detail::synth3way(x.first, y.first); c != 0)
	{
		return c;
	}
	return bksge::detail::synth3way(x.second, y.second);
}

#else

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR bool
operator<(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return x.first < y.first ||
		(!(y.first < x.first) && x.second < y.second);
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR bool
operator!=(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return !(x == y);
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR bool
operator>(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return y < x;
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR bool
operator<=(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return !(y < x);
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR bool
operator>=(pair<T1, T2> const& x, pair<T1, T2> const& y)
{
	return !(x < y);
}

#endif	// defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)


template <typename T1, typename T2>
inline BKSGE_CXX14_CONSTEXPR
bksge::enable_if_t<bksge::conjunction<
	bksge::is_swappable<T1>,
	bksge::is_swappable<T2>>::value>
swap(pair<T1, T2>& x, pair<T1, T2>& y)
	BKSGE_NOEXCEPT_IF_EXPR(x.swap(y))
{
	x.swap(y);
}

template <typename T1, typename T2>
bksge::enable_if_t<!bksge::conjunction<
	bksge::is_swappable<T1>,
	bksge::is_swappable<T2>>::value>
swap(pair<T1, T2>&, pair<T1, T2>&) = delete;


template <typename T1, typename T2>
inline BKSGE_CONSTEXPR pair<
	bksge::unwrap_ref_decay_t<T1>,
	bksge::unwrap_ref_decay_t<T2>>
make_pair(T1&& x, T2&& y)
{
	using type1 = bksge::unwrap_ref_decay_t<T1>;
	using type2 = bksge::unwrap_ref_decay_t<T2>;
	using pair_type = pair<type1, type2>;
	return pair_type(bksge::forward<T1>(x), bksge::forward<T2>(y));
}

namespace detail
{

template <bksge::size_t I>
struct pair_get;

template <>
struct pair_get<0>
{
	template <typename T1, typename T2>
	static BKSGE_CONSTEXPR T1&
	get(pair<T1, T2>& p) BKSGE_NOEXCEPT
	{
		return p.first;
	}

	template <typename T1, typename T2>
	static BKSGE_CONSTEXPR T1&&
	get(pair<T1, T2>&& p) BKSGE_NOEXCEPT
	{
		return bksge::forward<T1>(p.first);
	}

	template <typename T1, typename T2>
	static BKSGE_CONSTEXPR T1 const&
	get(pair<T1, T2> const& p) BKSGE_NOEXCEPT
	{
		return p.first;
	}

	template <typename T1, typename T2>
	static BKSGE_CONSTEXPR T1 const&&
	get(pair<T1, T2> const&& p) BKSGE_NOEXCEPT
	{
		return bksge::forward<T1 const>(p.first);
	}
};

template <>
struct pair_get<1>
{
	template <typename T1, typename T2>
	static BKSGE_CONSTEXPR T2&
	get(pair<T1, T2>& p) BKSGE_NOEXCEPT
	{
		return p.second;
	}

	template <typename T1, typename T2>
	static BKSGE_CONSTEXPR T2&&
	get(pair<T1, T2>&& p) BKSGE_NOEXCEPT
	{
		return bksge::forward<T2>(p.second);
	}

	template <typename T1, typename T2>
	static BKSGE_CONSTEXPR T2 const&
	get(pair<T1, T2> const& p) BKSGE_NOEXCEPT
	{
		return p.second;
	}

	template <typename T1, typename T2>
	static BKSGE_CONSTEXPR T2 const&&
	get(pair<T1, T2> const&& p) BKSGE_NOEXCEPT
	{
		return bksge::forward<T2 const>(p.second);
	}
};

}	// namespace detail

template <bksge::size_t I, typename T1, typename T2>
inline BKSGE_CONSTEXPR
bksge::tuple_element_t<I, pair<T1, T2>>&
get(pair<T1, T2>& in) BKSGE_NOEXCEPT
{
	return detail::pair_get<I>::get(in);
}

template <bksge::size_t I, typename T1, typename T2>
inline BKSGE_CONSTEXPR
bksge::tuple_element_t<I, pair<T1, T2>>&&
get(pair<T1, T2>&& in) BKSGE_NOEXCEPT
{
	return detail::pair_get<I>::get(bksge::move(in));
}

template <bksge::size_t I, typename T1, typename T2>
inline BKSGE_CONSTEXPR
bksge::tuple_element_t<I, pair<T1, T2>> const&
get(pair<T1, T2> const& in) BKSGE_NOEXCEPT
{
	return detail::pair_get<I>::get(in);
}

template <bksge::size_t I, typename T1, typename T2>
inline BKSGE_CONSTEXPR
bksge::tuple_element_t<I, pair<T1, T2>> const&&
get(pair<T1, T2> const&& in) BKSGE_NOEXCEPT
{
	return detail::pair_get<I>::get(bksge::move(in));
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR T1&
get(pair<T1, T2>& p) BKSGE_NOEXCEPT
{
	return p.first;
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR T1 const&
get(pair<T1, T2> const& p) BKSGE_NOEXCEPT
{
	return p.first;
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR T1&&
get(pair<T1, T2>&& p) BKSGE_NOEXCEPT
{
	return bksge::move(p.first);
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR T1 const&&
get(pair<T1, T2> const&& p) BKSGE_NOEXCEPT
{
	return bksge::move(p.first);
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR T1&
get(pair<T2, T1>& p) BKSGE_NOEXCEPT
{
	return p.second;
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR T1 const&
get(pair<T2, T1> const& p) BKSGE_NOEXCEPT
{
	return p.second;
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR T1&&
get(pair<T2, T1>&& p) BKSGE_NOEXCEPT
{
	return bksge::move(p.second);
}

template <typename T1, typename T2>
inline BKSGE_CONSTEXPR T1 const&&
get(pair<T2, T1> const&& p) BKSGE_NOEXCEPT
{
	return bksge::move(p.second);
}

}	// namespace bksge

#include <bksge/fnd/tuple/tuple.hpp>
#include <bksge/fnd/tuple/get.hpp>

namespace bksge
{

template <typename T1, typename T2>
template <
	typename... Args1, bksge::size_t... Indices1,
	typename... Args2, bksge::size_t... Indices2>
constexpr
pair<T1, T2>::pair(
	bksge::tuple<Args1...>& tuple1,
	bksge::tuple<Args2...>& tuple2,
	bksge::index_sequence<Indices1...>,
	bksge::index_sequence<Indices2...>)
	: first (bksge::forward<Args1>(get<Indices1>(tuple1))...)
	, second(bksge::forward<Args2>(get<Indices2>(tuple2))...)
{}

}	// namespace bksge

#endif	// defined(BKSGE_USE_STD_PAIR)

#include <bksge/fnd/tuple/tuple_element.hpp>
#include <bksge/fnd/tuple/tuple_size.hpp>
#include <bksge/fnd/tuple/config.hpp>

#if !defined(BKSGE_USE_STD_TUPLE) || !defined(BKSGE_USE_STD_PAIR)

#include <bksge/fnd/type_traits/integral_constant.hpp>

namespace BKSGE_TUPLE_NAMESPACE
{

template <typename T1, typename T2>
struct tuple_size<bksge::pair<T1, T2>>
	: public bksge::integral_constant<bksge::size_t, 2> {};

template <typename T1, typename T2>
struct tuple_element<0, bksge::pair<T1, T2>>
{
	using type = T1;
};

template <typename T1, typename T2>
struct tuple_element<1, bksge::pair<T1, T2>>
{
	using type = T2;
};

}	// namespace BKSGE_TUPLE_NAMESPACE

#endif

#endif // BKSGE_FND_UTILITY_PAIR_HPP
