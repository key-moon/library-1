#ifndef call_from_test
#include <bits/stdc++.h>
using namespace std;
#endif
//BEGIN CUT HERE
template<typename Vertex, typename Cluster, size_t LIM>
struct TopTree{
  enum Type { Compress, Rake, Edge, None };
  struct Node{
    Vertex* vs[2];
    Cluster dat;
    Node* p;
    Node* q;
    Node* ch[2];
    bool rev,guard;
    Type type;
    Node():p(nullptr),q(nullptr),rev(false),guard(false),type(Type::None){}
  };

  static array<Vertex, LIM> pool_v;
  static array<Node, LIM> pool_c;
  size_t ptr_v,ptr_c;

  Cluster id;
  TopTree(Cluster id=Cluster()):ptr_v(0),ptr_c(0),id(id){}

  inline Vertex* create(Vertex v){
    auto t=&pool_v[ptr_v++];
    auto dummy=&pool_v[ptr_v++];
    *t=v;
    link(t,id,dummy);
    return t;
  }

  inline Node* edge(Vertex* u,Cluster w,Vertex* v){
    auto t=&(pool_c[ptr_c++]);
    t->vs[0]=u;t->vs[1]=v;t->dat=w;t->type=Type::Edge;
    return pushup(t);
  }

  inline Node* compress(Node* l,Node* r){
    auto t=&(pool_c[ptr_c++]);
    t->ch[0]=l;t->ch[1]=r;t->type=Type::Compress;
    return pushup(t);
  }

  inline Node* rake(Node* l,Node* r){
    auto t=&(pool_c[ptr_c++]);
    t->ch[0]=l;t->ch[1]=r;t->type=Type::Rake;
    return pushup(t);
  }

  int parent_dir(Node* t){
    Node* p=t->p;
    if(!p) return -1;
    if(p->guard) return -1;
    if(p->ch[0]==t) return 0;
    if(p->ch[1]==t) return 1;
    return -1;
  }

  inline Node* pushup(Node* const t){
    Node* const l=t->ch[0];
    Node* const r=t->ch[1];

    if(t->type==Type::Edge){
      if(!t->p){
	t->vs[0]->handle=t;
	t->vs[1]->handle=t;
      }else if(t->p->type==Type::Compress){
	if(parent_dir(t)==-1)
	  t->vs[0]->handle=t;
      }else if(t->p->type==Type::Rake){
	t->vs[0]->handle=t;
      }
    }else if(t->type==Type::Compress){
      assert(l->vs[1]==r->vs[0]);
      t->vs[0]=l->vs[0];
      t->vs[1]=r->vs[1];

      Cluster lf=l->dat;
      if(t->q){
	Node* q=t->q;
	assert(l->vs[1]==q->vs[1]);
	lf=Cluster::rake(l->dat,q->dat,q->vs[0]);
      }
      t->dat=Cluster::compress(lf,r->vs[0],r->dat);

      l->vs[1]->handle=t;
      if(!t->p){
	t->vs[0]->handle=t;
	t->vs[1]->handle=t;
      }else if(t->p->type==Type::Compress){
	if(parent_dir(t)==-1)
	  t->vs[0]->handle=t;
      }else if(t->p->type==Type::Rake){
	t->vs[0]->handle=t;
      }
    }else if(t->type==Type::Rake){
      propagate(t);
      assert(l->vs[1]==r->vs[1]);
      t->vs[0]=l->vs[0];
      t->vs[1]=l->vs[1];
      t->dat=Cluster::rake(l->dat,r->dat,r->vs[0]);
    }else abort();
    return t;
  }


  int parent_dir_ignore_guard(Node* t){
    Node* p=t->p;
    if(!p) return -1;
    if(p->ch[0]==t) return 0;
    if(p->ch[1]==t) return 1;
    return -1;
  }

  void rotate(Node* t,Node* x,size_t dir){
    Node* y=x->p;
    int par=parent_dir_ignore_guard(x);
    propagate(t->ch[dir]);
    x->ch[dir^1]=t->ch[dir];
    t->ch[dir]->p=x;
    t->ch[dir]=x;
    x->p=t;
    t->p=y;
    if(~par) y->ch[par]=t;
    else if(y and y->type==Type::Compress) y->q=t;
    pushup(x);pushup(t);
    if(y and !y->guard) pushup(y);
  }

  inline void propagate(Node* t){
    if(t->type==Type::Compress){
      if(t->rev){
	assert(t->ch[0] and t->ch[1]);
	swap(t->ch[0],t->ch[1]);
	toggle(t->ch[0]);
	toggle(t->ch[1]);
	t->rev=false;
      }
    }
  }

  inline void toggle(Node* t){
    if(t->type==Type::Edge){
      swap(t->vs[0],t->vs[1]);
      t->dat.toggle();
    }else if(t->type==Type::Compress){
      swap(t->vs[0],t->vs[1]);
      t->dat.toggle();
      t->rev^=true;
    }else if(t->type==Type::Rake){
    }else abort();
  }

  void splay(Node* t){
    assert(t->type!=Type::Edge);
    propagate(t);

    while(~parent_dir(t)){
      Node* q=t->p;
      if(q->type!=t->type) break;
      if(~parent_dir(q) and q->p and q->p->type==q->type){
	Node* r=q->p;
	if(r->p) propagate(r->p);
	propagate(r);propagate(q);propagate(t);
	int qt_dir=parent_dir(t);
	int rq_dir=parent_dir(q);
	if(rq_dir==qt_dir){
	  rotate(q,r,rq_dir^1);
	  rotate(t,q,qt_dir^1);
	}else{
	  rotate(t,q,qt_dir^1);
	  rotate(t,r,rq_dir^1);
	}
      }else{
	if(q->p) propagate(q->p);
	propagate(q);propagate(t);
	int qt_dir=parent_dir(t);
	rotate(t,q,qt_dir^1);
      }
    }
  }

  void pushdown(Node* t){
    if(!t) return;
    pushdown(t->p);
    propagate(t);
  }

  Node* expose(Node* t){
    pushdown(t);
    while(true){
      assert(t->type!=Type::Rake);
      if(t->type==Type::Compress) splay(t);
      Node* n=nullptr;
      {
	Node* p=t->p;
	if(!p) break;
	if(p->type==Type::Rake){
	  propagate(p);
	  splay(p);
	  n=p->p;
	}else if(p->type==Type::Compress){
	  propagate(p);
	  if(p->guard and ~parent_dir_ignore_guard(t)) break;
	  n=p;
	}else abort();
      }
      splay(n);
      int dir=parent_dir_ignore_guard(n);
      if(dir==-1 or n->p->type==Type::Rake) dir=0;

      Node* const c=n->ch[dir];
      if(dir==1){
	toggle(c);
	propagate(c);
	toggle(t);
	propagate(t);
      }
      int n_dir=parent_dir(t);
      if(~n_dir){
	propagate(c);
	Node* const r=t->p;
	propagate(r);
	r->ch[n_dir]=c;
	c->p=r;
	n->ch[dir]=t;
	t->p=n;
	pushup(c);pushup(r);pushup(t);pushup(n);
	splay(r);
      }else{
	propagate(c);
	n->q=c;
	c->p=n;
	n->ch[dir]=t;
	t->p=n;
	pushup(c);pushup(t);pushup(n);
      }
      if(t->type==Type::Edge) t=n;
    }
    return t;
  }

  Node* expose(Vertex* v){
    return expose((Node*)(v->handle));
  }

  Node* link(Vertex* u,Cluster w,Vertex* v){
    if(!u->handle and !v->handle) return edge(u,w,v);

    Node* nnu=(Node*)u->handle;
    Node* nnv=(Node*)v->handle;
    Node* ee=edge(u,w,v);
    Node* ll=nullptr;

    if(!nnv) ll=ee;
    else{
      Node* vv=expose(nnv);
      propagate(vv);
      if(vv->vs[1]==v){
	toggle(vv);
	propagate(vv);
      }
      if(vv->vs[0]==v){
	Node* nv=compress(ee,vv);
	ee->p=nv;
	pushup(ee);
	vv->p=nv;
	pushup(vv);pushup(nv);
	ll=nv;
      }else{
	Node* nv=vv;
	Node* ch=nv->ch[0];
	propagate(ch);
	nv->ch[0]=ee;
	ee->p=nv;
	pushup(ee);

	Node* bt=nv->q;
	Node* rk=nullptr;
	if(bt){
	  propagate(bt);
	  rk=rake(bt,ch);
	  bt->p=rk;
	  ch->p=rk;
	  pushup(bt);pushup(ch);
	}else{
	  rk=ch;
	}
	nv->q=rk;
	rk->p=nv;
	pushup(rk);pushup(nv);
	ll=nv;
      }
    }

    if(nnu){
      Node* uu=expose(nnu);
      propagate(uu);
      if(uu->vs[0]==u){
	toggle(uu);
	propagate(uu);
      }
      if(uu->vs[1]==u){
	Node* tp=compress(uu,ll);
	uu->p=tp;
	ll->p=tp;
	pushup(uu);pushup(ll);pushup(tp);
      }else{
	Node* nu=uu;
	Node* ch=nu->ch[1];
	toggle(ch);
	propagate(ch);

	nu->ch[1]=ll;
	ll->p=nu;
	pushup(ll);

	Node* al=nu->q;
	Node* rk=nullptr;
	if(al){
	  propagate(al);
	  rk=rake(al,ch);
	  al->p=rk;
	  ch->p=rk;
	  pushup(al);pushup(ch);
	}else{
	  rk=ch;
	}
	nu->q=rk;
	rk->p=nu;
	pushup(rk);pushup(nu);
      }
    }
    return ee;
  }

  void set_toggle(Node* v){
    toggle(v);propagate(v);
  }

  void soft_expose(Vertex* u,Vertex* v){
    pushdown((Node*)u->handle);
    pushdown((Node*)v->handle);
    Node* rt=expose((Node*)u->handle);

    if(u->handle==v->handle){
      if(rt->vs[1]==u or rt->vs[0]==v)
	set_toggle(rt);
      return;
    }

    rt->guard=true;
    Node* soft=expose((Node*)v->handle);
    rt->guard=false;

    pushup(rt);
    if(parent_dir(soft)==0) set_toggle(rt);
  }

  Cluster query(Vertex* u,Vertex* v){
    soft_expose(u,v);
    Node* rt=(Node*)u->handle;
    propagate(rt);

    if(rt->vs[0]==u and rt->vs[1]==v) return rt->dat;
    if(rt->vs[0]==u) return rt->ch[0]->dat;
    if(rt->vs[1]==v) return rt->ch[1]->dat;
    propagate(rt->ch[1]);
    return rt->ch[1]->ch[0]->dat;
  }

  void bring(Node* rt){
    Node* rk=rt->q;
    if(!rk){
      Node* ll=rt->ch[0];
      ll->p=nullptr;
      pushup(ll);
    }else if(rk->type==Type::Compress or rk->type==Type::Edge){
      propagate(rk);

      Node* nr=rk;
      set_toggle(nr);
      rt->ch[1]=nr;
      nr->p=rt;
      rt->q=nullptr;

      pushup(nr);pushup(rt);
    }else if(rk->type==Type::Rake){
      propagate(rk);
      while(rk->ch[1]->type==Type::Rake){
	propagate(rk->ch[1]);
	rk=rk->ch[1];
      }
      pushdown(rk);

      rt->guard=true;
      splay(rk);
      rt->guard=false;

      Node* ll=rk->ch[0];
      Node* rr=rk->ch[1];
      propagate(ll);
      set_toggle(rr);

      rt->ch[1]=rr;
      rr->p=rt;

      rt->q=ll;
      ll->p=rt;

      pushup(ll);pushup(rr);pushup(rt);
    }
  }

  void cut(Vertex* u,Vertex *v){
    soft_expose(u,v);
    Node* rt=(Node*)u->handle;
    propagate(rt);
    Node* rr=rt->ch[1];
    rr->p=nullptr;
    set_toggle(rr);
    bring(rr);bring(rt);
  }
};
template<typename Vertex, typename Cluster, size_t LIM>
array<Vertex, LIM> TopTree<Vertex, Cluster, LIM>::pool_v;
template<typename Vertex, typename Cluster, size_t LIM>
array<typename TopTree<Vertex, Cluster, LIM>::Node, LIM>
TopTree<Vertex, Cluster, LIM>::pool_c;
//END CUT HERE
#ifndef call_from_test
//INSERT ABOVE HERE
signed main(){
  AOJ_1595();
  return 0;
}
#endif
