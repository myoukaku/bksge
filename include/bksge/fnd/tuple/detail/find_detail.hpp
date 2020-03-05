/**
 *	@file	find_detail.hpp
 *
 *	@brief	find_detail の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_TUPLE_DETAIL_FIND_DETAIL_HPP
#define BKSGE_FND_TUPLE_DETAIL_FIND_DETAIL_HPP

#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>

namespace bksge
{

namespace find_detail
{

static constexpr bksge::size_t not_found = static_cast<bksge::size_t>(-1);
static constexpr bksge::size_t ambiguous = not_found - 1;

inline constexpr bksge::size_t
find_idx_return(bksge::size_t curr_i, bksge::size_t res, bool matches)
{
	return !matches ? res :
		(res == not_found ? curr_i : ambiguous);
}

template <bksge::size_t _Nx>
inline constexpr bksge::size_t
find_idx(bksge::size_t i, const bool (&matches)[_Nx])
{
	return i == _Nx ? not_found :
		find_idx_return(i, find_idx(i + 1, matches), matches[i]);
}

template <typename T, typename... Types>
struct find_exactly_one_checked
{
	static constexpr bool matches[sizeof...(Types)] = { bksge::is_same<T, Types>::value... };
	static constexpr bksge::size_t value = find_detail::find_idx(0, matches);
	static_assert(value != not_found, "type not found in type list");
	static_assert(value != ambiguous, "type occurs more than once in type list");
};

template <typename T>
struct find_exactly_one_checked<T>
{
	static_assert(!bksge::is_same<T, T>::value, "type not in empty type list");
};

template <typename T, typename... Types>
struct find_exactly_one_t
	: public find_detail::find_exactly_one_checked<T, Types...>
{};

}	// namespace find_detail

}	// namespace bksge

#endif // BKSGE_FND_TUPLE_DETAIL_FIND_DETAIL_HPP
