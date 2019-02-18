/* INCLUDES */
// includes all essential libraries
#include <bits/stdc++.h>

/* HASHING */
// Probably should be something different than xor

struct pairhash { 
public:
	template <typename T, typename U>
	std::size_t operator()(const std::pair<T, U> &x) const {
		return std::hash<T>()(x.first) ^ std::hash<U>()(x.second);
	}
};

struct tuplehash {
public:
	template <typename T, typename U, typename W>
	std::size_t operator()(const std::tuple<T, U, W> &x) const {
		return std::hash<T>()(get<0>(x)) ^ std::hash<U>()(get<1>(x)) ^ std::hash<W>()(get<2>(x));
	}
};

/* PRINTING */
// using this line might be dangerous when mixing cout and printf,
// because it turns off synchronization between these two IOs and 
// might result in unexpected output.
ios_base::sync_with_stdio(false);

// prints double with 9 digit after comma precision
// it's important to print it this way when dealing with double
// as normal cout happens to print << "1e9" notation
// keep in mind to turn on synchronization between cout and printf using ios_base::sync_with_stdio(true);
printf("%.9f", variable);

/* BINARY SEARCH */
/*
Binary search for answer. Function pointer must be applied, however
it can be extended to:
bool (*solve)(long long) -> bool (*solve)(long long, ...) 
in case you need to pass more arguments easily
*/

// case: no, no, no, yes, yes, yes; finds the first 'yes'
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

// case: yes, yes, yes, no, no, no; finds the last 'yes'
long long binary_answer2(long long l, long long r, bool (*solve)(long long)) {
	if (l > r) return -1; // base case; no found element

	long long m = l + (r - l) / 2;

	if (solve(m)) { // we met some 'yes' here
		long long answer = binary_answer2(m + 1, r, solve);
		if (answer != -1) {
			return answer;
		}
		else {
			return m;
		}
	}
	else {
		return binary_answer2(l, m - 1, solve);
	}
}

// binary search for double answer 
double binary_answer(double low, double high, int iterations, bool (*solve)(double)) {
	for (int i = 0; i < iterations; i++) {
		double mid = (high + low) / 2.0;
		if (solve(mid)) high = mid; else low = mid;
	}

	return high;
}

/* ROUNDING */
// If you ever need to combine a lot of multiplications and divisions in the future, where intermediate values might get very small, it helps to work in log space:
A * B / C = exp( log(A) + log(B) - log(C) )
// it avoids rounding all the time


/* COMPARATOR */
// Difference between declaration and object created
class Compare {
public:
    bool operator() (T a , T b) const {
        return true;
    }
}compare;

priority_queue<T, vector<T>, Compare> pq;
sort(v.begin(), v.end(), compare);


/* PERMUTATION */
vector<int> myints = {1,2,3};
std::sort(myints.begin(), myints.end()); // required if you want them in lexicographical order from first to last

do {
	std::cout << myints[0] << ' ' << myints[1] << ' ' << myints[2] << '\n';
} while(std::next_permutation(myints.begin(), myints.end()));

/*
To generate all subsets of size <= 64 we can use 
long long subset = 0...LL_MAX

Now to get next subset we just do:
subset++;

In order to find out if i-th element belongs to current subset we just check if i-th bit is set in variable subset.
*/


/* TEXT 
To find pattern in O(n) time we can in fact use .find method of string class

std::string str ("There are two needles in this haystack with needles.");
  std::string str2 ("needle");

  // different member versions of find in the same order as above:
  std::size_t found = str.find(str2);
  if (found!=std::string::npos)
    std::cout << "first 'needle' found at: " << found << '\n';

  found=str.find("needles are small",found+1,6);
  if (found!=std::string::npos)
    std::cout << "second 'needle' found at: " << found << '\n';

  found=str.find("haystack");
  if (found!=std::string::npos)
    std::cout << "'haystack' also found at: " << found << '\n';

  found=str.find('.');
  if (found!=std::string::npos)
    std::cout << "Period found at: " << found << '\n';

  // let's replace the first needle:
  str.replace(str.find(str2),str2.length(),"preposition");
  std::cout << str << '\n';

*/

/* TEXT */
// String concatenation is quite fast in c++, however we might as well use 
std::stringstream ss;
ss << "Hello world, " << 42 << "nice to see you.";
std::string s = ss.str();

// It can be a case, similarly like with vector, that the space is doubled evety time it needs to do some resizing.

// Declare string of n characters
std::string s(5, 'a'); // s == "aaaaa"

// convert string line with objects into variables
string s = "1 30 55";
stringstream ss(s);

int a, b, c;
ss >> a >> b >> c;