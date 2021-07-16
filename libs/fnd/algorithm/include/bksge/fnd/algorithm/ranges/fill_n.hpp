/**
 *	@file	fill_n.hpp
 *
 *	@brief	ranges::fill_n の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_ALGORITHM_RANGES_FILL_N_HPP
#define BKSGE_FND_ALGORITHM_RANGES_FILL_N_HPP

#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/iterator/concepts/output_iterator.hpp>
#include <bksge/fnd/iterator/iter_difference_t.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_scalar.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

namespace ranges
{

struct fill_n_fn
{
private:
	//// TODO: Generalize this optimization to contiguous iterators.
	//if constexpr (is_pointer_v<Out>
	//	// Note that __is_byte already implies !is_volatile.
	//	&& __is_byte<remove_pointer_t<Out>>::value
	//	&& integral<T>)
	//{
	//	__builtin_memset(first, static_cast<unsigned char>(value), n);
	//	return first + n;
	//}

	template <typename T, typename Out, typename Difference,
		typename = bksge::enable_if_t<bksge::is_scalar<T>::value>>
	static BKSGE_CXX14_CONSTEXPR Out
	impl(Out first, Difference n, T const& value,
		bksge::detail::overload_priority<1>)
	{
		auto const tmp = value;
		for (; n > 0; --n, (void)++first)
		{
			*first = tmp;
		}

		return first;
	}

	template <typename T, typename Out, typename Difference>
	static BKSGE_CXX14_CONSTEXPR Out
	impl(Out first, Difference n, T const& value,
		bksge::detail::overload_priority<0>)
	{
		for (; n > 0; --n, (void)++first)
		{
			*first = value;
		}

		return first;
	}

public:
	template <
		typename T,
		BKSGE_REQUIRES_PARAM_2(bksge::output_iterator, T const&, Out)
	>
	BKSGE_CXX14_CONSTEXPR Out operator()(
		Out first, bksge::iter_difference_t<Out> n, T const& value) const
	{
		if (n <= 0)
		{
			return first;
		}

		return impl(
			std::move(first),
			std::move(n),
			value,
			bksge::detail::overload_priority<1>{});
	}
};

inline namespace cpo
{

BKSGE_INLINE_VAR BKSGE_CONSTEXPR fill_n_fn fill_n{};

}	// inline namespace cpo

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_ALGORITHM_RANGES_FILL_N_HPP
