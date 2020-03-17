/**
 *	@file	constexpr_array.hpp
 *
 *	@brief	constexpr_array の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_CONSTEXPR_ARRAY_HPP
#define BKSGE_FND_VARIANT_DETAIL_CONSTEXPR_ARRAY_HPP

#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

template <typename T, std::size_t N>
class constexpr_array
{
public:
    using size_type       = std::size_t;
    using reference       = T&;
    using const_reference = T const&;

	T m_elems[N];

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reference
	operator[](size_type i) BKSGE_NOEXCEPT
	{
		return m_elems[i];
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reference
	operator[](size_type i) const BKSGE_NOEXCEPT
	{
		return m_elems[i];
	}
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_CONSTEXPR_ARRAY_HPP
