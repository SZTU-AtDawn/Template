//边双连通分量缩点
//链式前向星存原图，邻接表存缩点图
vector<int> G[maxn];
int to[M],hd[maxn],nt[M],e;
int dfn[maxn],low[maxn],tim;
int id[maxn],cnt,bridge[M],ans; //id[x]表示x所在的缩点号，bridge[i]标记i号边是否为桥
int fa[maxn],dt[maxn]; 
inline void add(int x,int y){ to[e]=y;nt[e]=hd[x];hd[x]=e++;}
void tarjan(int x,int ind)
{
    dfn[x]=low[x]=++tim;
    for(int k=hd[x];k;k=nt[k])
    {   
        int i=to[k];
        if(!dfn[i])
        {
            tarjan(i,k);
            low[x]=min(low[x],low[i]);
            if(low[i]>dfn[x])
            {
                bridge[k]=bridge[k^1]=1; //链式前向星中无向边的来回两边编号相邻，若以偶数为第一个边编号，则相邻编号的异或值为1，比如0^1,2^3。
                ++ans;
            }
        }
        else if(k!=(ind^1)) //如果与上一步不是同一条无向边（因为要考虑到两条边可能连接同一对点）
            low[x]=min(low[x],dfn[i]);
    }
}
void dfs0(int x,int f) //建树
{
    id[x]=cnt;
    for(int k=hd[x];k;k=nt[k])
    {   
        int i=to[k];
        if(i!=f)
        {
            if(!bridge[k] && !id[i]) //如果是不是桥且未访问
                dfs0(i,x);
            else if(bridge[k] && id[i]) //如果是桥且已编号（避免对同一条无向边建两次）
            {
                G[cnt].push_back(id[i]);
                G[id[i]].push_back(cnt);
            }
        }
    }
}
void dfs(int x,int f,int d)//初始化fa和dt数组
{
    fa[x]=f;
    dt[x]=d; //深度
    for(int i:G[x])
        if(i!=f)
            dfs(i,x,d+1);
}
int main()
{
    cin.sync_with_stdio(false);
    int n,m;
    while(cin>>n>>m)
    {
        if(n==0 && m==0) return 0;
        for(int i=0;i<=e;++i) //一定要注意bridge是来标记边编号的，其总数不止maxn
            bridge[i]=0;
        cnt=tim=ans=0;
        e=2; //从偶数开始计边的编号
        for(int i=0;i<=n;++i)
        {
            G[i].clear();
            hd[i]=0;
            id[i]=0;
            low[i]=dfn[i]=0; //别忘了对这两个量初始化
        }
        for(int i=1;i<=m;++i)
        {
            int x,y;
            cin>>x>>y;
            add(x,y); add(y,x);
        }
        for(int i=1;i<=n;++i) //如果是无向连通图，只需一次tarjan
            if(!dfn[i])
                tarjan(i,0);
        for(int i=1;i<=n;++i)
        {
            if(!id[i])
            {
                ++cnt;
                dfs0(i,0);
            }
        }
        dfs(1,0,1); 
}
