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

vector < vector <int> > g;
vector <int> in;
int n, m;

void init() {
    g.resize(n);
    for(auto &i: g) {
        i.clear();
    }
    in.resize(n);
    fill(in.begin(), in.end(), 0);
}

void add(int a, int b) {
    g[a].PB(b);
}

int main() {

    cin >> n >> m;

    init();

    for(int i = 0; i < m; i++) {
        int p, q;
        cin >> p >> q;
        add(p, q);
        in[q]++;
    }

    queue <int> q;
    vector <int> seq;
    // priority_queue<int,vector<int>,greater<int>>q;
    // 优先队列的话，会按照数值大小有顺序的输出
    // 此处为了理解，暂时就用简单队列
    for(int i = 0; i < n;i++) {
        if(in[i] == 0) {
            q.push(i);
        }
    }

    int temp;
    while(!q.empty()) {
        temp = q.front(); // 如果是优先队列，这里可以是top()
        cout << temp << ' ';
        seq.PB(temp);
        q.pop();
        for(auto i : g[temp]) {
            in[i]--;
            if(in[i] == 0) {
                q.push(i);
            }
        }
    } cout << endl;
    return 0;
}
