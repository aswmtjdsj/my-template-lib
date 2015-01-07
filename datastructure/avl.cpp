#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define type int
using namespace std;

template <class T>
class node {
	public:
		T dt;
		int size;
		node *l, *r, *pa;	

		void init(T _dt, node *t) {
			l = r = NULL;
			pa = t;
			size = 1;
			dt = _dt;
		}

		node(): l(NULL), r(NULL), pa(NULL) {
		}
};

template <class T>
class avl {
	public:
		node<T> * root;
		avl(): root(NULL) {
		}

		void update(node<T> * &t) {
			puts("update");
			int a,b;

			if(t->l != NULL) {
				a = t->l->size;
			} else {
				a = 0;
			}

			if(t->r != NULL) {
				b = t->r->size;
			} else {
				b = 0;
			}

			t->size = a + b + 1;
		}

		node<T> * zig(node<T> * &t) { //parent to left child
			puts("zig");
			node<T> * q = t->r;
			//swap(t->dt,q->dt);
			if(t->pa != NULL) {
				if(t->pa->l == t) {
					t->pa->l = q;
				} else if(t->pa->r == t) {
					t->pa->r = q;
				}
			}
			puts("zig2");
			//q is null then what????
			q->pa = t->pa;
			t->pa = q;
			t->r = q->l;
			if(q->l != NULL) {
				q->l->pa = t;
			}
			q->l = t;
			//after change ,no break
			//before change , no min
			update(q);
			update(t);
			return q;
		}

		node<T> * zag(node<T> * &t) { //parent to right child
			puts("zag");
			node<T> * q = t->l;
			//swap(t->dt,q->dt);
			if(t->pa != NULL) {
				if(t->pa->l == t) {
					t->pa->l = q;
				} else if(t->pa->r == t) {
					t->pa->r = q;
				}
			}

			q->pa = t->pa;
			t->pa = q;
			t->l = q->r;

			if(q->r != NULL) {
				q->r->pa = t;
			}
			q->r = t;
			update(q);
			update(t);

			return q;
		}

		node<T> * adjust(node<T> * &t) {
			puts("adjust");
			int a,b;
			if(t->l == NULL) {
				a = 0;
			} else {
				a = t->l->size;
			}

			if(t->r == NULL) {
				b = 0;
			} else {
				b = t->r->size;
			}

			if(a - b > 2) {
				t = zag(t);
			} else if(b - a > 2) {
				t = zig(t);
			}

			update(t);

			return t;
		}

		void insert(T x, node<T> * &t, node<T> * pr)//t is a reference pointer...
		{
			puts("insert");
			if(t == NULL) {
				t = new node<T>();//apply memory
				t->init(x, pr);//initialize
				//return t;
				return ;
			}

			if(x < t->dt) {
				insert(x, t->l, t);
				t = adjust(t);
			} else {
				insert(x, t->r, t);
				t = adjust(t);
			} //we assume that all the elements here are different
		}

		bool find(T x,node<T> * t) {
			if(t == NULL) {
				return false;
			}

			if(x == t->dt) {
				return true;
			} else if(x < t->dt) {
				return find(x,t->l);
			} else {
				return find(x,t->r);
			}
		}

		node<T> * max() {
			node<T> * t = root;
			while(t->r != NULL) {
				printf("trace: %d\n", t->dt);
				t = t->r;
			}
			return t;
		}

		node<T> * min() {
			node<T> * t = root;
			while(t->l != NULL) {
				t = t->l;
			}
			return t;
		}
};
int main()
{
	avl<int> tree;
	int num;
	while(scanf("%d",&num) == 1)
	{
		tree.insert(num,tree.root,NULL);
		printf("max:%d\n",tree.max()->dt);
		printf("min:%d\n",tree.min()->dt);
	}
}
