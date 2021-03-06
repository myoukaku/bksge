﻿/**
 *	@file	iota_inl.hpp
 *
 *	@brief	iota の実装
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_NUMERIC_INL_IOTA_INL_HPP
#define BKSGE_FND_NUMERIC_INL_IOTA_INL_HPP

#include <bksge/fnd/numeric/iota.hpp>

namespace bksge
{

template <typename ForwardIterator, typename T>
inline BKSGE_CXX14_CONSTEXPR void
iota(ForwardIterator first, ForwardIterator last, T value)
{
	for (; first != last; ++first)
	{
		*first = value;
		++value;
	}
}

}	// namespace bksge

#endif // BKSGE_FND_NUMERIC_INL_IOTA_INL_HPP
