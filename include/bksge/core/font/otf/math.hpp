/**
 *	@file	math.hpp
 *
 *	@brief	MathTable の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_CORE_FONT_OTF_MATH_HPP
#define BKSGE_CORE_FONT_OTF_MATH_HPP

#include <bksge/core/font/otf/read_big_endian.hpp>
#include <bksge/core/font/otf/types.hpp>
#include <bksge/core/font/otf/device_table.hpp>
#include <bksge/core/font/otf/coverage_table.hpp>
#include <bksge/fnd/memory/unique_ptr.hpp>
#include <bksge/fnd/memory/make_unique.hpp>
#include <bksge/fnd/cstdint.hpp>

namespace bksge
{

namespace otf
{

struct MathTable
{
	struct MathValueRecord
	{
		friend bksge::uint8_t const*
		ReadBigEndian(
			bksge::uint8_t const* ptr,
			MathValueRecord* dst,
			bksge::uint8_t const* start)
		{
			Offset16 deviceOffset;

			ptr = ReadBigEndian(ptr, &dst->value);
			ptr = ReadBigEndian(ptr, &deviceOffset);

			if (deviceOffset != 0)
			{
				dst->device = bksge::make_unique<DeviceTable>(
					start + deviceOffset);
			}

			return ptr;
		}

		FWORD							value;
		bksge::unique_ptr<DeviceTable>	device;
	};

	struct MathConstants
	{
		explicit MathConstants(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			ptr = ReadBigEndian(ptr, &scriptPercentScaleDown);
			ptr = ReadBigEndian(ptr, &scriptScriptPercentScaleDown);
			ptr = ReadBigEndian(ptr, &delimitedSubFormulaMinHeight);
			ptr = ReadBigEndian(ptr, &displayOperatorMinHeight);
			ptr = ReadBigEndian(ptr, &mathLeading, start);
			ptr = ReadBigEndian(ptr, &axisHeight, start);
			ptr = ReadBigEndian(ptr, &accentBaseHeight, start);
			ptr = ReadBigEndian(ptr, &flattenedAccentBaseHeight, start);
			ptr = ReadBigEndian(ptr, &subscriptShiftDown, start);
			ptr = ReadBigEndian(ptr, &subscriptTopMax, start);
			ptr = ReadBigEndian(ptr, &subscriptBaselineDropMin, start);
			ptr = ReadBigEndian(ptr, &superscriptShiftUp, start);
			ptr = ReadBigEndian(ptr, &superscriptShiftUpCramped, start);
			ptr = ReadBigEndian(ptr, &superscriptBottomMin, start);
			ptr = ReadBigEndian(ptr, &superscriptBaselineDropMax, start);
			ptr = ReadBigEndian(ptr, &subSuperscriptGapMin, start);
			ptr = ReadBigEndian(ptr, &superscriptBottomMaxWithSubscript, start);
			ptr = ReadBigEndian(ptr, &spaceAfterScript, start);
			ptr = ReadBigEndian(ptr, &upperLimitGapMin, start);
			ptr = ReadBigEndian(ptr, &upperLimitBaselineRiseMin, start);
			ptr = ReadBigEndian(ptr, &lowerLimitGapMin, start);
			ptr = ReadBigEndian(ptr, &lowerLimitBaselineDropMin, start);
			ptr = ReadBigEndian(ptr, &stackTopShiftUp, start);
			ptr = ReadBigEndian(ptr, &stackTopDisplayStyleShiftUp, start);
			ptr = ReadBigEndian(ptr, &stackBottomShiftDown, start);
			ptr = ReadBigEndian(ptr, &stackBottomDisplayStyleShiftDown, start);
			ptr = ReadBigEndian(ptr, &stackGapMin, start);
			ptr = ReadBigEndian(ptr, &stackDisplayStyleGapMin, start);
			ptr = ReadBigEndian(ptr, &stretchStackTopShiftUp, start);
			ptr = ReadBigEndian(ptr, &stretchStackBottomShiftDown, start);
			ptr = ReadBigEndian(ptr, &stretchStackGapAboveMin, start);
			ptr = ReadBigEndian(ptr, &stretchStackGapBelowMin, start);
			ptr = ReadBigEndian(ptr, &fractionNumeratorShiftUp, start);
			ptr = ReadBigEndian(ptr, &fractionNumeratorDisplayStyleShiftUp, start);
			ptr = ReadBigEndian(ptr, &fractionDenominatorShiftDown, start);
			ptr = ReadBigEndian(ptr, &fractionDenominatorDisplayStyleShiftDown, start);
			ptr = ReadBigEndian(ptr, &fractionNumeratorGapMin, start);
			ptr = ReadBigEndian(ptr, &fractionNumDisplayStyleGapMin, start);
			ptr = ReadBigEndian(ptr, &fractionRuleThickness, start);
			ptr = ReadBigEndian(ptr, &fractionDenominatorGapMin, start);
			ptr = ReadBigEndian(ptr, &fractionDenomDisplayStyleGapMin, start);
			ptr = ReadBigEndian(ptr, &skewedFractionHorizontalGap, start);
			ptr = ReadBigEndian(ptr, &skewedFractionVerticalGap, start);
			ptr = ReadBigEndian(ptr, &overbarVerticalGap, start);
			ptr = ReadBigEndian(ptr, &overbarRuleThickness, start);
			ptr = ReadBigEndian(ptr, &overbarExtraAscender, start);
			ptr = ReadBigEndian(ptr, &underbarVerticalGap, start);
			ptr = ReadBigEndian(ptr, &underbarRuleThickness, start);
			ptr = ReadBigEndian(ptr, &underbarExtraDescender, start);
			ptr = ReadBigEndian(ptr, &radicalVerticalGap, start);
			ptr = ReadBigEndian(ptr, &radicalDisplayStyleVerticalGap, start);
			ptr = ReadBigEndian(ptr, &radicalRuleThickness, start);
			ptr = ReadBigEndian(ptr, &radicalExtraAscender, start);
			ptr = ReadBigEndian(ptr, &radicalKernBeforeDegree, start);
			ptr = ReadBigEndian(ptr, &radicalKernAfterDegree, start);
			ptr = ReadBigEndian(ptr, &radicalDegreeBottomRaisePercent);
		}

		int16			scriptPercentScaleDown;
		int16			scriptScriptPercentScaleDown;
		UFWORD			delimitedSubFormulaMinHeight;
		UFWORD			displayOperatorMinHeight;
		MathValueRecord	mathLeading;
		MathValueRecord	axisHeight;
		MathValueRecord	accentBaseHeight;
		MathValueRecord	flattenedAccentBaseHeight;
		MathValueRecord	subscriptShiftDown;
		MathValueRecord	subscriptTopMax;
		MathValueRecord	subscriptBaselineDropMin;
		MathValueRecord	superscriptShiftUp;
		MathValueRecord	superscriptShiftUpCramped;
		MathValueRecord	superscriptBottomMin;
		MathValueRecord	superscriptBaselineDropMax;
		MathValueRecord	subSuperscriptGapMin;
		MathValueRecord	superscriptBottomMaxWithSubscript;
		MathValueRecord	spaceAfterScript;
		MathValueRecord	upperLimitGapMin;
		MathValueRecord	upperLimitBaselineRiseMin;
		MathValueRecord	lowerLimitGapMin;
		MathValueRecord	lowerLimitBaselineDropMin;
		MathValueRecord	stackTopShiftUp;
		MathValueRecord	stackTopDisplayStyleShiftUp;
		MathValueRecord	stackBottomShiftDown;
		MathValueRecord	stackBottomDisplayStyleShiftDown;
		MathValueRecord	stackGapMin;
		MathValueRecord	stackDisplayStyleGapMin;
		MathValueRecord	stretchStackTopShiftUp;
		MathValueRecord	stretchStackBottomShiftDown;
		MathValueRecord	stretchStackGapAboveMin;
		MathValueRecord	stretchStackGapBelowMin;
		MathValueRecord	fractionNumeratorShiftUp;
		MathValueRecord	fractionNumeratorDisplayStyleShiftUp;
		MathValueRecord	fractionDenominatorShiftDown;
		MathValueRecord	fractionDenominatorDisplayStyleShiftDown;
		MathValueRecord	fractionNumeratorGapMin;
		MathValueRecord	fractionNumDisplayStyleGapMin;
		MathValueRecord	fractionRuleThickness;
		MathValueRecord	fractionDenominatorGapMin;
		MathValueRecord	fractionDenomDisplayStyleGapMin;
		MathValueRecord	skewedFractionHorizontalGap;
		MathValueRecord	skewedFractionVerticalGap;
		MathValueRecord	overbarVerticalGap;
		MathValueRecord	overbarRuleThickness;
		MathValueRecord	overbarExtraAscender;
		MathValueRecord	underbarVerticalGap;
		MathValueRecord	underbarRuleThickness;
		MathValueRecord	underbarExtraDescender;
		MathValueRecord	radicalVerticalGap;
		MathValueRecord	radicalDisplayStyleVerticalGap;
		MathValueRecord	radicalRuleThickness;
		MathValueRecord	radicalExtraAscender;
		MathValueRecord	radicalKernBeforeDegree;
		MathValueRecord	radicalKernAfterDegree;
		int16			radicalDegreeBottomRaisePercent;
	};

	struct MathGlyphInfo
	{
		struct MathItalicsCorrectionInfo
		{
			explicit MathItalicsCorrectionInfo(bksge::uint8_t const* ptr)
			{
				auto const start = ptr;

				Offset16	italicsCorrectionCoverageOffset;
				uint16		italicsCorrectionCount;

				ptr = ReadBigEndian(ptr, &italicsCorrectionCoverageOffset);
				ptr = ReadBigEndian(ptr, &italicsCorrectionCount);
				italicsCorrection.resize(italicsCorrectionCount);
				ptr = ReadBigEndian(ptr, &italicsCorrection, start);

				if (italicsCorrectionCoverageOffset != 0)
				{
					italicsCorrectionCoverage = bksge::make_unique<CoverageTable>(
						start + italicsCorrectionCoverageOffset);
				}
			}

			bksge::unique_ptr<CoverageTable>	italicsCorrectionCoverage;
			bksge::vector<MathValueRecord>		italicsCorrection;
		};

		struct MathTopAccentAttachment
		{
			explicit MathTopAccentAttachment(bksge::uint8_t const* ptr)
			{
				auto const start = ptr;

				Offset16	topAccentCoverageOffset;
				uint16		topAccentAttachmentCount;

				ptr = ReadBigEndian(ptr, &topAccentCoverageOffset);
				ptr = ReadBigEndian(ptr, &topAccentAttachmentCount);
				topAccentAttachment.resize(topAccentAttachmentCount);
				ptr = ReadBigEndian(ptr, &topAccentAttachment, start);

				if (topAccentCoverageOffset != 0)
				{
					topAccentCoverage = bksge::make_unique<CoverageTable>(
						start + topAccentCoverageOffset);
				}
			}

			bksge::unique_ptr<CoverageTable>	topAccentCoverage;
			bksge::vector<MathValueRecord>		topAccentAttachment;
		};

		struct ExtendedShapeCoverage
		{
			explicit ExtendedShapeCoverage(bksge::uint8_t const* ptr)
			{
				(void)ptr;
			}
			// TODO
		};

		struct MathKern
		{
			explicit MathKern(bksge::uint8_t const* ptr)
			{
				auto const start = ptr;

				uint16	heightCount;
				ptr = ReadBigEndian(ptr, &heightCount);

				correctionHeight.resize(heightCount);
				ptr = ReadBigEndian(ptr, &correctionHeight, start);

				kernValues.resize(heightCount + 1);
				ptr = ReadBigEndian(ptr, &kernValues, start);
			}

			bksge::vector<MathValueRecord>	correctionHeight;
			bksge::vector<MathValueRecord>	kernValues;
		};

		struct MathKernInfoRecord
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				MathKernInfoRecord* dst,
				bksge::uint8_t const* start)
			{
				Offset16	topRightMathKernOffset;
				Offset16	topLeftMathKernOffset;
				Offset16	bottomRightMathKernOffset;
				Offset16	bottomLeftMathKernOffset;

				ptr = ReadBigEndian(ptr, &topRightMathKernOffset);
				ptr = ReadBigEndian(ptr, &topLeftMathKernOffset);
				ptr = ReadBigEndian(ptr, &bottomRightMathKernOffset);
				ptr = ReadBigEndian(ptr, &bottomLeftMathKernOffset);

				if (topRightMathKernOffset != 0)
				{
					dst->topRightMathKern = bksge::make_unique<MathKern>(
						start + topRightMathKernOffset);
				}
				if (topLeftMathKernOffset != 0)
				{
					dst->topLeftMathKern = bksge::make_unique<MathKern>(
						start + topLeftMathKernOffset);
				}
				if (bottomRightMathKernOffset != 0)
				{
					dst->bottomRightMathKern = bksge::make_unique<MathKern>(
						start + bottomRightMathKernOffset);
				}
				if (bottomLeftMathKernOffset != 0)
				{
					dst->bottomLeftMathKern = bksge::make_unique<MathKern>(
						start + bottomLeftMathKernOffset);
				}

				return ptr;
			}

			bksge::unique_ptr<MathKern>	topRightMathKern;
			bksge::unique_ptr<MathKern>	topLeftMathKern;
			bksge::unique_ptr<MathKern>	bottomRightMathKern;
			bksge::unique_ptr<MathKern>	bottomLeftMathKern;
		};

		struct MathKernInfo
		{
			explicit MathKernInfo(bksge::uint8_t const* ptr)
			{
				auto const start = ptr;

				Offset16	mathKernCoverageOffset;
				uint16		mathKernCount;

				ptr = ReadBigEndian(ptr, &mathKernCoverageOffset);
				ptr = ReadBigEndian(ptr, &mathKernCount);
				mathKernInfoRecords.resize(mathKernCount);
				ptr = ReadBigEndian(ptr, &mathKernInfoRecords, start);

				if (mathKernCoverageOffset != 0)
				{
					mathKernCoverage = bksge::make_unique<CoverageTable>(
						start + mathKernCoverageOffset);
				}
			}

			bksge::unique_ptr<CoverageTable>	mathKernCoverage;
			bksge::vector<MathKernInfoRecord>	mathKernInfoRecords;
		};

		explicit MathGlyphInfo(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	mathItalicsCorrectionInfoOffset;
			Offset16	mathTopAccentAttachmentOffset;
			Offset16	extendedShapeCoverageOffset;
			Offset16	mathKernInfoOffset;

			ptr = ReadBigEndian(ptr, &mathItalicsCorrectionInfoOffset);
			ptr = ReadBigEndian(ptr, &mathTopAccentAttachmentOffset);
			ptr = ReadBigEndian(ptr, &extendedShapeCoverageOffset);
			ptr = ReadBigEndian(ptr, &mathKernInfoOffset);

			if (mathItalicsCorrectionInfoOffset != 0)
			{
				mathItalicsCorrectionInfo =
					bksge::make_unique<MathItalicsCorrectionInfo>(
						start + mathItalicsCorrectionInfoOffset);
			}
			if (mathTopAccentAttachmentOffset != 0)
			{
				mathTopAccentAttachment =
					bksge::make_unique<MathTopAccentAttachment>(
						start + mathTopAccentAttachmentOffset);
			}
			if (extendedShapeCoverageOffset != 0)
			{
				extendedShapeCoverage =
					bksge::make_unique<ExtendedShapeCoverage>(
						start + extendedShapeCoverageOffset);
			}
			if (mathKernInfoOffset != 0)
			{
				mathKernInfo =
					bksge::make_unique<MathKernInfo>(
						start + mathKernInfoOffset);
			}
		}

		bksge::unique_ptr<MathItalicsCorrectionInfo>	mathItalicsCorrectionInfo;
		bksge::unique_ptr<MathTopAccentAttachment>		mathTopAccentAttachment;
		bksge::unique_ptr<ExtendedShapeCoverage>		extendedShapeCoverage;
		bksge::unique_ptr<MathKernInfo>					mathKernInfo;
	};

	struct MathVariants
	{
		struct GlyphPartRecord
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				GlyphPartRecord* dst)
			{
				ptr = ReadBigEndian(ptr, &dst->glyphID);
				ptr = ReadBigEndian(ptr, &dst->startConnectorLength);
				ptr = ReadBigEndian(ptr, &dst->endConnectorLength);
				ptr = ReadBigEndian(ptr, &dst->fullAdvance);
				ptr = ReadBigEndian(ptr, &dst->partFlags);
				return ptr;
			}

			uint16	glyphID;
			UFWORD	startConnectorLength;
			UFWORD	endConnectorLength;
			UFWORD	fullAdvance;
			uint16	partFlags;
		};

		struct GlyphAssembly
		{
			explicit GlyphAssembly(bksge::uint8_t const* ptr)
			{
				auto const start = ptr;

				uint16	partCount;

				ptr = ReadBigEndian(ptr, &italicsCorrection, start);
				ptr = ReadBigEndian(ptr, &partCount);
				partRecords.resize(partCount);
				ptr = ReadBigEndian(ptr, &partRecords);
			}

			MathValueRecord					italicsCorrection;
			bksge::vector<GlyphPartRecord>	partRecords;
		};

		struct MathGlyphVariantRecord
		{
			friend bksge::uint8_t const*
			ReadBigEndian(
				bksge::uint8_t const* ptr,
				MathGlyphVariantRecord* dst)
			{
				ptr = ReadBigEndian(ptr, &dst->variantGlyph);
				ptr = ReadBigEndian(ptr, &dst->advanceMeasurement);
				return ptr;
			}

			uint16	variantGlyph;
			UFWORD	advanceMeasurement;
		};

		struct MathGlyphConstruction
		{
			explicit MathGlyphConstruction(bksge::uint8_t const* ptr)
			{
				auto const start = ptr;

				Offset16	glyphAssemblyOffset;
				uint16		variantCount;

				ptr = ReadBigEndian(ptr, &glyphAssemblyOffset);
				ptr = ReadBigEndian(ptr, &variantCount);
				mathGlyphVariantRecord.resize(variantCount);
				ptr = ReadBigEndian(ptr, &mathGlyphVariantRecord);

				if (glyphAssemblyOffset != 0)
				{
					glyphAssembly = bksge::make_unique<GlyphAssembly>(
						start + glyphAssemblyOffset);
				}
			}

			bksge::unique_ptr<GlyphAssembly>		glyphAssembly;
			bksge::vector<MathGlyphVariantRecord>	mathGlyphVariantRecord;
		};

		explicit MathVariants(bksge::uint8_t const* ptr)
		{
			auto const start = ptr;

			Offset16	vertGlyphCoverageOffset;
			Offset16	horizGlyphCoverageOffset;
			uint16		vertGlyphCount;
			uint16		horizGlyphCount;

			ptr = ReadBigEndian(ptr, &minConnectorOverlap);
			ptr = ReadBigEndian(ptr, &vertGlyphCoverageOffset);
			ptr = ReadBigEndian(ptr, &horizGlyphCoverageOffset);
			ptr = ReadBigEndian(ptr, &vertGlyphCount);
			ptr = ReadBigEndian(ptr, &horizGlyphCount);

			for (uint16 i = 0; i < vertGlyphCount; ++i)
			{
				Offset16 vertGlyphConstructionOffset;
				ptr = ReadBigEndian(ptr, &vertGlyphConstructionOffset);
				vertGlyphConstructions.emplace_back(
					start + vertGlyphConstructionOffset);
			}

			for (uint16 i = 0; i < horizGlyphCount; ++i)
			{
				Offset16 horizGlyphConstructionOffset;
				ptr = ReadBigEndian(ptr, &horizGlyphConstructionOffset);
				horizGlyphConstructions.emplace_back(
					start + horizGlyphConstructionOffset);
			}

			if (vertGlyphCoverageOffset != 0)
			{
				vertGlyphCoverage = bksge::make_unique<CoverageTable>(
					start + vertGlyphCoverageOffset);
			}
			if (horizGlyphCoverageOffset != 0)
			{
				horizGlyphCoverage = bksge::make_unique<CoverageTable>(
					start + horizGlyphCoverageOffset);
			}
		}

		UFWORD									minConnectorOverlap;
		bksge::unique_ptr<CoverageTable>		vertGlyphCoverage;
		bksge::unique_ptr<CoverageTable>		horizGlyphCoverage;
		bksge::vector<MathGlyphConstruction>	vertGlyphConstructions;
		bksge::vector<MathGlyphConstruction>	horizGlyphConstructions;
	};

	explicit MathTable(bksge::uint8_t const* ptr)
	{
		auto const start = ptr;

		uint16		majorVersion;
		uint16		minorVersion;
		Offset16	mathConstantsOffset;
		Offset16	mathGlyphInfoOffset;
		Offset16	mathVariantsOffset;

		ptr = ReadBigEndian(ptr, &majorVersion);
		ptr = ReadBigEndian(ptr, &minorVersion);
		ptr = ReadBigEndian(ptr, &mathConstantsOffset);
		ptr = ReadBigEndian(ptr, &mathGlyphInfoOffset);
		ptr = ReadBigEndian(ptr, &mathVariantsOffset);

		if (mathConstantsOffset != 0)
		{
			mathConstants = bksge::make_unique<MathConstants>(
				start + mathConstantsOffset);
		}
		if (mathGlyphInfoOffset != 0)
		{
			mathGlyphInfo = bksge::make_unique<MathGlyphInfo>(
				start + mathGlyphInfoOffset);
		}
		if (mathVariantsOffset != 0)
		{
			mathVariants = bksge::make_unique<MathVariants>(
				start + mathVariantsOffset);
		}
	}

	bksge::unique_ptr<MathConstants>	mathConstants;
	bksge::unique_ptr<MathGlyphInfo>	mathGlyphInfo;
	bksge::unique_ptr<MathVariants>		mathVariants;
};

}	// namespace otf

}	// namespace bksge

#endif // BKSGE_CORE_FONT_OTF_MATH_HPP
