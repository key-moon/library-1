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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: test/yosupo/multipoint_evaluation.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/test/yosupo/multipoint_evaluation.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-23 19:42:36+09:00


* see: <a href="https://judge.yosupo.jp/problem/multipoint_evaluation">https://judge.yosupo.jp/problem/multipoint_evaluation</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/convolution/numbertheoretictransform.cpp.html">convolution/numbertheoretictransform.cpp</a>
* :heavy_check_mark: <a href="../../../library/mod/mint.cpp.html">mod/mint.cpp</a>
* :heavy_check_mark: <a href="../../../library/polynomial/formalpowerseries.cpp.html">polynomial/formalpowerseries.cpp</a>
* :heavy_check_mark: <a href="../../../library/polynomial/multieval.cpp.html">polynomial/multieval.cpp</a>
* :heavy_check_mark: <a href="../../../library/tools/fastio.cpp.html">tools/fastio.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"

#include<bits/stdc++.h>
using namespace std;

#define call_from_test
#include "../../tools/fastio.cpp"
#include "../../mod/mint.cpp"
#include "../../convolution/numbertheoretictransform.cpp"
#include "../../polynomial/formalpowerseries.cpp"
#include "../../polynomial/multieval.cpp"
#undef call_from_test

signed main(){
  int n,m;
  cin>>n>>m;

  NTT<2> ntt;
  using M = NTT<2>::M;
  auto conv=[&](auto as,auto bs){return ntt.multiply(as,bs);};
  MultiEval<M> me(conv);

  vector<M> cs(n),ps(m);
  for(int i=0;i<n;i++) cin>>cs[i].v;
  for(int i=0;i<m;i++) cin>>ps[i].v;

  auto ans=me.build(cs,ps);
  for(int i=0;i<m;i++){
    if(i) cout<<" ";
    cout<<ans[i];
  }
  cout<<endl;
  return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 340, in write_contents
    bundler.update(self.file_class.file_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/bundle.py", line 154, in update
    self.update(self._resolve(included, included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/bundle.py", line 123, in update
    raise BundleError(path, i + 1, "found codes out of include guard")
onlinejudge_verify.bundle.BundleError: tools/fastio.cpp: line 5: found codes out of include guard

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
