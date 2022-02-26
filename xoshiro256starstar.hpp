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
#ifndef STOKHOS_XOSHIRO256STARSTAR_HPP
#define STOKHOS_XOSHIRO256STARSTAR_HPP

#include "splitmix64.hpp"

#include <array>

namespace stokhos
{

class Xoshiro256starstar : public AbstractRNG<uint64_t, std::array<uint64_t, 4>, 1>
{
  public:
    using AbstractRNG::AbstractRNG;

    // If given a single uint64_t for the state, uses SplitMix64 to initialize
    // all 256 bits as suggested by Vigna et al.
    explicit Xoshiro256starstar(uint64_t seed) noexcept : AbstractRNG(seed_state(seed)) {}

    // Default constructor seed from urandom
    Xoshiro256starstar() : AbstractRNG(get_bits_from_urandom<std::array<uint64_t, 4>>()) {}

    uint64_t operator()() noexcept override
    {
        const uint64_t result = rol64(m_state[1] * 5, 7) * 9;
        const uint64_t t = m_state[1] << 17;

        m_state[2] ^= m_state[0];
        m_state[3] ^= m_state[1];
        m_state[1] ^= m_state[2];
        m_state[0] ^= m_state[3];
        m_state[2] ^= t;
        m_state[3] = rol64(m_state[3], 45);

        return result;
    }

  private:
    // This function is responsible for seeding the state from a 64-bit seed
    // by feeding it into SplitMix64
    static std::array<uint64_t, 4> seed_state(uint64_t seed)
    {
        SplitMix64 splitmix(seed);
        std::array<uint64_t, 4> state{splitmix(), splitmix(), splitmix(), splitmix()};
        return state;
    }

    static uint64_t rol64(uint64_t x, int k) { return (x << k) | (x >> (64 - k)); }
};

} // namespace stokhos

#endif // STOKHOS_XOSHIRO256STARSTAR_HPP
