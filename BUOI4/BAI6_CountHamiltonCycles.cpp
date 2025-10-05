#include <iostream>
#include <vector>
#include <deque>
using namespace std;

#define FI "COUNT_HAMCYC.INP"
#define FO "COUNT_HAMCYC.OUT"

int n;
vector<vector<int>> mtke;

vector<int> cycC;
vector<int> usedC;
long long cntC;

void dfs_count(int k){
    if(k==n){
        if(mtke[cycC[n-1]][cycC[0]] > 0) ++cntC;
        return;
    }
    for(int v=2; v<=n; ++v){ // cố định 1 ở đầu để tránh hoán vị vòng
        if(!usedC[v] && mtke[cycC[k-1]][v] > 0){
            usedC[v]=1; cycC[k]=v;
            dfs_count(k+1);
            usedC[v]=0;
        }
    }
}

long long count_cycles(){
    cycC.assign(n,0);
    usedC.assign(n+1,0);
    cntC = 0;
    cycC[0]=1; usedC[1]=1;
    dfs_count(1);
    return cntC / 2; // loại trùng do đảo hướng
}

void solve(){
    cin >> n;
    mtke.assign(n+1, vector<int>(n+1,0));
    for(int i=1;i<=n;++i)
        for(int j=1;j<=n;++j)
            cin >> mtke[i][j];

    cout << count_cycles() << "\n";
}

int main(){
    freopen(FI,"rt",stdin);
    freopen(FO,"wt",stdout);
    solve();
    return 0;
}
