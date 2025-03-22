# MKP算法

```
class Solution {
public:
    string shortestPalindrome(string s) {
        if(s.size() <= 1)
        {
            return s;
        }

        int len = s.size();
        vector<int> dp(len, 0);

        int j = 0;
        for(int i = 1; i < len; i++)
        {
            while(j > 0 && s[i] != s[j])
            {
                j = dp[j - 1];
            }
            if(s[i] == s[j])
            {
                j++;
            }
            dp[i] = j;
        }

        for(int i : dp)
        {
            cout << i << " ";
        }
        cout << endl;
        j = 0;
        for(int i = len - 1; i >=0; i--)
        {
            while(j > 0 && s[j] != s[i])
            {
                j = dp[j - 1];
            }

            if(s[j] == s[i])
            {
                j++;
            }
            
        }
        string s1 = s.substr(j, len);
        reverse(s1.begin(), s1.end());
        
        return s1 + s;
    }
};
```