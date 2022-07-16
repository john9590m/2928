#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n,m;

template <typename T>
void update(int s, int e, int x, int p, T v, vector<T> seg);
template <typename T>
T query(int s, int e, int x, int l, int r, vector<T> seg);

class ynode2
{
public:
    int x1y1,x1y2,x2y1,x2y2,x1,x2,y1,y2,t;
    int n;
    int arr[16];
    friend bool operator<(ynode2 &a, ynode2 &b)
    {
        return a.y2 < b.y2;
    }
    ynode2()
    {
        x1y1=0;
        x1y2=0;
        x2y1=0;
        x2y2=0;
        x1=0;
        x2=0;
        y1=0;
        y2=0;
        t=0;
    }
    ~ynode2() {}
private:
};

class ynode
{
public:
    int x1y1, x1y2, x2y1, x2y2, x1, x2, y1, y2,t;
    int arr[16];
    vector<ynode2> ynode2,seg;
    friend bool operator< (ynode &a,ynode &b)
    {
        return a.y1 < b.y1;
    }
    int find(int t, int s, int e)
    {
        if (ynode2.size() <= 1)
            return 0;
        if (s >= e)
            return s;
        int m = (s + e) / 2;
        if (ynode2[m].y2 > t)
            return find(s, m, t);
        else if (ynode2[m].y2 < t)
            return find(m + 1, e, t);
        else
            return m;
    }
    void init();
    ynode()
    {
        x1y1=0;
        x1y2=0;
        x2y1=0;
        x2y2=0;
        x1=0;
        x2=0;
        y1=0;
        y2=0;
        t=0;
    }
    ~ynode(){}   
private:
};

class xnode
{
public:
    int x1y1, x1y2, x2y1, x2y2, x1, x2, y1, y2,t;
    int arr[16];
    vector<ynode> ynode1;
    vector<ynode> seg;
    friend bool operator<(xnode &a, xnode &b)
    {
        if (a.y1 == b.y1)
            return a.x2 < b.x2;
        return a.y1 < b.y1;
    }
    int find(int t, int s, int e)
    {
        if (ynode1.size() <= 1)
            return 0;
        if (s >= e)
            return s;
        int m = (s + e) / 2;
        if (ynode1[m].y2 > t)
            return find(s, m, t);
        else if (ynode1[m].y2 < t)
            return find(m + 1, e, t);
        else
            return m;
    }
    void init();
    xnode()
    {
        x1y1 = 0;
        x1y2 = 0;
        x2y1 = 0;
        x2y2 = 0;
        x1 = 0;
        x2 = 0;
        y1 = 0;
        y2 = 0;
        t = 0;
    }
    ~xnode() {}
private:
};

class node
{
public:
    int x1y1, x1y2, x2y1, x2y2, x1, x2, y1, y2,t;
    int arr[16];
    vector<xnode> xnode2;                     
    vector<xnode> seg;
    friend bool operator< (node &a,node &b)
    {
        return a.x1<b.x1;
    }
    int find(int s, int e, int t)
    {
        if (xnode2.size()<=1) return 0;
        if (s>=e) return s;
        int m = (s+e)/2;
        if(xnode2[m].x2>t) return find(s,m,t);
        else if (xnode2[m].x2<t) return find(m+1,e,t);
        else return m;
    }
    void init();
    node()
    {
        x1y1 = 0;
        x1y2 = 0;
        x2y1 = 0;
        x2y2 = 0;
        x1 = 0;
        x2 = 0;
        y1 = 0;
        y2 = 0;
        t=0;
    }
    ~node(){}
private:
};
ynode2 merge(ynode2 a, ynode2 b);
ynode merge(ynode a,ynode b);
xnode merge(xnode a, xnode b);
node merge(node a, node b);
node query(int s, int e, int x, int l, int r, vector<node> seg);
xnode query(int s, int e, int x, int l, int r, vector<xnode> seg);
ynode query(int s, int e, int x, int l, int r, vector<ynode> seg);
ynode2 query(int s, int e, int x, int l, int r, vector<ynode2> seg);

vector<node> seg,node2;
int t=-1;

ynode2 merge(ynode2 a,ynode2 b)
{
    ynode2 r;

    r.x1y1 = a.x1y1 + b.x1y1;

    r.x1y2 = a.x1y2 + b.x1y2;

    r.x2y1 = a.x2y1 + b.x2y1;

    r.x2y2 = a.x2y2 + b.x2y2;

    r.x1 = a.x1 + b.x1;

    r.x2 = a.x2 + b.x2;

    r.y1 = a.y1 + b.y1;

    r.y2 = a.y2 + b.y2;

    return r;
}
ynode merge(ynode a, ynode b) //y2에 대한 분기점
{
    ynode2 temp, temp2;
    ynode r;
    r.t=t;
    if (t > 0)
    {
        int m1,m2;
        if (a.t != t)
        {
            m1 = a.find(-t, 0, a.ynode2.size());
            m2 = a.find(t, 0, a.ynode2.size());
            temp = query(0, n, 1, m1, m2,a.seg);
            temp2 = query(0, n, 1, m2, a.ynode2.size(),a.seg);
            a.arr[0] = temp.x2y2 + temp.x1 * t + temp.y1 * t + t * t; //(y2+t)(x2+t)
            a.arr[1] = temp2.x2 * t * 2 + temp2.x2 + 2 * t * t + t; //(x2+t)(2t+1)
            a.arr[2] = temp.x2y2 - temp.x2y1 - temp.y1 * t + temp.y2 * t; //(y2-y1)(x2+t)
            a.arr[3] = -temp2.x2y1 + (t + 1) * temp2.x2 + (t + 1 - temp2.y1) * t; //(t+1-y1)(x2+t)
            a.arr[4] = temp.y2 * t * 2 + 2 * t * t + temp.y2 + t; //(2t+1)(y2+t)
            a.arr[5] = 4 * t * t + 4 * t + 1; //(2t+1)(2t+1)
            a.arr[6] = temp.y2 * t * 2 - temp.y1 * t * 2 + temp.y2 - temp.y1; //(y2-y1)(2t+1)
            a.arr[7] = (t + 1 - temp2.y1) * (2 * t + 1); //(t+1-y1)(2t+1)
            a.arr[8] = temp.x2y2 - temp.x1y2 + temp.x2 * t - temp.x1 * t; //(y2+t)(x2-x1)
            a.arr[9] = temp2.x2 * t * 2 - temp2.x1 * t * 2 + temp2.x2 - temp2.x1; //(2t+1)(x2-x1)
            a.arr[10] = temp.x2y2 + temp.x1y1 - temp.x1y2 - temp.x2y1; //(y2-y1)(x2-x1)
            a.arr[11] = -temp2.x2y1 + temp2.x1y1 + (t + 1) * (temp2.x2 - temp2.x1); //(t + 1 -y1)(x2-x1)
            a.arr[12] = -temp.x1y2 - temp.x1 * t + (t + 1) * (temp.y2 + t); //(y2+t)(t+1-x1)
            a.arr[13] = (2 * t + 1) * (t + 1 - temp2.x1); //(2t+1)(t+1-x1)
            a.arr[14] = -temp.x1y2 + temp.x1y1 + (t + 1) * (temp.y2 - temp.y1); //(y2-y1)(t + 1-x1)
            a.arr[15] = temp2.x1y1 - (t + 1) * temp2.y1 - (t + 1) * temp2.x1 + (t + 1) * (t + 1); //(t+1 - y1)(t+1-x1)
        }
        if (b.t!=t)
        {
            m1 = b.find(-t, 0, b.ynode2.size());
            m2 = b.find(t, 0, b.ynode2.size());
            temp = query(0, n, 1, m1, m2,b.seg);
            temp2 = query(0, n, 1, m2, n,b.seg);
            b.arr[0] = temp.x2y2 + temp.x1 * t + temp.y1 * t + t * t; //(y2+t)(x2+t)
            b.arr[1] = temp2.x2 * t * 2 + temp2.x2 + 2 * t * t + t; //(x2+t)(2t+1)
            b.arr[2] = temp.x2y2 - temp.x2y1 - temp.y1 * t + temp.y2 * t; //(y2-y1)(x2+t)
            b.arr[3] = -temp2.x2y1 + (t + 1) * temp2.x2 + (t + 1 - temp2.y1) * t; //(t+1-y1)(x2+t)
            b.arr[4] = temp.y2 * t * 2 + 2 * t * t + temp.y2 + t; //(2t+1)(y2+t)
            b.arr[5] = 4 * t * t + 4 * t + 1; //(2t+1)(2t+1)
            b.arr[6] = temp.y2 * t * 2 - temp.y1 * t * 2 + temp.y2 - temp.y1; //(y2-y1)(2t+1)
            b.arr[7] = (t + 1 - temp2.y1) * (2 * t + 1); //(t+1-y1)(2t+1)
            b.arr[8] = temp.x2y2 - temp.x1y2 + temp.x2 * t - temp.x1 * t; //(y2+t)(x2-x1)
            b.arr[9] = temp2.x2 * t * 2 - temp2.x1 * t * 2 + temp2.x2 - temp2.x1; //(2t+1)(x2-x1)
            b.arr[10] = temp.x2y2 + temp.x1y1 - temp.x1y2 - temp.x2y1; //(y2-y1)(x2-x1)
            b.arr[11] = -temp2.x2y1 + temp2.x1y1 + (t + 1) * (temp2.x2 - temp2.x1); //(t + 1 -y1)(x2-x1)
            b.arr[12] = -temp.x1y2 - temp.x1 * t + (t + 1) * (temp.y2 + t); //(y2+t)(t+1-x1)
            b.arr[13] = (2 * t + 1) * (t + 1 - temp2.x1); //(2t+1)(t+1-x1)
            b.arr[14] = -temp.x1y2 + temp.x1y1 + (t + 1) * (temp.y2 - temp.y1); //(y2-y1)(t + 1-x1)
            b.arr[15] = temp2.x1y1 - (t + 1) * temp2.y1 - (t + 1) * temp2.x1 + (t + 1) * (t + 1); //(t+1 - y1)(t+1-x1)
        }
        for(int i=0;i<16;i++) r.arr[i] = a.arr[i] + b.arr[i];
    }   
    else
    {
        r.ynode2 = a.ynode2;
        for (ynode2 i : b.ynode2) r.ynode2.push_back(i);
        r.init();
    }
    r.x1y1 = a.x1y1 + b.x1y1;
    r.x1y2 = a.x1y2 + b.x1y2;
    r.x2y1 = a.x2y1 + b.x2y1;
    r.x2y2 = a.x2y2 + b.x2y2;
    r.x1 = a.x1 + b.x1;
    r.x2 = a.x2 + b.x2;
    r.y1 = a.y1 + b.y1;
    r.y2 = a.y2 + b.y2;
    return r;
}

node query(int s, int e, int x, int l, int r,vector<node> seg)
{
    node I;
    if (l <= s and e <= r)
    {
        return merge(seg[x],I);
    }
    else if (l <= e and s <= r)
    {
        int m = (s + e) / 2;
        return merge(query(s, m, 2 * x, l, r,seg), query(m + 1, e, 2 * x + 1, l, r,seg));
    }
    else
        return I;
}
xnode query(int s, int e, int x, int l, int r, vector<xnode> seg)

{

    xnode I;

    if (l <= s and e <= r)

    {

        return merge(seg[x], I);
    }

    else if (l <= e and s <= r)

    {

        int m = (s + e) / 2;

        return merge(query(s, m, 2 * x, l, r, seg), query(m + 1, e, 2 * x + 1, l, r, seg));
    }

    else

        return I;
}

ynode query(int s, int e, int x, int l, int r, vector<ynode> seg)

{

    ynode I;

    if (l <= s and e <= r)

    {

        return merge(seg[x], I);
    }

    else if (l <= e and s <= r)

    {

        int m = (s + e) / 2;

        return merge(query(s, m, 2 * x, l, r, seg), query(m + 1, e, 2 * x + 1, l, r, seg));
    }

    else

        return I;
}

ynode2 query(int s, int e, int x, int l, int r, vector<ynode2> seg)

{

    ynode2 I;

    if (l <= s and e <= r)

    {

        return merge(seg[x], I);
    }

    else if (l <= e and s <= r)

    {

        int m = (s + e) / 2;

        return merge(query(s, m, 2 * x, l, r, seg), query(m + 1, e, 2 * x + 1, l, r, seg));
    }

    else

        return I;
}

xnode merge(xnode a, xnode b) //y1에 대한 분기점
{
    xnode r;
    r.t = t;
    ynode temp1,temp2;
    if (t > 0)
    {
        int m1,m2;
        if (a.t!=t)
        {
            m1 = a.find(-t, 0, a.ynode1.size());
            m2 = a.find(t, 0, a.ynode1.size());
            temp1 = query(0, a.seg.size(), 1, 0, m1,a.seg);
            temp2 = query(0, a.seg.size(), 1, m1, m2,a.seg);
            for (int i = 0; i < 16; i++)
            {
                if (i % 4 == 0 || i % 4 == 1)
                    a.arr[i] = temp1.arr[i];
                else
                    a.arr[i] = temp2.arr[i];
            }
        }
        if (b.t!=t)
        {
            m1 = b.find(-t, 0, b.ynode1.size());
            m2 = b.find(t, 0, b.ynode1.size());
            temp1 = query(0, b.seg.size(), 1, 0, m1,b.seg);
            temp2 = query(0, b.seg.size(), 1, m1, m2,b.seg);
            for (int i = 0; i < 16; i++)
            {
                if (i % 4 == 0 || i % 4 == 1)
                    b.arr[i] = temp1.arr[i];
                else
                    b.arr[i] = temp2.arr[i];
            }
        }
        for (int i=0;i<16;i++) r.arr[i] = a.arr[i] + b.arr[i];
    }
    else
    {
        r.ynode1 = a.ynode1;
        for (ynode i : b.ynode1) r.ynode1.push_back(i);
        r.init();
    }
    r.x1y1 = a.x1y1 + b.x1y1;
    r.x1y2 = a.x1y2 + b.x1y2;
    r.x2y1 = a.x2y1 + b.x2y1;
    r.x2y2 = a.x2y2 + b.x2y2;
    r.x1 = a.x1 + b.x1;
    r.x2 = a.x2 + b.x2;
    r.y1 = a.y1 + b.y1;
    r.y2 = a.y2 + b.y2;
    return r;
}

node merge(node a, node b) //x2에 대한 정리
{
    node r;
    xnode temp1,temp2;
    r.t = t;
    if (t > 0)
    {
        int m1,m2;
        if (t!=a.t)
        {
            m1 = a.find(-t, 0, a.xnode2.size());
            m2 = a.find(t, 0, a.xnode2.size());
            temp1 = query(0, a.seg.size(), 1, 0, m1,a.seg);
            temp2 = query(0, a.seg.size(), 1, m1, m2,a.seg);
            for (int i = 0; i < 16; i++)
            {
                if (i / 4 == 0 || i / 4 == 2)
                    a.arr[i] = temp1.arr[i];
                else
                    a.arr[i] = temp2.arr[i];
            }
        }
        if (t!=b.t)
        {
            m1 = b.find(-t, 0, b.xnode2.size());
            m2 = b.find(t, 0, b.xnode2.size());
            temp1 = query(0, b.seg.size(), 1, 0, m1,b.seg);
            temp2 = query(0, b.seg.size(), 1, m1, m2,b.seg);
            for (int i = 0; i < 16; i++)
            {
                if (i / 4 == 0 || i / 4 == 2)
                    b.arr[i] = temp1.arr[i];
                else
                    b.arr[i] = temp2.arr[i];
            }
        }
        for (int i=0;i<16;i++) r.arr[i] = a.arr[i] + b.arr[i];
    }
    else
    {
        r.xnode2 = a.xnode2;
        for (xnode i : b.xnode2) r.xnode2.push_back(i);
        r.init();
    }
    r.x1y1 = a.x1y1 + b.x1y1;
    r.x1y2 = a.x1y2 + b.x1y2;
    r.x2y1 = a.x2y1 + b.x2y1;
    r.x2y2 = a.x2y2 + b.x2y2;
    r.x1 = a.x1 + b.x1;
    r.x2 = a.x2 + b.x2;
    r.y1 = a.y1 + b.y1;
    r.y2 = a.y2 + b.y2;
    return r;
}

void update(int s, int e, int x, int p, ynode v, vector<ynode> seg)
{
    if (s == e)
        seg[x] = v;
    else
    {
        int m = (s + e) / 2;
        if (p <= m)
            update(s, m, 2 * x, p, v, seg);
        else
            update(m + 1, e, 2 * x + 1, p, v, seg);
        seg[x] = merge(seg[2 * x], seg[2 * x + 1]);
    }
}

void update(int s, int e, int x, int p, node v, vector<node> seg)

{

    if (s == e)

        seg[x] = v;

    else

    {

        int m = (s + e) / 2;

        if (p <= m)

            update(s, m, 2 * x, p, v, seg);

        else

            update(m + 1, e, 2 * x + 1, p, v, seg);

        seg[x] = merge(seg[2 * x], seg[2 * x + 1]);
    }
}

void update(int s, int e, int x, int p, xnode v, vector<xnode> seg)

{

    if (s == e)

        seg[x] = v;

    else

    {

        int m = (s + e) / 2;

        if (p <= m)

            update(s, m, 2 * x, p, v, seg);

        else

            update(m + 1, e, 2 * x + 1, p, v, seg);

        seg[x] = merge(seg[2 * x], seg[2 * x + 1]);
    }
}

void update(int s, int e, int x, int p, ynode2 v, vector<ynode2> seg)

{

    if (s == e)

        seg[x] = v;

    else

    {

        int m = (s + e) / 2;

        if (p <= m)

            update(s, m, 2 * x, p, v, seg);

        else

            update(m + 1, e, 2 * x + 1, p, v, seg);

        seg[x] = merge(seg[2 * x], seg[2 * x + 1]);
    }
}

void ynode::init()

{

    if (ynode2.size() <= 1)

        return;

    sort(ynode2.begin(), ynode2.end());

    seg.resize(2 * ynode2.size() + 4);

    for (int i = 0; i < n; i++)

        update(n + i, 2 * n - 1, 1, i + 1, ynode2[i], seg);
}

void xnode::init()
{

    if (ynode1.size() <= 1)

        return;

    sort(ynode1.begin(), ynode1.end());

    seg.resize(2 * ynode1.size() + 4);

    for (int i = 0; i < n; i++)

        update(n + i, 2 * n - 1, 1, i + 1, ynode1[i], seg);
}

void node::init()
{

    if (xnode2.size() <= 1)

        return;

    sort(xnode2.begin(), xnode2.end());

    seg.resize(2 * xnode2.size() + 4);

    for (int i = 0; i < n; i++)

        update(n + i, 2 * n - 1, 1, i + 1, xnode2[i], seg);
}

void init()
{
    int i,n=node2.size();
    sort(node2.begin(),node2.end());
    for (i=0;i<n;i++)
        update(n+i,2*n-1,1,n+i,node2[i],seg);
}

using namespace std;

int main(void)
{
    int x1,y1,x2,y2;
    cin >> n;
    node temp;
    xnode xtemp;
    ynode ytemp;
    ynode2 ytemp2;
    for (int i=0;i<n;i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        ytemp2.x1 = x1;
        ytemp2.x2 = x2;
        ytemp2.y1 = y1;
        ytemp2.y2 = y2;
        ytemp2.x1y1 = x1 * y1;
        ytemp2.x1y2 = x1 * y2;
        ytemp2.x2y1 = x2 * y1;
        ytemp2.x2y2 = x2 * y2;
        ytemp.x1 = x1;
        ytemp.x2 = x2;
        ytemp.y1 = y1;
        ytemp.y2 = y2;
        ytemp.x1y1 = x1 * y1;
        ytemp.x1y2 = x1 * y2;
        ytemp.x2y1 = x2 * y1;
        ytemp.x2y2 = x2 * y2;
        ytemp.ynode2.push_back(ytemp2);
        xtemp.x1 = x1;
        xtemp.x2 = x2;
        xtemp.y1 = y1;
        xtemp.y2 = y2;
        xtemp.x1y1 = x1 * y1;
        xtemp.x1y2 = x1 * y2;
        xtemp.x2y1 = x2 * y1;
        xtemp.x2y2 = x2 * y2;
        xtemp.ynode1.push_back(ytemp);
        temp.x1=x1;
        temp.x2=x2;
        temp.y1=y1;
        temp.y2=y2;
        temp.x1y1=x1*y1;
        temp.x1y2=x1*y2;
        temp.x2y1=x2*y1;
        temp.x2y2=x2*y2;
        temp.xnode2.push_back(xtemp);
        node2.push_back(temp);
    }
    init();
    cin >> m;
    node a,b;
    int mx,my;
    cout << 1;
    for (int i=0;i<m;i++)
    {
        cin >> t;
        int result = 0;
        a = query(0,n,1,0,n,seg);
        for (int j=0;j<16;j++) result += a.arr[j];
        cout << result << endl;
    }
}
