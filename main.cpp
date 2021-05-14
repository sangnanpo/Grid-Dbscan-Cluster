#include <set> 
#include <ctime>
#include <iostream>

using namespace std;

int find_neighbor(int query, int rows, int cols, set<int>& setIn, set<int>& neiOut) {
    int row_i = query / cols;
    int col_j = query % cols;
    int row_num = 0;
    int col_num = 0;
    int num = 0;
    for (int ii = row_i - 1; (++row_num <= 3) && (ii >= -1) && (ii < rows); ++ii) {
        if (ii == -1) continue;
        col_num = 0;
        for (int jj = col_j - 1; ++col_num <= 3; ++jj) {
            if (jj < 0)
                jj += cols;
            if (jj >= cols)
                jj -= cols;
            if (setIn.find(ii * cols + jj) != setIn.end()) {
                if (neiOut.find(ii * cols + jj) == neiOut.end()) {
                    neiOut.insert(ii * cols + jj);
                    ++num;
                }
                    
            }
        }
    }
    return num;
}

void cluster_one(int query, int rows, int cols, set<int>& setIn, set<int>& temp, set<int>& cluOut) {
    int Ptnew;
    int cluster = 0;
    Ptnew = find_neighbor(query, rows, cols, setIn, temp);  // 先放入temp中
    // if (Ptnew == 0) return ++cluster;
    int next;
    while (1)
    {
        if (Ptnew == 0) break;
        auto it = temp.begin();
        next = *it;
        if (next == 0) break;
        temp.erase(next);   // 这里每删一个，cluout就要insert一个
        cluOut.insert(next);
        setIn.erase(next); 
        cluster_one(next, rows, cols, setIn, temp, cluOut);
    }
}

int main(int argc, char** argv) {
    
    set<int> test = {2, 3, 4, 13, 23, 35, 36, 46, 45, 55, 54, 63, 77, 78, 88, 89, 80, 90};
    set<int> cluster;
    set<int> temp;
    int clusterID = 0;
    	// 'advance' the iterator random times
    while(test.size() != 0) {
        auto ite = test.begin();
        srand(time(0));
        advance(ite, rand() % test.size());
        cluster_one(*ite, 10, 10, test, temp, cluster);
        cout << "cluster:" << ++clusterID << endl;
        for (auto it = cluster.begin(); it != cluster.end(); ++it) {
            cout << *it << "\t";
        }
        temp.clear();
        cluster.clear();
        cout << "\n\n";
    }
    return 0;
}
