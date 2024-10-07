struct Node{
    int l,r;
    mutable LL v;

    Node(const int &il,const int &ir,const int &iv):l(il),r(ir),v(iv) {}
    bool operator< (const Node &o) const{ return l<o.l; }
};
set<Node> odt;

void build()
{
    for(int i=0;i<n;i++)
    {
        int j=i;
        while(j+1<n&&a[j+1]==a[i]) j++;
        odt.insert({i,j,a[i]});
        i=j;
    }
}

auto split(int x)
{
    if(x>=n) return odt.end();
    auto it=--odt.upper_bound({x,0,0});
    if(it->l==x) return it;
    int l=it->l,r=it->r,v=it->v;
    odt.erase(it);
    odt.insert({l,x-1,v});
    return odt.insert({x,r,v}).first;
}

void range_add(int l,int r,int c)
{
    auto itr=split(r+1),itl=split(l);
    for(;itl!=itr;itl++) itl->v+=c;
}

void assign(int l,int r,int v)
{
    auto itr=split(r+1),itl=split(l);
    odt.erase(itl,itr);
    odt.insert({l,r,v});
}

int query1(int l,int r,int k)
{
    auto itr=split(r+1),itl=split(l);
    for(;itl!=itr;++itl)
    {

    }
}