/**
 *	@file	render_test_utility.hpp
 *
 *	@brief	Renderライブラリテスト用のユーティリティ
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_RENDER_RENDER_TEST_UTILITY_HPP
#define UNIT_TEST_RENDER_RENDER_TEST_UTILITY_HPP

#include <bksge/type_traits/is_arithmetic.hpp>
#include <bksge/cmath/abs.hpp>
#include <bksge/cstddef.hpp>
#include <bksge/iostream.hpp>

namespace
{

template <typename T, typename U>
bool IsNear(T const& x1, T const& x2, U error);

template <typename T, bool is_arithmetic = bksge::is_arithmetic<T>::value>
struct IsNearImpl
{
	template <typename U>
	static bool Invoke(T const& x1, T const& x2, U error)
	{
		return bksge::abs(x1 - x2) <= error;
	}
};

template <typename T>
struct IsNearImpl<T, false>
{
	template <typename U>
	static bool Invoke(T const& x1, T const& x2, U error)
	{
		for (bksge::size_t i = 0; i < T::Max(); ++i)
		{
			if (!IsNear(x1[i], x2[i], error))
			{
				bksge::cout << "lhs:" << x1 << bksge::endl;
				bksge::cout << "rhs:" << x2 << bksge::endl;
				return false;
			}
		}

		return true;
	}
};

template <typename T, typename U>
bool IsNear(T const& x1, T const& x2, U error)
{
	return IsNearImpl<T>::Invoke(x1, x2, error);
}

}	// namespace

#endif // UNIT_TEST_RENDER_RENDER_TEST_UTILITY_HPP
