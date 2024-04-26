vector<int> left(n, -1);
vector<int> right(n, n);
    stack<int> stk;
    for (int i = 0; i < n; ++i) {
        while (!stk.empty() && v[stk.top()] <= v[i]) {
            stk.pop();
        }
        if (!stk.empty()) {
            left[i] = stk.top();
        }
        stk.push(i);
    }
    stk = stack<int>();
    for (int i = n - 1; ~i; --i) {
        while (!stk.empty() && v[stk.top()] <= v[i]) {
            stk.pop();
        }
        if (!stk.empty()) {
            right[i] = stk.top();
        }
        stk.push(i);
    }
