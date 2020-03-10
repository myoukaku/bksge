/**
 *	@file	allocator.hpp
 *
 *	@brief	allocator を定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_MEMORY_ALLOCATOR_HPP
#define BKSGE_FND_MEMORY_ALLOCATOR_HPP

#if 1

#include <memory>

namespace bksge
{

using std::allocator;

}	// namespace bksge

#else

#include <bksge/fnd/memory/fwd/allocator_fwd.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/config.hpp>

// TODO
#include <bksge/fnd/utility/forward.hpp>

namespace bksge
{

BKSGE_WARNING_PUSH()
BKSGE_WARNING_DISABLE_MSVC(4100)	// 'p' : 引数は関数の本体部で 1 度も参照されません。

template <typename T>
class allocator
{
public:
	using value_type                             = T;
	using propagate_on_container_move_assignment = bksge::true_type;
	using is_always_equal                        = bksge::true_type;

	// TODO deprecated
	template <typename U>
	struct rebind
	{
		using other = allocator<U>;
	};

	allocator() BKSGE_NOEXCEPT
	{}

	template <typename U>
	allocator(allocator<U> const&) BKSGE_NOEXCEPT
	{}

	BKSGE_NODISCARD T*
	allocate(bksge::size_t n)
	{
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	// TODO deprecated
	BKSGE_NODISCARD T*
	allocate(bksge::size_t n, void const* /*hint*/)
	{
		return allocate(n);
	}

	void deallocate(T* p, bksge::size_t) BKSGE_NOEXCEPT
	{
		::operator delete(p);
	}

	// TODO deprecated
	template <typename U, typename... Args>
	void construct(U* p, Args&&... args)
	{
		::new((void*)p) U(bksge::forward<Args>(args)...);
	}

	// TODO deprecated
	void destroy(T* p)
	{
		p->~T();
	}
};

BKSGE_WARNING_POP()

template <typename T, typename U>
inline bool
operator==(allocator<T> const&, allocator<U> const&) BKSGE_NOEXCEPT
{
	return true;
}

template <typename T, typename U>
inline bool
operator!=(allocator<T> const&, allocator<U> const&) BKSGE_NOEXCEPT
{
	return false;
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_MEMORY_ALLOCATOR_HPP
