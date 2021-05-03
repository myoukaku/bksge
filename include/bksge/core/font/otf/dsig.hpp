/**
 *	@file	dsig.hpp
 *
 *	@brief	DigitalSignatureTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_DSIG_HPP
#define BKSGE_CORE_FONT_OTF_DSIG_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/fnd/vector.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct DigitalSignatureTable
{
	struct SignatureBlock
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			SignatureBlock* dst)
		{
			uint16	reserved1;
			uint16	reserved2;
			uint32	signatureLength;

			ptr = ReadBigEndian(ptr, &reserved1);
			ptr = ReadBigEndian(ptr, &reserved2);
			ptr = ReadBigEndian(ptr, &signatureLength);
			dst->signature.resize(signatureLength);
			ptr = ReadBigEndian(ptr, &dst->signature);

			return ptr;
		}

		bksge::vector<uint8>	signature;
	};

	struct SignatureRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			SignatureRecord* dst,
			bksge::uint8_t const* start)
		{
			uint32		format;
			uint32		length;
			Offset32	signatureBlockOffset;

			ptr = ReadBigEndian(ptr, &format);
			ptr = ReadBigEndian(ptr, &length);
			ptr = ReadBigEndian(ptr, &signatureBlockOffset);

			ptr = ReadBigEndian(start + signatureBlockOffset, &dst->signatureBlock);

			return ptr;
		}

		SignatureBlock signatureBlock;
	};

	explicit DigitalSignatureTable(bksge::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint32	version;
		uint16	numSignatures;
		uint16	flags;

		ptr = ReadBigEndian(ptr, &version);
		ptr = ReadBigEndian(ptr, &numSignatures);
		ptr = ReadBigEndian(ptr, &flags);
		signatureRecords.resize(numSignatures);
		ptr = ReadBigEndian(ptr, &signatureRecords, start);
	}

	bksge::vector<SignatureRecord>	signatureRecords;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_DSIG_HPP
