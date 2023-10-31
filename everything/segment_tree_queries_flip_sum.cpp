struct node{
    ll val1 = 0;
    ll val2 = 0;
    ll lazy = 0;
    ll cnt1 = 0;
    ll cnt2 = 0;
    ll sm1 = 0;
    ll sm2 = 0;

    node(){
        val1 = 0;
        val2 = 0;
        lazy = 0;

        cnt1 = cnt2 = sm1 = sm2 = 0;
    }

    node(ll v){
        val2 = v;
        val1 = 0;
        lazy = 0;
        cnt1 = cnt2 = sm1 = sm2 = 0;
    }

    void merge(node &n1, node &n2){
        val1 = n1.val1 + n2.val1;
        val2 = n1.val2 + n2.val2;
        cnt1 = n1.cnt1 + n2.cnt1;
        cnt2 = n1.cnt2 + n2.cnt2;
        sm1 = n1.sm1 + n2.sm1;
        sm2 = n1.sm2 + n2.sm2;
    }
};

class LazySegTree{
public:
    ll n;
    vector<node> tree;
    string arr;

    LazySegTree(ll n, string arr){
        this->n = n;
        this->arr = arr;
        tree.resize(4*n + 10);

        fill(tree.begin(), tree.end(), node());
    }

    void build(ll ind, ll tl, ll tr){
        if(tl == tr){
            if(arr[tl] == '0'){
                tree[ind].val1 = (tl + 1ll) * (tl + 1ll);
                tree[ind].cnt1++;
                tree[ind].sm1 += (tl + 1ll);
            }

            else{
                tree[ind].val2 = (tl + 1ll) * (tl + 1ll);
                tree[ind].cnt2++;
                tree[ind].sm2 += (tl + 1ll);
            }

            return;
        }

        ll tm = (tl + tr) / 2;

        build(2*ind + 1, tl, tm);
        build(2*ind + 2, tm+1, tr);

        tree[ind].merge(tree[2*ind + 1], tree[2*ind + 2]);
    }

    void performUpdate(ll ind, ll tl, ll tr, ll upd){
        if(upd == 1){
            swap(tree[ind].val1, tree[ind].val2);            
            swap(tree[ind].cnt1, tree[ind].cnt2);
            swap(tree[ind].sm1, tree[ind].sm2);
        }

        if(tr != tl){
            tree[2*ind + 1].lazy ^= upd;
            tree[2*ind + 2].lazy ^= upd;
        }
    }
            
    node query(ll ind, ll tl, ll tr, ll l, ll r){
        if(tl > tr || tl > r || tr < l){
            return node(0);
        }

        performUpdate(ind, tl, tr, tree[ind].lazy);
        tree[ind].lazy = 0;

        if(tl >= l && tr <= r)
            return tree[ind];

        ll tm = (tl + tr) / 2;

        node left = query(2*ind + 1, tl, tm, l, r);
        node right = query(2*ind + 2, tm + 1, tr, l, r);

        node temp(0);
        temp.merge(left, right);

        return temp;
    }

    void update(ll ind, ll tl, ll tr, ll l, ll r, ll val){
        performUpdate(ind, tl, tr, tree[ind].lazy);
        tree[ind].lazy = 0;

        if(tl > tr || tl > r || tr < l)
            return; 

        if(tl >= l && tr <= r){
            performUpdate(ind, tl, tr, val);
            return;
        }

        ll tm = (tl + tr) / 2;
        update(2*ind + 1, tl, tm, l, r, val);
        update(2*ind + 2, tm+1, tr, l, r, val);

        tree[ind].merge(tree[2*ind + 1], tree[2*ind + 2]);
    }
};
