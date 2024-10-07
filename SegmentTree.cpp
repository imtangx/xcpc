template<class Info>
struct SegmentTree
{
	#define l(p) (p<<1)
	#define r(p) (p<<1|1)
	int n;
	vector<Info> info;

	SegmentTree() {}
	SegmentTree(vector<Info> _init) {
		n=_init.size()-1;
		info.resize(4*n+10);
		auto build=[&](auto build,int p,int l,int r)->void {
			if(l==r) info[p]=_init[l];
			else {
				int mid=l+r>>1;
				build(build,l(p),l,mid);
				build(build,r(p),mid+1,r);
				pushup(p);
			}
		};
		build(build,1,1,n);
	}

	void pushup(int p) {
		info[p]=info[l(p)]+info[r(p)];
	}

	void modify(int pos,const Info &v) {
		modify(1,1,n,pos,v);
	}

	void modify(int p,int l,int r,int pos,const Info &v) {
		if(l==r) info[p]=v;
		else {
			int mid=l+r>>1;
			if(mid>=pos) modify(l(p),l,mid,pos,v);
			else modify(r(p),mid+1,r,pos,v);
			pushup(p);
		}
	}

	Info query(int l,int r) {
		return query(1,1,n,l,r);
	}

	Info query(int p,int pl,int pr,int l,int r) { 
		if(pl>=l&&pr<=r) return info[p];
		else {
			int pmid=pl+pr>>1;
			
			if(pmid>=l&&pmid+1<=r) {
				return query(l(p),pl,pmid,l,r)+query(r(p),pmid+1,pr,l,r);
			}
			else if(pmid>=l) return query(l(p),pl,pmid,l,r);
			else if(pmid+1<=r) return  query(r(p),pmid+1,pr,l,r);
		}
	}

	#undef l(p)
	#undef r(p)
};

struct Info {
	
};

Info operator+(Info a,Info b) {
	Info c;

	return c;
}