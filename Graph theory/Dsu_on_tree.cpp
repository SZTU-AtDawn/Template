// 树上启发式合并

void dfs0( int u, int fa ) { //遍历整个树，找每个点的重儿子
	siz[u] = 1;
	for( int v : G[u]) {
		if( v == fa ) continue;
		dfs0( v, u );
		siz[u] += siz[v];
		if( siz[v] > siz[son[u]] )
			son[u] = v;
	}
}

int ans; //记录答案的全局变量，跟随全局数组一起重置

void calc( int u, int fa, bool flag ) {//flag=0回退 flag=1添加 
	if( flag ) {
		//统计数据
	}	
	else {
		//按原路清理数据（通常是彻底清除，直接赋0、inf或-inf）
	}
	for( int v : G[u] )
		if( v != fa ) calc( v, u, flag );
}

void dfs( int u, int fa ) { //默认不清理遗留数据
	for( int v : G[u] ) {
		if( v == fa || v == son[u] ) continue;
		dfs( v, u );//先算轻儿子的答案
		calc( v, u, 0 );//计算完轻儿子的答案后 要把儿子的痕迹擦干净 为下一个儿子准备
        ans=0;//或+-inf
		//...可能还有其他的操作
	} //以下才是启发式合并的正式开始
	if( son[u] ) dfs( son[u], u );//重儿子的贡献仍然保留 不回退
    //别忘了把u本身加入数据
    //如果重儿子遗留的ans不是我们需要的，还得重置一下
	for( int v : G[u] ) {
		if( v == fa || v == son[u] ) continue;
		else calc( v, u, 1 );//开始重新添加每个轻儿子的贡献 为后面计算自己准备
	}
	//...一堆操作，比如将ans计入res[u]，或者处理挂在u上的询问
}
