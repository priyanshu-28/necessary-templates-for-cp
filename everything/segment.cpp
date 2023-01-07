void build(ll node,ll start,ll end,vector<ll> &tree,vector<ll> &a) 
{
    if(start==end){    
        tree[node]=a[start];
    }
    else{
    
        ll mid=(start+end)/2;
        build(2*node+1,start,mid,tree,a);
        build(2*node+2,mid+1,end,tree,a);
        tree[node]=min(tree[2*node+1],tree[2*node+2]);
    }
 }
 
void update(ll node,ll start,ll end,ll idx,ll val,vector<ll> &tree,vector<ll> &a)
{
 
    if(start==end){
       
       a[idx]=val;
       tree[node]=val;
    
    }
 
    else{
      
        ll mid=(start+end)/2;
        if(idx>=start && idx<=mid){    
            update(2*node+1,start,mid,idx,val,tree,a);
        }
        else{    
            update(2*node+2,mid+1,end,idx,val,tree,a);
        }
        tree[node]=min(tree[2*node+1],tree[2*node+2]);
    }
}
ll query(ll node,ll start,ll end,ll l,ll r,vector<ll> &tree)
{
    if(l>end||start>r)
    {     
        return INF;
    }
    if(l<=start&&r>=end)
    {    
        return tree[node];
    }
    ll q1,q2;
    ll mid=(start+end)/2;
    q1 = query(2*node+1,start,mid,l,r,tree);
    q2 = query(2*node+2,mid+1,end,l,r,tree);
    return (min(q1,q2));
}
//build(0,0,n-1,tree,B);
//query(0,0,n-1,left_range, right_range, tree);
//update(0,0,n-1,index,value,tree,B);
