SPOJ submission 19744688 (C++ 4.3.2) plaintext list. Status: AC, problem LUBENICA, contest SPOJVN. By lahoangphong (LHPhong), 2017-07-06 15:14:38.
/* <3 <3 <3 */
#include <bits/stdc++.h>
 
using namespace std;
 
#define ii pair <int,int>
#define iii pair <ii,int>
#define fi first
#define se second
#define ll long long
#define ull unsigned long long
#define pb push_back
 
const int HashMod=1125022017;
const int dx[4]={0,1,0,-1};
const int dy[4]={1,0,-1,0};
const int oo = 1e9;
const int nmax=1e5+9;
 
vector < ii > v[nmax];
int nchild[nmax];
int depth[nmax];
int chain[nmax];
int lab[nmax];
int HLD[nmax];
int value[nmax];
int pos[nmax];
int ITMi[nmax*4];
int ITMa[nmax*4];
 
int n,m;
int q;
 
void Inp()
{
    cin >> n;
    for (int i=1;i<n;i++)
    {
        int x,y,w;
        cin >> x >> y >> w;
        v[x].pb(ii(y,w));
        v[y].pb(ii(x,w));
    }
}
 
int Dfs(int u)
{
    int t=0;
    int ma=-1;
    for (int i=0;i<v[u].size();i++)
    {
        int e=v[u][i].fi;
        if (e==lab[u])
        {
            value[u]=v[u][i].se;
            continue;
        }
        lab[e]=u;
        depth[e]=depth[u]+1;
        t+=Dfs(e);
        if (ma==-1 || nchild[v[u][ma].fi]<nchild[e])
            ma=i;
    }
    if (ma!=-1)
        swap(v[u][0],v[u][ma]);
    return nchild[u]=t+1;
}
 
void HLD_(int u,int c)
{
    m+=1;
    HLD[m]=u;
    pos[u]=m;
    chain[u]=c;
    if (v[u][0].fi!=lab[u])
        HLD_(v[u][0].fi,c);
    for (int i=1;i<v[u].size();i++)
    {
        int e=v[u][i].fi;
        if (e==lab[u])
            continue;
        HLD_(e,e);
    }
}
void Build_HLD()
{
    lab[1]=1;
    m=0;
    value[1]=oo;
    Dfs(1);
    HLD_(1,1);
}
 
void Build_IT(int id,int l,int r)
{
    //cout << id << " " << l << " "  <<r << endl;
    if (l>r)
        return;
    if (l==r)
    {
        ITMi[id]=value[HLD[l]];
        ITMa[id]=ITMi[id];
        return;
    }
    int mid = (l+r)/2;
    Build_IT(id*2,l,mid);
    Build_IT(id*2+1,mid+1,r);
    ITMi[id]= min(ITMi[id*2],ITMi[id*2+1]);
    ITMa[id]= max(ITMa[id*2],ITMa[id*2+1]);
    return ;
}
 
int Query_ITMi(int id,int l,int r,int L,int R)
{
    if (l>R || r<L)
        return oo;
    if (l>=L && r<=R)
        return ITMi[id];
    int mid = (l+r)/2;
    return min(Query_ITMi(id*2,l,mid,L,R),Query_ITMi(id*2+1,mid+1,r,L,R));
}
int Query_ITMa(int id,int l,int r,int L,int R)
{
    if (l>R || r<L)
        return 0;
    if (l>=L && r<=R)
        return ITMa[id];
    int mid = (l+r)/2;
    return max(Query_ITMa(id*2,l,mid,L,R),Query_ITMa(id*2+1,mid+1,r,L,R));
}
ii Query(int x,int y)
{
    if (x==y)
        return (ii(0,0));
    //cout << x << " " << y <<  " ";
    int lca;
    int mi=oo;
    int ma=0;
    int xx=x;
    int yy=y;
    ii res;
    while (chain[x]!=chain[y])
    {
        if (depth[chain[x]]>depth[chain[y]])
        {
            mi=min(mi,Query_ITMi(1,1,n,pos[chain[x]],pos[x]));
            ma=max(ma,Query_ITMa(1,1,n,pos[chain[x]],pos[x]));
            x=lab[chain[x]];
        }
        else
        {
            mi=min(mi,Query_ITMi(1,1,n,pos[chain[y]],pos[y]));
            ma=max(ma,Query_ITMa(1,1,n,pos[chain[y]],pos[y]));
            y=lab[chain[y]];
        }
    }
    if (depth[x]>depth[y])
    {
        lca=y;
        mi=min(mi,Query_ITMi(1,1,n,pos[y]+1,pos[x]));
        ma=max(ma,Query_ITMa(1,1,n,pos[y]+1,pos[x]));
    }
    else
    {
        lca=x;
        ma=max(ma,Query_ITMa(1,1,n,pos[x]+1,pos[y]));
        mi=min(mi,Query_ITMi(1,1,n,pos[x]+1,pos[y]));
    }
    return ii(mi,ma);
}
void Out()
{
    cin >> q;
    for (int i=1;i<=q;i++)
    {
        int x,y;
        cin >> x >> y;
        ii ans = Query(x,y);
        cout << ans.fi << " " << ans.se << endl;
    }
}
 
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    //freopen("Test.inp","r",stdin);
    //freopen("Test.out","w",stdout);
    Inp();
    Build_HLD();
    Build_IT(1,1,n);
    Out();
    return 0;
}
 
