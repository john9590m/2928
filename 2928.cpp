#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct y2node{
    long long x1=0,x2=0,y1=0,y2=0,x1y1=0,x1y2=0,x2y1=0,x2y2=0;
    int n=0;
    long long arr[16];
    bool operator< (const y2node &a) const
    {
        return y2<a.y2;
    }
};

struct y1node{
    long long y1=0;
    int n=0;
    long long arr[16];
    vector<y2node> seg;
    bool operator< (const y1node &a) const
    {
        return y1<a.y1;
    }
};

struct x2node{
    long long x2=0;
    int n=0;
    long long arr[16];
    vector<y1node> seg;
    bool operator< (const x2node &a) const
    {
        return x2<a.x2;
    }
};

struct x1node{
    long long x1=0,n=0;
    long long arr[16];
    vector<x2node> seg;
    bool operator< (const x1node &a) const
    {
        return x1<a.x1;
    }
};


vector<x1node> seg,ar;
long long arr[16];
long long m,t=-1;
int n;

y2node query(vector<y2node> seg,int node, int start, int end, int left, int right);
y1node query(vector<y1node> seg,int node, int start, int end, int left, int right);
x2node query(vector<x2node> seg,int node, int start, int end, int left, int right);
x1node query(int node, int start, int end, int left, int right);


void y1init(y1node &a,long long x1, long long x2,long long y1,long long y2)
{
    y2node b;
    a.seg.push_back(b);
    b.x1=x1;
    b.x2=x2;
    b.y1=y1;
    b.y2=y2;
    b.x1y1=x1*y1;
    b.x1y2=x1*y2;
    b.x2y1=x2*y1;
    b.x2y2=x2*y2;
    b.n=1;
    for (int i =0; i<16; i++) b.arr[i]=0;
    a.seg.push_back(b);
}

void x2init(x2node &a,long long x1, long long x2,long long y1,long long y2)
{
    y1node b;
    a.seg.push_back(b);
    b.y1=y1;
    y1init(b,x1,x2,y1,y2);
    b.n=1;
    for (int i =0; i<16; i++) b.arr[i]=0;
    a.seg.push_back(b);
}

void x1init(x1node &a,long long x1, long long x2,long long y1,long long y2)
{
    x2node b;
    a.seg.push_back(b);
    b.x2=x2;
    b.n=1;
    x2init(b,x1,x2,y1,y2);
    for (int i =0; i<16; i++) b.arr[i]=0;
    a.seg.push_back(b);
}

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
    r.n = a.n + b.n;
    return r;
}
y1node combine (y1node a,y1node b)
{
    y1node r;
    vector<y2node> ar;
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
        for (int j=0;i+j<r.n;j++) r.seg[n+j] = ar[i+j];
        for (i=r.n-1;i>=0;i--)
        {
            if (2*i+1<=2*r.n-1) r.seg[i] = combine(r.seg[2*i],r.seg[2*i+1]);
            else r.seg[i] = r.seg[2*i];
        }
        ar.clear();
    }
    return r;
}

x2node combine (x2node a,x2node b)
{
    x2node r;
    vector<y1node> ar;
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
        for (int j=0;i+j<r.n;j++) r.seg[n+j] = ar[i+j];
        for (i=r.n-1;i>=0;i--)
        {
            if (2*i+1<=2*r.n-1) r.seg[i] = combine(r.seg[2*i],r.seg[2*i+1]);
            else r.seg[i] = r.seg[2*i];
        }
        ar.clear();
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
        for (int j=0;i+j<r.n;j++) r.seg[n+j] = ar[i+j];
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

y2node nodeinit(y2node y)
{
	long long n = y.n;
    //n이랑 상관이 있어야한다
    y.arr[0] = n*t*t+t*y.x2+t*y.y2+2*n*t+y.x2y2+y.x2+y.y2+n;
    //(y2+t+1)(x2+t+1)
    y.arr[1] = 2*n*t*t+2*t*y.x2+3*t*n+y.x2+n;
    //(x2+t+1)(2t+1)
    y.arr[2] = -t*y.y1+t*y.y2+n*t-y.x2y1+y.x2y2+y.x2-y.y1+y.y2+n; 
    //(y2-y1+1)(x2+t+1)
    y.arr[3] = n*t*t+t*y.x2-t*y.y1+2*n*t-y.x2y1+y.x2-y.y1+n;
    //(t+1-y1)(x2+t+1)
    y.arr[4] = 2*n*t*t + 2*t*y.y2 + 3*n*t +y.y2 + n;
    //(2t+1)(y2+t+1)
    y.arr[5] = 4*n*t*t + 4*n*t + n;
    //(2t+1)(2t+1)
    y.arr[6] = -2*t*y.y1 + 2*t*y.y2 + 2*n*t - y.y1 + y.y2 + n; 
    //(y2-y1+1)(2t+1)
    y.arr[7] = 2*n*t*t - 2*t*y.y1 + 3*n*t - y.y1 + n; 
    //(t+1-y1)(2t+1)
    y.arr[8] = -t*y.x1 + t*y.x2 + n*t - y.x1y2 + y.x2y2 - y.x1 + y.x2 + y.y2 + n;//(y2+t+1)(x2-x1+1)
    y.arr[9] = -2*t*y.x1 + 2*t*y.x2 + 2*n*t - y.x1 + y.x2 + n; //(2t+1)(x2-x1+1)
    y.arr[10] = y.x1y1-y.x1y2-y.x2y1 + y.x2y2 - y.x1 + y.x2 - y.y1 + y.y2 + n; //(y2-y1+1)(x2-x1+1)
    y.arr[11] = -t*y.x1 + t*y.x2 + n*t + y.x1y1 - y.x2y1 - y.x1 + y.x2 - y.y1 + n; //(t + 1 -y1)(x2-x1+1)
    y.arr[12] = n*t*t - t*y.x1 + t*y.y2 + n*t - y.x1y2 - y.x1 + y.y2 + n; //(y2+t+1)(t+1-x1)
    y.arr[13] = 2*n*t*t - 2*t*y.x1 + 3*n*t - y.x1 + n; //(2t+1)(t+1-x1)
    y.arr[14] = -t*y.y1 + y.x1y1 - y.y1 + t*y.y2 - y.x1y2 + y.y2 + n*t - y.x1 + n; //(y2-y1+1)(t + 1-x1)
    y.arr[15] = n*t*t - t*y.x1 - t*y.y1 + 2*n*t + y.x1y1 - y.x1 - y.y1 + n; //(t+1 - y1)(t+1-x1)  
    return y;
}
y1node nodeinit(y1node x1)
{
    y1node r;
    y2node r1,r2,tm,tp;
    for (int i=0;i<16;i++)
    {
        r.arr[i] = 0;
        r1.arr[i]=0;
        r2.arr[i]=0;
    }
    if (x1.n == 0) return r;
    tm.y2 = -t;
    tp.y2 = t;
    int pow = 1;
    for (int m=0;x1.n>pow;m++) pow*=2;
    int a,b;
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
    if (x1.n>0 && x1.n-1 >= b) r2=query(x1.seg,1,0,x1.n-1,b,x1.n-1);
    for (int j=0;j<8;j++) r.arr[2*j]=r1.arr[2*j];
    for (int j=0;j<8;j++) r.arr[2*j+1]=r2.arr[2*j+1];
    return r;
}

x2node nodeinit(x2node x1)
{
    x2node r;
    y1node r1,r2,tm,tp;
    for (int i=0;i<16;i++)
    {
        r.arr[i] = 0;
        r1.arr[i]=0;
        r2.arr[i]=0;
    }
    if (x1.n == 0) return r;
    tm.y1 = -t;
    tp.y1 = t;
    int pow = 1;
    for (int m=0;x1.n>pow;m++) pow*=2;
    int a,b;
    if(x1.n == pow) 
    {
        if (x1.seg[2*x1.n-1] < tm) a = x1.n - 1;
        else a = lower_bound(&x1.seg[x1.n],&x1.seg[2*x1.n-1],tm) - &x1.seg[x1.n] - 1;
        if (x1.seg[2*x1.n-1].y1 <=tp.y1) b = x1.n - 1;
        else b = upper_bound(&x1.seg[x1.n],&x1.seg[2*x1.n-1],tp) - &x1.seg[x1.n] - 1;
    }
    else
    {
        if (x1.seg[pow - 1] < tm) a = x1.n - 1;
        else if (x1.seg[2*x1.n-1]<tm) a = lower_bound(&x1.seg[x1.n], &x1.seg[pow - 1],tm) - &x1.seg[pow-x1.n] - 1;
        else a = lower_bound(&x1.seg[pow], &x1.seg[2*x1.n-1],tm) - &x1.seg[pow] - 1;
        if (x1.seg[pow - 1].y1 <= tp.y1) b = x1.n - 1;
        else if (x1.seg[2*x1.n-1].y1<=tp.y1) b = upper_bound(&x1.seg[x1.n],&x1.seg[pow - 1],tp) - &x1.seg[pow-x1.n] - 1;
        else b = upper_bound(&x1.seg[pow],&x1.seg[2*x1.n-1],tp) - &x1.seg[pow] - 1;
    }
    if (x1.n>0 && a>=0) r1=query(x1.seg,1,0,x1.n-1,0,a);
    a++;
    if (x1.n>0 && b>=a) r2=query(x1.seg,1,0,x1.n-1,a,b);
    for (int j=0;j<4;j++) for (int i=0;i<2;i++) r.arr[4*j+i]=r1.arr[4*j+i];
    for (int j=0;j<4;j++) for (int i=2;i<4;i++) r.arr[4*j+i]=r2.arr[4*j+i];
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

y2node query(vector<y2node> seg,int node, int start, int end, int left, int right)
{
    y2node I;
    if (left > end || right < start)
    {
        for (int i=0;i<16;i++) I.arr[i] = 0;
        return I;
    }
    if (left <= start && end <= right) return nodeinit(seg[node]);
    int mid = (start + end)/2;
    return combine(query(seg,node*2,start,mid,left,right),query(seg,node*2+1,mid+1,end,left,right));
}

y1node query(vector<y1node> seg,int node, int start, int end, int left, int right)
{
    y1node I;
    if (left > end || right < start)
    {
        for (int i=0;i<16;i++) I.arr[i] = 0;
        return I;
    }
    if (left <= start && end <= right) return nodeinit(seg[node]);
    int mid = (start + end)/2;
    return combine(query(seg,node*2,start,mid,left,right),query(seg,node*2+1,mid+1,end,left,right));
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
        a->n=1;
        a->x1 = x1;
        for (int i=0; i<16; i++)  a->arr[i] = 0;
        x1init(*a,x1,x2,y1,y2);
        ar.push_back(*a);
    } 
    init(); 
    cin >> m;
    for (int i=0;i<m;i++)
    {
        cin >> t;
        cout << result() << endl;
    }
}
