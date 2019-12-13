/**
 *	@file	vector_value.hpp
 *
 *	@brief	VectorValue の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_MATH_DETAIL_VECTOR_VALUE_HPP
#define BKSGE_CORE_MATH_DETAIL_VECTOR_VALUE_HPP

#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace math
{

namespace detail
{

template <typename T, std::size_t N>
class VectorValue
{
public:
	using size_type              = std::size_t;
	using reference              = T&;
	using const_reference        = T const&;

	BKSGE_NODISCARD BKSGE_CXX14_CONSTEXPR reference
	operator[](size_type pos) BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return m_elems[pos];
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR const_reference
	operator[](size_type pos) const BKSGE_NOEXCEPT_OR_NOTHROW
	{
		return m_elems[pos];
	}

public:
	T	m_elems[N];
};

}	// namespace detail

}	// namespace math

}	// namespace bksge

#endif // BKSGE_CORE_MATH_DETAIL_VECTOR_VALUE_HPP
