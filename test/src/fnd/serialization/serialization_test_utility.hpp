/**
 *	@file	serialization_test_utility.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

#ifndef UNIT_TEST_FND_SERIALIZATION_SERIALIZATION_TEST_UTILITY_HPP
#define UNIT_TEST_FND_SERIALIZATION_SERIALIZATION_TEST_UTILITY_HPP

#include <limits>
#include <random>

namespace
{

inline std::mt19937& get_random_engine()
{
	static std::mt19937 mt;
	return mt;
}

template <typename T>
inline T get_random_int(T min, T max)
{
	std::uniform_int_distribution<T> dist(min, max);
	return dist(get_random_engine());
}

template <typename T>
inline T get_random_int()
{
	return get_random_int(
		std::numeric_limits<T>::min(),
		std::numeric_limits<T>::max());
}

template <typename T>
inline T get_random_float()
{
	std::uniform_real_distribution<T> dist(
		std::numeric_limits<T>::lowest() / 2,
		std::numeric_limits<T>::max() / 2);
	return dist(get_random_engine());
}

inline bool get_random_bool()
{
	return get_random_int<unsigned int>() % 2 == 0;
}

}	// namespace

#endif // UNIT_TEST_FND_SERIALIZATION_SERIALIZATION_TEST_UTILITY_HPP
