#include<stdio.h>
#include<algorithm>

using namespace std;
int w, n, lb = 0;

struct Item
{
    int value, weight;
};
struct Item item[1000];

int bound(int value, int weight, int level)
{
    if (weight >= w)
        return 0;

    while(level < n && weight + item[level].weight <= w)
    {
        weight += item[level].weight;
        value += item[level].value;
        ++level;
    }
    if(level < n)
        value += (w - weight) * item[level].value / item[level].weight;
    return value;
}

void knapsack(int value, int weight, int level)
{
    if(level == n || lb >= bound(value, weight, level))
        return;

    int new_weight = weight + item[level].weight, new_value = value + item[level].value;
    if(new_weight <= w && new_value > lb)
        lb = new_value;

    knapsack(new_value, new_weight, level + 1);
    knapsack(value, weight, level + 1);
}

bool for_sort(struct Item a, struct Item b)
{
    return (double)a.value / a.weight > (double)b.value / b.weight;
}

int main()
{
    scanf("%d %d", &w, &n);
    for(int i=0; i<n; ++i)
        scanf("%d %d", &item[i].value, &item[i].weight);

    sort(item, item + n, for_sort);
    knapsack(0,0,0);
    printf("%d\n", lb);
    return 0;
}
