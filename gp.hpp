/**
 * @file gp.hpp
 * @author Marek Sedlacek (xsedla1b@fit.vutbr.cz)
 * @brief Genetic programming unit
 * @date December 2021
 */

#ifndef _GP_HPP_
#define _GP_HPP_

#include "graph.hpp"
#include <list>
#include <stddef.h>
#include <random>
#include <time.h>
#include <cstdlib>

/** Genetic programming resources */
namespace GP {
    
    inline void init() {
        std::srand(time(nullptr));
    }

    inline int rand_int(int min, int max) {
        return (std::rand() % (max - min + 1)) + min;
    }

    /** Phenotype of a genome */
    class Phenotype {
    private:
        Graph *graph;  ///< The main graph for this phenotype
        int k;

        /**
         * DFS visit for fitness calculation
         * @param v Node to visit
         * @param visited Array of visted flags
         * @param[out] incorrect The amount of incorrectly colored nodes
         */
        void fitness_dfs_visit(int v, bool **visited, int *incorrect);
    public:
        Color *colors; ///< Phenotype's coloring
        
        /**
         * @brief Construct a new Phenotype object
         * @param graph Graph in which this phenotype is evolving
         * @param k The amount of colors to color with
         */
        Phenotype(Graph *graph, int k);

        /**
         * @brief Destroy the Phenotype object
         */
        ~Phenotype() {
            delete[] colors;
        }

        /**
         * Calculates fitness value for a phenotype
         * @return Phenotype's fitness where the lower it is the better and 0 is correctly colored graph
         */
        int fitness();
    };


    /** Population of phenotypes for genetic programming */
    class Population { 
    private:
        Graph *graph; ///< Graph in which this population is evolving
        size_t size;
        int k;        ///< Number of available colors (k-coloring)
    public:
        std::list<Phenotype *> *candidates;  ///< Candidate phenotypes
        int *quality; ///< An array of fitness quality values for each phenotype
        
        /**
         * @brief Construct a new Population object
         * @param size The amount of candidate colorings (phenotypes) to create
         * @param k The amount of colors to color with
         */
        Population(Graph *graph, size_t size, int k);
        /**
         * @brief Destroy the Population object
         */
        ~Population();

        /**
         * @brief Updates fitness values
         * 
         * @return Color* 
         */
        Color *evaluate();
    };
};

#endif//_GP_HPP_