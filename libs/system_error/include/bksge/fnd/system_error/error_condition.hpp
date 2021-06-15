/**
 *	@file	error_condition.hpp
 *
 *	@brief	error_condition の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_SYSTEM_ERROR_ERROR_CONDITION_HPP
#define BKSGE_FND_SYSTEM_ERROR_ERROR_CONDITION_HPP

#include <bksge/fnd/system_error/config.hpp>

#if defined(BKSGE_USE_STD_SYSTEM_ERROR)

#include <system_error>

namespace bksge
{

using std::error_condition;

}	// namespace bksge

#else

#include <bksge/fnd/system_error/is_error_condition_enum.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/compare/strong_ordering.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/config.hpp>

namespace bksge
{

class error_category;

class error_condition
{
public:
	error_condition() BKSGE_NOEXCEPT;

	error_condition(int val, error_category const& cat) BKSGE_NOEXCEPT;

	template <typename E, typename = bksge::enable_if_t<is_error_condition_enum<E>::value>>
	error_condition(E e) BKSGE_NOEXCEPT;

	void assign(int val, error_category const& cat) BKSGE_NOEXCEPT;

	template <typename E, typename = bksge::enable_if_t<is_error_condition_enum<E>::value>>
	error_condition& operator=(E e) BKSGE_NOEXCEPT;

	void clear() BKSGE_NOEXCEPT;

	int value() const BKSGE_NOEXCEPT;

	error_category const& category() const BKSGE_NOEXCEPT;

	bksge::string message() const;

	explicit operator bool() const BKSGE_NOEXCEPT;

private:
	int                   m_val;
	error_category const* m_cat;
};

bool operator==(error_condition const& lhs, error_condition const& rhs) BKSGE_NOEXCEPT;
#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)
bksge::strong_ordering operator<=>(error_condition const& lhs, error_condition const& rhs) BKSGE_NOEXCEPT;
#else
bool operator!=(error_condition const& lhs, error_condition const& rhs) BKSGE_NOEXCEPT;
bool operator< (error_condition const& lhs, error_condition const& rhs) BKSGE_NOEXCEPT;
#endif

}	// namespace bksge

#include <bksge/fnd/system_error/inl/error_condition_inl.hpp>

#endif

#if !defined(BKSGE_USE_STD_SYSTEM_ERROR) || !defined(BKSGE_USE_STD_HASH)

#include <bksge/fnd/functional/hash.hpp>

namespace BKSGE_HASH_NAMESPACE
{

template <>
struct hash<bksge::error_condition>
{
	/*BKSGE_CXX14_CONSTEXPR*/ bksge::size_t
	operator()(bksge::error_condition const& ec) const BKSGE_NOEXCEPT
	{
		return static_cast<bksge::size_t>(ec.value());
	}
};

}	// namespace BKSGE_HASH_NAMESPACE

#endif

#endif // BKSGE_FND_SYSTEM_ERROR_ERROR_CONDITION_HPP
