#include <DNest4/code/RNG.h>
#include <iostream>
#include <TPDB/Example.hpp>
#include <TPDB/Sampler.hpp>

using DNest4::RNG;
using Sampler = TPDB::Sampler<TPDB::Example>;

int main()
{
    // Create RNG
    RNG rng(time(0));

    // Create Sampler
    Sampler sampler(rng);

    return 0;
}

