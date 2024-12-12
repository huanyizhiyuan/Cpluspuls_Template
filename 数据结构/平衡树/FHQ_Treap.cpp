/*-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
ƽ�������������ǲ���FHQ_treap
FHQ���ѡ�
��һ�������ǰ�ֵ���ѣ��ڶ��������ǰ����������ѡ�
1��std::mt19937 sj(114514);
������������

2��int add(int v)
�½�����㡣

3��void pushup(int u)
�����߶����У���Ҫ���Ӧ��Ĳ�����
�������������Ĳ�����

4��void split(int u,int v,int &x,int &y)+int merge(int x,int y)
���Ĳ�����
* ���԰�ֵ���ѡ�
* ���԰��������ѡ�
���ݷ��ѵķ�ʽ��ͬ���õ��Ľ�������������Ҳ��ͬ��

����Ҳ���ǰ���ƽ�����ķ�ʽ���ѣ����忴��ȸƽ̨��

5�������������Щ����������Ҫ�Լ�д�ģ��Լ�����ġ�
insert erase kth find_rank, find_pre find_nxt
-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define maxn 500050
#define pb push_back
#define int i64
//using namespace std;
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const int INF=2e16+5;
const i64 N=1e6+1e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;

//ę́19937
std::mt19937 sj(114514);
//����ǿ
struct FHQ
{
    int L,R,key,sz,val;
}fhq[N];
int root,T1,T2,T3,ck;
struct FHQ_treap
{
    #define ls fhq[u].L
    #define rs fhq[u].R
    //�½���㡣
    int add(int v)
    {
        fhq[++ck]={0,0,(int)sj(),1,v};
        return ck;
    }
    //���Ӧ�䣬���ܻ���fa,sum֮��ġ�
    void pushup(int u)
    {
        fhq[u].sz=fhq[ls].sz+fhq[rs].sz+1;
    }

    //u�ǵ�ǰfhq-treap�ĸ�
    void split(int u,int v,int &x,int &y)
    {
        // &x �� &y�ֱ���fhq-treap���Ѻ�õ�������fhq-treap�ĸ���������ָ��(����)�ķ�ʽ�����ڴ���ֵ
        if(!u)//����ýڵ�Ϊ����������ѳɵ�����������ҲӦΪ��
        {
            x=y=0;
            return ;
        }
        // �����ǰ�ڵ��valֵ����v����֤���ýڵ�������������е�valֵҲ����v
        if(fhq[u].val > v)
        {
            //�øýڵ��Ϊ�����Ľڵ�
            y=u;
            //�����ݹ���뵱ǰ�ڵ��������
            split(ls,v,x,ls);
        }
        // �����ǰ�ڵ��valֵС�ڵ���v����֤���ýڵ�������������е�valֵҲС�ڵ���v
        else
        {
            //�øýڵ��Ϊ�����Ľڵ�
            x=u;
            //�����ݹ���뵱ǰ�ڵ��������
            split(rs,v,rs,y);
        }
        //һ��Ҫ�ǵ�push_up����Ϊpos�������������С�����˸ı䣬����ᵼ����Ϣ����
        pushup(u);
    }
    //������õ�key
    //�������������ĸ��ڵ�
    int merge(int x,int y)
    {
        //����п���
        if(!x || !y)
            return x+y;//ֱ�ӷ��طǿ���(���X�m������д��x|y��ͬ��x+y,������װ����)
        if(fhq[x].key > fhq[y].key)
        {
            //��������ϵ�ǰ�ڵ��valֵ���������ϵ�ǰ�ڵ��valֵ
            //��l��Ϊ�ϲ������fhq-treap�ĸ��ڵ�
            fhq[x].R = merge(fhq[x].R, y);//�����ݹ�ȷ��l���������ý�˭
            pushup(x);//һ���ǵ��ϴ�
            return x;//�����µõ��ĸ��ڵ�
        }
        else
        {
            fhq[y].L = merge(x,fhq[y].L);
            pushup(y);
            return y;
        }
    }

    //����ɾ����
    void insert(int v)
    {
        split(root,v,T1,T2);
        root = merge(merge(T1,add(v)),T2);
    }
    void erase(int x)
    {
        split(root,x,T1,T2);
        split(T1,x-1,T1,T3);
        T3=merge(fhq[T3].L,fhq[T3].R);
        root = merge(merge(T1,T3),T2);
    }

    //�ҳ�С�ڵ���x-1�ĸ�����
    int find_rank(int x)
    {
        split(root,x-1,T1,T2);
        int res = fhq[T1].sz+1;
        root = merge(T1,T2);
        return res;
    }
    //�ҵ���kС��
    int kth(int k)
    {
        int u =root;
        while(u)
        {
            int tmp = fhq[ls].sz+1;
            if(tmp == k)
                break;
            else if(k<tmp)
                u=ls;
            //���ȥ�������������ݡ�
            else
                k-=tmp,u = rs;
        }
        return fhq[u].val;
    }

    int find_pre(int u,int v)
    {
        if(u==0)return -INF;
        if(fhq[u].val < v)
        {
            int res = find_pre(rs,v);
            return res==-INF?fhq[u].val:res;
        }
        else
            return find_pre(ls,v);
    }

    int find_nxt(int u,int v)
    {
        if(u==0)return INF;
        if(fhq[u].val>v)
        {
            int res = find_nxt(ls,v);
            return res == INF?fhq[u].val:res;
        }
        else
            return find_nxt(rs,v);
    }

    // int find_pre2(int x)
    // {
    //     split(root,x-1,T1,T2);
    //     int u=T1;
    //     while(rs)u=rs;
    //     root=merge(T1,T2);
    //     return fhq[u].val;
    // }

    // int find_nxt2(int x)
    // {
    //     split(root,x,T1,T2);
    //     int u=T2;
    //     while(ls)u=ls;
    //     root=merge(T1,T2);
    //     return fhq[u].val;
    // }
    #undef ls
    #undef rs
}Treap;

void solve()
{
    int op,x;
    std::cin>>n>>m;
    for(int i=1;i<=n;i++)
    {
        std::cin>>x;
        Treap.insert(x);
    }
    int ans=0,res=0;
    while(m--)
    {
        std::cin>>op>>x;
        // if(op>2)
            x^=res;
        if(op==1)
            Treap.insert(x);
        else if(op==2)
            Treap.erase(x);
        else if(op==3)
            res=Treap.find_rank(x);
        else if(op==4)
            res=Treap.kth(x);
        else if(op==5)
            res=Treap.find_pre(root,x);
        else
            res=Treap.find_nxt(root,x);
        // std::cout<<res<<"\n";
        if(op>2)
            ans^=res;
    }
    std::cout<<ans<<"\n";
}

signed main()
{
#ifndef ONLINE_JUDGE
	// freopen("title.in","r",stdin);
	// freopen("title.out","w",stdout);
#endif

    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    // std::cin>>T;
    while(T--)
    {
        solve();
    }
    return  0;
}
/*-------------------------------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------------------------------------*/

