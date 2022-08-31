int sz[maxn];//表示当前树中以某节点为根的子树大小
int mxsz[maxn];//表示当前树中某节点的最大支的大小。初始化mxsz[0]=inf
int vis[maxn];//标记删除的点，禁止向其搜索，这样其各支就相当于分离了
int judge[10000007];//我们要维护的查询表。同往常一样，每次不能暴力清空
int rt,tot; //tot表示当前树的总大小。这两个量要在递归进入每个solve时重置
int n,m;

void get_root(int x,int f) //将rt更新为当前树的重心
{
    mxsz[x]=0,sz[x]=1;
    for(auto p:G[x])
    {
        int i=p.first;
        if(vis[i] || i==f) continue;
        get_root(i,x);
        mxsz[x]=max(sz[i],mxsz[x]);
        sz[x]+=sz[i];
    }
    mxsz[x]=max(mxsz[x],tot-sz[x]);
    if(mxsz[x]<mxsz[rt]) rt=x;
}

void calc(int x,int f,int mode)
{
    //...
}

void solve(int x) //与寻常分治不同，点分治是自上而下的，即先处理以本点为根的树，在递归处理其子树
{//一定要确保x是所在子树的重心
    for(auto p:G[x])
    {
        int i=p.first;
        if(vis[i]) continue;
        calc(i,x,0);//计算
        calc(i,x,1);//录入
    }
    for(auto p:G[x])
    {
        int i=p.first;
        if(vis[i]) continue;
        calc(i,x,2);//清除
    }
    vis[x]=1;
    get_root(x,0); //以x为根dfs重置sz数组（很经典的漏洞，会导致重心找错从而影响算法效率）
    for(auto p:G[x])
    {
        int i=p.first;
        if(vis[i]) continue;
        tot=sz[i]; //这里的sz[i]不会被下面的get_root影响，因为x的各个子节点在不同的连通块中
        rt=0; //这里不可取rt=i
        get_root(i,x); //将rt更新为“结点i所在的树的子图”的重心
        solve(rt);
    }
}
