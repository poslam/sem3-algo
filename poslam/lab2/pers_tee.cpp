#include <algorithm>
#include <vector>

using namespace std;

struct Segtree
{
    int lb, rb;
    int s = 0;
    Segtree *l = 0, *r = 0;
    
    Segtree(int lb, int rb) 
    {
        this->lb = lb;
        this->rb = rb;

        if (lb != rb)
        {
            int t = (lb + rb) / 2;
            l = new Segtree(lb, t);
            r = new Segtree(t, rb);
        }
    }
    void copy()
    {
        if (l)
        {
            l = new Segtree(*l);
            r = new Segtree(*r);
        }
    }
    void add(int k, int x)
    {
        copy();
        s += x;
        if (l)
        {
            if (k < l->rb)
                l->add(k, x);
            else
                r->add(k, x);
        }
    }

    int sum(int lq, int rq)
    {
        // этот метод ничего не меняет -- он и так хороший
        if (lq <= lb && rb <= rq)
            return s;
        if (max(lb, lq) >= min(rb, rq))
            return 0;
        return l->sum(lq, rq) + r->sum(lq, rq);
    }
};

int main()
{

    vector<Segtree *> roots;

    roots.push_back(new Segtree(0, 2));

    // void add(int k, int x, int v)
    // {
    //     Segtree *root = new Segtree(*roots[v]);
    //     root->add(k, x);
    //     roots.push_back(root);
    // }
}