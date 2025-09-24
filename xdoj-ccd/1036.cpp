#include <iostream>
#include <vector>
#include <utility>
#include <cmath>
#include <iomanip>
#include <queue>

using namespace std;

class BFS {
	public:
		BFS(vector<pair<int, int>> node, int count, int step)
			: node(node), count(count), step(step) {
			getMinDistance();
			initMap();
			getResult();
		}

		void printMinDistance() {
			cout << fixed << setprecision(1) << min_distance << endl;
		}

		void printResult() {
			if (result == true) {
				cout << "Yes" << endl;
			} else {
				cout << "No" << endl;
			}
		}

//		void traverseMap() {
//			for (int i = 0; i < count; i++) {
//				for (int j = 0; j < count; j++) {
//					cout << mapForNode[i][j] << " ";
//				}
//				cout << endl;
//			}
//		}
	private:
		vector<pair<int, int>> node;
		double min_distance;
		int count;
		int step;
		bool result;
		vector<vector<double>> mapForNode;

		double getDistance(pair<int, int> one, pair<int, int> two) {
			int temp = pow(one.first - two.first, 2) + pow(one.second - two.second, 2);
			return sqrt(temp);
		}

		void getMinDistance() {
			double min = 5000;
			for (int i = 0; i < count; i++) {
				double temp = getDistance(node[i], {0, 0});
				if (temp < min) {
					min = temp;
				}
			}
			min_distance = min - 7.5;
		}

		void initMap() {
			vector<vector<double>> temp(count + 2, vector<double>(count + 2, -1.0));
			for (int i = 0; i < count; i++) {
				for (int j = 0; j < count; j++) {
					double dis = getDistance(node[i], node[j]);
					if (dis <= step && dis > 0) {
						temp[i][j] = dis;
					}
				}
			}

			for (int i = 0; i < count; i++) {
				double temp_dis = getDistance(node[i], {0, 0});
				if (temp_dis - 7.5 < step) {
					temp[count][i] = temp_dis;
					temp[i][count] = temp_dis;
				}
			}

			for (int i = 0; i < count; i++) {
				double distanceToLeftOrRightEdge = abs(node[i].first) - 50;
				if (distanceToLeftOrRightEdge < 0)
					distanceToLeftOrRightEdge = -distanceToLeftOrRightEdge;

				double distanceToTopOrBottomEdge = abs(node[i].second) - 50;
				if (distanceToTopOrBottomEdge < 0)
					distanceToTopOrBottomEdge = -distanceToTopOrBottomEdge;

				double distanceToClosestEdge = min(distanceToLeftOrRightEdge, distanceToTopOrBottomEdge);

				if (distanceToClosestEdge <= step) {
					temp[i][count + 1] = distanceToClosestEdge;
					temp[count + 1][i] = distanceToClosestEdge;
				}
			}
			mapForNode = temp;
		}

		void getResult() {
			queue<int> q;
			vector<bool> visited(count + 2, false);


			for (int i = 0; i < count; i++) {
				if (mapForNode[count][i] != -1) {
					q.push(i);
					visited[i] = true;
				}
			}

			bool canEscape = false;

			while (!q.empty()) {
				int curr = q.front();
				q.pop();

				if (mapForNode[curr][count + 1] != -1) {
					canEscape = true;
					break;
				}

				for (int i = 0; i < count + 2; i++) {
					if (!visited[i] && mapForNode[curr][i] != -1) {
						q.push(i);
						visited[i] = true;
					}
				}
			}

			result = canEscape;
		}
};

int main() {
	int count, step;
	vector<pair<int, int>> input;

	cin >> count >> step;

	for (int i = 0; i < count; i++) {
		pair<int, int> buffer;
		cin >> buffer.first >> buffer.second;
		input.push_back(buffer);
	}

	BFS bfs = BFS(input, count, step);
	bfs.printMinDistance();
	// bfs.traverseMap();
	bfs.printResult();
	return 0;
}