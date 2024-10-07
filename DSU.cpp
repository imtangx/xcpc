struct DSU {
    vector<int> p,siz;

    DSU(){}
    DSU(int n) {
        p.assign(n+1,0);
        siz.assign(n+1,1);
        iota(p.begin(),p.end(),0);
    }

    int find(int x) {
        if(p[x]!=x) p[x]=find(p[x]);
        return p[x];
    }

    bool same(int x,int y) {
        return find(x)==find(y);
    }

    bool merge(int x,int y) {
        x=find(x); 
        y=find(y);
        if(x==y) {
            return false;
        }

        p[x]=y;
        siz[y]+=siz[x];
        return true;
    }

    int size(int x) {
        return siz[find(x)];
    }
};