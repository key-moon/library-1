#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../bbst/basic/dual.cpp"
#undef call_from_test

signed main(){
  int n,q;
  cin>>n>>q;

  auto h=[](int a,int b){return a+b;};
  int ei=0;
  RBST<int> rbst(h,ei);
  auto rt=rbst.init(n);

  for(int i=0;i<q;i++){
    int tp;
    cin>>tp;
    if(tp==0){
      int s,t,x;
      cin>>s>>t>>x;
      s--;
      rt=rbst.update(rt,s,t,x);
    }
    if(tp==1){
      int s;
      cin>>s;
      s--;
      cout<<rbst.get_val(rt,s)<<"\n";
    }
  }
  cout<<flush;
  return 0;
}