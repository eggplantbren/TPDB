#ifndef TPDB_Example_hpp
#define TPDB_Example_hpp

#include "DNest4/code/RNG.h"
#include "DNest4/code/Utils.h"
#include <tuple>

using DNest4::RNG;
using DNest4::wrap;

namespace TPDB
{

/*
* A simple example model.
*/
class Example
{
    private:
        static constexpr int N = 20; // Dimensionality
        std::vector<double> xs;

    public:

        // Constructor
        Example(RNG& rng);

        // Metropolis proposal in-place, return log(hastings) for prior sampling
        double perturb(RNG& rng);

        // Return scalars
        std::pair<double, double> get_scalars() const;

        // Render as string
        std::string render() const;

};

/* IMPLEMENTATIONS FOLLOW */

Example::Example(RNG& rng)
:xs(N)
{
    for(int i=0; i<N; ++i)
        xs[i] = rng.rand();
}

double Example::perturb(RNG& rng)
{
    int k = rng.rand_int(N);
    xs[k] += rng.randh();
    wrap(xs[k], 0.0, 1.0);
    return 0;
}

std::pair<double, double> Example::get_scalars() const
{
    double f1 = 0.0;
    double f2 = 0.0;

    // Parameters of the two peaks
    static constexpr double w = 0.01;
    static constexpr double tau = 1.0/(w*w);

    for(int i=0; i<N; ++i)
    {
        f1 += -0.5*tau*pow(xs[i] - 0.4, 2);
        f2 += -0.5*tau*pow(xs[i] - 0.6, 2);
    }

    return {f1, f2};
}

} // namespace

#endif

