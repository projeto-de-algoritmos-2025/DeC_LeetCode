function kClosest(points: number[][], k: number): number[][] {
    function distanceSquared([x, y]: number[]): number {
        return x * x + y * y;
    }

    function mergeSortKClosest(pts: number[][]): number[][] {
        if (pts.length <= 1) return pts;

        const mid = Math.floor(pts.length / 2);
        const left = mergeSortKClosest(pts.slice(0, mid));
        const right = mergeSortKClosest(pts.slice(mid));

        return merge(left, right, k);
    }

    function merge(left: number[][], right: number[][], limit: number): number[][] {
        const result: number[][] = [];
        let i = 0, j = 0;

        while (result.length < limit && (i < left.length || j < right.length)) {
            const distL = i < left.length ? distanceSquared(left[i]) : Infinity;
            const distR = j < right.length ? distanceSquared(right[j]) : Infinity;

            if (distL < distR) {
                result.push(left[i]);
                i++;
            } else {
                result.push(right[j]);
                j++;
            }
        }

        return result;
    }

    return mergeSortKClosest(points).slice(0, k);
}