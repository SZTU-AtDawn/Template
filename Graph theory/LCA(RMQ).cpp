//O(1)求LCA——欧拉环游序+ST表
int dfn[maxn],sa[2*maxn],st[22][maxn*2],bin[32],tim;
void dfs(int x,int f,int d)
{
	sa[++tim]=x; //生成欧拉环游序
	dfn[x]=tim; //时间戳（每个节点在欧拉环游序中第一次出现的位置）
	int n=G[x].size();
	for(auto p:G[x])
	{
        int i=p.first;
		if(i!=f)
		{
			dfs(i,x,d+p.second);
			sa[++tim]=x;
		}
	}
}
void init() //预处理ST表
{
	bin[0]=1;
	for(int i=1;i<30;++i)
		bin[i]=bin[i-1]*2;
	for(int i=1;i<=cnt;++i)
		st[0][i]=dfn[sa[i]];
	for(int i=1;i<=22;++i)
	{
		for(int j=0;j+bin[i]<=cnt;++j)
		{
			st[i][j]=min(st[i-1][j],st[i-1][j+bin[i-1]]);
		}
	}
}
inline int lca(int x,int y)
{
	int a=dfn[x],b=dfn[y];
	if(a>b)
		swap(a,b);  //序列区间[a,b]中最小的时间戳，其对应位置的序列元素，就是x,y的lca
	int t=log2(b-a+1);
	return sa[min(st[t][a],st[t][b-bin[t]+1])];
}
