/**
 *	@file	allocator_like.hpp
 *
 *	@brief	allocator_like の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_DETAIL_ALLOCATOR_LIKE_HPP
#define BKSGE_FND_STRING_DETAIL_ALLOCATOR_LIKE_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <utility>

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
		alloc.allocate(std::declval<std::size_t>());
	};

#else

template <typename Allocator, typename = void>
struct allocator_like : public bksge::false_type {};

template <typename Allocator>
struct allocator_like<Allocator,
	bksge::void_t<typename Allocator::value_type,
	decltype(std::declval<Allocator&>().allocate(std::size_t{}))>>
	: public bksge::true_type {};

#endif

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_STRING_DETAIL_ALLOCATOR_LIKE_HPP
