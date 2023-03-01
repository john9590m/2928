#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

struct node
{
    long long var=0;
    long long tvar=0;
    long long n=1;
    node operator+= (node &a)
    {
        var += a.var;
        tvar += a.tvar;
        return *this;
    }
};

long long n,m;
long long x[4];
long long seg[2700010];
long long seg1[2700010];
long long ten=1000000;
long long cap;

long long query(long long start,long long end)
{
    long long result = 0,last=0;
    start += cap;
    end += cap;
    for (long long i=start;i<=end;i++)
    {
        long long n=1;
        long long a=0;
        for (long long j=i;j>0;j/=2)
        {
            result += seg[j];
            result += seg1[j]*a;
            if (j%2) a+=n;
            n*=2;
        }
        last = result;
    }
    return result;
}

long long update(long long start, long long end, node data)
{
    start += cap;
    end += cap;
    long long s = start;
    long long e = end;
    long long n = 1;
    long long svalue = 0,evalue = end-start,result = 0;
    for (; s<e; s/=2, e/=2)
    {
        if(s%2) 
        {
            seg1[s] += data.tvar;
            seg[s++] += data.var + svalue * data.tvar;
            result += (svalue*data.tvar + data.var) * n + data.tvar * n * (n-1) / 2;
            svalue+=n;
        }
        if (!(e%2))
        {
            seg1[e] += data.tvar;
            seg[e--] += data.var + evalue * data.tvar;
            result += (evalue*data.tvar + data.var) * n + data.tvar * n * (n-1) / 2;
            evalue-=2*n;
        }
        else evalue-=n;
        n*=2;
    }
    if (s==e)
    {
        seg1[s] += data.tvar;
        seg[s] += data.var + svalue * data.tvar;
        result += (svalue*data.tvar + data.var) * n + data.tvar * n * (n-1) / 2;
    }
    return result;
}
node getval(long long t)
{
    node result;
    if (x[0] > t || x[1] > t|| x[2] < -t|| x[3] < -t) return result;
    if (x[0] > -t)
    {
        if (x[1]>-t)
        {
            if(x[2]<t)
            {
                if(x[3]<t);
                else result.var = x[2]-x[0]+1;
            }
            else
            {
                if(x[3]<t) result.var=x[3]-x[1]+1;
                else 
                {
                    result.tvar = 2;
                    result.var = t - x[0] + t - x[1] + 1; //
                }
            }
        }
        else
        {
            if(x[2]<t)
            {
                if(x[3]<t) result.var = x[2]-x[0]+1;
                else result.var = 2*(x[2]-x[0]+1);
            }
            else
            {
                if(x[3]<t)
                {
                    result.tvar = 2;
                    result.var = t - x[0] + x[3] + t + 1;
                }
                else 
                {
                    result.tvar = 4;
                    result.var = 2*(t-x[0]) + t + t + 1;
                }
            }
        }
    }
    else
    {
        if (x[1]>-t)
        {
            if(x[2]<t)
            {
                if(x[3]<t) result.var = x[3]-x[1]+1;
                else
                {
                    result.tvar = 2;
                    result.var = x[2]+t + t - x[1] + 1;
                }
            }
            else
            {
                if(x[3]<t) result.var= 2*(x[3] - x[1] + 1);
                else 
                {
                    result.tvar = 4;
                    result.var = 2*(t-x[1]) + t + t  + 1;
                }
            }
        }
        else
        {
            if(x[2]<t)
            {
                if(x[3]<t) 
                {
                    result.tvar = 2;
                    result.var = x[2]+t + x[3] + t + 1;
                }
                else 
                {
                    result.tvar = 4;
                    result.var = 2*(x[2]+t) + t + t  + 1;
                }
            }
            else
            {
                if(x[3]<t)
                {
                    result.tvar = 4;
                    result.var = 2*(x[3]+t) + t + t  + 1;
                }
                else 
                {
                    result.tvar = 8;
                    result.var = 4*t-4;
                }
            }
        }
    }
    return result;
}

long long getnode(long long t,long long a)
{
    long long result;
    if (x[0] > t || x[1] > t|| x[2] < -t|| x[3] < -t) return 0;
    result = (min(x[2],t) - max(x[0],-t) +1)*(min(x[3],t)-max(x[1],-t)+1)-a;
    if (result>0) 
    { 
        seg[cap+t] += result;
        return result;
    }
    return 0;
}
int main(void)
{
    cin >> n;
    long long x1,x2,y1,y2;
    vector<long long> temp;
    node data;
    for (cap=1;cap<ten;cap*=2);
    for (long long i=0;i<n;i++)
    {
        long long count = 0;
        cin >> x[0] >> x[1] >> x[2] >> x[3]; //x1 y1 x2 y2 
        for (long long k=0;k<4;k++) temp.push_back(abs(x[k]));
        sort(temp.begin(),temp.end());
        count += getnode(0,count);
        if (temp[0]>1) count+=update(1,temp[0]-1,getval(1));
        for (long long j=0;j<3;j++)
        {
            if ((j==0 && temp[j]>0) || (j>0 && temp[j]>temp[j-1])) count += getnode(temp[j],count);
            if (temp[j+1]-temp[j]>1) count += update(temp[j]+1,temp[j+1]-1,getval(temp[j]+1));
        }
        if (temp[3]>temp[2]) count+=getnode(temp[3],count);
        temp.clear();
    }
    cin >> m;
    long long last_t = 0;
    long long accumulate = 0;
    for (long long i=0;i<m;i++)
    {
        long long t;
        cin >> t;
        accumulate += query(last_t,t);
        cout << accumulate << endl;
        last_t = t + 1;
    }
}