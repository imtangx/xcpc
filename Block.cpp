struct Block {
    int n,B;
    vector<int> a,bel,lazy;

    Block(vector<int> _init) {
        n=_init.size();
        B=sqrt(n);
        a.resize(n);
        bel.resize(n);
        lazy.resize(B+10);
        for(int i=0;i<n;i++) {
            a[i]=_init[i];
            bel[i]=i/B;
        } 
    }

    void rangeAdd(int l,int r,int c) {
        if(bel[l]==bel[r]) {
            for(int i=l;i<=r;i++) a[i]+=c;
        }
        else {
            int i=l;
            for(;bel[i]==bel[l];i++) a[i]+=c;
            for(;bel[i]!=bel[r];i+=B) lazy[bel[i]]+=c;
            for(;i<=r;i++) a[i]+=c;
        }
    }
};