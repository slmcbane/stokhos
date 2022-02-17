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
