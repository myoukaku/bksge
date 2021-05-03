/**
 *	@file	vorg.hpp
 *
 *	@brief	VerticalOriginTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_VORG_HPP
#define BKSGE_CORE_FONT_OTF_VORG_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct VerticalOriginTable
{
	struct VertOriginYMetric
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			VertOriginYMetric* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->glyphIndex);
			ptr = ReadBigEndian(ptr, &dst->vertOriginY);
			return ptr;
		}

		uint16	glyphIndex;
		int16	vertOriginY;
	};

	explicit VerticalOriginTable(bksge::uint8_t const* ptr)
	{
		uint16	majorVersion;
		uint16	minorVersion;
		uint16	numVertOriginYMetrics;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &defaultVertOriginY);
		ptr = ReadBigEndian(ptr, &numVertOriginYMetrics);

		vertOriginYMetrics.resize(numVertOriginYMetrics);
		ptr = ReadBigEndian(ptr, &vertOriginYMetrics);
	}

	using VertOriginYMetrics = bksge::vector<VertOriginYMetric>;

	int16				defaultVertOriginY;
	VertOriginYMetrics	vertOriginYMetrics;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_VORG_HPP
