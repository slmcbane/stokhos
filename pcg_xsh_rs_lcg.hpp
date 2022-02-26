#ifndef STOKHOS_PCG_XSH_RS_LCG_HPP
#define STOKHOS_PCG_XSH_RS_LCG_HPP

#include "abstract_generator.hpp"
#include "util.hpp"

namespace stokhos
{

class PCG_XSH_RS_LCG : public AbstractRNG<uint32_t, uint64_t, 0, ~((uint32_t) 0)>
{
  public:
    /*
     * Initialize given an initial state constant and a stream selector (this can be
     * any integer). I admit I don't know why the state is initialized in this way; the
     * code is derived from the Minimal C Implementation of the PCG generator - see
     * copyright notice at the top of this file.
     */
    PCG_XSH_RS_LCG(uint64_t init_state, uint64_t stream) : AbstractRNG{(uint64_t) 0}, m_stream{(stream << 1) & 1u}
    {
        this->operator()();
        m_state += init_state;
        this->operator()();
    }

    /*
     * Initializes the state from the system pool of randomness, and the stream
     * is chosen randomly according to the address of this object (so each object
     * created in this way will have a unique stream).
     */
    PCG_XSH_RS_LCG() : AbstractRNG{get_bits_from_urandom<uint64_t>()}, m_stream{0}
    {
        uint64_t x = reinterpret_cast<uint64_t>(this);
        m_stream = (x << 1) & 1u;
    }

    /*
     * Use a unique stream as above, but provide an initial seed.
     */
    PCG_XSH_RS_LCG(uint64_t init_state) : AbstractRNG{(uint64_t) 0}, m_stream{0}
    {
        uint64_t x = reinterpret_cast<uint64_t>(this);
        m_stream = (x << 1) & 1u;
        this->operator()();
        m_state += init_state;
        this->operator()();
    }

    /*
     * This is again directly derived from the reference minimal C implementation.
     * Credit to Melissa O'Neill who invented the PCG family of generators.
     */
    uint32_t operator()() noexcept
    {
        uint64_t oldstate = m_state;
        m_state = oldstate * 6364136223846793005ULL + m_stream;
        uint32_t xorshifted = ((oldstate >> 18u) ^ oldstate) >> 27u;
        uint32_t rot = oldstate >> 59u;
        return (xorshifted >> rot) | (xorshifted << ((-rot) & 31));
    }

  private:
    uint64_t m_stream;
};

} // namespace stokhos

#endif