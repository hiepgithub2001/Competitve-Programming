#include    <bits/stdc++.h>
#pragma comment(linker, "/STACK:268435456")
#define __unique(V) (V).resize(unique((V).begin(),(V).end())-(V).begin())
#define cntbit(X)   __builtin_popcount((X))
#define bit(S,i) (((S)>>(i))&1)
#define    first_bit(S) (__builtin_ctz((S)))
#define PI    acos(-1)
#define fi  first
#define se  second
#define LL  long long
#define ii  pair<int,int>
#define iii pair<int,ii>
#define eb  emplace_back
#define lch ((k) << 1)
#define rch ((k) << 11)
#define _abs(x) ((x) > 0 ? (x) : -(x))
#define TASK "KTURN"
using namespace std;
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
const int N = 1e5 + 5;
const int K = 12;
const LL MIN_LL = -1000000000000000000;
int a[N], b[N];
LL pw[N][K];
LL dp[N][K][K][2];
/// dp[i, opening, closed, type]
int n, k;
///--------------------------
inline void    optimize(LL &x,LL y){
    x = max(x, y);
}
///--------------------------
int     main(){
    ///
        srand(time(NULL));
        ios::sync_with_stdio(0);
        cin.tie(0);cout.tie(0);
        #ifdef TLH2203
            freopen(TASK".inp", "r", stdin);
            freopen(TASK".out", "w", stdout);
        #endif // TLH2203
    ///

    cin >> n >> k;

    for(int i = 1; i <= n; ++i){
        cin >> a[i];
    }

    for(int i = 1; i <= n; ++i){
        cin >> b[i];
    }

    for(int i = 1; i <= n; ++i){
        pw[i][0] = 1;
        for(int j = 1; j <= k; ++j){
            pw[i][j] = 1ll * pw[i][j - 1] * b[i];
        }
    }

    for(int i = 0; i <= n + 1; ++i){
        for(int j = 0; j <= k; ++j){
            for(int p = 0; p <= k; ++p){
                for(int t = 0; t < 2; ++t){
                    dp[i][j][p][t] = MIN_LL;
                }
            }
        }
    }

    dp[0][0][0][0] = 0;
    a[n + 1] = 0;

    for(int i = 0; i < n; ++i){
        for(int closed = 0; closed <= k; ++closed){
            for(int opening = 0; closed + opening <= k; ++opening){

                if (i == 0){
                    if (opening > 0 || closed > 0) continue;
                }

                if (dp[i][closed][opening][0] != MIN_LL){
                    LL tmp = dp[i][closed][opening][0];
                    optimize(dp[i + 1][closed][opening][0], tmp);

                    for(int t = 0; t + opening + closed <= k; ++t){
                        optimize(dp[i + 1][closed][opening + t][1],
                                 tmp + 1ll * a[i + 1] * pw[i + 1][opening + t]);
                    }
                }

                if (dp[i][closed][opening][1] != MIN_LL){
                    LL tmp = dp[i][closed][opening][1];

                    for(int t = 0; t + opening + closed <= k; ++t){
                        optimize(dp[i + 1][closed][opening + t][1],
                                 tmp + 1ll * a[i + 1] * pw[i + 1][opening + t]);
                    }

                    for(int t = 1; opening - t >= 0; ++t){
                        optimize(dp[i + 1][closed + t][opening - t][1],
                                 tmp + 1ll * a[i + 1] * pw[i + 1][opening - t]);
                    }
                }
            }
        }
    }

    LL answer = MIN_LL;

    for(int i = 1; i <= n; ++i){
        for(int closed = 0; closed <= k; ++closed){
            for(int opening = 0; closed + opening <= k; ++opening){
                answer = max(answer, dp[i][closed][opening][1]);
            }
        }
    }

    cout << answer << '\n';
}




