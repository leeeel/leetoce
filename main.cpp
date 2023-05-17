#include "bits/stdc++.h"

using namespace std;

struct ListNode {
    [[maybe_unused]] int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    [[maybe_unused]] explicit ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;

    TreeNode() : val(0), left(nullptr), right(nullptr) {}

    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}

    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

class Node {
public:
    [[maybe_unused]] int val;
    Node *left;
    Node *right;
    [[maybe_unused]] Node *next;

    explicit Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

    explicit Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

    explicit Node(int _val, Node *_left, Node *_right, Node *_next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

class [[maybe_unused]] Solution1487 {
public:
    static string addSuffix(string str, int num) {
        return str.append("(" + to_string(num) + ")");
    }

    [[maybe_unused]] static vector<string> getFolderNames(vector<string> &names) {
        vector<string> res;
        unordered_map<string, int> mp;

        for (auto &name: names) {
            if (!mp.count(name)) {
                mp[name]++;
                res.push_back(name);
            } else {
                int version = mp[name];
                while (mp.count(addSuffix(name, version))) {
                    version++;
                }

                mp[addSuffix(name, version)]++;
                mp[name] = version;
                res.push_back(addSuffix(name, version));
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution1642 {
public:
    [[maybe_unused]] static int furthestBuilding(vector<int> &heights, int bricks, int ladders) {
        unsigned int n = heights.size();
        priority_queue<int, vector<int>, greater<>> pq;

        for (int i = 1; i < n; ++i) {
            int gap = heights[i] - heights[i - 1];
            if (gap > 0) {
                pq.push(gap);
                int temp = 0;
                if (pq.size() > ladders) {
                    temp = pq.top();
                    pq.pop();
                }
                if (temp > bricks) {
                    return i - 1;
                } else {
                    bricks -= temp;
                }
            }
        }

        return int(n) - 1;
    }
};

class [[maybe_unused]] Solution1010 {
public:
    [[maybe_unused]] static int numPairsDivisibleby60(vector<int> &time) {
        long int res = 0;
        unordered_map<int, int> mp;

        for (int &t: time) {
            mp[t % 60]++;
        }

        // [1, 29]
        for (int i = 1; i < 30; ++i) {
            res += mp[i] * mp[60 - i];
        }

        // [30, 30]
        res += (long) mp[30] * (mp[30] - 1) / 2;
        // [0, 0]
        res += (long) mp[0] * (mp[0] - 1) / 2;

        return (int) res;
    }
};

class [[maybe_unused]] Solution513 {
public:
    [[maybe_unused]] static int findBottomLeftValue(TreeNode *root) {
        queue<TreeNode *> q;
        int res;

        q.push(root);
        res = root->val;

        while (!q.empty()) {
            unsigned int size = q.size();

            for (int i = 0; i < size; i++) {
                auto temp = q.front();
                q.pop();

                if (temp->right != nullptr) {
                    q.push(temp->right);
                }
                if (temp->left != nullptr) {
                    q.push(temp->left);
                }

                res = temp->val;// right -> left
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution165 {
public:
    [[maybe_unused]] static int compareVersion(string version1, string version2) {
        int i = 0, j = 0;
        unsigned int m = version1.size(), n = version2.size();

        while (i < m || j < n) {
            unsigned int num1 = 0, num2 = 0;

            for (; i < m && version1[i] != '.'; ++i) {
                num1 = num1 * 10 + version1[i] - '0';
            }
            for (; j < n && version2[j] != '.'; ++j) {
                num2 = num2 * 10 + version2[j] - '0';
            }

            if (num1 < num2) {
                return -1;
            } else if (num1 > num2) {
                return 1;
            }

            i++, j++;
        }

        return 0;
    }
};

class [[maybe_unused]] Solution1263 {
public:
    [[maybe_unused]] static int minPushBox(vector<vector<char>> &grid) {
        int m = int(grid.size());
        int n = int(grid[0].size());
        int sx = 0, sy = 0;
        int bx = 0, by = 0;
        int tx = 0, ty = 0;

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                if (grid[i][j] == 'S') {
                    sx = i, sy = j;
                    continue;
                }
                if (grid[i][j] == 'B') {
                    bx = i, by = j;
                }
                if (grid[i][j] == 'T') {
                    tx = i, ty = j;
                }
            }
        }

        auto f = [&](int &i, int &j) -> int {
            return i * n + j;
        };
        auto check = [&](int &i, int &j) -> bool {
            return i >= 0 && i < m && j >= 0 && j < n && grid[i][j] != '#';
        };

        deque<tuple<int, int, int>> q;
        q.emplace_back(f(sx, sy), f(bx, by), 0);
        vector<vector<bool>> visited(m * n, vector<bool>(m * n, false));
        visited[f(sx, sy)][f(bx, by)] = true;
        vector<vector<int>> dirs = {{0, 1},
                                    {0, -1},
                                    {1, 0},
                                    {-1, 0}};

        while (!q.empty()) {
            auto [s, b, d] = q.front();
            q.pop_front();

            sx = s / n;
            sy = s % n;
            bx = b / n;
            by = b % n;

            if (bx == tx && ty == by) {
                return d;
            }

            for (int i = 0; i < 4; ++i) {
                int dx = dirs[i][0];
                int dy = dirs[i][1];

                int ssx = sx + dx;
                int ssy = sy + dy;
                if (!check(ssx, ssy)) {
                    continue;
                }

                if (ssx == bx && ssy == by) {
                    int bbx = bx + dx;
                    int bby = by + dy;
                    if (!check(bbx, bby) || visited[f(ssx, ssy)][f(bbx, bby)]) {
                        continue;
                    }

                    visited[f(ssx, ssy)][f(bbx, bby)] = true;
                    q.emplace_back(f(ssx, ssy), f(bbx, bby), d + 1);
                } else if (!visited[f(ssx, ssy)][f(bx, by)]) {
                    visited[f(ssx, ssy)][f(bx, by)] = true;
                    q.emplace_front(f(ssx, ssy), f(bx, by), d);
                }
            }
        }

        return -1;
    }
};

class [[maybe_unused]] Solution92 {
public:
    [[maybe_unused]] static ListNode *reverseBetween(ListNode *head, int left, int right) {
        auto *dummy = new ListNode(0, head);
        auto *pre = dummy;

        for (int i = 0; i < left - 1; ++i) {
            pre = pre->next;
        }
        auto cur = pre->next;

        for (int j = 0; j < right - left; ++j) {
            auto temp = cur->next;
            cur->next = temp->next;
            temp->next = pre->next;
            pre->next = temp;
        }

        return dummy->next;
    }
};

class [[maybe_unused]] Solution1015 {
public:
    [[maybe_unused]] static int smallestRepunitDivByK(int k) {
        int res = 1;
        int num = 1;

        for (int i = 0; i < k; ++i, ++res) {
            if (num % k == 0) {
                return res;
            }
            num = (num * 10 + 1) % k;
        }

        return -1;
    }
};

class [[maybe_unused]] Solution1016 {
public:
    [[maybe_unused]] static bool queryString(string s, int n) {
        unsigned int m = s.size();
        unordered_set<int> set;

        for (int i = 0; i < m; ++i) {
            if (s[i] == '0') {
                continue;
            }
            int num = 1;

            for (int j = i + 1; num <= n; ++j) {
                set.insert(num);
                if (j == m) {
                    break;
                }
                num = (num << 1) | (s[j] - '0');
            }
        }

        return set.size() == n;
    }
};

class [[maybe_unused]] Solution224 {
public:
    [[maybe_unused]] static int calculate(string s) {
        int res = 0, op = 1;
        stack<int> stk;
        stk.push(op);
        unsigned int n = s.size();

        for (int i = 0; i < n; i++) {
            char ch = s[i];
            if (ch == ' ') {
                continue;
            } else if (ch == '(') {
                stk.push(op);
            } else if (ch == ')') {
                stk.pop();
            } else if (ch == '-') {
                op = -stk.top();
            } else if (ch == '+') {
                op = stk.top();
            } else {
                int num = 0;
                while (i < n && s[i] >= '0' && s[i] <= '9') {
                    num = num * 10 + s[i] - '0';
                    i++;
                }
                res += op * num;
                i--;
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution1096 {
public:
    [[maybe_unused]] static vector<string> braceExpansionII(string expression) {
        stack<char> op;// '{', '+', '*'
        stack<set<string>> st;
        unsigned int n = expression.size();

        auto cal = [&]() {
            auto strSet1 = st.top();
            st.pop();
            auto &strSet2 = st.top();
            st.pop();

            auto opr = op.top();
            if (opr == '+') {
                strSet1.merge(strSet2);
                st.emplace(strSet1);
            } else if (opr == '*') {
                set<string> temp;
                for (auto &str2: strSet2) {
                    for (auto &str1: strSet1) {
                        temp.insert(str2 + str1);
                    }
                }

                st.emplace(temp);
            }
            op.pop();
        };

        for (int i = 0; i < n; ++i) {
            switch (expression[i]) {
                case '{':
                    if (i > 0 && (expression[i - 1] == '}' || isalpha(expression[i - 1]))) {
                        op.emplace('*');
                    }
                    op.emplace(expression[i]);
                    continue;
                case '}':
                    while (!op.empty() && op.top() != '{') {
                        cal();
                    }
                    op.pop();
                    continue;
                case ',':
                    while (!op.empty() && op.top() == '*') {
                        cal();
                    }
                    op.emplace('+');
                    continue;
                default:
                    if (i > 0 && (expression[i - 1] == '}' || isalpha(expression[i - 1]))) {
                        op.emplace('*');
                    }
                    st.push({string(1, expression[i])});
            }
        }

        while (!op.empty()) {
            cal();
        }

        return {st.top().begin(), st.top().end()};
    }
};

class [[maybe_unused]] Solution264 {
public:
    [[maybe_unused]] static int nthUglyNumber(int n) {
        vector<int> dp(n + 1, 1);
        int p2 = 1, p3 = 1, p5 = 1;
        int num1, num2, num3;

        for (int i = 2; i <= n; ++i) {
            num1 = dp[p2] * 2;
            num2 = dp[p3] * 3;
            num3 = dp[p5] * 5;
            dp[i] = min(num1, min(num2, num3));
            if (num1 == dp[i]) {
                p2++;
            }
            if (num2 == dp[i]) {
                p3++;
            }
            if (num3 == dp[i]) {
                p5++;
            }
        }

        return dp[n];
    }
};

class [[maybe_unused]] Solution1023 {
public:
    [[maybe_unused]] static vector<bool> camelMatch(vector<string> &queries, string pattern) {
        unsigned int n = queries.size();
        unsigned int m = pattern.size();

        vector<bool> res(n, true);

        for (int i = 0; i < n; ++i) {
            int k = 0;
            for (char &c: queries[i]) {
                if (k < m && pattern[k] == c) {
                    k++;
                    continue;
                }
                if (isupper(c)) {
                    res[i] = false;
                    break;
                }
            }

            if (k != m) {
                res[i] = false;
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution1041 {
public:
    [[maybe_unused]] static bool isRobotBounded(const string &instructions) {
        int x = 0, y = 0, index = 0;
        int dx, dy;

        vector<vector<int>> dirs = {{0, 1},
                                    {1, 0},
                                    {0, -1},
                                    {-1, 0}};
        for (auto instruction: instructions) {
            if (instruction == 'R') {
                index = (index + 1) % 4;
            } else if (instruction == 'L') {
                index = (index + 3) % 4;
            } else {
                dx = dirs[index][0];
                dy = dirs[index][1];
                x += dx;
                y += dy;
            }
        }

        return index != 0 || (x == 0 && y == 0);
    }
};

class [[maybe_unused]] Solution1033 {
public:
    [[maybe_unused]] static vector<int> numMovesStones(int a, int b, int c) {
        vector<int> res(2, 0);
        int minNum = min({a, b, c});
        int maxNum = max({a, b, c});
        int midNum = a + b + c - minNum - maxNum;

        if (maxNum - midNum == 1 && midNum - minNum == 1) {
            res[0] = 0;
        } else if (maxNum - midNum <= 2 || midNum - minNum <= 2) {
            res[0] = 1;
        } else {
            res[0] = 2;
        }
        res[1] = maxNum - minNum - 2;

        return res;
    }
};

class [[maybe_unused]] Solution970 {
public:
    [[maybe_unused]] static vector<int> powerfulIntegers(int x, int y, int bound) {
        vector<int> res;
        unordered_set<int> tempSet;
        int a = 0, b = 0;
        int sum = 0;

        if (x == 1) {
            a = 1;
        } else {
            while (pow(x, a) <= bound) {
                a++;
            }
        }
        if (y == 1) {
            b = 1;
        } else {
            while (pow(y, b) <= bound) {
                b++;
            }
        }
        for (int i = 0; i < a; i++) {
            for (int j = 0; j < b; j++) {
                sum = int(pow(x, i) + pow(y, j));
                if (sum <= bound) {
                    tempSet.emplace(sum);
                }
            }
        }

        return {tempSet.begin(), tempSet.end()};
    }
};

class [[maybe_unused]] Solution1376 {
public:
    [[maybe_unused]] static int
    numOfMinutes([[maybe_unused]] int n, int headID, vector<int> &manager, vector<int> &informTime) {
        int res = 0;

        unordered_map<int, vector<int>> mp;
        for (int i = 0; i < manager.size(); ++i) {
            mp[manager[i]].push_back(i);
        }

        queue<pair<int, int>> q;
        q.emplace(headID, 0);
        while (!q.empty()) {
            int unsigned size = q.size();

            for (int i = 0; i < size; ++i) {
                auto temp = q.front();
                q.pop();
                if (!mp[temp.first].empty()) {
                    for (auto item: mp[temp.first]) {
                        q.emplace(item, temp.second + informTime[temp.first]);
                    }
                } else {
                    res = max(res, temp.second);
                }
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution1003 {
public:
    [[maybe_unused]] static bool isValid(const string &s) {
        string st;

        for (auto ch: s) {
            st.push_back(ch);
            if (st.size() >= 3 && st.substr(st.size() - 3, 3) == "abc") {
                st.erase(st.size() - 3, 3);
            }
        }

        return st.empty();
    }
};

class [[maybe_unused]] Solution2106 {
public:
    [[maybe_unused]] static int maxTotalFruits(vector<vector<int>> &fruits, int startPos, int k) {
        int res = 0;
        int cnt = 0;

        auto steps = [&fruits, &startPos](int &i, int &j) -> int {
            return fruits[j][0] - fruits[i][0] + min(abs(startPos - fruits[i][0]), abs(startPos - fruits[j][0]));
        };

        for (int i = 0, j = 0; j < fruits.size(); ++j) {
            cnt += fruits[j][1];
            while (i <= j &&
                   steps(i, j) > k) {
                cnt -= fruits[i++][1];
            }

            res = max(res, cnt);
        }

        return res;
    }
};

class [[maybe_unused]] Solution692 {
public:
    [[maybe_unused]] static vector<string> topKFrequent(vector<string> &words, int k) {
        vector<string> res(k);
        unordered_map<string, int> cnt;

        for (const auto &word: words) {
            cnt[word]++;
        }

        auto cmp = [](const pair<string, int> &a, const pair<string, int> &b) {
            return a.second == b.second ? a.first < b.first : a.second > b.second;
        };

        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> pq(cmp);
        for (const auto &it: cnt) {
            pq.emplace(it);
            if (pq.size() > k) {
                pq.pop();
            }
        }

        for (int i = k - 1; i >= 0; --i) {
            res[i] = pq.top().first;
            pq.pop();
        }

        return res;
    }
};

class [[maybe_unused]] Solution2432 {
public:
    [[maybe_unused]] static int hardestWorker([[maybe_unused]] int n, vector<vector<int>> &logs) {
        int res = logs[0][0];
        int maxCost = logs[0][1];

        for (int i = 1; i < logs.size(); ++i) {
            int curCost = logs[i][1] - logs[i - 1][1];

            if (curCost > maxCost || curCost == maxCost && logs[i][0] < res) {
                res = logs[i][0];
                maxCost = curCost;
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution1497 {
public:
    [[maybe_unused]] static bool canArrange(vector<int> &arr, int k) {
        unordered_map<int, int> mp;
        for (auto &num: arr) {
            mp[(num % k + k) % k]++;
        }
        for (auto [key, value]: mp) {
            if (key != 0 && (mp.count(k - key) == 0 || mp[k - key] != value)) {
                return false;
            }
        }

        return mp[0] % 2 == 0;
    }
};

class [[maybe_unused]] Solution1344 {
public:
    [[maybe_unused]] static double angleClock(int hour, int minutes) {
        double minuteAngle = minutes == 60 ? 0 : minutes * 6;
        double hourAngle = (hour == 12 ? 0 : hour * 30) + double(minutes) / 2.0;
        double res = abs(hourAngle - minuteAngle);

        return res > 180 ? 360 - res : res;
    }
};

class [[maybe_unused]] Solution199 {
public:
    [[maybe_unused]] static vector<int> rightSideView(TreeNode *root) {
        vector<int> res;
        queue<TreeNode *> q;

        if (root != nullptr) {
            q.emplace(root);
        }

        while (!q.empty()) {
            unsigned int size = q.size();
            for (int i = 0; i < size; ++i) {
                TreeNode *temp = q.front();
                q.pop();

                if (temp->left != nullptr) {
                    q.push(temp->left);
                }
                if (temp->right != nullptr) {
                    q.push(temp->right);
                }
                if (i == size - 1) {
                    res.emplace_back(temp->val);
                }
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution151 {
public:
    [[maybe_unused]] static string reverseWords(string s) {
        reverse(s.begin(), s.end());
        int idx = 0;

        for (int start = 0; start < s.size(); ++start) {
            if (s[start] != ' ') {
                if (idx != 0) {
                    s[idx++] = ' ';
                }

                int end = start;
                while (end < s.size() && s[end] != ' ') {
                    s[idx++] = s[end++];
                }

                reverse(s.begin() + idx - (end - start), s.begin() + idx);
                start = end;
            }
        }

        s.erase(s.begin() + idx, s.end());

        return s;
    }
};

class [[maybe_unused]] Solution986 {
public:
    [[maybe_unused]] static vector<vector<int>>
    intervalIntersection(vector<vector<int>> &firstList, vector<vector<int>> &secondList) {
        vector<vector<int>> res;
        int i = 0, j = 0;
        unsigned int m = firstList.size(), n = secondList.size();

        while (i < m && j < n) {
            if (firstList[i][0] > secondList[j][1]) {
                j++;
                continue;
            }
            if (firstList[i][1] < secondList[j][0]) {
                i++;
                continue;
            }

            int left = max(firstList[i][0], secondList[j][0]);
            int right = min(firstList[i][1], secondList[j][1]);
            res.push_back({left, right});

            if (firstList[i][1] >= secondList[j][1]) {
                j++;
            } else {
                i++;
            }
        }

        return res;
    }
};

class [[maybe_unused]] Solution701 {
public:
    [[maybe_unused]] static TreeNode *insertIntoBST(TreeNode *root, int val) {
        if (root == nullptr) {
            return new TreeNode(val);
        }

        TreeNode *cur = root;

        //        if (val< root->val){
        //            if (root->left == nullptr){
        //                root->left = new TreeNode(val);
        //            }else{
        //                insertIntoBST(root->left,val);
        //            }
        //        }else{
        //            if (root->right == nullptr){
        //                root->right = new TreeNode(val);
        //            }else{
        //                insertIntoBST(root->right,val);
        //            }
        //        }

        while (true) {
            if (val < cur->val) {
                if (cur->left == nullptr) {
                    cur->left = new TreeNode(val);
                    break;
                } else {
                    cur = cur->left;
                }
            } else {
                if (cur->right == nullptr) {
                    cur->right = new TreeNode(val);
                    break;
                } else {
                    cur = cur->right;
                }
            }
        }

        return root;
    }
};

class [[maybe_unused]] Solution973 {
public:
    [[maybe_unused]] static vector<vector<int>> kClosest(vector<vector<int>> &points, int k) {
        vector<vector<int>> res;
        priority_queue<pair<double, int>> pq;

        for (int i = 0; i < points.size(); ++i) {
            double dis = sqrt(pow(points[i][0], 2) + pow(points[i][1], 2));

            if (pq.size() < k) {
                pq.emplace(dis, i);
            } else {
                if (pq.top().first > dis) {
                    pq.pop();
                    pq.emplace(dis, i);
                }
            }
        }

        while (!pq.empty()) {
            res.emplace_back(points[pq.top().second]);
            pq.pop();
        }

        return res;
    }
};

class [[maybe_unused]] Solution1419 {
public:
    [[maybe_unused]] static int minNumberOfFrogs(string &croakOfFrogs) {
        unordered_map<char, int> mp = {{'c', 0},
                                       {'r', 1},
                                       {'o', 2},
                                       {'a', 3},
                                       {'k', 4}};
        vector<int> help(5, 0);
        int cnt = 0;
        int res = 0;

        for (auto &ch: croakOfFrogs) {
            int idx = mp[ch];

            if (idx == 0) {
                cnt++;
                help[idx]++;
            } else {
                if (help[idx - 1] > help[idx]) {
                    help[idx]++;
                } else {
                    return -1;
                }

                if (idx == 4) {
                    res = max(res, cnt);
                    cnt--;
                }
            }
        }

        if (help[0] == help[4]) {
            return res;
        }

        return -1;
    };
};

class [[maybe_unused]] Solution1190 {
public:
    [[maybe_unused]] static string reverseParentheses(string &s) {
        stack<string> stk;
        string str;

        for (auto &ch: s) {
            if (ch == '(') {
                stk.push(str);
                str = "";
            } else if (ch == ')') {
                reverse(str.begin(), str.end());
                str = stk.top().append(str);
                stk.pop();
            } else {
                str.push_back(ch);
            }
        }

        return str;
    }
};

class [[maybe_unused]] Solution1190_1 {
public:
    [[maybe_unused]] static string reverseParentheses(string &s) {
        unsigned int n = s.size();
        vector<int> pair(n);
        stack<int> stk;

        for (int i = 0; i < s.size(); ++i) {
            if (s[i] == '(') {
                stk.push(i);
            } else if (s[i] == ')') {
                int j = stk.top();
                stk.pop();
                pair[i] = j;
                pair[j] = i;
            }
        }

        string res;
        int idx = 0, dir = 1;
        while (idx < n) {
            if (s[idx] == '(' || s[idx] == ')') {
                idx = pair[idx];
                dir *= -1;
            } else {
                res.push_back(s[idx]);
            }

            idx += dir;
        }

        return res;
    }
};

class [[maybe_unused]] Solution223 {
public:
    [[maybe_unused]] static int computeArea(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2) {
        int s1 = abs((ax2 - ax1) * (ay2 - ay1));
        int s2 = abs((bx2 - bx1) * (by2 - by1));
        int overlapWidth = min(ax2, bx2) - max(ax1, bx1);
        int overlapHeight = min(ay2, by2) - max(ay1, by1);

        return s1 + s2 - max(0, overlapHeight) * max(0, overlapWidth);
    }
};

class [[maybe_unused]] Solution468 {
public:
    [[maybe_unused]] static string validIPAddress(string &queryIP) {
        string ipv4 = "IPv4";
        string ipv6 = "IPv6";
        string neither = "Neither";
        unsigned int n = queryIP.size();

        if (queryIP.find('.') != string::npos) {
            int idx = 0;
            int cnt = 0;

            while (idx < int(n)) {
                string temp;
                while (idx < n && queryIP[idx] != '.') {
                    if (!isdigit(queryIP[idx])) {
                        return neither;
                    }
                    temp.push_back(queryIP[idx++]);
                }

                if (temp.size() > 3 || temp.empty()) {
                    return neither;
                }
                int num = stoi(temp);
                if (num < 0 || num > 255) {
                    return neither;
                }
                if (num > 0 && temp[0] == '0' || num == 0 && temp.size() != 1) {
                    return neither;
                }
                if (queryIP[n - 1] == '.') {
                    return neither;
                }

                idx++, cnt++;
            }
            if (cnt != 4) {
                return neither;
            }

            return ipv4;
        }

        if (queryIP.find(':') != string::npos) {
            int idx = 0;
            int cnt = 0;
            int zeroCnt = 0;

            while (idx < int(n)) {
                string temp;
                while (idx < n && queryIP[idx] != ':') {
                    char ch = queryIP[idx];
                    if (!isdigit(queryIP[idx]) && !(ch <= 'F' && ch >= 'A') && !(ch <= 'f' && ch >= 'a')) {
                        return neither;
                    }
                    if (queryIP[idx] == '0') {
                        zeroCnt++;
                    }
                    temp.push_back(queryIP[idx++]);
                }

                if (temp.size() > 4 || temp.empty()) {
                    return neither;
                }
                if (zeroCnt == queryIP.size() && zeroCnt != 1) {
                    return neither;
                }
                if (queryIP[n - 1] == ':') {
                    return neither;
                }

                idx++, cnt++;
            }
            if (cnt != 8) {
                return neither;
            }

            return ipv6;
        }

        return neither;
    }
};

class [[maybe_unused]] Solution63 {
public:
    [[maybe_unused]] static int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        unsigned int m = obstacleGrid.size();
        unsigned int n = obstacleGrid[0].size();
        vector<vector<int>> dp(m, vector<int>(n, 0));

        for (int i = 0; i < m; ++i) {
            if (obstacleGrid[i][0] == 1) {
                break;
            }
            dp[i][0] = 1;
        }
        for (int j = 0; j < n; ++j) {
            if (obstacleGrid[0][j] == 1) {
                break;
            }
            dp[0][j] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 1; j < n; ++j) {
                if (obstacleGrid[i][j] == 1) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
                }
            }
        }

        return dp[m - 1][n - 1];
    }
};

class [[maybe_unused]] Solution63_1 {
public:
    [[maybe_unused]] static int uniquePathsWithObstacles(vector<vector<int>> &obstacleGrid) {
        unsigned int m = obstacleGrid.size();
        unsigned int n = obstacleGrid[0].size();
        vector<int> dp(n, 0);

        dp[0] = obstacleGrid[0][0] == 1 ? 0 : 1;
        for (int j = 0; j < n; ++j) {
            if (obstacleGrid[0][j] == 1) {
                break;
            }
            dp[j] = 1;
        }
        for (int i = 1; i < m; ++i) {
            for (int j = 0; j < n; j++) {
                if (obstacleGrid[i][j] == 1) {
                    dp[j] = 0;
                    continue;
                }
                if (j >= 1) {
                    dp[j] = dp[j] + dp[j - 1];
                }
            }
        }

        return dp[n - 1];
    }
};

class [[maybe_unused]] Solution871 {
public:
    [[maybe_unused]] static int minRefuelStops(int target, int startFuel, vector<vector<int>> &stations) {
        int res = 0;
        priority_queue<int> pq;

        stations.push_back({target, 0});
        for (auto &station: stations) {
            while (startFuel < station[0] && !pq.empty()) {
                auto temp = pq.top();
                pq.pop();
                res++;
                startFuel += temp;
            }

            if (startFuel < station[0]) {
                return -1;
            }

            pq.emplace(station[1]);
        }

        return res;
    }
};

class [[maybe_unused]] Solution117 {
public:
    [[maybe_unused]] static Node *connect(Node *root) {
        if (root == nullptr) {
            return root;
        }

        queue<Node *> q;
        q.push(root);

        while (!q.empty()) {
            unsigned int n = q.size();
            for (int i = 0; i < n; ++i) {
                auto temp = q.front();
                q.pop();

                if (temp->left != nullptr) {
                    q.push(temp->left);
                }
                if (temp->right != nullptr) {
                    q.push(temp->right);
                }
                if (i < n - 1) {
                    temp->next = q.front();
                }
            }
        }

        return root;
    }
};

class [[maybe_unused]] Solution2437 {
public:
    [[maybe_unused]] static int countTime(string time) {
        int hourCnt = 0, minCnt = 0;

        for (int i = 0; i < 24; ++i) {
            int a = i / 10;
            int b = i % 10;
            if ((time[0] == '?' || time[0] == a + '0') && (time[1] == '?' || time[1] == b + '0')) {
                hourCnt++;
            }
        }
        for (int j = 0; j < 60; ++j) {
            int a = j / 10;
            int b = j % 10;
            if ((time[3] == '?' || time[3] == a + '0') && (time[4] == '?' || time[4] == b + '0')) {
                minCnt++;
            }
        }

        return hourCnt * minCnt;
    }
};

class [[maybe_unused]] Solution1035 {
public:
    [[maybe_unused]] static int maxUncrossedLines(vector<int> &nums1, vector<int> &nums2) {
        unsigned int m = nums1.size();
        unsigned int n = nums2.size();
        vector<vector<int>> dp(m + 1, vector(n + 1, 0));

        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (nums1[i - 1] == nums2[j - 1]) {
                    dp[i][j] = 1 + dp[i - 1][j - 1];
                } else {
                    dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
                }
            }
        }

        return dp[m][n];
    }
};

class [[maybe_unused]] Solution679 {
private:
    constexpr static const int target = 24;
    constexpr static const double EPSILON = 1e-6;

    static bool solve(vector<double> &nums) {
        unsigned int m = nums.size();

        if (m == 1) {
            return abs(nums[0] - target) < EPSILON;
        }

        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < m; ++j) {
                if (j == i) {
                    continue;
                }

                vector<double> nums1;
                for (int k = 0; k < m; ++k) {
                    if (k == j || k == i) {
                        continue;
                    }
                    nums1.emplace_back(nums[k]);
                }

                double a = nums[i], b = nums[j];
                vector<double> nums2 = {a + b, a - b, a * b};
                if (b != 0) {
                    nums2.emplace_back(a / b);
                }

                unsigned int n = nums2.size();
                for (int k = 0; k < n; ++k) {
                    nums1.emplace_back(nums2[k]);
                    if (solve(nums1)) {
                        return true;
                    }
                    nums1.pop_back();
                }
            }
        }

        return false;
    }

public:
    [[maybe_unused]] static bool judgePoint24(vector<int> &cards) {
        unsigned int n = cards.size();
        vector<double> nums(n);
        for (int i = 0; i < n; ++i) {
            nums[i] = double(cards[i]);
        }

        return solve(nums);
    }
};

[[maybe_unused]] int main() {
    return 0;
}