struct Trie {
    int n,tot;
    vector<array<int,26>> tr;
    vector<int> cnt;
    Trie(int n) {
        this->n=n;
        tot=0;
        tr.assign(n,{});
        cnt.assign(n,{});
    }

    void add(string s) {
        int p=0;
        for(auto ch:s) {
            int u=ch-'a';
            if(tr[p][u]==0) tr[p][u]=++tot;
            p=tr[p][u];   
        }
        cnt[p]++;
    }

    int query(string s) {
        int p=0;
        for(auto ch:s) {
            int u=ch-'a';
            if(tr[p][u]==0) return 0;
            p=tr[p][u];
        }

        return cnt[p];
    }
};
