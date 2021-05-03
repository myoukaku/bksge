/**
 *	@file	svg.hpp
 *
 *	@brief	SVGTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_SVG_HPP
#define BKSGE_CORE_FONT_OTF_SVG_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/string.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct SVGTable
{
	struct SVGDocumentRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			SVGDocumentRecord* dst,
			char const* start)
		{
			Offset32	svgDocOffset;
			uint32		svgDocLength;
			ptr = ReadBigEndian(ptr, &dst->startGlyphID);
			ptr = ReadBigEndian(ptr, &dst->endGlyphID);
			ptr = ReadBigEndian(ptr, &svgDocOffset);
			ptr = ReadBigEndian(ptr, &svgDocLength);
			dst->svgDoc = bksge::string(start + svgDocOffset, svgDocLength);
			return ptr;
		}

		uint16			startGlyphID;
		uint16			endGlyphID;
		bksge::string	svgDoc;
	};

	struct SVGDocumentList
	{
		explicit SVGDocumentList(bksge::uint8_t const* ptr)
		{
			auto const start = reinterpret_cast<char const*>(ptr);

			uint16	numEntries;
			ptr = ReadBigEndian(ptr, &numEntries);
			documentRecords.resize(numEntries);
			ptr = ReadBigEndian(ptr, &documentRecords, start);
		}

		bksge::vector<SVGDocumentRecord>	documentRecords;
	};

	explicit SVGTable(bksge::uint8_t const* ptr)
	{
		auto start = ptr;

		uint16		version;
		Offset32	svgDocumentListOffset;
		uint32		reserved;

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &svgDocumentListOffset);
		ptr = ReadBigEndian(ptr, &reserved);

		if (svgDocumentListOffset != 0)
		{
			svgDocumentList = bksge::make_unique<SVGDocumentList>(
				start + svgDocumentListOffset);
		}
	}

	bksge::unique_ptr<SVGDocumentList>	svgDocumentList;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_SVG_HPP
