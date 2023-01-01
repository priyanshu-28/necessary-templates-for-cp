stack<ll> s;

    i = 0;

    ll ans = 0;
    while(i < n){

        if(s.empty() or v[s.top()] <= v[i]){
            s.push(i);
            i++;
        }
        else{
            j = s.top();
            s.pop();
            cnt = v[j] * (s.empty() ? i : (i - s.top() - 1));
            ans = max(ans, cnt);
        }
    }

    while(!s.empty()){
        j = s.top();
        s.pop();
        cnt = v[j] * (s.empty() ? i : (i - s.top() - 1));
        ans = max(ans, cnt);
    }
