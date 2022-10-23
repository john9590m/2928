#include <iostream>
#include <algorithm>
#include <vector>
#include <math.h>

using namespace std;

typedef struct node
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
node seg[2700010];
int ten=1000000;

long long calc (int idx)
{
    long long result = seg[idx].n*seg[idx].var;
    result += seg[idx].n*(seg[idx].n+1)/ 2 * seg[idx].tvar;
    return result;
}

long long query(int start,int end)
{
    long long result = 0;
    start += ten;
    end += ten;
    for (int i=start;i<=end;i++)
    {
        for (int j=i;j>0;j/=2) result += calc(j);
    }
    return result;
}

long long update(int start, int end, node data)
{
    start=abs(start);
    end=abs(end);
    start += ten;
    end += ten;
    int n = 1;
    for (; start<end; start/=2, end/=2)
    {
        data.n=n;
        if(start%2) seg[start++] += data;
        if (!(end%2)) seg[end--] += data;
        n*=2;
    }
    if (start==end) seg[start] += data;
    n = end - start + 1;
    return n*data.var + n*(n+1)/2 * data.tvar;
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
                    result.var = x[2]+ t + t - x[1] + 1;
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

void getnode(int t,long long a)
{
    node result;
    result.var = (min(x[2],t) - max(x[0],-t) +1)*(min(x[3],t)-max(x[1],-t)+1)-a;
    seg[ten+t] += result;
}
int main(void)
{
    cin >> n;
    int x1,x2,y1,y2;
    vector<int> temp;
    int cap;
    node data;
    for (cap=1;cap<ten;cap*=2);
    for(int i = cap+ten;i<cap*2;i++) seg[i].n = 0;
    for(int i = cap -1 ; i>0 ; i--) seg[i].n = seg[i*2].n+seg[i*2+1].n;
    for (int i=0;i<n;i++)
    {
        long long count = 0;
        cin >> x[0] >> x[1] >> x[2] >> x[3]; //x1 y1 x2 y2 
        for (int k=0;k<4;k++) temp.push_back(abs(x[k]));
        sort(temp.begin(),temp.end());
        getnode(0,count);
        if (temp[0]>1) count+=update(1,temp[0]-1,getval(1));
        for (int j=0;j<3;j++)
        {
            getnode(temp[j],count);
            if (temp[j+1]-temp[j]>1) count += update(temp[j]+1,temp[j+1]-1,getval(temp[j]));
        } 
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
    }
}