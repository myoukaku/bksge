/**
 *	@file	allocator_like.hpp
 *
 *	@brief	allocator_like の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_DETAIL_ALLOCATOR_LIKE_HPP
#define BKSGE_FND_STRING_DETAIL_ALLOCATOR_LIKE_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Allocator>
concept allocator_like =
	requires(Allocator& alloc)
	{
		typename Allocator::value_type;
		alloc.allocate(bksge::declval<bksge::size_t>());
	};

#else

template <typename Allocator, typename = void>
struct allocator_like : public bksge::false_type {};

template <typename Allocator>
struct allocator_like<Allocator,
	bksge::void_t<typename Allocator::value_type,
	decltype(bksge::declval<Allocator&>().allocate(bksge::size_t{}))>>
	: public bksge::true_type {};

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STRING_DETAIL_ALLOCATOR_LIKE_HPP
