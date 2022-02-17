#ifndef STOKHOS_UTIL_HPP
#define STOKHOS_UTIL_HPP

#include <cstdio>
#include <exception>
#include <type_traits>

namespace stokhos
{

struct exception : public std::exception
{
    const char *message;

    exception(const char *what) : message{what} {}

    const char *what() const noexcept { return message; }
};

template <class T>
T get_bits_from_urandom()
{
    static_assert(std::is_trivial<T>::value, "This only works for trivial types");
    std::FILE *urandom = fopen("/dev/urandom", "rb");

    if (!urandom)
    {
        throw exception("Failed to open /dev/urandom!\n");
    }

    T dst;
    size_t read = fread(&dst, sizeof(T), 1, urandom);
    if (read != sizeof(T))
    {
        throw exception("Number of read bytes from /dev/urandom was less than requested\n");
    }
    fclose(urandom);

    return dst;
}

} // namespace stokhos

#endif // STOKHOS_UTIL_HPP

