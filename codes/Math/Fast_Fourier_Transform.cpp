// const int MAXN = 262144;
// (must be 2^k)

typedef long double ld;
typedef complex<ld> cplx;
const ld PI = acosl(-1);
const cplx I(0, 1);

cplx omega[MAXN+1];
void pre_fft()
{
  for(int i=0; i<=MAXN; i++)
    omega[i] = exp(i * 2 * PI / MAXN * I);
}
void fft(int n, cplx a[], bool inv=false)
{
  int basic = MAXN / n;
  int theta = basic;
  for (int m = n; m >= 2; m >>= 1) {
    int mh = m >> 1;
    for (int i = 0; i < mh; i++) {
      cplx w = omega[inv ? MAXN-(i*theta%MAXN) : i*theta%MAXN];
      for (int j = i; j < n; j += m) {
        int k = j + mh;
        cplx x = a[j] - a[k];
        a[j] += a[k];
        a[k] = w * x;
      }
    }
    theta = (theta * 2) % MAXN;
  }
  int i = 0;
  for (int j = 1; j < n - 1; j++) {
    for (int k = n >> 1; k > (i ^= k); k >>= 1);
    if (j < i) swap(a[i], a[j]);
  }
  if (inv)
    for (i = 0; i < n; i++)
      a[i] /= n;
}

// wangyenjen
typedef complex<double> cplx;
const double PI = acos(-1.0);
const int MAX_N = 1<<20;
void fft(cplx *a , int n , int dir) {
    static cplx tmp[MAX_N];
    if(n == 1) return;
    REP(i , n) tmp[i] = a[i];
    REP(i , n) a[(i&1) ? (n>>1) + (i>>1) : (i>>1)] = tmp[i];
    cplx *a1 = a , *a2 = a + (n>>1);
    fft(a1 , n>>1 , dir);
    fft(a2 , n>>1 , dir);
    cplx w_base(cos(2.0 * PI / (double)n) , sin(2.0 * PI / (double)n));
    cplx w(1.0 , 0.0);
    if(dir < 0) w_base = conj(w_base);
    for(int i = 0; (i<<1) < n; i++ , w *= w_base) {
        tmp[i] = a1[i] + w * a2[i];
        tmp[(n>>1) + i] = a1[i] - w * a2[i];
    }
    REP(i , n) a[i] = tmp[i];
}
inline int mult(cplx *a , int la , cplx *b , int lb , cplx *c) {
  int n = 2;
  while(n < la + lb) n <<= 1;
  REP1(i , la , n - 1) a[i] = cplx(0.0 , 0.0);
  REP1(i , lb , n - 1) b[i] = cplx(0.0 , 0.0);
  fft(a , n , 1);
  fft(b , n , 1);
  REP(i , n) c[i] = a[i] * b[i];
  fft(c , n , -1);
  REP(i , n) c[i] /= n;
  return la + lb - 1;
}
cplx a[MAX_N] , b[MAX_N] , c[MAX_N];
int main() {
  int n , m;
  RI(n , m);
  REP(i , n + 1) {
    int x;
    RI(x);
    a[i] = cplx((double)x , 0.0);
  }
  REP(i , m + 1) {
    int x;
    RI(x);
    b[i] = cplx((double)x , 0.0);
  }
  int len = mult(a , n + 1 , b , m + 1 , c);
  REP(i , len) printf("%d%c",(int)real(c[i] + 0.5)," \n"[i == len - 1]);
  return 0;
}
