class Solution {
public:
    
    string a, b;
    int sizea = 0, sizeb = 0;
    bool resultof[2001][2001];
    unordered_map<int, unordered_set<int>> availablepatternsfor;
    
    bool ismatch(int i, int j) {
        
        if(i == sizea and j == sizeb) return true;
        if(i < sizea and j == sizeb) return false;
        if(availablepatternsfor[i].find(j) != availablepatternsfor[i].end()) return resultof[i][j];
        if(i == sizea and j < sizeb) {
            availablepatternsfor[i].insert(j);
            for(int idx = j; idx < sizeb; idx++)
                if(b[idx] != '*') {
                    resultof[i][j] = false;
                    return false;
                }
            resultof[i][j] = true;
            return true;
        }
        // anyone might be empty case over also DP part is done
        // now let's move to none empty case
        
        if((a[i] == b[j]) or (b[j] == '?')) {
            bool res = ismatch(i+1, j+1);
            availablepatternsfor[i].insert(j);
            resultof[i][j] = res;
            return res;
        }
        
        if(b[j] != '*') {
            availablepatternsfor[i].insert(j);
            resultof[i][j] = false;
            return false;
        }
        
        // now there must be asterisk in b
        
        bool res_star_ignored = ismatch(i, j+1);
        bool res_star_takes_one = ismatch(i+1, j+1);
        bool res_star_eats_more = ismatch(i+1, j);
        bool res = (res_star_ignored or res_star_takes_one or res_star_eats_more);
        availablepatternsfor[i].insert(j);
        resultof[i][j] = res;
        return res;
    }
    
    bool isMatch(string s, string p) {
        a = s, b = p;
        sizea = s.size(), sizeb = p.size();
        return ismatch(0, 0);
    }
};

