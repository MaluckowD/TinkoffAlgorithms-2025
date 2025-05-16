#include <iostream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX;

class StringCompressor {
private:
    string input;
    vector<vector<int>> dp;
    int length;

    int countDigits(int number) {
        if (number == 0) return 1;
        int count = 0;
        while (number > 0) {
            number /= 10;
            count++;
        }
        return count;
    }

    bool isRepeatingPattern(int start, int end, int patternLen) {
        for (int i = start; i < start + patternLen; i++) {
            for (int j = i + patternLen; j <= end; j += patternLen) {
                if (input[i] != input[j]) {
                    return false;
                }
            }
        }
        return true;
    }

    string reconstruct(int start, int end) {
        if (start == end) {
            return string(1, input[start]);
        }

        int totalLen = end - start + 1;
        
        for (int patternLen = 1; patternLen <= totalLen / 2; patternLen++) {
            if (totalLen % patternLen != 0) continue;
            
            if (isRepeatingPattern(start, end, patternLen)) {
                int compressedLen = countDigits(totalLen / patternLen) + 2 + dp[start][start + patternLen - 1];
                if (compressedLen == dp[start][end]) {
                    string pattern = reconstruct(start, start + patternLen - 1);
                    return to_string(totalLen / patternLen) + "(" + pattern + ")";
                }
            }
        }

        for (int mid = start; mid < end; mid++) {
            if (dp[start][mid] + dp[mid + 1][end] == dp[start][end]) {
                return reconstruct(start, mid) + reconstruct(mid + 1, end);
            }
        }

        return "";
    }

public:
    void readInput() {
        cin >> input;
        length = input.size();
        dp.resize(length, vector<int>(length, 0));
    }

    void computeCompression() {
        for (int len = 0; len < length; len++) {
            for (int i = 0; i + len < length; i++) {
                int j = i + len;
                
                if (len == 0) {
                    dp[i][j] = 1;
                    continue;
                }

                int minCompression = INF;
                int currentLen = j - i + 1;

                for (int patternLen = 1; patternLen <= currentLen / 2; patternLen++) {
                    if (currentLen % patternLen != 0) continue;
                    
                    if (isRepeatingPattern(i, j, patternLen)) {
                        int compressionSize = countDigits(currentLen / patternLen) + 2 + dp[i][i + patternLen - 1];
                        minCompression = min(minCompression, compressionSize);
                    }
                }

                for (int mid = i; mid < j; mid++) {
                    minCompression = min(minCompression, dp[i][mid] + dp[mid + 1][j]);
                }

                dp[i][j] = minCompression;
            }
        }
    }

    void printResult() {
        string result = reconstruct(0, length - 1);
        cout << result << endl;
    }
};

int main() {
    StringCompressor compressor;
    compressor.readInput();
    compressor.computeCompression();
    compressor.printResult();
    return 0;
}