/**
 *	@file	use_alloc.hpp
 *
 *	@brief	use_alloc の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_USE_ALLOC_HPP
#define BKSGE_FND_TUPLE_DETAIL_USE_ALLOC_HPP

#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/memory/allocator_arg.hpp>
#include <bksge/fnd/memory/uses_allocator.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace tuple_detail
{

struct uses_alloc_base {};

struct uses_alloc0 : public uses_alloc_base
{
	struct Sink
	{
		void BKSGE_CXX14_CONSTEXPR operator=(void const*) {}
	} m_a;
};

template <typename Alloc>
struct uses_alloc1 : public uses_alloc_base
{
	Alloc const* m_a;
};

template <typename Alloc>
struct uses_alloc2 : public uses_alloc_base
{
	Alloc const* m_a;
};

template <bool, typename T, typename Alloc, typename... Args>
struct uses_alloc;

template<typename T, typename Alloc, typename... Args>
struct uses_alloc<true, T, Alloc, Args...>
	: public bksge::conditional<
	bksge::is_constructible<T, bksge::allocator_arg_t, Alloc const&, Args...>::value,
	uses_alloc1<Alloc>,
	uses_alloc2<Alloc>>::type
{
	static_assert(bksge::disjunction<
		bksge::is_constructible<T, bksge::allocator_arg_t, Alloc const&, Args...>,
		bksge::is_constructible<T, Args..., Alloc const&>>::value,
		"construction with an allocator must be possible"
		" if uses_allocator is true");
};

template<typename T, typename Alloc, typename... Args>
struct uses_alloc<false, T, Alloc, Args...>
	: public uses_alloc0 {};

template<typename T, typename Alloc, typename... Args>
using uses_alloc_t = uses_alloc<bksge::uses_allocator<T, Alloc>::value, T, Alloc, Args...>;

template<typename T, typename Alloc, typename... Args>
inline BKSGE_CXX14_CONSTEXPR uses_alloc_t<T, Alloc, Args...>
use_alloc(Alloc const& a)
{
	uses_alloc_t<T, Alloc, Args...> ret{};
	ret.m_a = bksge::addressof(a);
	return ret;
}

template<typename T, typename Alloc, typename... Args>
void use_alloc(Alloc const&&) = delete;

}	// namespace tuple_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_USE_ALLOC_HPP
