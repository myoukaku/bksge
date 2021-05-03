/**
 *	@file	tuple_record.hpp
 *
 *	@brief	TupleRecord の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_TUPLE_RECORD_HPP
#define BKSGE_CORE_FONT_OTF_TUPLE_RECORD_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct TupleRecord
{
	friend bksge::uint8_t const*
	ReadBigEndian(
		bksge::uint8_t const* ptr,
		TupleRecord* dst,
		uint16 axisCount)
	{
		dst->coordinates.resize(axisCount);
		ptr = ReadBigEndian(ptr, &dst->coordinates);
		return ptr;
	}

	bksge::vector<F2DOT14>	coordinates;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_TUPLE_RECORD_HPP
