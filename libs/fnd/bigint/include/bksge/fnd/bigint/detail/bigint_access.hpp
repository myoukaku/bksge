/**
 *	@file	bigint_access.hpp
 *
 *	@brief	bigint_access クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_BIGINT_ACCESS_HPP
#define BKSGE_FND_BIGINT_DETAIL_BIGINT_ACCESS_HPP

#include <bksge/fnd/string.hpp>
#include <cstddef>

namespace bksge
{

namespace detail
{

class bigint_access
{
public:
	template <typename BigInt>
	static constexpr int
	compare(BigInt const& lhs, BigInt const& rhs) noexcept
	{
		return lhs.compare(rhs);
	}

	template <typename CharT, typename BigInt>
	static bksge::basic_string<CharT>
	to_basic_string(BigInt const& val)
	{
		return val.template to_basic_string<CharT>();
	}

	template <typename BigInt>
	static BKSGE_CXX14_CONSTEXPR std::size_t
	hash(BigInt const& x) BKSGE_NOEXCEPT
	{
		return x.hash();
	}
};

}	// namespace detail

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_BIGINT_ACCESS_HPP
