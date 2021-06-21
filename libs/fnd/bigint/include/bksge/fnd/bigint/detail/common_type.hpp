/**
 *	@file	common_type.hpp
 *
 *	@brief	common_type クラスの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_BIGINT_DETAIL_COMMON_TYPE_HPP
#define BKSGE_FND_BIGINT_DETAIL_COMMON_TYPE_HPP

#include <bksge/fnd/bigint/fwd/basic_bigint_fwd.hpp>
#include <bksge/fnd/algorithm/max.hpp>
#include <bksge/fnd/concepts/arithmetic.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <limits>

namespace bksge
{

template <bksge::size_t B1, bool S1, bksge::size_t B2, bool S2>
struct common_type<basic_bigint<B1, S1>, basic_bigint<B2, S2>>
{
private:
	static const bool S =
		B1 == B2 ? S1 && S2 :
		B1 >  B2 ? S1 :
		           S2;
public:
	using type = basic_bigint<bksge::max(B1, B2), S>;
};

// TODO
//template <bksge::size_t B1, bool S1, BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic)>
template <bksge::size_t B1, bool S1, typename Arithmetic>
struct common_type<basic_bigint<B1, S1>, Arithmetic>
{
private:
	static const bksge::size_t B2 = sizeof(Arithmetic) * CHAR_BIT;
	static const bool S2 = std::numeric_limits<Arithmetic>::is_signed;
	static const bool is_integer = std::numeric_limits<Arithmetic>::is_integer;
public:
	using type =
		bksge::conditional_t<!is_integer,
			Arithmetic,
		bksge::conditional_t<(B1 > B2),
			basic_bigint<B1, S1>,
		bksge::conditional_t<(B1 < B2),
			Arithmetic,
		bksge::conditional_t<S1,
			Arithmetic,
		bksge::conditional_t<S1 == S2,
			Arithmetic,
			basic_bigint<B1, S1>
		>>>>>;
};

// TODO
//template <BKSGE_REQUIRES_PARAM(bksge::arithmetic, Arithmetic), bksge::size_t B, bool S>
template <typename Arithmetic, bksge::size_t B, bool S>
struct common_type<Arithmetic, basic_bigint<B, S>>
	: public common_type<basic_bigint<B, S>, Arithmetic>
{};

}	// namespace bksge

#endif // BKSGE_FND_BIGINT_DETAIL_COMMON_TYPE_HPP
