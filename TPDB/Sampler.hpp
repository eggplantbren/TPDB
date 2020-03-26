#ifndef TPDB_Sampler_hpp
#define TPDB_Sampler_hpp

#include <DNest4/code/RNG.h>
#include <sqlite_modern_cpp/hdr/sqlite_modern_cpp.h>
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

        // Current iteration
        int iteration;

        // Particles and their scalars
        std::vector<T> particles;
        std::vector<std::pair<double, double>> scalars;

        // An output database
        sqlite::database db;

    public:

        // Default constructor
        Sampler(RNG& rng);

        // Do NS iteration
        void do_iteration(RNG& rng);
};

/* Begin Sampler implementations */

template<typename T>
Sampler<T>::Sampler(RNG& rng)
:options(100, 1000)
,iteration(0)
,db("output/output.db")
{
    for(int i=0; i<options.num_particles; ++i)
    {
        particles.emplace_back(rng);
        scalars.emplace_back(particles.back().get_scalars());
    }

    // Database pragmas
    db << "PRAGMA JOURNAL_MODE=WAL;";
    db << "PRAGMA SYNCHRONOUS=0;";
    
    // Create database tables
    db << "BEGIN;";
    db << "CREATE TABLE IF NOT EXISTS runs\
                (id            INTEGER PRIMARY KEY,\
                 num_particles INTEGER NOT NULL,\
                 mcmc_steps    INTEGER NOT NULL);";
    db << "CREATE TABLE IF NOT EXISTS particles\
                (id            INTEGER PRIMARY KEY,\
                 run_id        INTEGER NOT NULL,\
                 iteration     INTEGER NOT NULL,\
                 scalar1       REAL NOT NULL,\
                 scalar2       REAL NOT NULL,\
                 FOREIGN KEY (run_id) REFERENCES runs (id));";
    db << "COMMIT;";
    // Done creating database tables
    
    // Write this run's info to the database
    db << "BEGIN;";
    db << "INSERT INTO runs (num_particles, mcmc_steps)\
                VALUES (?, ?);" << options.num_particles << options.mcmc_steps;
    db << "COMMIT;";
}

template<typename T>
void Sampler<T>::do_iteration(RNG& rng)
{
    // Increment counter
    ++iteration;

    // Find worst particle
    int worst = 0;
    for(int i=1; i<options.num_particles; ++i)
        if(std::get<0>(scalars[i]) < std::get<0>(scalars[worst]))
            worst = i;

    // Save the scalars
    db << "BEGIN;";
    db << "INSERT INTO particles ()
}

/* End Sampler implementations */


} // namespace

#endif

