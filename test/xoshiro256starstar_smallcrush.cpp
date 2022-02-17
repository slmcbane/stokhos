#include "cdecls.hpp"

#include "xoshiro256starstar.hpp"

static_assert(std::is_same<uint32_t, unsigned long>::value, "Uh oh");

unsigned long get_next()
{
    static stokhos::TruncatedGenerator<stokhos::Xoshiro256starstar, uint32_t> rng(
        stokhos::Xoshiro256starstar());

    return rng();
}

int main()
{
    char name[] = "Lower 32 of xoshiro256starstar";
    unif01_Gen *gen = unif01_CreateExternGenBitsL(name, get_next);

    bbattery_SmallCrush(gen);
}
