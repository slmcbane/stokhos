#include "cdecls.hpp"

#include "truncated_generator.hpp"
#include "xoshiro256starstar.hpp"

using namespace stokhos;

static_assert(std::is_same<uint32_t, unsigned int>::value, "Uh oh");

uint32_t reverse_bits(uint32_t n)
{
    n = ((n >> 1) & 0x55555555) | ((n << 1) & 0xaaaaaaaa);
    n = ((n >> 2) & 0x33333333) | ((n << 2) & 0xcccccccc);
    n = ((n >> 4) & 0x0f0f0f0f) | ((n << 4) & 0xf0f0f0f0);
    n = ((n >> 8) & 0x00ff00ff) | ((n << 8) & 0xff00ff00);
    n = ((n >> 16) & 0x0000ffff) | ((n << 16) & 0xffff0000);
    return n;
}

unsigned int get_next_upper32()
{
    static auto rng = Xoshiro256starstar();
    constexpr uint64_t mask = static_cast<uint64_t>(static_cast<uint32_t>(-1)) << 32;

    return (rng() & mask >> 32);
}

unsigned int get_next_upper32_reversed() { return reverse_bits(get_next_upper32()); }

int main()
{
    char name2[] = "upper 32 bits of xoshiro256starstar";
    unif01_Gen *gen = unif01_CreateExternGenBits(name2, get_next_upper32);
    bbattery_Crush(gen);
    unif01_DeleteExternGenBits(gen);

    char name4[] = "upper 32 bits of xoshiro256starstar reversed";
    gen = unif01_CreateExternGenBits(name4, get_next_upper32_reversed);
    bbattery_Crush(gen);
    unif01_DeleteExternGenBits(gen);

    return 0;
}
