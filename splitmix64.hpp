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
#ifndef STOKHOS_SPLITMIX64_HPP
#define STOKHOS_SPLITMIX64_HPP

#include "abstract_generator.hpp"
#include "util.hpp"

#include <cstdint>

namespace stokhos
{

class SplitMix64 : public AbstractRNG<uint64_t, uint64_t, 1ULL>
{
  public:
    using AbstractRNG::AbstractRNG;

    // Default construction tries to get random bits from /dev/urandom
    SplitMix64() : AbstractRNG(get_bits_from_urandom<uint64_t>()) {}

    uint64_t operator()()
    {
        m_state += 0x9E3779B97f4A7C15;
        uint64_t result = m_state;
        result = (result ^ (result >> 30)) * 0xBF58476D1CE4E5B9;
        result = (result ^ (result >> 27)) * 0x94D049BB133111EB;
        return result ^ (result >> 31);
    }
};

} // namespace stokhos

#endif // STOKHOS_SPLITMIX64_HPP

