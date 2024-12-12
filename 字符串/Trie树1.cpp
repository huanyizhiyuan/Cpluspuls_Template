struct trie
{
    int nex[maxn][26], tot=0;//每个结点都可能有26个子结点。
    bool word[maxn];  // 该结点结尾的字符串是否存在。
    // int word[maxn];  // 用于记录以这个结点为单词末尾单词个数。

    // 插入字符串
    void insert(std::string s) 
    {  
        int u = 0;//根结点。
        for (int i = 0; i < s.size(); i++) 
        {
            int c = s[i] - 'a';
            if (!nex[u][c]) nex[u][c] = ++tot;  // 如果没有，就添加结点
            u = nex[u][c];
            // res+=word[u];    //加上已经存在的。
        }
        word[u] = 1;
        // word[u]++;
    }

    // 查找字符串，如果要返回别的数，要改为int
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
        //这里的word[p]是用来判断单词是否存在的。
        //前面的遍历说面存在这个链，但不保证存在这个单词。
        return word[p];
    }
}Tree;