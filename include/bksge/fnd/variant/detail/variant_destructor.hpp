/**
 *	@file	variant_destructor.hpp
 *
 *	@brief	variant_destructor の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VARIANT_DESTRUCTOR_HPP
#define BKSGE_FND_VARIANT_DETAIL_VARIANT_DESTRUCTOR_HPP

#include <bksge/fnd/variant/detail/trait_enum.hpp>
#include <bksge/fnd/variant/detail/variant_base.hpp>
#include <bksge/fnd/variant/detail/variant_npos_t.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/variant/detail/visitation.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

namespace variant_detail
{

template <typename Traits, trait_enum = Traits::destructible_trait>
class variant_destructor;

#define BKSGE_VARIANT_DESTRUCTOR(destructible_trait, destructor, destroy)  \
template <typename... Types>                                               \
class variant_destructor<variant_traits<Types...>, destructible_trait>     \
	: public variant_base<destructible_trait, Types...>                    \
{                                                                          \
private:                                                                   \
	using base_type = variant_base<destructible_trait, Types...>;          \
	                                                                       \
protected:                                                                 \
	using index_t = typename base_type::index_t;                           \
	                                                                       \
public:                                                                    \
	using base_type::base_type;                                            \
	using base_type::operator=;                                            \
	                                                                       \
	variant_destructor(variant_destructor const&) = default;               \
	variant_destructor(variant_destructor&&) = default;                    \
	destructor                                                             \
	variant_destructor& operator=(variant_destructor const&) = default;    \
	variant_destructor& operator=(variant_destructor&&) = default;         \
	                                                                       \
protected:                                                                 \
	destroy                                                                \
}

BKSGE_VARIANT_DESTRUCTOR(
	trait_enum::TriviallyAvailable,
	~variant_destructor() = default;,
	void destroy() BKSGE_NOEXCEPT
	{
		this->m_index = variant_npos_t<index_t>::value;
	}
);

BKSGE_VARIANT_DESTRUCTOR(
	trait_enum::Available,
	~variant_destructor() { destroy(); },
	struct DestroyVisitor
	{
		template <typename Alt>
		void operator()(Alt& alt) const BKSGE_NOEXCEPT
		{
			using alt_type = bksge::remove_cvref_t<Alt>;
			alt.~alt_type();
		}
	};
	void destroy() BKSGE_NOEXCEPT
	{
		if (!this->valueless_by_exception())
		{
			visitation::base_t::visit_alt(DestroyVisitor{}, *this);
		}

		this->m_index = variant_npos_t<index_t>::value;
	}
);

BKSGE_VARIANT_DESTRUCTOR(
	trait_enum::Unavailable,
	~variant_destructor() = delete;,
	void destroy() BKSGE_NOEXCEPT = delete;
);

#undef BKSGE_VARIANT_DESTRUCTOR

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VARIANT_DESTRUCTOR_HPP
