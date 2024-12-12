#include<bits/stdc++.h>
#define i64 long long
#define maxn 500050
#define N 100050
typedef std::pair<i64,i64> PII;
std::vector<PII>G[maxn];
/*-------------------------------------------------------------------------------------
一、求树的基础属性：树的深度、树的子树结点个数、树的距根结点的异或值

1、树的深度：数组需求：dis[maxn]
dfs，然后先进行迭代再递归dfs(v,u)，因为这是自上而下。

2、树的子树结点个数：数组需求：siz[maxn]
需要初始化为1，因为自己算一个。
先递归求dfs(v,u)，再求siz数组，因为这是自下而上。

3、树的距根结点的异或值之和：数组需求：s[maxn]
先进行迭代，再递归，因为这是自上而下。

最后一个是结合深度与个数的结合版。
---------------------------------------------------------------------------------------*/
i64 dis[maxn];
void dfs(int u,int fa)
{
	for(auto ve:G[u])
	{
		i64 v=ve.first,w=ve.second;
		if(v==fa)continue;
		dis[v]=dis[u]+w;
		if(dis[v]>dis[far])far=v;
		dfs(v,u);
	}
}

i64 siz[maxn]; // dp数组，sz[v] = 子树v的大小
void dfs(int v)
{
	siz[v] = 1; // 初始化，最初大小为1，后面累加
	for(int u: G[v]) // 遍历子结点
	{
		dfs(u); // 先对子结点进行dfs
		siz[v] += siz[u]; // 更新当前子树的大小
	}
}

i64 s[maxn];
void dfs(i64 u,i64 fa)
{
    for(auto ve:G[u])
    {
        i64 v=ve.first,w=ve.second;
        if(v.first==fa)continue;
        //从根结点向下，自上而下。
        s[v]=s[u]^w.
        dfs(v,u);
        //s[u]=s[v]^w.这叫自下而上。
    }
}

//预处理dfs求出深度dep数组
//这就是结合了。
void dfs(int u,int fa)
{
	sz[u]=1;
	//深度求法。
	dep[u]=dep[fa]+1;
	for(auto v:G[u])
	{
		if(v==fa)continue;
		dfs(v,u);
		//点的个数求法。
		sz[u]+=sz[v];
	}
}

/*-------------------------------------------------------------------------------------
二、求树的DFN序，化树为线：
in和ou分别是入序和出序的时间序，子树就相当于在线性的这个范围[in[x],ou[x]]
dfn序代表的是时间序对应的结点名称。
dfn 数组在这段代码中用于记录深度优先搜索（DFS）的访问顺序，也称为 DFS 序列或时间戳。
	 1
   /   \
  2     3
 / \   /
4   5 6
在 DFS 过程中，节点的访问顺序可能是：1 -> 2 -> 4 -> 5 -> 3 -> 6。

对应的 dfn 数组将会是：dfn = [1, 2, 4, 5, 3, 6]。

通过 dfn 数组，我们可以知道每个节点在 DFS 序列中的位置。这在某些算法中非常有用，例如树链剖分、LCA（最近公共祖先）等。

总结一下，dfn 数组的作用是：

1、记录 DFS 的访问顺序（时间戳）。
2、将节点按照 DFS 序列的顺序存储在数组中。
3、可以通过 dfn 数组快速获取节点在 DFS 序列中的位置。
---------------------------------------------------------------------------------------*/


int in[N],ou[N],dfn[N],tim,x,n;
std::vector<int>G[N];

void dfs(int u,int fa)
{
    in[u]=++tim;
    dfn[tim]=u;
    for(auto v:G[u])
    {
        if(v==fa)continue;
        dfs(v,u);
    }
    ou[u]=tim;
}

std::cin>>n;
for(int i=2;i<=n;i++)
{
    //构图：
    std::cin>>x;
    G[x].push_back(i);
    G[i].push_back(x);
}
for(int i=1;i<=n;i++)
{
    std::cin>>a[i];
}
dfs(1,0);

/*-----------------------------------------------------------------------------------------------------
三、求树的结点到达直径两端点的距离：
首先，我们很会求树的直径，所以我们可以很快捷方便的求出两个端点，靠dfs与far即可求出两个端点A,B
有了A，B，我们就可以求两次dfs，得到数组dis[N],dis2[N]。这样就赢了。
----------------------------------------------------------------------------------------------------------*/
//求深度自上而下。
int far=0;
void dfs(int u,int fa)
{
    for(auto v:G[u])
    {
        if(v==fa)continue;
        dis[v]=dis[u]+1;
        if(dis[far]<dis[v])
        {
            far=v;//最远的点。
        }
        dfs(v,u);
    }
};
void dfs2(int u,int fa)
{
    for(auto v:G[u])
    {
        if(v==fa)continue;
        dis2[v]=dis2[u]+1;
        dfs2(v,u);
    }
};

/*-----------------------------------------------------------------------------------------------------
四、求根结点到每一个点的异或值
自上而下。
----------------------------------------------------------------------------------------------------------*/
std::vector<std::vector<PII>>G(n + 1);
for(int i = 1;i < n;i ++)
{
    int x, y, z;
    std::cin >> x >> y >> z;
    G[x].emplace_back(y, z);
    G[y].emplace_back(x, z);
}

std::vector<int>dis(n + 1, 0);
// 处理根结点到每个点的距离，这其实是个套路了，要记住。
auto dfs = [&](auto self, int u, int fa) -> void
{
    for(auto [v, w] : G[u])
    {
        if(v == fa)
            continue ;
        dis[v] = dis[u] ^ w;
        self(self, v, u);
    }
};

dfs(dfs, 1, 0);
