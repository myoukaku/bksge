/**
 *	@file	range_adaptor_closure.hpp
 *
 *	@brief	range_adaptor_closure の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_DETAIL_RANGE_ADAPTOR_CLOSURE_HPP
#define BKSGE_FND_RANGES_VIEWS_DETAIL_RANGE_ADAPTOR_CLOSURE_HPP

#include <bksge/fnd/ranges/views/detail/range_adaptor.hpp>
#include <bksge/fnd/ranges/concepts/viewable_range.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

namespace views
{

namespace detail
{

template <typename Callable>
struct range_adaptor_closure : public range_adaptor<Callable>
{
	using range_adaptor<Callable>::range_adaptor;

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <ranges::viewable_range Range>
	requires requires { std::declval<Callable>()(std::declval<Range>()); }
#else
	template <typename Range,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::viewable_range<Range>
		>::value>,
		typename = decltype(std::declval<Callable>()(std::declval<Range>()))
	>
#endif
	constexpr auto operator()(Range&& r) const
	->decltype(this->get_callable()(bksge::forward<Range>(r)))
	{
		return this->get_callable()(bksge::forward<Range>(r));
	}

#if defined(BKSGE_HAS_CXX20_CONCEPTS)
	template <ranges::viewable_range Range>
	requires requires { std::declval<Callable>()(std::declval<Range>()); }
#else
	template <typename Range,
		typename = bksge::enable_if_t<bksge::conjunction<
			ranges::viewable_range<Range>
		>::value>,
		typename = decltype(std::declval<Callable>()(std::declval<Range>()))
	>
#endif
	friend constexpr auto
	operator|(Range&& r, const range_adaptor_closure& o)
	->decltype(o(bksge::forward<Range>(r)))
	{
		return o(bksge::forward<Range>(r));
	}

private:
	template <typename T1, typename T2, bool, bool>
	struct ClosureTImpl;

	template <typename T1, typename T2>
	struct ClosureTImpl<T1, T2, true, true>
	{
		constexpr ClosureTImpl(T1 const&, T2 const&)
		{}

		template <typename U>
		constexpr auto operator()(U&& e) const
		->decltype(bksge::forward<U>(e) | T1{} | T2{})
		{
			return bksge::forward<U>(e) | T1{} | T2{};
		};
	};

	template <typename T1, typename T2>
	struct ClosureTImpl<T1, T2, true, false>
	{
		T2 const& m_y;

		constexpr ClosureTImpl(T1 const&, T2 const& y)
			: m_y(y)
		{}

		template <typename U>
		constexpr auto operator()(U&& e) const
		->decltype(bksge::forward<U>(e) | T1{} | m_y)
		{
			return bksge::forward<U>(e) | T1{} | m_y;
		};
	};

	template <typename T1, typename T2>
	struct ClosureTImpl<T1, T2, false, true>
	{
		T1 const& m_x;

		constexpr ClosureTImpl(T1 const& x, T2 const&)
			: m_x(x)
		{}

		template <typename U>
		constexpr auto operator()(U&& e) const
		->decltype(bksge::forward<U>(e) | m_x | T2{})
		{
			return bksge::forward<U>(e) | m_x | T2{};
		};
	};

	template <typename T1, typename T2>
	struct ClosureTImpl<T1, T2, false, false>
	{
		T1 const& m_x;
		T2 const& m_y;

		constexpr ClosureTImpl(T1 const& x, T2 const& y)
			: m_x(x)
			, m_y(y)
		{}

		template <typename U>
		constexpr auto operator()(U&& e) const
		->decltype(bksge::forward<U>(e) | m_x | m_y)
		{
			return bksge::forward<U>(e) | m_x | m_y;
		};
	};

	template <typename T1, typename T2>
	using ClosureT = ClosureTImpl<
		range_adaptor_closure<T1>,
		range_adaptor_closure<T2>,
		bksge::is_default_constructible<T1>::value,
		bksge::is_default_constructible<T2>::value
	>;

public:
	template <typename T>
	friend constexpr auto operator|(
		range_adaptor_closure<T> const& x,
		range_adaptor_closure<Callable> const& y)
	-> range_adaptor_closure<ClosureT<T, Callable>>
	{
		using closure_t = ClosureT<T, Callable>;
		return range_adaptor_closure<closure_t>(closure_t{x, y});
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Callable>
range_adaptor_closure(Callable) -> range_adaptor_closure<Callable>;

#endif

}	// namespace detail

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_DETAIL_RANGE_ADAPTOR_CLOSURE_HPP
