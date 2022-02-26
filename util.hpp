/*
 * Copyright 2022 Sean McBane
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#ifndef STOKHOS_UTIL_HPP
#define STOKHOS_UTIL_HPP

#include <cstdio>
#include <exception>
#include <type_traits>

#include <inttypes.h>

#if __SIZEOF_INT128__
typedef __uint128_t uint128_t;
#define STOKHOS_128_BIT
#endif

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
    if (read != 1U)
    {
        throw exception("Number of read bytes from /dev/urandom was less than requested\n");
    }
    fclose(urandom);

    return dst;
}

} // namespace stokhos

#endif // STOKHOS_UTIL_HPP

