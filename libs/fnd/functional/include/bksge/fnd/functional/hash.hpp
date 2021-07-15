/**
 *	@file	hash.hpp
 *
 *	@brief	hash クラステンプレートの定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_FUNCTIONAL_HASH_HPP
#define BKSGE_FND_FUNCTIONAL_HASH_HPP

#include <bksge/fnd/functional/config.hpp>

#if defined(BKSGE_USE_STD_HASH)

#include <functional>

namespace bksge
{

using std::hash;

}	// namespace bksge

#else

#include <bksge/fnd/bit/bit_cast.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/type_traits/conditional.hpp>
#include <bksge/fnd/type_traits/is_enum.hpp>
#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <bksge/fnd/config.hpp>
#include <cstddef>

namespace bksge
{

template <typename T>
struct hash;

namespace detail
{

template <typename T>
struct poison_hash
{
private:
	// Private rather than deleted to be non-trivially-copyable.
	poison_hash(poison_hash&&);
	~poison_hash();
};

template <typename T>
struct hash_enum
{
	BKSGE_CONSTEXPR std::size_t
	operator()(T val) const BKSGE_NOEXCEPT
	{
		using type = bksge::underlying_type_t<T>;
		return hash<type>{}(static_cast<type>(val));
	}
};

inline BKSGE_CONSTEXPR std::size_t
hash_fnv_impl(std::size_t ret) BKSGE_NOEXCEPT
{
	return ret;
}
template <typename... Args>
inline BKSGE_CONSTEXPR std::size_t
hash_fnv_impl(std::size_t ret, std::size_t arg0, Args const&... args) BKSGE_NOEXCEPT
{
	return hash_fnv_impl((ret * 0x01000193) ^ arg0, args...);
}
template <typename... Args>
inline BKSGE_CONSTEXPR std::size_t
hash_fnv(Args const&... args) BKSGE_NOEXCEPT
{
	return hash_fnv_impl(0x811c9dc5, args...);
}

template <typename T, std::size_t = sizeof(T), std::size_t = sizeof(std::size_t)>
struct hash_representation_impl
{
	static BKSGE_CONSTEXPR std::size_t hash(T val) BKSGE_NOEXCEPT
	{
		return static_cast<std::size_t>(val);
	}
};

template <typename T>
struct hash_representation_impl<T, 8, 4>
{
	static BKSGE_CONSTEXPR std::size_t hash(T val) BKSGE_NOEXCEPT
	{
		return hash_fnv(
			static_cast<std::size_t>(val >> 32),
			static_cast<std::size_t>(val));
	}
};

template <typename T>
BKSGE_CONSTEXPR std::size_t
hash_representation(T const& val) BKSGE_NOEXCEPT
{
	return hash_representation_impl<T>::hash(val);
}

}	// namespace detail

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4624);	// destructor was implicitly defined as deleted

template <typename T>
struct hash : public bksge::conditional_t<
	bksge::is_enum<T>::value, detail::hash_enum<T>, detail::poison_hash<T>>
{};

BKSGE_WARNING_POP();

template <typename T>
struct hash<T*>
{
	/*BKSGE_CONSTEXPR*/ std::size_t
	operator()(T* p) const BKSGE_NOEXCEPT
	{
		return detail::hash_representation(reinterpret_cast<bksge::uintptr_t>(p));
	}
};

#define BKSGE_DEFINE_TRIVIAL_HASH(T)                 \
	template <>                                      \
	struct hash<T>                                   \
	{                                                \
		BKSGE_CONSTEXPR std::size_t                \
		operator()(T val) const BKSGE_NOEXCEPT       \
		{                                            \
			return detail::hash_representation(val); \
		}                                            \
	}

BKSGE_DEFINE_TRIVIAL_HASH(bool);
BKSGE_DEFINE_TRIVIAL_HASH(char);
BKSGE_DEFINE_TRIVIAL_HASH(wchar_t);
#if defined(BKSGE_HAS_CXX20_CHAR8_T)
BKSGE_DEFINE_TRIVIAL_HASH(char8_t);
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
BKSGE_DEFINE_TRIVIAL_HASH(char16_t);
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
BKSGE_DEFINE_TRIVIAL_HASH(char32_t);
#endif
BKSGE_DEFINE_TRIVIAL_HASH(signed char);
BKSGE_DEFINE_TRIVIAL_HASH(signed short);
BKSGE_DEFINE_TRIVIAL_HASH(signed int);
BKSGE_DEFINE_TRIVIAL_HASH(signed long);
BKSGE_DEFINE_TRIVIAL_HASH(signed long long);
BKSGE_DEFINE_TRIVIAL_HASH(unsigned char);
BKSGE_DEFINE_TRIVIAL_HASH(unsigned short);
BKSGE_DEFINE_TRIVIAL_HASH(unsigned int);
BKSGE_DEFINE_TRIVIAL_HASH(unsigned long);
BKSGE_DEFINE_TRIVIAL_HASH(unsigned long long);

#undef BKSGE_DEFINE_TRIVIAL_HASH

namespace detail
{

template <typename T, std::size_t = sizeof(T)>
struct hash_float;

template <typename T>
struct hash_float<T, 1>
{
	static BKSGE_CXX20_CONSTEXPR std::size_t hash(T val) BKSGE_NOEXCEPT
	{
		return detail::hash_representation(bksge::bit_cast<bksge::uint8_t>(val));
	}
};
template <typename T>
struct hash_float<T, 2>
{
	static BKSGE_CXX20_CONSTEXPR std::size_t hash(T val) BKSGE_NOEXCEPT
	{
		return detail::hash_representation(bksge::bit_cast<bksge::uint16_t>(val));
	}
};
template <typename T>
struct hash_float<T, 4>
{
	static BKSGE_CXX20_CONSTEXPR std::size_t hash(T val) BKSGE_NOEXCEPT
	{
		return detail::hash_representation(bksge::bit_cast<bksge::uint32_t>(val));
	}
};
template <typename T>
struct hash_float<T, 8>
{
	static BKSGE_CXX20_CONSTEXPR std::size_t hash(T val) BKSGE_NOEXCEPT
	{
		return detail::hash_representation(bksge::bit_cast<bksge::uint64_t>(val));
	}
};
template <typename T>
struct hash_float<T, 16>
{
	static BKSGE_CXX20_CONSTEXPR std::size_t hash(T val) BKSGE_NOEXCEPT
	{
		struct Dummy { bksge::uint32_t a[4]; };
		auto const t = bksge::bit_cast<Dummy>(val);
		return detail::hash_fnv(t.a[0], t.a[1], t.a[2], t.a[3]);
	}
};

}	// namespace detail

template <>
struct hash<float>
{
	BKSGE_CXX20_CONSTEXPR std::size_t
	operator()(float val) const BKSGE_NOEXCEPT
	{
		// 0 and -0 both hash to zero.
		return detail::hash_float<float>::hash(val == 0.0f ? 0.0f : val);
	}
};

template <>
struct hash<double>
{
	BKSGE_CXX20_CONSTEXPR std::size_t
	operator()(double val) const BKSGE_NOEXCEPT
	{
		// 0 and -0 both hash to zero.
		return detail::hash_float<double>::hash(val == 0.0 ? 0.0 : val);
	}
};

template <>
struct hash<long double>
{
	BKSGE_CXX20_CONSTEXPR std::size_t
	operator()(long double val) const BKSGE_NOEXCEPT
	{
		// 0 and -0 both hash to zero.
		return detail::hash_float<long double>::hash(val == 0.0L ? 0.0L : val);
	}
};

template <>
struct hash<bksge::nullptr_t>
{
	BKSGE_CONSTEXPR std::size_t
	operator()(bksge::nullptr_t) const BKSGE_NOEXCEPT
	{
		return detail::hash_representation(0u);
	}
};

}	// namespace bksge

#endif

#endif // BKSGE_FND_FUNCTIONAL_HASH_HPP
