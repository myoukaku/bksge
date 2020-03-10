/**
 *	@file	unit_test_fnd_sstream_stringbuf.cpp
 *
 *	@brief	stringbuf のテスト
 *
 *	@author	myoukaku
 */

#include <bksge/fnd/sstream.hpp>
//#include <bksge/fnd/string.hpp>
#include <string>
//#include <bksge/fnd/streambuf.hpp>
#include <streambuf>
#include <bksge/fnd/ios.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/type_traits/is_base_of.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/memory/allocator.hpp>
#include <gtest/gtest.h>

namespace bksge_sstream_test
{

namespace stringbuf_test
{

namespace ctor_default_test
{

template <typename CharT>
struct testbuf
	: bksge::basic_stringbuf<CharT>
{
	void check()
	{
		EXPECT_TRUE(this->eback() == NULL);
		EXPECT_TRUE(this->gptr()  == NULL);
		EXPECT_TRUE(this->egptr() == NULL);
		EXPECT_TRUE(this->pbase() == NULL);
		EXPECT_TRUE(this->pptr()  == NULL);
		EXPECT_TRUE(this->epptr() == NULL);
	}
};

GTEST_TEST(StringbufTest, CtorDefaultTest)
{
	{
		bksge::stringbuf buf;
		EXPECT_TRUE(buf.str() == "");
	}
	{
		bksge::wstringbuf buf;
		EXPECT_TRUE(buf.str() == L"");
	}
	{
		testbuf<char> buf;
		buf.check();
	}
	{
		testbuf<wchar_t> buf;
		buf.check();
	}
}

}	// namespace ctor_default_test

GTEST_TEST(StringbufTest, CtorMoveTest)
{
	{
		bksge::stringbuf buf1("testing");
		bksge::stringbuf buf(bksge::move(buf1));
		EXPECT_TRUE(buf.str() == "testing");
	}
	{
		bksge::stringbuf buf1("testing", std::ios_base::in);
		bksge::stringbuf buf(bksge::move(buf1));
		EXPECT_TRUE(buf.str() == "testing");
	}
	{
		bksge::stringbuf buf1("testing", std::ios_base::out);
		bksge::stringbuf buf(bksge::move(buf1));
		EXPECT_TRUE(buf.str() == "testing");
	}
	{
		bksge::wstringbuf buf1(L"testing");
		bksge::wstringbuf buf(bksge::move(buf1));
		EXPECT_TRUE(buf.str() == L"testing");
	}
	{
		bksge::wstringbuf buf1(L"testing", std::ios_base::in);
		bksge::wstringbuf buf(bksge::move(buf1));
		EXPECT_TRUE(buf.str() == L"testing");
	}
	{
		bksge::wstringbuf buf1(L"testing", std::ios_base::out);
		bksge::wstringbuf buf(bksge::move(buf1));
		EXPECT_TRUE(buf.str() == L"testing");
	}
}

GTEST_TEST(StringbufTest, CtorStringTest)
{
	{
		bksge::stringbuf buf("testing");
		EXPECT_TRUE(buf.str() == "testing");
	}
	{
		bksge::stringbuf buf("testing", std::ios_base::in);
		EXPECT_TRUE(buf.str() == "testing");
	}
	{
		bksge::stringbuf buf("testing", std::ios_base::out);
		EXPECT_TRUE(buf.str() == "testing");
	}
	{
		bksge::wstringbuf buf(L"testing");
		EXPECT_TRUE(buf.str() == L"testing");
	}
	{
		bksge::wstringbuf buf(L"testing", std::ios_base::in);
		EXPECT_TRUE(buf.str() == L"testing");
	}
	{
		bksge::wstringbuf buf(L"testing", std::ios_base::out);
		EXPECT_TRUE(buf.str() == L"testing");
	}
}

GTEST_TEST(StringbufTest, MoveAssignTest)
{
	{
		bksge::stringbuf buf1("testing");
		bksge::stringbuf buf;
		buf = bksge::move(buf1);
		EXPECT_TRUE(buf.str() == "testing");
	}
	{
		bksge::stringbuf buf1("testing", std::ios_base::in);
		bksge::stringbuf buf;
		buf = bksge::move(buf1);
		EXPECT_TRUE(buf.str() == "testing");
	}
	{
		bksge::stringbuf buf1("testing", std::ios_base::out);
		bksge::stringbuf buf;
		buf = bksge::move(buf1);
		EXPECT_TRUE(buf.str() == "testing");
	}
	{
		bksge::wstringbuf buf1(L"testing");
		bksge::wstringbuf buf;
		buf = bksge::move(buf1);
		EXPECT_TRUE(buf.str() == L"testing");
	}
	{
		bksge::wstringbuf buf1(L"testing", std::ios_base::in);
		bksge::wstringbuf buf;
		buf = bksge::move(buf1);
		EXPECT_TRUE(buf.str() == L"testing");
	}
	{
		bksge::wstringbuf buf1(L"testing", std::ios_base::out);
		bksge::wstringbuf buf;
		buf = bksge::move(buf1);
		EXPECT_TRUE(buf.str() == L"testing");
	}
}

GTEST_TEST(StringbufTest, SwapTest)
{
	{
		bksge::stringbuf buf1("testing");
		bksge::stringbuf buf;
		buf.swap(buf1);
		EXPECT_TRUE(buf.str() == "testing");
		EXPECT_TRUE(buf1.str() == "");
	}
	{
		bksge::stringbuf buf1("testing", std::ios_base::in);
		bksge::stringbuf buf;
		buf.swap(buf1);
		EXPECT_TRUE(buf.str() == "testing");
		EXPECT_TRUE(buf1.str() == "");
	}
	{
		bksge::stringbuf buf1("testing", std::ios_base::out);
		bksge::stringbuf buf;
		buf.swap(buf1);
		EXPECT_TRUE(buf.str() == "testing");
		EXPECT_TRUE(buf1.str() == "");
	}
	{
		bksge::wstringbuf buf1(L"testing");
		bksge::wstringbuf buf;
		buf.swap(buf1);
		EXPECT_TRUE(buf.str() == L"testing");
		EXPECT_TRUE(buf1.str() == L"");
	}
	{
		bksge::wstringbuf buf1(L"testing", std::ios_base::in);
		bksge::wstringbuf buf;
		buf.swap(buf1);
		EXPECT_TRUE(buf.str() == L"testing");
		EXPECT_TRUE(buf1.str() == L"");
	}
	{
		bksge::wstringbuf buf1(L"testing", std::ios_base::out);
		bksge::wstringbuf buf;
		buf.swap(buf1);
		EXPECT_TRUE(buf.str() == L"testing");
		EXPECT_TRUE(buf1.str() == L"");
	}
	{
		bksge::stringbuf buf1("testing");
		bksge::stringbuf buf;
		swap(buf, buf1);
		EXPECT_TRUE(buf.str() == "testing");
		EXPECT_TRUE(buf1.str() == "");
	}
	{
		bksge::stringbuf buf1("testing", std::ios_base::in);
		bksge::stringbuf buf;
		swap(buf, buf1);
		EXPECT_TRUE(buf.str() == "testing");
		EXPECT_TRUE(buf1.str() == "");
	}
	{
		bksge::stringbuf buf1("testing", std::ios_base::out);
		bksge::stringbuf buf;
		swap(buf, buf1);
		EXPECT_TRUE(buf.str() == "testing");
		EXPECT_TRUE(buf1.str() == "");
	}
	{
		bksge::wstringbuf buf1(L"testing");
		bksge::wstringbuf buf;
		swap(buf, buf1);
		EXPECT_TRUE(buf.str() == L"testing");
		EXPECT_TRUE(buf1.str() == L"");
	}
	{
		bksge::wstringbuf buf1(L"testing", std::ios_base::in);
		bksge::wstringbuf buf;
		swap(buf, buf1);
		EXPECT_TRUE(buf.str() == L"testing");
		EXPECT_TRUE(buf1.str() == L"");
	}
	{
		bksge::wstringbuf buf1(L"testing", std::ios_base::out);
		bksge::wstringbuf buf;
		swap(buf, buf1);
		EXPECT_TRUE(buf.str() == L"testing");
		EXPECT_TRUE(buf1.str() == L"");
	}
}

GTEST_TEST(StringbufTest, StrTest)
{
	{
		bksge::stringbuf buf("testing");
		EXPECT_TRUE(buf.str() == "testing");
		buf.str("another test");
		EXPECT_TRUE(buf.str() == "another test");
	}
	{
		bksge::wstringbuf buf(L"testing");
		EXPECT_TRUE(buf.str() == L"testing");
		buf.str(L"another test");
		EXPECT_TRUE(buf.str() == L"another test");
	}
}

namespace overflow_test
{

int overflow_called = 0;

template <typename CharT>
struct testbuf
	: public bksge::basic_stringbuf<CharT>
{
	using base = bksge::basic_stringbuf<CharT>;

	explicit testbuf(const std::basic_string<CharT>& str,
					 std::ios_base::openmode which = std::ios_base::in | std::ios_base::out)
		: base(str, which) {}

	typename base::int_type
		overflow(typename base::int_type c = base::traits_type::eof())
	{
		++overflow_called; return base::overflow(c);
	}

	void pbump(int n) { base::pbump(n); }
};

GTEST_TEST(StringbufTest, OverflowTest)
{
	{  // sanity check
		testbuf<char> tb("");
		tb.overflow();
	}
	{
		testbuf<char> sb("abc");
		EXPECT_TRUE(sb.sputc('1') == '1');
		EXPECT_TRUE(sb.str() == "1bc");
		EXPECT_TRUE(sb.sputc('2') == '2');
		EXPECT_TRUE(sb.str() == "12c");
		EXPECT_TRUE(sb.sputc('3') == '3');
		EXPECT_TRUE(sb.str() == "123");
		EXPECT_TRUE(sb.sputc('4') == '4');
		EXPECT_TRUE(sb.str() == "1234");
		EXPECT_TRUE(sb.sputc('5') == '5');
		EXPECT_TRUE(sb.str() == "12345");
		EXPECT_TRUE(sb.sputc('6') == '6');
		EXPECT_TRUE(sb.str() == "123456");
		EXPECT_TRUE(sb.sputc('7') == '7');
		EXPECT_TRUE(sb.str() == "1234567");
		EXPECT_TRUE(sb.sputc('8') == '8');
		EXPECT_TRUE(sb.str() == "12345678");
		EXPECT_TRUE(sb.sputc('9') == '9');
		EXPECT_TRUE(sb.str() == "123456789");
		EXPECT_TRUE(sb.sputc('0') == '0');
		EXPECT_TRUE(sb.str() == "1234567890");
		EXPECT_TRUE(sb.sputc('1') == '1');
		EXPECT_TRUE(sb.str() == "12345678901");
	}
	{
		testbuf<wchar_t> sb(L"abc");
		EXPECT_TRUE(sb.sputc(L'1') == L'1');
		EXPECT_TRUE(sb.str() == L"1bc");
		EXPECT_TRUE(sb.sputc(L'2') == L'2');
		EXPECT_TRUE(sb.str() == L"12c");
		EXPECT_TRUE(sb.sputc(L'3') == L'3');
		EXPECT_TRUE(sb.str() == L"123");
		EXPECT_TRUE(sb.sputc(L'4') == L'4');
		EXPECT_TRUE(sb.str() == L"1234");
		EXPECT_TRUE(sb.sputc(L'5') == L'5');
		EXPECT_TRUE(sb.str() == L"12345");
		EXPECT_TRUE(sb.sputc(L'6') == L'6');
		EXPECT_TRUE(sb.str() == L"123456");
		EXPECT_TRUE(sb.sputc(L'7') == L'7');
		EXPECT_TRUE(sb.str() == L"1234567");
		EXPECT_TRUE(sb.sputc(L'8') == L'8');
		EXPECT_TRUE(sb.str() == L"12345678");
		EXPECT_TRUE(sb.sputc(L'9') == L'9');
		EXPECT_TRUE(sb.str() == L"123456789");
		EXPECT_TRUE(sb.sputc(L'0') == L'0');
		EXPECT_TRUE(sb.str() == L"1234567890");
		EXPECT_TRUE(sb.sputc(L'1') == L'1');
		EXPECT_TRUE(sb.str() == L"12345678901");
	}
	{
		testbuf<char> sb("abc", std::ios_base::app | std::ios_base::out);
		EXPECT_TRUE(sb.sputc('1') == '1');
		EXPECT_TRUE(sb.str() == "abc1");
		EXPECT_TRUE(sb.sputc('2') == '2');
		EXPECT_TRUE(sb.str() == "abc12");
	}
}

}	// namespace overflow_test

namespace pbackfail_test
{

template <typename CharT>
struct testbuf
	: public bksge::basic_stringbuf<CharT>
{
	using base = bksge::basic_stringbuf<CharT>;

	explicit testbuf(const std::basic_string<CharT>& str,
					 std::ios_base::openmode which = std::ios_base::in | std::ios_base::out)
		: base(str, which) {}

	typename base::int_type
		pbackfail(typename base::int_type c = base::traits_type::eof())
	{
		return base::pbackfail(c);
	}

	void pbump(int n) { base::pbump(n); }
};

GTEST_TEST(StringbufTest, PbackfailTest)
{
	{  // sanity check
		testbuf<char> tb("");
		tb.pbackfail();
	}
	{
		testbuf<char> sb("123", std::ios_base::in);
		EXPECT_TRUE(sb.sgetc() == '1');
		EXPECT_TRUE(sb.snextc() == '2');
		EXPECT_TRUE(sb.snextc() == '3');
		EXPECT_TRUE(sb.sgetc() == '3');
		EXPECT_TRUE(sb.snextc() == std::char_traits<char>::eof());
		EXPECT_TRUE(sb.pbackfail('3') == '3');
		EXPECT_TRUE(sb.pbackfail('3') == std::char_traits<char>::eof());
		EXPECT_TRUE(sb.pbackfail('2') == '2');
		EXPECT_TRUE(sb.pbackfail(std::char_traits<char>::eof()) != std::char_traits<char>::eof());
		EXPECT_TRUE(sb.pbackfail(std::char_traits<char>::eof()) == std::char_traits<char>::eof());
		EXPECT_TRUE(sb.str() == "123");
	}
	{
		testbuf<char> sb("123");
		EXPECT_TRUE(sb.sgetc() == '1');
		EXPECT_TRUE(sb.snextc() == '2');
		EXPECT_TRUE(sb.snextc() == '3');
		EXPECT_TRUE(sb.sgetc() == '3');
		EXPECT_TRUE(sb.snextc() == std::char_traits<char>::eof());
		EXPECT_TRUE(sb.pbackfail('3') == '3');
		EXPECT_TRUE(sb.pbackfail('3') == '3');
		EXPECT_TRUE(sb.pbackfail(std::char_traits<char>::eof()) != std::char_traits<char>::eof());
		EXPECT_TRUE(sb.pbackfail(std::char_traits<char>::eof()) == std::char_traits<char>::eof());
		EXPECT_TRUE(sb.str() == "133");
	}
	{
		testbuf<wchar_t> sb(L"123", std::ios_base::in);
		EXPECT_TRUE(sb.sgetc() == L'1');
		EXPECT_TRUE(sb.snextc() == L'2');
		EXPECT_TRUE(sb.snextc() == L'3');
		EXPECT_TRUE(sb.sgetc() == L'3');
		EXPECT_TRUE(sb.snextc() == std::char_traits<wchar_t>::eof());
		EXPECT_TRUE(sb.pbackfail(L'3') == L'3');
		EXPECT_TRUE(sb.pbackfail(L'3') == std::char_traits<wchar_t>::eof());
		EXPECT_TRUE(sb.pbackfail(L'2') == L'2');
		EXPECT_TRUE(sb.pbackfail(std::char_traits<wchar_t>::eof()) != std::char_traits<wchar_t>::eof());
		EXPECT_TRUE(sb.pbackfail(std::char_traits<wchar_t>::eof()) == std::char_traits<wchar_t>::eof());
		EXPECT_TRUE(sb.str() == L"123");
	}
	{
		testbuf<wchar_t> sb(L"123");
		EXPECT_TRUE(sb.sgetc() == L'1');
		EXPECT_TRUE(sb.snextc() == L'2');
		EXPECT_TRUE(sb.snextc() == L'3');
		EXPECT_TRUE(sb.sgetc() == L'3');
		EXPECT_TRUE(sb.snextc() == std::char_traits<wchar_t>::eof());
		EXPECT_TRUE(sb.pbackfail(L'3') == L'3');
		EXPECT_TRUE(sb.pbackfail(L'3') == L'3');
		EXPECT_TRUE(sb.pbackfail(std::char_traits<wchar_t>::eof()) != std::char_traits<wchar_t>::eof());
		EXPECT_TRUE(sb.pbackfail(std::char_traits<wchar_t>::eof()) == std::char_traits<wchar_t>::eof());
		EXPECT_TRUE(sb.str() == L"133");
	}
}

}	// namespace pbackfail_test

GTEST_TEST(StringbufTest, SeekoffTest)
{
	{
		bksge::stringbuf sb(std::ios_base::in);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(0, std::ios_base::beg, std::ios_base::in) == 0);
		EXPECT_TRUE(sb.pubseekoff(0, std::ios_base::cur, std::ios_base::in) == 0);
		EXPECT_TRUE(sb.pubseekoff(0, std::ios_base::end, std::ios_base::in) == 0);
	}
	{
		bksge::stringbuf sb(std::ios_base::out);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(0, std::ios_base::beg, std::ios_base::out) == 0);
		EXPECT_TRUE(sb.pubseekoff(0, std::ios_base::cur, std::ios_base::out) == 0);
		EXPECT_TRUE(sb.pubseekoff(0, std::ios_base::end, std::ios_base::out) == 0);
	}
	{
		bksge::stringbuf sb("0123456789", std::ios_base::in);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == '3');
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in) == 6);
		EXPECT_TRUE(sb.sgetc() == '6');
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in) == 7);
		EXPECT_TRUE(sb.sgetc() == '7');
	}
	{
		bksge::stringbuf sb("0123456789", std::ios_base::out);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out | std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out | std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out | std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out) == 3);
		EXPECT_TRUE(sb.sputc('a') == 'a');
		EXPECT_TRUE(sb.str() == "012a456789");
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out) == 7);
		EXPECT_TRUE(sb.sputc('b') == 'b');
		EXPECT_TRUE(sb.str() == "012a456b89");
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out) == 7);
		EXPECT_TRUE(sb.sputc('c') == 'c');
		EXPECT_TRUE(sb.str() == "012a456c89");
	}
	{
		bksge::stringbuf sb("0123456789");
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == '3');
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in) == 6);
		EXPECT_TRUE(sb.sgetc() == '6');
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in) == 7);
		EXPECT_TRUE(sb.sgetc() == '7');
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out | std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == '3');
		EXPECT_TRUE(sb.sputc('a') == 'a');
		EXPECT_TRUE(sb.str() == "012a456789");
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out | std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out | std::ios_base::in) == 7);
		EXPECT_TRUE(sb.sgetc() == '7');
		EXPECT_TRUE(sb.sputc('c') == 'c');
		EXPECT_TRUE(sb.str() == "012a456c89");
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out) == 3);
		EXPECT_TRUE(sb.sputc('3') == '3');
		EXPECT_TRUE(sb.str() == "0123456c89");
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out) == 7);
		EXPECT_TRUE(sb.sputc('7') == '7');
		EXPECT_TRUE(sb.str() == "0123456789");
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out) == 7);
		EXPECT_TRUE(sb.sputc('c') == 'c');
		EXPECT_TRUE(sb.str() == "0123456c89");
	}
	{
		bksge::wstringbuf sb(L"0123456789", std::ios_base::in);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == L'3');
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in) == 6);
		EXPECT_TRUE(sb.sgetc() == L'6');
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in) == 7);
		EXPECT_TRUE(sb.sgetc() == L'7');
	}
	{
		bksge::wstringbuf sb(L"0123456789", std::ios_base::out);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out | std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out | std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out | std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out) == 3);
		EXPECT_TRUE(sb.sputc(L'a') == L'a');
		EXPECT_TRUE(sb.str() == L"012a456789");
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out) == 7);
		EXPECT_TRUE(sb.sputc(L'b') == L'b');
		EXPECT_TRUE(sb.str() == L"012a456b89");
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out) == 7);
		EXPECT_TRUE(sb.sputc(L'c') == L'c');
		EXPECT_TRUE(sb.str() == L"012a456c89");
	}
	{
		bksge::wstringbuf sb(L"0123456789");
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == L'3');
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::in) == 6);
		EXPECT_TRUE(sb.sgetc() == L'6');
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::in) == 7);
		EXPECT_TRUE(sb.sgetc() == L'7');
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out | std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == L'3');
		EXPECT_TRUE(sb.sputc(L'a') == L'a');
		EXPECT_TRUE(sb.str() == L"012a456789");
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out | std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out | std::ios_base::in) == 7);
		EXPECT_TRUE(sb.sgetc() == L'7');
		EXPECT_TRUE(sb.sputc(L'c') == L'c');
		EXPECT_TRUE(sb.str() == L"012a456c89");
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::beg, std::ios_base::out) == 3);
		EXPECT_TRUE(sb.sputc(L'3') == L'3');
		EXPECT_TRUE(sb.str() == L"0123456c89");
		EXPECT_TRUE(sb.pubseekoff(3, std::ios_base::cur, std::ios_base::out) == 7);
		EXPECT_TRUE(sb.sputc(L'7') == L'7');
		EXPECT_TRUE(sb.str() == L"0123456789");
		EXPECT_TRUE(sb.pubseekoff(-3, std::ios_base::end, std::ios_base::out) == 7);
		EXPECT_TRUE(sb.sputc(L'c') == L'c');
		EXPECT_TRUE(sb.str() == L"0123456c89");
	}
}

#if 0	// TODO
GTEST_TEST(StringbufTest, SeekposTest)
{
	{
		bksge::stringbuf sb("0123456789", std::ios_base::in);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == '3');
	}
	{
		bksge::stringbuf sb("0123456789", std::ios_base::out);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::out | std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::out) == 3);
		EXPECT_TRUE(sb.sputc('a') == 'a');
		EXPECT_TRUE(sb.str() == "012a456789");
	}
	{
		bksge::stringbuf sb("0123456789");
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == '3');
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::out | std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == '3');
		EXPECT_TRUE(sb.sputc('a') == 'a');
		EXPECT_TRUE(sb.str() == "012a456789");
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::out) == 3);
		EXPECT_TRUE(sb.sputc('3') == '3');
		EXPECT_TRUE(sb.str() == "0123456789");
	}
	{
		bksge::wstringbuf sb(L"0123456789", std::ios_base::in);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::in | std::ios_base::out) == -1);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == L'3');
	}
	{
		bksge::wstringbuf sb(L"0123456789", std::ios_base::out);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::out | std::ios_base::in) == -1);
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::out) == 3);
		EXPECT_TRUE(sb.sputc(L'a') == L'a');
		EXPECT_TRUE(sb.str() == L"012a456789");
	}
	{
		bksge::wstringbuf sb(L"0123456789");
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == L'3');
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::out | std::ios_base::in) == 3);
		EXPECT_TRUE(sb.sgetc() == L'3');
		EXPECT_TRUE(sb.sputc(L'a') == L'a');
		EXPECT_TRUE(sb.str() == L"012a456789");
		EXPECT_TRUE(sb.pubseekpos(3, std::ios_base::out) == 3);
		EXPECT_TRUE(sb.sputc(L'3') == L'3');
		EXPECT_TRUE(sb.str() == L"0123456789");
	}
}
#endif

GTEST_TEST(StringbufTest, SetbufTest)
{
	{
		bksge::stringbuf sb("0123456789");
		EXPECT_TRUE(sb.pubsetbuf(0, 0) == &sb);
		EXPECT_TRUE(sb.str() == "0123456789");
	}
	{
		bksge::wstringbuf sb(L"0123456789");
		EXPECT_TRUE(sb.pubsetbuf(0, 0) == &sb);
		EXPECT_TRUE(sb.str() == L"0123456789");
	}
}

namespace underflow_test
{

template <typename CharT>
struct testbuf
	: public bksge::basic_stringbuf<CharT>
{
	using base = bksge::basic_stringbuf<CharT>;

	explicit testbuf(const std::basic_string<CharT>& str)
		: base(str) {}

	typename base::int_type underflow() { return base::underflow(); }

	void pbump(int n) { base::pbump(n); }
};

GTEST_TEST(StringbufTest, UnderflowTest)
{
	{
		testbuf<char> sb("123");
		sb.pbump(3);
		EXPECT_TRUE(sb.underflow() == '1');
		EXPECT_TRUE(sb.underflow() == '1');
		EXPECT_TRUE(sb.snextc() == '2');
		EXPECT_TRUE(sb.underflow() == '2');
		EXPECT_TRUE(sb.underflow() == '2');
		EXPECT_TRUE(sb.snextc() == '3');
		EXPECT_TRUE(sb.underflow() == '3');
		EXPECT_TRUE(sb.underflow() == '3');
		EXPECT_TRUE(sb.snextc() == std::char_traits<char>::eof());
		EXPECT_TRUE(sb.underflow() == std::char_traits<char>::eof());
		EXPECT_TRUE(sb.underflow() == std::char_traits<char>::eof());
		sb.sputc('4');
		EXPECT_TRUE(sb.underflow() == '4');
		EXPECT_TRUE(sb.underflow() == '4');
	}
	{
		testbuf<wchar_t> sb(L"123");
		sb.pbump(3);
		EXPECT_TRUE(sb.underflow() == L'1');
		EXPECT_TRUE(sb.underflow() == L'1');
		EXPECT_TRUE(sb.snextc() == L'2');
		EXPECT_TRUE(sb.underflow() == L'2');
		EXPECT_TRUE(sb.underflow() == L'2');
		EXPECT_TRUE(sb.snextc() == L'3');
		EXPECT_TRUE(sb.underflow() == L'3');
		EXPECT_TRUE(sb.underflow() == L'3');
		EXPECT_TRUE(sb.snextc() == std::char_traits<wchar_t>::eof());
		EXPECT_TRUE(sb.underflow() == std::char_traits<wchar_t>::eof());
		EXPECT_TRUE(sb.underflow() == std::char_traits<wchar_t>::eof());
		sb.sputc(L'4');
		EXPECT_TRUE(sb.underflow() == L'4');
		EXPECT_TRUE(sb.underflow() == L'4');
	}
}

}	// namespace underflow_test

GTEST_TEST(StringbufTest, TypesTest)
{
	static_assert((bksge::is_base_of<std::basic_streambuf<char>, bksge::basic_stringbuf<char>>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringbuf<char>::char_type, char>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringbuf<char>::traits_type, std::char_traits<char>>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringbuf<char>::int_type, std::char_traits<char>::int_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringbuf<char>::pos_type, std::char_traits<char>::pos_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringbuf<char>::off_type, std::char_traits<char>::off_type>::value), "");
	static_assert((bksge::is_same<bksge::basic_stringbuf<char>::allocator_type, bksge::allocator<char>>::value), "");
}

}	// namespace stringbuf_test

}	// namespace bksge_sstream_test
