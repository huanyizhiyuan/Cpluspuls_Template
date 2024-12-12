#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;
int f[305][305], s[305], n, m;
vector<int> e[305];

int dfs(int u) {
    int p = 1;
    f[u][1] = s[u];
    for (auto v : e[u]) {
        int siz = dfs(v);
        // ע����������ѭ�����Ͻ���½�
        // ֻ�����Ѿ��ϲ������������Լ�ѡ�Ŀγ������� m+1 ��״̬û������
        for (int i = min(p, m + 1); i; i--)
            for (int j = 1; j <= siz && i + j <= m + 1; j++)
                f[u][i + j] = max(f[u][i + j], f[u][i] + f[v][j]);  // ת�Ʒ���
        p += siz;
    }
    return p;
}

int main() {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n; i++) {
        int k;
        scanf("%d%d", &k, &s[i]);
        e[k].push_back(i);
    }
    dfs(0);
    printf("%d", f[0][m + 1]);
    return 0;
}