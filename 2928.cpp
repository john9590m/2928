#include <iostream>
#include <algorithm>
#include <vector>
#include <time.h>

using namespace std;

struct x2node{
    long long x=0;
    long long y=0;
    long long xy=0;
    int n=0;
    long long arr[4];
    bool operator< (const x2node &a) const
    {
        return y<a.y;
    }
};

struct x1node{
    long long x=0,n=0;
    long long arr[4];
    vector<x2node> seg,ar;
    bool operator< (const x1node &a) const
    {
        return x<a.x;
    }
};


vector<x1node> seg,ar,seg1,ar1;
long long arr[4];
long long m,t=-1;
int n;

long long zz=0;

void query(vector<x2node> &seg,int node, int start, int end, int left, int right,long long* r);
void query(vector<x1node> &seg,int node, int start, int end, int left, int right,long long* r);
x2node x2nodeinit(vector<x2node> &seg,vector<x2node> &ar, int node, int start, int end);
x1node x1nodeinit1(int node, int start, int end);
x1node x1nodeinit2(int node, int start, int end);




void x1init(x1node &a,long long x,long long y)
{
    x2node b;
    a.n=1;
    a.x = x;
    for (int i =0; i<4; i++) b.arr[i]=0;
    b.n=1;
    b.x=x;
    b.y=y;
    b.xy=x*y;
    a.ar.push_back(b);
    a.seg.resize(1);
    a.seg.push_back(b);
}


x2node combine (x2node &a,x2node &b)
{
    x2node r;
    for (int i=0;i<4;i++) r.arr[i]=a.arr[i]+b.arr[i];
    if (t==-1)
    {
        r.n=a.n+b.n;
        r.x=a.x+b.x;
        r.y=a.y+b.y;
        r.xy=a.xy+b.xy;
    }
    return r;
}

x2node x2nodeinit(vector<x2node> &seg,vector<x2node> &ar, int node, int start, int end)
{
    if(start == end) return seg[node] = ar[start];
    int mid = (start + end) / 2;
    x2node a = x2nodeinit(seg,ar,node*2,start,mid);
    x2node b = x2nodeinit(seg,ar,node*2+1,mid+1,end);
    return seg[node] = combine(a,b);
}

x1node combine (x1node &a,x1node &b)
{
    x1node r;
    for (int i=0;i<4;i++) r.arr[i]=a.arr[i]+b.arr[i];
    if (t==-1)
    {
        r.ar = a.ar;
        for (x2node i : b.ar) r.ar.push_back(i);
        r.n = a.n+b.n;
        sort(r.ar.begin(),r.ar.end()); 
        r.seg.resize(4*r.n);
        x2nodeinit(r.seg,r.ar,1,0,r.n-1);
    }
    return r;
}

x1node x1nodeinit1(int node, int start, int end)
{
    if(start == end) return seg[node] = ar[start];
    int mid = (start + end) / 2;
    x1node a =x1nodeinit1(node*2,start,mid);
    x1node b = x1nodeinit1(node*2+1,mid+1,end);
    return seg[node] = combine(a,b);
}


x1node x1nodeinit2(int node, int start, int end)
{
    if(start == end) return seg1[node] = ar1[start];
    int mid = (start + end) / 2;
    x1node a = x1nodeinit2(node*2,start,mid);
    x1node b = x1nodeinit2(node*2+1,mid+1,end);
    return seg[node] = combine(a,b);
}

long long* nodeinit(x2node &r)
{
    long long l[4];
    l[0] = 4*r.n*t*t + 4*r.n*t + r.n; //(2t+1)(2t+1)
    l[1] = 2*r.n*t*t - 2*t*r.y + 3*r.n*t -r.y + r.n; //(t-y+1)(2t+1)
    l[2] = 2*r.n*t*t - 2*t*r.x + 3*r.n*t -r.x + r.n; //(t-x+1)(2t+1)
    l[3] = (t+1)*(t+1)*r.n - r.x*(t+1) - r.y*(t+1) + r.xy; //(t-x+1)(t-y+1)
    return l;
}

long long* nodeinit(x1node &x1)
{
    long long r[4],r1[4],r2[4];
    x2node tm,tp;
    long long n = x1.n;
    for (int i=0;i<4;i++)
    {
        r[i] = 0;
        r1[i]=0;
        r2[i]=0;
    }
    if (x1.n == 0) return r;
    tm.y = -t;
    tp.y = t;
    int a,b;
    if (x1.ar[n-1] < tm) a = n - 1;
    else a = lower_bound(x1.ar.begin(),x1.ar.end(),tm) - x1.ar.begin() - 1;
    if (x1.ar[n-1].y <= tp.y) b = n - 1;
    else b = upper_bound(x1.ar.begin(),x1.ar.end(),tp) - x1.ar.begin() - 1;
    //clock_t start = clock();
    if (x1.n>0&&a>=0) query(x1.seg,1,0,x1.n-1,0,a,r1);
    a++;
    if (x1.n>0&&b>=a) query(x1.seg,1,0,x1.n-1,a,b,r2);
    //cout << (clock()-start)*100000000.0/CLOCKS_PER_SEC << endl << endl;
    for(int i=0;i<4;i++)
    {
        if(i%2==0) r[i] = r1[i];
        else r[i] = r2[i];
    }
    return r;
}


void query(vector<x2node> &seg,int node, int start, int end, int left, int right,long long* r)
{
    if (left > end || right < start)
    {
        for (int i=0;i<4;i++) r[i] = 0;   
        return;
    }
    if (left <= start && end <= right)
    {
          r = nodeinit(seg[node]);
          return;
    }
    int mid = (start + end)/2;
    long long a[4],b[4];
    query(seg,node*2,start,mid,left,right,a);
    query(seg,node*2+1,mid+1,end,left,right,b);
    for (int i=0;i<4;i++) r[i]=a[i]+b[i];
}

void query(vector<x1node> &seg,int node, int start, int end, int left, int right, long long* r)
{
    if (left > end || right < start) 
    {
        for (int i=0;i<4;i++) r[i] = 0;
        return;
    }
    if (left <= start && end <= right)
    {
         r = nodeinit(seg[node]);
         return;
    }
    int mid = (start + end)/2;
    long long a[4],b[4];
    query(seg, node*2,start,mid,left,right,a);
    query(seg,node*2+1,mid+1,end,left,right,b);
    for (int i=0;i<4;i++) r[i] = a[i]+b[i]; 
}

long long result(vector<x1node> &seg,vector<x1node> &ar)
{
    clock_t start = clock();
    x1node tm,tp;
    long long r1[4],r2[4];
    int a,b;
    tm.x = -t;
    tp.x = t;
    for (int i=0;i<4;i++)
    {
        r1[i]=0;
        r2[i]=0;
    }
    long long r=0;
    if (ar[n-1] < tm) a = n - 1;
    else a = lower_bound(ar.begin(),ar.end(),tm) - ar.begin() - 1;
    if (ar[n-1].x <= tp.x) b = n - 1;
    else b = upper_bound(ar.begin(),ar.end(),tp) - ar.begin() - 1;
    //cout << (clock()-start)*100000000/CLOCKS_PER_SEC << endl;
    if (n>0&&a>=0) query(seg,1,0,n-1,0,a,r1);
    a++;
    if (n>0&&b>=a) query(seg,1,0,n-1,a,b,r2);
    for (int i=0;i<2;i++) r += r1[i];
    for (int i=2;i<4;i++) r += r2[i];
    //cout << (clock()-start)*100000000/CLOCKS_PER_SEC << endl << endl;
    return r;
}

int main(void)
{
    ios_base :: sync_with_stdio(false); 
    cin.tie(NULL); 
    cout.tie(NULL);
    cin >> n;
    x1node *a;
    clock_t start = clock();
    long long x1,x2,y1,y2;
    for (int i=0;i<n;i++)
    {
        a = new x1node();
        cin >> x1 >> y1 >> x2 >> y2;
        for (int i=0; i<4; i++)  a->arr[i] = 0;
        x2++;
        y2++;
        x1init(*a,x1,y1);
        ar.push_back(*a);
        a = new x1node();
        x1init(*a,x2,y2);
        ar.push_back(*a);
        a = new x1node();
        x1init(*a,x1,y2);
        ar1.push_back(*a);
        a = new x1node();
        x1init(*a,x2,y1);
        ar1.push_back(*a);
    }
    n*=2;
    sort(ar.begin(),ar.end());
    seg.resize(4*n);
    x1nodeinit1(1,0,n-1);
    sort(ar1.begin(),ar1.end());
    seg1.resize(4*n);
    x1nodeinit2(1,0,n-1);
    cin >> m;
    for (int i=0;i<m;i++)
    {
        cin >> t;
        cout << result(seg,ar) - result(seg1,ar1) << endl;
    }
}
