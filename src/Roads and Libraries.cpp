#include <bits/stdc++.h>
#include <vector>
#include <string>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'roadsAndLibraries' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER c_lib
 *  3. INTEGER c_road
 *  4. 2D_INTEGER_ARRAY cities
 */

long long roadsAndLibraries(int n, int c_lib, int c_road, vector<vector<int>> cities) {
    if (c_road >= c_lib) {
        return (long long) n * c_lib;
    }

    long long totalCost = 0;
    vector<vector<int>> adjacencyList(n, vector<int>());

    for(int idx = 0; idx < cities.size(); ++idx) {
        int beginIdx = cities[idx][0];
        int endIdx = cities[idx][1];
        adjacencyList[beginIdx - 1].push_back(endIdx - 1);
        adjacencyList[endIdx - 1].push_back(beginIdx - 1);
    }

    vector<bool> visited (n, false);
    list<int> stack;

    for (int vertexIdx = 0; vertexIdx < n; ++vertexIdx) {
        if (!visited[vertexIdx]) {
            totalCost += (c_lib - c_road);
            stack.push_back(vertexIdx);
            while(!stack.empty()) {
                int currentIdx = stack.back();
                stack.pop_back();

                if (visited[currentIdx]) continue;
                visited[currentIdx] = true;
                totalCost += c_road;
                for (int neighbourIdx = 0; neighbourIdx < adjacencyList[currentIdx].size(); ++neighbourIdx) {
                        stack.push_back(adjacencyList[currentIdx][neighbourIdx]);
                }
            }
        }
    }

    return totalCost;
}

int main()
{
    ofstream fout("output.txt", ios::out);
    ifstream fin("input.txt", ios::in);

    string q_temp;
    getline(fin, q_temp);

    int q = stoi(ltrim(rtrim(q_temp)));

    for (int q_itr = 0; q_itr < q; q_itr++) {
        string first_multiple_input_temp;
        getline(fin, first_multiple_input_temp);

        vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

        int n = stoi(first_multiple_input[0]);

        int m = stoi(first_multiple_input[1]);

        int c_lib = stoi(first_multiple_input[2]);

        int c_road = stoi(first_multiple_input[3]);

        vector<vector<int>> cities(m);

        for (int i = 0; i < m; i++) {
            cities[i].resize(2);

            string cities_row_temp_temp;
            getline(fin, cities_row_temp_temp);

            vector<string> cities_row_temp = split(rtrim(cities_row_temp_temp));

            for (int j = 0; j < 2; j++) {
                int cities_row_item = stoi(cities_row_temp[j]);

                cities[i][j] = cities_row_item;
            }
        }

        long long result = roadsAndLibraries(n, c_lib, c_road, cities);

        fout << result << "\n";
    }

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}
