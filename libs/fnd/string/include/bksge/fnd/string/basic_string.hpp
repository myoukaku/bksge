/**
 *	@file	basic_string.hpp
 *
 *	@brief	basic_string の定義
 *
 *	@author	myoukaku
 */

#ifndef BKSGE_FND_STRING_BASIC_STRING_HPP
#define BKSGE_FND_STRING_BASIC_STRING_HPP

#include <bksge/fnd/string/config.hpp>

#if defined(BKSGE_USE_STD_STRING)

#include <string>

namespace bksge
{

using std::basic_string;

}	// namespace bksge

#else

#include <bksge/fnd/string/detail/alloc_on_copy.hpp>
#include <bksge/fnd/string/detail/alloc_on_move.hpp>
#include <bksge/fnd/string/detail/alloc_on_swap.hpp>
#include <bksge/fnd/string/detail/allocator_like.hpp>
#include <bksge/fnd/string/detail/is_char.hpp>
#include <bksge/fnd/string/detail/is_null_pointer.hpp>
#include <bksge/fnd/string/char_traits.hpp>
#include <bksge/fnd/algorithm/min.hpp>
#include <bksge/fnd/concepts/detail/require.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/cstddef/nullptr_t.hpp>
#include <bksge/fnd/functional/less.hpp>
#include <bksge/fnd/ostream/basic_ostream.hpp>
#include <bksge/fnd/iterator/distance.hpp>
#include <bksge/fnd/iterator/normal_iterator.hpp>
#include <bksge/fnd/iterator/reverse_iterator.hpp>
#include <bksge/fnd/iterator/iterator_traits.hpp>
#include <bksge/fnd/iterator/tag.hpp>
#include <bksge/fnd/iterator/concepts/detail/cpp17_input_iterator.hpp>
#include <bksge/fnd/memory/addressof.hpp>
#include <bksge/fnd/memory/allocator.hpp>
#include <bksge/fnd/memory/allocator_traits.hpp>
#include <bksge/fnd/memory/pointer_traits.hpp>
#include <bksge/fnd/string_view/basic_string_view.hpp>
#include <bksge/fnd/stdexcept/out_of_range.hpp>
#include <bksge/fnd/stdexcept/length_error.hpp>
#include <bksge/fnd/stdexcept/logic_error.hpp>
#include <bksge/fnd/type_traits/bool_constant.hpp>
#include <bksge/fnd/type_traits/enable_if.hpp>
#include <bksge/fnd/type_traits/conjunction.hpp>
#include <bksge/fnd/type_traits/is_convertible.hpp>
#include <bksge/fnd/type_traits/is_nothrow_default_constructible.hpp>
#include <bksge/fnd/type_traits/is_same.hpp>
#include <bksge/fnd/type_traits/negation.hpp>
#include <bksge/fnd/type_traits/void_t.hpp>
#include <bksge/fnd/utility/declval.hpp>
#include <bksge/fnd/utility/move.hpp>
#include <bksge/fnd/utility/swap.hpp>
#include <bksge/fnd/config.hpp>
#include <bksge/fnd/assert.hpp>
#include <initializer_list>
#include <limits>
#include <istream>

namespace bksge
{

namespace detail
{

// Helper for basic_string and basic_string_view members.
inline BKSGE_CXX14_CONSTEXPR bksge::size_t
sv_check_pos(bksge::size_t size, bksge::size_t pos, char const* s)
{
	if (pos > size)
	{
		//__throw_out_of_range_fmt(__N("%s: pos (which is %zu) > size "
		//	"(which is %zu)"), s, pos, size);
		bksge::throw_out_of_range(s);
	}
	return pos;
}

// Helper for basic_string members.
// NB: sv_limit doesn't check for a bad pos value.
inline BKSGE_CONSTEXPR bksge::size_t
sv_limit(bksge::size_t size, bksge::size_t pos, bksge::size_t off) BKSGE_NOEXCEPT
{
	return (off < size - pos) ? off : size - pos;
}

}	// namespace detail

template <
	typename CharT,
	typename Traits = bksge::char_traits<CharT>,
	typename Allocator = bksge::allocator<CharT>
>
class basic_string;

template <typename CharT, typename Traits, typename Allocator>
class basic_string
{
private:
	using CharAllocType = typename bksge::allocator_traits<Allocator>::template rebind_alloc<CharT>;
	using AllocTraits = bksge::allocator_traits<CharAllocType>;

public:
	using traits_type            = Traits;
	using value_type             = typename Traits::char_type;// CharT;
	using allocator_type         = CharAllocType;// Allocator;
	using size_type              = typename AllocTraits::size_type;
	using difference_type        = typename AllocTraits::difference_type;
	using reference              = value_type&;
	using const_reference        = value_type const&;
	using pointer                = typename AllocTraits::pointer;
	using const_pointer          = typename AllocTraits::const_pointer;
	using iterator               = bksge::normal_iterator<pointer, basic_string>;
	using const_iterator         = bksge::normal_iterator<const_pointer, basic_string>;
	using const_reverse_iterator = bksge::reverse_iterator<const_iterator>;
	using reverse_iterator       = bksge::reverse_iterator<iterator>;

	///  Value returned by various member functions when they fail.
	static size_type const npos = static_cast<size_type>(-1);

private:
	// A helper type for avoiding boiler-plate.
	using string_view_type = bksge::basic_string_view<CharT, Traits>;

	template <typename T, typename Res>
	using enable_if_string_view = bksge::enable_if_t<
		bksge::conjunction<
			bksge::is_convertible<T const&, string_view_type>,
			bksge::negation<bksge::is_convertible<T const*, basic_string const*>>,
			bksge::negation<bksge::is_convertible<T const&, CharT const*>>
		>::value,
		Res>;

	// Allows an implicit conversion to string_view_type.
	static BKSGE_CONSTEXPR string_view_type
	ToStringView(string_view_type svt) BKSGE_NOEXCEPT
	{
		return svt;
	}

	// Wraps a string_view by explicit conversion and thus
	// allows to add an internal constructor that does not
	// participate in overload resolution when a string_view
	// is provided.
	struct StringViewWrapper
	{
		explicit BKSGE_CONSTEXPR
		StringViewWrapper(string_view_type sv) BKSGE_NOEXCEPT
			: m_sv(sv) {}

		string_view_type m_sv;
	};

	/**
	 *  @brief  Only internally used: Construct string from a string view
	 *          wrapper.
	 *  @param  svw  string view wrapper.
	 *  @param  a  Allocator to use.
	 */
	explicit BKSGE_CONSTEXPR
	basic_string(StringViewWrapper svw, Allocator const& a)
		: basic_string(svw.m_sv.data(), svw.m_sv.size(), a) {}

	// Use empty-base optimization: http://www.cantrip.org/emptyopt.html
	struct AllocHider : public allocator_type // TODO check __is_final
	{
		BKSGE_CONSTEXPR
		AllocHider(pointer dat, Allocator const& a)
			: allocator_type(a)
			, m_p(dat) {}

		BKSGE_CONSTEXPR
		AllocHider(pointer dat, Allocator&& a = Allocator())
			: allocator_type(bksge::move(a))
			, m_p(dat) {}

		pointer m_p; // The actual data.
	};

	AllocHider	m_dataplus;
	size_type	m_string_length;

	enum { s_local_capacity = 15 / sizeof(CharT) };

	union
	{
		CharT		m_local_buf[s_local_capacity + 1];
		size_type	m_allocated_capacity;
	};

	BKSGE_CXX14_CONSTEXPR void SetData(pointer p)
	{
		m_dataplus.m_p = p;
	}

	BKSGE_CXX14_CONSTEXPR void SetLength(size_type len)
	{
		m_string_length = len;
	}

	BKSGE_CXX14_CONSTEXPR void SetCapacity(size_type cap)
	{
		m_allocated_capacity = cap;
	}

	BKSGE_CXX14_CONSTEXPR void SetLengthAndNullTerminate(size_type len)
	{
		SetLength(len);
		traits_type::assign(GetData()[len], CharT());
	}

	BKSGE_CONSTEXPR pointer GetData() const
	{
		return m_dataplus.m_p;
	}

	BKSGE_CXX14_CONSTEXPR pointer GetLocalData()
	{
		return bksge::pointer_traits<pointer>::pointer_to(*m_local_buf);
	}

	BKSGE_CONSTEXPR const_pointer GetLocalData() const
	{
		return bksge::pointer_traits<const_pointer>::pointer_to(*m_local_buf);
	}

	BKSGE_CXX14_CONSTEXPR allocator_type& GetAllocator()
	{
		return m_dataplus;
	}

	BKSGE_CONSTEXPR allocator_type const& GetAllocator() const
	{
		return m_dataplus;
	}

	BKSGE_CONSTEXPR bool IsLocal() const
	{
		return GetData() == GetLocalData();
	}

	// Create & Destroy
	BKSGE_CXX14_CONSTEXPR pointer
	Create(size_type& capacity, size_type old_capacity)
	{
		if (capacity > max_size())
		{
			bksge::throw_length_error("basic_string::Create");
		}

		if (capacity > old_capacity && capacity < (2 * old_capacity))
		{
			capacity = 2 * old_capacity;
			// Never allocate a string bigger than max_size.
			if (capacity > max_size())
			{
				capacity = max_size();
			}
		}

		// NB: Need an array of char_type[capacity], plus a terminating
		// null char_type() element.
		return AllocTraits::allocate(GetAllocator(), capacity + 1);
	}

	BKSGE_CXX14_CONSTEXPR void Dispose()
	{
		if (!IsLocal())
		{
			Destroy(m_allocated_capacity);
		}
	}

	BKSGE_CXX14_CONSTEXPR void Destroy(size_type size) BKSGE_NOEXCEPT
	{
		AllocTraits::deallocate(GetAllocator(), GetData(), size + 1);
	}

	// For Input Iterators, used in istreambuf_iterators, etc.
	template <typename InputIterator>
	BKSGE_CXX20_CONSTEXPR void
	ConstructAux(InputIterator first, InputIterator last, bksge::input_iterator_tag)
	{
		size_type len = 0;
		size_type capacity = size_type(s_local_capacity);

		while (first != last && len < capacity)
		{
			GetData()[len++] = *first;
			++first;
		}

		try
		{
			while (first != last)
			{
				if (len == capacity)
				{
					// Allocate more space.
					capacity = len + 1;
					pointer another = Create(capacity, len);
					this->CopyImpl(another, GetData(), len);
					Dispose();
					SetData(another);
					SetCapacity(capacity);
				}
				GetData()[len++] = *first;
				++first;
			}
		}
		catch(...)
		{
			Dispose();
			//__throw_exception_again;
			throw;
		}

		SetLengthAndNullTerminate(len);
	}

	// For forward_iterators up to random_access_iterators, used for
	// string::iterator, CharT*, etc.
	template <typename ForwardIterator>
	BKSGE_CXX20_CONSTEXPR void
	ConstructAux(ForwardIterator first, ForwardIterator last, bksge::forward_iterator_tag)
	{
		// NB: Not required, but considered best practice.
		if (detail::is_null_pointer(first) && first != last)
		{
			bksge::throw_logic_error("basic_string::Construct null not valid");
		}

		size_type dnew = static_cast<size_type>(bksge::distance(first, last));

		if (dnew > size_type(s_local_capacity))
		{
			SetData(Create(dnew, size_type(0)));
			SetCapacity(dnew);
		}

		// Check for out_of_range and length_error exceptions.
		try
		{
			this->CopyCharsImpl(GetData(), first, last);
		}
		catch(...)
		{
			Dispose();
			//__throw_exception_again;
			throw;
		}

		SetLengthAndNullTerminate(dnew);
	}

	template <typename InIterator>
	BKSGE_CXX14_CONSTEXPR void
	Construct(InIterator first, InIterator last)
	{
		using tag = typename bksge::iterator_traits<InIterator>::iterator_category;
		ConstructAux(first, last, tag());
	}

	BKSGE_CXX14_CONSTEXPR void
	Construct(size_type n, CharT c)
	{
		if (n > size_type(s_local_capacity))
		{
			SetData(Create(n, size_type(0)));
			SetCapacity(n);
		}

		if (n)
		{
			this->AssignImpl(GetData(), n, c);
		}

		SetLengthAndNullTerminate(n);
	}

	//BKSGE_CXX14_CONSTEXPR size_type
	//_M_check(size_type pos, char const* s) const
	//{
	//	if (pos > this->size())
	//	{
	//		//__throw_out_of_range_fmt(__N("%s: pos (which is %zu) > "
	//		//	"this->size() (which is %zu)"),
	//		//	s, pos, this->size());
	//		bksge::throw_out_of_range(s);
	//	}
	//	return pos;
	//}

	BKSGE_CXX14_CONSTEXPR void
	CheckLength(size_type n1, size_type n2, char const* s) const
	{
		if (this->max_size() - (this->size() - n1) < n2)
		{
			bksge::throw_length_error(s);
		}
	}

	// NB: _M_limit doesn't check for a bad pos value.
	//BKSGE_CXX14_CONSTEXPR size_type
	//_M_limit(size_type pos, size_type off) const BKSGE_NOEXCEPT
	//{
	//	const bool __testoff =  off < this->size() - pos;
	//	return __testoff ? off : this->size() - pos;
	//}

	// True if _Rep and source do not overlap.
	BKSGE_CXX14_CONSTEXPR bool
	Disjunct(CharT const* s) const BKSGE_NOEXCEPT
	{
		return (
			bksge::less<CharT const*>()(s, GetData()) ||
			bksge::less<CharT const*>()(GetData() + this->size(), s));
	}

	// When n = 1 way faster than the general multichar
	// traits_type::copy/move/assign.
	static BKSGE_CXX14_CONSTEXPR void
	CopyImpl(CharT* d, CharT const* s, size_type n)
	{
		if (n == 1)
		{
			traits_type::assign(*d, *s);
		}
		else
		{
			traits_type::copy(d, s, n);
		}
	}

	static BKSGE_CXX14_CONSTEXPR void
	MoveImpl(CharT* d, CharT const* s, size_type n)
	{
		if (n == 1)
		{
			traits_type::assign(*d, *s);
		}
		else
		{
			traits_type::move(d, s, n);
		}
	}

	static BKSGE_CXX14_CONSTEXPR void
	AssignImpl(CharT* d, size_type n, CharT c)
	{
		if (n == 1)
		{
			traits_type::assign(*d, c);
		}
		else
		{
			traits_type::assign(d, n, c);
		}
	}

	// CopyCharsImpl is a separate template to permit specialization
	// to optimize for the common case of pointers as iterators.
	template <typename Iterator>
	static BKSGE_CXX14_CONSTEXPR void
	CopyCharsImpl(CharT* p, Iterator k1, Iterator k2)
	{
		for (; k1 != k2; ++k1, (void)++p)
		{
			traits_type::assign(*p, *k1); // These types are off.
		}
	}

	static BKSGE_CXX14_CONSTEXPR void
	CopyCharsImpl(CharT* p, CharT* k1, CharT* k2) BKSGE_NOEXCEPT
	{
		CopyImpl(p, k1, k2 - k1);
	}

	static BKSGE_CXX14_CONSTEXPR void
	CopyCharsImpl(CharT* p, CharT const* k1, CharT const* k2) BKSGE_NOEXCEPT
	{
		CopyImpl(p, k1, k2 - k1);
	}

	static BKSGE_CXX14_CONSTEXPR void
	CopyCharsImpl(CharT* p, iterator k1, iterator k2) BKSGE_NOEXCEPT
	{
		CopyCharsImpl(p, k1.base(), k2.base());
	}

	static BKSGE_CXX14_CONSTEXPR void
	CopyCharsImpl(CharT* p, const_iterator k1, const_iterator k2) BKSGE_NOEXCEPT
	{
		CopyCharsImpl(p, k1.base(), k2.base());
	}

	static BKSGE_CXX14_CONSTEXPR int
	CompareImpl(size_type n1, size_type n2) BKSGE_NOEXCEPT
	{
		difference_type const d = difference_type(n1 - n2);

		if (d > std::numeric_limits<int>::max())
		{
			return std::numeric_limits<int>::max();
		}
		else if (d < std::numeric_limits<int>::min())
		{
			return std::numeric_limits<int>::min();
		}
		else
		{
			return int(d);
		}
	}

	BKSGE_CXX14_CONSTEXPR void
	Assign(basic_string const& str)
	{
		if (this != &str)
		{
			size_type const rsize = str.length();
			size_type const cap = capacity();

			if (rsize > cap)
			{
				size_type new_capacity = rsize;
				pointer tmp = Create(new_capacity, cap);
				Dispose();
				SetData(tmp);
				SetCapacity(new_capacity);
			}

			if (rsize)
			{
				this->CopyImpl(GetData(), str.GetData(), rsize);
			}

			SetLengthAndNullTerminate(rsize);
		}
	}

	BKSGE_CXX14_CONSTEXPR void
	Mutate(size_type pos, size_type len1, CharT const* s, size_type len2)
	{
		size_type const how_much = length() - pos - len1;

		size_type new_capacity = length() + len2 - len1;
		pointer r = Create(new_capacity, capacity());

		if (pos)
		{
			this->CopyImpl(r, GetData(), pos);
		}

		if (s && len2)
		{
			this->CopyImpl(r + pos, s, len2);
		}

		if (how_much)
		{
			this->CopyImpl(r + pos + len2, GetData() + pos + len1, how_much);
		}

		Dispose();
		SetData(r);
		SetCapacity(new_capacity);
	}

	BKSGE_CXX14_CONSTEXPR void
	Erase(size_type pos, size_type n)
	{
		size_type const how_much = length() - pos - n;

		if (how_much && n)
		{
			this->MoveImpl(GetData() + pos, GetData() + pos + n, how_much);
		}

		SetLengthAndNullTerminate(length() - n);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	Append(CharT const* s, size_type count)
	{
		size_type const len = count + this->size();

		if (len <= this->capacity())
		{
			if (count)
			{
				this->CopyImpl(this->GetData() + this->size(), s, count);
			}
		}
		else
		{
			this->Mutate(this->size(), size_type(0), s, count);
		}

		this->SetLengthAndNullTerminate(len);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	Replace(size_type pos1, size_type count1, size_type count2, CharT c)
	{
		CheckLength(count1, count2, "basic_string::Replace");

		size_type const old_size = this->size();
		size_type const new_size = old_size + count2 - count1;

		if (new_size <= this->capacity())
		{
			pointer p = this->GetData() + pos1;

			size_type const how_much = old_size - pos1 - count1;
			if (how_much && count1 != count2)
			{
				this->MoveImpl(p + count2, p + count1, how_much);
			}
		}
		else
		{
			this->Mutate(pos1, count1, 0, count2);
		}

		if (count2)
		{
			this->AssignImpl(this->GetData() + pos1, count2, c);
		}

		this->SetLengthAndNullTerminate(new_size);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	Replace(size_type pos, size_type len1, CharT const* s, size_type const len2)
	{
		CheckLength(len1, len2, "basic_string::Replace");

		size_type const old_size = this->size();
		size_type const new_size = old_size + len2 - len1;

		if (new_size <= this->capacity())
		{
			pointer p = this->GetData() + pos;

			size_type const how_much = old_size - pos - len1;
			if (Disjunct(s))
			{
				if (how_much && len1 != len2)
				{
					this->MoveImpl(p + len2, p + len1, how_much);
				}

				if (len2)
				{
					this->CopyImpl(p, s, len2);
				}
			}
			else
			{
				// Work in-place.
				if (len2 && len2 <= len1)
				{
					this->MoveImpl(p, s, len2);
				}

				if (how_much && len1 != len2)
				{
					this->MoveImpl(p + len2, p + len1, how_much);
				}

				if (len2 > len1)
				{
					if (s + len2 <= p + len1)
					{
						this->MoveImpl(p, s, len2);
					}
					else if (s >= p + len1)
					{
						this->CopyImpl(p, s + len2 - len1, len2);
					}
					else
					{
						size_type const nleft = (p + len1) - s;
						this->MoveImpl(p, s, nleft);
						this->CopyImpl(p + nleft, p + len2, len2 - nleft);
					}
				}
			}
		}
		else
		{
			this->Mutate(pos, len1, s, len2);
		}

		this->SetLengthAndNullTerminate(new_size);
		return *this;
	}

public:
	// construct from std::basic_string
	template <typename Traits2, typename Allocator2>
	BKSGE_CXX14_CONSTEXPR
	basic_string(std::basic_string<CharT, Traits2, Allocator2> const& str)
		: basic_string(str.begin(), str.end())
	{}

	// convert to std::basic_string
	template <typename Traits2, typename Allocator2>
	BKSGE_CXX14_CONSTEXPR
	operator std::basic_string<CharT, Traits2, Allocator2>() const
	{
		return std::basic_string<CharT, Traits2, Allocator2>(begin(), end());
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string()
		BKSGE_NOEXCEPT_IF(bksge::is_nothrow_default_constructible<Allocator>::value)
		: m_dataplus(GetLocalData())
	{
		SetLengthAndNullTerminate(0);
	}

	explicit BKSGE_CXX14_CONSTEXPR
	basic_string(Allocator const& alloc) BKSGE_NOEXCEPT
		: m_dataplus(GetLocalData(), alloc)
	{
		SetLengthAndNullTerminate(0);
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string(basic_string const& str)
		: m_dataplus(GetLocalData(), AllocTraits::select_on_container_copy_construction(str.GetAllocator()))
	{
		Construct(str.GetData(), str.GetData() + str.length());
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string(basic_string const& str, size_type pos, Allocator const& alloc = Allocator())
		: m_dataplus(GetLocalData(), alloc)
	{
		CharT const* first = str.GetData() + detail::sv_check_pos(str.size(), pos, "basic_string::basic_string");
		Construct(first, first + detail::sv_limit(str.size(), pos, npos));
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string(basic_string const& str, size_type pos, size_type count)
		: m_dataplus(GetLocalData())
	{
		CharT const* first = str.GetData() + detail::sv_check_pos(str.size(), pos, "basic_string::basic_string");
		Construct(first, first + detail::sv_limit(str.size(), pos, count));
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string(basic_string const& str, size_type pos, size_type count, Allocator const& alloc)
		: m_dataplus(GetLocalData(), alloc)
	{
		CharT const* first = str.GetData() + detail::sv_check_pos(str.size(), pos, "basic_string::basic_string");
		Construct(first, first + detail::sv_limit(str.size(), pos, count));
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string(CharT const* s, size_type count, Allocator const& alloc = Allocator())
		: m_dataplus(GetLocalData(), alloc)
	{
		Construct(s, s + count);
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string(CharT const* s, Allocator const& alloc = Allocator())
		: m_dataplus(GetLocalData(), alloc)
	{
		Construct(s, s ? s + traits_type::length(s) : s+npos);
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string(size_type count, CharT c, Allocator const& alloc = Allocator())
		: m_dataplus(GetLocalData(), alloc)
	{
		Construct(count, c);
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string(basic_string&& str) BKSGE_NOEXCEPT
		: m_dataplus(GetLocalData(), bksge::move(str.GetAllocator()))
	{
		if (str.IsLocal())
		{
			traits_type::copy(m_local_buf, str.m_local_buf, s_local_capacity + 1);
		}
		else
		{
			SetData(str.GetData());
			SetCapacity(str.m_allocated_capacity);
		}

		// Must use SetLength() here not SetLengthAndNullTerminate() because
		// basic_stringbuf relies on writing into unallocated capacity so
		// we mess up the contents if we put a '\0' in the string.
		SetLength(str.length());
		str.SetData(str.GetLocalData());
		str.SetLengthAndNullTerminate(0);
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string(std::initializer_list<CharT> ilist, Allocator const& alloc = Allocator())
		: m_dataplus(GetLocalData(), alloc)
	{
		Construct(ilist.begin(), ilist.end());
	}

	BKSGE_CXX14_CONSTEXPR
	basic_string(basic_string const& str, Allocator const& alloc)
		: m_dataplus(GetLocalData(), alloc)
	{
		Construct(str.begin(), str.end());
	}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant

	BKSGE_CXX14_CONSTEXPR
	basic_string(basic_string&& str, Allocator const& alloc)
		BKSGE_NOEXCEPT((AllocTraits::is_always_equal::value))
		: m_dataplus(GetLocalData(), alloc)
	{
		if (str.IsLocal())
		{
			traits_type::copy(m_local_buf, str.m_local_buf, s_local_capacity + 1);
			SetLength(str.length());
			str.SetLengthAndNullTerminate(0);
		}
		else if (AllocTraits::is_always_equal::value || str.get_allocator() == alloc)
		{
			SetData(str.GetData());
			SetLength(str.length());
			SetCapacity(str.m_allocated_capacity);
			str.SetData(str.m_local_buf);
			str.SetLengthAndNullTerminate(0);
		}
		else
		{
			Construct(str.begin(), str.end());
		}
	}

BKSGE_WARNING_POP();

	template <BKSGE_REQUIRES_PARAM(bksge::detail::cpp17_input_iterator, InputIterator)>
	BKSGE_CXX14_CONSTEXPR
	basic_string(InputIterator first, InputIterator last, Allocator const& alloc = Allocator())
		: m_dataplus(GetLocalData(), alloc)
	{
		Construct(first, last);
	}

	template <typename T, typename = enable_if_string_view<T, void>>
	BKSGE_CXX14_CONSTEXPR
	basic_string(T const& t, size_type pos, size_type count, Allocator const& alloc = Allocator())
		: basic_string(ToStringView(t).substr(pos, count), alloc) {}

	template <typename T, typename = enable_if_string_view<T, void>>
	explicit BKSGE_CXX14_CONSTEXPR
	basic_string(T const& t, Allocator const& alloc = Allocator())
		: basic_string(StringViewWrapper(ToStringView(t)), alloc) {}

	~basic_string()
	{
		Dispose();
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	operator=(basic_string const& str)
	{
		return this->assign(str);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	operator=(CharT const* s)
	{
		return this->assign(s);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	operator=(CharT c)
	{
		this->assign(1, c);
		return *this;
	}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant

	BKSGE_CXX14_CONSTEXPR basic_string&
	operator=(basic_string&& str)
		BKSGE_NOEXCEPT((
			AllocTraits::propagate_on_container_move_assignment::value ||
			AllocTraits::is_always_equal::value))
	{
		if (!IsLocal() &&
			AllocTraits::propagate_on_container_move_assignment::value &&
			!AllocTraits::is_always_equal::value &&
			GetAllocator() != str.GetAllocator())
		{
			// Destroy existing storage before replacing allocator.
			Destroy(m_allocated_capacity);
			SetData(GetLocalData());
			SetLengthAndNullTerminate(0);
		}

		// Replace allocator if POCMA is true.
		detail::alloc_on_move(GetAllocator(), str.GetAllocator());

		if (str.IsLocal())
		{
			// We've always got room for a short string, just copy it
			// (unless this is a self-move, because that would violate the
			// char_traits::copy precondition that the ranges don't overlap).

			// TODO
			//if (__builtin_expect(bksge::addressof(str) != this, true))
			if (bksge::addressof(str) != this)
			{
				if (str.size())
				{
					this->CopyImpl(GetData(), str.GetData(), str.size());
				}
				SetLengthAndNullTerminate(str.size());
			}
		}
		else if (
			AllocTraits::propagate_on_container_move_assignment::value ||
			AllocTraits::is_always_equal::value ||
			GetAllocator() == str.GetAllocator())
		{
			// Just move the allocated pointer, our allocator can free it.
			pointer data = nullptr;
			size_type capacity = 0;
			if (!IsLocal())
			{
				if (AllocTraits::is_always_equal::value)
				{
					// str can reuse our existing storage.
					data = GetData();
					capacity = m_allocated_capacity;
				}
				else // str can't use it, so free it.
				{
					Destroy(m_allocated_capacity);
				}
			}

			SetData(str.GetData());
			SetLength(str.length());
			SetCapacity(str.m_allocated_capacity);

			if (data)
			{
				str.SetData(data);
				str.SetCapacity(capacity);
			}
			else
			{
				str.SetData(str.m_local_buf);
			}
		}
		else // Need to do a deep copy
		{
			assign(str);
		}

		str.clear();
		return *this;
	}

BKSGE_WARNING_POP();

	BKSGE_CXX14_CONSTEXPR basic_string&
	operator=(std::initializer_list<CharT> ilist)
	{
		this->assign(ilist.begin(), ilist.size());
		return *this;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR
	enable_if_string_view<T, basic_string&>
	operator=(T const& svt)
	{
		return this->assign(svt);
	}

	BKSGE_CONSTEXPR
	operator string_view_type() const BKSGE_NOEXCEPT
	{
		return string_view_type(data(), size());
	}

	BKSGE_CXX14_CONSTEXPR
	iterator begin() BKSGE_NOEXCEPT
	{
		return iterator(GetData());
	}

	BKSGE_CONSTEXPR
	const_iterator begin() const BKSGE_NOEXCEPT
	{
		return const_iterator(GetData());
	}

	BKSGE_CXX14_CONSTEXPR
	iterator end() BKSGE_NOEXCEPT
	{
		return iterator(GetData() + this->size());
	}

	BKSGE_CONSTEXPR
	const_iterator end() const BKSGE_NOEXCEPT
	{
		return const_iterator(GetData() + this->size());
	}

	BKSGE_CXX14_CONSTEXPR
	reverse_iterator rbegin() BKSGE_NOEXCEPT
	{
		return reverse_iterator(this->end());
	}

	BKSGE_CONSTEXPR
	const_reverse_iterator rbegin() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(this->end());
	}

	BKSGE_CXX14_CONSTEXPR
	reverse_iterator rend() BKSGE_NOEXCEPT
	{
		return reverse_iterator(this->begin());
	}

	BKSGE_CONSTEXPR
	const_reverse_iterator rend() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(this->begin());
	}

	BKSGE_CONSTEXPR
	const_iterator cbegin() const BKSGE_NOEXCEPT
	{
		return const_iterator(this->GetData());
	}

	BKSGE_CONSTEXPR
	const_iterator cend() const BKSGE_NOEXCEPT
	{
		return const_iterator(this->GetData() + this->size());
	}

	BKSGE_CONSTEXPR
	const_reverse_iterator crbegin() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(this->end());
	}

	BKSGE_CONSTEXPR
	const_reverse_iterator crend() const BKSGE_NOEXCEPT
	{
		return const_reverse_iterator(this->begin());
	}

public:
	BKSGE_CONSTEXPR
	size_type size() const BKSGE_NOEXCEPT
	{
		return m_string_length;
	}

	BKSGE_CONSTEXPR
	size_type length() const BKSGE_NOEXCEPT
	{
		return m_string_length;
	}

	BKSGE_CONSTEXPR
	size_type max_size() const BKSGE_NOEXCEPT
	{
		return (AllocTraits::max_size(GetAllocator()) - 1) / 2;
	}

	BKSGE_CXX14_CONSTEXPR
	void resize(size_type count, CharT c)
	{
		size_type const sz = this->size();
		if (sz < count)
		{
			this->append(count - sz, c);
		}
		else if (count < sz)
		{
			this->SetLengthAndNullTerminate(count);
		}
	}

	BKSGE_CXX14_CONSTEXPR
	void resize(size_type count)
	{
		this->resize(count, CharT());
	}

	BKSGE_CONSTEXPR
	size_type capacity() const BKSGE_NOEXCEPT
	{
		return IsLocal() ? size_type(s_local_capacity) : m_allocated_capacity;
	}

	BKSGE_CXX20_CONSTEXPR
	void shrink_to_fit() BKSGE_NOEXCEPT
	{
		if (IsLocal())
		{
			return;
		}

		size_type const length = this->length();
		size_type const capacity = m_allocated_capacity;

		if (length <= size_type(s_local_capacity))
		{
			this->CopyImpl(GetLocalData(), GetData(), length + 1);
			Destroy(capacity);
			SetData(GetLocalData());
		}
#if !defined(BKSGE_NO_EXCEPTIONS)
		else if (length < capacity)
		{
			try
			{
				pointer tmp = AllocTraits::allocate(GetAllocator(), length + 1);
				this->CopyImpl(tmp, GetData(), length + 1);
				Dispose();
				SetData(tmp);
				SetCapacity(length);
			}
			// TODO
			/*catch (__cxxabiv1::__forced_unwind const&)
			{
				throw;
			}*/
			catch (...)
			{
				/* swallow the exception */
			}
		}
#endif
	}

	BKSGE_CXX14_CONSTEXPR
	void reserve(size_type new_cap)
	{
		size_type const cap = capacity();

		if (new_cap <= cap)
		{
			return;
		}

		pointer tmp = Create(new_cap, cap);
		this->CopyImpl(tmp, GetData(), length() + 1);
		Dispose();
		SetData(tmp);
		SetCapacity(new_cap);
	}

	BKSGE_DEPRECATED("use shrink_to_fit() instead")
	BKSGE_CXX14_CONSTEXPR
	void reserve()
	{
		shrink_to_fit();
	}

	BKSGE_CXX14_CONSTEXPR
	void clear() BKSGE_NOEXCEPT
	{
		SetLengthAndNullTerminate(0);
	}

	BKSGE_NODISCARD BKSGE_CONSTEXPR bool
	empty() const BKSGE_NOEXCEPT
	{
		return this->size() == 0;
	}

	BKSGE_CONSTEXPR const_reference
	operator[] (size_type pos) const BKSGE_NOEXCEPT
	{
		// Allow pos == size().
		BKSGE_ASSERT(pos <= size());
		return GetData()[pos];
	}

	BKSGE_CXX14_CONSTEXPR reference
	operator[](size_type pos) BKSGE_NOEXCEPT
	{
		// Allow pos == size().
		BKSGE_ASSERT(pos <= size());
		return GetData()[pos];
	}

	BKSGE_CONSTEXPR const_reference
	at(size_type pos) const
	{
		if (pos >= this->size())
		{
			//__throw_out_of_range_fmt(__N("basic_string::at: pos "
			//	"(which is %zu) >= this->size() "
			//	"(which is %zu)"),
			//	pos, this->size());
			bksge::throw_out_of_range("basic_string::at");
		}
		return GetData()[pos];
	}

	BKSGE_CXX14_CONSTEXPR reference
	at(size_type pos)
	{
		if (pos >= size())
		{
			//__throw_out_of_range_fmt(__N("basic_string::at: pos "
			//	"(which is %zu) >= this->size() "
			//	"(which is %zu)"),
			//	pos, this->size());
			bksge::throw_out_of_range("basic_string::at");
		}
		return GetData()[pos];
	}

	BKSGE_CXX14_CONSTEXPR reference front() BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(!empty());
		return operator[](0);
	}

	BKSGE_CONSTEXPR const_reference front() const BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(!empty());
		return operator[](0);
	}

	BKSGE_CXX14_CONSTEXPR reference back() BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(!empty());
		return operator[](this->size() - 1);
	}

	BKSGE_CONSTEXPR const_reference back() const BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(!empty());
		return operator[](this->size() - 1);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	operator+=(basic_string const& str)
	{
		return this->append(str);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	operator+=(CharT const* s)
	{
		return this->append(s);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	operator+=(CharT c)
	{
		this->push_back(c);
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	operator+=(std::initializer_list<CharT> ilist)
	{
		return this->append(ilist.begin(), ilist.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR
	enable_if_string_view<T, basic_string&>
	operator+=(T const& svt)
	{
		return this->append(svt);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	append(basic_string const& str)
	{
		return Append(str.GetData(), str.size());
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	append(basic_string const& str, size_type pos, size_type count = npos)
	{
		return Append(
			str.GetData() + detail::sv_check_pos(str.size(), pos, "basic_string::append"),
			detail::sv_limit(str.size(), pos, count));
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	append(CharT const* s, size_type count)
	{
		//__glibcxx_requires_string_len(s, count);
		CheckLength(size_type(0), count, "basic_string::append");
		return Append(s, count);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	append(CharT const* s)
	{
		//__glibcxx_requires_string(s);
		size_type const count = traits_type::length(s);
		CheckLength(size_type(0), count, "basic_string::append");
		return Append(s, count);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	append(size_type count, CharT c)
	{
		return Replace(this->size(), size_type(0), count, c);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	append(std::initializer_list<CharT> ilist)
	{
		return this->append(ilist.begin(), ilist.size());
	}

	template <BKSGE_REQUIRES_PARAM(bksge::detail::cpp17_input_iterator, InputIterator)>
	BKSGE_CXX14_CONSTEXPR basic_string&
	append(InputIterator first, InputIterator last)
	{
		return this->replace(end(), end(), first, last);
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, basic_string&>
	append(T const& svt)
	{
		string_view_type sv = svt;
		return this->append(sv.data(), sv.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, basic_string&>
	append(T const& svt, size_type pos, size_type count = npos)
	{
		string_view_type sv = svt;
		return Append(
			sv.data() + detail::sv_check_pos(sv.size(), pos, "basic_string::append"),
			detail::sv_limit(sv.size(), pos, count));
	}

	BKSGE_CXX14_CONSTEXPR void push_back(CharT c)
	{
		size_type const size = this->size();
		if (size + 1 > this->capacity())
		{
			this->Mutate(size, size_type(0), 0, size_type(1));
		}
		traits_type::assign(this->GetData()[size], c);
		this->SetLengthAndNullTerminate(size + 1);
	}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4127);	// conditional expression is constant

	BKSGE_CXX14_CONSTEXPR basic_string&
	assign(basic_string const& str)
	{
		if (AllocTraits::propagate_on_container_copy_assignment::value)
		{
			if (!AllocTraits::is_always_equal::value &&
				!IsLocal() &&
				GetAllocator() != str.GetAllocator())
			{
				// Propagating allocator cannot free existing storage so must
				// deallocate it before replacing current allocator.
				if (str.size() <= s_local_capacity)
				{
					Destroy(m_allocated_capacity);
					SetData(GetLocalData());
					SetLengthAndNullTerminate(0);
				}
				else
				{
					auto const len = str.size();
					auto alloc = str.GetAllocator();
					// If this allocation throws there are no effects:
					auto ptr = AllocTraits::allocate(alloc, len + 1);
					Destroy(m_allocated_capacity);
					SetData(ptr);
					SetCapacity(len);
					SetLengthAndNullTerminate(len);
				}
			}
			detail::alloc_on_copy(GetAllocator(), str.GetAllocator());
		}

		this->Assign(str);
		return *this;
	}

BKSGE_WARNING_POP();

	BKSGE_CXX14_CONSTEXPR basic_string&
	assign(basic_string&& str)
		BKSGE_NOEXCEPT((
			AllocTraits::propagate_on_container_move_assignment::value ||
			AllocTraits::is_always_equal::value))
	{
		return *this = bksge::move(str);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	assign(basic_string const& str, size_type pos, size_type count = npos)
	{
		return Replace(size_type(0), this->size(),
			str.GetData() + detail::sv_check_pos(str.size(), pos, "basic_string::assign"),
			detail::sv_limit(str.size(), pos, count));
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	assign(CharT const* s, size_type count)
	{
		//__glibcxx_requires_string_len(s, count);
		return Replace(size_type(0), this->size(), s, count);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	assign(CharT const* s)
	{
		//__glibcxx_requires_string(s);
		return Replace(size_type(0), this->size(), s, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	assign(size_type count, CharT c)
	{
		return Replace(size_type(0), this->size(), count, c);
	}

	template <BKSGE_REQUIRES_PARAM(bksge::detail::cpp17_input_iterator, InputIterator)>
	BKSGE_CXX14_CONSTEXPR basic_string&
	assign(InputIterator first, InputIterator last)
	{
		return this->replace(begin(), end(), first, last);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	assign(std::initializer_list<CharT> ilist)
	{
		return this->assign(ilist.begin(), ilist.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, basic_string&>
	assign(T const& svt)
	{
		string_view_type sv = svt;
		return this->assign(sv.data(), sv.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, basic_string&>
	assign(T const& svt, size_type pos, size_type count = npos)
	{
		string_view_type sv = svt;
		return Replace(size_type(0), this->size(),
			sv.data() + detail::sv_check_pos(sv.size(), pos, "basic_string::assign"),
			detail::sv_limit(sv.size(), pos, count));
	}

	BKSGE_CXX14_CONSTEXPR iterator
	insert(const_iterator pos, size_type count, CharT c)
	{
		//_GLIBCXX_DEBUG_PEDASSERT(pos >= begin() && pos <= end());
		size_type const p = pos - begin();
		this->replace(pos, pos, count, c);
		return iterator(this->GetData() + p);
	}

	template <BKSGE_REQUIRES_PARAM(bksge::detail::cpp17_input_iterator, InputIterator)>
	BKSGE_CXX14_CONSTEXPR iterator
	insert(const_iterator pos, InputIterator first, InputIterator last)
	{
		//_GLIBCXX_DEBUG_PEDASSERT(pos >= begin() && pos <= end());
		size_type const p = pos - begin();
		this->replace(pos, pos, first, last);
		return iterator(this->GetData() + p);
	}

	BKSGE_CXX14_CONSTEXPR iterator
	insert(const_iterator pos, std::initializer_list<CharT> ilist)
	{
		return this->insert(pos, ilist.begin(), ilist.end());
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	insert(size_type index, basic_string const& str)
	{
		return this->replace(index, size_type(0), str.GetData(), str.size());
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	insert(size_type index, basic_string const& str, size_type index_str, size_type count = npos)
	{
		return this->replace(index, size_type(0),
			str.GetData() + detail::sv_check_pos(str.size(), index_str, "basic_string::insert"),
			detail::sv_limit(str.size(), index_str, count));
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	insert(size_type index, CharT const* s, size_type count)
	{
		return this->replace(index, size_type(0), s, count);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	insert(size_type index, CharT const* s)
	{
		//__glibcxx_requires_string(s);
		return this->replace(index, size_type(0), s, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	insert(size_type index, size_type count, CharT c)
	{
		return Replace(
			detail::sv_check_pos(this->size(), index, "basic_string::insert"),
			size_type(0), count, c);
	}

	BKSGE_CXX14_CONSTEXPR iterator
	insert(const_iterator pos, CharT c)
	{
		//_GLIBCXX_DEBUG_PEDASSERT(pos >= begin() && pos <= end());
		size_type const p = pos - begin();
		Replace(p, size_type(0), size_type(1), c);
		return iterator(GetData() + p);
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, basic_string&>
	insert(size_type index, T const& svt)
	{
		string_view_type sv = svt;
		return this->insert(index, sv.data(), sv.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, basic_string&>
	insert(size_type index, T const& svt, size_type index_str, size_type count = npos)
	{
		string_view_type sv = svt;
		return this->replace(index, size_type(0),
			sv.data() + detail::sv_check_pos(sv.size(), index_str, "basic_string::insert"),
			detail::sv_limit(sv.size(), index_str, count));
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	erase(size_type index = 0, size_type count = npos)
	{
		detail::sv_check_pos(this->size(), index, "basic_string::erase");
		if (count == npos)
		{
			this->SetLengthAndNullTerminate(index);
		}
		else if (count != 0)
		{
			this->Erase(index, detail::sv_limit(this->size(), index, count));
		}
		return *this;
	}

	BKSGE_CXX14_CONSTEXPR iterator
	erase(const_iterator position)
	{
		//_GLIBCXX_DEBUG_PEDASSERT(position >= begin() && position < end());
		size_type const pos = position - begin();
		this->Erase(pos, size_type(1));
		return iterator(GetData() + pos);
	}

	BKSGE_CXX14_CONSTEXPR iterator
	erase(const_iterator first, const_iterator last)
	{
		//_GLIBCXX_DEBUG_PEDASSERT(first >= begin() && first <= last && last <= end());
		size_type const pos = first - begin();
		if (last == end())
		{
			this->SetLengthAndNullTerminate(pos);
		}
		else
		{
			this->Erase(pos, last - first);
		}
		return iterator(this->GetData() + pos);
	}

	BKSGE_CXX14_CONSTEXPR void pop_back() BKSGE_NOEXCEPT
	{
		BKSGE_ASSERT(!empty());
		Erase(size() - 1, 1);
	}

	// (1)
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(size_type pos, size_type count, basic_string const& str)
	{
		return this->replace(pos, count, str.GetData(), str.size());
	}

	// (1)
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(const_iterator first, const_iterator last, basic_string const& str)
	{
		return this->replace(first, last, str.GetData(), str.size());
	}

	// (2)
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(size_type pos1, size_type count1, basic_string const& str,
			size_type pos2, size_type count2 = npos)
	{
		return this->replace(pos1, count1,
			str.GetData() + detail::sv_check_pos(str.size(), pos2, "basic_string::replace"),
			detail::sv_limit(str.size(), pos2, count2));
	}

	// (3)
	template <BKSGE_REQUIRES_PARAM(bksge::detail::cpp17_input_iterator, InputIterator)>
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(const_iterator first1, const_iterator last1,
			InputIterator  first2, InputIterator  last2)
	{
		//_GLIBCXX_DEBUG_PEDASSERT(begin() <= first1 && first1 <= last1 && last1 <= end());
		//__glibcxx_requires_valid_range(first2, last2);

		basic_string const s(first2, last2, this->get_allocator());
		return Replace(first1 - begin(), last1 - first1, s.data(), s.size());
	}

	// Specializations for the common case of pointer and iterator:
	// useful to avoid the overhead of temporary buffering in replace.
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(const_iterator first1, const_iterator last1, CharT* first2, CharT* last2)
	{
		//_GLIBCXX_DEBUG_PEDASSERT(begin() <= first1 && first1 <= last1 && last1 <= end());
		//__glibcxx_requires_valid_range(first2, last2);
		return this->replace(first1 - begin(), last1 - first1, first2, last2 - first2);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(const_iterator first1, const_iterator last1, CharT const* first2, CharT const* last2)
	{
		//_GLIBCXX_DEBUG_PEDASSERT(begin() <= first1 && first1 <= last1 && last1 <= end());
		//__glibcxx_requires_valid_range(first2, last2);
		return this->replace(first1 - begin(), last1 - first1, first2, last2 - first2);
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(const_iterator first1, const_iterator last1, iterator first2, iterator last2)
	{
		return this->replace(first1 , last1, first2.base(), last2.base());
	}

	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(const_iterator first1, const_iterator last1, const_iterator first2, const_iterator last2)
	{
		return this->replace(first1 , last1, first2.base(), last2.base());
	}

	// (4)
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(size_type pos, size_type count1, CharT const* s, size_type count2)
	{
		//__glibcxx_requires_string_len(s, count2);
		return Replace(
			detail::sv_check_pos(this->size(), pos, "basic_string::replace"),
			detail::sv_limit(this->size(), pos, count1),
			s, count2);
	}

	// (4)
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(const_iterator first, const_iterator last, CharT const* s, size_type count2)
	{
		//_GLIBCXX_DEBUG_PEDASSERT(begin() <= first && first <= last && last <= end());
		return this->replace(first - begin(), last - first, s, count2);
	}

	// (5)
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(size_type pos, size_type count, CharT const* s)
	{
		//__glibcxx_requires_string(s);
		return this->replace(pos, count, s, traits_type::length(s));
	}

	// (5)
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(const_iterator first, const_iterator last, CharT const* s)
	{
		//__glibcxx_requires_string(s);
		return this->replace(first, last, s, traits_type::length(s));
	}

	// (6)
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(size_type pos, size_type count1, size_type count2, CharT c)
	{
		return Replace(
			detail::sv_check_pos(this->size(), pos, "basic_string::replace"),
			detail::sv_limit(this->size(), pos, count1),
			count2, c);
	}

	// (6)
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(const_iterator first, const_iterator last, size_type count, CharT c)
	{
		//_GLIBCXX_DEBUG_PEDASSERT(begin() <= first && first <= last && last <= end());
		return Replace(first - begin(), last - first, count, c);
	}

	// (7)
	BKSGE_CXX14_CONSTEXPR basic_string&
	replace(const_iterator first, const_iterator last, std::initializer_list<CharT> ilist)
	{
		return this->replace(first, last, ilist.begin(), ilist.size());
	}

	// (8)
	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, basic_string&>
	replace(size_type pos, size_type count, T const& svt)
	{
		string_view_type sv = svt;
		return this->replace(pos, count, sv.data(), sv.size());
	}

	// (8)
	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, basic_string&>
	replace(const_iterator first, const_iterator last, T const& svt)
	{
		string_view_type sv = svt;
		return this->replace(first - begin(), last - first, sv);
	}

	// (9)
	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, basic_string&>
	replace(size_type pos1, size_type count1, T const& svt,
			size_type pos2, size_type count2 = npos)
	{
		string_view_type sv = svt;
		return this->replace(pos1, count1,
			sv.data() + detail::sv_check_pos(sv.size(), pos2, "basic_string::replace"),
			detail::sv_limit(sv.size(), pos2, count2));
	}

	BKSGE_CXX14_CONSTEXPR size_type
	copy(CharT* s, size_type count, size_type pos = 0) const
	{
		detail::sv_check_pos(this->size(), pos, "basic_string::copy");
		count = detail::sv_limit(this->size(), pos, count);
		//__glibcxx_requires_string_len(s, count);

		if (count)
		{
			CopyImpl(s, GetData() + pos, count);
		}

		return count;
	}

	BKSGE_CXX14_CONSTEXPR void
	swap(basic_string& s) BKSGE_NOEXCEPT
	{
		if (this == &s)
		{
			return;
		}

		detail::alloc_on_swap(GetAllocator(), s.GetAllocator());

		if (IsLocal())
		{
			if (s.IsLocal())
			{
				if (length() && s.length())
				{
					CharT tmp_data[s_local_capacity + 1];
					traits_type::copy(tmp_data, s.m_local_buf, s_local_capacity + 1);
					traits_type::copy(s.m_local_buf, m_local_buf, s_local_capacity + 1);
					traits_type::copy(m_local_buf, tmp_data, s_local_capacity + 1);
				}
				else if (s.length())
				{
					traits_type::copy(m_local_buf, s.m_local_buf, s_local_capacity + 1);
					SetLength(s.length());
					s.SetLengthAndNullTerminate(0);
					return;
				}
				else if (length())
				{
					traits_type::copy(s.m_local_buf, m_local_buf, s_local_capacity + 1);
					s.SetLength(length());
					SetLengthAndNullTerminate(0);
					return;
				}
			}
			else
			{
				size_type const tmp_capacity = s.m_allocated_capacity;
				traits_type::copy(s.m_local_buf, m_local_buf, s_local_capacity + 1);
				SetData(s.GetData());
				s.SetData(s.m_local_buf);
				SetCapacity(tmp_capacity);
			}
		}
		else
		{
			size_type const tmp_capacity = m_allocated_capacity;
			if (s.IsLocal())
			{
				traits_type::copy(m_local_buf, s.m_local_buf, s_local_capacity + 1);
				s.SetData(GetData());
				SetData(m_local_buf);
			}
			else
			{
				pointer tmp_ptr = GetData();
				SetData(s.GetData());
				s.SetData(tmp_ptr);
				SetCapacity(s.m_allocated_capacity);
			}
			s.SetCapacity(tmp_capacity);
		}

		size_type const tmp_length = length();
		SetLength(s.length());
		s.SetLength(tmp_length);
	}

	BKSGE_CONSTEXPR CharT const* c_str() const BKSGE_NOEXCEPT
	{
		return GetData();
	}

	BKSGE_CONSTEXPR CharT const* data() const BKSGE_NOEXCEPT
	{
		return GetData();
	}

	BKSGE_CXX14_CONSTEXPR CharT* data() BKSGE_NOEXCEPT
	{
		return GetData();
	}

	BKSGE_CONSTEXPR allocator_type get_allocator() const BKSGE_NOEXCEPT
	{
		return GetAllocator();
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find(CharT const* s, size_type pos, size_type count) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, count);
		size_type const size = this->size();

		if (count == 0)
		{
			return pos <= size ? pos : npos;
		}

		if (pos >= size)
		{
			return npos;
		}

		CharT const        elem0 = s[0];
		CharT const* const data  = this->data();
		CharT const*       first = data + pos;
		CharT const* const last  = data + size;
		size_type len = size - pos;

		while (len >= count)
		{
			// Find the first occurrence of elem0:
			first = traits_type::find(first, len - count + 1, elem0);
			if (!first)
			{
				return npos;
			}

			// Compare the full strings from the first occurrence of elem0.
			// We already know that first[0] == s[0] but compare them again
			// anyway because s is probably aligned, which helps memcmp.
			if (traits_type::compare(first, s, count) == 0)
			{
				return first - data;
			}

			len = last - ++first;
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find(basic_string const& str, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find(str.data(), pos, str.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, size_type>
	find(T const& svt, size_type pos = 0) const
		BKSGE_NOEXCEPT((bksge::is_same<T, string_view_type>::value))
	{
		string_view_type sv = svt;
		return this->find(sv.data(), pos, sv.size());
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find(CharT const* s, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string(s);
		return this->find(s, pos, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find(CharT c, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		size_type ret = npos;
		size_type const size = this->size();
		if (pos < size)
		{
			CharT const* data = GetData();
			size_type const n = size - pos;
			CharT const* p = traits_type::find(data + pos, n, c);
			if (p)
			{
				ret = p - data;
			}
		}

		return ret;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	rfind(basic_string const& str, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->rfind(str.data(), pos, str.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, size_type>
	rfind(T const& svt, size_type pos = npos) const
		BKSGE_NOEXCEPT((bksge::is_same<T, string_view_type>::value))
	{
		string_view_type sv = svt;
		return this->rfind(sv.data(), pos, sv.size());
	}

	BKSGE_CXX14_CONSTEXPR size_type
	rfind(CharT const* s, size_type pos, size_type count) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, count);
		size_type const size = this->size();
		if (count <= size)
		{
			pos = bksge::min(size_type(size - count), pos);
			CharT const* data = GetData();
			do
			{
				if (traits_type::compare(data + pos, s, count) == 0)
				{
					return pos;
				}
			}
			while (pos-- > 0);
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	rfind(CharT const* s, size_type pos = npos) const
	{
		//__glibcxx_requires_string(s);
		return this->rfind(s, pos, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR size_type
	rfind(CharT c, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		size_type size = this->size();
		if (size)
		{
			if (--size > pos)
			{
				size = pos;
			}

			for (++size; size-- > 0; )
			{
				if (traits_type::eq(GetData()[size], c))
				{
					return size;
				}
			}
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_of(basic_string const& str, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find_first_of(str.data(), pos, str.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, size_type>
	find_first_of(T const& svt, size_type pos = 0) const
		BKSGE_NOEXCEPT((bksge::is_same<T, string_view_type>::value))
	{
		string_view_type sv = svt;
		return this->find_first_of(sv.data(), pos, sv.size());
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_of(CharT const* s, size_type pos, size_type count) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, count);
		for (; count && pos < this->size(); ++pos)
		{
			CharT const* p = traits_type::find(s, count, GetData()[pos]);
			if (p)
			{
				return pos;
			}
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_of(CharT const* s, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string(s);
		return this->find_first_of(s, pos, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_of(CharT c, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find(c, pos);
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_of(basic_string const& str, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->find_last_of(str.data(), pos, str.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, size_type>
	find_last_of(T const& svt, size_type pos = npos) const
		BKSGE_NOEXCEPT((bksge::is_same<T, string_view_type>::value))
	{
		string_view_type sv = svt;
		return this->find_last_of(sv.data(), pos, sv.size());
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_of(CharT const* s, size_type pos, size_type count) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, count);
		size_type size = this->size();
		if (size && count)
		{
			if (--size > pos)
			{
				size = pos;
			}

			do
			{
				if (traits_type::find(s, count, GetData()[size]))
				{
					return size;
				}
			}
			while (size-- != 0);
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_of(CharT const* s, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string(s);
		return this->find_last_of(s, pos, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_of(CharT c, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->rfind(c, pos);
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_not_of(basic_string const& str, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		return this->find_first_not_of(str.data(), pos, str.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, size_type>
	find_first_not_of(T const& svt, size_type pos = 0) const
		BKSGE_NOEXCEPT((bksge::is_same<T, string_view_type>::value))
	{
		string_view_type sv = svt;
		return this->find_first_not_of(sv.data(), pos, sv.size());
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_not_of(CharT const* s, size_type pos, size_type count) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, count);
		for (; pos < this->size(); ++pos)
		{
			if (!traits_type::find(s, count, GetData()[pos]))
			{
				return pos;
			}
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_not_of(CharT const* s, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string(s);
		return this->find_first_not_of(s, pos, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_first_not_of(CharT c, size_type pos = 0) const BKSGE_NOEXCEPT
	{
		for (; pos < this->size(); ++pos)
		{
			if (!traits_type::eq(GetData()[pos], c))
			{
				return pos;
			}
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_not_of(basic_string const& str, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		return this->find_last_not_of(str.data(), pos, str.size());
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, size_type>
	find_last_not_of(T const& svt, size_type pos = npos) const
		BKSGE_NOEXCEPT((bksge::is_same<T, string_view_type>::value))
	{
		string_view_type sv = svt;
		return this->find_last_not_of(sv.data(), pos, sv.size());
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_not_of(CharT const* s, size_type pos, size_type count) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string_len(s, count);
		size_type size = this->size();
		if (size)
		{
			if (--size > pos)
			{
				size = pos;
			}

			do
			{
				if (!traits_type::find(s, count, GetData()[size]))
				{
					return size;
				}
			}
			while (size--);
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_not_of(CharT const* s, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string(s);
		return this->find_last_not_of(s, pos, traits_type::length(s));
	}

	BKSGE_CXX14_CONSTEXPR size_type
	find_last_not_of(CharT c, size_type pos = npos) const BKSGE_NOEXCEPT
	{
		size_type size = this->size();
		if (size)
		{
			if (--size > pos)
			{
				size = pos;
			}

			do
			{
				if (!traits_type::eq(GetData()[size], c))
				{
					return size;
				}
			}
			while (size--);
		}

		return npos;
	}

	BKSGE_CXX14_CONSTEXPR basic_string
	substr(size_type pos = 0, size_type count = npos) const
	{
		return basic_string(
			*this,
			detail::sv_check_pos(this->size(), pos, "basic_string::substr"),
			count);
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(basic_string const& str) const
	{
		size_type const size = this->size();
		size_type const osize = str.size();
		size_type const len = bksge::min(size, osize);

		int r = traits_type::compare(GetData(), str.data(), len);
		if (!r)
		{
			r = CompareImpl(size, osize);
		}
		return r;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, int>
	compare(T const& svt) const
		BKSGE_NOEXCEPT((bksge::is_same<T, string_view_type>::value))
	{
		string_view_type sv = svt;
		size_type const size = this->size();
		size_type const osize = sv.size();
		size_type const len = bksge::min(size, osize);

		int r = traits_type::compare(GetData(), sv.data(), len);
		if (!r)
		{
			r = CompareImpl(size, osize);
		}
		return r;
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, int>
	compare(size_type pos, size_type count, T const& svt) const
		BKSGE_NOEXCEPT((bksge::is_same<T, string_view_type>::value))
	{
		string_view_type sv = svt;
		return string_view_type(*this).substr(pos, count).compare(sv);
	}

	template <typename T>
	BKSGE_CXX14_CONSTEXPR enable_if_string_view<T, int>
	compare(size_type pos1, size_type count1, T const& svt,
			size_type pos2, size_type count2 = npos) const
		BKSGE_NOEXCEPT((bksge::is_same<T, string_view_type>::value))
	{
		string_view_type sv = svt;
		return string_view_type(*this).substr(pos1, count1).compare(sv.substr(pos2, count2));
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos, size_type count, basic_string const& str) const
	{
		detail::sv_check_pos(this->size(), pos, "basic_string::compare");
		count = detail::sv_limit(this->size(), pos, count);
		size_type const osize = str.size();
		size_type const len = bksge::min(count, osize);
		int r = traits_type::compare(GetData() + pos, str.data(), len);
		if (!r)
		{
			r = CompareImpl(count, osize);
		}
		return r;
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(
		size_type pos1, size_type count1, basic_string const& str,
		size_type pos2, size_type count2 = npos) const
	{
		detail::sv_check_pos(this->size(), pos1, "basic_string::compare");
		detail::sv_check_pos(str.size(),   pos2, "basic_string::compare");
		count1 = detail::sv_limit(this->size(), pos1, count1);
		count2 = detail::sv_limit(str.size(),   pos2, count2);
		size_type const len = bksge::min(count1, count2);
		int r = traits_type::compare(GetData() + pos1, str.data() + pos2, len);
		if (!r)
		{
			r = CompareImpl(count1, count2);
		}
		return r;
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(CharT const* s) const BKSGE_NOEXCEPT
	{
		//__glibcxx_requires_string(s);
		size_type const size = this->size();
		size_type const osize = traits_type::length(s);
		size_type const len = bksge::min(size, osize);
		int r = traits_type::compare(GetData(), s, len);
		if (!r)
		{
			r = CompareImpl(size, osize);
		}
		return r;
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos, size_type count, CharT const* s) const
	{
		//__glibcxx_requires_string(s);
		detail::sv_check_pos(this->size(), pos, "basic_string::compare");
		count = detail::sv_limit(this->size(), pos, count);
		size_type const osize = traits_type::length(s);
		size_type const len = bksge::min(count, osize);
		int r = traits_type::compare(GetData() + pos, s, len);
		if (!r)
		{
			r = CompareImpl(count, osize);
		}
		return r;
	}

	BKSGE_CXX14_CONSTEXPR int
	compare(size_type pos, size_type count1, CharT const* s, size_type count2) const
	{
		//__glibcxx_requires_string_len(s, count2);
		detail::sv_check_pos(this->size(), pos, "basic_string::compare");
		count1 = detail::sv_limit(this->size(), pos, count1);
		size_type const len = bksge::min(count1, count2);
		int r = traits_type::compare(GetData() + pos, s, len);
		if (!r)
		{
			r = CompareImpl(count1, count2);
		}
		return r;
	}

	BKSGE_CXX14_CONSTEXPR bool
	starts_with(bksge::basic_string_view<CharT, Traits> sv) const BKSGE_NOEXCEPT
	{
		return string_view_type(this->data(), this->size()).starts_with(sv);
	}

	BKSGE_CXX14_CONSTEXPR bool
	starts_with(CharT c) const BKSGE_NOEXCEPT
	{
		return string_view_type(this->data(), this->size()).starts_with(c);
	}

	BKSGE_CXX14_CONSTEXPR bool
	starts_with(CharT const* s) const BKSGE_NOEXCEPT
	{
		return string_view_type(this->data(), this->size()).starts_with(s);
	}

	BKSGE_CXX14_CONSTEXPR bool
	ends_with(bksge::basic_string_view<CharT, Traits> sv) const BKSGE_NOEXCEPT
	{
		return string_view_type(this->data(), this->size()).ends_with(sv);
	}

	BKSGE_CXX14_CONSTEXPR bool
	ends_with(CharT c) const BKSGE_NOEXCEPT
	{
		return string_view_type(this->data(), this->size()).ends_with(c);
	}

	BKSGE_CXX14_CONSTEXPR bool
	ends_with(CharT const* s) const BKSGE_NOEXCEPT
	{
		return string_view_type(this->data(), this->size()).ends_with(s);
	}

	BKSGE_CXX14_CONSTEXPR bool
	contains(bksge::basic_string_view<CharT, Traits> sv) const BKSGE_NOEXCEPT
	{
		return find(sv) != npos;
	}

	BKSGE_CXX14_CONSTEXPR bool
	contains(CharT c) const BKSGE_NOEXCEPT
	{
		return find(c) != npos;
	}

	BKSGE_CXX14_CONSTEXPR bool
	contains(CharT const* s) const
	{
		return find(s) != npos;
	}
};

#if defined(BKSGE_HAS_CXX17_DEDUCTION_GUIDES)

template <
	BKSGE_REQUIRES_PARAM(bksge::detail::cpp17_input_iterator, InputIterator),
	typename CharT = typename bksge::iterator_traits<InputIterator>::value_type,
	BKSGE_REQUIRES_PARAM_D(detail::allocator_like, Allocator, bksge::allocator<CharT>)
>
basic_string(InputIterator, InputIterator, Allocator = Allocator())
-> basic_string<CharT, char_traits<CharT>, Allocator>;

template <typename CharT, typename Traits,
	BKSGE_REQUIRES_PARAM_D(detail::allocator_like, Allocator, bksge::allocator<CharT>)
>
basic_string(bksge::basic_string_view<CharT, Traits>, Allocator const& = Allocator())
-> basic_string<CharT, Traits, Allocator>;

template <typename CharT, typename Traits,
	BKSGE_REQUIRES_PARAM_D(detail::allocator_like, Allocator, bksge::allocator<CharT>)
>
basic_string(bksge::basic_string_view<CharT, Traits>,
	typename basic_string<CharT, Traits, Allocator>::size_type,
	typename basic_string<CharT, Traits, Allocator>::size_type,
	Allocator const& = Allocator())
-> basic_string<CharT, Traits, Allocator>;

#endif

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	basic_string<CharT, Traits, Allocator> str(lhs);
	str.append(rhs);
	return str;
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	//__glibcxx_requires_string(lhs);
	using string_type   = basic_string<CharT, Traits, Allocator>;
	using size_type     = typename string_type::size_type;
	using CharAllocType = typename bksge::allocator_traits<Allocator>::template rebind_alloc<CharT>;
	using AllocTraits   = bksge::allocator_traits<CharAllocType>;
	size_type const len = Traits::length(lhs);
	string_type str(AllocTraits::select_on_container_copy_construction(rhs.get_allocator()));
	str.reserve(len + rhs.size());
	str.append(lhs, len);
	str.append(rhs);
	return str;
}

template <typename CharT, typename Traits, typename Allocator>
basic_string<CharT, Traits, Allocator> operator+(
	CharT lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	using string_type   = basic_string<CharT, Traits, Allocator>;
	using size_type     = typename string_type::size_type;
	using CharAllocType = typename bksge::allocator_traits<Allocator>::template rebind_alloc<CharT>;
	using AllocTraits   = bksge::allocator_traits<CharAllocType>;
	string_type str(AllocTraits::select_on_container_copy_construction(rhs.get_allocator()));
	str.reserve(1 + rhs.size());
	str.append(size_type(1), lhs);
	str.append(rhs);
	return str;
}

template <typename CharT, typename Traits, typename Allocator>
inline basic_string<CharT, Traits, Allocator> operator+(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	basic_string<CharT, Traits, Allocator> str(lhs);
	str.append(rhs);
	return str;
}

template <typename CharT, typename Traits, typename Allocator>
inline basic_string<CharT, Traits, Allocator> operator+(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT rhs)
{
	using string_type = basic_string<CharT, Traits, Allocator>;
	using size_type   = typename string_type::size_type;
	string_type str(lhs);
	str.append(size_type(1), rhs);
	return str;
}

template <typename CharT, typename Traits, typename Allocator>
inline basic_string<CharT, Traits, Allocator> operator+(
	basic_string<CharT, Traits, Allocator>&& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return bksge::move(lhs.append(rhs));
}

template <typename CharT, typename Traits, typename Allocator>
inline basic_string<CharT, Traits, Allocator> operator+(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator>&& rhs)
{
	return bksge::move(rhs.insert(0, lhs));
}

template <typename CharT, typename Traits, typename Allocator>
inline basic_string<CharT, Traits, Allocator> operator+(
	basic_string<CharT, Traits, Allocator>&& lhs,
	basic_string<CharT, Traits, Allocator>&& rhs)
{
	using AllocTraits = bksge::allocator_traits<Allocator>;
	bool const use_rhs =
		AllocTraits::is_always_equal::value ||
		(lhs.get_allocator() == rhs.get_allocator());

	if (use_rhs)
	{
		auto const size = lhs.size() + rhs.size();
		if (lhs.capacity() < size && size <= rhs.capacity())
		{
			return bksge::move(rhs.insert(0, lhs));
		}
	}

	return bksge::move(lhs.append(rhs));
}

template <typename CharT, typename Traits, typename Allocator>
inline basic_string<CharT, Traits, Allocator> operator+(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator>&& rhs)
{
	return bksge::move(rhs.insert(0, lhs));
}

template <typename CharT, typename Traits, typename Allocator>
inline basic_string<CharT, Traits, Allocator> operator+(
	CharT lhs,
	basic_string<CharT, Traits, Allocator>&& rhs)
{
	return bksge::move(rhs.insert(0, 1, lhs));
}

template <typename CharT, typename Traits, typename Allocator>
inline basic_string<CharT, Traits, Allocator> operator+(
	basic_string<CharT, Traits, Allocator>&& lhs,
	CharT const* rhs)
{
	return bksge::move(lhs.append(rhs));
}

template <typename CharT, typename Traits, typename Allocator>
inline basic_string<CharT, Traits, Allocator> operator+(
	basic_string<CharT, Traits, Allocator>&& lhs,
	CharT rhs)
{
	return bksge::move(lhs.append(1, rhs));
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator==(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) == 0;
}

template <typename CharT>
inline bksge::enable_if_t<detail::is_char<CharT>::value, bool>
operator==(
	basic_string<CharT> const& lhs,
	basic_string<CharT> const& rhs) BKSGE_NOEXCEPT
{
	return (lhs.size() == rhs.size() &&
		!bksge::char_traits<CharT>::compare(lhs.data(), rhs.data(), lhs.size()));
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator==(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return lhs.compare(rhs) == 0;
}

#if defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename CharT, typename Traits, typename Allocator>
inline auto operator<=>(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) BKSGE_NOEXCEPT
-> detail::char_traits_cmp_cat_t<Traits>
{
	using cat = detail::char_traits_cmp_cat_t<Traits>;
	return static_cast<cat>(lhs.compare(rhs) <=> 0);
}

template <typename CharT, typename Traits, typename Allocator>
inline auto operator<=>(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs) BKSGE_NOEXCEPT
-> detail::char_traits_cmp_cat_t<Traits>
{
	using cat = detail::char_traits_cmp_cat_t<Traits>;
	return static_cast<cat>(lhs.compare(rhs) <=> 0);
}

#else

template <typename CharT, typename Traits, typename Allocator>
inline bool operator==(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return rhs.compare(lhs) == 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator!=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) BKSGE_NOEXCEPT
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator!=(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator!=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return !(lhs == rhs);
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator<(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator<(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return lhs.compare(rhs) < 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator<(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return rhs.compare(lhs) > 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator>(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator>(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return lhs.compare(rhs) > 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator>(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return rhs.compare(lhs) < 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator<=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator<=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return lhs.compare(rhs) <= 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator<=(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return rhs.compare(lhs) >= 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator>=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	basic_string<CharT, Traits, Allocator> const& rhs) BKSGE_NOEXCEPT
{
	return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator>=(
	basic_string<CharT, Traits, Allocator> const& lhs,
	CharT const* rhs)
{
	return lhs.compare(rhs) >= 0;
}

template <typename CharT, typename Traits, typename Allocator>
inline bool operator>=(
	CharT const* lhs,
	basic_string<CharT, Traits, Allocator> const& rhs)
{
	return rhs.compare(lhs) <= 0;
}

#endif	// defined(BKSGE_HAS_CXX20_THREE_WAY_COMPARISON)

template <typename CharT, typename Traits, typename Allocator>
inline BKSGE_CXX14_CONSTEXPR void
swap(
	basic_string<CharT, Traits, Allocator>& lhs,
	basic_string<CharT, Traits, Allocator>& rhs)
	BKSGE_NOEXCEPT_IF_EXPR((lhs.swap(rhs)))
{
	lhs.swap(rhs);
}

template <typename CharT, typename Traits1, typename Traits2, typename Allocator>
inline std::basic_istream<CharT, Traits1>&
operator>>(
	std::basic_istream<CharT, Traits1>& is,
	basic_string<CharT, Traits2, Allocator>& str)
{
	using istream_type = std::basic_istream<CharT, Traits1>;
	using string_type  = bksge::basic_string<CharT, Traits2, Allocator>;
	using ios_base     = typename istream_type::ios_base;
	using int_type     = typename istream_type::int_type;
	using size_type    = typename string_type::size_type;
	using ctype_type   = std::ctype<CharT>;
	using ctype_base   = typename ctype_type::ctype_base;

	size_type extracted = 0;
	typename ios_base::iostate err = ios_base::goodbit;
	typename istream_type::sentry cerb(is, false);

	if (cerb)
	{
		try
		{
			// Avoid reallocation for common case.
			str.erase();
			CharT buf[128];
			size_type len = 0;
			std::streamsize const w = is.width();
			size_type const n = w > 0 ? static_cast<size_type>(w) : str.max_size();
			ctype_type const& ct = std::use_facet<ctype_type>(is.getloc());
			int_type const eof = Traits2::eof();
			int_type c = is.rdbuf()->sgetc();

			while (extracted < n &&
				!Traits2::eq_int_type(c, eof) &&
				!ct.is(ctype_base::space, Traits2::to_char_type(c)))
			{
				if (len == sizeof(buf) / sizeof(CharT))
				{
					str.append(buf, sizeof(buf) / sizeof(CharT));
					len = 0;
				}

				buf[len++] = Traits2::to_char_type(c);
				++extracted;
				c = is.rdbuf()->snextc();
			}

			str.append(buf, len);

			if (extracted < n && Traits2::eq_int_type(c, eof))
			{
				err |= ios_base::eofbit;
			}

			is.width(0);
		}
		// TODO
		/*catch(__cxxabiv1::__forced_unwind&)
		{
			is._M_setstate(ios_base::badbit);
			__throw_exception_again;
		}*/
		catch(...)
		{
			//is._M_setstate(ios_base::badbit);
			is.setstate(ios_base::badbit);
			if (is.exceptions() & ios_base::badbit)
			{
				throw;//__throw_exception_again;
			}
		}
	}

	// 211.  operator>>(istream&, string&) doesn't set failbit
	if (!extracted)
	{
		err |= ios_base::failbit;
	}

	if (err)
	{
		is.setstate(err);
	}

	return is;
}

//template <>
//std::basic_istream<char>&
//operator>>(
//	std::basic_istream<char>& is,
//	basic_string<char>& str);

template <typename CharT, typename Traits1, typename Traits2, typename Allocator>
inline bksge::basic_ostream<CharT, Traits1>&
operator<<(
	bksge::basic_ostream<CharT, Traits1>& os,
	basic_string<CharT, Traits2, Allocator> const& str)
{
	//return __ostream_insert(os, str.data(), str.size());
	return os.write(str.data(), str.size());
}

inline namespace literals
{
inline namespace string_literals
{

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4455);	// literal suffix identifiers that do not start with an underscore are reserved
BKSGE_WARNING_DISABLE_MSVC(4267);	// conversion from 'bksge::size_t' to 'const int', possible loss of data
BKSGE_WARNING_DISABLE_CLANG("-Wuser-defined-literals");
BKSGE_WARNING_DISABLE_GCC("-Wliteral-suffix");

inline basic_string<char>
operator""s(char const* str, bksge::size_t len)
{
	return basic_string<char>{str, len};
}

inline basic_string<wchar_t>
operator""s(const wchar_t* str, bksge::size_t len)
{
	return basic_string<wchar_t>{str, len};
}

#if defined(BKSGE_HAS_CXX20_CHAR8_T)
inline basic_string<char8_t>
operator""s(const char8_t* str, bksge::size_t len)
{
	return basic_string<char8_t>{str, len};
}
#endif
#if defined(BKSGE_HAS_CXX11_CHAR16_T)
inline basic_string<char16_t>
operator""s(const char16_t* str, bksge::size_t len)
{
	return basic_string<char16_t>{str, len};
}
#endif
#if defined(BKSGE_HAS_CXX11_CHAR32_T)
inline basic_string<char32_t>
operator""s(const char32_t* str, bksge::size_t len)
{
	return basic_string<char32_t>{str, len};
}
#endif

BKSGE_WARNING_POP();

}	// inline namespace string_literals
}	// inline namespace literals

}	// namespace bksge

#endif

#include <bksge/fnd/functional/config.hpp>

#if !defined(BKSGE_USE_STD_STRING) || !defined(BKSGE_USE_STD_HASH)

#include <bksge/fnd/functional/hash.hpp>
#include <bksge/fnd/hash_functions/murmur_hash_3.hpp>
#include <bksge/fnd/cstddef/size_t.hpp>
#include <bksge/fnd/config.hpp>

namespace BKSGE_HASH_NAMESPACE
{

template <typename T>
struct hash<bksge::basic_string<T>>
{
	BKSGE_CXX14_CONSTEXPR bksge::size_t
	operator()(bksge::basic_string<T> const& arg) const BKSGE_NOEXCEPT
	{
		return bksge::murmur_hash_3{}(arg.data(), arg.length());
	}
};

}	// namespace BKSGE_HASH_NAMESPACE

#endif

#endif // BKSGE_FND_STRING_BASIC_STRING_HPP
