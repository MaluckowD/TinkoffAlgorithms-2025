#include <iostream>
#include <vector>
using namespace std;

class CoinCombinationFinder {
private:
    int target_amount;
    int coin_types_count;
    vector<int> coin_values;
    long long total_max_possible;
    vector<int> current_combination;
    vector<int> best_combination;

    void searchCombinations(int position = 0, long long current_sum = 0) {
        if (position == coin_types_count) {
            if (current_sum == target_amount) {
                if (best_combination.empty() || current_combination.size() < best_combination.size()) {
                    best_combination = current_combination;
                }
            }
            return;
        }

        searchCombinations(position + 1, current_sum);

        current_combination.push_back(coin_values[position]);
        searchCombinations(position + 1, current_sum + coin_values[position]);

        current_combination.push_back(coin_values[position]);
        searchCombinations(position + 1, current_sum + 2 * coin_values[position]);

        current_combination.pop_back();
        current_combination.pop_back();
    }

public:
    void readInput() {
        cin >> target_amount >> coin_types_count;
        coin_values.resize(coin_types_count);
        total_max_possible = 0;

        for (int i = 0; i < coin_types_count; i++) {
            cin >> coin_values[i];
            total_max_possible += 2 * coin_values[i];
        }
    }

    void findSolution() {
        if (total_max_possible < target_amount) {
            cout << -1 << "\n";
            return;
        }

        searchCombinations();

        if (best_combination.empty()) {
            cout << 0 << "\n";
        } else {
            cout << best_combination.size() << "\n";
            for (int coin : best_combination) {
                cout << coin << " ";
            }
            cout << "\n";
        }
    }
};

int main() {
    CoinCombinationFinder finder;
    finder.readInput();
    finder.findSolution();
    return 0;
}