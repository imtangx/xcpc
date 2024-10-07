template <class Info, class Tag> struct LazySegmentTree {
	#define l(p) (p << 1)
	#define r(p) (p << 1 | 1)

    int n;
    vector<Info> info;
    vector<Tag> tag;

    LazySegmentTree() {}
    LazySegmentTree(vector<Info> _init) {
        n = _init.size() - 1;
        tag.resize(4 * n + 10);
        info.resize(4 * n + 10);
        auto build = [&](auto build, int p, int l, int r) -> void {
            if (l == r) {
                info[p] = _init[l];
            } else {
                int mid = l + r >> 1;
                build(build, l(p), l, mid);
                build(build, r(p), mid + 1, r);
                pushup(p);
            }
        };
        build(build, 1, 1, n);
    }

    void pushup(int p) { info[p] = info[l(p)] + info[r(p)]; }

    void apply(int p, const Tag &t) {
        info[p].apply(t);
        tag[p].apply(t);
    }

    void pushdown(int p) {
        apply(l(p), tag[p]);
        apply(r(p), tag[p]);
        tag[p] = Tag();
    }

    void modify(int pos, const Info &v) { modify(1, 1, n, pos, v); }

    void modify(int p, int l, int r, int pos, const Info &v) {
        if (l == r) {
            info[p] = v;
        } else {
            pushdown(p);
            int mid = l + r >> 1;
            if (mid >= pos) {
                modify(l(p), l, mid, pos, v);
			} else {
                modify(r(p), mid + 1, r, pos, v);
			}
            pushup(p);
        }
    }

    void Rangeapply(int l, int r, const Tag &t) { Rangeapply(1, 1, n, l, r, t); }

    void Rangeapply(int p, int pl, int pr, int l, int r, const Tag &t) {
        if (pl >= l && pr <= r) {
            apply(p, t);
		} else {
            pushdown(p);
            int pmid = pl + pr >> 1;
            if (pmid >= l) {
                Rangeapply(l(p), pl, pmid, l, r, t);
			}
            if (pmid + 1 <= r) {
                Rangeapply(r(p), pmid + 1, pr, l, r, t);
			}
            pushup(p);
        }
    }

    Info query(int l, int r) { return query(1, 1, n, l, r); }

    Info query(int p, int pl, int pr, int l, int r) {
        if (pl >= l && pr <= r) {
            return info[p];
		}
        else {
            pushdown(p);

            int pmid = pl + pr >> 1;
            if (pmid >= l && pmid + 1 <= r) {
                return query(l(p), pl, pmid, l, r) + query(r(p), pmid + 1, pr, l, r);
            } else if (pmid >= l) {
                return query(l(p), pl, pmid, l, r);
			} else if (pmid + 1 <= r) {
                return query(r(p), pmid + 1, pr, l, r);
			}
        }
    }

	#undef l(p)
	#undef r(p)
};

struct Tag {

    void apply(Tag t) { // 传入父节点的tag更新子结点tag

    }
};

struct Info {

    int len = 1;
    void apply(Tag t) { // 传入父节点的tag更新子结点Info
	
    }
};

Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    return c;
}