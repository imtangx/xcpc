template<class Info>
struct ChairmanTree
{
    #define l(p) info[p].ch[0]
    #define r(p) info[p].ch[1]
    int n,idx=0;
    vector<Info> info;

    ChairmanTree() {}
    ChairmanTree(int _n){
        n=_n;
        info.resize((n<<5)+10);
    }
    ChairmanTree(int l,int r){
        n=r-l+1;
        info.resize((n<<5)+10);
        auto build=[&](auto &&self,int p,int l,int r){
            p=++idx;
            if(l==r) return;
            int mid=l+r>>1;
            self(self,l(p),l,mid);
            self(self,r(p),mid+1,r);
        };
        build(build,1,l,r);
    }

    void insert(int pre,int &cur,int l,int r,int v){
        cur=++idx; info[cur]=info[pre]; info[cur].v++;
        if(l==r) return;
        int mid=l+r>>1;
        if(v<=mid) insert(l(pre),l(cur),l,mid,v);
        else insert(r(pre),r(cur),mid+1,r,v);  
    }

    // int query(int pre,int cur,int l,int r,int k){
    //     if(l==r) return l;
    //     int mid=l+r>>1;
    //     int s=info[l(cur)].cnt-info[l(pre)].cnt;
    //     if(k<=s) return query(l(pre),l(cur),l,mid,k);
    //     else return query(r(pre),r(cur),mid+1,r,k-s);
    // }

    int query(int cur,int l,int r) {
        return query(cur,1,n,l,r);
    }

    Info query(int p,int pl,int pr,int l,int r) {
        if(pl>=l&&pr<=r) return info[p];
        else {
            int pmid=pl+pr>>1;
            if(pmid>=l&&pmid+1<=r){
				return query(l(p),pl,pmid,l,r)+query(r(p),pmid+1,pr,l,r);
			}
			else if(pmid>=l) return query(l(p),pl,pmid,l,r);
			else if(pmid+1<=r) return  query(r(p),pmid+1,pr,l,r);
        }
    }
};

struct Info {
    int ch[2];
    int v;
};

Info operator+(Info a,Info b){
    Info c;
    c.v=a.v+b.v;
    return c;
}