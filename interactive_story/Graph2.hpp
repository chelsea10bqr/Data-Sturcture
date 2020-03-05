#include <queue>
#include <algorithm>
#include <string>
#include <list>
#include "Graph.h"

/**
 * Returns an std::list of vertex keys that creates some shortest path between `start` and `end`.
 *
 * This list MUST include the key of the `start` vertex as the first vertex in the list, the key of
 * the `end` vertex as the last element in the list, and an ordered list of all vertices that must
 * be traveled along the shortest path.
 *
 * For example, the path a -> c -> e returns a list with three elements: "a", "c", "e".
 *
 * @param start The key for the starting vertex.
 * @param end   The key for the ending vertex.
 */
template <class V, class E>
std::list<std::string> Graph<V,E>::shortestPath(const std::string start, const std::string end) {
  std::list<std::string> path;
  std::queue<std::string> queue;
  std::unordered_map<std::string, int> visited;
  std::unordered_map <string,string> record;
  for(auto i = vertexMap.begin(); i != vertexMap.end(); ++i) {
    visited.insert({i->second.key(), 0});
  }
  std:: string starting = start;
visited[starting] = 1;
queue.push(starting);
while (!queue.empty()) {
  string plot = queue.front();
  queue.pop();
  std::list<std::reference_wrapper<E>> incident = incidentEdges(plot);
  for (auto it = incident.begin(); it != incident.end(); ++it) {
    string destination = it->get().dest().key();
    string source = it->get().source().key();
    string check;
    if(destination == plot) check = source;
    if(source == plot) check = destination;
      if (visited[check] == 1) {
        continue;
      } else {
          visited[check] = 1;
          record[check] = plot;
          queue.push(check);
          if (check == end){
             break;
           }
      }
  }
}

string ending = end;
path.push_back(ending);
for (auto it = record.begin(); it != record.end(); ++it) {
  if (record[ending] != "") {
    path.push_front(record[ending]);
    ending = record[ending];
  }
}
return path;
}
