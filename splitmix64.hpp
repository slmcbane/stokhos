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

