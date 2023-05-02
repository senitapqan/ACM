class Solution {
public:
    int t[int(4e6 + 500)];
    int tag[int(4e6 + 500)];

    void build(int u, int l, int r, vector<int>& a) {
        if (l == r) {
            t[u] = a[l];
            return;
        }
        int m = l + r >> 1;
        build(u + u, l, m, a);
        build(u + u + 1, m + 1, r, a);
        t[u] = t[u + u] + t[u + u + 1];
    }

	void push(int u, int l, int r) {
		if (l == r || tag[u] == 0) {
			return;
		}
		
		tag[u + u] += tag[u];
		tag[u + u + 1] += tag[u];
		
		tag[u + u] %= 2;
		tag[u + u + 1] %= 2;
		
		int m = l + r >> 1;
		
		int len_left_son = m - l + 1;
		int len_right_son = r - m;
		
		int cnt_1_left_son = t[u + u];
		int cnt_1_right_son = t[u + u + 1];
		
		int new_cnt_1_left_son = len_left_son - cnt_1_left_son;
		int new_cnt_1_right_son = len_right_son - cnt_1_right_son;
		
		t[u + u] = new_cnt_1_left_son;
		t[u + u + 1] = new_cnt_1_right_son;
		
		tag[u] = 0;
		
	}

    void update(int u, int ul, int ur, int l, int r) {
    	
		push(u, ul, ur);
    	
    	if (ul > r || l > ur) return;
    	
		if (l <= ul && ur <= r) {
			
    		int len = ur - ul + 1;
    		int cnt_1 = t[u];
    		int new_cnt_1 = len - cnt_1;
    		
    		t[u] = new_cnt_1;
    		
    		tag[u]++;
            return;
		}
		
		int um = ul + ur >> 1;
		
		update(u + u, ul, um, l, r);
		update(u + u + 1, um + 1, ur, l, r);
		
		t[u] = t[u + u] + t[u + u + 1];
    }

    vector<long long> handleQuery(vector<int>& a, vector<int>& nums2, vector<vector<int>>& q) {
        int n = a.size();
        
        vector<long long> result;
        long long sum = 0;
        
        int cnt_1 = 0;

        for (int i = 0; i < n; i++) {sum += nums2[i]; if (a[i] == 1) cnt_1++;}

        build(1, 0, n - 1, a);

        for (int i = 0; i < q.size(); i++) {
            vector<int> qr = q[i];
            int tp = qr[0];
            if (tp == 1) {
                int l = qr[1];
                int r = qr[2];
                
                update(1, 0, n - 1, l, r);
            }
            if (tp == 2) {
                int p = qr[1];
                sum += p * 1ll * t[1];
            }
            if (tp == 3) {
                result.push_back(sum);  
            }
        }
        return result;

           
    }
};


/*

	/// for getting k-th number
	
	
	int get(int u, int l, int r, int k) {
		
		push(u, l, r);
		
		if (l == r) {
			return l;
		}
		
		int m = l + r>> 1;
	
	
		/// 9
		/// [...5...] [...6...]
	
		if (t[u + u] >= k) return get(u + u, l, m, k);
		else return get(u + u + 1, m + 1, r, k - t[u + u]);
	}

*/
