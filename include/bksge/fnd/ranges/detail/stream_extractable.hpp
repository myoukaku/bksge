/**
 *	@file	stream_extractable.hpp
 *
 *	@brief	stream_extractable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_RANGES_DETAIL_STREAM_EXTRACTABLE_HPP
#define BKSGE_FND_RANGES_DETAIL_STREAM_EXTRACTABLE_HPP

#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/config.hpp>
#include <istream>

namespace bksge
{

namespace ranges
{

namespace detail
{

#if defined(BKSGE_HAS_CXX20_CONCEPTS)

template <typename Val, typename CharT, typename Traits>
concept stream_extractable =
	requires(std::basic_istream<CharT, Traits>& is, Val& t) { is >> t; };

#else

template <typename Val, typename CharT, typename Traits>
struct stream_extractable_impl
{
private:
	template <typename V2, typename Stream>
	static auto test(int) -> decltype(
		bksge::declval<Stream&>() >> bksge::declval<V2&>(),
		bksge::true_type{});

	template <typename V2, typename Stream>
	static auto test(...) -> bksge::false_type;

public:
	using type = decltype(test<Val, std::basic_istream<CharT, Traits>>(0));
};

template <typename Val, typename CharT, typename Traits>
using stream_extractable =
	typename stream_extractable_impl<Val, CharT, Traits>::type;

#endif

}	// namespace detail

}	// namespace ranges

}	// namespace bksge

#endif // BKSGE_FND_RANGES_DETAIL_STREAM_EXTRACTABLE_HPP
