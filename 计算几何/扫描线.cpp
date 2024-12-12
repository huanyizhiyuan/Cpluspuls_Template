/*--------------------------------------------------------------------------------------------------------------------------------------------------
ɨ����ģ�棺
������߶�����ͬ�ı������R+1������֮����ʹ��R+1����Ϊ����������߶�����ʾ������ǡ��߶Ρ������Ե���Ҷ�ӽ��һ������û�У���������������߶Σ��������ǲ���[L,R)��������ʾ�ľ����߶Σ�
���²��裺
�� ��ɢ��ȥ�غ����꣬������
�� ���ݸ߶��������ж�ά���
�� ����1~n-1���߶������£�����������ans
����1���������ɨ���ߡ�
--------------------------------------------------------------------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define maxn 500050
#define pb push_back
//#define int ll
//using namespace std;
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,ans,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;
i64 a[N<<2];

struct segtree
{
    i64 L,R,w,len;
}t[N<<2];

struct ScanLine
{
    i64 l,r,h;
    int mark;
    bool operator<(const ScanLine & rhs)const
    {
        return h<rhs.h;
    }
}line[N<<1];

struct segment_tree
{
    #define ls u<<1
    #define rs u<<1|1
    void pushup(i64 u)
    {
        i64 L=t[u].L,R=t[u].R;
        //���ڵ㱻���ǣ�����㸲�ǳ��ȣ�
        //���������ӽڵ�ĳ�����ӡ�
        //����R+1����Ϊ���ǵ����Ҫ����߶�
        if(t[u].w)
            t[u].len = a[R+1]-a[L];
        else
            t[u].len = t[ls].len+t[rs].len;
    }
    //��ʼ��L,R?
    void build(i64 u,i64 L,i64 R)
    {
        t[u].L=L,t[u].R=R;
        if(L==R)
            return ;
        i64 M=L+R>>1;
        build(ls,L,M);
        build(rs,M+1,R);
        return ;
    }
    void update(i64 u,i64 l,i64 r,int mark)
    {
        i64 L=t[u].L,R=t[u].R,M=L+R>>1;
        //˵���޹�
        if(a[R+1] <= l || r <= a[L])
            return ;
        //˵����ȫ�ص��������ǡ�
        // if (l <= t[rt].l && t[rt].r <= r)
        if(l<=a[L] && a[R+1]<=r)
        {
            //sum�����á�
            t[u].w+=mark;
            pushup(u);
            return ;
        }
        //�����ָ��ǡ�
        update(ls,l,r,mark);
        update(rs,l,r,mark);
        pushup(u);
    }
    #undef ls
    #undef rs
}Tree;

void solve()
{
    std::cin>>n;
    i64 x1,x2,y1,y2;
    for(int i=1;i<=n;i++)
    {
        std::cin>>x1>>y1>>x2>>y2;
        a[2*i-1]=x1,a[2*i]=x2;
        line[2*i-1]=(ScanLine){x1,x2,y1,1};
        line[2*i]=(ScanLine){x1,x2,y2,-1};
    }
    n<<=1;
    std::sort(a+1,a+1+n);
    std::sort(line+1,line+1+n);
    //unique����Ҫ-1-a����Ϊ�����ص�����һ��λ�á�
    //����������Ϊ�˺��潨����
    i64 tot = std::unique(a+1,a+1+n)-a-1;
    //���㶥���Ǹ�
    Tree.build(1,1,tot-1);
    for(int i=1;i<n;i++)
    {
        Tree.update(1,line[i].l,line[i].r,line[i].mark);
        ans+=t[1].len*(line[i+1].h-line[i].h);
        // std::cout<<"t[1].len="<<t[1].len<<",ans="<<ans<<"\n";
    }
    std::cout<<ans<<"\n";
}

signed main()
{
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

/*--------------------------------------------------------------------------------------------------------------------------------------------------
double���͵�
--------------------------------------------------------------------------------------------------------------------------------------------------*/
#include<bits/stdc++.h>
#define i64 long long
#define maxn 500050
#define pb push_back
//#define int ll
//using namespace std;
typedef std::pair<i64,i64> PII;
const i64 inf=1e16+5;
const i64 N=3e5+10;
const i64 mod=1e9+7;
i64 T=1,n,m,k,_a,_b,cnt,sum,num,res,avg,x,y,z,zz,p,flag=1;

double a[N<<2];
double ans;

struct segtree
{
    i64 L,R;
	double w,len;
}t[N<<2];

struct ScanLine
{
    double l,r,h;
    int mark;
    bool operator<(const ScanLine & rhs)const
    {
        return h<rhs.h;
    }
}line[N<<2];

struct segment_tree
{
    #define ls u<<1
    #define rs u<<1|1
    void pushup(i64 u)
    {
        int L=t[u].L,R=t[u].R;
        //���ڵ㱻���ǣ�����㸲�ǳ��ȣ�
        //���������ӽڵ�ĳ�����ӡ�
        //����R+1����Ϊ���ǵ����Ҫ����߶�
        if(t[u].w)
            t[u].len = a[R+1]-a[L];
        else
            t[u].len = t[ls].len+t[rs].len;
    }
    //��ʼ��L,R?
    void build(i64 u,i64 L,i64 R)
    {
        t[u].L=L,t[u].R=R;
        if(L==R)
            return ;
        i64 M=L+R>>1;
        build(ls,L,M);
        build(rs,M+1,R);
        return ;
    }
    void update(i64 u,double l,double r,int mark)
    {
        i64 L=t[u].L,R=t[u].R,M=L+R>>1;
        //˵���޹�
        if(a[R+1] <= l || r <= a[L])
            return ;
        //˵����ȫ�ص��������ǡ�
        // if (l <= t[rt].l && t[rt].r <= r)
        if(l<=a[L] && a[R+1]<=r)
        {
            //sum�����á�
            t[u].w+=mark;
            pushup(u);
            return ;
        }
        //�����ָ��ǡ�
        update(ls,l,r,mark);
        update(rs,l,r,mark);
        pushup(u);
    }
    #undef ls
    #undef rs
}Tree;

void solve()
{
	int cnt = 0;
	while(true)
	{
		std::cin>>n;
		if(n==0)break;
		ans=0;
		for(int i=1;i<=(n<<2);i++)
		{
			t[i].L=t[i].R=t[i].len=t[i].w=0;
			line[i].l=line[i].r=line[i].mark=line[i].h=0;
		}
		std::cout<<"Test case #"<<++cnt<<"\n";

		double x1,x2,y1,y2;
		for(int i=1;i<=n;i++)
		{
			std::cin>>x1>>y1>>x2>>y2;
			a[2*i-1]=x1,a[2*i]=x2;
			line[2*i-1]=(ScanLine){x1,x2,y1,1};
			line[2*i]=(ScanLine){x1,x2,y2,-1};
		}
		n<<=1;
		std::sort(a+1,a+1+n);
		std::sort(line+1,line+1+n);
		//unique����Ҫ-1-a����Ϊ�����ص�����һ��λ�á�
		//����������Ϊ�˺��潨����
		i64 tot = std::unique(a+1,a+1+n)-a-1;
		//���㶥���Ǹ�
		Tree.build(1,1,tot-1);
		for(int i=1;i<n;i++)
		{
			Tree.update(1,line[i].l,line[i].r,line[i].mark);
			ans+=t[1].len*(line[i+1].h-line[i].h);
		}
		std::cout<<std::fixed<<std::setprecision(2)<<"Total explored area: "<<ans<<"\n\n";
	}
}

signed main()
{
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