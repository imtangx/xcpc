struct Tree {
    int n,tot,mx,cur;
    vector<int> L,R,in,siz,big,cnt,ans,col;
    vector<vector<int>> G;

    Tree() {}
    Tree(int n) {
        this->n=n;
        tot=0;
        mx=0; //最多出现次数
        cur=0; //现在的答案
        L.assign(n+10,0);
        R.assign(n+10,0);
        in.assign(n+10,0);
        siz.assign(n+10,1);
        big.assign(n+10,-1);
        cnt.assign(n+10,0);
        ans.assign(n+10,0);
        col.assign(n+10,0);
        G.assign(n+10,{});
    }

    void addEdge(int u,int v) {
        G[u].push_back(v);
    }

    void work() {
        dfs0(0,-1);
        dfs1(0,-1,false);
    }

    void add(int x) {

    }

    void del(int x) {

    }

    void dfs0(int u,int fa) { //求重儿子和DFS序
        L[u]=++tot;
        in[tot]=u;
        siz[u]=1;
        for(auto v:G[u]) {
            if(v==fa) continue;
            dfs0(v,u);
            siz[u]+=siz[v];
            if(big[u]==-1||siz[v]>siz[big[u]]) big[u]=v;
        }
        R[u]=tot;
    }

    void dfs1(int u,int fa,bool isBig) {
        for(auto v:G[u]) { 
            if(v==fa) continue;
            if(v==big[u]) continue;
            dfs1(v,u,false);
        }

        if(big[u]!=-1) {
            dfs1(big[u],u,true);
        }

        for(auto v:G[u]) {
            if(v==fa) continue;
            if(v==big[u]) continue;
            for(int i=L[v];i<=R[v];i++) {
                add(in[i]);
            }
        }

        add(u);
        ans[u]=cur;

        if(!isBig) {
            for(int i=L[u];i<=R[u];i++) {
                del(in[i]);
            }
        }
    }
};