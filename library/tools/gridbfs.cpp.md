---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: tools/gridbfs.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4a931512ce65bdc9ca6808adf92d8783">tools</a>
* <a href="{{ site.github.repository_url }}/blob/master/tools/gridbfs.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-18 14:43:35+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/test/aoj/0558.test.cpp.html">test/aoj/0558.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#ifndef call_from_test
#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
vector< vector<int> >
gridbfs(vector<string> &st,int sy,int sx,char wall,int dir){
  int h=st.size(),w=st.front().size();
  vector<vector<int> > dp(h,vector<int>(w,-1));
  using P = pair<int, int>;
  queue<P> qu;

  dp[sy][sx]=0;
  qu.emplace(sy,sx);

  int dy[]={1,-1,0,0,1,1,-1,-1};
  int dx[]={0,0,1,-1,1,-1,1,-1};
  auto in=[&](int y,int x){return 0<=y&&y<h&&0<=x&&x<w;};

  while(!qu.empty()){
    int y,x;
    tie(y,x)=qu.front();qu.pop();
    for(int k=0;k<dir;k++){
      int ny=y+dy[k],nx=x+dx[k];
      if(!in(ny,nx)||st[ny][nx]==wall) continue;
      if(~dp[ny][nx]) continue;
      dp[ny][nx]=dp[y][x]+1;
      qu.emplace(ny,nx);
    }
  }

  return dp;
}
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed main(){
  return 0;
}
#endif

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "tools/gridbfs.cpp"

#include<bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
vector< vector<int> >
gridbfs(vector<string> &st,int sy,int sx,char wall,int dir){
  int h=st.size(),w=st.front().size();
  vector<vector<int> > dp(h,vector<int>(w,-1));
  using P = pair<int, int>;
  queue<P> qu;

  dp[sy][sx]=0;
  qu.emplace(sy,sx);

  int dy[]={1,-1,0,0,1,1,-1,-1};
  int dx[]={0,0,1,-1,1,-1,1,-1};
  auto in=[&](int y,int x){return 0<=y&&y<h&&0<=x&&x<w;};

  while(!qu.empty()){
    int y,x;
    tie(y,x)=qu.front();qu.pop();
    for(int k=0;k<dir;k++){
      int ny=y+dy[k],nx=x+dx[k];
      if(!in(ny,nx)||st[ny][nx]==wall) continue;
      if(~dp[ny][nx]) continue;
      dp[ny][nx]=dp[y][x]+1;
      qu.emplace(ny,nx);
    }
  }

  return dp;
}
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed main(){
  return 0;
}
#endif

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
