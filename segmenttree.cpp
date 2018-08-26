/* https://codeforces.com/blog/entry/18051 */

/*
SegmentTree(int n): initializes tree with given size.
int n: maximum number of tree's leafs
T (*func)(T, T): function that returns parent's value based on two leafs. Function must be commutative (i.e. a + b = b + a)
T identity: identity given function 'func' (0 for sum, +inf for min, -inf for max)
Remember to initialize all leafs using initialize_leaf function and when finished call build.
First leaf is at t[n]
*/
template <class T>
class SegmentTree
{
public:
	SegmentTree(int n, T (*func)(T, T), T identity) {
		this->n = n;
		this->function = func;
		this->identity = identity;
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
		for (int i = n - 1; i > 0; --i) t[i] = function(t[i << 1], t[i << 1 | 1]);
	}

	void modify_point(int p, T value) {  // set value at position p FINE
		for (t[p += n] = value; p > 1; p >>= 1) {
			t[p >> 1] = function(t[p], t[p ^ 1]); // t[p ^ 1] is the other child
		}
	}

	T query_interval(int l, int r) {  // query on interval [l, r) FINE
		T res = identity; // ?
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = function(res, t[l++]);
			if (r & 1) res = function(res, t[--r]);
		}
		return res;
	}

	/*void modify_interval(int l, int r, T value) { // modify interval [l, r)
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) t[l++] = function(t[l], value);
			if (r & 1) t[r] = function(t[--r], value);
		}
	}

	T query_point(int p) { // query value at position p
		T res = identity; // ?
		for (p += n; p > 0; p >>= 1) res = function(res, t[p]);
		return res;
	}*/

	// If at some point after modifications we need to inspect all the elements in the array, 
	// we can push all the modifications to the leaves using the following code. 
	// After that we can just traverse elements starting with index n.
	// Time complexity: O(n)
	void push() {
		for (int i = 1; i < n; ++i) {
			t[i << 1] = function(t[i << 1], t[i]);
			t[i << 1 | 1] = function(t[i << 1 | 1], t[i]);
			t[i] = identity;
		}
	}

private:
	int* t;
	int n;
	T identity;

	T (*function)(T leaf1, T leaf2);
};