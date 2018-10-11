// Description of how it works:
// http://www.inf.fh-flensburg.de/lang/algorithmen/pattern/kmpen.htm

#include <vector>
#include <string>

using namespace std;

// t is a string to find pattern in
// p is pattern string
// b is prefix function result
vector<int> kmpPreprocess(string p)
{
	vector<int> b(p.size() + 1);
	int i = 0, j = -1;
	b[i] = j;
	while (i < p.size())
	{
		while (j >= 0 && p[i] != p[j]) j = b[j];
		i++; j++;
		b[i] = j;
	}

	return b;
}

// you must first call kmp preprocess so that you receive b.
void kmpSearch(string t, string p, vector<int>& b)
{
	int i = 0, j = 0;
	while (i < t.size())
	{
		while (j >= 0 && t[i] != p[j]) j = b[j];
		i++; j++;
		if (j == b.size() - 1)
		{
			report(i - j); // report (first) occurance of p in t
			j = b[j];
		}
	}
}

/*
string text = "AABAACAADAABAABA";
string pattern = "AABA";
auto sigma = kmpPreprocess(pattern);
kmpSearch(text, pattern, sigma);
*/