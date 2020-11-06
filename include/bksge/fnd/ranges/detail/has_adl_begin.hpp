/**
 *	@file	has_adl_begin.hpp
 *
 *	@brief	has_adl_begin の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_HAS_ADL_BEGIN_HPP
#define BKSGE_FND_RANGES_DETAIL_HAS_ADL_BEGIN_HPP

#include <bksge/fnd/ranges/detail/decay_copy.hpp>
#include <bksge/fnd/concepts/detail/class_or_enum.hpp>
#include <bksge/fnd/iterator/concepts/input_or_output_iterator.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/remove_reference.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if 0
void begin(auto&) = delete;
void begin(const auto&) = delete;
#else
template <typename T> void begin(T&) = delete;
template <typename T> void begin(const T&) = delete;
#endif

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_begin =
	bksge::detail::class_or_enum<bksge::remove_reference_t<T>> &&
	requires(T& t)
	{
		{ decay_copy(begin(t)) } -> bksge::input_or_output_iterator;
	};

#else

template <typename T>
struct has_adl_begin_impl
{
private:
	template <typename U,
		typename = bksge::enable_if_t<
			bksge::detail::class_or_enum<
				bksge::remove_reference_t<U>
			>::value>,
		typename B = decltype(decay_copy(begin(bksge::declval<U&>())))
	>
	static auto test(int) -> bksge::input_or_output_iterator<B>;

	template <typename U>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_begin = typename has_adl_begin_impl<T>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_HAS_ADL_BEGIN_HPP
