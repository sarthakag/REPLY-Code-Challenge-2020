#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;
typedef long long ll;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define fastio() ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)
#define test() int t;cin>>t;for(int test=1;test<=t;test++)
#define pb push_back
#define nl cout<<"\n"
#define F first
#define S second
#define all(x) x.begin(),x.end()
template<class C> void min_self( C &a, C b ){ a = min(a,b); }
template<class C> void max_self( C &a, C b ){ a = max(a,b); }

const int MAXN = 1e5+5;
const int LOGN = 21;
const ll INF = 1e14;
int dx[] = {1,0,-1,0};
int dy[] = {0,1,0,-1};

int rows, cols, D, P;
char grid[1005][1005];
vector<pii>managers, developers;
vector<pii>devans(MAXN,{-1,-1});
vector<pii>pmans(MAXN,{-1,-1});


struct dev
{
    int bonus, num_skills;
    string company;
    vector<string>skills;
    int index;
    void read(int id)
    {
        cin>>company>>bonus>>num_skills;
        skills.resize(num_skills);
        for(int i=0;i<num_skills;i++)
            cin>>skills[i];
        index = id;
    }
};

struct pm
{
    string company;
    int bonus,index;
    void read(int id)
    {
        cin>>company>>bonus;
        index = id;
    }
};
bool devcomp(pair<dev,int>a, pair<dev,int>b)
{
    return a.first.bonus > b.first.bonus;
}
bool pmcomp(pair<pm,int>a, pair<pm,int>b)
{
    return a.first.bonus > b.first.bonus;
}
struct company
{
    vector<pair<dev,int>>devs;
    vector<pair<pm,int>>pms;
    void add_dev( dev d, int dev_no )
    {
        devs.pb({d,dev_no});
    }
    void add_pm( pm p, int pm_no )
    {
        pms.pb({p,pm_no});
    }
};
int devidx = 0, pmidx = 0;

vector<dev>devs;
vector<pm>pms;
map<string, company>comps;
map<string,company>::iterator it;

bool check(int i,int j)
{
    if(i>=0 && j>=0 && i<rows && j<cols && grid[i][j]!='#')return 1;
    return 0;
}
void dfs(int i,int j)
{
    // cout<<i<<" "<<j<<endl;
    if(grid[i][j]=='_')
    {
        while(it!=comps.end() && devidx==((it->second).devs.size()))it++,devidx = 0,pmidx = 0;
        if(it==comps.end())return;

        devans[(it->second).devs[devidx].second] = {i,j};
        devidx++;
        grid[i][j] = '#';
    }
    if(grid[i][j]=='M')
    {
        while(it!=comps.end() && pmidx==(it->second).pms.size())it++,devidx = 0,pmidx = 0;
        if(it==comps.end())return;

        pmans[it->second.pms[pmidx].first.index] = {i,j};
        pmidx++;
        grid[i][j] = '#';
    }
    for(int k = 0;k<4;k++)
    {
        int x = i+dx[k];
        int y = j+dy[k];
        if(check(x,y))dfs(x,y);
    }
}
int main() 
{
    // #ifndef ONLINE_JUDGE
    //     freopen("a_solar.txt", "r", stdin);
    //     freopen("out.txt", "w", stdout);
    // #endif
    fastio();

    cin>>cols>>rows;

    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<cols;j++)
        {
            cin>>grid[i][j];
            if( grid[i][j] == 'M' )
                managers.pb({i,j});
            if( grid[i][j] == '_' )
                developers.pb({i,j});
        }
    }

    cin>>D;
    devs.resize(D);
    devans.resize(D);
    for(int i=0;i<D;i++)
    {
        devs[i].read(i);
        comps[devs[i].company].add_dev( devs[i] , i );
    }

    cin>>P;
    pms.resize(P);
    pmans.resize(P);
    for(int i=0;i<P;i++)
    {
        pms[i].read(i);
        comps[pms[i].company].add_pm( pms[i], i );
    }
    for(auto &it:comps)
    {
        sort(it.second.devs.begin(),it.second.devs.end(),devcomp);
        sort(it.second.pms.begin(),it.second.pms.end(),pmcomp);
    }
    it = comps.begin();
    for(int i = 0;i<rows;i++)
    {
        for(int j = 0;j<cols;j++)
        {
            if(grid[i][j]!='#')
                dfs(i,j);
        }
    }

    for(auto i:devans)
    {
        if(i.first == -1)cout<<"X\n";
        else 
            cout<<i.second<<" "<<i.first<<endl;
    }
    for(auto i:pmans)
    {
        if(i.first == -1)cout<<"X\n";
        else 
            cout<<i.second<<" "<<i.first<<endl;
    }


    

    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}



