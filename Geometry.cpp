const double eps = 1e-8;
const double PI = acos(-1.0);

template <class T>
struct Point
{
    T x, y;
    Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}

    friend ostream &operator<<(ostream &os, Point p) { return os << "(" << p.x << ", " << p.y << ")"; }
    bool operator==(const Point &o) const { return abs(x - o.x) <= eps && abs(y - o.y) <= eps; }
    bool operator<(const Point &o) const { if(abs(x - o.x) >= eps) return x < o.x; return y < o.y;}
    Point operator+(const Point &o) const { return {x + o.x, y + o.y}; }
    Point operator-(const Point &o) const { return {x - o.x, y - o.y}; }
    Point operator-() const { return {-x, -y}; }
    Point operator*(const T &k) const { return {k * x, k * y}; }
    Point operator/(const T &k) const { return {x / k, y / k}; }
    T operator*(const Point &o) const { return {x * o.x + y * o.y}; } // Dot
    T operator^(const Point &o) const { return {x * o.y - y * o.x}; } // Cross
    T len2() const { return (*this) * (*this); }
    T len() const { return sqrt(len2()); }
    bool is_par(const Point &o) const { return abs((*this) ^ o) <= eps; }
    bool is_ver(const Point &o) const { return abs((*this) * o) <= eps; }
    int to_left(const Point &o) const
    {
        if (abs((*this) ^ o) <= eps)
            return 0;
        if (((*this) ^ o) > eps)
            return 1; // left
        return -1;    // right
    }
};

template <class T>
struct Line
{
    Point<T> p, v; // p=p0+v*t
    Line(Point<T> a = Point<T>(), Point<T> b = Point<T>()) : p(a), v(b - a) {}
};

template <class T>
struct Seg
{
    Point<T> a, b;
    Seg(Point<T> _a = Point<T>(), Point<T> _b = Point<T>()) : a(_a), b(_b) {}
};

template <class T>
struct Polygon
{
    vector<Point<T>> p;
    Polygon(vector<Point<T>> _v) : p(_v) {}
};

double radToDeg(double rad) { return 180 / PI * rad; }
double degToRad(double deg) { return PI / 180 * deg; }

template <class T>
Polygon<T> convex_hull(Polygon<T> poly)
{
    auto v = poly.p;
    sort(v.begin(), v.end());

    vector<Point<T>> stk;

    auto check = [=](vector<Point<T>> stk, Point<T> p) -> bool
    {
        auto s1 = stk.back();
        auto s2 = *prev(--stk.end());
        return to_left(p, Line<T>(s2, s1)) <= 0;
    };

    for (int i = 0; i < v.size(); i++)
    {
        while (stk.size() > 1 && check(stk, v[i]))
            stk.pop_back();
        stk.push_back(v[i]);
    }

    int k = stk.size();
    v.pop_back();
    reverse(v.begin(), v.end());
    for (int i = 0; i < v.size(); i++)
    {
        while (stk.size() > k && check(stk, v[i]))
            stk.pop_back();
        stk.push_back(v[i]);
    }

    stk.pop_back();
    return Polygon<T>(stk);
}

template <class T>
T get_hull_d2(Polygon<T> hull)
{
	auto v=hull.p;
	if(v.size()==2){
		return (v[0]-v[1]).len2();
	}

	auto sqr=[](Point<T> a,Point<T> b,Point<T> c)->T{
		return abs((b-a)^(c-a));
	};

	T ans=0;
	int j=2,n=v.size();
	for(int i=0;i<n;i++)
	{
		while(sqr(v[j],v[i],v[(i+1)%n])<=
		sqr(v[(j+1)%n],v[i],v[(i+1)%n])) j=(j+1)%n;
		ans=max({ans,(v[i]-v[j]).len2(),(v[(i+1)%n]-v[j]).len2()});
	}

	return ans;
}

template <class T>
T poly_s2(Polygon<T> poly)
{
    T s = 0;
    auto p = poly.p;
    int n = p.size();
    for (int i = 0; i < n; i++)
        s += p[i] ^ p[(i + 1) % n];
    return abs(s);
}

template <class T>
bool p_on_poly(Point<T> a, Polygon<T> poly)
{
    auto p = poly.p;
    int n = p.size();
    for (int i = 0; i < n; i++)
    {
        if (p_on_s(a, Seg(p[i], p[(i + 1) % n])))
        {
            return true;
        }
    }
    return false;
}

template <class T>
pair<bool, int> p_in_poly(Point<T> a, Polygon<T> poly)
{
    auto p = poly.p;
    int n = p.size();
    if (p_on_poly(a, poly))
        return {true, 0};

    int t = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++)
    {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (u.x < a.x && v.x >= a.x && to_left(a, Line<int>(v, u)) == 1)
        {
            t ^= 1;
            cnt--;
        }
        if (u.x >= a.x && v.x < a.x && to_left(a, Line<int>(u, v)) == 1)
        {
            t ^= 1;
            cnt++;
        }
    }

    return {t == 1, cnt};
}

template <class T>
bool p_on_s(Point<T> p, Seg<T> s)
{
    Point<T> pa = s.a - p, pb = s.b - p;
    return abs(pa ^ pb) <= eps && min(s.a.x, s.b.x) <= p.x && p.x <= max(s.a.x, s.b.x) && min(s.a.y, s.b.y) <= p.y && p.y <= max(s.a.y, s.b.y);
}

template <class T>
bool p_on_l(Point<T> p, Line<T> l)
{
    return to_left(p, l) == 0;
}

template <class T>
T p_Dist_l(Point<T> a, Line<T> l)
{
    Point<T> pa = a - l.p;
    return (pa ^ l.v) / l.v.len();
}

template <class T>
Point<T> p_Project_l(Point<T> a, Line<T> l)
{
    Point<T> pa = a - l.p;
    return l.p + l.v * ((pa * l.v) / l.v.len2());
}

template <class T>
int to_left(Point<T> p, Line<T> l)
{
    Point<T> a = l.p, b = a + l.v;
    double res = (b - a) ^ (p - b);
    if (abs(res) <= eps)
        return 0;
    if (res > 0)
        return 1; // left
    return -1;    // right
}

template <class T>
Point<T> turn(Point<T> a, double r)
{
    return {a.x * cos(r) - a.y * cos(r), a.x * sin(r) + a.y * cos(r)};
}

template <class T>
Point<T> turn90(Point<T> a)
{
    return {-a.y, a.x};
}

template <class T>
Point<T> line_Intersect_line(Line<T> a, Line<T> b)
{
    return a.p + a.v * ((b.v ^ (a.p - b.p)) / (a.v ^ b.v));
}

template <class T>
Line<T> seg_to_line(Seg<T> s)
{
    return Line<T>(s.a, s.b);
}

// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
template <class T>
tuple<int, Point<T>, Point<T>> seg_Intersection_seg(Seg<T> l1, Seg<T> l2)
{
    if (max(l1.a.x, l1.b.x) < min(l2.a.x, l2.b.x))
    {
        return {0, Point<T>(), Point<T>()};
    }
    if (min(l1.a.x, l1.b.x) > max(l2.a.x, l2.b.x))
    {
        return {0, Point<T>(), Point<T>()};
    }
    if (max(l1.a.y, l1.b.y) < min(l2.a.y, l2.b.y))
    {
        return {0, Point<T>(), Point<T>()};
    }
    if (min(l1.a.y, l1.b.y) > max(l2.a.y, l2.b.y))
    {
        return {0, Point<T>(), Point<T>()};
    }
    if (abs((l1.b - l1.a) ^ (l2.b - l2.a)) <= eps)
    {
        if (abs((l1.b - l1.a) ^ (l2.a - l1.a)) > eps)
        {
            return {0, Point<T>(), Point<T>()};
        }
        else
        {
            auto maxx1 = max(l1.a.x, l1.b.x);
            auto minx1 = min(l1.a.x, l1.b.x);
            auto maxy1 = max(l1.a.y, l1.b.y);
            auto miny1 = min(l1.a.y, l1.b.y);
            auto maxx2 = max(l2.a.x, l2.b.x);
            auto minx2 = min(l2.a.x, l2.b.x);
            auto maxy2 = max(l2.a.y, l2.b.y);
            auto miny2 = min(l2.a.y, l2.b.y);
            Point<T> p1(max(minx1, minx2), max(miny1, miny2));
            Point<T> p2(min(maxx1, maxx2), min(maxy1, maxy2));
            if (!p_on_s(p1, l1))
            {
                swap(p1.y, p2.y);
            }
            if (p1 == p2)
            {
                return {3, p1, p2};
            }
            else
            {
                return {2, p1, p2};
            }
        }
    }
    auto cp1 = (l2.a - l1.a) ^ (l2.b - l1.a);
    auto cp2 = (l2.a - l1.b) ^ (l2.b - l1.b);
    auto cp3 = (l1.a - l2.a) ^ (l1.b - l2.a);
    auto cp4 = (l1.a - l2.b) ^ (l1.b - l2.b);

    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) || (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0))
    {
        return {0, Point<T>(), Point<T>()};
    }

    Point p = line_Intersect_line(seg_to_line(l1), seg_to_line(l2));
    if (abs(cp1) <= eps && abs(cp2) <= eps && abs(cp3) <= eps && abs(cp4) <= eps)
    {
        return {1, p, p};
    }
    else
    {
        return {3, p, p};
    }
}