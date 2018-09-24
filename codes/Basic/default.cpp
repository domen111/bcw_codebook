#include<bits/stdc++.h>

#define ALL(a) begin(a), end(a)

using namespace std;

// deBuG function
// example:
// int a = 3; int b[] = {1,2}; string c = "abc";
// BG(a, b[1], c); // stderr: int main():37: a = 3,  b[1] = 2,  c = a
#ifdef LITE

void _BG(const char * s) {cerr<<s<<endl;}
template<class T, class ... TT>
void _BG(const char * s,T a, TT...b)
{
    for (size_t c = 0; *s && (c || *s != ','); cerr<<*s++)
        c += count(ALL("([{"), *s) - count(ALL(")]}"), *s); // Implementation defined. But that's ok since it only runs on local.
    cerr<<" = "<<a;
    if (*s) {
        cerr<<", ";
        ++s;
    }
    _BG(s,b...);
}
#define BG(...) do { \
    cerr << __PRETTY_FUNCTION__ << ':' << __LINE__ << ": "; \
    _BG(#__VA_ARGS__,__VA_ARGS__); \
} while(0)

#else
#define BG(...)
#endif

int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);

    // lite !
}
