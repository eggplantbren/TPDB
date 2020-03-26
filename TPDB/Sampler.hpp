#ifndef TPDB_Sampler_hpp
#define TPDB_Sampler_hpp

#include "DNest4/code/RNG.h"
#include <tuple>
#include <vector>

/* This file defines the following types: SamplerOptions, Sampler<T> */

using DNest4::RNG;


namespace TPDB
{

/* SamplerOptions type */
class SamplerOptions
{
    private:
        int num_particles;
        int mcmc_steps;
        
    public:
        SamplerOptions(int _num_particles, int _mcmc_steps);

        template<typename T>
        friend class Sampler;
};

/* Begin SamplerOptions implementations */

SamplerOptions::SamplerOptions(int _num_particles, int _mcmc_steps)
:num_particles(_num_particles)
,mcmc_steps(_mcmc_steps)
{

}

/* End SamplerOptions implementations */



/* Sampler type */
template<typename T>
class Sampler
{
    private:
        // Options object
        SamplerOptions options;

        // Particles and their scalars
        std::vector<T> particles;
        std::vector<std::pair<double, double>> scalars;

    public:

        // Default constructor
        Sampler(RNG& rng);
};

/* Begin Sampler implementations */

template<typename T>
Sampler<T>::Sampler(RNG& rng)
:options(100, 1000)
{
    for(int i=0; i<options.num_particles; ++i)
    {
        particles.emplace_back(rng);
        scalars.emplace_back(particles.back().get_scalars());
    }
}

/* End Sampler implementations */


} // namespace

#endif

