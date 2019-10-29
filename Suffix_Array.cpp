const int maxn = 1e5;

struct entry {
    int nr[2], p;

    bool operator <(const entry &rhs) {
        if(nr[0] == rhs.nr[0]) 
            return nr[1] < rhs.nr[1];
        return nr[0] < rhs.nr[0];
    }
} L[maxn];
int P[20][maxn], SA[maxn];

int main()
{   
    string str; int n;
    cin >> str; n = str.length();

    for(int i = 0; i < n; i++) 
        P[0][i] = str[i] - 'a';

    int step = 1;
    for(int cnt = 1; cnt >> 1 < n; step++, cnt <<= 1) {
        
        for(int i = 0; i < n; i++) {
            L[i].nr[0] = P[step-1][i];
            L[i].nr[1] = i + cnt < n ? P[step-1][i+cnt] : -1;
            L[i].p = i;
        }
        sort(L, L+n);
        for(int i = 0; i < n; i++)
            P[step][L[i].p] = ((i > 0) && (L[i].nr[0] == L[i-1].nr[0]) && (L[i].nr[1] == L[i-1].nr[1])) ?
                              P[step][L[i-1].p] : i;
    } 
    for(int i = 0; i < n; i++) SA[P[step-1][i]] = i;

    for(int i = 0; i < n; i++) cout << SA[i] << " ";
    cout << endl;

    return 0;   
}
