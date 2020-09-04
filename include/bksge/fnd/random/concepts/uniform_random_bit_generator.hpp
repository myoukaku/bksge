/**
 *	@file	uniform_random_bit_generator.hpp
 *
 *	@brief	uniform_random_bit_generator の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANDOM_CONCEPTS_UNIFORM_RANDOM_BIT_GENERATOR_HPP
#define BKSGE_FND_RANDOM_CONCEPTS_UNIFORM_RANDOM_BIT_GENERATOR_HPP

#include <bksge/fnd/concepts/invocable.hpp>
#include <bksge/fnd/concepts/unsigned_integral.hpp>
#include <bksge/fnd/concepts/same_as.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Gen>
concept uniform_random_bit_generator =
	bksge::invocable<Gen&> &&
	bksge::unsigned_integral<bksge::invoke_result_t<Gen&>> &&
	requires
	{
		{ Gen::min() } -> bksge::same_as<bksge::invoke_result_t<Gen&>>;
		{ Gen::max() } -> bksge::same_as<bksge::invoke_result_t<Gen&>>;
		requires bksge::bool_constant<(Gen::min() < Gen::max())>::value;
	};

#else

template <typename Gen>
struct uniform_random_bit_generator_impl
{
private:
	template <typename G>
	static auto test(int) -> bksge::conjunction<
		bksge::invocable<G&>,
		bksge::unsigned_integral<bksge::invoke_result_t<G&>>,
		bksge::same_as<decltype(G::min()), bksge::invoke_result_t<G&>>,
		bksge::same_as<decltype(G::max()), bksge::invoke_result_t<G&>>,
		bksge::bool_constant<(G::min() < G::max())>
	>;

	template <typename G>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Gen>(0));
};

template <typename Gen>
using uniform_random_bit_generator =
	typename uniform_random_bit_generator_impl<Gen>::type;

#endif

}	// namespace bksge

#endif // BKSGE_FND_RANDOM_CONCEPTS_UNIFORM_RANDOM_BIT_GENERATOR_HPP
