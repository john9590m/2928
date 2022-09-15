#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;


int n,m;
long long seg[210001];

long long query(int start,int end)
{
    long long result = 0;
    return result;
}

void update(int start, int end, long long var, long long tvar)
{
    start += 100000;
    end += 100000;
    
}

int main(void)
{
    cin >> n;
    int x1,x2,y1,y2;
    int x[4];
    vector<pair<int,int>> temp;
    for (int i=0;i<n;i++)
    {
        int count = 0;
        cin >> x[0] >> x[1] >> x[2] >> x[3]; //x1 y1 x2 y2 
        for (int j=-1;j<2;j=j+2) for (int k=0;k<4;k++) temp.push_back(make_pair(j*x[k],k%2));
        if (temp[0].first==x[0] || temp[0].first == x[1] || temp[0].first == -x[2] || temp[0].first == -x[3]) continue;
        update(0,temp[0].first,4,8);
        for (int k=1;k<4;k++)
        {
            if (temp[k].first==x[0] || temp[k].first == x[1] || temp[k].first == -x[2] || temp[k].first == -x[3]) break;
            else
            {
                switch (count){
                        case 0 : update(temp[0].first,temp[1].first,2-2*temp[0].first,4); //맞나 싶다 너무 x1기준인듯?
                                        break;
                        case 1 : if(temp[0].second == temp[1].second) 
                                        {
                                            if (temp[0].second)update(temp[1].first,temp[2].first,2*(x[3]-x[1]),0);
                                            else update(temp[1].first,temp[2].first,2*(x[2]-x[1]),0);
                                        }
                                        else update(temp[1].first,temp[2].first,temp[0].first+temp[1].first+1,2);
                                        break;
                        case 2 : if(temp[0].second+temp[1].second+temp[2].second == 2)update(temp[2].first,temp[3].first,x[3]-x[1],0);
                                        else update(temp[2].first,temp[3].first,x[2]-x[0],0);
                                        break;
                        default : break;
                }
                count++;
            }            
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
        cout << accumulate;
    }
}