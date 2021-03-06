    #include<bits/stdc++.h>
    using namespace std;
     
     
    #define SET(p) memset(p, -1, sizeof(p))
    #define CLR(p) memset(p, 0, sizeof(p))
    #define i64 long long
     
    const int INF = 0x7fffffff;
    const int MAXN = 500, MAXE = 80006;
     
    int src, snk, nNode, nEdge;
    int Q[MAXN], fin[MAXN], pro[MAXN], dist[MAXN];
    int flow[MAXE], cap[MAXE], nex[MAXE], to[MAXE];
     
    inline void init(int _src, int _snk, int _n) {
        src = _src, snk = _snk, nNode = _n, nEdge = 0;
        SET(fin);
    }
     
    inline void add(int u, int v, int c) {
        to[nEdge] = v, cap[nEdge] = c, flow[nEdge] = 0, nex[nEdge] = fin[u], fin[u] = nEdge++;
        to[nEdge] = u, cap[nEdge] = 0, flow[nEdge] = 0, nex[nEdge] = fin[v], fin[v] = nEdge++;
    }
     
    bool bfs() {
        int st, en, i, u, v;
        SET(dist);
        dist[src] = st = en = 0;
        Q[en++] = src;
        while(st < en) {
            u = Q[st++];
            for(i=fin[u]; i>=0; i=nex[i]) {
                v = to[i];
                if(flow[i] < cap[i] && dist[v]==-1) {
                    dist[v] = dist[u]+1;
                    Q[en++] = v;
                }
            }
        }
        return dist[snk]!=-1;
    }
     
    int dfs(int u, int fl) {
        if(u==snk) return fl;
        for(int &e=pro[u], v, df; e>=0; e=nex[e]) {
            v = to[e];
            if(flow[e] < cap[e] && dist[v]==dist[u]+1) {
                df = dfs(v, min(cap[e]-flow[e], fl));
                if(df>0) {
                    flow[e] += df;
                    flow[e^1] -= df;
                    return df;
                }
            }
        }
        return 0;
    }
     
    i64 dinitz() {
        i64 ret = 0;
        int df;
        while(bfs()) {
            for(int i=1; i<=nNode; i++) pro[i] = fin[i];
            while(true) {
                df = dfs(src, INF);
                if(df) ret += (i64)df;
                else break;
            }
        }
        return ret;
    }
     
     
    int main()
    {
        int t;
        cin>>t;
        while(t--)
        {
            int n;
            cin>>n;
            init(1, n, n);
            for(int i=1;i<n;++i)
            {
                int u;
                cin>>u;
                for(int j=1;j<=u;++j)
                {
                    int v;cin>>v;
                    if(i==1||v==n)
                    add(i, v, 1);
                else add(i, v, INF);
                }
            }
            printf("%lld\n", dinitz());
     
        }
     
     
    return 0;
    } 