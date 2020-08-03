/**
 *	@file	view_interface.hpp
 *
 *	@brief	ranges::view_interface の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEW_INTERFACE_HPP
#define BKSGE_FND_RANGES_VIEW_INTERFACE_HPP

#include <bksge/fnd/ranges/begin.hpp>
#include <bksge/fnd/ranges/empty.hpp>
#include <bksge/fnd/ranges/end.hpp>
#include <bksge/fnd/ranges/iterator_t.hpp>
#include <bksge/fnd/ranges/range_difference_t.hpp>
#include <bksge/fnd/ranges/sentinel_t.hpp>
#include <bksge/fnd/ranges/view_base.hpp>
#include <bksge/fnd/ranges/concepts/bidirectional_range.hpp>
#include <bksge/fnd/ranges/concepts/common_range.hpp>
#include <bksge/fnd/ranges/concepts/forward_range.hpp>
#include <bksge/fnd/ranges/concepts/random_access_range.hpp>
#include <bksge/fnd/ranges/concepts/range.hpp>
#include <bksge/fnd/ranges/concepts/view.hpp>
#include <bksge/fnd/concepts/derived_from.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/iterator/prev.hpp>
#include <bksge/fnd/iterator/concepts/contiguous_iterator.hpp>
#include <bksge/fnd/iterator/concepts/sized_sentinel_for.hpp>
#include <bksge/fnd/memory/to_address.hpp>
#include <bksge/fnd/type_traits/is_class.hpp>
#include <bksge/fnd/type_traits/remove_cv.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>

namespace bksge
{

namespace ranges
{

template <
	typename Derived
#if !defined(BKSGE_HAS_CXX20_CONCEPTS)
	, typename = bksge::enable_if_t<
		bksge::is_class<Derived>::value && bksge::same_as<Derived, bksge::remove_cv_t<Derived>>::value
	>
#endif
>
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
requires bksge::is_class<Derived>::value && bksge::same_as<Derived, bksge::remove_cv_t<Derived>>
#endif
class view_interface : public view_base
{
private:
	template <typename D>
	BKSGE_CXX14_CONSTEXPR D& derived() noexcept
	{
		static_assert(bksge::is_derived_from<bksge::remove_cv_t<D>, view_interface<Derived>>::value, "");
		static_assert(ranges::is_view<bksge::remove_cv_t<D>>::value, "");
		return static_cast<D&>(*this);
	}

	template <typename D>
	BKSGE_CXX14_CONSTEXPR D& derived() const noexcept
	{
		static_assert(bksge::is_derived_from<bksge::remove_cv_t<D>, view_interface<Derived>>::value, "");
		static_assert(ranges::is_view<bksge::remove_cv_t<D>>::value, "");
		return static_cast<D&>(*this);
	}

public:
	template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, D, Derived)>
	BKSGE_CXX14_CONSTEXPR bool empty()
	{
		return ranges::begin(derived<D>()) == ranges::end(derived<D>());
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, D, Derived const)>
	BKSGE_CXX14_CONSTEXPR bool empty() const
	{
		return ranges::begin(derived<D>()) == ranges::end(derived<D>());
	}

	template <typename D = Derived>
	BKSGE_CXX14_CONSTEXPR explicit operator bool()
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		requires requires { ranges::empty(derived<D>()); }
#endif
	{
		return !ranges::empty(derived<D>());
	}

	template <typename D = Derived const>
	BKSGE_CXX14_CONSTEXPR explicit operator bool() const
#if defined(BKSGE_HAS_CXX20_CONCEPTS)
		requires requires { ranges::empty(derived<D>()); }
#endif
	{
		return !ranges::empty(derived<D>());
	}

	template <typename D = Derived>
		BKSGE_REQUIRES(bksge::contiguous_iterator<ranges::iterator_t<D>>)
	BKSGE_CXX14_CONSTEXPR auto data()
	->decltype(bksge::to_address(ranges::begin(derived<D>())))
	{
		return bksge::to_address(ranges::begin(derived<D>()));
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::range, D, Derived const)>
		BKSGE_REQUIRES(bksge::contiguous_iterator<ranges::iterator_t<D>>)
	BKSGE_CXX14_CONSTEXPR auto data() const
	->decltype(bksge::to_address(ranges::begin(derived<D>())))
	{
		return bksge::to_address(ranges::begin(derived<D>()));
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, D, Derived)>
		BKSGE_REQUIRES(bksge::sized_sentinel_for<ranges::sentinel_t<D>, ranges::iterator_t<D>>)
	BKSGE_CXX14_CONSTEXPR auto size()
	->decltype(ranges::end(derived<D>()) - ranges::begin(derived<D>()))
	{
		return ranges::end(derived<D>()) - ranges::begin(derived<D>());
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, D, Derived const)>
		BKSGE_REQUIRES(bksge::sized_sentinel_for<ranges::sentinel_t<D>, ranges::iterator_t<D>>)
	BKSGE_CXX14_CONSTEXPR auto size() const
	->decltype(ranges::end(derived<D>()) - ranges::begin(derived<D>()))
	{
		return ranges::end(derived<D>()) - ranges::begin(derived<D>());
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, D, Derived)>
	BKSGE_CXX14_CONSTEXPR auto front()
	->decltype((*ranges::begin(derived<D>())))
	{
		BKSGE_ASSERT(!empty());
		return *ranges::begin(derived<D>());
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::forward_range, D, Derived const)>
	BKSGE_CXX14_CONSTEXPR auto front() const
	->decltype((*ranges::begin(derived<D>())))
	{
		BKSGE_ASSERT(!empty());
		return *ranges::begin(derived<D>());
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::bidirectional_range, D, Derived)>
		BKSGE_REQUIRES(ranges::common_range<D>)
	BKSGE_CXX14_CONSTEXPR auto back()
	->decltype((*ranges::prev(ranges::end(derived<D>()))))
	{
		BKSGE_ASSERT(!empty());
		return *ranges::prev(ranges::end(derived<D>()));
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::bidirectional_range, D, Derived const)>
		BKSGE_REQUIRES(ranges::common_range<D>)
	BKSGE_CXX14_CONSTEXPR auto back() const
	->decltype((*ranges::prev(ranges::end(derived<D>()))))
	{
		BKSGE_ASSERT(!empty());
		return *ranges::prev(ranges::end(derived<D>()));
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, D, Derived)>
	BKSGE_CXX14_CONSTEXPR auto
		operator[](ranges::range_difference_t<D> n)
	->decltype((ranges::begin(derived<D>())[n]))
	{
		return ranges::begin(derived<D>())[n];
	}

	template <BKSGE_REQUIRES_PARAM_D(ranges::random_access_range, D, Derived const)>
	BKSGE_CXX14_CONSTEXPR auto
		operator[](ranges::range_difference_t<D> n) const
	->decltype((ranges::begin(derived<D>())[n]))
	{
		return ranges::begin(derived<D>())[n];
	}
};

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEW_INTERFACE_HPP
