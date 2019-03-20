/**
 *	@file	make_unique.hpp
 *
 *	@brief	make_unique を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_MEMORY_MAKE_UNIQUE_HPP
#define BKSGE_MEMORY_MAKE_UNIQUE_HPP

#include <memory>

#if defined(__cpp_lib_make_unique) && (__cpp_lib_make_unique >= 201304)

namespace bksge
{

using std::make_unique;

}	// namespace bksge

#else

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

namespace bksge
{

template <typename T, typename... Types> inline
typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
make_unique(Types&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Types>(args)...));
}

template <typename T> inline
typename std::enable_if<std::is_array<T>::value && std::extent<T>::value == 0, std::unique_ptr<T>>::type
make_unique(std::size_t size)
{
	using Elem = typename std::remove_extent<T>::type;
	return std::unique_ptr<T>(new Elem[size]());
}

template <typename T, typename... Types>
typename std::enable_if<std::extent<T>::value != 0, void>::type
make_unique(Types&&...) = delete;

}	// namespace bksge

#endif

#endif // BKSGE_MEMORY_MAKE_UNIQUE_HPP
