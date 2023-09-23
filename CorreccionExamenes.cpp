#include <vector>
#include <iostream>
#include <string>
#include <tuple>
#include <algorithm>
using namespace std;


int INF = 1000000000;
vector<long long > M;
vector<long long > C;
vector<bool> used;
const int mod = 1000000007;
vector<tuple<long long, long long, int>> relac;

bool comparaCostos(const tuple<long long, long long, int>& a, const tuple<long long, long long, int>& b) {

    long long costoA = get<1>(a);
    long long costoB = get<1>(b);
    long long tiempoA = get<0>(a);
    long long tiempoB = get<0>(b);

    long long primero = ((get<0>(a) * get<1>(b)) % mod);
    long long segundo = (get<0>(b) * get<1>(a)) % mod;

    if ((costoA * tiempoB > mod && costoB * tiempoA <= mod)) {
        return true;
    }
    if ((costoA * tiempoB <= mod && costoB * tiempoA > mod)) {
        return false;
    } else {
        return (primero < segundo);
    }
}

long long parciales(int tiempo) {
    int idx = 0;
    long long  costAcumulado = 0;
    long long  tAcum = 0;
    for(int i = 0;i<relac.size();i++){
        idx = get<2>(relac[i]);
        tAcum = (tAcum + M[idx])%mod;
        long long prueba = C[idx];
        long long  nuevoCosto = (((tAcum)%mod)*C[idx])%mod;
        costAcumulado = (costAcumulado + nuevoCosto)%mod;
    }
    return costAcumulado%mod;
}



int main(){
    int c;
    cin >> c;
    while(c--){
        int n, m_i, c_i;
        cin >> n;
        M.clear();
        C.clear();
        relac.clear();

        used.resize(n, false);
        for (int i = 0; i < n; i++){
            cin >> m_i;
            M.push_back(m_i);
        }
        for (int i = 0; i < n; i++) {
            cin >> c_i;
            C.push_back(c_i);
        }
        for(int i = 0;i<C.size();i++) {

            relac.emplace_back(M[i],C[i],i);
        }
        sort(relac.begin(), relac.end(),comparaCostos);
        vector<tuple<long long, long long, int>> copia = relac;
        cout << parciales(0) << endl;
    }
    return 0;
}