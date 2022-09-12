//可撤销并查集

struct DSU{ 
    int fa[N],rk[N];//rk[x]表示x的秩
    struct edge{
        int x,y,w; //w记录秩是否改变
    }st[N];//回退栈
    int up;
    void init()
    {
        up=0;
        for(int i=1;i<N;++i) fa[i]=i,rk[i]=1;
    }
    int find(int x)
    {
        if(x==fa[x])return x;
        return find(fa[x]);
    }
    void join(int x,int y)
    {
        int a=find(x),b=find(y);
        if(a!=b)
        {
            if(rk[a]>rk[b])
                swap(a,b);
            if(rk[a]==rk[b]) ++rk[b];
            fa[a]=b;
            st[++up]={a,b,rk[a]==rk[b]};
        }
        else
            st[++up]={0,0,0}; //即便无连接，也别忘了这一步
    }
    int withdraw() //如果撤回的是无效边，返回1
    {
        auto p=st[up--];
        if(p.x)
        {
            fa[p.x]=p.x;
            rk[p.y]-=p.w;
            return 0;
        }
    }
};
