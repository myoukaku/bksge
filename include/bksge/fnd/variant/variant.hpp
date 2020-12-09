/**
 *	@file	variant.hpp
 *
 *	@brief	variant の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_VARIANT_VARIANT_HPP
#define BKSGE_FND_VARIANT_VARIANT_HPP

#include <bksge/fnd/variant/config.hpp>

#if defined(BKSGE_HAS_STD_VARIANT)

namespace bksge
{

using std::variant;

}	// namespace bksge

#else

#include <bksge/fnd/variant/fwd/variant_fwd.hpp>
#include <bksge/fnd/variant/get.hpp>
#include <bksge/fnd/variant/variant_alternative.hpp>
#include <bksge/fnd/variant/variant_npos.hpp>
#include <bksge/fnd/variant/detail/accepted_index.hpp>
#include <bksge/fnd/variant/detail/exactly_once.hpp>
#include <bksge/fnd/variant/detail/index_of.hpp>
#include <bksge/fnd/variant/detail/never_valueless.hpp>
#include <bksge/fnd/variant/detail/never_valueless_alt.hpp>
#include <bksge/fnd/variant/detail/raw_idx_visit.hpp>
#include <bksge/fnd/variant/detail/raw_visit.hpp>
#include <bksge/fnd/variant/detail/variant_access.hpp>
#include <bksge/fnd/variant/detail/variant_base.hpp>
#include <bksge/fnd/variant/detail/variant_cookie.hpp>
#include <bksge/fnd/variant/detail/variant_traits.hpp>
#include <bksge/fnd/compare/concepts/three_way_comparable.hpp>
#include <bksge/fnd/compare/common_comparison_category.hpp>
#include <bksge/fnd/compare/compare_three_way.hpp>
#include <bksge/fnd/compare/compare_three_way_result.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/concepts/detail/overload_priority.hpp>
#include <bksge/fnd/detail/enable_copy_move.hpp>
#include <bksge/fnd/detail/enable_default_constructor.hpp>
#include <bksge/fnd/detail/enable_hash_call.hpp>
#include <bksge/fnd/functional/invoke.hpp>
#include <bksge/fnd/functional/ranges/equal_to.hpp>
#include <bksge/fnd/functional/ranges/greater.hpp>
#include <bksge/fnd/functional/ranges/greater_equal.hpp>
#include <bksge/fnd/functional/ranges/less.hpp>
#include <bksge/fnd/functional/ranges/less_equal.hpp>
#include <bksge/fnd/functional/ranges/not_equal_to.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/decay.hpp>
#include <bksge/fnd/type_traits/disjunction.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/is_assignable.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/is_constructible.hpp>
#include <bksge/fnd/type_traits/is_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_scalar.hpp>
#include <bksge/fnd/type_traits/is_swappable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_move_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_constructible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_assignable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_swappable.hpp>
#include <bksge/fnd/type_traits/is_nothrow_invocable.hpp>
#include <bksge/fnd/type_traits/is_reference.hpp>
#include <bksge/fnd/type_traits/is_void.hpp>
#include <bksge/fnd/type_traits/make_signed.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/remove_cvref.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/forward.hpp>
#include <bksge/fnd/utility/in_place_index.hpp>
#include <bksge/fnd/utility/in_place_type.hpp>
#include <bksge/fnd/utility/index_sequence.hpp>
#include <bksge/fnd/utility/index_sequence_for.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>
#include <initializer_list>
#include <functional>	// hash

namespace bksge
{

template <typename... Types>
class variant
	: private variant_detail::VariantBase<Types...>
	, private detail::enable_default_constructor<
		variant_detail::VariantTraits<Types...>::s_default_ctor,
		variant<Types...>>
	, private detail::enable_copy_move<
		variant_detail::VariantTraits<Types...>::s_copy_ctor,
		variant_detail::VariantTraits<Types...>::s_copy_assign,
		variant_detail::VariantTraits<Types...>::s_move_ctor,
		variant_detail::VariantTraits<Types...>::s_move_assign,
		variant<Types...>>
{
private:
	friend class variant_detail::variant_access;

	static_assert(sizeof...(Types) > 0, "variant must have at least one alternative");
	static_assert(!bksge::disjunction<bksge::is_reference<Types>...>::value, "variant must have no reference alternative");
	static_assert(!bksge::disjunction<bksge::is_void<Types>...>::value, "variant must have no void alternative");

	using Base = variant_detail::VariantBase<Types...>;
	using DefaultCtorEnabler =
		detail::enable_default_constructor<
		variant_detail::VariantTraits<Types...>::s_default_ctor,
		variant<Types...>>;

	template <typename T>
	using not_self = bksge::negation<bksge::is_same<bksge::remove_cvref_t<T>, variant>>;

	template <typename T>
	using exactly_once = variant_detail::exactly_once<T, Types...>;

	template <typename T>
	using accepted_index = variant_detail::accepted_index<T, variant>;

	template <std::size_t N, typename = bksge::enable_if_t<(N < sizeof...(Types))>>
	using to_type = variant_alternative_t<N, variant>;

	template <typename T, typename = bksge::enable_if_t<not_self<T>::value>>
	using accepted_type = to_type<accepted_index<T>::value>;

	template <typename T>
	using index_of = variant_detail::index_of<T, Types...>;

	using VariantTraits = variant_detail::VariantTraits<Types...>;

	template <typename T>
	struct is_in_place_tag : bksge::false_type {};
	template <typename T>
	struct is_in_place_tag<bksge::in_place_type_t<T>> : bksge::true_type {};
	template <std::size_t N>
	struct is_in_place_tag<bksge::in_place_index_t<N>> : bksge::true_type {};

	template <typename T>
	using not_in_place_tag = bksge::negation<is_in_place_tag<bksge::remove_cvref_t<T>>>;

public:
	variant() = default;
	variant(variant const& rhs) = default;
	variant(variant&&) = default;
	variant& operator=(variant const&) = default;
	variant& operator=(variant&&) = default;
	~variant() = default;

	template <typename T,
		typename = bksge::enable_if_t<sizeof...(Types) != 0>,
		typename = bksge::enable_if_t<not_in_place_tag<T>::value>,
		typename Tj = accepted_type<T&&>,
		typename = bksge::enable_if_t<exactly_once<Tj>::value && bksge::is_constructible<Tj, T>::value>>
	constexpr
	variant(T&& t)
		noexcept(bksge::is_nothrow_constructible<Tj, T>::value)
		: variant(bksge::in_place_index<accepted_index<T>::value>, bksge::forward<T>(t))
	{}

	template <typename T, typename... Args,
		typename = bksge::enable_if_t<exactly_once<T>::value && bksge::is_constructible<T, Args...>::value>>
	constexpr explicit
	variant(bksge::in_place_type_t<T>, Args&&... args)
		: variant(bksge::in_place_index<index_of<T>::value>, bksge::forward<Args>(args)...)
	{}

	template <typename T, typename U, typename... Args,
		typename = bksge::enable_if_t<exactly_once<T>::value && bksge::is_constructible<T, std::initializer_list<U>&, Args...>::value>>
	constexpr explicit
	variant(bksge::in_place_type_t<T>, std::initializer_list<U> il, Args&&... args)
		: variant(bksge::in_place_index<index_of<T>::value>, il, bksge::forward<Args>(args)...)
	{}

	template <std::size_t N, typename... Args,
		typename T = to_type<N>,
		typename = bksge::enable_if_t<bksge::is_constructible<T, Args...>::value>>
	constexpr explicit
	variant(bksge::in_place_index_t<N>, Args&&... args)
		: Base(bksge::in_place_index<N>, bksge::forward<Args>(args)...)
		, DefaultCtorEnabler(detail::enable_default_constructor_tag{})
	{}

	template <std::size_t N, typename U, typename... Args,
		typename T = to_type<N>,
		typename = bksge::enable_if_t<bksge::is_constructible<T, std::initializer_list<U>&, Args...>::value>>
	constexpr explicit
	variant(bksge::in_place_index_t<N>, std::initializer_list<U> il, Args&&... args)
		: Base(bksge::in_place_index<N>, il, bksge::forward<Args>(args)...)
		, DefaultCtorEnabler(detail::enable_default_constructor_tag{})
	{}

private:
	template <typename T>
	void assign_impl(T&& rhs, bksge::true_type)
	{
		constexpr auto Index = accepted_index<T>::value;
		this->emplace<Index>(bksge::forward<T>(rhs));
	}

	template <typename T>
	void assign_impl(T&& rhs, bksge::false_type)
	{
		operator=(variant(bksge::forward<T>(rhs)));
	}

public:
	template <typename T>
	bksge::enable_if_t<
		exactly_once<accepted_type<T&&>>::value &&
		bksge::is_constructible<accepted_type<T&&>, T>::value &&
		bksge::is_assignable<accepted_type<T&&>&, T>::value,
		variant&
	>
	operator=(T&& rhs)
		noexcept(
			bksge::is_nothrow_assignable<accepted_type<T&&>&, T>::value &&
			bksge::is_nothrow_constructible<accepted_type<T&&>, T>::value)
	{
		constexpr auto Index = accepted_index<T>::value;
		if (index() == Index)
		{
			bksge::get<Index>(*this) = bksge::forward<T>(rhs);
		}
		else
		{
			using Tj = accepted_type<T&&>;
			assign_impl(bksge::forward<T>(rhs),
				bksge::bool_constant<
					bksge::is_nothrow_constructible<Tj, T>::value ||
					!bksge::is_nothrow_move_constructible<Tj>::value>{});
		}
		return *this;
	}

	template <typename T, typename... Args>
	bksge::enable_if_t<
		bksge::is_constructible<T, Args...>::value &&
		exactly_once<T>::value,
		T&
	>
	emplace(Args&&... args)
	{
		constexpr std::size_t Index = index_of<T>::value;
		return this->emplace<Index>(bksge::forward<Args>(args)...);
	}

	template <typename T, typename U, typename... Args>
	bksge::enable_if_t<
		bksge::is_constructible<T, std::initializer_list<U>&, Args...>::value &&
		exactly_once<T>::value,
		T&
	>
	emplace(std::initializer_list<U> il, Args&&... args)
	{
		constexpr std::size_t Index = index_of<T>::value;
		return this->emplace<Index>(il, bksge::forward<Args>(args)...);
	}

private:
	// Provide the strong exception-safety guarantee when possible,
	// to avoid becoming valueless.
	template <std::size_t N, typename AltType, typename... Args,
		typename = bksge::enable_if_t<bksge::is_nothrow_constructible<AltType, Args...>::value>>
	void emplace_impl(Args&&... args, bksge::detail::overload_priority<3>)
	{
		this->reset();
		variant_detail::variant_access::variant_construct_by_index<N>(*this, bksge::forward<Args>(args)...);
	}

	template <std::size_t N, typename AltType, typename... Args,
		typename = bksge::enable_if_t<bksge::is_scalar<AltType>::value>>
	void emplace_impl(Args&&... args, bksge::detail::overload_priority<2>)
	{
		// This might invoke a potentially-throwing conversion operator:
		const AltType tmp(bksge::forward<Args>(args)...);
		// But these steps won't throw:
		this->reset();
		variant_detail::variant_access::variant_construct_by_index<N>(*this, tmp);
	}

	template <std::size_t N, typename AltType, typename... Args,
		typename = bksge::enable_if_t<variant_detail::NeverValuelessAlt<AltType>() && VariantTraits::s_move_assign>>
	void emplace_impl(Args&&... args, bksge::detail::overload_priority<1>)
	{
		// This construction might throw:
		variant tmp(bksge::in_place_index<N>, bksge::forward<Args>(args)...);
		// But NeverValuelessAlt<AltType> means this won't:
		*this = bksge::move(tmp);
	}

	template <std::size_t N, typename AltType, typename... Args>
	void emplace_impl(Args&&... args, bksge::detail::overload_priority<0>)
	{
		// This case only provides the basic exception-safety guarantee,
		// i.e. the variant can become valueless.
		this->reset();
		try
		{
			variant_detail::variant_access::variant_construct_by_index<N>(*this, bksge::forward<Args>(args)...);
		}
		catch (...)
		{
			using index_type = decltype(this->m_index);
			this->m_index = static_cast<index_type>(bksge::variant_npos);
			throw;
		}
	}

public:
	template <std::size_t N, typename... Args>
	bksge::enable_if_t<
		bksge::is_constructible<variant_alternative_t<N, variant>, Args...>::value,
		variant_alternative_t<N, variant>&
	>
	emplace(Args&&... args)
	{
		static_assert(N < sizeof...(Types), "The index must be in [0, number of alternatives)");
		using alt_type = variant_alternative_t<N, variant>;
		emplace_impl<N, alt_type, Args...>(bksge::forward<Args>(args)..., bksge::detail::overload_priority<3>{});
		return bksge::get<N>(*this);
	}

	template <std::size_t N, typename U, typename... Args>
	bksge::enable_if_t<
		bksge::is_constructible<variant_alternative_t<N, variant>, std::initializer_list<U>&, Args...>::value,
		variant_alternative_t<N, variant>&
	>
	emplace(std::initializer_list<U> il, Args&&... args)
	{
		static_assert(N < sizeof...(Types), "The index must be in [0, number of alternatives)");
		using alt_type = variant_alternative_t<N, variant>;
		emplace_impl<N, alt_type, std::initializer_list<U>&, Args...>(il, bksge::forward<Args>(args)..., bksge::detail::overload_priority<3>{});
		return bksge::get<N>(*this);
	}

	constexpr bool valueless_by_exception() const noexcept
	{
		return !this->valid();
	}

private:
	template <typename... UTypes, typename = bksge::enable_if_t<variant_detail::NeverValueless<UTypes...>::value>>
	constexpr std::size_t index_impl(bksge::detail::overload_priority<2>) const noexcept
	{
		return this->m_index;
	}

	template <typename... UTypes, typename = bksge::enable_if_t<(sizeof...(UTypes) <= typename Base::index_type(-1) / 2)>>
	constexpr std::size_t index_impl(bksge::detail::overload_priority<1>) const noexcept
	{
		return bksge::make_signed_t<typename Base::index_type>(this->m_index);
	}

	template <typename... UTypes>
	constexpr std::size_t index_impl(bksge::detail::overload_priority<0>) const noexcept
	{
		return std::size_t(typename Base::index_type(this->m_index + 1)) - 1;
	}

public:
	constexpr std::size_t index() const noexcept
	{
		return index_impl<Types...>(bksge::detail::overload_priority<2>{});
	}

private:
	struct SwapVisitor
	{
		variant& m_lhs;
		variant& m_rhs;

		// rhs_index == bksge::variant_npos
		template <typename RhsMem, typename RhsIndex>
		void impl(RhsMem&&, RhsIndex, bksge::true_type)
		{
			if (!m_lhs.valueless_by_exception()) /*[[__likely__]]*/
			{
				m_rhs = bksge::move(m_lhs);
				m_lhs.reset();
			}
		}

		// rhs_index != bksge::variant_npos
		template <typename RhsMem, typename RhsIndex>
		void impl(RhsMem&& rhs_mem, RhsIndex rhs_index, bksge::false_type)
		{
			if (m_lhs.index() == rhs_index)
			{
				auto& this_mem = bksge::get<rhs_index>(m_lhs);
				using std::swap;
				swap(this_mem, rhs_mem);
			}
			else
			{
				if (!m_lhs.valueless_by_exception()) /*[[__likely__]]*/
				{
					auto tmp(bksge::move(rhs_mem));
					m_rhs = bksge::move(m_lhs);
					m_lhs.destructive_move(static_cast<unsigned short>(rhs_index), bksge::move(tmp));
				}
				else
				{
					m_lhs.destructive_move(static_cast<unsigned short>(rhs_index), bksge::move(rhs_mem));
					m_rhs.reset();
				}
			}
		}

		template <typename RhsMem, typename RhsIndex>
		void operator()(RhsMem&& rhs_mem, RhsIndex rhs_index)
		{
			impl(bksge::forward<RhsMem>(rhs_mem), rhs_index,
				bksge::bool_constant<rhs_index == bksge::variant_npos>{});
		}
	};

public:
	void swap(variant& rhs)
		noexcept(
			bksge::conjunction<bksge::is_nothrow_swappable<Types>...>::value &&
			bksge::is_nothrow_move_constructible<variant>::value)
	{
		variant_detail::raw_idx_visit(SwapVisitor{*this, rhs}, rhs);
	}

#if defined(__clang__) && __clang_major__ <= 7
public:
	using Base::m_u; // See https://bugs.llvm.org/show_bug.cgi?id=31852
#endif
};

namespace variant_detail
{

template <typename Pred, typename Result, typename... Types>
struct VariantRelopVisitor
{
	variant<Types...> const& m_lhs;
	Result&	m_ret;
	Pred	m_pred {};

	template <typename RhsMem, typename RhsIndex>
	constexpr void impl(RhsMem&& , RhsIndex rhs_index, bksge::false_type)
	{
		m_ret = bksge::invoke(m_pred, m_lhs.index() + 1, rhs_index + 1);
	}

	template <typename RhsMem, typename RhsIndex>
	constexpr void impl(RhsMem&& rhs_mem, RhsIndex rhs_index, bksge::true_type)
	{
		if (m_lhs.index() == rhs_index)
		{
			auto& this_mem = bksge::get<rhs_index>(m_lhs);
			m_ret = bksge::invoke(m_pred, this_mem, rhs_mem);
		}
		else
		{
			impl(bksge::forward<RhsMem>(rhs_mem), rhs_index, bksge::false_type{});
		}
	}

	template <typename RhsMem, typename RhsIndex>
	constexpr void operator()(RhsMem&& rhs_mem, RhsIndex rhs_index)
	{
		impl(bksge::forward<RhsMem>(rhs_mem), rhs_index,
			bksge::bool_constant<rhs_index != bksge::variant_npos>{});
	}
};

}	// namespace variant_detail

#define BKSGE_VARIANT_RELATION_FUNCTION_TEMPLATE(OP, PRED)                      \
template <typename... Types>                                                    \
constexpr bool operator OP(                                                     \
	variant<Types...> const& lhs, variant<Types...> const& rhs)                 \
{                                                                               \
	bool ret = true;                                                            \
	variant_detail::VariantRelopVisitor<PRED, bool, Types...> visitor{lhs, ret};\
	variant_detail::raw_idx_visit(visitor, rhs);                                \
	return ret;                                                                 \
}

BKSGE_VARIANT_RELATION_FUNCTION_TEMPLATE(==, bksge::ranges::equal_to)
BKSGE_VARIANT_RELATION_FUNCTION_TEMPLATE(!=, bksge::ranges::not_equal_to)
BKSGE_VARIANT_RELATION_FUNCTION_TEMPLATE(<,  bksge::ranges::less)
BKSGE_VARIANT_RELATION_FUNCTION_TEMPLATE(>,  bksge::ranges::greater)
BKSGE_VARIANT_RELATION_FUNCTION_TEMPLATE(<=, bksge::ranges::less_equal)
BKSGE_VARIANT_RELATION_FUNCTION_TEMPLATE(>=, bksge::ranges::greater_equal)

#undef BKSGE_VARIANT_RELATION_FUNCTION_TEMPLATE


#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename... Types>
requires (bksge::three_way_comparable<Types> && ...)
constexpr
bksge::common_comparison_category_t<bksge::compare_three_way_result_t<Types>...>
operator<=>(variant<Types...> const& lhs, variant<Types...> const& rhs)
{
	using result_type = bksge::common_comparison_category_t<
		bksge::compare_three_way_result_t<Types>...>;
	result_type ret = bksge::strong_ordering::equal;
	variant_detail::VariantRelopVisitor<bksge::compare_three_way, result_type, Types...> visitor{lhs, ret};
	variant_detail::raw_idx_visit(visitor, rhs);
	return ret;
}

#endif

template <typename... Types>
inline bksge::enable_if_t<bksge::conjunction<
	bksge::is_move_constructible<Types>...,
	bksge::is_swappable<Types>...
>::value>
swap(variant<Types...>& lhs, variant<Types...>& rhs)
	noexcept(noexcept(lhs.swap(rhs)))
{
	lhs.swap(rhs);
}

template <typename... Types>
bksge::enable_if_t<!bksge::conjunction<
	bksge::is_move_constructible<Types>...,
	bksge::is_swappable<Types>...
>::value>
swap(variant<Types...>&, variant<Types...>&) = delete;

namespace variant_detail
{

template <bool, typename... Types>
struct variant_hash_call_base_impl
{
private:
	struct variant_hash_visitor
	{
	public:
		std::size_t&             m_ret;
		variant<Types...> const& m_var;

	private:
		template <typename VarMem>
		void impl(VarMem&& /*var_mem*/, bksge::true_type)
		{
			m_ret = std::hash<std::size_t>{}(m_var.index());
		}

		template <typename VarMem>
		void impl(VarMem&& var_mem, bksge::false_type)
		{
			using Type = bksge::remove_cvref_t<VarMem>;
			m_ret = std::hash<std::size_t>{}(m_var.index()) + std::hash<Type>{}(var_mem);
		}

	public:
		template <typename VarMem>
		void operator()(VarMem&& var_mem)
		{
			using Type = bksge::remove_cvref_t<VarMem>;
			impl(bksge::forward<VarMem>(var_mem),
				bksge::is_same<Type, variant_detail::VariantCookie>{});
		}
	};

public:
	std::size_t operator()(variant<Types...> const& var) const
		noexcept((bksge::conjunction<
			bksge::is_nothrow_invocable<std::hash<bksge::decay_t<Types>>, Types>...>::value))
	{
		std::size_t ret;
		variant_detail::raw_visit(variant_hash_visitor{ret, var}, var);
		return ret;
	}
};

template <typename... Types>
struct variant_hash_call_base_impl<false, Types...>
{
private:
	// Private rather than deleted to be non-trivially-copyable.
	variant_hash_call_base_impl(variant_hash_call_base_impl&&);
	~variant_hash_call_base_impl();
};

template <typename... Types>
using variant_hash_call_base =
	variant_hash_call_base_impl<
		bksge::conjunction<bksge::detail::enable_hash_call<Types>...>::value,
		Types...>;

}	// namespace variant_detail

}	// namespace bksge

namespace std
{

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4624);	// destructor was implicitly defined as deleted

template <typename... Types>
struct hash<bksge::variant<Types...>>
	: public bksge::variant_detail::variant_hash_call_base<Types...>
{};

BKSGE_WARNING_POP();

}	// namespace std

#endif	// defined(BKSGE_HAS_STD_VARIANT)

#endif // BKSGE_FND_VARIANT_VARIANT_HPP
