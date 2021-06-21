/**
 *	@file	xorshift_base.hpp
 *
 *	@brief	xorshift_base の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANDOM_ENGINES_DETAIL_XORSHIFT_BASE_HPP
#define BKSGE_FND_RANDOM_ENGINES_DETAIL_XORSHIFT_BASE_HPP

#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/random/engines/detail/split_mix64.hpp>
#include <bksge/fnd/ios/flags_saver.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>
#include <bksge/fnd/config.hpp>
#include <limits>
#include <istream>

namespace bksge
{

template <typename UIntType, bksge::size_t N, typename Derived>
class xorshift_base
{
public:
	using result_type = UIntType;

	static BKSGE_CONSTEXPR result_type const default_seed = 2463534242UL;

	static BKSGE_CONSTEXPR result_type min() { return std::numeric_limits<result_type>::min(); }
	static BKSGE_CONSTEXPR result_type max() { return std::numeric_limits<result_type>::max(); }

	explicit xorshift_base(result_type sd = default_seed)
	{
		seed(sd);
	}

	template <typename Sseq>
	explicit xorshift_base(Sseq& q)
	{
		seed(q);
	}

	void seed(result_type sd = default_seed)
	{
		split_mix64 sm(sd);

		for (bksge::size_t i = 0; i < N; ++i)
		{
			m_state[i] = static_cast<result_type>(sm());
		}
	}

	template <typename Sseq>
	void seed(Sseq& q)
	{
		typename Sseq::result_type ar[N];
		q.generate(ar, ar + N);
		for (bksge::size_t i = 0; i < N; ++i)
		{
			m_state[i] = ar[i];
		}
	}

	void discard(unsigned long long z)
	{
		auto derived = static_cast<Derived*>(this);
		for (; z; --z)
		{
			derived->operator()();
		}
	}

	bool operator==(xorshift_base const& rhs) const
	{
		for (bksge::size_t i = 0; i < N; ++i)
		{
			if (m_state[i] != rhs.m_state[i])
			{
				return false;
			}
		}
		return true;
	}

	bool operator!=(xorshift_base const& rhs) const
	{
		return !(*this == rhs);
	}

protected:
	result_type m_state[N];

private:
	template <
		typename CharT, typename Traits,
		typename U, bksge::size_t M, typename D
	>
	friend bksge::basic_ostream<CharT, Traits>&
	operator<<(
		bksge::basic_ostream<CharT, Traits>& os,
		xorshift_base<U, M, D> const& e);

	template <
		typename CharT, typename Traits,
		typename U, bksge::size_t M, typename D
	>
	friend std::basic_istream<CharT, Traits>&
	operator>>(
		std::basic_istream<CharT, Traits>& is,
		xorshift_base<U, M, D>& e);
};

template <
	typename CharT, typename Traits,
	typename UIntType, bksge::size_t N, typename Derived
>
inline bksge::basic_ostream<CharT, Traits>&
operator<<(
	bksge::basic_ostream<CharT, Traits>& os,
	xorshift_base<UIntType, N, Derived> const& e)
{
	bksge::ios::flags_saver lx(os);
	os.flags(
		std::ios_base::dec |
		std::ios_base::left |
		std::ios_base::fixed |
		std::ios_base::scientific);
	CharT sp = os.widen(' ');

	for (bksge::size_t i = 0; i < N; ++i)
	{
		os << sp << e.m_state[i];
	}

	return os;
}

template <
	typename CharT, typename Traits,
	typename UIntType, bksge::size_t N, typename Derived
>
inline std::basic_istream<CharT, Traits>&
operator>>(
	std::basic_istream<CharT, Traits>& is,
	xorshift_base<UIntType, N, Derived>& e)
{
	bksge::ios::flags_saver lx(is);
	is.flags(
		std::ios_base::dec |
		std::ios_base::skipws |
		std::ios_base::fixed |
		std::ios_base::scientific);

	UIntType tbl[N];
	for (bksge::size_t i = 0; i < N; ++i)
	{
		is >> tbl[i];
	}

	if (!is.fail())
	{
		for (bksge::size_t i = 0; i < N; ++i)
		{
			e.m_state[i] = tbl[i];
		}
	}

	return is;
}

}	// namespace bksge

#endif // BKSGE_FND_RANDOM_ENGINES_DETAIL_XORSHIFT_BASE_HPP
