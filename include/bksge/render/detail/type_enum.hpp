/**
 *	@file	type_enum.hpp
 *
 *	@brief	TypeEnum の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_RENDER_DETAIL_TYPE_ENUM_HPP
#define BKSGE_RENDER_DETAIL_TYPE_ENUM_HPP

#include <bksge/render/detail/fwd/type_enum_fwd.hpp>
#include <cstddef>
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
	kByte,
	kUnsignedByte,
	kShort,
	kUnsignedShort,
	kInt,
	kUnsignedInt,
	kFloat,
};

/**
 *	@brief	型をTypeEnumに変換
 */
template <typename T> struct TypeToEnum;
template <> struct TypeToEnum<signed char>
{
	static TypeEnum const value = TypeEnum::kByte;
};
template <> struct TypeToEnum<unsigned char>
{
	static TypeEnum const value = TypeEnum::kUnsignedByte;
};
template <> struct TypeToEnum<signed short>
{
	static TypeEnum const value = TypeEnum::kShort;
};
template <> struct TypeToEnum<unsigned short>
{
	static TypeEnum const value = TypeEnum::kUnsignedShort;
};
template <> struct TypeToEnum<signed int>
{
	static TypeEnum const value = TypeEnum::kInt;
};
template <> struct TypeToEnum<unsigned int>
{
	static TypeEnum const value = TypeEnum::kUnsignedInt;
};
template <> struct TypeToEnum<float>
{
	static TypeEnum const value = TypeEnum::kFloat;
};

/**
 *	@brief	TypeEnumを型に変換
 */
template <TypeEnum type> struct EnumToType;
template <> struct EnumToType<TypeEnum::kByte>
{
	using type = signed char;
};
template <> struct EnumToType<TypeEnum::kUnsignedByte>
{
	using type = unsigned char;
};
template <> struct EnumToType<TypeEnum::kShort>
{
	using type = signed short;
};
template <> struct EnumToType<TypeEnum::kUnsignedShort>
{
	using type = unsigned short;
};
template <> struct EnumToType<TypeEnum::kInt>
{
	using type = signed int;
};
template <> struct EnumToType<TypeEnum::kUnsignedInt>
{
	using type = unsigned int;
};
template <> struct EnumToType<TypeEnum::kFloat>
{
	using type = float;
};

/**
 *	@brief	TypeEnumから型のバイト数を取得
 */
std::size_t GetSizeOf(TypeEnum type_enum);

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

#include <bksge/config.hpp>
#if defined(BKSGE_HEADER_ONLY)
#include <bksge/render/detail/inl/type_enum_inl.hpp>
#endif

#endif // BKSGE_RENDER_DETAIL_TYPE_ENUM_HPP
