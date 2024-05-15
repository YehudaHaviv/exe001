// Algogithms.cpp

//id: 211998646
//mail: yehuda029974129@gmail.com

#include "Algorithms.hpp"
#include <queue>

    
// bfs sreach use to check connected one vertex and shortpath if there no valeu to edges in graph
std::vector<std::pair<std::string, size_t>> ariel::Algorithms::bfsSreach(const Graph& g, size_t start)
{
    size_t n = g.graph.size();

    std::vector<std::pair<std::string, size_t>> distanceANDpath(n, std::make_pair("", 1e9)); // distance of all vertex
    std::queue<size_t> q;
    q.push(start);
    distanceANDpath[start] = std::make_pair(std::to_string(start), 0);

    // bfs
    while (!q.empty())
    {   

        size_t vertex = q.front();
        q.pop();

        // neighbors
        for (size_t neighbor = 0; neighbor < n; neighbor++)
        {
            if (g.graph[vertex][neighbor] != 0 && distanceANDpath[neighbor].second > distanceANDpath[vertex].second + 1)
            {
                q.push(neighbor);
                distanceANDpath[neighbor].second = distanceANDpath[vertex].second + 1;
                distanceANDpath[neighbor].first = distanceANDpath[vertex].first + "->" + std::to_string(neighbor);
            }
        }
    }

    return distanceANDpath;
}

// Bellman-Ford algorithm for finding shortest paths in weighted graphs with negative cycles
std::vector<std::pair<std::string, int>> ariel::Algorithms::bellmanFord(const Graph& g, size_t start)
{
    size_t n = g.graph.size();
    std::vector<std::pair<std::string, int>> dist(n, std::make_pair("", 1e9)); // Initialize distances with a large value
    dist[start] = std::make_pair(std::to_string(start), 0);                    // Distance from source vertex to itself is always 0

    // Relax all edges V-1 times
    for (size_t i = 0; i < n - 1; ++i)
    {
        for (size_t u = 0; u < n; ++u)
        {
            for (size_t v = 0; v < n; ++v)
            {
                if (g.graph[u][v] != 0 && dist[u].second != 1e9 && dist[u].second + g.graph[u][v] < dist[v].second)
                {
                    dist[v].second = dist[u].second + g.graph[u][v];
                    dist[v].first = dist[u].first + "->" + std::to_string(v);
                }
            }
        }
    }

    // Check for negative cycles
    for (size_t u = 0; u < n; ++u)
    {
        for (size_t v = 0; v < n; ++v)
        {
            if (g.graph[u][v] != 0 && dist[u].second != 1e9 && dist[u].second + g.graph[u][v] < dist[v].second)
            {
                // Negative cycle found
                return std::vector<std::pair<std::string, int>>();
            }
        }
    }

    return dist; // No negative cycles
}

// basic use of bfs algo to check for each vertex if there is a way to get to all of the other vertex
int ariel::Algorithms::isConnected(const Graph& g)
{
    size_t n = g.graph.size();

    // Perform BFS from each vertex
    for (size_t i = 0; i < n ; i++)
    {
        std::vector<std::pair<std::string, size_t>> visited = bfsSreach(g, i);

        // check if all vertices are visited
        for (size_t visit = i + 1; visit < n; visit++)
        {
            if (visited[visit].second == 1e9)
            {
                return 0;
            } // found one vertex that was not been visited FALSE
        }
    }

    return 1; // true
}

std::string ariel::Algorithms::shortestPath(const Graph &g, int start, int end)
{
    int n = (int)g.graph.size();
    if (start < 0 || end < 0 || start > n || end > n)
    {
        return "input problem";
    }
    size_t s = (size_t)start;
    size_t e = (size_t)end;
    if (!g.valueEdgesGraph)
    {
        std::vector<std::pair<std::string, size_t>> distance(g.graph.size());
        distance = bfsSreach(g, s);

        if (distance[e].second == 1e9)
        {
            return "(-1) (there is no path between " + std::to_string(start) + " and " + std::to_string(end) + ").";
        }
        else
        {
            return distance[e].first;
        }
    }
    else
    { // Perform Dijkstra's algorithm for weighted graphs
        std::vector<std::pair<std::string, int>> distance(g.graph.size());
        distance = bellmanFord(g, s);
        if (distance.empty() || distance[e].second == 1e9)
        {
            return "(-1) (there is no path between " + std::to_string(start) + " and " + std::to_string(end) + ").";
        }
        else
        {
            return distance[e].first;
        }
    }
}
std::string ariel::Algorithms::isContainsCycle(const Graph& g)
{
    size_t n = g.graph.size();
    std::vector<int> parent(n, -1); // To store the parent of each vertex in the BFS traversal
    std::vector<int> color(n, 0); // 0: unvisited, 1: visiting, 2: visited

    // Perform BFS from each vertex in the graph
    for (size_t start = 0; start < n; ++start)
    {
        if (color[start] == 0)
        { // If vertex is unvisited
            std::queue<size_t> q;
            q.push(start);
            color[start] = 1; // Mark start vertex as visiting

            while (!q.empty())
            {
                size_t u = q.front();
                q.pop();

                for (size_t v = 0; v < n; ++v)
                {
                    if (g.graph[u][v] != 0)
                    { // If there's an edge from u to v
                        if (color[v] == 0)
                        { // If v is unvisited
                            parent[v] = u;
                            q.push(v);
                            color[v] = 1; // Mark v as visiting
                        }
                        else if (color[v] == 1 && parent[u] != v)
                        { // If v is visiting and not the parent of u
                            // Found a cycle
                            std::string cycle = std::to_string(v); // Start the cycle with v
                            int cur = u;
                            while (cur != v)
                            {
                                cycle = std::to_string(cur) + "->" + cycle; // Add vertices to the cycle
                                cur = parent[(size_t)cur];
                                if (cur == -1) break; // Break if cur is -1 (should not happen in a valid cycle)
                            }
                            cycle = std::to_string(v) + "->" + cycle; // Complete the cycle
                            return cycle; // Return the cycle
                        }
                    }
                }

                color[u] = 2; // Mark current vertex as visited
            }
        }
    }

    return "0"; // Return "0" if no cycle found
}

std::string ariel::Algorithms::isBipartite(const Graph& g)
{

    size_t n = g.graph.size();
    std::vector<int> color(n, -1); // 0 and 1: colors assigned to nodes, 2: unvisited
    std::queue<size_t> q;

    // Perform BFS from each vertex
    for (size_t start = 0; start < n; ++start)
    {
        if (color[start] == -1)
        {                     // If vertex is unvisited
            color[start] = 0; // Assign color 0 to start vertex
            q.push(start);

            while (!q.empty())
            {
                size_t u = q.front();
                q.pop();

                for (size_t v = 0; v < n; ++v)
                {
                    if (g.graph[u][v] != 0)
                    { // If there's an edge from u to v
                        if (color[v] == -1)
                        {                            // If v is unvisited
                            color[v] = 1 - color[u]; // Assign opposite color to v
                            q.push(v);
                        }
                        else if (color[v] == color[u])
                        {               // If u and v have the same color
                            return "0"; // Graph is not bipartite, return 0
                        }
                    }
                }
            }
        }
    }

    // Graph is bipartite, divide vertices into two sets
    size_t i = n-1;
    while (color[i] == 1)
    {
        i--;
    }
    size_t j = n;
    while (color[j] == 0)
    {
        j--;
    }
    std::string ans1 = "The graph is bipartite: A={";
    std::string ans2 = "B={";
    for (size_t t = 0; t < n; t++)
    {
        if (t != i && color[t] == 0)
        {
            ans1 += std::to_string(t) + ", ";
        }
        if (t != j && color[t] == 1)
        {
            ans2 += std::to_string(t) + ", ";
        }
    }
    ans1 += std::to_string(i) + "} ";
    ans2 += std::to_string(j) + "}.";
    return ans1 + ans2; // Return the sets
}

std::string ariel::Algorithms::negativeCycle(const Graph& g)
{
    if (!g.valueEdgesGraph)
    {
        return "no values to edges there for no negative cycle\n";
    }
    for (size_t i = 0; i < g.graph.size(); i++)
    {
        if (bellmanFord(g, i).empty())
        {
            return "there is a negative cycle in this graph\n";
        }
    }
    return "there is no negative cycle\n";
}
