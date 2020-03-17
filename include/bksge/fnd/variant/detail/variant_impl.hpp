/**
 *	@file	variant_impl.hpp
 *
 *	@brief	variant_impl の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_IMPL_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_IMPL_HPP

#include <bksge/fnd/variant/detail/access.hpp>
#include <bksge/fnd/variant/detail/variant_copy_assignment.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/variant/detail/visitation.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <utility>

namespace bksge
{

namespace variant_detail
{

template <typename... Types>
class variant_impl
	: public variant_copy_assignment<variant_traits<Types...>>
{
private:
	using base_type = variant_copy_assignment<variant_traits<Types...>>;

public:
	using base_type::base_type;
	using base_type::operator=;

	template <std::size_t I, typename Arg>
	void assign_impl(Arg&& arg)
	{
		this->assign_alt(access::base_t::get_alt<I>(*this), bksge::forward<Arg>(arg));
	}

private:
	struct Visitor
	{
		template <typename ThisAlt, typename ThatAlt>
		void operator()(ThisAlt& this_alt, ThatAlt& that_alt) const
		{
			using std::swap;
			swap(this_alt.m_value, that_alt.m_value);
		}
	};

public:
	void swap_impl(variant_impl& that)
	{
		if (this->valueless_by_exception() && that.valueless_by_exception())
		{
			// do nothing.
		}
		else if (this->index() == that.index())
		{
			visitation::base_t::visit_alt_at(this->index(), Visitor{}, *this, that);
		}
		else
		{
			variant_impl* lhs = this;
			variant_impl* rhs = bksge::addressof(that);
			if (lhs->move_nothrow() && !rhs->move_nothrow())
			{
				std::swap(lhs, rhs);
			}
			variant_impl tmp(bksge::move(*rhs));
#if !defined(BKSGE_NO_EXCEPTIONS)
			// EXTENSION: When the move construction of `lhs` into `rhs` throws
			// and `tmp` is nothrow move constructible then we move `tmp` back
			// into `rhs` and provide the strong exception safety guarantee.
			try
			{
				this->generic_construct(*rhs, bksge::move(*lhs));
			}
			catch (...)
			{
				if (tmp.move_nothrow())
				{
					this->generic_construct(*rhs, bksge::move(tmp));
				}
				throw;
			}
#else
			this->generic_construct(*rhs, bksge::move(*lhs));
#endif
			this->generic_construct(*lhs, bksge::move(tmp));
		}
	}

private:
	bool move_nothrow() const
	{
		BKSGE_CONSTEXPR bool results[] ={bksge::is_nothrow_move_constructible<Types>::value...};
		return this->valueless_by_exception() || results[this->index()];
	}
};

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_IMPL_HPP
