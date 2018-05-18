/// {{{ general graph matching template
#define MAXN 505
vector<int> g[MAXN];
int pa[MAXN] , match[MAXN] , st[MAXN] , S[MAXN] , vis[MAXN];
int n;
inline int lca(int u,int v){
    static int t=0;
    for(++t;;swap(u,v)){
        if(u==0)continue;
        if(vis[u]==t)return u;
        vis[u]=t;
        u=st[pa[match[u]]];
    }
}
#define qpush(u) q.push(u),S[u]=0
inline void flower(int u,int v,int l,queue<int> &q){
    while(st[u]!=l){
        pa[u]=v;
        v=match[u];
        if(S[v]==1)qpush(v);
        st[u]=st[v]=l;
        u=pa[v];
    }
}
inline bool agument(int u,int v){
    for(int lst;u;v=lst,u=pa[v]){
        lst=match[u];
        match[u]=v;
        match[v]=u;
    }
}
inline bool bfs(int u){
    for(int i=1;i<=n;++i)st[i]=i;
    memset(S+1,-1,sizeof(int)*n);
    queue<int>q;
    qpush(u);
    while(q.size()){
        u=q.front(),q.pop();
        for(size_t i=0;i<g[u].size();++i){
            int v=g[u][i];
            if(S[v]==-1){
                pa[v]=u;
                S[v]=1;
                if(!match[v]){
                    agument(u,v);
                    return true;
                }
                qpush(match[v]);
            }else if(!S[v]&&st[v]!=st[u]){
                int l=lca(v,u);
                flower(v,u,l,q);
                flower(u,v,l,q);
            }
        }
    }
    return false;
}
inline int blossom(){
    memset(pa+1,0,sizeof(int)*n);
    memset(match+1,0,sizeof(int)*n);
    int ans=0;
    for(int i=1;i<=n;++i)
        if(!match[i]&&bfs(i))++ans;
    return ans;
}
int main() {
    int t;
    RI(t);
    while(t--) {
        int m;
        RI(n , m);
        REP1(i , 1 , n) g[i].clear();
        REP(i , m) {
            int x , y;
            RI(x , y);
            x++ , y++;
            g[x].PB(y);
            g[y].PB(x);
        }
        PL(blossom());
    }
    return 0;
}
