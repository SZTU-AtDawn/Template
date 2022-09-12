//求仙人掌的直径
#include <bits/stdc++.h>
using namespace std;
const int mx = 1e5 + 10;
int n,m,ans;
vector <int> g[mx];
int dp[mx<<1],dfn[mx],id[mx],sum[mx<<1];
int fa[mx],siz,st[mx],last,q[mx<<1];
void Loop(int u,int v)
{
    last = 0;
    for(int i=v;i!=fa[u];i=fa[i]) st[last++] = dp[i];
    for(int i=last;i<2*last;i++) st[i] = st[i-last];
    int lim = last>>1;
    int l = 0,r = 0;
    for(int i=0;i<2*last;i++){
        if(l!=r) ans = max(ans,st[i]+i+st[q[l]]-q[l]);
        while(l!=r&&st[i]-i>=st[q[r-1]]-q[r-1]) r--;
        q[r++] = i;
        while(l!=r&&i>=lim+q[l]) l++;  
    }
    for(int i=0;i<last;i++) dp[u] = max(dp[u],st[i]+min(i+1,last-i-1));
}
void tarjan(int u)
{
    dfn[u] = id[u] = ++siz;
    for(int v:g[u]){
        if(v==fa[u]) continue;
        if(!dfn[v]){
            fa[v] = u;
            tarjan(v);
            id[u] = min(id[u],id[v]);
        }else id[u] = min(id[u],dfn[v]);
        if(id[v]>dfn[u]){
            ans = max(ans,dp[u]+dp[v]+1);
            dp[u] = max(dp[u],dp[v]+1);
        }
    }
    for(int v:g[u]){
        if(fa[v]!=u&&dfn[v]>dfn[u])
        Loop(u,v);
    }
}
int main()
{
    scanf("%d%d",&n,&m);
    int k,x,y;
    while(m--){
        scanf("%d%d",&k,&x);
        while(--k){
            scanf("%d",&y);
            g[x].push_back(y);
            g[y].push_back(x);
            x = y;
        }
    }
    tarjan(1);
    printf("%d\n",ans);
    return 0;
} 
