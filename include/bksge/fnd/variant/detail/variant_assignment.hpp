/**
 *	@file	variant_assignment.hpp
 *
 *	@brief	variant_assignment の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_ASSIGNMENT_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_ASSIGNMENT_HPP

#include <bksge/fnd/variant/detail/access.hpp>
#include <bksge/fnd/variant/detail/variant_alt.hpp>
#include <bksge/fnd/variant/detail/variant_copy_constructor.hpp>
#include <bksge/fnd/variant/detail/visitation.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4197);	// キャストの トップレベルの volatile は無視されます。
BKSGE_WARNING_DISABLE_MSVC(4702);	// 制御が渡らないコードです。

namespace bksge
{

namespace variant_detail
{

template <typename Traits>
class variant_assignment : public variant_copy_constructor<Traits>
{
private:
	using base_type = variant_copy_constructor<Traits>;

public:
	using base_type::base_type;
	using base_type::operator=;

	template <std::size_t I, typename... Args>
	auto emplace_impl(Args&&... args)
	->decltype((this->construct_alt(
		access::base_t::get_alt<I>(*this),
		bksge::forward<Args>(args)...)))
	{
		this->destroy();
		auto& res = this->construct_alt(
			access::base_t::get_alt<I>(*this),
			bksge::forward<Args>(args)...);
		this->m_index = I;
		return res;
	}

protected:
	template <std::size_t I, typename T, typename Arg>
	void assign_alt(variant_alt<I, T>& a, Arg&& arg)
	{
		if (this->index() == I)
		{
			a.m_value = bksge::forward<Arg>(arg);
		}
		else
		{
			struct
			{
				void operator()(bksge::true_type) const
				{
					m_this->emplace_impl<I>(bksge::forward<Arg>(m_arg));
				}

				void operator()(bksge::false_type) const
				{
					m_this->emplace_impl<I>(T(bksge::forward<Arg>(m_arg)));
				}

				variant_assignment* m_this;
				Arg&& m_arg;
			} impl{this, bksge::forward<Arg>(arg)};

			impl(
				bksge::bool_constant<
					bksge::is_nothrow_constructible<T, Arg>::value ||
					!bksge::is_nothrow_move_constructible<T>::value
				>{});
		}
	}

private:
	struct Visitor
	{
		variant_assignment* m_this;

		template <typename ThisAlt, typename ThatAlt>
		void operator()(ThisAlt& this_alt, ThatAlt&& that_alt) const
		{
			m_this->assign_alt(
				this_alt,
				bksge::forward<ThatAlt>(that_alt).m_value);
		}
	};

protected:
	template <typename That>
	void generic_assign(That&& that)
	{
		if (this->valueless_by_exception() && that.valueless_by_exception())
		{
			// do nothing.
		}
		else if (that.valueless_by_exception())
		{
			this->destroy();
		}
		else
		{
			visitation::base_t::visit_alt_at(that.index(), Visitor{this}, *this, bksge::forward<That>(that));
		}
	}
};

}	// namespace variant_detail

}	// namespace bksge

BKSGE_WARNING_POP();

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_ASSIGNMENT_HPP
