function countSmaller(nums: number[]): number[] {
    const n = nums.length;
    const counts = Array(n).fill(0);
    const pairs: [number, number][] = nums.map((val, i) => [val, i]);

    function mergeSort(start: number, end: number): [number, number][] {
        if (end - start <= 1) return pairs.slice(start, end);

        const mid = Math.floor((start + end) / 2);
        const left = mergeSort(start, mid);
        const right = mergeSort(mid, end);

        const merged: [number, number][] = [];
        let i = 0, j = 0;
        let numRightSmaller = 0;

        while (i < left.length && j < right.length) {
            if (right[j][0] < left[i][0]) {
                merged.push(right[j]);
                numRightSmaller++;
                j++;
            } else {
                counts[left[i][1]] += numRightSmaller;
                merged.push(left[i]);
                i++;
            }
        }

        while (i < left.length) {
            counts[left[i][1]] += numRightSmaller;
            merged.push(left[i]);
            i++;
        }

        while (j < right.length) {
            merged.push(right[j]);
            j++;
        }

        for (let k = 0; k < merged.length; k++) {
            pairs[start + k] = merged[k];
        }

        return merged;
    }

    mergeSort(0, n);
    return counts;
}