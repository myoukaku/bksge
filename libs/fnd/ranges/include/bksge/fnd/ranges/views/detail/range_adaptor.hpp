/**
 *	@file	range_adaptor.hpp
 *
 *	@brief	range_adaptor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_VIEWS_DETAIL_RANGE_ADAPTOR_HPP
#define BKSGE_FND_RANGES_VIEWS_DETAIL_RANGE_ADAPTOR_HPP

#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/type_traits/is_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_invocable.hpp>
#include <bksge/fnd/type_traits/unwrap_reference.hpp>
#include <bksge/fnd/type_traits/remove_const.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/functional/reference_wrapper.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace views
{

namespace detail
{

struct Empty {};

template <typename T>
inline constexpr bksge::reference_wrapper<T>
maybe_refwrap(T& arg)
{
	return bksge::reference_wrapper<T>{arg};
}

template <typename T>
inline constexpr bksge::reference_wrapper<T const>
maybe_refwrap(T const& arg)
{
	return bksge::reference_wrapper<T const>{arg};
}

template <typename T>
inline constexpr auto
maybe_refwrap(T&& arg)
->decltype((bksge::forward<T>(arg)))
{
	return bksge::forward<T>(arg);
}

template <typename Callable>
struct range_adaptor_closure;

template <typename Callable>
struct range_adaptor_base
{
private:
	template <typename C, typename... Args>
	struct ClosureT;

	template <typename C, typename Arg0, typename... Args>
	struct ClosureT<C, Arg0, Args...> : public ClosureT<C, Args...>
	{
		using BaseT = ClosureT<C, Args...>;

		decltype(maybe_refwrap(bksge::declval<Arg0>()))	m_ref;

		constexpr ClosureT(Arg0&& arg0, Args&&... args)
			: BaseT(bksge::forward<Args>(args)...)
			, m_ref(maybe_refwrap(bksge::forward<Arg0>(arg0)))
		{}

		template <typename Range, typename... Ts>
		constexpr auto operator()(Range&& r, Ts&&... ts) const
		->decltype(BaseT::operator()(
				bksge::forward<Range>(r),
				bksge::forward<Ts>(ts)...,
				static_cast<bksge::unwrap_reference_t<bksge::remove_const_t<decltype(m_ref)>>>(m_ref)))
		{
			return BaseT::operator()(
				bksge::forward<Range>(r),
				bksge::forward<Ts>(ts)...,
				// This static_cast has two purposes: it forwards a
				// bksge::reference_wrapper<T> capture as a T&, and otherwise
				// forwards the captured argument as an rvalue.
				static_cast<bksge::unwrap_reference_t<bksge::remove_const_t<decltype(m_ref)>>>(m_ref));
		}
	};

	template <typename C>
	struct ClosureT<C>
	{
		template <typename Range, typename... Ts>
		constexpr auto operator()(Range&& r, Ts&&... ts) const
		-> bksge::invoke_result_t<C, Range, Ts...>
		{
			return C{}(bksge::forward<Range>(r), bksge::forward<Ts>(ts)...);
		}
	};

	// [range.adaptor.object]: If a range adaptor object accepts more
	// than one argument, then the following expressions are equivalent:
	//
	//   (1) adaptor(range, args...)
	//   (2) adaptor(args...)(range)
	//   (3) range | adaptor(args...)
	//
	// In this case, adaptor(args...) is a range adaptor closure object.
	//
	// We handle (1) and (2) here, and (3) is just a special case of a
	// more general case already handled by range_adaptor_closure.
	template <typename... Args, typename = bksge::enable_if_t<bksge::is_invocable<Callable, Args...>::value>>
	static constexpr auto impl(bksge::detail::overload_priority<1>, Args&&... args)
	-> bksge::invoke_result_t<Callable, Args...>
	{
		static_assert(sizeof...(Args) != 1,
			"a range_adaptor that accepts only one argument "
			"should be defined as a range_adaptor_closure");
		// Here we handle adaptor(range, args...) -- just forward all
		// arguments to the underlying adaptor routine.
		return Callable{}(bksge::forward<Args>(args)...);
	}

	// Here we handle adaptor(args...)(range).
	// Given args..., we return a range_adaptor_closure that takes a
	// range argument, such that (2) is equivalent to (1).
	//
	// We need to be careful about how we capture args... in this
	// closure.  By using maybe_refwrap, we capture lvalue
	// references by reference (through a bksge::reference_wrapper) and
	// otherwise capture by value.
	template <typename... Args, typename ClosureType = ClosureT<Callable, Args...>>
	static constexpr auto impl(bksge::detail::overload_priority<0>, Args&&... args)
	-> range_adaptor_closure<ClosureType>
	{
		return range_adaptor_closure<ClosureType>(ClosureType(bksge::forward<Args>(args)...));
	}

public:
	template <typename Arg0, typename... Args>
	constexpr auto operator()(Arg0&& arg0, Args&&... args) const
	->decltype(impl(
			bksge::detail::overload_priority<1>{},
			bksge::forward<Arg0>(arg0),
			bksge::forward<Args>(args)...))
	{
		return impl(
			bksge::detail::overload_priority<1>{},
			bksge::forward<Arg0>(arg0),
			bksge::forward<Args>(args)...);
	}
};

template <typename Callable, bool = bksge::is_default_constructible<Callable>::value>
struct range_adaptor
	: public range_adaptor_base<Callable>
{
private:
	Callable	m_callable;

protected:
	constexpr Callable const& get_callable() const
	{
		return m_callable;
	}

public:
	constexpr range_adaptor(Callable callable)
		: m_callable(bksge::move(callable))
	{}
};

template <typename Callable>
struct range_adaptor<Callable, true>
	: public range_adaptor_base<Callable>
{
protected:
	constexpr Callable get_callable() const
	{
		return Callable{};
	}

public:
	constexpr range_adaptor(Callable const& = {})
	{}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename Callable>
range_adaptor(Callable) -> range_adaptor<Callable>;

#endif

}	// namespace detail

}	// namespace views

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_VIEWS_DETAIL_RANGE_ADAPTOR_HPP
