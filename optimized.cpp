#include<stdio.h>
#include <time.h> 

#include <iostream>
#include <string>
#include <map>
#include <queue>
#include <stack>
#include <algorithm>
#include <list>
#include <set>
#include <cmath>
#include <cstring>

#include <stdio.h>
#include <string.h>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <iomanip>
#include <ctime>
#include <string>
#include<cstring>
#include<string.h>


#define REP(i,n) for (int i=0;i<n;i++)
#define Clear(x,with) memset(x,with,sizeof(x))

using namespace std;


#define MAXN 400500
#define MAXL 26
 
int Case, n, pos, m, suffix[MAXN], tmp[MAXN], sum[MAXN], Count[MAXN], Rank[MAXL][MAXN];
char input[MAXN], temp[MAXN], pat[MAXN];
int occurences[MAXN],revoccurences[MAXN]; 


string patterns[MAXN]; 

bool checkEqual(const int &u, const int &v)
{
    if(!pos) 
        return input[u] == input[v];
    if(Rank[pos-1][u] != Rank[pos-1][v]) 
        return false;
    int a = u + m < n ? Rank[pos-1][u+m] : -1;
    int b = v + m < n ? Rank[pos-1][v+m] : -1;
    return a == b;
}
 
void updateRank()
{
    int i, rnk;
    REP(i,n) sum[i] = 0;
    for(i = rnk = 0; i < n; i++) 
    {
        suffix[i] = tmp[i];
        if(i && !checkEqual(suffix[i], suffix[i-1])) 
        {
            Rank[pos][suffix[i]] = ++rnk;
            sum[rnk+1] = sum[rnk];
        }
        else 
            Rank[pos][suffix[i]] = rnk;
        sum[rnk+1]++;
    }
}
 
void bucketSort() 
{
    int i;
    REP(i,n) Count[i] = 0;
    Clear(tmp,-1);
    
    for(i = 0; i < m; i++)
    {
        int idx = Rank[pos - 1][n - i - 1];
        int x = sum[idx];
        tmp[x + Count[idx]] = n - i - 1;
        Count[idx]++;
    }
    REP(i,n)
    {
        int idx = suffix[i] - m;
        if(idx < 0)
            continue;
        idx = Rank[pos-1][idx];
        int x = sum[idx];
        tmp[x + Count[idx]] = suffix[i] - m;
        Count[idx]++;
    }
    
    updateRank();
    
    return;
}
 
bool Compare(const int &a, const int &b)
{
    if(input[a]!=input[b]) return input[a]<input[b];
    return false;
}
 
void sortSuffixes() 
{
    int i;
    REP(i,n) tmp[i] = i;

    sort(tmp, tmp + n, Compare);
    
    pos = 0;
    updateRank();
    ++pos;
    for(m = 1; m < n; m <<= 1) {
        bucketSort(); // Resources on Bucket sort I read: https://www.scaler.com/topics/data-structures/bucket-sort/ 
        pos++;
    }
    pos--;
    for(i = 0; i <= pos; i++)
    {
        Rank[i][n] = -1;
    } 
        
}
int occurance = 0; 

string convertToString(char* a)
{
    string s(a);

    return s;
}
void printsuffix(char *txt, int *suffArr, int n)
{
    for(int i=0; i <n ; i++)
    {   
        string st = convertToString(txt+suffArr[i]);
        printf("sufix-> %d %s\n",i,st.c_str());
        //freq[st]++;
    }
}
// char* reverse(char *str) {                       // defining the function
//     static int i = 0;
//     static char rev[100];
//     if(*str)
//     {
//     reverse(str+1);
//     rev[i++] = *str;
//     }
//     return rev;
// }


int suffixArraySearch(char *txt,int *suffix, const char *substring, int n)
{
    int lo;
    int hi;
    int mid;
    int len;
    int cmp;

    len = strlen(substring);

    /* invariant: suffix[lo] <= substring < suffix[hi] */
    lo = 0;
    hi = n;

    while(lo + 1 < hi) {
        mid = (lo+hi)/2;
        cmp = strncmp(txt + suffix[mid], substring, len);
        
        //printf("")
        if(cmp == 0) {
            printf("matched text: %s\n", txt + suffix[mid]);
            /* we have a winner */
            /* search backwards and forwards for first and last */
            for(lo = mid; lo > 0 && strncmp(txt + suffix[lo-1], substring, len) == 0; lo--);
            for(hi = mid; hi < n && strncmp(txt + suffix[hi+1], substring, len) == 0; hi++);

            return hi - lo + 1;
        } else if(cmp < 0) {
            lo = mid;
        } else {
            hi = mid;
        }
    }

    return 0;
}

string reversestr(string str)
{
    for (int i = str.length() - 1; i >= 0; i--)
        cout << str[i];
}


int main()
{
    // freopen("large.in","r",stdin);
    // freopen("large.out","w",stdout);
    //cin >> Case;

    
    
    //REP(i,Case)
    //{
    cin >> input;
    
    n = strlen(input); 
    
    // compute the suffix tree 
    sortSuffixes();

    int npat;
    cin >> npat; 

    REP(j,npat)
    {
        cin >> patterns[j];
        strcpy(pat, patterns[j].c_str());
        occurences[j] = suffixArraySearch(input,suffix,pat,n);
        reverse(patterns[j].begin(),patterns[j].end());
        
        printf("pattern: %s: -> %d\n",pat,occurences[j]);
    }
    string st = input;

    reverse(st.begin(),st.end());

    strcpy(input,st.c_str());

    sortSuffixes();

    REP(j,npat)
    {
        strcpy(pat, patterns[j].c_str());
        revoccurences[j] = suffixArraySearch(input,suffix,pat,n);
        
        printf("pattern: %s: -> %d\n",pat,revoccurences[j]);
    }   
    
    print("something I changed");
    return 0;
}