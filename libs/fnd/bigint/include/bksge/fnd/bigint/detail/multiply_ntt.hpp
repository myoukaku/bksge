/**
 *	@file	multiply_ntt.hpp
 *
 *	@brief	multiply_ntt 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_MULTIPLY_NTT_HPP
#define BKSGE_FND_BIGINT_DETAIL_MULTIPLY_NTT_HPP

#include <bksge/fnd/bigint/detail/polynomial_ntt.hpp>
#include <bksge/fnd/bigint/detail/add.hpp>
#include <bksge/fnd/bigint/detail/construct_from_integral.hpp>
#include <bksge/fnd/bigint/detail/shift_left.hpp>
//#include <bksge/fnd/bigint/detail/remove_leading_zeros.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <cstdint>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <typename VectorType>
inline VectorType
multiply_ntt(VectorType const& lhs, VectorType const& rhs)
{
//	using ntt2 = polynomial_ntt<2013265921, 31>;//285838663483393
	using ntt1 = polynomial_ntt<2113929217, 5>;
	using ntt2 = polynomial_ntt<1811939329, 13>;
	const ntt2::modulo magic_mult = ntt2::modulo(ntt1::modulo::get_mod()).inv();

	bksge::vector<ntt1::modulo> nxtdigit1 = ntt1::convolve(
		bksge::vector<ntt1::modulo>(lhs.begin(), lhs.end()),
		bksge::vector<ntt1::modulo>(rhs.begin(), rhs.end()));
	bksge::vector<ntt2::modulo> nxtdigit2 = ntt2::convolve(
		bksge::vector<ntt2::modulo>(lhs.begin(), lhs.end()),
		bksge::vector<ntt2::modulo>(rhs.begin(), rhs.end()));
	auto const capacity = nxtdigit1.size();
	VectorType result{0};//(capacity);
	for (std::uint32_t i = 0; i < capacity; ++i)
	{
		std::uint64_t nxtdigit =
			std::uint64_t(ntt1::modulo::get_mod()) *
			((nxtdigit2[i] - nxtdigit1[i].get()) * magic_mult).get() +
			nxtdigit1[i].get();
		//using value_type = bksge::ranges::range_value_t<VectorType>;
		auto tmp = construct_from_integral<VectorType>(nxtdigit);
		add(result, bigint_algo::shift_left(tmp, i));
	}

//	carry_up<Radix>(result);
//	remove_leading_zeros(result);
	return result;
}

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_MULTIPLY_NTT_HPP
