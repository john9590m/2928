#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

struct node
{
    long long var=0;
    long long tvar=0;
    int n=1;
    node operator+= (node &a)
    {
        var += a.var;
        tvar += a.tvar;
        return *this;
    }
};

int n,m;
int x[4];
long long seg[2700010];
int ten=1000000;
int cap;

long long query(int start,int end)
{
    long long result = 0;
    start += cap;
    end += cap;
    for (int i=start;i<=end;i++)
    {
        for (int j=i;j>0;j/=2) result += seg[j];
    }
    return result;
}

long long update(int start, int end, node data)
{
    start += cap;
    end += cap;
    int s = start;
    int e = end;
    int n = 1;
    for (; s<e; s/=2, e/=2)
    {
        if(s%2) seg[s++] += n*(2*(s*n-start)*data.tvar + (n-1)* data.tvar)/2;
        if (!(e%2)) seg[e--] += n*(2*(e*n-start)*data.tvar + (n-1)* data.tvar)/2;
        n*=2;
    }
    if (s==e) seg[s] += n*(2*(s*n-start)*data.tvar + (n-1)* data.tvar)/2;
    return n*(2*(end*n-start)*data.tvar + (n-1)* data.tvar)/2;
}
node getval(int t)
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
                    result.var = x[2]+t + t - x[0] + 1;
                }
            }
            else
            {
                if(x[3]<t) result.var= x[2]+t + t - x[0] + 1;
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

long long getnode(int t,long long a)
{
    long long result;
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
    int x1,x2,y1,y2;
    vector<int> temp;
    node data;
    for (cap=1;cap<ten;cap*=2);
    for (int i=0;i<n;i++)
    {
        long long count = 0;
        cin >> x[0] >> x[1] >> x[2] >> x[3]; //x1 y1 x2 y2 
        for (int k=0;k<4;k++) temp.push_back(abs(x[k]));
        sort(temp.begin(),temp.end());
        count += getnode(0,count);
        if (temp[0]>1) count+=update(1,temp[0]-1,getval(1));
        for (int j=0;j<3;j++)
        {
            if ((j==0 && temp[j]>0) || (j>0 && temp[j]>temp[j-1])) count += getnode(temp[j],count);
            if (temp[j+1]-temp[j]>1) count += update(temp[j]+1,temp[j+1]-1,getval(temp[j]));
        }
        if (temp[3]>temp[2]) count+=getnode(temp[3],count);
        temp.clear();
    }
    cin >> m;
    int last_t = 0;
    long long accumulate = 0;
    for (int i=0;i<m;i++)
    {
        int t;
        cin >> t;
        accumulate += query(last_t,t);
        cout << accumulate << endl;
        last_t = t;
    }
}