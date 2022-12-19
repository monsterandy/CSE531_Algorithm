class Graph:
    def __init__(self, vertices) -> None:
        self.vertices = vertices
        self.edges = []
        self.parent = [i for i in range(vertices)]
        self.rank = [0 for i in range(vertices)]
    
    def print_all_edges(self):
        for edge in self.edges:
            print(edge)

    def sort_edges(self):
        self.edges.sort(key=lambda x: x[2])

    def root(self, u):
        if self.parent[u] != u:
            self.parent[u] = self.root(self.parent[u])
        return self.parent[u]

    def union(self, u, v):
        u_root = self.root(u)
        v_root = self.root(v)

        if self.rank[u_root] < self.rank[v_root]:
            self.parent[u_root] = v_root
        elif self.rank[u_root] > self.rank[v_root]:
            self.parent[v_root] = u_root
        else:
            self.parent[v_root] = u_root
            self.rank[u_root] += 1
    
    def kruskal(self):
        # assume the edges are sorted
        weight = 0
        for edge in self.edges:
            u, v, w = edge
            if self.root(u) != self.root(v):
                self.union(u, v)
                weight += w
        
        return weight


if __name__ == "__main__":
    n, m = map(int, input().split())
    graph = Graph(n)
    
    for i in range(m):
        u, v, w = map(int, input().split())
        graph.edges.append([u-1, v-1, w])
    
    graph.sort_edges()
    print(graph.kruskal())