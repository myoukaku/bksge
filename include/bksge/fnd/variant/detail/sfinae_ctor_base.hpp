/**
 *	@file	sfinae_ctor_base.hpp
 *
 *	@brief	sfinae_ctor_base の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_SFINAE_CTOR_BASE_HPP
#define BKSGE_FND_VARIANT_DETAIL_SFINAE_CTOR_BASE_HPP

namespace bksge
{

namespace variant_detail
{

template <bool CanCopy, bool CanMove>
struct sfinae_ctor_base {};
template <>
struct sfinae_ctor_base<false, false>
{
	sfinae_ctor_base()                                   = default;
	sfinae_ctor_base(sfinae_ctor_base const&)            = delete;
	sfinae_ctor_base(sfinae_ctor_base&&)                 = delete;
	sfinae_ctor_base& operator=(sfinae_ctor_base const&) = default;
	sfinae_ctor_base& operator=(sfinae_ctor_base&&)      = default;
};
template <>
struct sfinae_ctor_base<true, false>
{
	sfinae_ctor_base()                                   = default;
	sfinae_ctor_base(sfinae_ctor_base const&)            = default;
	sfinae_ctor_base(sfinae_ctor_base&&)                 = delete;
	sfinae_ctor_base& operator=(sfinae_ctor_base const&) = default;
	sfinae_ctor_base& operator=(sfinae_ctor_base&&)      = default;
};
template <>
struct sfinae_ctor_base<false, true>
{
	sfinae_ctor_base()                                   = default;
	sfinae_ctor_base(sfinae_ctor_base const&)            = delete;
	sfinae_ctor_base(sfinae_ctor_base&&)                 = default;
	sfinae_ctor_base& operator=(sfinae_ctor_base const&) = default;
	sfinae_ctor_base& operator=(sfinae_ctor_base&&)      = default;
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_SFINAE_CTOR_BASE_HPP
