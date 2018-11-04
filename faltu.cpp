#include<bits/stdc++.h>
using namespace std;

int main(){
   int n,c=0,m=0;
    string s;
    char ch;
    cin >> n >> s;
    map<char,int> mp;
    for(int i=0;i<s.length();i++){
        mp[s[i]] += 1;
    }
    for(map<char, int> :: iterator it = mp.begin();it!=mp.end();++it){
        if(n== it->second){
            ch= it->first;
            break;
        }
        if(m< it->second){
            m= it->second;
            ch= it->first;
        }
    }
    printf("%c", ch);

}