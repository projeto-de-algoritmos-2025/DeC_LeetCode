class Solution {
public:
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        vector<int> merged = merge(nums1, nums2);
        int total = merged.size();
        if (total % 2 == 1) {
            return selectKth(merged, total / 2);
        } else {
            return (selectKth(merged, total / 2 - 1) + selectKth(merged, total / 2)) / 2.0;
        }
    }

private:
    vector<int> merge(const vector<int>& a, const vector<int>& b) {
        vector<int> res = a;
        res.insert(res.end(), b.begin(), b.end());
        return res;
    }

    int selectKth(vector<int>& arr, int k) {
        if (arr.size() == 1) return arr[0];

        int pivot = getMedianOfMedians(arr);
        vector<int> lows, highs, pivots;

        for (int num : arr) {
            if (num < pivot) lows.push_back(num);
            else if (num > pivot) highs.push_back(num);
            else pivots.push_back(num);
        }

        if (k < lows.size()) {
            return selectKth(lows, k);
        } else if (k < lows.size() + pivots.size()) {
            return pivot;
        } else {
            return selectKth(highs, k - lows.size() - pivots.size());
        }
    }

    int getMedianOfMedians(vector<int>& arr) {
        if (arr.size() <= 5) {
            sort(arr.begin(), arr.end());
            return arr[arr.size() / 2];
        }

        vector<int> medians;
        for (size_t i = 0; i < arr.size(); i += 5) {
            size_t end = min(i + 5, arr.size());
            vector<int> group(arr.begin() + i, arr.begin() + end);
            sort(group.begin(), group.end());
            medians.push_back(group[group.size() / 2]);
        }

        return selectKth(medians, medians.size() / 2);
    }
};

