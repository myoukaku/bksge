/**
 *	@file	visitation.hpp
 *
 *	@brief	visitation の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_DETAIL_VISITATION_HPP
#define BKSGE_FND_VARIANT_DETAIL_VISITATION_HPP

#include <bksge/fnd/variant/detail/access.hpp>
#include <bksge/fnd/variant/detail/constexpr_array.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/tmp/all_of.hpp>
#include <bksge/fnd/type_traits/common_type.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_invocable.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/type_identity.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/make_index_sequence.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

namespace variant_detail
{

namespace visitation
{

namespace base_t_impl
{

template <typename... Indices>
struct at_impl;

template <typename I, typename... Indices>
struct at_impl<I, Indices...>
{
	template <typename T>
	static BKSGE_CONSTEXPR auto get(T const& elems, I index, Indices... indices)
	->decltype(at_impl<Indices...>::get(elems[index], indices...))
	{
		return at_impl<Indices...>::get(elems[index], indices...);
	}
};

template <>
struct at_impl<>
{
	template <typename T>
	static BKSGE_CONSTEXPR T const& get(T const& elem)
	{
		return elem;
	}
};

template <typename T, typename... Indices>
static BKSGE_CONSTEXPR auto at(T const& elems, Indices... indices)
->decltype(at_impl<Indices...>::get(elems, indices...))
{
	return at_impl<Indices...>::get(elems, indices...);
}

template <typename F, typename... Fs>
static BKSGE_CONSTEXPR bool std_visit_visitor_return_type_check()
{
	return bksge::conjunction<bksge::is_same<F, Fs>...>::value;
}

template <
	typename... Fs,
	typename Result = constexpr_array<
		bksge::common_type_t<bksge::remove_cvref_t<Fs>...>,
		sizeof...(Fs)
	>
>
static BKSGE_CONSTEXPR Result make_farray(Fs&&... fs)
{
	static_assert(
		std_visit_visitor_return_type_check<bksge::remove_cvref_t<Fs>...>(),
		"`std::visit` requires the visitor to have a single return type.");
	return Result{{bksge::forward<Fs>(fs)...}};
}

template <typename IndexSeq, typename F, typename... Vs>
struct dispatcher;

template <typename F, typename... Vs, std::size_t... Is>
struct dispatcher<bksge::index_sequence<Is...>, F, Vs...>
{
	static BKSGE_CONSTEXPR auto dispatch(F f, Vs... vs)
	->decltype(bksge::invoke(static_cast<F>(f), access::base_t::get_alt<Is>(static_cast<Vs>(vs))...))
	{
		return bksge::invoke(static_cast<F>(f), access::base_t::get_alt<Is>(static_cast<Vs>(vs))...);
	}
};

template <typename F, typename... Vs, std::size_t... Is>
static BKSGE_CONSTEXPR auto make_dispatch(bksge::index_sequence<Is...>)
->decltype(&dispatcher<bksge::index_sequence<Is...>, F, Vs...>::dispatch)
{
	return &dispatcher<bksge::index_sequence<Is...>, F, Vs...>::dispatch;
}

template <std::size_t I, typename F, typename... Vs>
static BKSGE_CONSTEXPR auto make_fdiagonal_impl()
->decltype(make_dispatch<F, Vs...>(bksge::index_sequence<(bksge::type_identity<Vs>{}, I)...>{}))
{
	return make_dispatch<F, Vs...>(bksge::index_sequence<(bksge::type_identity<Vs>{}, I)...>{});
}

template <typename F, typename... Vs, std::size_t... Is>
static BKSGE_CONSTEXPR auto make_fdiagonal_impl(bksge::index_sequence<Is...>)
->decltype(base_t_impl::make_farray(make_fdiagonal_impl<Is, F, Vs...>()...))
{
	return base_t_impl::make_farray(make_fdiagonal_impl<Is, F, Vs...>()...);
}

template <typename F, typename V, typename... Vs, std::size_t N = bksge::remove_cvref_t<V>::size()>
static BKSGE_CONSTEXPR auto make_fdiagonal()
->decltype(make_fdiagonal_impl<F, V, Vs...>(bksge::make_index_sequence<N>{}))
{
	static_assert(bksge::tmp::all_of<(N == bksge::remove_cvref_t<Vs>::size())...>::value, "");
	return make_fdiagonal_impl<F, V, Vs...>(bksge::make_index_sequence<N>{});
}

#if !(defined(_MSC_VER) && (_MSC_VER <= 1916))

template <typename... IndexSequences>
struct make_fmatrix_impl_helper;

template <std::size_t... Is, std::size_t... Js, typename... IndexSequences>
struct make_fmatrix_impl_helper<bksge::index_sequence<Is...>, bksge::index_sequence<Js...>, IndexSequences...>
{
	template <typename F, typename... Vs>
	static BKSGE_CONSTEXPR auto get()
	->decltype(base_t_impl::make_farray(make_fmatrix_impl_helper<bksge::index_sequence<Is..., Js>, IndexSequences...>::template get<F, Vs...>()...))
	{
		return base_t_impl::make_farray(make_fmatrix_impl_helper<bksge::index_sequence<Is..., Js>, IndexSequences...>::template get<F, Vs...>()...);
	}
};

template <std::size_t... Is>
struct make_fmatrix_impl_helper<bksge::index_sequence<Is...>>
{
	template <typename F, typename... Vs>
	static BKSGE_CONSTEXPR auto get()
	->decltype(make_dispatch<F, Vs...>(bksge::index_sequence<Is...>{}))
	{
		return make_dispatch<F, Vs...>(bksge::index_sequence<Is...>{});
	}
};

template <typename F, typename... Vs, typename... IndexSequences>
static BKSGE_CONSTEXPR auto make_fmatrix_impl(IndexSequences...)
->decltype(make_fmatrix_impl_helper<IndexSequences...>::template get<F, Vs...>())
{
	return make_fmatrix_impl_helper<IndexSequences...>::template get<F, Vs...>();
}

#else

// Visual Studio 2017 のバグを回避
template <typename F, typename... Vs, std::size_t... Is>
static BKSGE_CONSTEXPR auto make_fmatrix_impl(bksge::index_sequence<Is...> is)
{
	return make_dispatch<F, Vs...>(is);
}

template <typename F, typename... Vs, std::size_t... Is, typename... Ls>
static BKSGE_CONSTEXPR auto
make_fmatrix_impl(
	bksge::index_sequence<Is...>,
	bksge::index_sequence<>,
	Ls... ls)
{
	return base_t_impl::make_farray(
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is...>{}, ls...)
	);
}

template <
	typename F,
	typename... Vs,
	std::size_t... Is,
	std::size_t J0,
	typename... Ls
>
static BKSGE_CONSTEXPR auto
make_fmatrix_impl(
	bksge::index_sequence<Is...>,
	bksge::index_sequence<J0>,
	Ls... ls)
{
	return base_t_impl::make_farray(
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J0>{}, ls...)
	);
}

template <
	typename F,
	typename... Vs,
	std::size_t... Is,
	std::size_t J0,
	std::size_t J1,
	typename... Ls
>
static BKSGE_CONSTEXPR auto
make_fmatrix_impl(
	bksge::index_sequence<Is...>,
	bksge::index_sequence<J0, J1>,
	Ls... ls)
{
	return base_t_impl::make_farray(
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J0>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J1>{}, ls...)
	);
}

template <
	typename F,
	typename... Vs,
	std::size_t... Is,
	std::size_t J0,
	std::size_t J1,
	std::size_t J2,
	typename... Ls
>
static BKSGE_CONSTEXPR auto
make_fmatrix_impl(
	bksge::index_sequence<Is...>,
	bksge::index_sequence<J0, J1, J2>,
	Ls... ls)
{
	return base_t_impl::make_farray(
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J0>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J1>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J2>{}, ls...)
	);
}

template <
	typename F,
	typename... Vs,
	std::size_t... Is,
	std::size_t J0,
	std::size_t J1,
	std::size_t J2,
	std::size_t J3,
	typename... Ls
>
static BKSGE_CONSTEXPR auto
make_fmatrix_impl(
	bksge::index_sequence<Is...>,
	bksge::index_sequence<J0, J1, J2, J3>,
	Ls... ls)
{
	return base_t_impl::make_farray(
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J0>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J1>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J2>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J3>{}, ls...)
	);
}

template <
	typename F,
	typename... Vs,
	std::size_t... Is,
	std::size_t J0,
	std::size_t J1,
	std::size_t J2,
	std::size_t J3,
	std::size_t J4,
	typename... Ls
>
static BKSGE_CONSTEXPR auto
make_fmatrix_impl(
	bksge::index_sequence<Is...>,
	bksge::index_sequence<J0, J1, J2, J3, J4>,
	Ls... ls)
{
	return base_t_impl::make_farray(
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J0>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J1>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J2>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J3>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J4>{}, ls...)
	);
}

template <
	typename F,
	typename... Vs,
	std::size_t... Is,
	std::size_t J0,
	std::size_t J1,
	std::size_t J2,
	std::size_t J3,
	std::size_t J4,
	std::size_t J5,
	typename... Ls
>
static BKSGE_CONSTEXPR auto
make_fmatrix_impl(
	bksge::index_sequence<Is...>,
	bksge::index_sequence<J0, J1, J2, J3, J4, J5>,
	Ls... ls)
{
	return base_t_impl::make_farray(
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J0>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J1>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J2>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J3>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J4>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J5>{}, ls...)
	);
}

template <
	typename F,
	typename... Vs,
	std::size_t... Is,
	std::size_t J0,
	std::size_t J1,
	std::size_t J2,
	std::size_t J3,
	std::size_t J4,
	std::size_t J5,
	std::size_t J6,
	typename... Ls
>
static BKSGE_CONSTEXPR auto
make_fmatrix_impl(
	bksge::index_sequence<Is...>,
	bksge::index_sequence<J0, J1, J2, J3, J4, J5, J6>,
	Ls... ls)
{
	return base_t_impl::make_farray(
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J0>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J1>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J2>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J3>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J4>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J5>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J6>{}, ls...)
	);
}

template <
	typename F,
	typename... Vs,
	std::size_t... Is,
	std::size_t J0,
	std::size_t J1,
	std::size_t J2,
	std::size_t J3,
	std::size_t J4,
	std::size_t J5,
	std::size_t J6,
	std::size_t J7,
	std::size_t J8,
	typename... Ls
>
static BKSGE_CONSTEXPR auto
make_fmatrix_impl(
	bksge::index_sequence<Is...>,
	bksge::index_sequence<J0, J1, J2, J3, J4, J5, J6, J7, J8>,
	Ls... ls)
{
	return base_t_impl::make_farray(
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J0>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J1>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J2>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J3>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J4>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J5>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J6>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J7>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J8>{}, ls...)
	);
}

template <
	typename F,
	typename... Vs,
	std::size_t... Is,
	std::size_t J0,
	std::size_t J1,
	std::size_t J2,
	std::size_t J3,
	std::size_t J4,
	std::size_t J5,
	std::size_t J6,
	std::size_t J7,
	std::size_t J8,
	std::size_t J9,
	typename... Ls
>
static BKSGE_CONSTEXPR auto
make_fmatrix_impl(
	bksge::index_sequence<Is...>,
	bksge::index_sequence<J0, J1, J2, J3, J4, J5, J6, J7, J8, J9>,
	Ls... ls)
{
	return base_t_impl::make_farray(
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J0>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J1>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J2>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J3>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J4>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J5>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J6>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J7>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J8>{}, ls...),
		make_fmatrix_impl<F, Vs...>(bksge::index_sequence<Is..., J9>{}, ls...)
	);
}

#endif

template <typename F, typename... Vs>
static BKSGE_CONSTEXPR auto make_fmatrix()
->decltype(make_fmatrix_impl<F, Vs...>(bksge::index_sequence<>{}, bksge::make_index_sequence<bksge::remove_cvref_t<Vs>::size()>{}...))
{
	return make_fmatrix_impl<F, Vs...>(bksge::index_sequence<>{}, bksge::make_index_sequence<bksge::remove_cvref_t<Vs>::size()>{}...);
}

template <typename FDiagonal, typename Visitor, typename... Vs>
static BKSGE_CONSTEXPR auto
visit_alt_at_impl(FDiagonal const& fdiagonal, std::size_t index, Visitor&& visitor, Vs&&... vs)
->decltype(fdiagonal[index](bksge::forward<Visitor>(visitor), bksge::forward<Vs>(vs)...))
{
	return fdiagonal[index](bksge::forward<Visitor>(visitor), bksge::forward<Vs>(vs)...);
}

template <typename FMatrix, typename Visitor, typename... Vs>
static BKSGE_CONSTEXPR auto
visit_alt_impl(FMatrix const& fmatrix, Visitor&& visitor, Vs&&... vs)
->decltype(at(fmatrix, vs.index()...)(bksge::forward<Visitor>(visitor), bksge::forward<Vs>(vs)...))
{
	return at(fmatrix, vs.index()...)(bksge::forward<Visitor>(visitor), bksge::forward<Vs>(vs)...);
}

}	// namespace base_t_impl

struct base_t
{
	template <typename Visitor, typename... Vs>
	static BKSGE_CONSTEXPR auto
	visit_alt_at(std::size_t index, Visitor&& visitor, Vs&&... vs)
	->decltype(base_t_impl::visit_alt_at_impl(
			base_t_impl::make_fdiagonal<Visitor&&, decltype(bksge::forward<Vs>(vs).as_base())...>(),
			index,
			bksge::forward<Visitor>(visitor),
			bksge::forward<Vs>(vs).as_base()...))
	{
		return base_t_impl::visit_alt_at_impl(
			base_t_impl::make_fdiagonal<Visitor&&, decltype(bksge::forward<Vs>(vs).as_base())...>(),
			index,
			bksge::forward<Visitor>(visitor),
			bksge::forward<Vs>(vs).as_base()...);
	}

	template <typename Visitor, typename... Vs>
	static BKSGE_CONSTEXPR auto
	visit_alt(Visitor&& visitor, Vs&&... vs)
	->decltype(base_t_impl::visit_alt_impl(
			base_t_impl::make_fmatrix<Visitor&&, decltype(bksge::forward<Vs>(vs).as_base())...>(),
			bksge::forward<Visitor>(visitor),
			bksge::forward<Vs>(vs).as_base()...))
	{
		return base_t_impl::visit_alt_impl(
			base_t_impl::make_fmatrix<Visitor&&, decltype(bksge::forward<Vs>(vs).as_base())...>(),
			bksge::forward<Visitor>(visitor),
			bksge::forward<Vs>(vs).as_base()...);
	}
};

struct variant_t
{
private:
	template <typename Visitor>
	struct value_visitor
	{
		Visitor&& m_visitor;

		template <typename... Alts>
		BKSGE_CONSTEXPR auto operator()(Alts&&... alts) const
		->decltype(bksge::invoke(bksge::forward<Visitor>(m_visitor), bksge::forward<Alts>(alts).m_value...))
		{
			static_assert(
				bksge::is_invocable<Visitor, decltype((bksge::forward<Alts>(alts).m_value))...>::value,
				"`std::visit` requires the visitor to be exhaustive.");

			return bksge::invoke(bksge::forward<Visitor>(m_visitor), bksge::forward<Alts>(alts).m_value...);
		}
	};

	template <typename Visitor>
	static BKSGE_CONSTEXPR auto
	make_value_visitor(Visitor&& visitor)
	->value_visitor<Visitor>
	{
		return value_visitor<Visitor>{bksge::forward<Visitor>(visitor)};
	}

public:
	template <typename Visitor, typename... Vs>
	static BKSGE_CONSTEXPR auto
	visit_alt_at(std::size_t index, Visitor&& visitor, Vs&&... vs)
	->decltype(base_t::visit_alt_at(index, bksge::forward<Visitor>(visitor), bksge::forward<Vs>(vs).m_impl...))
	{
		return base_t::visit_alt_at(index, bksge::forward<Visitor>(visitor), bksge::forward<Vs>(vs).m_impl...);
	}

	template <typename Visitor, typename... Vs>
	static BKSGE_CONSTEXPR auto
	visit_alt(Visitor&& visitor, Vs&&... vs)
	->decltype(base_t::visit_alt(bksge::forward<Visitor>(visitor), bksge::forward<Vs>(vs).m_impl...))
	{
		return base_t::visit_alt(bksge::forward<Visitor>(visitor), bksge::forward<Vs>(vs).m_impl...);
	}

	template <typename Visitor, typename... Vs>
	static BKSGE_CONSTEXPR auto
	visit_value_at(std::size_t index, Visitor&& visitor, Vs&&... vs)
	->decltype(visit_alt_at(index, make_value_visitor(bksge::forward<Visitor>(visitor)), bksge::forward<Vs>(vs)...))
	{
		return visit_alt_at(index, make_value_visitor(bksge::forward<Visitor>(visitor)), bksge::forward<Vs>(vs)...);
	}

	template <typename Visitor, typename... Vs>
	static BKSGE_CONSTEXPR auto
	visit_value(Visitor&& visitor, Vs&&... vs)
	->decltype(visit_alt(make_value_visitor(bksge::forward<Visitor>(visitor)), bksge::forward<Vs>(vs)...))
	{
		return visit_alt(make_value_visitor(bksge::forward<Visitor>(visitor)), bksge::forward<Vs>(vs)...);
	}
};

}	// namespace visitation

}	// namespace variant_detail

}	// namespace bksge

#endif // BKSGE_FND_VARIANT_DETAIL_VISITATION_HPP
