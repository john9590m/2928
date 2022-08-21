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
    long long arr[16];
    bool operator< (const x2node &a) const
    {
        return y<a.y;
    }
};

struct x1node{
    long long x=0,n=0;
    long long arr[16];
    vector<x2node> seg;
    bool operator< (const x1node &a) const
    {
        return x<a.x;
    }
};


vector<x1node> seg,ar,seg1,ar1;
long long arr[16];
long long m,t=-1;
int n;

long long zz=0;

x2node query(vector<x2node> seg,int node, int start, int end, int left, int right);
x1node query(int node, int start, int end, int left, int right);



void x1init(x1node &a,long long x,long long y)
{
    x2node b;
    a.n=1;
    for (int i =0; i<16; i++) b.arr[i]=0;
    b.n=1;
    b.x=x;
    b.y=y;
    b.xy=x*y;
    a.seg.resize(1);
    a.seg.push_back(b);
}


x2node combine (x2node a,x2node b)
{
    x2node r;
    for (int i=0;i<16;i++) r.arr[i]=a.arr[i]+b.arr[i];
    if (t==-1)
    {
        r.n=a.n+b.n;
        r.x=a.x+b.x;
        r.y=a.y+b.y;
        r.xy=a.xy+b.xy;
    }
    return r;
}

x1node combine (x1node a,x1node b)
{
    x1node r;
    vector<x2node> ar;
    for (int i=0;i<16;i++) r.arr[i]=a.arr[i]+b.arr[i];
    if (t==-1)
    {
        for (int i=0;i<a.n;i++) ar.push_back(a.seg[a.n+i]);
        for (int i=0;i<b.n;i++) ar.push_back(b.seg[b.n+i]);
        r.n = a.n+b.n;
        sort(ar.begin(),ar.end()); 
        r.seg.resize(2*r.n);
        int pow=1,i;
        for (i=0;r.n>pow;i++) pow*=2;
        for (i=0;pow+i<2*r.n;i++) r.seg[pow+i] = ar[i];
        for (int j=0;i+j<r.n;j++) r.seg[r.n+j] = ar[i+j];
        for (i=r.n-1;i>=0;i--)
        {
            if (2*i+1<=2*r.n-1) r.seg[i] = combine(r.seg[2*i],r.seg[2*i+1]);
            else r.seg[i] = r.seg[2*i];
        }
        ar.clear();
    }
    return r;
}

void init()
{
    sort(ar.begin(),ar.end());
    seg.resize(2*n);
    int pow = 1;
    for (int i=0;n>pow;i++) pow *=2;
    int i;
    for (i=0;pow+i<2*n;i++) seg[pow+i] = ar[i];
    for (int j=0;i+j<n;j++) seg[n+j] = ar[i+j];
    for (i=n-1; i>=0;i--)
    { 
        if (2*i+1<=2*n-1) seg[i] = combine(seg[2*i],seg[2*i+1]);
        else seg[i] = seg[2*i];
    }
}

void init1()
{
    sort(ar1.begin(),ar1.end());
    seg1.resize(2*n);
    int pow = 1;
    for (int i=0;n>pow;i++) pow *=2;
    int i;
    for (i=0;pow+i<2*n;i++) seg1[pow+i] = ar1[i];
    for (int j=0;i+j<n;j++) seg1[n+j] = ar1[i+j];
    for (i=n-1; i>=0;i--)
    { 
        if (2*i+1<=2*n-1) seg1[i] = combine(seg1[2*i],seg1[2*i+1]);
        else seg1[i] = seg1[2*i];
    }
}

x2node nodeinit(x2node r)
{
    x1.arr[0] = 4*r.n*t*t + 4*r.n*t + r.n;
    x1.arr[1] = 
    x1.arr[2]
    x1.arr[3]
    return r;
}

x1node nodeinit(x1node x1)
{
    x1node r;
    x2node r1,r2,tm,tp;
    for (int i=0;i<16;i++)
    {
        r.arr[i] = 0;
        r1.arr[i]=0;
        r2.arr[i]=0;
    }
    if (x1.n == 0) return r;
    tm.x2 = -t;
    tp.x2 = t;
    int a,b;
    int pow = 1;
    for (int m=0;x1.n>pow;m++) pow*=2;
    if(x1.n == pow) 
    {
        if (x1.seg[2*x1.n-1] < tm) a = x1.n;
        else a = lower_bound(&x1.seg[x1.n],&x1.seg[2*x1.n-1],tm) - &x1.seg[x1.n];
        if (x1.seg[2*x1.n-1] < tp) b = x1.n - 1;
        else b = lower_bound(&x1.seg[x1.n],&x1.seg[2*x1.n-1],tp) - &x1.seg[x1.n] - 1;
    }
    else
    {
        if (x1.seg[pow - 1] < tm) a = x1.n;
        else if (x1.seg[2*x1.n-1]<tm) a = lower_bound(&x1.seg[x1.n], &x1.seg[pow - 1],tm) - &x1.seg[pow-x1.n];
        else a = lower_bound(&x1.seg[pow], &x1.seg[2*x1.n-1],tm) - &x1.seg[pow];
        if (x1.seg[pow - 1] < tp) b = x1.n - 1;
        else if (x1.seg[2*x1.n-1]<tp) b = lower_bound(&x1.seg[x1.n],&x1.seg[pow - 1],tp) - &x1.seg[pow-x1.n] - 1;
        else b = lower_bound(&x1.seg[pow],&x1.seg[2*x1.n-1],tp) - &x1.seg[pow] - 1;
    }
    if (x1.n>0 && b>=a) r1=query(x1.seg,1,0,x1.n-1,a,b);
    b++;
    if (x1.n>0&&x1.n-1>=b) r2=query(x1.seg,1,0,x1.n-1,b,x1.n-1);
    for (int j=0;j<2;j++) for (int i=0;i<4;i++) r.arr[8*j+i]=r1.arr[8*j+i];
    for (int j=0;j<2;j++) for (int i=4;i<8;i++) r.arr[8*j+i]=r2.arr[8*j+i];
    return r;
}


x2node query(vector<x2node> seg,int node, int start, int end, int left, int right)
{
    x2node I;
    if (left > end || right < start)     
    {
        for (int i=0;i<16;i++) I.arr[i] = 0;
        return I;
    }
    if (left <= start && end <= right) return nodeinit(seg[node]);
    int mid = (start + end)/2;
    return combine(query(seg,node*2,start,mid,left,right),query(seg,node*2+1,mid+1,end,left,right));
}

x1node query(int node, int start, int end, int left, int right)
{
    x1node I;
    if (left > end || right < start) 
    {
        for (int i=0;i<16;i++) I.arr[i] = 0;
        return I;
    }
    if (left <= start && end <= right) return nodeinit(seg[node]);
    int mid = (start + end)/2;
    return combine(query(node*2,start,mid,left,right),query(node*2+1,mid+1,end,left,right));
}

long long result()
{
    x1node r1,r2,tm,tp;
    int a,b;
    tm.x1 = -t;
    tp.x1 = t;
    for (int i=0;i<16;i++)
    {
        r1.arr[i]=0;
        r2.arr[i]=0;
    }
    int pow = 1;
    for (int m=0;n>pow;m++) pow*=2;
    long long r=0;
    if(n == pow) 
    {
        if (seg[2*n-1] < tm) a = n - 1;
        else a = lower_bound(&seg[n],&seg[2*n-1],tm) - &seg[n] - 1;
        if (seg[2*n-1].x1 <=tp.x1) b = n - 1;
        else b = upper_bound(&seg[n],&seg[2*n-1],tp) - &seg[n] - 1;
    }
    else
    {
        if (seg[pow-1]<tm) a = n-1;
        else if (seg[2*n-1]<tm) a = lower_bound(&seg[n], &seg[pow - 1],tm) - &seg[pow-n] - 1;
        else a = lower_bound(&seg[pow], &seg[2*n-1],tm) - &seg[pow] - 1;
        if (seg[pow-1].x1 <= tp.x1) b = n-1;
        else if (seg[2*n-1].x1<=tp.x1) b = upper_bound(&seg[n],&seg[pow - 1],tp) - &seg[pow-n] - 1;
        else b = upper_bound(&seg[pow],&seg[2*n-1],tp) - &seg[pow] - 1;
    }
    if (n>0&&a>=0) r1=query(1,0,n-1,0,a);
    a++;
    if (n>0&&b>=a) r2=query(1,0,n-1,a,b);
    for (int i=0;i<8;i++) r+=r1.arr[i];
    for (int i=8;i<16;i++) r+=r2.arr[i];
    return r;
}

int main(void)
{
    cin >> n;
    x1node *a;
    clock_t start = clock();
    long long x1,x2,y1,y2;
    for (int i=0;i<n;i++)
    {
        a = new x1node();
        cin >> x1 >> y1 >> x2 >> y2;
        for (int i=0; i<16; i++)  a->arr[i] = 0;
        x1init(*a,x1,y1);
        ar.push_back(*a);
        delete a;
        a = new x1node();
        x1init(*a,x2,y2);
        ar.push_back(*a);
        delete a;
        x1init(*a,x1,y2);
        ar1.push_back(*a);
        delete a;
        a = new x1node();
        x1init(*a,x2,y1);
        ar1.push_back(*a);
        delete a;
    }
    init();
    init1();
    cin >> m;
    for (int i=0;i<m;i++)
    {
        cin >> t;
        cout << result() << endl;
    }
}
