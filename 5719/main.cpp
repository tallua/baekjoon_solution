#include <algorithm>
#include <array>
#include <iostream>
#include <queue>
#include <ranges>
#include <set>
#include <unordered_map>
#include <vector>

//

using Distance = int;
using Node = std::size_t;
struct Edge {
    Node node;
    Distance distance;
};
using Graph = std::vector<std::vector<Edge>>;

Distance almost_min_path(Graph& g, Node S, Node D);

namespace {

const Distance max_distance = 10000000;
struct Backtrace {
    Node node;
    Edge* prev = nullptr;
};

struct Task {
    Node node;
    Backtrace trace;
    Distance distance;
};

struct Comp {
    auto operator()(const Task& lhs, const Task rhs) const {
        return lhs.distance > rhs.distance;
    }
};

struct Dijkstra {
    Distance distance;
    std::vector<Backtrace> prev;
};

std::vector<Dijkstra> RunDijkstra(Graph& graph, Node start) {
    std::vector<bool> visited(graph.size(), false);

    std::vector<Dijkstra> dijkstra(graph.size(), {max_distance, {}});

    std::priority_queue<Task, std::vector<Task>, Comp> task_queue;
    task_queue.push({start, {start, nullptr}, 0});

    while (!task_queue.empty()) {
        auto task = task_queue.top();
        task_queue.pop();

        if (dijkstra[task.node].distance < task.distance) {
            continue;
        } else if (dijkstra[task.node].distance == task.distance) {
            dijkstra[task.node].prev.push_back(task.trace);
            continue;
        }
        dijkstra[task.node].distance = task.distance;
        dijkstra[task.node].prev.push_back(task.trace);

        for (auto&& adj : graph[task.node]) {
            const auto dist_to_adj = task.distance + adj.distance;
            if (dijkstra[adj.node].distance < dist_to_adj) {
                continue;
            }

            task_queue.push(
                {adj.node, {task.node, std::addressof(adj)}, dist_to_adj});
        }
    }

    return dijkstra;
}

void RemoveMinPathEdges(Graph& graph, Node end,
                        const std::vector<Dijkstra>& dijkstra) {
    std::vector<bool> visited(graph.size(), false);
    std::vector<Node> nodes_on_min_dist;
    nodes_on_min_dist.push_back(end);
    while (!nodes_on_min_dist.empty()) {
        const auto top = nodes_on_min_dist.back();
        nodes_on_min_dist.pop_back();
        if (visited[top]) {
            continue;
        }
        visited[top] = true;

        for (auto&& back : dijkstra[top].prev) {
            if (back.prev == nullptr)
                continue;
            back.prev->distance = max_distance;
            nodes_on_min_dist.push_back(back.node);
        }
    }
}

void test_case(std::size_t N, std::size_t M) {
    Graph directedGraph(N);

    Node S, D;
    std::cin >> S >> D;

    for (auto m = decltype(M)(0); m < M; ++m) {
        Node U, V;
        Distance P;
        std::cin >> U >> V >> P;

        directedGraph[U].push_back({V, P});
    }

    std::cout << almost_min_path(directedGraph, S, D) << '\n';
}

}  // namespace

Distance almost_min_path(Graph& g, Node S, Node D) {
    const auto dijkstra = RunDijkstra(g, S);

    RemoveMinPathEdges(g, D, dijkstra);

    const auto dijkstra2 = RunDijkstra(g, S);

    if (dijkstra2[D].distance == max_distance) {
        return -1;
    }

    return dijkstra2[D].distance;
}

#ifndef TEST_ENABLED
int main(int argc, char** argv) {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    std::size_t N, M;
    std::cin >> N >> M;

    while (N != 0 && M != 0) {
        test_case(N, M);

        std::cin >> N >> M;
    }

    return 0;
}
#endif