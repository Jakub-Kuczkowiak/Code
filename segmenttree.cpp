/* https://codeforces.com/blog/entry/18051 */

/*
SegmentTree efficient implementation.
SegmentTree(int n): initializes tree with given size.
Remember to initialize all leafs using initialize_leaf function and when finished call build.
First leaf is at position t[n]
*/
template <class T>
class SegmentTree
{
public:
	SegmentTree(int n) {
		this->n = n;
		t = new T[2 * n];
	}

	~SegmentTree() {
		delete[] t;
	}

	__inline void initialize_leaf(int index, T value) {
		t[n + index] = value;
	}

	// We use build to reduce complexity to O(n) instead of O(nlog n)
	void build() {
		for (int i = n - 1; i > 0; --i) t[i] = t[i << 1] + t[i << 1 | 1];
	}

	void modify_point(int p, T value) {  // set value at position p?
		for (t[p += n] = value; p > 1; p >>= 1) {
			t[p >> 1] = t[p] + t[p ^ 1]; // t[p ^ 1] is the other child
		}
	}

	T query_interval(int l, int r) {  // sum on interval [l, r)?
		T res = 0;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res += t[l++];
			if (r & 1) res += t[--r];
		}
		return res;
	}

	void modify_interval(int l, int r, T value) { // modify interval [l, r)?
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) t[l++] += value;
			if (r & 1) t[--r] += value;
		}
	}

	T query_point(int p) {
		T res = 0;
		for (p += n; p > 0; p >>= 1) res += t[p];
		return res;
	}

	// If at some point after modifications we need to inspect all the elements in the array, 
	// we can push all the modifications to the leaves using the following code. 
	// After that we can just traverse elements starting with index n.
	// Time complexity: O(n)
	void push() {
		for (int i = 1; i < n; ++i) {
			t[i << 1] += t[i];
			t[i << 1 | 1] += t[i];
			t[i] = 0;
		}
	}

private:
	int* t;
	int n;
};
