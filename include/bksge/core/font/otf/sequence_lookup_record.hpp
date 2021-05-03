/**
 *	@file	sequence_lookup_record.hpp
 *
 *	@brief	SequenceLookupRecord の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_SEQUENCE_LOOKUP_RECORD_HPP
#define BKSGE_CORE_FONT_OTF_SEQUENCE_LOOKUP_RECORD_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct SequenceLookupRecord
{
	friend bksge::uint8_t const*
	ReadBigEndian(
		bksge::uint8_t const* ptr,
		SequenceLookupRecord* dst)
	{
		ptr = ReadBigEndian(ptr, &dst->sequenceIndex);
		ptr = ReadBigEndian(ptr, &dst->lookupListIndex);
		return ptr;
	}

	uint16	sequenceIndex;
	uint16	lookupListIndex;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_SEQUENCE_LOOKUP_RECORD_HPP
