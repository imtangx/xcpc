typedef unsigned long long ull;
constexpr int P=13331;

struct Hash {
    int n;
    vector<ull> p,f;
    
    Hash(string s) {
        this->n=s.size();
        p.assign(n+1,0);
        f.assign(n+1,0);
        p[0]=1;
        for(int i=1;i<=n;i++) {
            p[i]=p[i-1]*P;
            f[i]=f[i-1]*P+s[i-1];
        }
    }

    ull getHash(int l,int r) {
        return f[r]-f[l-1]*p[r-l+1];
    }
};