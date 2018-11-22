#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <vector>
#include <queue>
#define INT_MAX 2147483647

using namespace std;

typedef struct nod {
	int city;
	int cost;
	int status;
} node;

struct qbase {
	int key;
	int val;
	bool operator<(const struct qbase &s) const {
		return this->val > s.val;
	}
};

int N;
vector<node> graph[501];
bool visit[501];
int dist[501];

int Dijkstra(int s, int destroy) {
	//initialization
	fill_n(visit+1, N, false);
	fill_n(dist+1, N, INT_MAX);

	priority_queue<qbase> q;
	q.push(qbase { s, 0 });
	dist[s] = 0;

	int val;
	int city;
	qbase node;
	while (!q.empty()) {
		node = q.top();
		q.pop();
		city = node.key;
		val = node.val;
		if (visit[city]) {
			continue;
		}
		visit[city] = true;
		for (auto n : graph[city]) {
			if (!visit[n.city] && n.city!=destroy) {
				if (n.status == 1) {
					if (dist[n.city] > dist[city]) {
						dist[n.city] = dist[city];
						q.push(qbase{ n.city, dist[n.city] });
					}
				}
				else {
					if (dist[n.city] > dist[city] + n.cost) {
						dist[n.city] = dist[city] + n.cost;
						q.push(qbase{ n.city, dist[n.city] });
					}
				}
			}
		}
	}
	dist[destroy] = 0;
	return *max_element(dist+1, dist + N+1);
}


int main() {
	//initialization

	int M;
	scanf_s("%d %d", &N, &M);

	int v1, v2, cost, status;
	node vertex;
	while (M--) {
		scanf_s("%d %d %d %d", &v1, &v2, &cost, &status);
		vertex.city = v2;
		vertex.cost = cost;
		vertex.status = status;
		graph[v1].push_back(vertex);
		vertex.city = v1;
		graph[v2].push_back(vertex);
	}

	int costRepair[501] = { 0 };
	costRepair[1] = Dijkstra(2, 1);
	for (int v = 2; v <= N; v++) {
		costRepair[v] = Dijkstra(1, v);
	}

	vector<int> res;
	int maxCost = *max_element(costRepair + 1, costRepair + N + 1);

	if (maxCost == 0) {
		printf("%d\n");
		return 0;
	}

	for (int v = 1; v <= N; v++) {
		if (costRepair[v] == maxCost) {
			res.push_back(v);
		}
	}
	printf("%d", res[0]);
	for (int i = 1; i < res.size(); i++) {
		printf(" %d", res[i]);
	}
	printf("\n");

	system("pause");
	return 0;
}