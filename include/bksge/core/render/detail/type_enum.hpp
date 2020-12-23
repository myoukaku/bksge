/**
 *	@file	type_enum.hpp
 *
 *	@brief	TypeEnum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_RENDER_DETAIL_TYPE_ENUM_HPP
#define BKSGE_CORE_RENDER_DETAIL_TYPE_ENUM_HPP

#include <bksge/core/render/detail/fwd/type_enum_fwd.hpp>
#include <bksge/fnd/type_traits/is_signed.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstdint.hpp>
#include <ostream>
#include <string>

namespace bksge
{

namespace render
{

/**
 *	@brief	型をレンダリングAPIに渡すためのenum
 */
enum class TypeEnum
{
	kSInt8,
	kUInt8,
	kSInt16,
	kUInt16,
	kSInt32,
	kUInt32,
	kFloat,
};

/**
 *	@brief	型をTypeEnumに変換
 */
template <typename T>
struct TypeToEnum
{
private:
	template <typename U, bool, bksge::size_t>
	struct Helper;

	template <typename U> struct Helper<U, true,  1> { static TypeEnum const value = TypeEnum::kSInt8; };
	template <typename U> struct Helper<U, false, 1> { static TypeEnum const value = TypeEnum::kUInt8; };
	template <typename U> struct Helper<U, true,  2> { static TypeEnum const value = TypeEnum::kSInt16; };
	template <typename U> struct Helper<U, false, 2> { static TypeEnum const value = TypeEnum::kUInt16; };
	template <typename U> struct Helper<U, true,  4> { static TypeEnum const value = TypeEnum::kSInt32; };
	template <typename U> struct Helper<U, false, 4> { static TypeEnum const value = TypeEnum::kUInt32; };

public:
	static TypeEnum const value = Helper<T, bksge::is_signed<T>::value, sizeof(T)>::value;
};

template <>
struct TypeToEnum<float>
{
	static TypeEnum const value = TypeEnum::kFloat;
};

/**
 *	@brief	TypeEnumを型に変換
 */
template <TypeEnum type> struct EnumToType;
template <> struct EnumToType<TypeEnum::kSInt8>
{
	using type = bksge::int8_t;
};
template <> struct EnumToType<TypeEnum::kUInt8>
{
	using type = bksge::uint8_t;
};
template <> struct EnumToType<TypeEnum::kSInt16>
{
	using type = bksge::int16_t;
};
template <> struct EnumToType<TypeEnum::kUInt16>
{
	using type = bksge::uint16_t;
};
template <> struct EnumToType<TypeEnum::kSInt32>
{
	using type = bksge::int32_t;
};
template <> struct EnumToType<TypeEnum::kUInt32>
{
	using type = bksge::uint32_t;
};
template <> struct EnumToType<TypeEnum::kFloat>
{
	using type = float;
};

/**
 *	@brief	TypeEnumから型のバイト数を取得
 */
bksge::size_t GetSizeOf(TypeEnum type_enum);

/**
 *	@brief	文字列への変換
 */
std::string to_string(TypeEnum const& type_enum);

/**
 *	@brief	ストリームへの出力
 */
template <typename CharT, typename Traits>
inline std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os, TypeEnum const& rhs)
{
	return os << to_string(rhs).c_str();
}

}	// namespace render

}	// namespace bksge

#if BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/type_traits/underlying_type.hpp>
#include <functional>

namespace std
{

template<>
struct hash<bksge::render::TypeEnum>
{
	bksge::size_t operator()(bksge::render::TypeEnum const& arg) const
	{
		using type = bksge::underlying_type_t<bksge::render::TypeEnum>;
		return std::hash<type>{}(static_cast<type>(arg));
	}
};

}	// namespace std

#endif // BKSGE_CXX_STANDARD <= 11

#include <bksge/fnd/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/core/render/detail/inl/type_enum_inl.hpp>
#endif

#endif // BKSGE_CORE_RENDER_DETAIL_TYPE_ENUM_HPP
