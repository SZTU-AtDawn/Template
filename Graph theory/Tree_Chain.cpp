//树链剖分
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5+5;
const long long inf=1e18;
int sz[maxn],son[maxn],fa[maxn],dep[maxn],top[maxn],l[maxn],r[maxn],tim,sa[maxn];
//sz子树大小；son重儿子；fa父节点；dep深度；top所在重链的顶端
//tim时间戳；l[x] x的dfs序时间戳；sa[k] 表示dfs中时间戳为k的节点
int ar[maxn]; //点权（题给）
int n,m,rt,mod;
struct node{
    int l,r;
    long long val,tag;
}nd[4*maxn];
vector<int> G[maxn];
void dfs1(int x,int f,int d)
{
    fa[x]=f;
    dep[x]=d;
    sz[x]=1;
    int t=0;
    for(int i:G[x])
    {
        if(i!=f)
        {
            dfs1(i,x,d+1);
            if(sz[i]>t){t=sz[i];son[x]=i;}
            sz[x]+=sz[i];
        }
    }
}
void dfs2(int x,int tp)//当前点以及当前点所在重链的顶端
{
    l[x]=++tim;//得到每个点的dfs序（新编号）
    sa[tim]=x;//记录每个新编号对应的原来的点 
    top[x]=tp;//更新每个点所在的重链的顶端 
    if(son[x]) dfs2(son[x],tp);//优先往重儿子那里走 
    for(int i:G[x])
    {
        if(i!=fa[x] && i!=son[x])
            dfs2(i,i);
    }
    r[x]=tim;
}
inline void pushup(int x)
{
    nd[x].val=nd[x<<1].val+nd[x<<1|1].val;
}
inline void pushdown(int x)
{
    nd[x<<1].val+=nd[x].tag*(nd[x<<1].r-nd[x<<1].l+1);
    nd[x<<1|1].val+=nd[x].tag*(nd[x<<1|1].r-nd[x<<1|1].l+1);
    nd[x<<1].tag+=nd[x].tag;
    nd[x<<1|1].tag+=nd[x].tag;
    nd[x].tag=0;
}
void make(int x,int l,int r)
{
    nd[x].l=l,nd[x].r=r;
    if(l==r)
    {
        nd[x].val=ar[sa[l]]; //注意这里的初始化要从位置映射回原节点
        return;
    }
    int mid=(l+r)/2;
    make(x<<1,l,mid);
    make(x<<1|1,mid+1,r);
    pushup(x);
}
void updata(int x,int l,int r,long long v)
{
    if(l<=nd[x].l&&nd[x].r<=r)
    {
        nd[x].val+=v*(nd[x].r-nd[x].l+1);
        nd[x].tag+=v;
        return;
    }
    pushdown(x);
    int mid=(nd[x].l+nd[x].r)/2;
    if(l<=mid)
        updata(x<<1,l,r,v);
    if(r>mid)
        updata(x<<1|1,l,r,v);
    pushup(x);
}
long long query(int x,int l,int r)
{
    if(l<=nd[x].l&&nd[x].r<=r)
    {
        return nd[x].val;
    }
    pushdown(x);
    long long res=0;
    int mid=(nd[x].l+nd[x].r)/2;
    if(l<=mid)
        res+=query(x<<1,l,r);
    if(r>mid)
        res+=query(x<<1|1,l,r);
    pushup(x);
    return res;
}
void add(int x,int y,int z)
{
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);//使得x所在的重链顶端比y深，并优先在x处向上跳
        updata(1,l[top[x]],l[x],z);//注意l[top[x]]和l[x]的先后次序
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])
        swap(x,y);
    updata(1,l[y],l[x],z);//注意l[y]和l[x]的先后次序
}
long long sum1(int x,int y)
{
    long long res=0;
    while(top[x]!=top[y])
    {
        if(dep[top[x]]<dep[top[y]])
            swap(x,y);
        res+=query(1,l[top[x]],l[x]);
        x=fa[top[x]];
    }
    if(dep[x]<dep[y])
        swap(x,y);
    res+=query(1,l[y],l[x]);
    return res%mod;
}
int main()
{
    cin.sync_with_stdio(false);
    cin>>n>>m>>rt>>mod;
    for(int i=1;i<=n;++i)
    {
        cin>>ar[i];
    }
    for(int i=1;i<n;++i)
    {
        int x,y;
        cin>>x>>y;
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs1(rt,0,1);
    dfs2(rt,rt);
    make(1,1,n);
    while(m--)
    {
        int p,x,y,z;
        cin>>p;
        if(p==1)
        {
            cin>>x>>y>>z;
            add(x,y,z);
        }
        else if(p==2)
        {
            cin>>x>>y;
            cout<<sum1(x,y)<<"\n";
        }
        else if(p==3)
        {
            cin>>x>>z;
            updata(1,l[x],r[x],z);
        }
        else{
            cin>>x;
            cout<<query(1,l[x],r[x])%mod<<"\n";
        }
    }
    return 0;
}
