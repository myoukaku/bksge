/**
 *	@file	hash_facade.hpp
 *
 *	@brief	hash_facadeクラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_HASH_FUNCTIONS_HASH_FACADE_HPP
#define BKSGE_FND_HASH_FUNCTIONS_HASH_FACADE_HPP

#include <bksge/fnd/iterator/begin.hpp>
#include <bksge/fnd/iterator/end.hpp>
#include <bksge/fnd/cstring/strlen.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

/**
 *	@brief	hash_facade
 */
template <typename Hasher, typename ResultType>
class hash_facade
{
public:
	using result_type = ResultType;

	template <typename Iterator>
	BKSGE_CONSTEXPR result_type
	operator()(Iterator first, Iterator last) const
	{
		return derived().invoke(first, last);
	}

	BKSGE_CXX14_CONSTEXPR result_type
	operator()(char const* ptr) const
	{
		return operator()(ptr, ptr + bksge::strlen(ptr));
	}

	BKSGE_CXX14_CONSTEXPR result_type
	operator()(wchar_t const* ptr) const
	{
		return operator()(ptr, ptr + bksge::strlen(ptr));
	}

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
	BKSGE_CXX14_CONSTEXPR result_type
	operator()(char8_t const* ptr) const
	{
		return operator()(ptr, ptr + bksge::strlen(ptr));
	}
#endif

#if defined(BKSGE_HAS_CXX11_CHAR16_T)
	BKSGE_CXX14_CONSTEXPR result_type
	operator()(char16_t const* ptr) const
	{
		return operator()(ptr, ptr + bksge::strlen(ptr));
	}
#endif

#if defined(BKSGE_HAS_CXX11_CHAR32_T)
	BKSGE_CXX14_CONSTEXPR result_type
	operator()(char32_t const* ptr) const
	{
		return operator()(ptr, ptr + bksge::strlen(ptr));
	}
#endif

	template <typename T>
	BKSGE_CXX14_CONSTEXPR result_type
	operator()(T const* ptr, std::size_t bytes) const
	{
		return operator()(ptr, ptr + bytes);
	}

	template <typename Range>
	BKSGE_CONSTEXPR result_type
	operator()(Range const& range) const
	{
		return operator()(bksge::begin(range), bksge::end(range));
	}

private:
	BKSGE_CONSTEXPR Hasher const& derived() const
	{
		return *static_cast<Hasher const*>(this);
	}
};

}	// namespace bksge

#endif // BKSGE_FND_HASH_FUNCTIONS_HASH_FACADE_HPP
