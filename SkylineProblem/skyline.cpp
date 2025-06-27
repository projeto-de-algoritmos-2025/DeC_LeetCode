class Solution {
public:
    vector<vector<int>> getSkyline(vector<vector<int>>& buildings) {
        return divide(buildings, 0, buildings.size() - 1);
    }

private:
    vector<vector<int>> divide(const vector<vector<int>>& buildings, int left, int right) {
        if (left > right) return {};
        if (left == right) {
            int l = buildings[left][0];
            int r = buildings[left][1];
            int h = buildings[left][2];
            return {{l, h}, {r, 0}};
        }

        int mid = left + (right - left) / 2;
        auto leftSkyline = divide(buildings, left, mid);
        auto rightSkyline = divide(buildings, mid + 1, right);

        return mergeSkylines(leftSkyline, rightSkyline);
    }

    vector<vector<int>> mergeSkylines(const vector<vector<int>>& left, const vector<vector<int>>& right) {
        vector<vector<int>> result;
        int h1 = 0, h2 = 0, i = 0, j = 0;
        int currHeight = 0;

        while (i < left.size() && j < right.size()) {
            int x = 0;
            if (left[i][0] < right[j][0]) {
                x = left[i][0];
                h1 = left[i][1];
                ++i;
            } else if (left[i][0] > right[j][0]) {
                x = right[j][0];
                h2 = right[j][1];
                ++j;
            } else {
                x = left[i][0];
                h1 = left[i][1];
                h2 = right[j][1];
                ++i;
                ++j;
            }
            int maxHeight = max(h1, h2);
            if (result.empty() || result.back()[1] != maxHeight)
                result.push_back({x, maxHeight});
        }

        while (i < left.size()) result.push_back(left[i++]);
        while (j < right.size()) result.push_back(right[j++]);

        vector<vector<int>> finalResult;
        for (const auto& point : result) {
            if (finalResult.empty() || finalResult.back()[1] != point[1])
                finalResult.push_back(point);
        }

        return finalResult;
    }
};
