/**
 *	@file	not_fn.hpp
 *
 *	@brief	not_fn 関数テンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_NOT_FN_HPP
#define BKSGE_FND_FUNCTIONAL_NOT_FN_HPP

#include <functional>

#if defined(__cpp_lib_not_fn) && (__cpp_lib_not_fn >= 201603)

namespace bksge
{

using std::not_fn;

}	// namespace bksge

#else

 #include <bksge/fnd/functional/invoke.hpp>
 #include <bksge/fnd/type_traits/decay.hpp>
 #include <bksge/fnd/type_traits/enable_if.hpp>
 #include <bksge/fnd/type_traits/is_same.hpp>
 #include <bksge/fnd/type_traits/is_constructible.hpp>
 #include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
 #include <bksge/fnd/utility/forward.hpp>
 #include <bksge/fnd/utility/move.hpp>
 #include <bksge/fnd/config.hpp>

namespace bksge
{

namespace detail
{

#define BKSGE_NOEXCEPT_DECLTYPE_RETURN(...) \
	BKSGE_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

template <typename F>
class not_fn_imp
{
private:
	bksge::decay_t<F> m_fd;

public:
	not_fn_imp() = delete;

	template <typename... Args>
	auto operator()(Args&&... args) &
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			!bksge::invoke(m_fd, bksge::forward<Args>(args)...))

	template <typename... Args>
	auto operator()(Args&&... args) &&
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			!bksge::invoke(bksge::move(m_fd), bksge::forward<Args>(args)...))

	template <typename... Args>
	auto operator()(Args&&... args) const&
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			!bksge::invoke(m_fd, bksge::forward<Args>(args)...))

	template <typename... Args>
	auto operator()(Args&&... args) const&&
		BKSGE_NOEXCEPT_DECLTYPE_RETURN(
			!bksge::invoke(bksge::move(m_fd), bksge::forward<Args>(args)...))

	template <
		typename F2,
		typename = bksge::enable_if_t<
			!bksge::is_same<bksge::decay_t<F2>, not_fn_imp>::value
		>
	>
	explicit not_fn_imp(F2&& fn)
		: m_fd(bksge::forward<F2>(fn)) {}
};

#undef BKSGE_NOEXCEPT_DECLTYPE_RETURN

}	// namespace detail

template <
	typename F,
	typename = bksge::enable_if_t<
		bksge::is_constructible<bksge::decay_t<F>, F>::value
	>
>
inline detail::not_fn_imp<F>
not_fn(F&& fn)
BKSGE_NOEXCEPT_IF((
	bksge::is_nothrow_constructible<bksge::decay_t<F>, F&&>::value))
{
	return detail::not_fn_imp<F>(bksge::forward<F>(fn));
}

}	// namespace bksge

#endif

#endif // BKSGE_FND_FUNCTIONAL_NOT_FN_HPP
