#ifndef GRAPH_H
#define GRAPH_H
#include <string>
#include <vector>
#include "STACK.h"
#include "QUEUE.h"
#include "HEAP.h"
#include <iostream>
#include <cstdint>
class Graph
{
public:
    struct adjVertex
    {
        int weight;
        int id;
    };
    struct arrayElem
    {
        std::vector<adjVertex> adjListOfVertex;
        int id;
        std::string name;
        int indegree = 0;
    };

private:
    int vertexNum;
    std::vector<arrayElem> adjArray;
    bool connectivity;
    bool isHaveCircle;

public:
    Graph(int n);
    ~Graph();
    void DFS(int startVertexId);
    void BFS(int startVertexId);
    void addEdge(int id, adjVertex newEdge);
    void addVertex(arrayElem newVertex);
    void CreatGraph();
    void Topsort();
    void Dijkstra(int startId,int endId=-1);
    void Prim();
};

Graph::Graph(int n)
{
    vertexNum = n;
    adjArray.resize(vertexNum);
}
Graph::~Graph() {}
void Graph::addEdge(int id, adjVertex newEdge)
{
    adjArray[id].adjListOfVertex.push_back(newEdge);
    adjArray[newEdge.id].indegree++;
}
void Graph::addVertex(arrayElem newVertex)
{
    adjArray[newVertex.id] = newVertex;
}
void Graph::CreatGraph()
{
    arrayElem newVertex;
    adjVertex newEdge;
    int value;
    std::string name;
    std::cout << "Please input the nodes:\n";
    for (int i = 0; i < vertexNum; ++i)
    {
        std::cout << "Enter the id:" << std::endl;
        std::cin >> value;
        newVertex.id = value;
        std::cin.ignore();
        std::cout << "Enter the name:" << std::endl;
        std::cin >> name;
        newVertex.name = name;
        addVertex(newVertex);
    }
    std::cout << "Please input the edge:(id,newEdge)\n";
    while (std::cin >> value)
    {
        std::cout << "input new edge's id:";
        std::cin >> newEdge.id;
        std::cout << "input new edge's weight:";
        std::cin >> newEdge.weight;
        addEdge(value, newEdge);
        std::cout << "input next new edge:\n";
    }
}
void Graph::DFS(int startVertexId)
{
    Stack<int> S;
    bool visited[vertexNum] = {false};
    int tempVertexId;
    S.Push(startVertexId);

    while (!S.IsEmpty())
    {
        tempVertexId = S.Pop();

        if (!visited[tempVertexId])
        {
            std::cout << adjArray[tempVertexId].name << " ";
            visited[tempVertexId] = true;
        }
        for (auto neighbor : adjArray[tempVertexId].adjListOfVertex)
        {
            if (!visited[neighbor.id])
            {
                S.Push(neighbor.id);
            }
        }
    }
}
void Graph::BFS(int startVertexId)
{
    Queue<int> Q;
    Q.enqueue(startVertexId);
    bool visited[vertexNum] = {false};

    while (!Q.isEmpty())
    {
        int currentVertexId = Q.dequeue();
        visited[currentVertexId] = true;
        std::cout << adjArray[currentVertexId].name << std::endl;

        for (auto neighbor : adjArray[currentVertexId].adjListOfVertex)
        {
            if (!visited[neighbor.id])
            {
                Q.enqueue(neighbor.id);
            }
        }
    }
}
void Graph::Topsort()
{
    int indegree[vertexNum];
    int currentVertexId;
    int currentNeighborId;
    Queue<int> Q;
    for (auto vertex : adjArray)
    {
        indegree[vertex.id] = vertex.indegree;
        if (vertex.indegree == 0)
        {
            Q.enqueue(vertex.id);
        }
    }
    while (!Q.isEmpty())
    {
        currentVertexId = Q.dequeue();
        std::cout << adjArray[currentVertexId].name << "->";
        for (auto neighbor : adjArray[currentVertexId].adjListOfVertex)
        {
            currentNeighborId = neighbor.id;
            indegree[currentNeighborId]--;
            if (indegree[currentNeighborId] == 0)
            {
                Q.enqueue(currentNeighborId);
            }
        }
    }
}
void Graph::Dijkstra(int startId,int endId) // 有向图有权最短路径算法
{
    // 初始化表
    enum
    {
        Inifinity = INT32_MAX,
        Unknown = -1
    };
    struct tableElem
    {
        bool isKnown = false;
        int preId = Unknown;
        int distance = Inifinity;
    };
    struct heapElem
    {
        int id;
        int distance;
    };
    Heap<heapElem> H = Heap<heapElem>([](const heapElem &A, const heapElem &B) -> bool
                                      { return A.distance > B.distance; },
                                      []() -> heapElem
                                      { return heapElem{-1, -1}; },
                                      [](const heapElem &A, const heapElem &B) -> bool
                                      { return A.id == B.id; },
                                      vertexNum);

    int currentId;
    tableElem Table[vertexNum];

    Table[startId].distance = 0;
    H.Insert(heapElem{startId, 0});

    // 开始进入循环，依次处理节点
    while (!H.IsEmpty())
    {
        currentId = H.PopMin().id;
        int i;
        if (Table[currentId].isKnown)
        {
            continue; // 如果该节点已经被处理则跳过
        }
        Table[currentId].isKnown = true;

        // 主要执行逻辑：处理该节点的每一个邻居节点
        for (auto neighbor : adjArray[currentId].adjListOfVertex)
        {
            if (Table[neighbor.id].isKnown)
            {
                continue; // 如果这个邻居节点已经被处理过，跳过
            }

            // 将未处理的邻居节点插入最小堆，下一个处理的节点就是目前距离源点最近的未处理的点
            heapElem newValue{neighbor.id, Table[neighbor.id].distance};
            if (Table[neighbor.id].distance > Table[currentId].distance + neighbor.weight)
            {                                                                          // 如果该邻居到源点的距离 大于 从当前节点到该邻居节点的路线的距离，那么更新该邻居节点的 pre节点信息 和 distance
                newValue = {neighbor.id, Table[currentId].distance + neighbor.weight}; // 更新后的信息
                i = H.Contain(newValue);                                               // 如果堆中已经插入过该节点，那么需要更新该堆中节点信息，通过对比id进行查找
                if (i == -1)                                                           // 当堆中没有该邻居节点时，直接插入
                {
                    H.Insert(newValue);
                }
                else // 如果堆中存在该邻居节点，降低该邻居的值
                {
                    H.DecreaseKey(i, newValue);
                }

                // 更新表的信息
                Table[neighbor.id].distance = newValue.distance;
                Table[neighbor.id].preId = currentId;
            }
        }
    }
    if( endId == -1 )
    {
        for (int i = 1; i < vertexNum; ++i)
        {
            std::cout << "id: " << i << "\tname:" << adjArray[i].name << " ,\tdistance: " << Table[i].distance << ",\tpreID: " << Table[i].preId << "\tis Known? : " << Table[i].isKnown << "\n";
        }
    }
    else
    {
        int temp = endId;
        Stack<int> S;
        while( temp != startId )
        {
            S.Push(temp);
            temp = Table[temp].preId;
        }
        S.Push(temp);
        while(!S.IsEmpty())
        {
            std::cout << adjArray[S.Pop()].name << ",";
        }
    }
    
}
void Graph::Prim()
{
    // Create a heap to store edges
    Heap<adjVertex> H(
        // Comparator function to compare edges based on weight
        [](const adjVertex &A, const adjVertex &B) -> bool
        {
            return A.weight > B.weight;
        },
        // Function to return a default edge (invalid edge)
        []() -> adjVertex
        {
            return adjVertex{-1, -1};
        },
        // Function to compare edges based on their id
        [](const adjVertex &A, const adjVertex &B) -> bool
        {
            return A.id == B.id;
        },
        vertexNum);

    // Array to store parent of each vertex in the MST
    int parent[vertexNum];

    // Array to mark whether a vertex is included in the MST
    bool inMST[vertexNum];

    // Initialize arrays
    for (int i = 0; i < vertexNum; ++i)
    {
        parent[i] = -1;
        inMST[i] = false;
    }

    // Start with the first vertex
    int startVertex = 0;
    inMST[startVertex] = true;

    // Insert all edges of the startVertex into the heap
    for (auto &edge : adjArray[startVertex].adjListOfVertex)
    {
        H.Insert(edge);
    }

    while (!H.IsEmpty())
    {
        // Get the minimum-weight edge
        adjVertex minEdge = H.PopMin();

        int currentVertex = minEdge.id;

        // Skip if the vertex is already included in the MST
        if (inMST[currentVertex])
        {
            continue;
        }

        // Include the vertex in the MST
        inMST[currentVertex] = true;

        // Print or store the edge information as needed
        std::cout << "Edge: " << parent[currentVertex] << " - " << currentVertex << " Weight: " << minEdge.weight << "\n";

        // Update parent and insert new edges
        for (auto &edge : adjArray[currentVertex].adjListOfVertex)
        {
            if (!inMST[edge.id])
            {
                parent[edge.id] = currentVertex;
                H.Insert(edge);
            }
        }
    }
}
#endif