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

/*
 * This code incorporates algorithms from the C++ implementation of the
 * PCG random number generator. See <http://www.pcg-random.org>. The
 * implementation is Copyright 2014-2021 Melissa O'Neill <oneill@pcg-random.org>
 * and PCG Project contributors
 * under the terms of the Apache License, Version 2.0 OR the MIT license, which allow
 * the distribution of this derivative work. The Apache license is reproduced in the
 * file "apache_2.0.txt" as required in the license conditions. The terms of the MIT
 * license are in the copyright notice above.
 */
#ifndef STOKHOS_PCG_XSL_RR_MCG_HPP
#define STOKHOS_PCG_XSL_RR_MCG_HPP

#include "abstract_generator.hpp"
#include "util.hpp"

#ifdef STOKHOS_128_BIT

namespace stokhos
{

inline uint64_t rotr_64(uint64_t v, unsigned rot) { return (v >> rot) | (v << ((-rot) & 63)); }

inline uint64_t xsl_rr_128_64(uint128_t state)
{
    return rotr_64(((uint64_t)(state >> 64u)) ^ (uint64_t)state, state >> 122u);
}

inline uint128_t mcg_advance(uint128_t state)
{
    constexpr uint64_t high = 2549297995355413924ULL;
    constexpr uint64_t low = 4865540595714422341ULL;

    return state * ((((uint128_t)high) << 64) + low);
}

class PCG_XSL_RR_MCG : public AbstractRNG<uint64_t, uint128_t, 0, ~((uint64_t)0)>
{
  public:
    PCG_XSL_RR_MCG(uint128_t init_state) : AbstractRNG(init_state | 1u) {}

    PCG_XSL_RR_MCG() : AbstractRNG(get_bits_from_urandom<uint128_t>() | 1u) {}

    uint64_t operator()() noexcept
    {
        uint64_t out = xsl_rr_128_64(m_state);
        m_state = mcg_advance(m_state);
        return out;
    }
};

} // namespace stokhos

#endif

#endif
