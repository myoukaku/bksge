/**
 *	@file	script_list.hpp
 *
 *	@brief	ScriptList の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_SCRIPT_LIST_HPP
#define BKSGE_CORE_FONT_OTF_SCRIPT_LIST_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/vector.hpp>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct ScriptList
{
	struct LangSys
	{
		explicit LangSys(std::uint8_t const* ptr)
		{
			Offset16	lookupOrderOffset;
			uint16		featureIndexCount;

			ptr = ReadBigEndian(ptr, &lookupOrderOffset);
			ptr = ReadBigEndian(ptr, &requiredFeatureIndex);
			ptr = ReadBigEndian(ptr, &featureIndexCount);
			featureIndices.resize(featureIndexCount);
			ptr = ReadBigEndian(ptr, &featureIndices);
		}

		uint16					requiredFeatureIndex;
		bksge::vector<uint16>	featureIndices;
	};

	struct LangSysRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			LangSysRecord* dst,
			std::uint8_t const* start)
		{
			Offset16 langSysOffset;

			ptr = ReadBigEndian(ptr, &dst->langSysTag);
			ptr = ReadBigEndian(ptr, &langSysOffset);

			dst->langSys = bksge::make_unique<LangSys>(
				start + langSysOffset);

			return ptr;
		}

		Tag							langSysTag;
		bksge::unique_ptr<LangSys>	langSys;
	};

	struct Script
	{
		explicit Script(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	defaultLangSysOffset;
			uint16		langSysCount;

			ptr = ReadBigEndian(ptr, &defaultLangSysOffset);
			ptr = ReadBigEndian(ptr, &langSysCount);
			langSysRecords.resize(langSysCount);
			ptr = ReadBigEndian(ptr, &langSysRecords, start);

			if (defaultLangSysOffset != 0)
			{
				defaultLangSys = bksge::make_unique<LangSys>(
					start + defaultLangSysOffset);
			}
		}

		bksge::unique_ptr<LangSys>		defaultLangSys;
		bksge::vector<LangSysRecord>	langSysRecords;
	};

	struct ScriptRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			ScriptRecord* dst,
			std::uint8_t const* start)
		{
			Offset16 scriptOffset;

			ptr = ReadBigEndian(ptr, &dst->scriptTag);
			ptr = ReadBigEndian(ptr, &scriptOffset);

			dst->script = bksge::make_unique<Script>(
				start + scriptOffset);

			return ptr;
		}

		Tag							scriptTag;
		bksge::unique_ptr<Script>	script;
	};

	explicit ScriptList(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16 scriptCount;
		ptr = ReadBigEndian(ptr, &scriptCount);
		scriptRecords.resize(scriptCount);
		ptr = ReadBigEndian(ptr, &scriptRecords, start);
	}

	bksge::vector<ScriptRecord>	scriptRecords;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_SCRIPT_LIST_HPP
