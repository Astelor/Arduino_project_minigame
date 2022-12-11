#include<bits/stdc++.h>
using namespace std;
int main()
{
    srand(time(NULL));
    int realAns[4];
    for(int i=0; i<4; i++) realAns[i]=rand()%10;
    
    //for(int i=0; i<4; i++) cout << realAns[i] << " ";
    //cout << endl;
    
    int b[4]={0};
    for(int i=0; i<4; i++) b[i]=realAns[i];
    int test[4]={0};
    while(cin >> test[0])
    {
        for(int i=1; i<4; i++) cin >> test[i];
        int x=0, y=0;
        for(int i=0; i<4; i++)
        {
            if(test[i]==b[i])
            {
                x++;
                test[i]=-1;
                b[i]=-1;
            }
        }
        for(int i=0; i<4; i++)
        {
            if(test[i]==-1) continue;
            for(int j=0; j<4; j++)
            {
                if(test[i]==b[j])
                {
                    y++;
                    test[i]=-1;
                    b[j]=-1;
                    break;
                }
            }
        }
        cout << x << 'A' << y << 'B' << endl;
        if(x==4) break;
        for(int i=0; i<4; i++) b[i]=realAns[i];
    }
    return 0;
}