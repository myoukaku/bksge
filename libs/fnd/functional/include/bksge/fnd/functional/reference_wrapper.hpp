/**
 *	@file	reference_wrapper.hpp
 *
 *	@brief	reference_wrapper クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_REFERENCE_WRAPPER_HPP
#define BKSGE_FND_FUNCTIONAL_REFERENCE_WRAPPER_HPP

#include <bksge/fnd/functional/fwd/reference_wrapper_fwd.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/invoke_result.hpp>
#include <bksge/fnd/type_traits/is_object.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/config.hpp>
#include <utility>

namespace bksge
{

template <typename T>
class reference_wrapper
{
private:
	BKSGE_CONSTEXPR
	static T* FUN(T& r) BKSGE_NOEXCEPT { return bksge::addressof(r); }

	static void FUN(T&&) = delete;

public:
	using type = T;

	template <
		typename U,
		typename = bksge::enable_if_t<
			!bksge::is_same<reference_wrapper, bksge::remove_cvref_t<U>>::value
		>,
		typename = decltype(reference_wrapper::FUN(std::declval<U>()))
	>
	BKSGE_CONSTEXPR
	reference_wrapper(U&& u)
		BKSGE_NOEXCEPT_IF_EXPR(reference_wrapper::FUN(std::declval<U>()))
		: m_ptr(reference_wrapper::FUN(std::forward<U>(u)))
	{}

	BKSGE_CONSTEXPR
	reference_wrapper(reference_wrapper const&) = default;

	BKSGE_CXX14_CONSTEXPR reference_wrapper&
	operator=(reference_wrapper const&) = default;

	BKSGE_CONSTEXPR operator T& () const BKSGE_NOEXCEPT
	{
		return this->get();
	}

	BKSGE_CONSTEXPR T& get() const BKSGE_NOEXCEPT
	{
		return *m_ptr;
	}

	template <typename... Args>
	BKSGE_CONSTEXPR bksge::invoke_result_t<T&, Args...>
	operator()(Args&&... args) const
	{
#if defined(BKSGE_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (bksge::is_object<type>::value)
		{
			static_assert(sizeof(type), "type must be complete");
		}
#endif
		return bksge::invoke(get(), std::forward<Args>(args)...);
	}

private:
	T* m_ptr;
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <typename T>
reference_wrapper(T&) -> reference_wrapper<T>;

#endif

}	// namespace bksge

#endif // BKSGE_FND_FUNCTIONAL_REFERENCE_WRAPPER_HPP
