// Original code by Gonçalo Leão
// Updated by DA 2024/2025 Team

#ifndef DA_TP_CLASSES_GRAPH
#define DA_TP_CLASSES_GRAPH

#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
#include "MutablePriorityQueue.h" // not needed for now

template <class T>
class Edge;

#define INF std::numeric_limits<double>::max()

/************************* Vertex  **************************/

template <class T>
class Vertex {
public:
    Vertex(std::string location,int id, T code, bool parking);
    bool operator<(Vertex<T> & vertex) const; // // required by MutablePriorityQueue

    T getCode() const;
    std::vector<Edge<T> *> getAdj() const;
    bool isVisited() const;
    bool isProcessing() const;
    unsigned int getIndegree() const;
    double getDist() const;
    double getForwardDist() const;
    Edge<T> *getPath() const;
    Edge<T> *getForwardPath() const;
    std::vector<Edge<T> *> getIncoming() const;

    int getId() const;

    void setCode(T code);
    void setVisited(bool visited);
    void setProcessing(bool processing);

    int getLow() const;
    void setLow(int value);
    int getNum() const;
    void setNum(int value);

    void setIndegree(unsigned int indegree);
    void setDist(double dist);

    void setForwardDist(double fowardDist);

    void setPath(Edge<T> *path);
    void setForwardPath(Edge<T> *forwardPath);

    Edge<T> * addEdge(Vertex<T> *dest, int driving, int walking);
    bool removeEdge(T in);
    void removeOutgoingEdges();

    void setLocation(std::string location);

    void setId(int id);

    std::string getLocation() const;
    void setParking(bool parking);
    bool isParking() const;
    void setSelected(bool selected);
    bool isSelected() const;


    friend class MutablePriorityQueue<Vertex>;
protected:
    std::string location;
    int id;
    T code;                // code node
    std::vector<Edge<T> *> adj;  // outgoing edges

    // auxiliary fields
    bool visited = false; // used by DFS, BFS, Prim ...
    bool processing = false; // used by isDAG (in addition to the visited attribute)
    int low = -1, num = -1; // used by SCC Tarjan
    unsigned int indegree; // used by topsort
    double dist = 0;
    Edge<T> *path = nullptr;
    Edge<T> *forwardPath = nullptr;

    double forwardDist;


    bool parking = false;
    bool selected = false;
    std::vector<Edge<T> *> incoming; // incoming edges

    int queueIndex = 0; 		// required by MutablePriorityQueue and UFDS

    void deleteEdge(Edge<T> *edge);
};

/********************** Edge  ****************************/

template <class T>
class Edge {
public:
    Edge(Vertex<T> *orig, Vertex<T> *dest, int driving, int walking);

    Vertex<T> * getDest() const;
    double getWeight() const;
    bool isSelected() const;
    Vertex<T> * getOrig() const;
    Edge<T> *getReverse() const;
    double getFlow() const;
    int getWalking();
    int getDriving() const;


    void setSelected(bool selected);
    void setReverse(Edge<T> *reverse);
    void setFlow(double flow);
    void setWalking(int walking);
    void setDriving(int driving);

protected:
    Vertex<T> *orig;

    Vertex<T> * dest; // destination vertex
    double weight = 0; // edge weight, can also be used for capacity

    // auxiliary fields
    bool selected = false;

    // used for bidirectional edges
    Edge<T> *reverse = nullptr;

    double flow; // for flow-related problems

    int driving;
    int walking;
};

/********************** Graph  ****************************/

template <class T>
class Graph {
public:
    ~Graph();
    /*
    * Auxiliary function to find a vertex with a given the content.
    */
    Vertex<T> *findVertex(const T &in) const;

    Vertex<T> *idFindVertex(int id) const;

    /*
     *  Adds a vertex with a given content or code (in) to a graph (this).
     *  Returns true if successful, and false if a vertex with that content already exists.
     */
    bool addVertex(int id, std::string location, T code, bool parking);
    bool removeVertex(const T &in);

    /*
     * Adds an edge to a graph (this), given the contents of the source and
     * destination vertices and the edge weight (w).
     * Returns true if successful, and false if the source or destination vertex does not exist.
     */
    bool addEdge(const T &sourc, const T &dest, int walking, int driving);
    bool removeEdge(const T &source, const T &dest);
    bool addBidirectionalEdge(const T &sourc, const T &dest, int driving, int walking);

    int getNumVertex() const;

    std::vector<Vertex<T> *> getVertexSet() const;


protected:
    std::vector<Vertex<T> *> vertexSet;    // vertex set

    double ** distMatrix = nullptr;   // dist matrix for Floyd-Warshall
    int **pathMatrix = nullptr;   // path matrix for Floyd-Warshall

    /*
     * Finds the index of the vertex with a given content.
     */
    int findVertexIdx(const T &in) const;
    /**
    * Auxiliary function to set the "path" field to make a spanning tree.
    */

};

void deleteMatrix(int **m, int n);
void deleteMatrix(double **m, int n);


/************************* Vertex  **************************/

template<class T>
Vertex<T>::Vertex(std::string location, int id, T code, bool parking) : location(location),id(id),code(code),parking(parking) {}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

template <class T>
Edge<T> * Vertex<T>::addEdge(Vertex<T> *d, int driving,int walking) {
    auto newEdge = new Edge<T>(this, d, driving, walking);
    adj.push_back(newEdge);
    d->incoming.push_back(newEdge);
    return newEdge;
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Vertex<T>::removeEdge(T in) {
    bool removedEdge = false;
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        Vertex<T> *dest = edge->getDest();
        if (dest->getCode() == in) {
            it = adj.erase(it);
            deleteEdge(edge);
            removedEdge = true; // allows for multiple edges to connect the same pair of vertices (multigraph)
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

/*
 * Auxiliary function to remove an outgoing edge of a vertex.
 */
template <class T>
void Vertex<T>::removeOutgoingEdges() {
    auto it = adj.begin();
    while (it != adj.end()) {
        Edge<T> *edge = *it;
        it = adj.erase(it);
        deleteEdge(edge);
    }
}


template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getCode() const {
    return this->code;
}

template <class T>
int Vertex<T>::getLow() const {
    return this->low;
}

template <class T>
void Vertex<T>::setLow(int value) {
    this->low = value;
}

template <class T>
int Vertex<T>::getNum() const {
    return this->num;
}

template <class T>
void Vertex<T>::setNum(int value) {
    this->num = value;
}

template <class T>
std::vector<Edge<T>*> Vertex<T>::getAdj() const {
    return this->adj;
}

template <class T>
bool Vertex<T>::isVisited() const {
    return this->visited;
}

template <class T>
bool Vertex<T>::isProcessing() const {
    return this->processing;
}

template <class T>
unsigned int Vertex<T>::getIndegree() const {
    return this->indegree;
}

template <class T>
double Vertex<T>::getDist() const {
    return this->dist;
}

template<class T>
double Vertex<T>::getForwardDist() const {
    return this->forwardDist;
}

template <class T>
Edge<T> *Vertex<T>::getPath() const {
    return this->path;
}

template<class T>
Edge<T> * Vertex<T>::getForwardPath() const {
    return this->forwardPath;
}

template <class T>
std::vector<Edge<T> *> Vertex<T>::getIncoming() const {
    return this->incoming;
}

template<class T>
int Vertex<T>::getId() const {
    return this->id;
}

template<class T>
std::string Vertex<T>::getLocation() const {
    return this->location;
}

template<class T>
bool Vertex<T>::isParking() const {
    return this->parking;
}

template<class T>
bool Vertex<T>::isSelected() const {
    return this->selected;
}

template <class T>
void Vertex<T>::setCode(T in) {
    this->code = in;
}

template <class T>
void Vertex<T>::setVisited(bool visited) {
    this->visited = visited;
}

template <class T>
void Vertex<T>::setProcessing(bool processing) {
    this->processing = processing;
}

template <class T>
void Vertex<T>::setIndegree(unsigned int indegree) {
    this->indegree = indegree;
}

template <class T>
void Vertex<T>::setDist(double dist) {
    this->dist = dist;
}

template <class T>
void Vertex<T>::setForwardDist(double forwardDist) {
    this->forwardDist = forwardDist;
}

template <class T>
void Vertex<T>::setPath(Edge<T> *path) {
    this->path = path;
}

template<class T>
void Vertex<T>::setForwardPath(Edge<T> *forwardPath) {
    this->forwardPath = forwardPath;
}

template <class T>
void Vertex<T>::setSelected(bool selected) {
    this->selected = selected;
}

template <class T>
void Vertex<T>::deleteEdge(Edge<T> *edge) {
    Vertex<T> *dest = edge->getDest();
    // Remove the corresponding edge from the incoming list
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        if ((*it)->getOrig()->getCode() == code) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete edge;
}

template<class T>
void Vertex<T>::setLocation(std::string location) {
    this->location = location;
}

template<class T>
void Vertex<T>::setId(int id) {
    this->id = id;
}

template<class T>
void Vertex<T>::setParking(bool parking) {
    this->parking = parking;
}



/********************** Edge  ****************************/

template <class T>
Edge<T>::Edge(Vertex<T> *orig, Vertex<T> *dest, int driving,int walking): orig(orig), dest(dest), driving(driving), walking(walking) {}

template <class T>
Vertex<T> * Edge<T>::getDest() const {
    return this->dest;
}

template <class T>
double Edge<T>::getWeight() const {
    return this->weight;
}

template <class T>
Vertex<T> * Edge<T>::getOrig() const {
    return this->orig;
}

template <class T>
Edge<T> *Edge<T>::getReverse() const {
    return this->reverse;
}

template<class T>
int Edge<T>::getWalking() {
    return this->walking;
}

template<class T>
int Edge<T>::getDriving() const {
    return this->driving;
}


template <class T>
bool Edge<T>::isSelected() const {
    return this->selected;
}

template <class T>
double Edge<T>::getFlow() const {
    return flow;
}

template <class T>
void Edge<T>::setSelected(bool selected) {
    this->selected = selected;
}

template <class T>
void Edge<T>::setReverse(Edge<T> *reverse) {
    this->reverse = reverse;
}

template <class T>
void Edge<T>::setFlow(double flow) {
    this->flow = flow;
}

template <class T>
void Edge<T>::setWalking(int walking) {
    this->walking = walking;
}

template <class T>
void Edge<T>::setDriving(int driving) {
    this->driving = driving;
}
/********************** Graph  ****************************/

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
std::vector<Vertex<T> *> Graph<T>::getVertexSet() const {
    return vertexSet;
}

/*
 * Auxiliary function to find a vertex with a given content.
 */
template <class T>
Vertex<T> * Graph<T>::findVertex(const T &in) const {
    for (auto v : vertexSet)
        if (v->getCode() == in)
            return v;
    return nullptr;
}

/**
 * @brief Searches for a vertex in the graph by its ID
 *
 * @param id The ID of the vertex to find
 *
 * @return Pointer to the vertex with the matching ID, or nullptr if no such vertex exists
 *
 * @note Time Complexity: O(V), where V is the number of vertices in the graph
 */
template <class T>
Vertex<T> * Graph<T>::idFindVertex(int id) const {
    for (auto v : vertexSet)
        if (v->getId() == id)
            return v;
    return nullptr;
}

template <class T>
int Graph<T>::findVertexIdx(const T &in) const {
    for (unsigned i = 0; i < vertexSet.size(); i++)
        if (vertexSet[i]->getCode() == in)
            return i;
    return -1;
}

/**
 * @brief Adds a new vertex to the graph.
 *
 * @param id The unique identifier of the vertex.
 * @param location The name of the location associated with the vertex.
 * @param code The unique code representing the vertex.
 * @param parking A boolean indicating whether parking is available at this location.
 *
 * @return true if successful, false if a vertex with that content already exists.
 *
 * @note Time Complexity: O(V), where V is the number of vertices in the graph.
 */
template <class T>
bool Graph<T>::addVertex(int id, std::string location, T code, bool parking){
    if (findVertex(code) != nullptr)
        return false;
    vertexSet.push_back(new Vertex<T>(location,id,code,parking));
    return true;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */
template <class T>
bool Graph<T>::removeVertex(const T &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++) {
        if ((*it)->getCode() == in) {
            auto v = *it;
            v->removeOutgoingEdges();
            for (auto u : vertexSet) {
                u->removeEdge(v->getCode());
            }
            vertexSet.erase(it);
            delete v;
            return true;
        }
    }
    return false;
}

/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */
template <class T>
bool Graph<T>::addEdge(const T &sourc, const T &dest, int driving, int walking) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    v1->addEdge(v2, driving,walking);
    return true;
}

/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */
template <class T>
bool Graph<T>::removeEdge(const T &sourc, const T &dest) {
    Vertex<T> * srcVertex = findVertex(sourc);
    if (srcVertex == nullptr) {
        return false;
    }
    return srcVertex->removeEdge(dest);
}

template <class T>
bool Graph<T>::addBidirectionalEdge(const T &sourc, const T &dest, int driving, int walking) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == nullptr || v2 == nullptr)
        return false;
    auto e1 = v1->addEdge(v2, driving,walking);
    auto e2 = v2->addEdge(v1, driving,walking);
    e1->setReverse(e2);
    e2->setReverse(e1);
    return true;
}

inline void deleteMatrix(int **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

inline void deleteMatrix(double **m, int n) {
    if (m != nullptr) {
        for (int i = 0; i < n; i++)
            if (m[i] != nullptr)
                delete [] m[i];
        delete [] m;
    }
}

template <class T>
Graph<T>::~Graph() {
    deleteMatrix(distMatrix, vertexSet.size());
    deleteMatrix(pathMatrix, vertexSet.size());
}

#endif /* DA_TP_CLASSES_GRAPH */