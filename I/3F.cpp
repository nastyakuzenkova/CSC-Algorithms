#include <cstdio>
#include <algorithm>
#include <queue>

using namespace std;

struct Segment {
  int index;
  int left;
  int right;

  Segment() {};
  Segment(const int &i, const int &l, const int &r)
   : index(i), left(l), right(r) {};

  bool operator < (const Segment &segment) const {
    return left < segment.left;
  }
};

Segment segments[100000];

int main() {
  int m = 0;
  scanf("%d", &m);
  int l = 0;
  int r = 0;
  int n = 0;
  scanf("%d %d", &l, &r);
  while (l != 0 || r != 0) {
    if (r >= 0 && l <= m) {
      segments[n] = Segment(n, l, r);
      ++n;
    }
    scanf("%d %d", &l, &r);
  }
  sort(segments, segments + n);

  int count = 0;
  int max_right = 0;
  int max_index_right = 0;
  int current = 0;

  queue<Segment> answer;
  for (int i = 0; i < n; ++i) {
    if (segments[i].left > current) {
      if (max_right < segments[i].left) {
        printf("No solution\n");
        return 0;
      }
      count++;
      answer.push(segments[max_index_right]);
      current = max_right;
    }
    if (segments[i].right > max_right) {
      max_right = segments[i].right;
      max_index_right = i;
      if (max_right >= m) {
        answer.push(segments[i]);
        count++;
        break;
      }
    }
  }
  if (count == 0 || max_right < m) {
    printf("No solution\n");
    return 0;
  }

  printf("%d\n", count);
  while(!answer.empty()) {
    Segment s = answer.front();
    printf("%d %d\n", s.left, s.right);
    answer.pop();
  }
  return 0;
}