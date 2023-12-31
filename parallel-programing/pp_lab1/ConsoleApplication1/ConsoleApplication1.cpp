#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <numeric>

using namespace std;

class Task {

private:
	int n_;
	vector<int> perst;
	default_random_engine generator_;

public:
	Task(int n) : n_(n) {
		for (int i = 1; i <= n_; i++) {
			perst.push_back(i);
		}
		random_device rd;
		generator_ = default_random_engine(rd());
	}

	vector<int> operator()() {
		shuffle(perst.begin(), perst.end(), generator_);
		return perst;
	}

};

int main() {
	int n = 5;
	int num_permutations = 100; 

	Task task(n);
	vector<int> cycle_lengths;

	for (int i = 0; i < num_permutations; i++) {
		vector<int> permutation = task();
		vector<bool> visited(n, false);
		int cycles = 0;

		for (int j = 0; j < n; j++) {
			if (!visited[j]) {
				int k = j;
				while (!visited[k]) {
					visited[k] = true;
					k = permutation[k] - 1;
				}
				cycles++;
			}
		}

		cycle_lengths.push_back(cycles);
	}


	double average_cycles = accumulate(cycle_lengths.begin(), cycle_lengths.end(), 0.0) / num_permutations;
	cout << "Avarage count cicle: " << average_cycles << endl;


	double average_cycle_length = static_cast<double>(n) / average_cycles;
	cout << "Avarale long cicle: " << average_cycle_length << endl;


	sort(cycle_lengths.begin(), cycle_lengths.end());
	int median = cycle_lengths[num_permutations / 2];
	cout << "Mediana: " << median << endl;

	return 0;
}
