#include<bits/stdc++.h>
#define ll long long
#define pb push_back
#define pix pair<pair<int,int>,int>
#define ss second
#define ff first
using namespace std;

class pixel
{
public:
    ll r, g, b;
};

int w,h;
clock_t begin_time;
int res[600][600];
pixel pic[600][600];
pix picc[600][600];
map< pix , int> m;
vector<pix> p;
#define M_PI 3.14159265358979323846
double dokraja=0.0;

bool cmpp(pair<pix,int> x, pair<pix, int> y)
{
    return x.second > y.second;
}

ll udaljenost(pix a,pix b)
{
    return (a.ss - b.ss)*(a.ss - b.ss) + (a.ff.ss - b.ff.ss)*(a.ff.ss - b.ff.ss) + (a.ff.ff - b.ff.ff)*(a.ff.ff - b.ff.ff);
}

pair<vector<pix>, ll> kMeans(vector<pix> prev)
{
    while(1){
        if((clock()-begin_time)/CLOCKS_PER_SEC>=4.0-dokraja)
            break;
        vector<pix> now(prev.size(),{{0,0},0});
        vector<int> cnt(prev.size(),0);
        for(auto i: p){
            int najblizi=0;
            int razmak = INT_MAX;
            for(int j=0;j<prev.size();j++){
                ll temp = udaljenost(prev[j], i);
                if(temp<razmak){
                    razmak=temp;
                    najblizi=j;
                }
            }
            cnt[najblizi]++;
            now[najblizi].ff.ff+=i.ff.ff;
            now[najblizi].ff.ss+=i.ff.ss;
            now[najblizi].ss+=i.ss;
        }
        for(int i=0;i<now.size();i++){
            if(cnt[i]==0)break;
            now[i].ff.ff/=cnt[i];
            now[i].ff.ss/=cnt[i];
            now[i].ss/=cnt[i];
        }

        if(now==prev)
            break;
        prev = now;
    }
    ll rez=0;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){

            int index=0;
            ll maxi = LLONG_MAX;
            for(int k=0;k<prev.size();k++){
                pix ii = prev[k];
                ll temp = (pic[i][j].b - ii.ss)*(pic[i][j].b - ii.ss) + (pic[i][j].g - ii.ff.ss)*(pic[i][j].g - ii.ff.ss) + (pic[i][j].r - ii.ff.ff)*(pic[i][j].r - ii.ff.ff);
                if(temp<maxi){
                    index = k;
                    maxi=temp;
                }
            }
            rez+=maxi;
        }
    }
    return {prev,rez};
}

pair<vector<pix>, ll> kMedians(vector<pix> prev)
{
    while(1){
        if((clock()-begin_time)/CLOCKS_PER_SEC>=4.0-dokraja)
            break;
        vector<pix> now(prev.size(),{{0,0},0});
        vector<pair<pair<vector<int>,vector<int>>,vector<int>>> cnt(prev.size());
        for(auto i: p){
            int najblizi=0;
            int razmak = INT_MAX;
            for(int j=0;j<prev.size();j++){
                ll temp = udaljenost(prev[j], i);
                if(temp<razmak){
                    razmak=temp;
                    najblizi=j;
                }
            }
            cnt[najblizi].ff.ff.pb(i.ff.ff);
            cnt[najblizi].ff.ss.pb(i.ff.ss);
            cnt[najblizi].ss.pb(i.ss);
        }
        for(int i=0;i<now.size();i++){
            if(cnt[i].ff.ff.size()==0)break;
            ll temp = cnt[i].ff.ff.size();
            sort(cnt[i].ff.ff.begin(),cnt[i].ff.ff.end());
            sort(cnt[i].ff.ss.begin(),cnt[i].ff.ss.end());
            sort(cnt[i].ss.begin(),cnt[i].ss.end());
            if(temp&1){
                now[i].ff.ff = cnt[i].ff.ff[temp/2];
                now[i].ff.ss = cnt[i].ff.ss[temp/2];
                now[i].ss = cnt[i].ss[temp/2];
            }
            else{
                now[i].ff.ff = (cnt[i].ff.ff[temp/2] + cnt[i].ff.ff[temp/2+1])/2;
                now[i].ff.ss = (cnt[i].ff.ss[temp/2] + cnt[i].ff.ss[temp/2+1])/2;
                now[i].ss = (cnt[i].ss[temp/2] + cnt[i].ss[temp/2+1])/2;
            }
        }

        if(now==prev)
            break;
        prev = now;
    }
    ll rez=0;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){

            int index=0;
            ll maxi = LLONG_MAX;
            for(int k=0;k<prev.size();k++){
                pix ii = prev[k];
                ll temp = (pic[i][j].b - ii.ss)*(pic[i][j].b - ii.ss) + (pic[i][j].g - ii.ff.ss)*(pic[i][j].g - ii.ff.ss) + (pic[i][j].r - ii.ff.ff)*(pic[i][j].r - ii.ff.ff);
                if(temp<maxi){
                    index = k;
                    maxi=temp;
                }
            }
            rez+=maxi;
        }
    }

    return {prev,rez};
}

vector<pix> createStartingV(int k)
{
    vector<pix> sol;
    vector<pair<pix,ll>> pp;
    vector<ll> distr(16, 1);
    for(auto i:p){
            pp.pb({i, INT_MAX});
        }
    srand(time(NULL));
    for(int i=0;i<k;i++){
        default_random_engine generator;
        discrete_distribution<ll> distribution(distr.begin(),distr.end());
        ll index = distribution(generator);
        index%=pp.size();
        distr.clear();
        sol.pb(pp[index].ff);
        //sol = kMeans(sol).ff;
        for(int j=0;j<(int)pp.size();j++){
            for(auto o:sol){
                pp[j].ss = min((ll)pp[j].ss, udaljenost(o, pp[j].ff));
            }
            distr.pb(pp[j].ss*pp[j].ss);
        }
    }
    for(int i=0;i<16-k;i++){
        sol.pb({{0,0}, 0});
    }
    return sol;
}

vector<pix> createStartingVRand(int k)
{
    vector<pix> sol;
    vector<pair<pix,ll>> pp;
    vector<ll> distr(16, 1);
    for(auto i:p){
        pp.pb({i, INT_MAX});
    }
    srand(time(NULL));
    for(int i=0;i<k;i++){
        ll index=0;
        if(1){
            index=rand()%pp.size();
        }
        sol.pb(pp[index].ff);
        for(int j=0;j<(int)pp.size();j++){
            for(auto o:sol){
                pp[j].ss = min((ll)pp[j].ss, udaljenost(o, pp[j].ff));
            }
            distr.pb(pp[j].ss*pp[j].ss);
        }
    }
    for(int i=0;i<16-k;i++){
        sol.pb({{0,0}, 0});
    }
    return sol;
}

ll choose(vector<pix> sol,int preskoci)
{
    vector<ll> distr;
    for(auto i:p){
        ll mini=LLONG_MAX;
        for(int j=0;j<16;j++){
            if(j==preskoci)continue;
            mini=min(mini,udaljenost(i, sol[j]));
        }
        distr.pb(mini*mini);
    }

    default_random_engine generator;
    discrete_distribution<ll> distribution(distr.begin(), distr.end());
    ll index = distribution(generator);
    index%=p.size();
    return index;
}

void compress()
{
    scanf("%d %d", &w, &h);
    //return w*h;
    dokraja = (w*h)/5000000.0;
    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            pix temp;
            scanf("%d %d %d", &temp.ff.ff, &temp.ff.ss, &temp.ss);
            pic[i][j].r = temp.ff.ff;
            pic[i][j].g = temp.ff.ss;
            pic[i][j].b = temp.ss;
            p.pb(temp);
        }
    }

    vector<pix> sol = createStartingV(16);
    pair<vector<pix>, ll> rez = kMeans(sol);
    vector<pix> prev = rez.ff;
    bool medians=true;
    srand(time(NULL));
    bool isti=false;
    //vector<ll> pojavljivanja(16, 0);
    while((clock()-begin_time)/CLOCKS_PER_SEC<3.5){
        vector<ll> pojavljivanja(16,0);
        for(int i=1;i<=h;i++){
            for(int j=1;j<=w;j++){
                int index=0;
                ll maxi = LLONG_MAX;
                int indexdrugi=-1;
                for(int k=0;k<prev.size();k++){
                    pix ii = prev[k];
                    ll temp = (pic[i][j].b - ii.ss)*(pic[i][j].b - ii.ss) + (pic[i][j].g - ii.ff.ss)*(pic[i][j].g - ii.ff.ss) + (pic[i][j].r - ii.ff.ff)*(pic[i][j].r - ii.ff.ff);
                    if(temp<maxi){
                        index = k;
                        maxi=temp;
                    }
                }
                ll maxidrugi=LLONG_MAX;
                for(int k=0;k<prev.size();k++){
                    pix ii = prev[k];
                    ll temp = (pic[i][j].b - ii.ss)*(pic[i][j].b - ii.ss) + (pic[i][j].g - ii.ff.ss)*(pic[i][j].g - ii.ff.ss) + (pic[i][j].r - ii.ff.ff)*(pic[i][j].r - ii.ff.ff);
                    if(temp<maxidrugi && k!=index){
                        indexdrugi = k;
                        maxidrugi=temp;
                    }
                }
                pojavljivanja[index]+=maxidrugi-maxi;
            }
        }

        ll najmanje=LLONG_MAX;
        ll indnajmanje=0;
        for(int i=0;i<16;i++){
            if(pojavljivanja[i]<najmanje){
                indnajmanje=i;
                najmanje=pojavljivanja[i];
            }
        }
        sol = prev;
        sol[indnajmanje] = p[choose(sol,indnajmanje)];
        pair<vector<pix>, ll> rez2;
        rez2 = kMeans(sol);
        if(medians)rez2 = kMedians(sol);
        else rez2 = kMeans(sol);
        medians=!medians;
        //printf("%lld\n",najmanje);
        if(rez2.ss < rez.ss){
            rez.ss=rez2.ss;
            prev = rez2.ff;
        }
    }
    //printf("%lld\n",rez.ss);
    for(auto i : prev){
        printf("%d %d %d\n",i.ff.ff, i.ff.ss, i.ss);
    }

    for(int i=1;i<=h;i++){
        for(int j=1;j<=w;j++){
            int index=0;
            ll maxi = LLONG_MAX;
            for(int k=0;k<prev.size();k++){
                pix ii = prev[k];
                ll temp = (pic[i][j].b - ii.ss)*(pic[i][j].b - ii.ss) + (pic[i][j].g - ii.ff.ss)*(pic[i][j].g - ii.ff.ss) + (pic[i][j].r - ii.ff.ff)*(pic[i][j].r - ii.ff.ff);
                if(temp<maxi){
                    index = k;
                    maxi=temp;
                }
            }
            res[i][j] = index;
            printf("%d ", res[i][j]);
        }
        printf("\n");
    }

    return;
}

map<int,int> poj[510][510];
int bio[510][510];

void decompress()
{
    map<int,pix> sol;
    for(int i=0;i<16;i++){
        pix x;
        scanf("%d %d %d", &x.ff.ff, &x.ff.ss, &x.ss);
        sol[i]= x;
    }
    int hh,ww;
    scanf("%d %d", &ww, &hh);
    for(int i=1;i<=hh;i++){
        for(int j=1;j<=ww;j++){
            scanf("%d", &res[i][j]);
            picc[i][j]=sol[res[i][j]];
        }
    }

    for(int i=2;i<hh;i++){
        for(int j=2;j<ww;j++){
            pix temp = {{0,0}, 0};
            temp.ff.ff+=4*sol[ res[i][j] ].ff.ff;
            temp.ff.ff+=1*sol[res[i][j+1]].ff.ff;
            temp.ff.ff+=1*sol[res[i+1][j]].ff.ff;
            temp.ff.ff+=1*sol[res[i-1][j]].ff.ff;
            temp.ff.ff+=1*sol[res[i][j-1]].ff.ff;
            temp.ff.ff/=8;

            temp.ff.ss+=4*sol[res[i][j]].ff.ss;
            temp.ff.ss+=1*sol[res[i][j+1]].ff.ss;
            temp.ff.ss+=1*sol[res[i+1][j]].ff.ss;
            temp.ff.ss+=1*sol[res[i-1][j]].ff.ss;
            temp.ff.ss+=1*sol[res[i][j-1]].ff.ss;
            temp.ff.ss/=8;

            temp.ss+=4*sol[res[i][j]].ss;
            temp.ss+=1*sol[res[i][j+1]].ss;
            temp.ss+=1*sol[res[i+1][j]].ss;
            temp.ss+=1*sol[res[i-1][j]].ss;
            temp.ss+=1*sol[res[i][j-1]].ss;
            temp.ss/=8;
            picc[i][j]= temp;
        }
    }
    for(int i=1;i<=hh;i++){
        if(i==1){
            pix temp = {{0,0}, 0};
            temp.ff.ff+=4*sol[ res[i][0] ].ff.ff;
            temp.ff.ff+=1*sol[res[i][0+1]].ff.ff;
            temp.ff.ff+=1*sol[res[i+1][0]].ff.ff;
            temp.ff.ff/=6;

            temp.ff.ss+=4*sol[res[i][0]].ff.ss;
            temp.ff.ss+=1*sol[res[i][0+1]].ff.ss;
            temp.ff.ss+=1*sol[res[i+1][0]].ff.ss;
            temp.ff.ss/=6;

            temp.ss+=4*sol[res[i][0]].ss;
            temp.ss+=1*sol[res[i][0+1]].ss;
            temp.ss+=1*sol[res[i+1][0]].ss;
            temp.ss/=6;
            picc[i][0]=temp;

            temp = {{0,0}, 0};
            temp.ff.ff+=4*sol[ res[i][ww] ].ff.ff;
            temp.ff.ff+=1*sol[res[i+1][ww]].ff.ff;
            temp.ff.ff+=1*sol[res[i][ww-1]].ff.ff;
            temp.ff.ff/=6;

            temp.ff.ss+=4*sol[res[i][ww]].ff.ss;
            temp.ff.ss+=1*sol[res[i+1][ww]].ff.ss;
            temp.ff.ss+=1*sol[res[i][ww-1]].ff.ss;
            temp.ff.ss/=6;

            temp.ss+=4*sol[res[i][ww]].ss;
            temp.ss+=1*sol[res[i+1][ww]].ss;
            temp.ss+=1*sol[res[i][ww-1]].ss;
            temp.ss/=6;

            picc[i][ww]=temp;
        }
        else if(i==hh){
            pix temp = {{0,0}, 0};
            temp.ff.ff+=4*sol[ res[i][0] ].ff.ff;
            temp.ff.ff+=1*sol[res[i][0+1]].ff.ff;
            temp.ff.ff+=1*sol[res[i-1][0]].ff.ff;
            temp.ff.ff/=6;

            temp.ff.ss+=4*sol[res[i][0]].ff.ss;
            temp.ff.ss+=1*sol[res[i][0+1]].ff.ss;
            temp.ff.ss+=1*sol[res[i-1][0]].ff.ss;
            temp.ff.ss/=6;

            temp.ss+=4*sol[res[i][0]].ss;
            temp.ss+=1*sol[res[i][0+1]].ss;
            temp.ss+=1*sol[res[i-1][0]].ss;
            temp.ss/=6;
            picc[i][0]=temp;

            temp = {{0,0}, 0};
            temp.ff.ff+=4*sol[ res[i][ww] ].ff.ff;
            temp.ff.ff+=1*sol[res[i-1][ww]].ff.ff;
            temp.ff.ff+=1*sol[res[i][ww-1]].ff.ff;
            temp.ff.ff/=6;

            temp.ff.ss+=4*sol[res[i][ww]].ff.ss;
            temp.ff.ss+=1*sol[res[i-1][ww]].ff.ss;
            temp.ff.ss+=1*sol[res[i][ww-1]].ff.ss;
            temp.ff.ss/=6;

            temp.ss+=4*sol[res[i][ww]].ss;
            temp.ss+=1*sol[res[i-1][ww]].ss;
            temp.ss+=1*sol[res[i][ww-1]].ss;
            temp.ss/=6;

            picc[i][ww]=temp;
        }
        else{
            pix temp = {{0,0}, 0};
            temp.ff.ff+=5*sol[ res[i][0] ].ff.ff;
            temp.ff.ff+=1*sol[res[i][0+1]].ff.ff;
            temp.ff.ff+=1*sol[res[i+1][0]].ff.ff;
            temp.ff.ff+=1*sol[res[i-1][0]].ff.ff;
            temp.ff.ff/=8;

            temp.ff.ss+=5*sol[res[i][0]].ff.ss;
            temp.ff.ss+=1*sol[res[i][0+1]].ff.ss;
            temp.ff.ss+=1*sol[res[i+1][0]].ff.ss;
            temp.ff.ss+=1*sol[res[i-1][0]].ff.ss;

            temp.ff.ss/=8;

            temp.ss+=5*sol[res[i][0]].ss;
            temp.ss+=1*sol[res[i][0+1]].ss;
            temp.ss+=1*sol[res[i+1][0]].ss;
            temp.ss+=1*sol[res[i-1][0]].ss;
            temp.ss/=8;
            picc[i][0]= temp;

            temp = {{0,0}, 0};
            temp.ff.ff+=5*sol[ res[i][ww] ].ff.ff;
            temp.ff.ff+=1*sol[res[i+1][ww]].ff.ff;
            temp.ff.ff+=1*sol[res[i-1][ww]].ff.ff;
            temp.ff.ff+=1*sol[res[i][ww-1]].ff.ff;
            temp.ff.ff/=8;

            temp.ff.ss+=5*sol[res[i][ww]].ff.ss;
            temp.ff.ss+=1*sol[res[i+1][ww]].ff.ss;
            temp.ff.ss+=1*sol[res[i-1][ww]].ff.ss;
            temp.ff.ss+=1*sol[res[i][ww-1]].ff.ss;
            temp.ff.ss/=8;

            temp.ss+=5*sol[res[i][ww]].ss;
            temp.ss+=1*sol[res[i+1][ww]].ss;
            temp.ss+=1*sol[res[i-1][ww]].ss;
            temp.ss+=1*sol[res[i][ww-1]].ss;
            temp.ss/=8;

            picc[i][ww]= temp;
        }
    }
    for(int i=1;i<=hh;i++){
        for(int j=1;j<=ww;j++){
            printf("%d %d %d ", picc[i][j].ff.ff,picc[i][j].ff.ss,picc[i][j].ss);
        }
        printf("\n");
    }
    return;
}

int main () {
    begin_time = clock();
    freopen("imrec.in","r", stdin);
    freopen("imrec.out","w", stdout);

    int test;
    scanf("%d",&test);
    if(test==0)
        compress();
    else
        decompress();
    return 0;
}
