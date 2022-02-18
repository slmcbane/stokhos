#include "cdecls.hpp"
#include "xoshiro256starstar.hpp"

#include <random>

using namespace stokhos;

double get_next()
{
    static auto rng = Xoshiro256starstar();
    return std::generate_canonical<double, 64>(rng);
}

int main()
{
    char name[] = "xoshiro256starstar";
    unif01_Gen *gen = unif01_CreateExternGen01(name, get_next);
    bbattery_Crush(gen);
    unif01_DeleteExternGen01(gen);

    return 0;
}
