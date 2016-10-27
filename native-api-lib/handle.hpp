#pragma once
#include "ntdll.h"
#include <vector>

namespace Nt
{
    //
    //	Handle traits. Used to specialize basic_unique_handle and basic_shared_handle for different types of handles.
    //

    struct nt_handle_traits
    {
        static NtApi nt;
        typedef HANDLE pointer;

        static auto invalid() throw() -> pointer
        {
            return nullptr;
        }

        static auto close(pointer value) throw() -> void
        {
            if (value != nullptr)
            {
                nt.NtClose(value);
            }
        }
    };

    //
    //	basic_unique_handle. Class template for a handle wrapper that allows only a single owner.
    //

    template <typename Traits>
    class basic_unique_handle
    {
        typedef typename Traits::pointer pointer;

    public:
        explicit basic_unique_handle(pointer value = Traits::invalid()) throw() : m_value{ value }
        {
        }

        virtual ~basic_unique_handle() throw()
        {
            close();
        }

        //	Copy (deleted)
        basic_unique_handle(const basic_unique_handle&) = delete;
        basic_unique_handle& operator=(const basic_unique_handle&) = delete;

        //	Move
        basic_unique_handle(basic_unique_handle&& o) throw() : m_value{ o.release() }
        {
        }

        auto operator=(basic_unique_handle&& o) throw() -> basic_unique_handle&
        {
            if (this != &o)
            {
                reset(o.release());
            }
            return *this;
        }

        explicit operator bool() const throw()
        {
            return Traits::invalid() != m_value;
        }

        auto get() const throw() -> pointer
        {
            return m_value;
        }

        auto get_address_of() throw() -> pointer*
        {
            return &m_value;
        }

        auto release() throw() -> pointer
        {
            auto value = m_value;
            m_value = Traits::invalid();
            return value;
        }

        auto reset(pointer value = Traits::invalid()) throw() -> bool
        {
            if (m_value != value)
            {
                close();
                m_value = value;
            }
            return static_cast<bool>(*this);
        }

        auto swap(basic_unique_handle<Traits>& other) throw() -> void
        {
            std::swap(m_value, other.m_value);
        }

    private:
        pointer m_value;

        auto close() throw() -> void
        {
            if (*this)
            {
                Traits::close(m_value);
            }
        }
    };

    template <typename Traits>
    auto swap(basic_unique_handle<Traits>& left, basic_unique_handle<Traits>& right) throw() -> void
    {
        left.swap(right);
    }

    template <typename Traits>
    auto operator==(const basic_unique_handle<Traits>& left, const basic_unique_handle<Traits>& right) throw() -> bool
    {
        return left.get() == right.get();
    }

    template <typename Traits>
    auto operator!=(const basic_unique_handle<Traits>& left, const basic_unique_handle<Traits>& right) throw() -> bool
    {
        return left.get() != right.get();
    }

    template <typename Traits>
    auto operator>(const basic_unique_handle<Traits>& left, const basic_unique_handle<Traits>& right) throw() -> bool
    {
        return left.get() > right.get();
    }

    template <typename Traits>
    auto operator>=(const basic_unique_handle<Traits>& left, const basic_unique_handle<Traits>& right) throw() -> bool
    {
        return left.get() >= right.get();
    }

    template <typename Traits>
    auto operator<(const basic_unique_handle<Traits>& left, const basic_unique_handle<Traits>& right) throw() -> bool
    {
        return left.get() < right.get();
    }

    template <typename Traits>
    auto operator<=(const basic_unique_handle<Traits>& left, const basic_unique_handle<Traits>& right) throw() -> bool
    {
        return left.get() <= right.get();
    }

    template <typename Traits>
    auto waitable_handles(const std::vector<basic_unique_handle<Traits>>& v) throw() -> const std::vector<typename Traits::pointer>
    {
        std::vector<typename Traits::pointer> r;
        for (auto& h : v)
        {
            r.emplace_back(h.get());
        }
        return r;
    }

    //
    //	Typedef specializations.
    //

    typedef basic_unique_handle<nt_handle_traits> unique_nt_handle;
}
