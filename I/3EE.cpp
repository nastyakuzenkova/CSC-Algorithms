#include <cstdio>
#include <algorithm>

using namespace std;

struct Segment {
  int index;
  int left;
  int right;

  Segment() {};
  Segment(const int &i, const int &l, const int &r)
   : index(i), left(l), right(r) {};

  bool operator < (const Segment &segment) const {
    return right < segment.right;
  }
};

Segment segments[100000];

int main() {
  int n = 0;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    int l = 0;
    int r = 0;
    scanf("%d %d", &l, &r);
    segments[i] = Segment(i, l, r);
  }
  sort(segments, segments + n);

  int count = 0;
  int current_right = 0;
  for (int i = 0; i < n; ++i) {
    if (segments[i].left >= current_right) {
      current_right = segments[i].right;
      count++;
    }
  }
  printf("%d", count);
  return 0;
}