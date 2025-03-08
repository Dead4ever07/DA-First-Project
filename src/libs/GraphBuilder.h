//
// Created by luis-santos on 2/27/25.
//

#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include "Graph.h"





/**
 * @brief It fullfills the graph with the information provided.
 * @param[out] g The name of the reservoir.
 * @param[in] Distances The municipality where the reservoir is located.
 * @param[in] Locations The ID of the reservoir.
 */
template <typename T>
void graphFiller(Graph<T> *g, std::string Distances, std::string Locations);














#endif //GRAPHBUILDER_H
