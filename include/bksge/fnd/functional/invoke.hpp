/**
 *	@file	invoke.hpp
 *
 *	@brief	invoke 関数の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_INVOKE_HPP
#define BKSGE_FND_FUNCTIONAL_INVOKE_HPP

#include <functional>

#if 0//defined(__cpp_lib_invoke) && (__cpp_lib_invoke >= 201411)

namespace bksge
{

using std::invoke;

}	// namespace bksge

#else

#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/functional/inl/invoke_inl.hpp>

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

namespace bksge
{

template <typename F, typename... Args>
inline BKSGE_CONSTEXPR auto
invoke(F&& f, Args&&... args)
	BKSGE_NOEXCEPT_DECLTYPE_RETURN(
		detail::invoke(bksge::forward<F>(f), bksge::forward<Args>(args)...))

}	// namespace bksge

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

#endif

#endif // BKSGE_FND_FUNCTIONAL_INVOKE_HPP
