struct trie
{
    int nex[maxn][26], tot=0;//ÿ����㶼������26���ӽ�㡣
    bool word[maxn];  // �ý���β���ַ����Ƿ���ڡ�
    // int word[maxn];  // ���ڼ�¼��������Ϊ����ĩβ���ʸ�����

    // �����ַ���
    void insert(std::string s) 
    {  
        int u = 0;//����㡣
        for (int i = 0; i < s.size(); i++) 
        {
            int c = s[i] - 'a';
            if (!nex[u][c]) nex[u][c] = ++tot;  // ���û�У�����ӽ��
            u = nex[u][c];
            // res+=word[u];    //�����Ѿ����ڵġ�
        }
        word[u] = 1;
        // word[u]++;
    }

    // �����ַ��������Ҫ���ر������Ҫ��Ϊint
    bool find(std::string s)
    {  
        int p = 0;
        for (int i = 0; i < s.size(); i++) 
        {
            int c = s[i] - 'a';
            if (!nex[p][c]) 
                return 0;
            p = nex[p][c];
        }
        //�����word[p]�������жϵ����Ƿ���ڵġ�
        //ǰ��ı���˵������������������֤����������ʡ�
        return word[p];
    }
}Tree;