/**
 *	@file	iterator_traits_base.hpp
 *
 *	@brief	iterator_traits_base の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITERATOR_TRAITS_BASE_HPP
#define BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITERATOR_TRAITS_BASE_HPP

#include <bksge/fnd/iterator/concepts/detail/iter_with_nested_types.hpp>
#include <bksge/fnd/iterator/concepts/detail/iter_without_nested_types.hpp>
#include <bksge/fnd/iterator/concepts/detail/cpp17_input_iterator.hpp>
#include <bksge/fnd/iterator/concepts/detail/cpp17_randacc_iterator.hpp>
#include <bksge/fnd/iterator/concepts/detail/cpp17_bidi_iterator.hpp>
#include <bksge/fnd/iterator/concepts/detail/cpp17_fwd_iterator.hpp>
#include <bksge/fnd/iterator/concepts/detail/cpp17_iterator.hpp>
#include <bksge/fnd/iterator/concepts/detail/has_iterator_category.hpp>
#include <bksge/fnd/iterator/concepts/detail/has_pointer.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/iterator/iter_reference_t.hpp>
#include <bksge/fnd/iterator/indirectly_readable_traits.hpp>
#include <bksge/fnd/iterator/incrementable_traits.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/declval.hpp>

namespace bksge
{

namespace detail
{

#define USE_CONCEPTS	0

template <typename T> struct always_false { static const bool value = false; };

template <typename Iterator, typename = void>
struct iterator_traits_base {};

template <typename Iterator>
#if USE_CONCEPTS
requires bksge::detail::iter_with_nested_types<Iterator>
#endif
struct iterator_traits_base<Iterator
#if !USE_CONCEPTS
	, bksge::enable_if_t<bksge::detail::iter_with_nested_types_t<Iterator>::value>
#endif
>
{
private:
	//static_assert(always_false<Iterator>::value, "iter_with_nested_types");

	template <typename Iter, typename = void>
	struct ptr
	{
		//static_assert(always_false<Iter>::value, "iter_with_nested_types::pointer = void");
		using type = void;
	};

	template <typename Iter>
#if USE_CONCEPTS
	requires requires { typename Iter::pointer; }
#endif
	struct ptr<Iter
#if !USE_CONCEPTS
		, bksge::void_t<typename Iter::pointer>
#endif
	>
	{
		//static_assert(always_false<Iter>::value, "iter_with_nested_types::pointer = Iter::pointer");
		using type = typename Iter::pointer;
	};

public:
	using iterator_category = typename Iterator::iterator_category;
	using value_type	    = typename Iterator::value_type;
	using difference_type   = typename Iterator::difference_type;
	using pointer	        = typename ptr<Iterator>::type;
	using reference	        = typename Iterator::reference;
};

template <typename Iterator>
#if USE_CONCEPTS
requires
	bksge::detail::iter_without_nested_types<Iterator> &&
	bksge::detail::cpp17_input_iterator<Iterator>
#endif
struct iterator_traits_base<Iterator
#if !USE_CONCEPTS
	, bksge::enable_if_t<
		bksge::detail::iter_without_nested_types_t<Iterator>::value &&
		bksge::detail::cpp17_input_iterator_t<Iterator>::value
	>
#endif
>
{
private:
	//static_assert(always_false<Iterator>::value, "cpp17_input_iterator");

	template <typename Iter, typename = void>
	struct cat
	{
		//static_assert(always_false<Iter>::value, "cpp17_input_iterator::category = input_iterator_tag");
		using type = bksge::input_iterator_tag;
	};

	template <typename Iter>
#if USE_CONCEPTS
	requires requires { typename Iter::iterator_category; }
#endif
	struct cat<Iter
#if !USE_CONCEPTS
		, bksge::enable_if_t<bksge::detail::has_iterator_category<Iter>::value>
#endif
	>
	{
		//static_assert(always_false<Iter>::value, "cpp17_input_iterator::category = Iter::iterator_category");
		using type = typename Iter::iterator_category;
	};

	template <typename Iter>
#if USE_CONCEPTS
	requires (
		!requires { typename Iter::iterator_category; } &&
		bksge::detail::cpp17_randacc_iterator<Iter>
	)
#endif
	struct cat<Iter
#if !USE_CONCEPTS
		, bksge::enable_if_t<
			!bksge::detail::has_iterator_category<Iter>::value &&
			bksge::detail::cpp17_randacc_iterator_t<Iter>::value
		>
#endif
	>
	{
		//static_assert(always_false<Iter>::value, "cpp17_input_iterator::category = random_access_iterator_tag");
		using type = bksge::random_access_iterator_tag;
	};

	template <typename Iter>
#if USE_CONCEPTS
	requires (
		!requires { typename Iter::iterator_category; } &&
		!bksge::detail::cpp17_randacc_iterator<Iter> &&
		bksge::detail::cpp17_bidi_iterator<Iter>
	)
#endif
	struct cat<Iter
#if !USE_CONCEPTS
		, bksge::enable_if_t<
			!bksge::detail::has_iterator_category<Iter>::value &&
			!bksge::detail::cpp17_randacc_iterator_t<Iter>::value &&
			bksge::detail::cpp17_bidi_iterator_t<Iter>::value
		>
#endif
	>
	{
		//static_assert(always_false<Iter>::value, "cpp17_input_iterator::category = bidirectional_iterator_tag");
		using type = bksge::bidirectional_iterator_tag;
	};

	template <typename Iter>
#if USE_CONCEPTS
	requires (
		!requires { typename Iter::iterator_category; } &&
		!bksge::detail::cpp17_bidi_iterator<Iter> &&
		bksge::detail::cpp17_fwd_iterator<Iter>
	)
#endif
	struct cat<Iter
#if !USE_CONCEPTS
		, bksge::enable_if_t<
			!bksge::detail::has_iterator_category<Iter>::value &&
			!bksge::detail::cpp17_bidi_iterator_t<Iter>::value &&
			bksge::detail::cpp17_fwd_iterator_t<Iter>::value
		>
#endif
	>
	{
		//static_assert(always_false<Iter>::value, "cpp17_input_iterator::category = forward_iterator_tag");
		using type = bksge::forward_iterator_tag;
	};

	template <typename Iter, typename = void, typename = void>
	struct ptr
	{
		//static_assert(always_false<Iter>::value, "cpp17_input_iterator::pointer = void");
		using type = void;
	};

	template <typename Iter>
#if USE_CONCEPTS
	requires requires { typename Iter::pointer; }
#endif
	struct ptr<Iter
#if !USE_CONCEPTS
		, bksge::enable_if_t<
			bksge::detail::has_pointer<Iter>::value
		>
#endif
	>
	{
		//static_assert(always_false<Iter>::value, "cpp17_input_iterator::pointer = Iter::pointer");
		using type = typename Iter::pointer;
	};

	template <typename Iter>
#if USE_CONCEPTS
	requires (
		!requires { typename Iter::pointer; } &&
		requires(Iter& it) { it.operator->(); }
	)
#endif
	struct ptr<Iter
#if !USE_CONCEPTS
		, bksge::enable_if_t<
			!bksge::detail::has_pointer<Iter>::value
		>,
		bksge::void_t<decltype(bksge::declval<Iter&>().operator->())>
#endif
	>
	{
		//static_assert(always_false<Iter>::value, "cpp17_input_iterator::pointer = decltype(operator->())");
		using type = decltype(bksge::declval<Iter&>().operator->());
	};

	template <typename Iter, typename = void>
	struct ref
	{
		//static_assert(always_false<Iter>::value, "cpp17_input_iterator::reference = iter_reference_t<Iter>");
		using type = bksge::iter_reference_t<Iter>;
	};

	template <typename Iter>
#if USE_CONCEPTS
	requires requires { typename Iter::reference; }
#endif
	struct ref<Iter
#if !USE_CONCEPTS
		, bksge::void_t<typename Iter::reference>
#endif
	>
	{
		//static_assert(always_false<Iter>::value, "cpp17_input_iterator::reference = Iter::reference");
		using type = typename Iter::reference;
	};

public:
	using iterator_category = typename cat<Iterator>::type;
	using value_type        = typename bksge::indirectly_readable_traits<Iterator>::value_type;
	using difference_type   = typename bksge::incrementable_traits<Iterator>::difference_type;
	using pointer	        = typename ptr<Iterator>::type;
	using reference	        = typename ref<Iterator>::type;
};

template <typename Iterator>
#if USE_CONCEPTS
requires
	bksge::detail::iter_without_nested_types<Iterator> &&
	bksge::detail::cpp17_iterator<Iterator>
#endif
struct iterator_traits_base<Iterator
#if !USE_CONCEPTS
	, bksge::enable_if_t<
		bksge::detail::iter_without_nested_types_t<Iterator>::value &&
		!bksge::detail::cpp17_input_iterator_t<Iterator>::value &&
		bksge::detail::cpp17_iterator_t<Iterator>::value
	>
#endif
>
{
private:
	//static_assert(always_false<Iterator>::value, "cpp17_iterator");

	template <typename Iter, typename = void>
	struct diff
	{
		//static_assert(always_false<Iter>::value, "cpp17_iterator::difference_type = void");
		using type = void;
	};

	template <typename Iter>
#if USE_CONCEPTS
	requires requires { typename bksge::incrementable_traits<Iter>::difference_type; }
#endif
	struct diff<Iter
#if !USE_CONCEPTS
		, bksge::void_t<typename bksge::incrementable_traits<Iter>::difference_type>
#endif
	>
	{
		//static_assert(always_false<Iter>::value, "cpp17_iterator::difference_type = incrementable_traits::difference_type");
		using type = typename bksge::incrementable_traits<Iter>::difference_type;
	};

public:
	using iterator_category = bksge::output_iterator_tag;
	using value_type	    = void;
	using difference_type   = typename diff<Iterator>::type;
	using pointer	        = void;
	using reference	        = void;
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_ITERATOR_CONCEPTS_DETAIL_ITERATOR_TRAITS_BASE_HPP
