#include<stdio.h>
#include<limits.h>
#include<algorithm>

using namespace std;
int point_num, dis = INT_MAX, index = -1;

struct Point
{
    int x, y, index;
};
struct Point point[100000];
struct Point tmp[100000];
struct Ans
{
    int x, y;
};
struct Ans ans[100000];

inline bool sort_ans(struct Ans a, struct Ans b)
{
    if(a.x == b.x && a.y < b.y)
        return true;
    return a.x < b.x;
}

inline bool sort_x(struct Point a, struct Point b)
{
    return a.x < b.x;
}

inline bool sort_y(struct Point a, struct Point b)
{
    return a.y < b.y;
}

inline int square(int a)
{
    return a * a;
}

void closest_pair(int left, int right)
{
    if(left >= right)
        return;

    int median = left + right >> 1;
    nth_element(point + left, point + median, point + right + 1, sort_x);
    closest_pair(left, median);
    closest_pair(median + 1, right);

    int i, j, interval = 0;
    for(i=left; i<=median && point[median].x - point[i].x < dis; ++i)
        tmp[interval++] = point[i];

    for(i=median+1; i<=right && point[i].x - point[median].x < dis; ++i)
    {
        tmp[interval] = point[i];
        tmp[interval].index *= -1;
        ++interval;
    }

    sort(tmp, tmp + interval, sort_y);
    for(i=0; i<interval-1; ++i)
        for(j=1; j<=3 && i+j<interval; ++j)
        {
            int t = square(tmp[i].x - tmp[i+j].x) + square(tmp[i].y - tmp[i+j].y);
            if(t <= dis)
                if(t == dis)
                {
                    if(tmp[i].index < 0 && tmp[i+j].index > 0)
                    {
                        ++index;
                        ans[index].x = -1 * tmp[i].index;
                        ans[index].y = tmp[i+j].index;
                        if(ans[index].x > ans[index].y)
                        {
                            ans[index].x ^= ans[index].y;
                            ans[index].y ^= ans[index].x;
                            ans[index].x ^= ans[index].y;
                        }
                    }
                    else if(tmp[i].index > 0 && tmp[i+j].index < 0)
                    {
                        ++index;
                        ans[index].x = tmp[i].index;
                        ans[index].y = -1 * tmp[i+j].index;
                        if(ans[index].x > ans[index].y)
                        {
                            ans[index].x ^= ans[index].y;
                            ans[index].y ^= ans[index].x;
                            ans[index].x ^= ans[index].y;
                        }
                    }
                }
                else
                {
                    dis = t;
                    index = 0;
                    ans[index].x = tmp[i].index > 0 ? tmp[i].index : -1 * tmp[i].index;
                    ans[index].y = tmp[i+j].index > 0 ? tmp[i+j].index : -1 * tmp[i+j].index;
                    if(ans[index].x > ans[index].y)
                    {
                        ans[index].x ^= ans[index].y;
                        ans[index].y ^= ans[index].x;
                        ans[index].x ^= ans[index].y;
                    }
                }
        }
}

int main()
{
    scanf("%d", &point_num);
    for(int i=0; i<point_num; ++i)
    {
        scanf("%d %d", &point[i].x, &point[i].y);
        point[i].index = i + 1;
    }

    closest_pair(0, point_num - 1);
    printf("%d %d\n", dis, index + 1);

    sort(ans, ans + index + 1, sort_ans);
    for(int i=0; i<=index; ++i)
        printf("%d %d\n", ans[i].x, ans[i].y);

    return 0;
}
