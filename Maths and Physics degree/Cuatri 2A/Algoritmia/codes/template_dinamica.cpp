using namespace std;
#include<iostream>
#include<vector>

using ll = long long;
using VL = vector<ll>;
using VVL = vector<VL>;

VL F = VL(101,-1);

ll f(int i){
  if(i==0) return 0;
  if(F[i]!=-1) return F[i];
  return (cosas con f(i-1), f(i-2), ...);
}

