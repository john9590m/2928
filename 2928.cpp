#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct y2node{
    int x1=0,x2=0,y1=0,y2=0,x1y1=0,x1y2=0,x2y1=0,x2y2=0,n=0,arr[16];
    bool operator< (const y2node &a) const
    {
        return y2<a.y2;
    }
    y2node& operator= (const y2node &a)
    {
         for (int i=0;i<16;i++) arr[i]=a.arr[i];
        x1 = a.x1;
        x2 = a.x2;
        y1 = a.y1;
        y2 = a.y2;
        x1y1 = a.x1y1;
        x2y1 = a.x2y1;
        x1y2 = a.x1y2;
        x2y2 = a.x2y2;
        return *this;
    }
};

struct y1node{
    int x1=0,x2=0,y1=0,y2=0,x1y1=0,x1y2=0,x2y1=0,x2y2=0,n=0,arr[16];
    vector<y2node> seg, ar;
    bool operator< (const y1node &a) const
    {
        return y2<a.y2;
    }
    y1node& operator= (const y1node &a)
    {
         for (int i=0;i<16;i++) arr[i]=a.arr[i];
        x1 = a.x1;
        x2 = a.x2;
        y1 = a.y1;
        y2 = a.y2;
        x1y1 = a.x1y1;
        x2y1 = a.x2y1;
        x1y2 = a.x1y2;
        x2y2 = a.x2y2;
        return *this;
    }
};

struct x2node{
    int x1=0,x2=0,y1=0,y2=0,x1y1=0,x1y2=0,x2y1=0,x2y2=0,n=0,arr[16];
    vector<y1node> seg, ar;
    bool operator< (const x2node &a) const
    {
        return y2<a.y2;
    }
    x2node& operator= (const x2node &a)
    {
         for (int i=0;i<16;i++) arr[i]=a.arr[i];
        x1 = a.x1;
        x2 = a.x2;
        y1 = a.y1;
        y2 = a.y2;
        x1y1 = a.x1y1;
        x2y1 = a.x2y1;
        x1y2 = a.x1y2;
        x2y2 = a.x2y2;
        return *this;
    }
};

struct x1node{
    int x1=0,x2=0,y1=0,y2=0,x1y1=0,x1y2=0,x2y1=0,x2y2=0,n=0,arr[16];
    vector<x2node> seg, ar;
    bool operator< (const x1node &a) const
    {
        return y2<a.y2;
    }
    x1node& operator= (const x1node &a)
    {
         for (int i=0;i<16;i++) arr[i]=a.arr[i];
        x1 = a.x1;
        x2 = a.x2;
        y1 = a.y1;
        y2 = a.y2;
        x1y1 = a.x1y1;
        x2y1 = a.x2y1;
        x1y2 = a.x1y2;
        x2y2 = a.x2y2;
        return *this;
    }
};


vector<x1node> ar;
vector<x1node> seg;
int arr[16];
int n,m,t=-1;

y2node seginit(vector<y2node> seg, vector<y2node> ar, int node, int start, int end);
y1node seginit(vector<y1node> seg, vector<y1node> ar, int node, int start, int end);
x2node seginit(vector<x2node> seg, vector<x2node> ar, int node, int start, int end);
x1node seginit(int node, int start, int end);
y2node query(vector<y2node> seg,int node, int start, int end, int left, int right);
y1node query(vector<y1node> seg,int node, int start, int end, int left, int right);
x2node query(vector<x2node> seg,int node, int start, int end, int left, int right);
x1node query(int node, int start, int end, int left, int right);

y2node combine (y2node a,y2node b)
{
    y2node r;
    for (int i=0;i<16;i++) r.arr[i]=a.arr[i]+b.arr[i];
    r.x1 = a.x1 + b.x1;
    r.x2 = a.x2 + b.x2;
    r.y1 = a.y1 + b.y1;
    r.y2 = a.y2 + b.y2;
    r.x1y1 = a.x1y1 + b.x1y1;
    r.x2y1 = a.x2y1 + b.x2y1;
    r.x1y2 = a.x1y2 + b.x1y2;
    r.x2y2 = a.x2y2 + b.x2y2;
    return r;
}
y1node combine (y1node a,y1node b)

{
    y1node r;
    for (int i=0;i<16;i++) r.arr[i]=a.arr[i]+b.arr[i];
    if (t==-1)
    {
        r.ar = a.ar;
        r.n = a.n+b.n;
        for (int i=0;i<b.ar.size();i++) r.ar.push_back(b.ar[i]); 
        sort(r.ar.begin(),r.ar.end()); 
        if (r.n>0) seginit(r.seg,r.ar,1,0,r.n-1);
    }
    return r;
}

x2node combine (x2node a,x2node b)
{
    x2node r;
    for (int i=0;i<16;i++) r.arr[i]=a.arr[i]+b.arr[i];
    if (t==-1)
    {
        r.ar = a.ar;
        r.n = a.n+b.n;
        for (int i=0;i<b.ar.size();i++) r.ar.push_back(b.ar[i]); 
        sort(r.ar.begin(),r.ar.end()); 
        if (r.n>0) seginit(r.seg,r.ar,1,0,r.n-1);
    }
    return r;
}

x1node combine (x1node a,x1node b)
{
    x1node r;
    for (int i=0;i<16;i++) r.arr[i]=a.arr[i]+b.arr[i];
    if (t==-1)
    {
        r.ar = a.ar;
        r.n = a.n+b.n;
        for (int i=0;i<b.ar.size();i++) r.ar.push_back(b.ar[i]); 
        sort(r.ar.begin(),r.ar.end()); 
        if (r.n>0) seginit(r.seg,r.ar,1,0,r.n-1);
    }
    return r;
}

void y1init(y1node &a)
{
    y2node b;
    b.x1=a.x1;
    b.x2=a.x2;
    b.y1=a.y1;
    b.y2=a.y2;
    b.x1y1=a.x1y1;
    b.x1y2=a.x1y2;
    b.x2y1=a.x2y1;
    b.x2y2=a.x2y2;
    b.n=1;
    for (int i =0; i<16; i++) b.arr[i]=0;
    a.ar.push_back(b);
}

void x2init(x2node &a)
{
    y1node b;
    b.x1=a.x1;
    b.x2=a.x2;
    b.y1=a.y1;
    b.y2=a.y2;
    b.x1y1=a.x1y1;
    b.x1y2=a.x1y2;
    b.x2y1=a.x2y1;
    b.x2y2=a.x2y2;
    y1init(b);
    b.n=1;
    for (int i =0; i<16; i++) b.arr[i]=0;
    a.ar.push_back(b);
}

void x1init(x1node &a)
{
    x2node b;
    b.x1=a.x1;
    b.x2=a.x2;
    b.y1=a.y1;
    b.y2=a.y2;
    b.x1y1=a.x1y1;
    b.x1y2=a.x1y2;
    b.x2y1=a.x2y1;
    b.x2y2=a.x2y2;
    b.n=1;
    x2init(b);
    for (int i =0; i<16; i++) b.arr[i]=0;
    a.ar.push_back(b);
}

y2node seginit(vector<y2node> seg, vector<y2node> ar, int node, int start, int end)
{
    if (start == end) return seg[node] = ar[start];
    int mid = (start + end) / 2;
    return seg[node] = combine(seginit(seg,ar,node*2,start,mid),seginit(seg,ar,node*2+1,mid+1,end));
}

y1node seginit(vector<y1node> seg, vector<y1node> ar, int node, int start, int end)
{
    if (start == end) return seg[node] = ar[start];
    int mid = (start + end) / 2;
    return seg[node] = combine(seginit(seg,ar,node*2,start,mid),seginit(seg,ar,node*2+1,mid+1,end));
}

x2node seginit(vector<x2node> seg, vector<x2node> ar, int node, int start, int end)
{
    if (start == end) return seg[node] = ar[start];
    int mid = (start + end) / 2;
    return seg[node] = combine(seginit(seg,ar,node*2,start,mid),seginit(seg,ar,node*2+1,mid+1,end));
}

x1node seginit(int node, int start, int end)
{
    if (start == end) return seg[node] = ar[start];
    int mid = (start + end) / 2;
    return seg[node] = combine(seginit(node*2,start,mid),seginit(node*2+1,mid+1,end));
}

void init()
{
    for (int i=0;i<n;i++) x1init(ar[i]);
    sort(ar.begin(),ar.end());
    seg.resize(2*n + 1);
    seginit(1,0,n-1);
}

y2node nodeinit(y2node y)
{
    y.arr[0] = y.x2y2 + y.x1 * t + y.y1 * t + t * t; //(y2+t)(x2+t)
    y.arr[1] = y.x2 * t * 2 + y.x2 + 2 * t * t + t; //(x2+t)(2t+1)
    y.arr[2] = y.x2y2 - y.x2y1 - y.y1 * t + y.y2 * t; //(y2-y1)(x2+t)
    y.arr[3] = -y.x2y1 + (t + 1) * y.x2 + (t + 1 - y.y1) * t; //(t+1-y1)(x2+t)
    y.arr[4] = y.y2 * t * 2 + 2 * t * t + y.y2 + t; //(2t+1)(y2+t)
    y.arr[5] = 4 * t * t + 4 * t + 1; //(2t+1)(2t+1)
    y.arr[6] = y.y2 * t * 2 - y.y1 * t * 2 + y.y2 - y.y1; //(y2-y1)(2t+1)
    y.arr[7] = (t + 1 - y.y1) * (2 * t + 1); //(t+1-y1)(2t+1)
    y.arr[8] = y.x2y2 - y.x1y2 + y.x2 * t - y.x1 * t; //(y2+t)(x2-x1)
    y.arr[9] = y.x2 * t * 2 - y.x1 * t * 2 + y.x2 - y.x1; //(2t+1)(x2-x1)
    y.arr[10] = y.x2y2 + y.x1y1 - y.x1y2 - y.x2y1; //(y2-y1)(x2-x1)
    y.arr[11] = -y.x2y1 + y.x1y1 + (t + 1) * (y.x2 - y.x1); //(t + 1 -y1)(x2-x1)
    y.arr[12] = -y.x1y2 - y.x1 * t + (t + 1) * (y.y2 + t); //(y2+t)(t+1-x1)
    y.arr[13] = (2 * t + 1) * (t + 1 - y.x1); //(2t+1)(t+1-x1)
    y.arr[14] = -y.x1y2 + y.x1y1 + (t + 1) * (y.y2 - y.y1); //(y2-y1)(t + 1-x1)
    y.arr[15] = y.x1y1 - (t + 1) * y.y1 - (t + 1) * y.x1 + (t + 1) * (t + 1); //(t+1 - y1)(t+1-x1)
    return y;
}
y1node nodeinit(y1node x1)
{
    y1node r;
    y2node r1,r2,tm,tp;
    tm.y2 = -t;
    tp.y2 = t;
    int a = lower_bound(r.ar.begin(),r.ar.end(),tm) - r.ar.begin();
    int b = lower_bound(r.ar.begin(),r.ar.end(),tp) - r.ar.begin();
    if (n>0) r1=query(x1.seg,1,0,x1.n-1,0,a);
    for (int j=0;j<4;j++) for (int i=0;i<2;i++) r.arr[4*j+i]=r1.arr[4*j+i];
    a = upper_bound(r.ar.begin(),r.ar.end(),tm) - r.ar.begin();
    if (n>0) r2=query(x1.seg,1,0,x1.n-1,a,b);
    for (int j=0;j<4;j++) for (int i=2;i<4;i++) r.arr[4*j+i]=r2.arr[4*j+i];
    return r;
}

x2node nodeinit(x2node x1)
{
    x2node r;
    y1node r1,r2,tm,tp;
    tm.y1 = -t;
    tp.y1 = t;
    int a = lower_bound(r.ar.begin(),r.ar.end(),tm) - r.ar.begin();
    int b = lower_bound(r.ar.begin(),r.ar.end(),tp) - r.ar.begin();
    if (n>0) r1=query(x1.seg,1,0,x1.n-1,0,a);
    for (int j=0;j<4;j++) for (int i=0;i<2;i++) r.arr[4*j+i]=r1.arr[4*j+i];
    a = upper_bound(r.ar.begin(),r.ar.end(),tm) - r.ar.begin();
    if (n>0) r2=query(x1.seg,1,0,x1.n-1,a,b);
    for (int j=0;j<4;j++) for (int i=2;i<4;i++) r.arr[4*j+i]=r2.arr[4*j+i];
    return r;
}

x1node nodeinit(x1node x1)
{
    x1node r;
    x2node r1,r2,tm,tp;
    tm.x2 = -t;
    tp.x2 = t;
    int a = lower_bound(r.ar.begin(),r.ar.end(),tm) - r.ar.begin();
    int b = lower_bound(r.ar.begin(),r.ar.end(),tp) - r.ar.begin();
    if (n>0) r1=query(x1.seg,1,0,x1.n-1,0,a);
    for (int j=0;j<2;j++) for (int i=0;i<4;i++) r.arr[8*j+i]=r1.arr[8*j+i];
    a = upper_bound(r.ar.begin(),r.ar.end(),tm) - r.ar.begin();
    if (n>0) r2=query(x1.seg,1,0,x1.n-1,a,b);
    for (int j=0;j<2;j++) for (int i=4;i<8;i++) r.arr[8*j+i]=r2.arr[8*j+i];
    return r;
}

y2node query(vector<y2node> seg,int node, int start, int end, int left, int right)
{
    y2node I;
    if (left > end || right < start) return I;
    if (left <= start && end <= right) return nodeinit(seg[node]);
    int mid = (start + end)/2;
    return combine(query(seg,node*2,start,mid,left,right),query(seg,node*2+1,mid+1,end,left,right));
}

y1node query(vector<y1node> seg,int node, int start, int end, int left, int right)
{
    y1node I;
    if (left > end || right < start) return I;
    if (left <= start && end <= right) return nodeinit(seg[node]);
    int mid = (start + end)/2;
    return combine(query(seg,node*2,start,mid,left,right),query(seg,node*2+1,mid+1,end,left,right));
}

x2node query(vector<x2node> seg,int node, int start, int end, int left, int right)
{
    x2node I;
    if (left > end || right < start) return I;
    if (left <= start && end <= right) return nodeinit(seg[node]);
    int mid = (start + end)/2;
    return combine(query(seg,node*2,start,mid,left,right),query(seg,node*2+1,mid+1,end,left,right));
}

x1node query(int node, int start, int end, int left, int right)
{
    x1node I;
    if (left > end || right < start) return I;
    if (left <= start && end <= right) return nodeinit(seg[node]);
    int mid = (start + end)/2;
    return combine(query(node*2,start,mid,left,right),query(node*2+1,mid+1,end,left,right));
}

long long result()
{
    x1node r1,r2,tm,tp;
    tm.x1 = -t;
    tp.x1 = t;
    int a = lower_bound(ar.begin(),ar.end(),tm) - ar.begin();
    int b = lower_bound(ar.begin(),ar.end(),tp) - ar.begin();
    long long r=0;
    if (n>0) r1=query(1,0,n-1,0,a);
    for (int i=0;i<8;i++) r=r1.arr[i];
    a = upper_bound(ar.begin(),ar.end(),tm) - ar.begin();
    if (n>0) r2=query(1,0,n-1,a,b);
    for (int i=8;i<16;i++) r=r2.arr[i];
    return r;
}

int main(void)
{
    cin >> n;
    x1node a;
    for (int i=0;i<n;i++)
    {
        cin >> a.x1 >> a.y1 >> a.x2 >> a.y2;
        a.x1y1 = a.x1*a.y1;
        a.x1y2 = a.x1*a.y2;
        a.x2y1 = a.x2*a.y1;
        a.x2y2 = a.x2*a.y2;
        a.n=1;
        for (int i=0; i<16; i++)  a.arr[i] = 0;
        ar.push_back(a);
    }
    init(); 
    cin >> m;
    for (int i=0;i<m;i++)
    {
        cin >> t;
        cout << result() << endl;
    }
}