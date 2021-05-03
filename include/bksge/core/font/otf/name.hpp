/**
 *	@file	name.hpp
 *
 *	@brief	NamingTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_NAME_HPP
#define BKSGE_CORE_FONT_OTF_NAME_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct NamingTable
{
	struct NameRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			NameRecord* dst,
			char const* stringStorage)
		{
			uint16		length;
			Offset16	stringOffset;
			ptr = ReadBigEndian(ptr, &dst->platformID);
			ptr = ReadBigEndian(ptr, &dst->encodingID);
			ptr = ReadBigEndian(ptr, &dst->languageID);
			ptr = ReadBigEndian(ptr, &dst->nameID);
			ptr = ReadBigEndian(ptr, &length);
			ptr = ReadBigEndian(ptr, &stringOffset);
			dst->str = bksge::string(stringStorage + stringOffset, length);
			return ptr;
		}

		uint16			platformID;
		uint16			encodingID;
		uint16			languageID;
		uint16			nameID;
		bksge::string	str;
	};

	struct LangTagRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			LangTagRecord* dst,
			char const* stringStorage)
		{
			uint16		length;
			Offset16	langTagOffset;

			ptr = ReadBigEndian(ptr, &length);
			ptr = ReadBigEndian(ptr, &langTagOffset);
			dst->str = bksge::string(stringStorage + langTagOffset, length);
			return ptr;
		}

		bksge::string	str;
	};

	explicit NamingTable(bksge::uint8_t const* ptr)
	{
		auto const start = ptr;
		uint16		count;
		Offset16	storageOffset;
		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &count);
		ptr = ReadBigEndian(ptr, &storageOffset);
		char const* stringStorage =
			reinterpret_cast<char const*>(start + storageOffset);
		nameRecord.resize(count);
		ptr = ReadBigEndian(ptr, &nameRecord, stringStorage);

		if (version < 1)
		{
			return;
		}

		uint16	langTagCount = 0;
		ptr = ReadBigEndian(ptr, &langTagCount);
		langTagRecord.resize(langTagCount);
		ptr = ReadBigEndian(ptr, &langTagRecord, stringStorage);
	}

	// Version 0
	uint16							version;
	bksge::vector<NameRecord>		nameRecord;
	// Version 1
	bksge::vector<LangTagRecord>	langTagRecord;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_NAME_HPP
