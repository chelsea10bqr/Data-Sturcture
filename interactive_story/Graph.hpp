#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

#include<cmath>
#include <string>
#include <iostream>

/**
* @return The number of vertices in the Graph
*/
template <class V, class E>
unsigned int Graph<V,E>::size() const {
  // TODO: Part 2
  return vertexMap.size();
}


/**
* @return Returns the degree of a given vertex.
* @param v Given vertex to return degree.
*/
template <class V, class E>
unsigned int Graph<V,E>::degree(const V & v) const {
  // TODO: Part 2
  return adjList.at(v.key()).size();
}


/**
* Inserts a Vertex into the Graph by adding it to the Vertex map and adjacency list
* @param key The key of the Vertex to insert
* @return The inserted Vertex
*/
template <class V, class E>
V & Graph<V,E>::insertVertex(std::string key) {
  // TODO: Part 2
  V & v = *(new V(key));
  vertexMap.insert(std::pair<std::string, V &> (key, v));
  std::list<edgeListIter> it;
  adjList.insert(std::pair<std::string, std::list<edgeListIter>> (key, it));
  return v;
}


/**
* Removes a given Vertex
* @param v The Vertex to remove
*/
template <class V, class E>
void Graph<V,E>::removeVertex(const std::string & key) {
  // TODO: Part 2
  V& vertex = vertexMap.find(key)->second;
  std::list<edgeListIter> incident = adjList.find(key)->second;

  for (auto i = incident.begin(); i != incident.end(); i++) {
   edgeList.erase(*i);
   }

   for(auto i2=adjList.begin();i2 !=adjList.end();i2++){
     for(auto i3=incident.begin();i3!=incident.end();i3++){
       for(auto i4=(*i2).second.begin();i4!=(*i2).second.end();i4++){
         if(*i4==*i3){
           ((*i2).second).erase(i4);
         }
       }
     }
   }

  vertexMap.erase(key);
}


/**
* Inserts an Edge into the adjacency list
* @param v1 The source Vertex
* @param v2 The destination Vertex
* @return The inserted Edge
*/
template <class V, class E>
E & Graph<V,E>::insertEdge(const V & v1, const V & v2) {
  // TODO: Part 2
  E & e = *(new E(v1, v2));
  // point to two new nodes of lists respectivecly
  edgeList.push_front(e);
  edgeListIter it = edgeList.begin();
  adjList.at(v1.key()).push_front(it);
  adjList.at(v2.key()).push_front(it);
  return e;
}


/**
* Removes an Edge from the Graph
* @param key1 The key of the ource Vertex
* @param key2 The key of the destination Vertex
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const std::string key1, const std::string key2) {
  // TODO: Part 2
  if(!isAdjacent(key1,key2)){
    return;
  }
  std::list<edgeListIter> incident = adjList.find(key1)->second;
  edgeListIter i;
  for (auto incidentIt = incident.begin();incidentIt != incident.end();incidentIt++){
    if(((**incidentIt).get().source().key()==key1&&(**incidentIt).get().dest().key()==key2)){
      i = *incidentIt;
    }
  }
edgeList.erase(i);
for(auto i2 = (adjList.find(key1)->second).begin();i2!=(adjList.find(key1)->second).end();i2++){
  if(*i2 == i){
    (adjList.find(key1)->second).erase(i2);
  }
}
for(auto i2 = (adjList.find(key2)->second).begin();i2!=(adjList.find(key2)->second).end();i2++){
  if(*i2 == i){
    (adjList.find(key1)->second).erase(i2);
  }
}
}


/**
* Removes an Edge from the adjacency list at the location of the given iterator
* @param it An iterator at the location of the Edge that
* you would like to remove
*/
template <class V, class E>
void Graph<V,E>::removeEdge(const edgeListIter & it) {
  // TODO: Part 2
  std::string key1;
  std::string key2;
  key1 = (*it).get().source().key();
  key2 = (*it).get().dest().key();
  edgeList.erase(it);
  for(auto it2 = (adjList.find(key1)->second).begin();it2!=(adjList.find(key1)->second).end();it2++){
    if(*it2 == it){
      (adjList.find(key1)->second).erase(it2);
    }
  }
  for(auto it2 = (adjList.find(key2)->second).begin();it2!=(adjList.find(key2)->second).end();it2++){
    if(*it2 == it){
      (adjList.find(key1)->second).erase(it2);
    }
  }

}


/**
* @param key The key of an arbitrary Vertex "v"
* @return The list edges (by reference) that are adjacent to "v"
*/
template <class V, class E>
const std::list<std::reference_wrapper<E>> Graph<V,E>::incidentEdges(const std::string key) const {
  // TODO: Part 2
  std::list<std::reference_wrapper<E>> edges;
  std::list<edgeListIter> newList = adjList.at(key);

  //add all elements of the list
  for(edgeListIter it: newList) {
    edges.push_front(*it);
  }
  return edges;
}


/**
* Return whether the two vertices are adjacent to one another
* @param key1 The key of the source Vertex
* @param key2 The key of the destination Vertex
* @return True if v1 is adjacent to v2, False otherwise
*/
template <class V, class E>
bool Graph<V,E>::isAdjacent(const std::string key1, const std::string key2) const {
  // TODO: Part 2
  std::string toCheck;
  std::string theOther;
  if (degree(vertexMap.at(key1)) < degree(vertexMap.at(key2))) {
    std::list<std::reference_wrapper<E>> incident = incidentEdges(key1);
    for(auto it: incident) {
      if((it.get()).dest() == key2) {
        return true;
      }
    }
    return false;
  } else {
    std::list<std::reference_wrapper<E>> incident = incidentEdges(key2);
    for(auto it: incident) {
      if((it.get()).source() == key1) {
        return true;
      }
    }
    return false;
  }
}
