/**
 *	@file	polynomial_ntt.hpp
 *
 *	@brief	polynomial_ntt の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_POLYNOMIAL_NTT_HPP
#define BKSGE_FND_BIGINT_DETAIL_POLYNOMIAL_NTT_HPP

#include <bksge/fnd/bigint/detail/modint.hpp>
#include <bksge/fnd/algorithm/copy.hpp>
#include <bksge/fnd/algorithm/fill.hpp>
#include <bksge/fnd/bit/bit_ceil.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <cstdint>
#include <utility>

namespace bksge
{

namespace detail
{

namespace bigint_algo
{

template <std::uint32_t Mod, std::uint32_t PrimRoot>
class polynomial_ntt
{
public:
	using modulo = modint<Mod>;

private:
	static void fourier_transform(bksge::vector<modulo> &v, bool inverse)
	{
		std::size_t s = v.size();
		for (std::size_t i = 0, j = 1; j < s - 1; ++j)
		{
			for (std::size_t k = s >> 1; k > (i ^= k); k >>= 1)
			{
				;
			}

			if (i < j)
			{
				using std::swap;
				swap(v[i], v[j]);
			}
		}

		std::size_t sc = 0, sz = 1;
		while (sz < s)
		{
			sz *= 2;
			++sc;
		}

		modulo root = modulo(PrimRoot).pow((Mod - 1) >> sc);
		bksge::vector<modulo> pw(s + 1);
		pw[0] = 1;
		for (std::size_t i = 1; i <= s; i++)
		{
			pw[i] = pw[i - 1] * root;
		}

		std::size_t qs = s;
		for (std::size_t b = 1; b < s; b <<= 1)
		{
			qs >>= 1;
			for (std::size_t i = 0; i < s; i += b * 2)
			{
				for (std::size_t j = i; j < i + b; ++j)
				{
					modulo delta = pw[(inverse ? b * 2 - j + i : j - i) * qs] * v[j + b];
					v[j + b] = v[j] - delta;
					v[j] += delta;
				}
			}
		}

		if (!inverse)
		{
			return;
		}

		modulo powinv = modulo((Mod + 1) / 2).pow(sc);
		for (std::size_t i = 0; i < s; ++i)
		{
			v[i] = v[i] * powinv;
		}
	}

public:
	static bksge::vector<modulo> convolve(bksge::vector<modulo> v1, bksge::vector<modulo> v2)
	{
		if(v1.empty() || v2.empty())
		{
			return bksge::vector<modulo>();
		}

		if(v1.size() < v2.size())
		{
			swap(v1, v2);
		}

		std::size_t const fsize = v1.size() + v2.size() - 1;
		std::size_t const step = bksge::bit_ceil(v2.size());

		v1.resize((v1.size() + step - 1) / step * step); // change v1.size() to multiple of step
		v2.resize(step * 2);
		bksge::vector<modulo> ans(fsize);
		bksge::vector<modulo> pv1(step * 2);
		fourier_transform(v2, false);
		for(std::size_t i = 0; i < v1.size(); i += step)
		{
			bksge::copy(v1.begin() + i, v1.begin() + i + step, pv1.begin());
			bksge::fill(pv1.begin() + step, pv1.end(), modulo(0));
			fourier_transform(pv1, false);
			for(std::size_t j = 0; j < step * 2; ++j)
			{
				pv1[j] *= v2[j];
			}

			fourier_transform(pv1, true);
			for(std::size_t j = 0; j < step * 2 && i + j < fsize; ++j)
			{
				ans[j + i] += pv1[j];
			}
		}

		return ans;
	}
};

}	// namespace bigint_algo

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_POLYNOMIAL_NTT_HPP
