/**
 *	@file	cmap.hpp
 *
 *	@brief	CMapTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_CMAP_HPP
#define BKSGE_CORE_FONT_OTF_CMAP_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/variant.hpp>
#include <cstddef>
#include <cstdint>

namespace bksge
{

namespace otf
{

struct CMapTable
{
	struct Subtable
	{
		struct Format0
		{
			static Format0 Create(std::uint8_t const* ptr)
			{
				Format0 result;
				ptr = ReadBigEndian(ptr, &result.length);
				ptr = ReadBigEndian(ptr, &result.language);
				ptr = ReadBigEndian(ptr, &result.glyphIdArray);
				return result;
			}

			std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
			{
				(void)char_code;
				return 0;
			}

			uint16	length;
			uint16	language;
			uint8	glyphIdArray[256];
		};

		struct Format2
		{
			struct SubHeader
			{
				uint16	firstCode;
				uint16	entryCount;
				int16	idDelta;
				uint16	idRangeOffset;
			};

			static Format2 Create(std::uint8_t const* ptr)
			{
				Format2 result;
				ptr = ReadBigEndian(ptr, &result.length);
				ptr = ReadBigEndian(ptr, &result.language);
				ptr = ReadBigEndian(ptr, &result.subHeaderKeys);
				// TODO subHeaders
				// TODO glyphIdArray

				return result;
			}

			std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
			{
				(void)char_code;
				return 0;
			}

			uint16	length;
			uint16	language;
			uint16	subHeaderKeys[256];
			bksge::vector<SubHeader>	subHeaders;		// subHeaders[]
			bksge::vector<uint16>		glyphIdArray;	// glyphIdArray[]
		};

		struct Format4
		{
			static Format4 Create(std::uint8_t const* ptr)
			{
				auto const start = ptr;

				Format4 result;

				ptr = ReadBigEndian(ptr, &result.length);
				ptr = ReadBigEndian(ptr, &result.language);
				ptr = ReadBigEndian(ptr, &result.segCountX2);
				ptr = ReadBigEndian(ptr, &result.searchRange);
				ptr = ReadBigEndian(ptr, &result.entrySelector);
				ptr = ReadBigEndian(ptr, &result.rangeShift);

				uint16 const segCount = result.segCountX2 / 2;

				result.endCode.resize(segCount);
				ptr = ReadBigEndian(ptr, &result.endCode);

				uint16	reservedPad;
				ptr = ReadBigEndian(ptr, &reservedPad);

				result.startCode.resize(segCount);
				ptr = ReadBigEndian(ptr, &result.startCode);

				result.idDelta.resize(segCount);
				ptr = ReadBigEndian(ptr, &result.idDelta);

				result.idRangeOffsets.resize(segCount);
				ptr = ReadBigEndian(ptr, &result.idRangeOffsets);

				auto const end = start + result.length;
				result.glyphIdArray.resize((end - ptr) / 2);
				ptr = ReadBigEndian(ptr, &result.glyphIdArray);

				return result;
			}

			std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
			{
				auto const segCount = endCode.size();
				for (std::size_t i = 0; i < segCount; ++i)
				{
					if (char_code <= endCode[i])
					{
						if (char_code < startCode[i])
						{
							return 0;
						}

						auto const offset = idRangeOffsets[i];
						if (offset == 0)
						{
							return (char_code + idDelta[i]) & 0xFFFF;
						}

						auto const index = offset / 2 - segCount + i + (char_code - startCode[i]);
						return glyphIdArray[index];
					}
				}

				return 0;
			}

			uint16	length;
			uint16	language;
			uint16	segCountX2;
			uint16	searchRange;
			uint16	entrySelector;
			uint16	rangeShift;
			bksge::vector<uint16>	endCode;
			bksge::vector<uint16>	startCode;
			bksge::vector<int16>	idDelta;
			bksge::vector<uint16>	idRangeOffsets;
			bksge::vector<uint16>	glyphIdArray;
		};

		struct Format6
		{
			static Format6 Create(std::uint8_t const* ptr)
			{
				Format6 result;

				uint16	entryCount;
				ptr = ReadBigEndian(ptr, &result.length);
				ptr = ReadBigEndian(ptr, &result.language);
				ptr = ReadBigEndian(ptr, &result.firstCode);
				ptr = ReadBigEndian(ptr, &entryCount);
				result.glyphIdArray.resize(entryCount);
				ptr = ReadBigEndian(ptr, &result.glyphIdArray);

				return result;
			}

			std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
			{
				(void)char_code;
				return 0;
			}

			uint16					length;
			uint16					language;
			uint16					firstCode;
			bksge::vector<uint16>	glyphIdArray;
		};

		struct Format8
		{
			struct SequentialMapGroup
			{
				friend std::uint8_t const*
				ReadBigEndian(std::uint8_t const* ptr, SequentialMapGroup* dst)
				{
					ptr = ReadBigEndian(ptr, &dst->startCharCode);
					ptr = ReadBigEndian(ptr, &dst->endCharCode);
					ptr = ReadBigEndian(ptr, &dst->startGlyphID);
					return ptr;
				}

				uint32	startCharCode;
				uint32	endCharCode;
				uint32	startGlyphID;
			};

			static Format8 Create(std::uint8_t const* ptr)
			{
				Format8 result;

				uint16	reserved;
				uint32	numGroups;
				ptr = ReadBigEndian(ptr, &reserved);
				ptr = ReadBigEndian(ptr, &result.length);
				ptr = ReadBigEndian(ptr, &result.language);
				ptr = ReadBigEndian(ptr, &result.is32);
				ptr = ReadBigEndian(ptr, &numGroups);
				result.groups.resize(numGroups);
				ptr = ReadBigEndian(ptr, &result.groups);

				return result;
			}

			std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
			{
				(void)char_code;
				return 0;
			}

			using SequentialMapGroups = bksge::vector<SequentialMapGroup>;

			uint32				length;
			uint32				language;
			uint8				is32[8192];
			SequentialMapGroups	groups;
		};

		struct Format10
		{
			static Format10 Create(std::uint8_t const* ptr)
			{
				Format10 result;

				uint16	reserved;
				ptr = ReadBigEndian(ptr, &reserved);
				ptr = ReadBigEndian(ptr, &result.length);
				ptr = ReadBigEndian(ptr, &result.language);
				ptr = ReadBigEndian(ptr, &result.startCharCode);
				ptr = ReadBigEndian(ptr, &result.numChars);
				// TODO glyphIdArray

				return result;
			}

			std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
			{
				(void)char_code;
				return 0;
			}

			uint32	length;
			uint32	language;
			uint32	startCharCode;
			uint32	numChars;
			bksge::vector<uint16>	glyphIdArray;	// glyphIdArray[];
		};

		struct Format12
		{
			struct SequentialMapGroup
			{
				friend std::uint8_t const*
				ReadBigEndian(std::uint8_t const* ptr, SequentialMapGroup* dst)
				{
					ptr = ReadBigEndian(ptr, &dst->startCharCode);
					ptr = ReadBigEndian(ptr, &dst->endCharCode);
					ptr = ReadBigEndian(ptr, &dst->startGlyphID);
					return ptr;
				}

				uint32	startCharCode;
				uint32	endCharCode;
				uint32	startGlyphID;
			};

			static Format12 Create(std::uint8_t const* ptr)
			{
				Format12 result;

				uint16	reserved;
				uint32	numGroups;
				ptr = ReadBigEndian(ptr, &reserved);
				ptr = ReadBigEndian(ptr, &result.length);
				ptr = ReadBigEndian(ptr, &result.language);
				ptr = ReadBigEndian(ptr, &numGroups);
				result.groups.resize(numGroups);
				ptr = ReadBigEndian(ptr, &result.groups);

				return result;
			}

			std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
			{
				(void)char_code;
				return 0;
			}

			using SequentialMapGroups = bksge::vector<SequentialMapGroup>;

			uint32				length;
			uint32				language;
			SequentialMapGroups	groups;
		};

		struct Format13
		{
			struct ConstantMapGroup
			{
				friend std::uint8_t const*
				ReadBigEndian(std::uint8_t const* ptr, ConstantMapGroup* dst)
				{
					ptr = ReadBigEndian(ptr, &dst->startCharCode);
					ptr = ReadBigEndian(ptr, &dst->endCharCode);
					ptr = ReadBigEndian(ptr, &dst->glyphID);
					return ptr;
				}

				uint32	startCharCode;
				uint32	endCharCode;
				uint32	glyphID;
			};

			static Format13 Create(std::uint8_t const* ptr)
			{
				Format13 result;

				uint16	reserved;
				uint32	numGroups;
				ptr = ReadBigEndian(ptr, &reserved);
				ptr = ReadBigEndian(ptr, &result.length);
				ptr = ReadBigEndian(ptr, &result.language);
				ptr = ReadBigEndian(ptr, &numGroups);
				result.groups.resize(numGroups);
				ptr = ReadBigEndian(ptr, &result.groups);

				return result;
			}

			std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
			{
				(void)char_code;
				return 0;
			}

			using ConstantMapGroups = bksge::vector<ConstantMapGroup>;

			uint32				length;
			uint32				language;
			ConstantMapGroups	groups;
		};

		struct Format14
		{
			struct DefaultUVS
			{
				struct UnicodeRange
				{
					friend std::uint8_t const*
					ReadBigEndian(std::uint8_t const* ptr, UnicodeRange* dst)
					{
						uint24	startUnicodeValue24;
						ptr = ReadBigEndian(ptr, &startUnicodeValue24);
						ptr = ReadBigEndian(ptr, &dst->additionalCount);
						dst->startUnicodeValue = startUnicodeValue24;
						return ptr;
					}

					uint32	startUnicodeValue;
					uint8	additionalCount;
				};

				explicit DefaultUVS(std::uint8_t const* ptr)
				{
					uint32	numUnicodeValueRanges;
					ptr = ReadBigEndian(ptr, &numUnicodeValueRanges);
					ranges.resize(numUnicodeValueRanges);
					ptr = ReadBigEndian(ptr, &ranges);
				}

				bksge::vector<UnicodeRange>	ranges;
			};

			struct NonDefaultUVS
			{
				struct UVSMapping
				{
					friend std::uint8_t const*
					ReadBigEndian(std::uint8_t const* ptr, UVSMapping* dst)
					{
						uint24	unicodeValue24;
						ptr = ReadBigEndian(ptr, &unicodeValue24);
						ptr = ReadBigEndian(ptr, &dst->glyphID);
						dst->unicodeValue = unicodeValue24;
						return ptr;
					}

					uint32	unicodeValue;
					uint16	glyphID;
				};

				explicit NonDefaultUVS(std::uint8_t const* ptr)
				{
					uint32	numUVSMappings;
					ptr = ReadBigEndian(ptr, &numUVSMappings);
					uvsMappings.resize(numUVSMappings);
					ptr = ReadBigEndian(ptr, &uvsMappings);
				}

				bksge::vector<UVSMapping>	uvsMappings;
			};

			struct VariationSelector
			{
				friend std::uint8_t const*
				ReadBigEndian(
					std::uint8_t const* ptr,
					VariationSelector* dst,
					std::uint8_t const* start)
				{
					uint24		varSelector24;
					Offset32	defaultUVSOffset;
					Offset32	nonDefaultUVSOffset;

					ptr = ReadBigEndian(ptr, &varSelector24);
					ptr = ReadBigEndian(ptr, &defaultUVSOffset);
					ptr = ReadBigEndian(ptr, &nonDefaultUVSOffset);

					dst->varSelector = varSelector24;

					if (defaultUVSOffset != 0)
					{
						dst->defaultUVS = bksge::make_unique<DefaultUVS>(
							start + defaultUVSOffset);
					}
					if (nonDefaultUVSOffset != 0)
					{
						dst->nonDefaultUVS = bksge::make_unique<NonDefaultUVS>(
							start + nonDefaultUVSOffset);
					}

					return ptr;
				}

				uint32								varSelector;
				bksge::unique_ptr<DefaultUVS>		defaultUVS;
				bksge::unique_ptr<NonDefaultUVS>	nonDefaultUVS;
			};

			static Format14 Create(
				std::uint8_t const* ptr, std::uint8_t const* start)
			{
				Format14 result;

				uint32	numVarSelectorRecords;
				ptr = ReadBigEndian(ptr, &result.length);
				ptr = ReadBigEndian(ptr, &numVarSelectorRecords);
				result.varSelector.resize(numVarSelectorRecords);
				ptr = ReadBigEndian(ptr, &result.varSelector, start);

				return result;
			}

			std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
			{
				(void)char_code;
				return 0;
			}

			uint32								length;
			bksge::vector<VariationSelector>	varSelector;
		};

		explicit Subtable(std::uint8_t const* ptr)
		{
			auto const start = ptr;

			uint16	format;
			ptr = ReadBigEndian(ptr, &format);
			switch (format)
			{
			case  0: value = Format0::Create(ptr); break;
			case  2: value = Format2::Create(ptr); break;
			case  4: value = Format4::Create(ptr); break;
			case  6: value = Format6::Create(ptr); break;
			case  8: value = Format8::Create(ptr); break;
			case 10: value = Format10::Create(ptr); break;
			case 12: value = Format12::Create(ptr); break;
			case 13: value = Format13::Create(ptr); break;
			case 14: value = Format14::Create(ptr, start); break;
			}
		}

		struct GetGlyphIndexVisitor
		{
			std::uint32_t m_char_code;

			template <typename T>
			std::uint16_t operator()(T const& v)
			{
				return v.GetGlyphIndex(m_char_code);
			}
		};

		std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
		{
			return bksge::visit(GetGlyphIndexVisitor{char_code}, value);
		}

		bksge::variant<
			Format0,
			Format2,
			Format4,
			Format6,
			Format8,
			Format10,
			Format12,
			Format13,
			Format14
		> value;
	};

	enum PlatformID
	{
		Unicode   = 0,
		Macintosh = 1,
		ISO       = 2,
		Windows   = 3,
		Custom    = 4,
	};

	struct EncodingRecord
	{
		friend std::uint8_t const*
		ReadBigEndian(
			std::uint8_t const* ptr,
			EncodingRecord* dst,
			std::uint8_t const* start)
		{
			Offset32	subtableOffset;

			ptr = ReadBigEndian(ptr, &dst->platformID);
			ptr = ReadBigEndian(ptr, &dst->encodingID);
			ptr = ReadBigEndian(ptr, &subtableOffset);

			dst->subtable = bksge::make_unique<Subtable>(
				start + subtableOffset);

			return ptr;
		}

		std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
		{
			return subtable->GetGlyphIndex(char_code);
		}

		uint16						platformID;
		uint16						encodingID;
		bksge::unique_ptr<Subtable>	subtable;
	};

	explicit CMapTable(std::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16	version;
		uint16	numTables;
		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &numTables);
		encodingRecords.resize(numTables);
		ptr = ReadBigEndian(ptr, &encodingRecords, start);
	}

	std::uint16_t GetGlyphIndex(std::uint32_t char_code) const
	{
		auto encodingRecord = GetEncodingRecord_Unicode();
		if (encodingRecord == nullptr)
		{
			return 0;
		}

		return encodingRecord->GetGlyphIndex(char_code);
	}

private:
	EncodingRecord const* GetEncodingRecord_Unicode() const
	{
		for (auto& encodingRecord : encodingRecords)
		{
			if (encodingRecord.platformID == Windows)
			{
				if (encodingRecord.encodingID == 1 ||	// Unicode BMP
					encodingRecord.encodingID == 10)	// Unicode full repertoire
				{
					return &encodingRecord;
				}
			}
		}

		for (auto& encodingRecord : encodingRecords)
		{
			if (encodingRecord.platformID == Unicode)
			{
				return &encodingRecord;
			}
		}

		return nullptr;
	}

private:
	bksge::vector<EncodingRecord>	encodingRecords;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_CMAP_HPP
