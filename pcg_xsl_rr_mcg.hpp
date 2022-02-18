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
