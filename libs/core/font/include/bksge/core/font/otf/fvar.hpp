/**
 *	@file	fvar.hpp
 *
 *	@brief	FontVariationsTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_FVAR_HPP
#define BKSGE_CORE_FONT_OTF_FVAR_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct FontVariationsTable
{
	struct Tuple
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			Tuple* dst,
			uint16 axisCount)
		{
			dst->coordinates.resize(axisCount);
			ptr = ReadBigEndian(ptr, &dst->coordinates);
			return ptr;
		}

		bksge::vector<Fixed>	coordinates;
	};

	struct InstanceRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			InstanceRecord* dst,
			uint16 axisCount)
		{
			ptr = ReadBigEndian(ptr, &dst->subfamilyNameID);
			ptr = ReadBigEndian(ptr, &dst->flags);
			ptr = ReadBigEndian(ptr, &dst->coordinates, axisCount);
			ptr = ReadBigEndian(ptr, &dst->postScriptNameID);
			return ptr;
		}

		uint16	subfamilyNameID;
		uint16	flags;
		Tuple	coordinates;
		uint16	postScriptNameID;
	};

	struct VariationAxisRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(bksge::uint8_t const* ptr, VariationAxisRecord* dst)
		{
			ptr = ReadBigEndian(ptr, &dst->axisTag);
			ptr = ReadBigEndian(ptr, &dst->minValue);
			ptr = ReadBigEndian(ptr, &dst->defaultValue);
			ptr = ReadBigEndian(ptr, &dst->maxValue);
			ptr = ReadBigEndian(ptr, &dst->flags);
			ptr = ReadBigEndian(ptr, &dst->axisNameID);
			return ptr;
		}

		Tag		axisTag;
		Fixed	minValue;
		Fixed	defaultValue;
		Fixed	maxValue;
		uint16	flags;
		uint16	axisNameID;
	};

	explicit FontVariationsTable(bksge::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		majorVersion;
		uint16		minorVersion;
		Offset16	axesArrayOffset;
		uint16		reserved;
		uint16		axisCount;
		uint16		axisSize;
		uint16		instanceCount;
		uint16		instanceSize;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &axesArrayOffset);
		ptr = ReadBigEndian(ptr, &reserved);
		ptr = ReadBigEndian(ptr, &axisCount);
		ptr = ReadBigEndian(ptr, &axisSize);
		ptr = ReadBigEndian(ptr, &instanceCount);
		ptr = ReadBigEndian(ptr, &instanceSize);

		ptr = start + axesArrayOffset;
		axes.resize(axisCount);
		ptr = ReadBigEndian(ptr, &axes);

		instances.resize(instanceCount);
		ptr = ReadBigEndian(ptr, &instances, axisCount);
	}

	uint16 axisCount() const
	{
		return static_cast<uint16>(axes.size());
	}

	bksge::vector<VariationAxisRecord>		axes;
	bksge::vector<InstanceRecord>			instances;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_FVAR_HPP
