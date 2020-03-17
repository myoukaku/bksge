/**
 *	@file	sfinae_assign_base.hpp
 *
 *	@brief	sfinae_assign_base の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_SFINAE_ASSIGN_BASE_HPP
#define BKSGE_FND_VARIANT_DETAIL_SFINAE_ASSIGN_BASE_HPP

namespace bksge
{

namespace variant_detail
{

template <bool CanCopy, bool CanMove>
struct sfinae_assign_base {};
template <>
struct sfinae_assign_base<false, false>
{
	sfinae_assign_base()                                     = default;
	sfinae_assign_base(sfinae_assign_base const&)            = default;
	sfinae_assign_base(sfinae_assign_base&&)                 = default;
	sfinae_assign_base& operator=(sfinae_assign_base const&) = delete;
	sfinae_assign_base& operator=(sfinae_assign_base&&)      = delete;
};
template <>
struct sfinae_assign_base<true, false>
{
	sfinae_assign_base()                                     = default;
	sfinae_assign_base(sfinae_assign_base const&)            = default;
	sfinae_assign_base(sfinae_assign_base&&)                 = default;
	sfinae_assign_base& operator=(sfinae_assign_base const&) = default;
	sfinae_assign_base& operator=(sfinae_assign_base&&)      = delete;
};
template <>
struct sfinae_assign_base<false, true>
{
	sfinae_assign_base()                                     = default;
	sfinae_assign_base(sfinae_assign_base const&)            = default;
	sfinae_assign_base(sfinae_assign_base&&)                 = default;
	sfinae_assign_base& operator=(sfinae_assign_base const&) = delete;
	sfinae_assign_base& operator=(sfinae_assign_base&&)      = default;
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_SFINAE_ASSIGN_BASE_HPP
