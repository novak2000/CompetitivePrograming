#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define pb push_back
#define db double
#define ff first
#define ss second

const ll maxN=10510;
const ll p=31;
const ll mod=1e9+9;
bool nemavremena=false;
clock_t begin_time=0;
clock_t time_alowed_for_word=0;
const double timelimit=4.1;
clock_t vremePoSlovu=0;
clock_t begin_time_for_word=0;
struct rec
{
    string sorce;
    vector<ll> hasheds;
    vector<pair<ll,ll>> start;
    string solution;
    ll index;
    ll nacin;
    ll n;
    ll brmax;
};

ll n,t,maxi=0,maxx=5,maxy=3,zbirn=0,x=5,y=2,proseky,suman=0;
char resenje[4000][maxN];
string text="";
string rek="";
vector<rec> reci;
ll pow_p[maxN];
set<char> posebni;
vector<vector<ll>> kombinacije;
ll lista[10];
ll mini=INT_MAX;

void kombinuj(ll now,ll n)
{
    if(now==5){
        vector<ll> ubaci;
        for(int i=1;i<=4;i++){
            ubaci.pb(lista[i]);
        }
        kombinacije.pb(ubaci);
        return;
    }
    for(int i=lista[now-1]+1;i<=n;i++){
        lista[now]=i;
        kombinuj(now+1,n);
        lista[now]=0;
    }
    return;
}
ll hashing(string const& now)
{
    ll vrati=0;
    for(int i=0;i<now.size();i++)
        vrati+=(now[i]-'a'+1)*pow_p[i];
        vrati%=mod;
    return vrati;
}
///pravi sve pow od p;
void make_pows(ll const& p,ll const& mod)
{
    pow_p[0]=1;
    for(int i=1;i<=10000+5;i++){
        pow_p[i]=(pow_p[i-1]*p) % mod;
    }
    return;
}
vector<ll> hashuj(const string &s)
{
    vector<ll> vrati;
    ll suma=0;
    for(int i=0;i<s.size();i++){
        suma+=(s[i]-'a'+1)*pow_p[i];
        suma%=mod;
        vrati.pb(suma);
    }
    return vrati;
}
bool cmpbegin(rec x,rec y)
{
    return x.n>y.n;
}
bool cmpend(rec x,rec y)
{
    return x.index<y.index;
}
ll moze(const string &s)
{
    bool radi=true;
    for(int i=1;i<s.size();i+=2){
        if(posebni.count(s[i])==0){
            radi=false;
            break;
        }
    }
    if(radi)return 0;
    radi=true;
    for(int i=0;i<s.size();i+=2){
        if(posebni.count(s[i])==0){
            radi=false;
            break;
        }
    }
    if(radi)return 1;
    return -1;
}
void nacini()
{
    resenje[2][2]='*';
    vector<ll> najbolji;
    ll najvise=-1;
    ll temp=0;
    for(auto k:kombinacije){
        temp=0;
        posebni.clear();
        for(auto o:k)
            posebni.insert(o+'a'-1);
        resenje[1][2]='a'+k[0]-1;
        resenje[3][2]='a'+k[1]-1;
        resenje[2][1]='a'+k[2]-1;
        resenje[2][3]='a'+k[3]-1;
        for(int i=0;i<n;i++){
            reci[i].nacin=moze(reci[i].sorce);
            if(reci[i].nacin!= -1)
                temp+=reci[i].n;
        }
        if(temp>najvise){
            najbolji=k;
            najvise=temp;
        }
    }
    if(najvise<=0){
        resenje[1][2]=0;
        resenje[3][2]=0;
        resenje[2][1]=0;
        resenje[2][3]=0;
        resenje[2][2]=0;
        return;
    }
    posebni.clear();
    for(auto o:najbolji)
        posebni.insert(o+'a'-1);
    resenje[1][2]='a'+najbolji[0]-1;
    resenje[3][2]='a'+najbolji[1]-1;
    resenje[2][1]='a'+najbolji[2]-1;
    resenje[2][3]='a'+najbolji[3]-1;

    for(int i=0;i<n;i++){
        reci[i].nacin = moze(reci[i].sorce);
    }
    return;
}
void ispisi0(ll now)
{
    reci[now].start.pb({1,1});
    for(int i=1;i<reci[now].n-1;i+=2){
        if(resenje[1][2]==reci[now].sorce[i])reci[now].solution+= "UD";
        else if(resenje[3][2]==reci[now].sorce[i])reci[now].solution+= "DU";
        else if(resenje[2][1]==reci[now].sorce[i])reci[now].solution+= "LR";
        else reci[now].solution+= "RL";
    }
    if((reci[now].n&1) == 0){
        ll t=reci[now].n-1;
        if(resenje[1][2]==reci[now].sorce[t])reci[now].solution+= "U";
        else if(resenje[3][2]==reci[now].sorce[t])reci[now].solution+= "D";
        else if(resenje[2][1]==reci[now].sorce[t])reci[now].solution+= "L";
        else reci[now].solution+= "R";
    }
    return;
}
void ispisi1(ll now)
{
    if(resenje[1][2]==reci[now].sorce[0]){
        reci[now].start.pb({1,0});
        reci[now].solution+= "D";
    }
    else if(resenje[3][2]==reci[now].sorce[0]){
        reci[now].start.pb({1,2});
        reci[now].solution+="U";
    }
    else if(resenje[2][1]==reci[now].sorce[0]){
        reci[now].start.pb({0,1});
        reci[now].solution+="R";
    }
    else{
        reci[now].start.pb({2,1});
        reci[now].solution+="L";
    }
    for(int i=2;i<reci[now].n-1;i+=2){
        if(resenje[1][2]==reci[now].sorce[i])reci[now].solution+= "UD";
        else if(resenje[3][2]==reci[now].sorce[i])reci[now].solution+= "DU";
        else if(resenje[2][1]==reci[now].sorce[i])reci[now].solution+= "LR";
        else reci[now].solution+= "RL";
    }
    if(((reci[now].n)&1) && reci[now].n>1){
        ll t=reci[now].n-1;
        if(resenje[1][2]==reci[now].sorce[t])reci[now].solution+= "U";
        else if(resenje[3][2]==reci[now].sorce[t])reci[now].solution+= "D";
        else if(resenje[2][1]==reci[now].sorce[t])reci[now].solution+= "L";
        else reci[now].solution+= "R";
    }
    return;
}
ll alreadyIn(const ll now)
{
    ll nowHash = reci[now].hasheds.back();
    ll l = reci[now].n;
    for(int sada=0;sada<now;sada++){
        if(reci[sada].nacin==-1){
            for(int i=0;i+l<=reci[sada].n;i++){
                ll lrHash=reci[sada].hasheds[i+l-1];
                if(i>0)lrHash-=reci[sada].hasheds[i-1];
                lrHash+=mod;
                lrHash%=mod;
                if((nowHash*pow_p[i])%mod == lrHash){
                    reci[now].solution+= reci[sada].solution.substr(i,l-1);
                    for(int j=i;j<i+l;j++){
                        reci[now].start.pb(reci[sada].start[j]);
                    }
                    return 2;
                }
            }
        }
    }
    return -1;
}
bool cmpp(pair<ll,ll> x,pair<ll,ll> y)
{
    if(x.ss==y.ss)
        return x.ff<y.ff;
    return x.ss<y.ss;
}
bool probabfs(string s,ll nowx,ll nowy,ll nowi)
{
    if(nowi>=s.size()){
        if(resenje[nowy][nowx+1]==0 && resenje[nowy][nowx+2]==0)return true;
        return false;
    }
    if(resenje[nowy][nowx+1]==s[nowi]){
        if(probabfs(s,nowx+1,nowy,nowi+1))return true;
    }
    if(resenje[nowy+1][nowx]==s[nowi]){
        if(probabfs(s,nowx,nowy+1,nowi+1))return true;
    }
    if(resenje[nowy-1][nowx]==s[nowi]){
        if(probabfs(s,nowx,nowy-1,nowi+1))return true;
    }
    if(resenje[nowy][nowx-1]==s[nowi]){
        if(probabfs(s,nowx-1,nowy,nowi+1))return true;
    }
    return false;
}
deque<pair<ll,ll>> proba;
bool bio=false;
void pravibfs(string s,ll nowx,ll nowy,ll nowi,ll now)
{
    if(bio)return;
    if(nowi>=s.size()){
        if(resenje[nowy][nowx+1]==0 && resenje[nowy][nowx+2]==0){
            if(bio)return;
            bio=true;
            x=nowx;
            y=nowy;
            reci[now].solution+=rek;
            for(auto i:proba)
            {
                reci[now].start.pb(i);
            }
            return;
        }
        return;
    }
    if(resenje[nowy][nowx+1]==s[nowi]){
        rek+='R';
        proba.pb({nowx,nowy-1});
        pravibfs(s,nowx+1,nowy,nowi+1,now);
        proba.pop_back();
        rek.pop_back();
    }
    if(resenje[nowy+1][nowx]==s[nowi]){
        rek+='D';
        proba.pb({nowx-1,nowy});
        pravibfs(s,nowx,nowy+1,nowi+1,now);
        proba.pop_back();
        rek.pop_back();
    }
    if(resenje[nowy-1][nowx]==s[nowi]){
        rek+='U';
        proba.pb({nowx-1,nowy-2});
        pravibfs(s,nowx,nowy-1,nowi+1,now);
        proba.pop_back();
        rek.pop_back();
    }
    if(resenje[nowy][nowx-1]==s[nowi]){
        rek+='L';
        proba.pb({nowx-2,nowy-1});
        pravibfs(s,nowx-1,nowy,nowi+1,now);
        proba.pop_back();
        rek.pop_back();
    }
    return;
}
void postavi(ll now)
{
    vector<pair<ll,ll>> isto;
    isto.pb({INT_MAX,INT_MAX});
    string rec=reci[now].sorce;
    ll nn=rec.size();
    for(int i=0;i<nn;i++){
        for(int j=i+1;j<nn;j++){
            if(rec[i]==rec[j] && (j-i-1)&1){
                isto.pb({i,j});
            }
        }
    }
    sort(isto.begin(),isto.end(),cmpp);
    ll temp=0;
    ll i=0;
    for(;i<nn;){
        while(temp+1<isto.size() && i>isto[temp].ff){
            temp++;
        }
        if(i<isto[temp].ff || i>isto[temp].ff){
            if(i)x++;
            resenje[y][x]=rec[i];
            reci[now].start.pb({x-1,y-1});
            if(i)reci[now].solution.pb('R');
            i++;
            maxx=max(maxx,x);
            maxy=max(maxy,y);
        }
        else if(i==isto[temp].ff){
            if(i)y++;
            if(i)reci[now].solution.pb('D');
            maxy=max(maxy,y);
            resenje[y][x]=rec[i];
            reci[now].start.pb({x-1,y-1});
            x--;
            i++;
            resenje[y][x]=rec[i];
            reci[now].start.pb({x-1,y-1});
            i++;
            reci[now].solution.pb('L');
            ll brojac=(isto[temp].ss-isto[temp].ff-2)/2;
            ll brojac2=brojac;
            maxx=max(maxx,x);
            maxy=max(maxy,y);
            while(brojac--){
                y++;
                reci[now].solution.pb('D');
                resenje[y][x]=rec[i];
                reci[now].start.pb({x-1,y-1});
                i++;
            }
            maxx=max(maxx,x);
            maxy=max(maxy,y);
            if(brojac2){
                x++;
                reci[now].solution.pb('R');
                resenje[y][x]=rec[i];
                reci[now].start.pb({x-1,y-1});
                i++;
                brojac2--;
                maxx=max(maxx,x);
                maxy=max(maxy,y);
            }
            while(brojac2--){
                y--;
                reci[now].solution.pb('U');
                resenje[y][x]=rec[i];
                reci[now].start.pb({x-1,y-1});
                i++;
            }
            maxx=max(maxx,x);
            maxy=max(maxy,y);
            if((isto[temp].ss-isto[temp].ff-2)/2>0){
                y--;
                reci[now].solution.pb('U');
                reci[now].start.pb({x-1,y-1});
                i++;
            }
            else{
                x++;
                reci[now].solution.pb('R');
                reci[now].start.pb({x-1,y-1});
                i++;
            }
            string pon="";
            ll naj=-1;
            for(int ponovo=0;ponovo<40 && ponovo+i<reci[now].n;ponovo++){
                pon+=reci[now].sorce[i+ponovo];
                if(probabfs(pon,x,y,0)){
                    naj=ponovo;
                }
            }
            text="";
            proba.clear();
            rek="";
            bio=false;
            if(naj>=0)pravibfs(pon.substr(0,naj+1),x,y,0,now);
            i+=naj+1;
            if(i+1<nn){
                maxx=max(maxx,x);
                maxy=max(maxy,y);
                x++;
                reci[now].solution.pb('R');
                resenje[y][x]=rec[i];
                reci[now].start.pb({x-1,y-1});
                i++;
            }
            if(t==2 && y>150){
                if(i+1<nn){
                    y--;
                    reci[now].solution.pb('U');
                    resenje[y][x]=rec[i];
                    reci[now].start.pb({x-1,y-1});
                    i++;
                }
                if(i+1<nn){
                    maxx=max(maxx,x);
                    maxy=max(maxy,y);
                    x++;
                    reci[now].solution.pb('R');
                    reci[now].start.pb({x-1,y-1});
                    resenje[y][x]=rec[i];
                    i++;
                }
            }
            if(i+1<nn){
                maxx=max(maxx,x);
                maxy=max(maxy,y);
                x++;
                reci[now].solution.pb('R');
                resenje[y][x]=rec[i];
                reci[now].start.pb({x-1,y-1});
                i++;
            }
            maxx=max(maxx,x);
            maxy=max(maxy,y);
            if(temp+1<isto.size())temp++;
        }
    }
}
ll biomat[5000][maxN];
ll br=0;
ll brmax=60;
ll ajmoprobamax=-1;
bool nemavremenazarec=false;
ll ajmoproba(ll nowx,ll nowy,ll now,ll nowi,ll skor)
{
    if(float( clock () - begin_time_for_word ) /  CLOCKS_PER_SEC > time_alowed_for_word) nemavremenazarec=true;
    if(nemavremenazarec) return -1;
    //if(nemavremena)return -1;
    if(nowi==reci[now].n){
        br++;
        return skor;
    }
    //if(ajmoprobamax>skor+reci[now].n-nowi && ajmoprobamax>2)return -1;
    ll vrati=-1;
    char c = reci[now].sorce[nowi];
    if(resenje[nowy][nowx+1]==c || biomat[nowy][nowx+1]==c){
        vrati=max(vrati,ajmoproba(nowx+1,nowy,now,nowi+1,skor+1));
        ajmoprobamax=max(ajmoprobamax,vrati);
    }
    if(br>=reci[now].brmax)return vrati;
    if(resenje[nowy][nowx-1]==c || biomat[nowy][nowx-1]==c){
        vrati=max(vrati,ajmoproba(nowx-1,nowy,now,nowi+1,skor+1));
        ajmoprobamax=max(ajmoprobamax,vrati);
    }
    if(br>=reci[now].brmax)return vrati;
    if(resenje[nowy+1][nowx]==c || biomat[nowy+1][nowx]==c){
        vrati=max(vrati,ajmoproba(nowx,nowy+1,now,nowi+1,skor+1));
        ajmoprobamax=max(ajmoprobamax,vrati);
    }
    if(br>=reci[now].brmax)return vrati;
    if(resenje[nowy-1][nowx]==c || biomat[nowy-1][nowx]==c){
        vrati=max(vrati,ajmoproba(nowx,nowy-1,now,nowi+1,skor+1));
        ajmoprobamax=max(ajmoprobamax,vrati);
    }

    if(br>=reci[now].brmax)return vrati;
    if(resenje[nowy+1][nowx]==0 && biomat[nowy+1][nowx]==0){
        biomat[nowy+1][nowx]=c;
        vrati=max(vrati,ajmoproba(nowx,nowy+1,now,nowi+1,skor));
        ajmoprobamax=max(ajmoprobamax,vrati);
        biomat[nowy+1][nowx]=0;
    }

    if(br>=reci[now].brmax)return vrati;

    if(resenje[nowy][nowx+1]==0 && biomat[nowy][nowx+1]==0){
        biomat[nowy][nowx+1]=c;
        vrati=max(vrati,ajmoproba(nowx+1,nowy,now,nowi+1,skor));
        ajmoprobamax=max(ajmoprobamax,vrati);
        biomat[nowy][nowx+1]=0;
    }

    if(br>=reci[now].brmax)return vrati;
    if(resenje[nowy][nowx-1]==0 && biomat[nowy][nowx-1]==0){
        biomat[nowy][nowx-1]=c;
        vrati=max(vrati,ajmoproba(nowx-1,nowy,now,nowi+1,skor));
        ajmoprobamax=max(ajmoprobamax,vrati);
        biomat[nowy][nowx-1]=0;
    }
    if(br>=reci[now].brmax)return vrati;
    if(resenje[nowy-1][nowx]==0 && biomat[nowy-1][nowx]==0){
        biomat[nowy-1][nowx]=c;
        vrati=max(vrati,ajmoproba(nowx,nowy-1,now,nowi+1,skor));
        ajmoprobamax=max(ajmoprobamax,vrati);
        biomat[nowy-1][nowx]=0;
    }
    return vrati;
}
ll naj=-1;
void ajmo(ll nowx,ll nowy,ll now,ll nowi,ll score)
{
    if(score+reci[now].n-nowi<naj)return;
    //if(float( clock () - begin_time ) /  CLOCKS_PER_SEC >timelimit)nemavremena=true;
    //if(nemavremena)return;
    if(bio)return;
    if(nowi==reci[now].n){
        if(score<naj)return;
        bio=true;
        reci[now].solution+=rek;
        for(int i=0;i<reci[now].n;i++){
            reci[now].start.pb(proba[i]);
            resenje[proba[i].ss+1][proba[i].ff+1]=reci[now].sorce[i];
            maxx=max(proba[i].first+1, maxx);
            maxy=max(proba[i].second+1, maxy);
        }
        return;
    }
    char c = reci[now].sorce[nowi];
    if(resenje[nowy][nowx+1]==c || biomat[nowy][nowx+1]==c){
        rek+='R';
        proba.pb({nowx,nowy-1});
        ajmo(nowx+1,nowy,now,nowi+1,score+1);
        proba.pop_back();
        rek.pop_back();
    }
    if(bio)return;
    if(resenje[nowy][nowx-1]==c || biomat[nowy][nowx-1]==c){
        rek+='L';
        proba.pb({nowx-2,nowy-1});
        ajmo(nowx-1,nowy,now,nowi+1,score+1);
        proba.pop_back();
        rek.pop_back();
    }
    if(bio)return;
    if(resenje[nowy+1][nowx]==c || biomat[nowy+1][nowx]==c){
        rek+='D';
        proba.pb({nowx-1,nowy});
        ajmo(nowx,nowy+1,now,nowi+1,score+1);
        proba.pop_back();
        rek.pop_back();
    }
    if(bio)return;
    if(resenje[nowy-1][nowx]==c || biomat[nowy-1][nowx]==c){
        rek+='U';
        proba.pb({nowx-1,nowy-2});
        ajmo(nowx,nowy-1,now,nowi+1,score+1);
        proba.pop_back();
        rek.pop_back();
    }
    if(bio)return;

    if(resenje[nowy+1][nowx]==0 && biomat[nowy+1][nowx]==0){
        biomat[nowy+1][nowx]=c;
        rek+='D';
        proba.pb({nowx-1,nowy});
        ajmo(nowx,nowy+1,now,nowi+1,score);
        proba.pop_back();
        rek.pop_back();
        biomat[nowy+1][nowx]=0;
    }
    if(bio)return;

    if(resenje[nowy][nowx+1]==0 && biomat[nowy][nowx+1]==0){
        biomat[nowy][nowx+1]=c;
        rek+='R';
        proba.pb({nowx,nowy-1});
        ajmo(nowx+1,nowy,now,nowi+1,score);
        proba.pop_back();
        rek.pop_back();
        biomat[nowy][nowx+1]=0;
    }
    if(bio)return;

    if(resenje[nowy][nowx-1]==0 && biomat[nowy][nowx-1]==0){
        biomat[nowy][nowx-1]=c;
        rek+='L';
        proba.pb({nowx-2,nowy-1});
        ajmo(nowx-1,nowy,now,nowi+1,score);
        proba.pop_back();
        rek.pop_back();
        biomat[nowy][nowx-1]=0;
    }
    if(bio)return;
    if(resenje[nowy-1][nowx]==0 && biomat[nowy-1][nowx]==0){
        biomat[nowy-1][nowx]=c;
        rek+='U';
        proba.pb({nowx-1,nowy-2});
        ajmo(nowx,nowy-1,now,nowi+1,score);
        proba.pop_back();
        rek.pop_back();
        biomat[nowy-1][nowx]=0;
    }
    return;
}
void resivreme(ll now)
{
    x=maxx+1;
    y=maxy;
    bool gore=true;
    while(now<n){
        if(reci[now].nacin!=-1){
            now++;
            continue;
        }
        ll cnt=0;
        while(cnt<reci[now].n){
            if(gore && y>2){
                y--;
                resenje[y][x]=reci[now].sorce[cnt];
                if(cnt)reci[now].solution.pb('U');
                reci[now].start.pb({x-1,y-1});
            }
            else if(gore && y==2){
                x++;
                resenje[y][x]=reci[now].sorce[cnt];
                if(cnt)reci[now].solution.pb('R');
                reci[now].start.pb({x-1,y-1});
                gore=false;
            }
            else if(gore==false && y<maxy-1){
                y++;
                resenje[y][x]=reci[now].sorce[cnt];
                if(cnt)reci[now].solution.pb('D');
                reci[now].start.pb({x-1,y-1});
            }
            else if(gore==false && y==maxy-1){
                x++;
                resenje[y][x]=reci[now].sorce[cnt];
                if(cnt)reci[now].solution.pb('R');
                reci[now].start.pb({x-1,y-1});
                gore=true;
            }
            cnt++;
        }
        now++;
    }
    return;
}
void resi3()
{
    y+=300;
    proseky=y;
    x+=30;
    for(int i=0;i<4000;i++){
        resenje[i][0]=-1;
        resenje[i][maxN-1]=-1;
    }
    for(int i=0;i<maxN;i++){
        resenje[0][i]=-1;
        resenje[4000-1][i]=-1;
    }
    set<pair<ll,ll>> mesta[40];
    for(int i=0;i<n;i++){
        if(reci[i].nacin==-1){
            reci[i].nacin=alreadyIn(i);
            if(reci[i].nacin==2)continue;
            if(mesta[reci[i].sorce[0]-'a'].empty()){
                while(resenje[y][x]>0)
                        x++;
                naj=-1;
                pair<ll,ll> mesto={x,y};
                nemavremenazarec=false;
                resenje[y][x]=reci[i].sorce[0];
                begin_time_for_word = clock();
                time_alowed_for_word= vremePoSlovu *(double)reci[i].n;
                br=0;
                ajmoprobamax=-1;
                ll temp=ajmoproba(x,y,i,1,1);
                if(float( clock () - begin_time ) /  CLOCKS_PER_SEC > timelimit) nemavremena=true;
                if(nemavremena){
                    naj=-1;
                    break;
                }
                if(temp>naj){
                    naj=temp;
                }

                if(naj==-1){
                    resenje[y][x]=0;
                    if(nemavremena){
                        resivreme(i);
                        return;
                    }
                    while(resenje[y][x]>0)
                        x++;
                    bool nasao=false;
                    while(!nasao){
                        bool moze=true;
                        for(int j=0;j<reci[i].n;j++){
                            if(resenje[y][x+j]){
                                x=x+j+1;
                                moze=false;
                                break;
                            }
                        }
                        if(moze)nasao=true;
                    }
                    for(int j=0;j<reci[i].n;j++){
                        if(j)reci[i].solution.pb('R');
                        reci[i].start.pb({x-1,y-1});
                        resenje[y][x]=reci[i].sorce[j];
                        x++;
                    }
                    maxx=max(maxx,x);
                }
                else{
                    proba.clear();
                    proba.pb({mesto.ff-1,mesto.ss-1});
                    rek="";
                    bio=false;
                    ajmo(mesto.ff,mesto.ss,i,1,1);
                    proba.pop_back();
                }
            }
            else{
                naj=-1;
                pair<ll,ll> mesto={0,0};
                nemavremenazarec=false;
                begin_time_for_word = clock();
                time_alowed_for_word= vremePoSlovu *(double)reci[i].n;
                for(auto j: mesta[reci[i].sorce[0]-'a']){
                    br=0;
                    ajmoprobamax=-1;
                    ll temp=ajmoproba(j.ff,j.ss,i,1,1);
                    if(float( clock () - begin_time ) /  CLOCKS_PER_SEC > timelimit) nemavremena=true;
                    if(nemavremena){
                        naj=-1;
                        break;
                    }
                    if(temp>naj){
                        naj=temp;
                        mesto=j;
                    }
                    if(nemavremenazarec)break;
                }
                if(naj==-1){
                    naj=-1;
                    while(resenje[y][x]>0)
                        x++;
                    pair<ll,ll> mesto={x,y};
                    nemavremenazarec=false;
                    resenje[y][x]=reci[i].sorce[0];
                    begin_time_for_word = clock();
                    time_alowed_for_word= vremePoSlovu *(double)reci[i].n;

                    br=0;
                    ajmoprobamax=-1;
                    ll temp=ajmoproba(x,y,i,1,1);
                    if(float( clock () - begin_time ) /  CLOCKS_PER_SEC > timelimit) nemavremena=true;
                    if(nemavremena){
                        naj=-1;
                        break;
                    }
                    if(temp>naj){
                        naj=temp;
                    }
                    if(naj==-1){
                        resenje[y][x]=0;
                        if(nemavremena){
                            resivreme(i);
                            return;
                        }
                        while(resenje[y][x]>0)
                            x++;
                        bool nasao=false;
                        while(!nasao){
                            bool moze=true;
                            for(int j=0;j<reci[i].n;j++){
                                if(resenje[y][x+j]){
                                    x=x+j+1;
                                    moze=false;
                                    break;
                                }
                            }
                            if(moze)nasao=true;
                        }
                        for(int j=0;j<reci[i].n;j++){
                            if(j)reci[i].solution.pb('R');
                            reci[i].start.pb({x-1,y-1});
                            resenje[y][x]=reci[i].sorce[j];
                            x++;
                        }
                        maxx=max(maxx,x);
                    }
                    else{
                        proba.clear();
                        proba.pb({mesto.ff-1,mesto.ss-1});
                        rek="";
                        bio=false;
                        ajmo(mesto.ff,mesto.ss,i,1,1);
                        proba.pop_back();
                    }
                }
                else{
                    proba.clear();
                    proba.pb({mesto.ff-1,mesto.ss-1});
                    rek="";
                    bio=false;
                    ajmo(mesto.ff,mesto.ss,i,1,1);
                    proba.pop_back();
                }
            }
            for(int j=0;j<reci[i].n;j++){
                mesta[reci[i].sorce[j]-'a'].insert({reci[i].start[j].ff+1,reci[i].start[j].ss+1});
                maxx=max(maxx,reci[i].start[j].ff+1);
                maxy=max(maxy,reci[i].start[j].ss+1);
            }
        }
    }
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    begin_time = clock();
    make_pows(p,mod);
    kombinuj(1,26);

    freopen("crossword.in","r", stdin);
    freopen("crossword.out","w", stdout);

    cin >> t >> n;
    for(int i=0;i<n;i++){
        string now;
        cin >> now;
        rec temp;
        temp.n=now.size();
        temp.sorce=now;
        temp.index=i;
        temp.hasheds=hashuj(now);
        temp.nacin=-1;
        temp.solution="";
        temp.brmax=100;
        if(temp.n<=30)temp.brmax=1000;
        else if(temp.n<=80)temp.brmax=200;
        else if(temp.n<=150)temp.brmax=120;
        maxi=max(maxi,temp.n);
        suman+=temp.n;
        reci.pb(temp);
    }

    vremePoSlovu = timelimit/(double)suman;
    sort(reci.begin(),reci.end(),cmpbegin);

    nacini();
    if(t!=2 && maxi<=400){
        resi3();
    }
    for(int i=0;i<n;i++){
        if(reci[i].nacin==0){
            ispisi0(i);
        }
        else if(reci[i].nacin==1){
            ispisi1(i);
        }
        else{
            if(t!=2 && maxi<=400)continue;
            reci[i].nacin=alreadyIn(i);
            if(reci[i].nacin == 2)continue;
            postavi(i);
            x+=2;
            y=2;
        }
    }
    sort(reci.begin(),reci.end(),cmpend);
    maxx=max(maxx,x);
    maxy=max(maxy,y);

    cout << maxx+5 << ' ' << maxy+5 << endl;
    for(int i=1;i<=maxy+5;i++){
        for(int j=1;j<=maxx+5;j++){
            if(resenje[i][j]==0)resenje[i][j]='#';
            cout << resenje[i][j];
        }
        cout << endl;
    }
    for(int i=0;i<n;i++){
        cout << reci[i].start[0].ff << ' ' << reci[i].start[0].ss << ' ';
        cout << reci[i].solution << endl;
    }

    return 0;
}
