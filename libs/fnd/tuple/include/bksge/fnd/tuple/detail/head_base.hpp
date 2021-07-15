/**
 *	@file	head_base.hpp
 *
 *	@brief	head_base の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_HEAD_BASE_HPP
#define BKSGE_FND_TUPLE_DETAIL_HEAD_BASE_HPP

#include <bksge/fnd/tuple/fwd/tuple_fwd.hpp>
#include <bksge/fnd/tuple/detail/use_alloc.hpp>
#include <bksge/fnd/memory/allocator_arg.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_empty.hpp>
#include <bksge/fnd/type_traits/is_final.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace tuple_detail
{

template <typename T>
struct is_empty_non_tuple : public bksge::is_empty<T> {};

// Using EBO for elements that are tuples causes ambiguous base errors.
template <typename T0, typename... Types>
struct is_empty_non_tuple<bksge::tuple<T0, Types...>> : public bksge::false_type {};

// Use the Empty Base-class Optimization for empty, non-final types.
template <typename T>
using empty_not_final = bksge::conditional_t<
	bksge::is_final<T>::value,
	bksge::false_type,
	is_empty_non_tuple<T>>;

template <std::size_t Idx, typename Head,
	bool = empty_not_final<Head>::value>
struct head_base;

#if defined(BKSGE_HAS_CXX20_NO_UNIQUE_ADDRESS)

template <std::size_t Idx, typename Head>
struct head_base<Idx, Head, true>
{
	BKSGE_CONSTEXPR
	head_base()
		: m_head_impl()
	{}

	BKSGE_CONSTEXPR
	head_base(Head const& h)
		: m_head_impl(h)
	{}

	BKSGE_CONSTEXPR head_base(head_base const&) = default;
	BKSGE_CONSTEXPR head_base(head_base&&) = default;

	template <typename UHead>
	BKSGE_CONSTEXPR
	head_base(UHead&& h)
		: m_head_impl(bksge::forward<UHead>(h))
	{}

	BKSGE_CONSTEXPR
	head_base(bksge::allocator_arg_t, uses_alloc0)
		: m_head_impl()
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	head_base(bksge::allocator_arg_t, uses_alloc1<Alloc> a)
		: m_head_impl(bksge::allocator_arg, *a.m_a)
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	head_base(bksge::allocator_arg_t, uses_alloc2<Alloc> a)
		: m_head_impl(*a.m_a)
	{}

	template <typename UHead>
	BKSGE_CONSTEXPR
	head_base(uses_alloc0, UHead&& uhead)
		: m_head_impl(bksge::forward<UHead>(uhead))
	{}

	template <typename Alloc, typename UHead>
	BKSGE_CONSTEXPR
	head_base(uses_alloc1<Alloc> a, UHead&& uhead)
		: m_head_impl(bksge::allocator_arg, *a.m_a, bksge::forward<UHead>(uhead))
	{}

	template <typename Alloc, typename UHead>
	BKSGE_CONSTEXPR
	head_base(uses_alloc2<Alloc> a, UHead&& uhead)
		: m_head_impl(bksge::forward<UHead>(uhead), *a.m_a)
	{}

	static BKSGE_CONSTEXPR Head&
	head(head_base& b) BKSGE_NOEXCEPT { return b.m_head_impl; }

	static BKSGE_CONSTEXPR Head const&
	head(head_base const& b) BKSGE_NOEXCEPT { return b.m_head_impl; }

	[[no_unique_address]] Head m_head_impl;
};

#else

template <std::size_t Idx, typename Head>
struct head_base<Idx, Head, true>
	: public Head
{
	BKSGE_CONSTEXPR
	head_base()
		: Head()
	{}

	BKSGE_CONSTEXPR
	head_base(Head const& h)
		: Head(h)
	{}

	BKSGE_CONSTEXPR head_base(head_base const&) = default;
	BKSGE_CONSTEXPR head_base(head_base&&) = default;

	template <typename UHead>
	BKSGE_CONSTEXPR
	head_base(UHead&& h)
		: Head(bksge::forward<UHead>(h))
	{}

	BKSGE_CONSTEXPR
	head_base(bksge::allocator_arg_t, uses_alloc0)
		: Head()
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	head_base(bksge::allocator_arg_t, uses_alloc1<Alloc> a)
		: Head(bksge::allocator_arg, *a.m_a)
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	head_base(bksge::allocator_arg_t, uses_alloc2<Alloc> a)
		: Head(*a.m_a)
	{}

	template <typename UHead>
	BKSGE_CONSTEXPR
	head_base(uses_alloc0, UHead&& uhead)
		: Head(bksge::forward<UHead>(uhead))
	{}

	template <typename Alloc, typename UHead>
	BKSGE_CONSTEXPR
	head_base(uses_alloc1<Alloc> a, UHead&& uhead)
		: Head(bksge::allocator_arg, *a.m_a, bksge::forward<UHead>(uhead))
	{}

	template <typename Alloc, typename UHead>
	BKSGE_CONSTEXPR
	head_base(uses_alloc2<Alloc> a, UHead&& uhead)
		: Head(bksge::forward<UHead>(uhead), *a.m_a)
	{}

	static BKSGE_CONSTEXPR Head&
	head(head_base& b) BKSGE_NOEXCEPT { return b; }

	static BKSGE_CONSTEXPR Head const&
	head(head_base const& b) BKSGE_NOEXCEPT { return b; }
};
#endif

template <std::size_t Idx, typename Head>
struct head_base<Idx, Head, false>
{
	BKSGE_CONSTEXPR head_base()
		: m_head_impl()
	{}

	BKSGE_CONSTEXPR head_base(Head const& h)
		: m_head_impl(h)
	{}

	BKSGE_CONSTEXPR head_base(head_base const&) = default;
	BKSGE_CONSTEXPR head_base(head_base&&) = default;

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

	template <typename UHead>
	BKSGE_CONSTEXPR head_base(UHead&& h)
		: m_head_impl(bksge::forward<UHead>(h))
	{}

BKSGE_WARNING_POP();

	BKSGE_CONSTEXPR
	head_base(bksge::allocator_arg_t, uses_alloc0)
		: m_head_impl()
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	head_base(bksge::allocator_arg_t, uses_alloc1<Alloc> a)
		: m_head_impl(bksge::allocator_arg, *a.m_a)
	{}

	template <typename Alloc>
	BKSGE_CONSTEXPR
	head_base(bksge::allocator_arg_t, uses_alloc2<Alloc> a)
		: m_head_impl(*a.m_a)
	{}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4244);

	template <typename UHead>
	BKSGE_CONSTEXPR
	head_base(uses_alloc0, UHead&& uhead)
		: m_head_impl(bksge::forward<UHead>(uhead))
	{}

BKSGE_WARNING_POP();

	template <typename Alloc, typename UHead>
	BKSGE_CONSTEXPR
	head_base(uses_alloc1<Alloc> a, UHead&& uhead)
		: m_head_impl(bksge::allocator_arg, *a.m_a, bksge::forward<UHead>(uhead))
	{}

	template <typename Alloc, typename UHead>
	BKSGE_CONSTEXPR
	head_base(uses_alloc2<Alloc> a, UHead&& uhead)
		: m_head_impl(bksge::forward<UHead>(uhead), *a.m_a)
	{}

	static BKSGE_CONSTEXPR Head&
	head(head_base& b) BKSGE_NOEXCEPT { return b.m_head_impl; }

	static BKSGE_CONSTEXPR Head const&
	head(head_base const& b) BKSGE_NOEXCEPT { return b.m_head_impl; }

	Head m_head_impl;
};

}	// namespace tuple_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_HEAD_BASE_HPP
