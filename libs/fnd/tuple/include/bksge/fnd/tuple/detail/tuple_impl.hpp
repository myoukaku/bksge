/**
 *	@file	tuple_impl.hpp
 *
 *	@brief	tuple_impl の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_TUPLE_IMPL_HPP
#define BKSGE_FND_TUPLE_DETAIL_TUPLE_IMPL_HPP

#include <bksge/fnd/tuple/detail/head_base.hpp>
#include <bksge/fnd/tuple/detail/use_alloc.hpp>
#include <bksge/fnd/memory/allocator_arg.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace tuple_detail
{

/**
 * Contains the actual implementation of the @c tuple template, stored
 * as a recursive inheritance hierarchy from the first element (most
 * derived class) to the last (least derived class). The @c Idx
 * parameter gives the 0-based index of the element stored at this
 * point in the hierarchy; we use it to implement a constant-time
 * get() operation.
 */
template <std::size_t Idx, typename... Types>
struct tuple_impl;

/**
 * Recursive tuple implementation. Here we store the @c Head element
 * and derive from a @c Tuple_impl containing the remaining elements
 * (which contains the @c Tail).
 */
template <std::size_t Idx, typename Head, typename... Tail>
struct tuple_impl<Idx, Head, Tail...>
	: public tuple_impl<Idx + 1, Tail...>
	, private head_base<Idx, Head>
{
	template <std::size_t, typename...>
	friend struct tuple_impl;

	using Inherited = tuple_impl<Idx + 1, Tail...>;
	using Base = head_base<Idx, Head>;

	static BKSGE_CONSTEXPR Head&
	head(tuple_impl& t) BKSGE_NOEXCEPT { return Base::head(t); }

	static BKSGE_CONSTEXPR Head const&
	head(tuple_impl const& t) BKSGE_NOEXCEPT { return Base::head(t); }

	static BKSGE_CONSTEXPR Inherited&
	tail(tuple_impl& t) BKSGE_NOEXCEPT { return t; }

	static BKSGE_CONSTEXPR Inherited const&
	tail(tuple_impl const& t) BKSGE_NOEXCEPT { return t; }

	BKSGE_CONSTEXPR
	tuple_impl()
		: Inherited()
		, Base()
	{}

	explicit BKSGE_CONSTEXPR
	tuple_impl(Head const& head, Tail const&... tail)
		: Inherited(tail...)
		, Base(head)
	{}

	template <typename UHead, typename... UTail,
		typename = bksge::enable_if_t<sizeof...(Tail) == sizeof...(UTail)>>
	explicit BKSGE_CONSTEXPR
	tuple_impl(UHead&& head, UTail&&... tail)
		: Inherited(bksge::forward<UTail>(tail)...)
		, Base(bksge::forward<UHead>(head))
	{}

	BKSGE_CONSTEXPR tuple_impl(tuple_impl const&) = default;

	tuple_impl& operator=(tuple_impl const&) = delete;

	BKSGE_CXX14_CONSTEXPR
	tuple_impl(tuple_impl&& in)
		BKSGE_NOEXCEPT_IF((bksge::conjunction<
			bksge::is_nothrow_move_constructible<Head>,
			bksge::is_nothrow_move_constructible<Inherited>>::value))
		: Inherited(std::move(tail(in)))
		, Base(bksge::forward<Head>(head(in)))
	{}

	template <typename... UTypes>
	BKSGE_CONSTEXPR
	tuple_impl(tuple_impl<Idx, UTypes...> const& in)
		: Inherited(tuple_impl<Idx, UTypes...>::tail(in))
		, Base(tuple_impl<Idx, UTypes...>::head(in))
	{}

	template <typename UHead, typename... UTails>
	BKSGE_CXX14_CONSTEXPR
	tuple_impl(tuple_impl<Idx, UHead, UTails...>&& in)
		: Inherited(std::move(tuple_impl<Idx, UHead, UTails...>::tail(in)))
		, Base(bksge::forward<UHead>(tuple_impl<Idx, UHead, UTails...>::head(in)))
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t tag, Alloc const& a)
		: Inherited(tag, a)
		, Base(tag, use_alloc<Head>(a))
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t tag, Alloc const& a, Head const& head, Tail const&... tail)
		: Inherited(tag, a, tail...)
		, Base(use_alloc<Head, Alloc, Head>(a), head)
	{}

	template <typename Alloc, typename UHead, typename... UTail,
		typename = bksge::enable_if_t<sizeof...(Tail) == sizeof...(UTail)>>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t tag, Alloc const& a, UHead&& head, UTail&&... tail)
		: Inherited(tag, a, bksge::forward<UTail>(tail)...)
		, Base(use_alloc<Head, Alloc, UHead>(a), bksge::forward<UHead>(head))
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t tag, Alloc const& a, tuple_impl const& in)
		: Inherited(tag, a, tail(in))
		, Base(use_alloc<Head, Alloc, Head>(a), head(in))
	{}

	template <typename Alloc>
	BKSGE_CXX14_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t tag, Alloc const& a, tuple_impl&& in)
		: Inherited(tag, a, std::move(tail(in)))
		, Base(use_alloc<Head, Alloc, Head>(a), bksge::forward<Head>(head(in)))
	{}

	template <typename Alloc, typename UHead, typename... UTails>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t tag, Alloc const& a, tuple_impl<Idx, UHead, UTails...> const& in)
		: Inherited(tag, a, tuple_impl<Idx, UHead, UTails...>::tail(in))
		, Base(use_alloc<Head, Alloc, UHead const&>(a), tuple_impl<Idx, UHead, UTails...>::head(in))
	{}

	template <typename Alloc, typename UHead, typename... UTails>
	BKSGE_CXX14_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t tag, Alloc const& a, tuple_impl<Idx, UHead, UTails...>&& in)
		: Inherited(tag, a, std::move(tuple_impl<Idx, UHead, UTails...>::tail(in)))
		, Base(use_alloc<Head, Alloc, UHead>(a), bksge::forward<UHead>(tuple_impl<Idx, UHead, UTails...>::head(in)))
	{}

	template <typename... UTypes>
	BKSGE_CXX14_CONSTEXPR
	void assign(tuple_impl<Idx, UTypes...> const& in)
	{
		head(*this) = tuple_impl<Idx, UTypes...>::head(in);
		tail(*this).assign(tuple_impl<Idx, UTypes...>::tail(in));
	}

	template <typename UHead, typename... UTails>
	BKSGE_CXX14_CONSTEXPR
	void assign(tuple_impl<Idx, UHead, UTails...>&& in)
	{
		head(*this) = bksge::forward<UHead>(tuple_impl<Idx, UHead, UTails...>::head(in));
		tail(*this).assign(std::move(tuple_impl<Idx, UHead, UTails...>::tail(in)));
	}

protected:
	BKSGE_CXX14_CONSTEXPR
	void swap(tuple_impl& in)
	{
		using bksge::swap;
		swap(head(*this), head(in));
		Inherited::swap(tail(in));
	}
};

// Basis case of inheritance recursion.
template <std::size_t Idx, typename Head>
struct tuple_impl<Idx, Head>
	: private head_base<Idx, Head>
{
	template <std::size_t, typename...>
	friend struct tuple_impl;

	using Base = head_base<Idx, Head>;

	static BKSGE_CONSTEXPR Head&
	head(tuple_impl& t) BKSGE_NOEXCEPT { return Base::head(t); }

	static BKSGE_CONSTEXPR Head const&
	head(tuple_impl const& t) BKSGE_NOEXCEPT { return Base::head(t); }

	BKSGE_CONSTEXPR
	tuple_impl()
		: Base()
	{}

	explicit BKSGE_CONSTEXPR
	tuple_impl(Head const& head)
		: Base(head)
	{}

	template <typename UHead>
	explicit BKSGE_CONSTEXPR
	tuple_impl(UHead&& head)
		: Base(bksge::forward<UHead>(head))
	{}

	BKSGE_CONSTEXPR tuple_impl(tuple_impl const&) = default;

	tuple_impl& operator=(tuple_impl const&) = delete;

	BKSGE_CONSTEXPR
	tuple_impl(tuple_impl&& in)
		BKSGE_NOEXCEPT_IF((bksge::is_nothrow_move_constructible<Head>::value))
		: Base(bksge::forward<Head>(head(in)))
	{}

	template <typename UHead>
	BKSGE_CONSTEXPR
	tuple_impl(tuple_impl<Idx, UHead> const& in)
		: Base(tuple_impl<Idx, UHead>::head(in))
	{}

	template <typename UHead>
	BKSGE_CONSTEXPR
	tuple_impl(tuple_impl<Idx, UHead>&& in)
		: Base(bksge::forward<UHead>(tuple_impl<Idx, UHead>::head(in)))
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t tag, Alloc const& a)
		: Base(tag, use_alloc<Head>(a))
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t /*tag*/, Alloc const& a, Head const& head)
		: Base(use_alloc<Head, Alloc, Head const&>(a), head)
	{}

	template <typename Alloc, typename UHead>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t /*tag*/, Alloc const& a, UHead&& head)
		: Base(use_alloc<Head, Alloc, UHead>(a), bksge::forward<UHead>(head))
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t /*tag*/, Alloc const& a, tuple_impl const& in)
		: Base(use_alloc<Head, Alloc, Head const&>(a), head(in))
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t /*tag*/, Alloc const& a, tuple_impl&& in)
		: Base(use_alloc<Head, Alloc, Head>(a), bksge::forward<Head>(head(in)))
	{}

	template <typename Alloc, typename UHead>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t /*tag*/, Alloc const& a, tuple_impl<Idx, UHead> const& in)
		: Base(use_alloc<Head, Alloc, UHead const&>(a), tuple_impl<Idx, UHead>::head(in))
	{}

	template <typename Alloc, typename UHead>
	BKSGE_CONSTEXPR
	tuple_impl(bksge::allocator_arg_t /*tag*/, Alloc const& a, tuple_impl<Idx, UHead>&& in)
		: Base(use_alloc<Head, Alloc, UHead>(a), bksge::forward<UHead>(tuple_impl<Idx, UHead>::head(in)))
	{}

	template <typename UHead>
	BKSGE_CXX14_CONSTEXPR
	void assign(tuple_impl<Idx, UHead> const& in)
	{
		head(*this) = tuple_impl<Idx, UHead>::head(in);
	}

	template <typename UHead>
	BKSGE_CXX14_CONSTEXPR
	void assign(tuple_impl<Idx, UHead>&& in)
	{
		head(*this) = bksge::forward<UHead>(tuple_impl<Idx, UHead>::head(in));
	}

protected:
	BKSGE_CXX14_CONSTEXPR
	void swap(tuple_impl& in)
	{
		using bksge::swap;
		swap(head(*this), head(in));
	}
};

template <typename... Types>
using tuple_impl_t = tuple_impl<0, Types...>;

}	// namespace tuple_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_TUPLE_IMPL_HPP
