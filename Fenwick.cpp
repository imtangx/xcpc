template<class T>
struct Fenwick {
    int n;
    vector<T> tr;

    Fenwick() {}
    Fenwick(int n) {
        this->n=n;
        tr.assign(n+1,T{});
    }

    Fenwick(vector<T> _init) {
        this->n=_init.size();
        tr.assign(n+1,T{});
        for(int i=0;i<n;i++) {
            add(i+1,_init[i]);
        }
    }

    int lowbit(int x) {
        return x&-x;
    }

    void add(int x,const T &v) {
        for(int i=x;i<=n;i+=lowbit(i)) {
            tr[i]+=v;
        }
    }

    T sum(int x) {
        T ans{};
        for(int i=x;i;i-=lowbit(i)) {
            ans+=tr[i];
        }
        return ans;
    }

    T rangeSum(int l,int r) {
        return sum(r)-sum(l-1);
    }

    int findFirst(const T &k) {
        int x=0;
        T cur{};
        for(int i=__lg(n);i;i--) {
            if(x+(1<<i)<=n&&cur+tr[x+(1<<i)]<=k) {
                cur+=tr[x+(1<<i)];
                x+=(1<<i);
            }
        }
        return x+1;
    }
};