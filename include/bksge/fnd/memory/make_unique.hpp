/**
 *	@file	make_unique.hpp
 *
 *	@brief	make_unique を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_MAKE_UNIQUE_HPP
#define BKSGE_FND_MEMORY_MAKE_UNIQUE_HPP

#include <memory>

#if defined(__cpp_lib_make_unique) && (__cpp_lib_make_unique >= 201304)

namespace bksge
{

using std::make_unique;

}	// namespace bksge

#else

#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/extent.hpp>
#include <bksge/fnd/type_traits/is_array.hpp>
#include <bksge/fnd/type_traits/remove_extent.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>

namespace bksge
{

template <typename T, typename... Types> inline
bksge::enable_if_t<!bksge::is_array<T>::value, bksge::unique_ptr<T>>
make_unique(Types&&... args)
{
	return bksge::unique_ptr<T>(new T(bksge::forward<Types>(args)...));
}

template <typename T> inline
bksge::enable_if_t<bksge::is_array<T>::value && bksge::extent<T>::value == 0, bksge::unique_ptr<T>>
make_unique(bksge::size_t size)
{
	using Elem = bksge::remove_extent_t<T>;
	return bksge::unique_ptr<T>(new Elem[size]());
}

template <typename T, typename... Types>
bksge::enable_if_t<bksge::extent<T>::value != 0, void>
make_unique(Types&&...) = delete;

}	// namespace bksge

#endif

#endif // BKSGE_FND_MEMORY_MAKE_UNIQUE_HPP
