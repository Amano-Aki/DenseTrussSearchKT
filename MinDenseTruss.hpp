/**
 * @file MinDenseTruss.hpp
 * @author Tianyang Xu
 * @brief Implementation of alg. 6
 * @version 0.1
 * @date 2021-04-03
 *
 *
 */

#pragma once
#include "TrussDecomposition.hpp"
#include <Snap.h>
#include <vector>

/**
 * @brief Implementation of alg. 6.
 *
 */
class MinDenseTruss {
  public:
    /**
     * @brief Users are allowed to choose the optimization type by using bit OR
     * on those enum values.
     *
     */
    enum Optimization {
        /// Optimization I: Batch based deletion
        BatchDeletion = 1,
        /// Optimization II: Early-stop based deletion
        EarlyStopDeletion = 2,
        /// Optimization III: Local exploration
        LocalExploration = 4
    };

    MinDenseTruss() = delete;
    /**
     * @brief Construct a new Min Dense Truss object. Computation does not start
     * when initialized because there are different optimizations that apply and
     * users are allowed to choose the optimizations to see the results.
     *
     * @param truss
     * @param keywords a keyword vector that satisfies keywords[keyword number]
     * = a vector of node numbers
     * @param trussness The trussness of the given parameter `truss`. You are
     * required to give it as to accelerate the calculation and simplify the
     * implementation.
     */
    MinDenseTruss(PUndirNet graph, TCnCom truss,
                  const std::vector<std::vector<int>> &keywords, int trussness)
        : graph(graph), truss(truss), keywords(keywords), trussness(trussness) {
    }

    /**
     * @brief An implementation of alg. 6.
     *
     * @param setting optimizations that apply.
     * @return TIntV vector of nodes in the minimal dense truss.
     */
    TIntV findMinDenseTruss(int setting);

  private:
    PUndirNet graph;
    TCnCom truss;
    const std::vector<std::vector<int>> &keywords;
    int trussness;
    /// Auxiliary variable for `selectNodesToDel`
    int deleteSize = 1;
    /// Auxiliary variable for `selectNodesToDel`
    bool isLastSuccessful = true;
    /// Early-stop threshold
    /// Number made by guessing
    int earlyStopThreshold = truss.Len() / 5;

    /**
     * @brief A helper function for alg. 6.
     *
     * @param gdenNodes A vector of nodes from which `toDelete` is deleted.
     * @param toDelete A vector of nodes where the deletion starts with.
     * @return TIntV vector of nodes in the truss. Empty if not exists.
     */
    TIntV findKTruss(TIntV gdenNodes, const TIntV &toDelete);
    /**
     * @brief To implement Optimization I.
     * @note This function increase the deletion size by 1. I personally
     * have no idea how it works.
     * @return TIntV
     */
    TIntV selectNodesToDel(const TIntV &gdenDiffVis, int setting);
};