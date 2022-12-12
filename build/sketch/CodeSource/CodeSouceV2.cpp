#include<bits/stdc++.h>
using namespace std;
int main()
{
    srand(time(NULL));
    string realAns="AAAA";
    for(int i=0; i<4; i++) {realAns[i]=(rand()%10)+'0';}

    //for(int i=0; i<4; i++) cout << realAns[i] << " ";
    //cout << endl;

    string b;
    b=realAns;
    string test;
    while(cin >> test)
    {
        if(test=="ans"){
           cout<<realAns;
            break;
        }

        int x=0, y=0;
        for(int i=0; i<4; i++)
        {
            if(test[i]==b[i])
            {
                x++;
                test[i]='b';
                b[i]='b';
            }
        }
        for(int i=0; i<4; i++)
        {
            if(test[i]=='b') continue;
            for(int j=0; j<4; j++)
            {
                if(test[i]==b[j])
                {
                    y++;
                    test[i]='b';
                    b[j]='b';
                    break;
                }
            }
        }
        cout << x << 'A' << y << 'B' << endl;
        if(x==4) break;
        b=realAns;
    }
    return 0;
}
