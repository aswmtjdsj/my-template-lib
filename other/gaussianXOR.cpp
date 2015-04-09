/* base IO */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <fstream>
#include <sstream>

/* data structure */
#include <vector>
#include <string>
#include <set>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <queue>
#include <stack>
#include <bitset>

/* alrotihm and math */
#include <algorithm>
#include <random>
#include <cmath>

/* run-time */
#include <cstdlib>
#include <ctime>
#include <climits>

/* system dependent */
#include <sys/time.h>

using namespace std;

#define VI vector<int>
#define VD vector<double>
#define PII pair<int, int>
#define PDD pair<double, double>
#define PB push_back
#define MP make_pair
#define len(x) ((x).size())

const int inf = INT_MAX;
const long long inf_ll = 0x7f7f7f7f;
const double eps = 1e-8;

/*
 * 0 1 2
 * 3   4
 * 5 6 7
 */
const int bfs_dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int bfs_dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};

/*
 *   3  
 * 2   0
 *   1  
 */
const int dfs_dy[] = {0, 1, 0, -1};
const int dfs_dx[] = {1, 0, -1, 0};

PII dir[] = {make_pair(0,1),make_pair(1,0),make_pair(0,-1),make_pair(-1,0)};
/* TC HEADER END */

int n, m, k;
const int M = 20 * 20 + 5;
int a[M][M], b[M];

int gauss() {
    int res = 0, r = 0;
    memset(l, 0, sizeof(bool) * n);
    for(int i = 0; i < m; i++){ // column dominated
        /*for(int k = 0; k < n; k++) {
            for(int j = 0; j < m; j++) {
                cout << a[k][j] << ' ';
            } cout << "| " << a[k][m] << endl;
        }
        cout << "------" << endl;*/
        for(int j = r; j < n; j++) {
            if(a[j][i] == 1){
                for(int k = i; k <= m; k++) {
                    swap(a[j][k], a[r][k]);
                }
                break;
            }
        }
        if(a[r][i] == 0){
            if(a[r][m] != 0) {
                return -1;//no solution
            }
            else{
                // free varbiable
                ++res;
                continue;
            }
        }
        for(int j = 0; j < n; j++){
            if(j != r && a[j][i] == 1){
                for(int k = i; k <= m; ++k) {
                    a[j][k] ^= a[r][k];
                }
            }
        }
        r++;
        //cout << "i: " << i << endl;
    }
    /*for(int k = 0; k < n; k++) {
        for(int j = 0; j < m; j++) {
            cout << a[k][j] << ' ';
        } cout << "| " << a[k][m] << endl;
    }*/
    return res;
}

int main() {
}
