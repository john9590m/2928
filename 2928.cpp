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
    bool operator< (const x2node &a) const
    {
        return y<a.y;
    }
};

struct x1node{
    int x,n=0;
    vector<x2node> seg,ar;
    bool operator< (const x1node &a) const
    {
        return x<a.x;
    }
};


vector<x1node> seg,ar,seg1,ar1;
long long arr[4];
long long m,t=-1;
int n,capacity;

long long zz=0;

void query(vector<x2node> &seg,int node, int start, int end, int left, int right,long long* r);
void query(vector<x1node> &seg,int node, int start, int end, int left, int right,long long* r);

void x1init(x1node &a,long long x,long long y)
{
    x2node b;
    a.n=1;
    a.x = x;
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
    r.n=a.n+b.n;
    r.x=a.x+b.x;
    r.y=a.y+b.y;
    r.xy=a.xy+b.xy;
    return r;
}

void combine (x1node &a,x1node &b,x1node &r)
{
    int c;
    r.n = a.n+b.n;
    if(r.n==0) return;
    for (x2node i : a.ar) r.ar.push_back(i);
    for (x2node i : b.ar) r.ar.push_back(i);
    sort(r.ar.begin(),r.ar.end());
    for (c=1;c<r.n;c*=2);
    r.seg.resize(2*c);
    for (int i=0;i<r.n;i++) r.seg[c+i]=r.ar[i];
    for (int i=c-1;i>0;i--) r.seg[i] = combine(r.seg[i*2],r.seg[i*2+1]);
}

long long* nodeinit(x2node &r,long long* l)
{
    l[0] = 4*r.n*t*t + 4*r.n*t + r.n; //(2t+1)(2t+1)
    l[1] = 2*r.n*t*t - 2*t*r.y + 3*r.n*t -r.y + r.n; //(t-y+1)(2t+1)
    l[2] = 2*r.n*t*t - 2*t*r.x + 3*r.n*t -r.x + r.n; //(t-x+1)(2t+1)
    l[3] = (t+1)*(t+1)*r.n - r.x*(t+1) - r.y*(t+1) + r.xy; //(t-x+1)(t-y+1)
    return l;
}

void nodeinit(x1node &x1,long long* r)
{
    long long r1[4],r2[4],temp[4];
    x2node tm,tp;
    long long n = x1.n;
    int c,L,R;
    for (int i=0;i<4;i++)
    {
        r[i] = 0;
        r1[i]=0;
        r2[i]=0;
    }
    if (x1.n == 0) return;
    tm.y = -t;
    tp.y = t;
    int a,b;
    if (x1.ar[n-1] < tm) a = n - 1;
    else a = lower_bound(x1.ar.begin(),x1.ar.end(),tm) - x1.ar.begin() - 1;
    if (x1.ar[n-1].y <= tp.y) b = n - 1;
    else b = upper_bound(x1.ar.begin(),x1.ar.end(),tp) - x1.ar.begin() - 1;
    //clock_t start = clock();
    for (c=1;c<n;c*=2);
    L=0+c;
    R=a+c;
    if (x1.n>0&&a>=0) 
    {
        for(;L<R;L/=2,R/=2) 
        {
            for (int i=0;i<4;i++) temp[i]=0;
            if(L%2) nodeinit(x1.seg[L++],temp);
            if(!(R%2)) nodeinit(x1.seg[R--],temp);
            for (int i=0;i<4;i++) r1[i] += temp[i];
        }
        for (int i=0;i<4;i++) temp[i]=0;
        if (L==R) nodeinit(x1.seg[L],temp);
        for (int i=0;i<4;i++) r1[i] += temp[i];
    }
    a++;
    L=a+c;
    R=b+c;
    if (x1.n>0&&b>=a)
    {
        for(;L<R;L/=2,R/=2) 
        {
            for (int i=0;i<4;i++) temp[i]=0;
            if(L%2) nodeinit(x1.seg[L++],temp);
            if(!(R%2)) nodeinit(x1.seg[R--],temp);
            for (int i=0;i<4;i++) r1[i] += temp[i];
        }
        for (int i=0;i<4;i++) temp[i]=0;
        if (L==R) nodeinit(x1.seg[L],temp);
        for (int i=0;i<4;i++) r1[i] += temp[i];
    }
    //cout << (clock()-start)*100000000.0/CLOCKS_PER_SEC << endl << endl;
    for(int i=0;i<4;i++)
    {
        if(i%2==0) r[i] = r1[i];
        else r[i] = r2[i];
    }
    return;
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
          nodeinit(seg[node],r);
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
         nodeinit(seg[node],r);
         return;
    }
    int mid = (start + end)/2;
    long long a[4],b[4];
    query(seg, node*2,start,mid,left,right,a);
    query(seg,node*2+1,mid+1,end,left,right,b);
    for (int i=0;i<4;i++) r[i] = a[i]+b[i]; 
}

long long  result(vector<x1node> &seg,vector<x1node> &ar)
{
    clock_t start = clock();
    x1node tm,tp;
    long long r1[4],r2[4],temp[4];
    int a,b,L,R,c;
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
    for (c=1;c<n;c*=2);
    L=c;
    R=a+c;
    if (n>0&&a>=0)
    {
        for(;L<R;L/=2,R/=2) 
        {
            for (int i=0;i<4;i++) temp[i]=0;
            if(L%2) nodeinit(seg[L++],temp);
            if(!(R%2)) nodeinit(seg[R--],temp);
            for (int i=0;i<4;i++) r1[i] += temp[i];
        }
        for (int i=0;i<4;i++) temp[i]=0;
        if (L==R) nodeinit(seg[L],temp);
        for (int i=0;i<4;i++) r1[i] += temp[i];
    }
    a++;
    L=a+c;
    R=b+c;
    if (n>0&&b>=a)
    {
        for(;L<R;L/=2,R/=2) 
        {
            for (int i=0;i<4;i++) temp[i]=0;
            if(L%2) nodeinit(seg[L++],temp);
            if(!(R%2)) nodeinit(seg[R--],temp);
            for (int i=0;i<4;i++) r1[i] += temp[i];
        }
        for (int i=0;i<4;i++) temp[i]=0;
        if (L==R) nodeinit(seg[L],temp);
        for (int i=0;i<4;i++) r1[i] += temp[i];
    }
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
    for(capacity=1;capacity<n;capacity*=2);
    sort(ar.begin(),ar.end());
    seg.resize(2*capacity);
    for (int i=0;i<n;i++) seg[capacity+i]=ar[i];
    for (int i=capacity-1;i>0;i--) combine(seg[i*2],seg[i*2+1],seg[i]);
    sort(ar1.begin(),ar1.end());
    seg1.resize(2*capacity);
    for (int i=0;i<n;i++) seg1[capacity+i]=ar1[i];
    for (int i=capacity-1;i>0;i--) combine(seg1[i*2],seg1[i*2+1],seg1[i]);
    cin >> m;
    for (int i=0;i<m;i++)
    {
        cin >> t;
        cout << result(seg,ar) - result(seg1,ar1) << endl;
    }
}
