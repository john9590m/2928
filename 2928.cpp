#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int n,m;

class ynode
{
public:
    int y;
    int xy;
    int x;
    friend bool operator< (ynode &a,ynode &b)
    {
        if (a.y==b.y) return a.x < b.x;
        return a.y < b.y;
    }
    ynode()
    {
        y=0;
        xy=0;
        x=0;
    }
    ~ynode(){}   
private:
};

class node
{
public:
    int x;
    vector<ynode> y;
    vector<ynode> seg;
    int n=0;
    int tx=0;
    int xt=0;
    friend bool operator< (node &a,node &b)
    {
        return a.x<b.x;
    }
    ynode merge(ynode a, ynode b)
    {
        ynode r;
        r.x=a.x+b.x;
        r.y=a.y+b.y;
        r.xy=a.xy+b.xy;
        return r;    
    }
    void update(int s, int e, int x, int p, ynode v)
    {
        if (s == e)
            y[x] = v;
        else
        {
            int m = (s + e) / 2;
            if (p <= m)
                update(s, m, 2 * x, p, v);
            else
                update(m + 1, e, 2 * x + 1, p, v);
            y[x] = merge(y[2 * x], y[2 * x + 1]);
        }
    }
    ynode query(int s, int e, int x, int l, int r)
    {
        ynode I;
        if (x>=seg.size()) return I;
        if (l <= s and e <= r)
            return seg[x];
        else if (l <= e and s <= r)
        {
            int m = (s + e) / 2;
            return merge(query(s, m, 2 * x, l, r), query(m + 1, e, 2 * x + 1, l, r));
        }
        else
            return I; 
    }
    void init()
    {
        n = y.size();
        if (y.size()<=1) return;
        sort(y.begin(),y.end());
        seg.resize(2*n+4);
        for (int i = 0; i < n; i++) 
            update(n+i, 2*n-1, 1, i+1, y[i]);
    }
    int find(int s, int e, int t)
    {
        if (y.size()<=1) return 0;
        if (s>=e) return s;
        int m = (s+e)/2;
        if(y[m].y>t) return find(s,m,t);
        else if (y[m].y<t) return find(m+1,e,t);
        else return m;
    }
    node()
    {
        xt=0;
        tx=0;
    }
    ~node(){}
private:
};

vector<node> x1y1t;
vector<node> x1y2t;
vector<node> x2y1t;
vector<node> x2y2t;
node x1y1[100004*2];
node x1y2[100004*2];
node x2y1[100004*2];
node x2y2[100004*2];
int t=-1;

node merge(node a, node b)
{ 
    node result;
    if (t==-1)
    {
        result.y = a.y;
        for (ynode i : b.y) result.y.push_back(i);
        result.init();
    }
    else
    {
        int m=a.find(0,a.n,t);
        ynode temp=a.query(0,a.n,1,0,m);
        ynode temp2=a.query(0,a.n,1,m+1,a.n);
        result.xt=temp.xy + temp2.x*t;
        result.tx=temp.y*t + t*t*(a.n-m-1);
        m=b.find(0,b.n,t);
        temp = b.query(0,b.n,1,0,m);
        temp2 = b.query(0,b.n,1,m+1,b.n);
        result.xt += temp.xy + temp2.x * t;
        result.tx += temp.y * t + t * t * (b.n - m - 1);
    }
    return result;
}

void update(int xy, int s, int e, int x, int p, node v)
{
    if (s == e)
        switch(xy)
        {
            case 0 : x1y1[x] = v;
                    break;
            case 1 : x1y2[x] = v; 
                    break;
            case 2 : x2y1[x] = v;
                    break;
            case 3 : x2y2[x] = v;
                    break;
            default : break;
        }
    else
    {
        int m = (s + e) / 2;
        if (p <= m)
            update(xy, s, m, 2 * x, p, v);
        else
            update(xy, m + 1, e, 2 * x + 1, p, v);
        switch (xy)
        {
            case 0:
                x1y1[x] = merge(x1y1[2 * x], x1y1[2 * x + 1]);
                break;
            case 1:
                x1y2[x] = merge(x1y2[2 * x], x1y2[2 * x + 1]);
                break;
            case 2:
                x2y1[x] = merge(x2y1[2 * x], x2y1[2 * x + 1]);
                break;
            case 3:
                x2y2[x] = merge(x2y2[2 * x], x2y2[2 * x + 1]);
                break;
            default:
                break;
        }
    }
}

node query(int xy, int s, int e, int x, int l, int r)
{
    node I;
    if (l <= s and e <= r)
    {
        switch (xy)
        {
        case 0:
            return x1y1[x];
        case 1:
            return x1y2[x];
        case 2:
            return x2y1[x];
        case 3:
            return x2y2[x];
        }
        return I;
    }
    else if (l <= e and s <= r)
    {
        int m = (s + e) / 2;
        return merge(query(xy, s, m, 2 * x, l, r), query(xy, m + 1, e, 2 * x + 1, l, r));
    }
    else
        return I;
}

int find(int xy,int s,int e,int t)
{
    if (s>=e) return s;
    int m = (s+e)/2;
    int r;
    switch (xy)
    {
        case 0:
            r=x1y1t[m].x;
            break;
        case 1:
            r=x1y2t[m].x;
            break;
        case 2:
            r=x2y1[m].x;
            break;
        case 3:
            r=x2y2[m].x;
            break;
    }
    if (r>t) return find(xy,s,m,t);
    else if (r<t) return find(xy,m+1,e,t);
    else return m;
}

void init()
{
    int i;
    sort(x1y1t.begin(), x1y1t.end());
    for (i=0;i<n;i++) 
        update(0,n+i,2*n-1,1,n+i,x1y1t[i]);
    sort(x1y2t.begin(), x1y2t.end());
    for (i = 0; i < n; i++)
        update(1, n + i, 2 * n - 1, 1, n + i, x1y2t[i]);
    for (i = 0; i < n; i++)
        update(2, n + i, 2 * n - 1, 1, n + i, x2y1t[i]);
    sort(x2y2t.begin(), x2y2t.end());
    for (i = 0; i < n; i++)
        update(3, n + i, 2 * n - 1, 1, n + i,x2y2t[i]);
}

int main(void)
{
    int x1,y1,x2,y2;
    cin >> n;
    node temp;
    ynode ytemp;
    for (int i=0;i<n;i++)
    {
        cin >> x1 >> y1 >> x2 >> y2;
        x1--; y1--;
        ytemp.x=x1;
        ytemp.y=y1;
        ytemp.xy=x1*y1;
        temp.n=1;
        temp.y.push_back(ytemp);
        x1y1t.push_back(temp);
        temp.y.clear();
        temp.x=x2;
        ytemp.xy=x2*y1;
        temp.y.push_back(ytemp);
        x2y1t.push_back(temp);
        temp.y.clear();
        ytemp.xy=x1*y2;
        ytemp.y=y2;
        temp.y.push_back(ytemp);
        temp.x=x1;
        x1y2t.push_back(temp);
        temp.y.clear();
        temp.x=x2;
        ytemp.xy=x2*y2;
        temp.y.push_back(ytemp);
        x2y2t.push_back(temp);
        temp.y.clear();
    }
    init();
    cin >> m;
    node a,b;
    int mx,my;
    for (int i=0;i<m;i++)
    {
        cin >> t;
        int result = 0;
        for (int j=0;j<4;j++)
        {
            int cur = 0;
            mx = find(j,0,n,t);
            a = query(j,0,n,1,0,mx);
            cur += a.xt;
            b = query(j,0,n,1,mx+1,n);
            cur += a.tx;
            if (j%3) result -= cur;
            else result += cur;
        }
        cout << result << endl;
    }
}
