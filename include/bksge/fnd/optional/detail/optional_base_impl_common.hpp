/**
 *	@file	optional_base_impl_common.hpp
 *
 *	@brief
 *
 *	@author	myoukaku
 */

// NO INCLUDE GUARD

#if defined(BKSGE_HAS_CXX11_UNRESTRICTED_UNIONS)

public:
	BKSGE_CONSTEXPR optional_base_impl() BKSGE_NOEXCEPT
		: m_engaged(false)
		, m_empty{}
	{}

	BKSGE_CONSTEXPR optional_base_impl(T const& t)
		: m_engaged(true)
		, m_storage(t)
	{}

	BKSGE_CONSTEXPR optional_base_impl(T&& t)
		: m_engaged(true)
		, m_storage(bksge::move(t))
	{}

#if defined(_MSC_VER)
	BKSGE_CONSTEXPR explicit
	optional_base_impl(in_place_t)
		: m_engaged(true)
		, m_storage()
	{}
#endif

	template <typename... Args>
	BKSGE_CONSTEXPR explicit
	optional_base_impl(in_place_t, Args&&... args)
		: m_engaged(true)
		, m_storage(bksge::forward<Args>(args)...)
	{}

protected:
	BKSGE_CONSTEXPR T const& get() const BKSGE_NOEXCEPT
	{
		return m_storage;
	}

	BKSGE_CXX14_CONSTEXPR T& get() BKSGE_NOEXCEPT
	{
		return m_storage;
	}

BKSGE_WARNING_PUSH();
BKSGE_WARNING_DISABLE_MSVC(4702);	// 制御が渡らないコードです。

	template <typename... Args>
	BKSGE_CXX14_CONSTEXPR void construct(Args&&... args)
	BKSGE_NOEXCEPT_IF((std::is_nothrow_constructible<T, Args...>::value))
	{
		::new (bksge::addressof(this->get())) T (bksge::forward<Args>(args)...);
		this->m_engaged = true;
	}

BKSGE_WARNING_POP();

	void destroy()
	{
		if (this->m_engaged)
		{
			this->m_engaged = false;
			this->get().~T();
		}
	}

protected:
	bool m_engaged = false;

	using stored_type = bksge::remove_const_t<T>;
	struct empty_byte {};
	union
	{
		empty_byte  m_empty;
		stored_type m_storage;
	};

#else	// defined(BKSGE_HAS_CXX11_UNRESTRICTED_UNIONS)

public:
	BKSGE_CONSTEXPR optional_base_impl() BKSGE_NOEXCEPT
		: m_engaged(false)
	{}

	BKSGE_CXX14_CONSTEXPR optional_base_impl(T const& t)
		: m_engaged(false)
	{
		this->construct(t);
	}

	BKSGE_CXX14_CONSTEXPR optional_base_impl(T&& t)
		: m_engaged(false)
	{
		this->construct(bksge::move(t));
	}

	template <typename... Args>
	explicit BKSGE_CXX14_CONSTEXPR
	optional_base_impl(in_place_t, Args&&... args)
		: m_engaged(false)
	{
		this->construct(bksge::forward<Args>(args)...);
	}

protected:
	BKSGE_CONSTEXPR T const& get() const BKSGE_NOEXCEPT
	{
		return *(static_cast<T const*>(static_cast<void const*>(&m_storage)));
	}

	BKSGE_CXX14_CONSTEXPR T& get() BKSGE_NOEXCEPT
	{
		return *(static_cast<T*>(static_cast<void*>(&m_storage)));
	}

	template <typename... Args>
	void construct(Args&&... args)
	BKSGE_NOEXCEPT_IF((std::is_nothrow_constructible<T, Args...>::value))
	{
		::new (bksge::addressof(this->get())) T (bksge::forward<Args>(args)...);
		this->m_engaged = true;
	}

	void destroy()
	{
		if (this->m_engaged)
		{
			this->m_engaged = false;
			this->get().~T();
		}
	}

protected:
	bool m_engaged = false;

	using storage_type = bksge::aligned_storage_t<sizeof(T), std::alignment_of<T>::value>;
	storage_type	m_storage;

#endif	// defined(BKSGE_HAS_CXX11_UNRESTRICTED_UNIONS)
