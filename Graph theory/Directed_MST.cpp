//有向图的最小生成树 - 朱刘算法
//算法顺序：扫描前驱——搜索有向环——标记环——缩点

//G[N][N]：邻接矩阵
//pre[i]记录点i的最小入边
//w[i]记录点i的最小入边边权
double mst(int u)//指定u为树形图的根
{
    ans=0;//记录结果
    for(int i=1;i<=n;++i)
        tag[i]=0;  //tag[x]为true表示点x被移除，不再参加下列代码中的任何步骤
    while(1)
    {
        for(int i=1;i<=n;++i)
        {
            if(tag[i] || i==u) continue; //根没有入边
            pre[i]=i; w[i]=inf; 
            for(int j=1;j<=n;++j)
            {
                if(!tag[j])
                    if(G[j][i]<w[i])
                    {
                        w[i]=G[j][i];
                        pre[i]=j;
                    }
            }
            if(pre[i]==i) //如果找不到入边，则树形图不存在
            {
                return -1;
            }
        }
        /*判断一个点是否在环上？首先，如果沿着前驱能找到根，那一定不在环上；若陷入循环（设一个计数器），却又回不到自己，说明点在水母触手上；
        否则，点必在一个环上。可以观察每个点最后是因为什么退出循环的。如果所有点都没有检测到在环上，则统计结果输出。*/
        int t;
        for(t=1;t<=n;++t)
        {
            if(tag[t]) continue;
            int j=t,cnt=0;
            while(j!=u && pre[j]!=t && cnt<=n)
            {
                j=pre[j];
                ++cnt;
            }
            if(j==u || cnt>n) continue; //t不在环上
            else break;
        }
        if(t>n) //如果找不到环，统计结果并返回
        {
            for(int i=1;i<=n;++i)
            {
                if(!tag[i] && i!=u)
                    ans+=w[i];
            }
            return ans;
        }
        for(int i=1;i<=n;++i)
            vis[i]=0;
        //将t所在的环缩至点t
        int j=t;
        do{
            ans+=w[j];
            j=pre[j];
            vis[j]=tag[j]=1; //vis标记当前环（每次重置为0），tag标记所有环
        }while(j!=t);
        tag[t]=0; //我们把环缩至一个代表点，即t，记得取消它的tag标记
        //把环上的边关系转移到t上
        for(int k=1;k<=n;++k)//环外点k
        {
            if(tag[k] || vis[k]) continue;
            for(int j=1;j<=n;++j)//环内点j
            {
                if(vis[j])
                {
                    if(G[j][k]<G[t][k])
                        G[t][k]=G[j][k];
                    if(G[k][j]<inf && G[k][t]>G[k][j]-G[pre[j]][j]) //需先保证G[k][j]存在再作减法
                        G[k][t]=G[k][j]-G[pre[j]][j];
                }
            }
        }
    }
}

