/* HASHING */

struct pairhash { 
public:
	template <typename T, typename U>
	std::size_t operator()(const std::pair<T, U> &x) const {
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

/* PRINTING */
// using this line might be dangerous when mixing cout and printf,
// because it turns off synchronization between these two IOs and 
// might result in unexpected output.
ios_base::sync_with_stdio(false);

// prints double with 9 digit after comma precision
printf("%.9f", variable);

/* BINARY SEARCH */
/*
Binary search for answer. Function pointer must be applied, however
it can be extended to:
bool (*solve)(long long) -> bool (*solve)(long long, ...) 
in case you need to pass more arguments easily
*/

// case: no, no, no, yes, yes, yes
long long binary_answer(long long l, long long r, bool (*solve)(long long)) {
	if (l > r) return -1; // base case; no found element

	long long m = l + (r - l) / 2;

	if (solve(m)) { // we met some 'yes' here
		long long answer = binary_answer(l, m - 1, solve);
		if (answer != -1) {
			return answer;
		}
		else {
			return m;
		}
	}
	else {
		return binary_answer(m + 1, r, solve);
	}
}

// binary search for double answer 
double binary_answer(double low, double high, int iterations) {
	for (int i = 0; i < iterations; i++) {
		double mid = (high + low) / 2.0;
		if (solve(mid)) high = mid; else low = mid;
	}

	return high;
}