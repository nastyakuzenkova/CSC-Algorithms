#include <cstdio>
#include <algorithm>

using namespace std;

int const start = 0;
int const point = 1;
int const finish = 2;

struct Event {
	int i;
	int type;
	int value;

	Event() {};
	Event(const int &i_i, const int &i_type, const int &i_value) 
	: i(i_i), type(i_type), value(i_value) {};

	bool operator < (const Event& event) const { 
    	return (value < event.value || 
    		(value == event.value && type < event.type)); 
    }
};

struct Point {
	int i;
	int count;

	Point() {};
	Point(const int &i_i, const int &i_count)
	: i(i_i), count(i_count) {};

	bool operator < (const Point& point) const { 
    	return (i < point.i); 
    }	
};


Event events[300000];
Point points[100000];

int main()
{
	int n, m;
	scanf("%d %d", &n, &m);
	int length = 2 * n + m;
	int index = 0;
	for (int i = 0; i < n; ++i) {
		int a, b;
		scanf("%d %d", &a, &b);
		if (a > b) {
			int temp = a;
			a = b;
			b = temp;
		}
		events[index] = Event(index, start, a);
		index++;
		events[index] = Event(index, finish, b);
		index++;
	}
	for (int i = 0; i < m; ++i) {
		int x;
		scanf("%d", &x);
		events[index] = Event(index, point, x);
		index++;
	}
	sort(events, events + length);

	int count = 0;
	int j = 0;
	for (int i = 0; i < length; ++i) {
		Event current = events[i];
		if (current.type == start) {
			count++;
		}
		else if (current.type == finish) {
			count--;
		}
		else if (current.type == point) {
			points[j] = Point(current.i, count);
			++j;
		}
	}
	sort(points, points + m);
	for (int i = 0; i < m; ++i) {
		printf("%d ", points[i].count);
	}
	return 0;
}