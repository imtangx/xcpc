struct ACAM {
    int n,tot;
    vector<array<int,26>> tr;
    vector<vector<int>> ed;
    vector<int> fail,in,deg,cnt;

    ACAM(int n) {
        this->n=n;
        tot=0;
        tr.assign(n,{});
        ed.assign(n,{});
        fail.assign(n,0);
        in.assign(n,0);
        deg.assign(n,0);
        cnt.assign(n,0);
    }

    void add(string s,int id) {
        int p=0;
        for(char ch:s) {
            int u=ch-'a';
            if(tr[p][u]==0) tr[p][u]=++tot;
            p=tr[p][u];
        }
        ed[p].push_back(id); 
        in[id]=p;
    }

    void work() {
        queue<int> q;
        for(int i=0;i<26;i++) {
            if(tr[0][i]) q.push(tr[0][i]);
        }

        while(!q.empty()) {
            int u=q.front();
            q.pop();

            for(int i=0;i<26;i++) {
                int &x=tr[u][i];
                if(x) {
                    fail[x]=tr[fail[u]][i];
                    deg[tr[fail[u]][i]]++;
                    q.push(x);
                }
                else {
                    x=tr[fail[u]][i];
                }
            }
        }
    }

    vector<int> query(string t,int siz) {
        int p=0;
        for(char ch:t) {
            int u=ch-'a';
            p=tr[p][u];
            cnt[p]++;
        }

        queue<int> q;
        for(int i=1;i<=tot;i++) {
            if(deg[i]==0) q.push(i);
        }

        while(!q.empty()) {
            int u=q.front();
            q.pop();

            int v=fail[u];
            cnt[v]+=cnt[u];
            if(--deg[v]==0) q.push(v);
        }

        vector<int> ans(siz);
        for(int i=0;i<siz;i++) {
            ans[i]=cnt[in[i]];
        }
        return ans;
    }
};