#include<stdio.h>
#include<math.h>
#include<limits.h>
#include<algorithm>
#define FIST_MAGIC ((((65536.0 * 65536.0 * 16)+(65536.0 * 0.5))* 65536.0))

struct linear
{
    int x;
    int y;
    int c;
    int next;
};

int intersect(struct linear* p1, struct linear* p2, float* tmp)
{
    int delta = p1->x * p2->y - p2->x * p1->y;
    int delta_x = p1->c * p2->y - p2->c * p1->y;
    int delta_y = p1->x * p2->c - p2->x * p1->c;

    if(0 != delta)
    {
        (*tmp) = (float)delta_x / delta;
        return 2;
    }
    else if(delta_x == 0 && delta_y == 0)
        return 1;
    else
        return 0;
}

void ahead(struct linear* p1, struct linear* p2)
{
    p1 -> x = p2 -> x;
    p1 -> y = p2 -> y;
    p1 -> c = p2 -> c;
    p1 -> next = p2 -> next;
}

int intersect2(struct linear* p1, struct linear* p2, float* tmp, float* tmp2)
{
    int delta = p1->x * p2->y - p2->x * p1->y;
    int delta_x = p1->c * p2->y - p2->c * p1->y;
    int delta_y = p1->x * p2->c - p2->x * p1->c;

    if(0 != delta)
    {
        (*tmp) = (float)delta_x / delta;
        (*tmp2) = (float)delta_y / delta;
        return 2;
    }
    else if(delta_x == 0 && delta_y == 0)
        return 1;
    else
        return 0;
}

int QuickFist(float inval)
{
    double dtemp = FIST_MAGIC + inval;
    return ((*(int*)&dtemp) - 0x80000000);
}

int main()
{
    int i, j, k, line, pos = -1, neg = -1;
    scanf("%d", &line);
    struct linear data[line];
    float ax[line];
    float tmp;

    for(i=0; i<line; ++i)
    {
        scanf("%d", &data[i].x);
        scanf("%d", &data[i].y);
        scanf("%d", &data[i].c);
        data[i].next = -1;
    }

    // split the data into positive and negative
    for(i=0; i<line; ++i)
    {
        if(0 > data[i].y)
        {
            if(0 > neg)
                neg = i;
            else
                data[k].next = i;
            k = i;
        }
        else
        {
            if(0 > pos)
                pos = i;
            else
                data[j].next = i;
            j = i;
        }
    }
    // start Megiddo Algorithm, prune the line into 3
    float xl = -INFINITY, xr = INFINITY;
    while(3 < line)
    {
        // remove the unnecessary line
        j = -1;
        i = neg;
        while(-1 < i && -1 < data[i].next)
        {
            --line;
            switch(intersect(&data[i], &data[data[i].next], &tmp))
            {
            case 2:
                if(xr < tmp)
                {

                    if((double)data[i].x / data[i].y > (double)data[data[i].next].x / data[data[i].next].y)
                        data[i].next = data[data[i].next].next;
                    else
                        ahead(&data[i], &data[data[i].next]);
                }
                else if(tmp < xl)
                {
                    if((double)data[i].x / data[i].y > (double)data[data[i].next].x / data[data[i].next].y)
                        ahead(&data[i], &data[data[i].next]);
                    else
                        data[i].next = data[data[i].next].next;
                }
                else
                {
                    ++line;
                    ax[++j] = tmp;
                    i = data[i].next;
                }
                break;
            case 1:
                data[i].next = data[data[i].next].next;
                break;
            case 0:
                if(data[i].c > data[data[i].next].c)
                    data[i].next = data[data[i].next].next;
                else
                    ahead(&data[i], &data[data[i].next]);
                break;
            }
            i = data[i].next;
        }
        i = pos;
        while(-1 < i && -1 < data[i].next)
        {
            --line;
            switch(intersect(&data[i], &data[data[i].next], &tmp))
            {
            case 2:
                if(xr < tmp)
                {
                    if((double)data[i].x / data[i].y < (double)data[data[i].next].x / data[data[i].next].y)
                        data[i].next = data[data[i].next].next;
                    else
                        ahead(&data[i], &data[data[i].next]);
                }
                else if(tmp < xl)
                {
                    if((double)data[i].x / data[i].y < (double)data[data[i].next].x / data[data[i].next].y)
                        ahead(&data[i], &data[data[i].next]);
                    else
                        data[i].next = data[data[i].next].next;
                }
                else
                {
                    ++line;
                    ax[++j] = tmp;
                    i = data[i].next;
                }
                break;
            case 1:
                data[i].next = data[data[i].next].next;
                break;
            case 0:
                if(data[i].c < data[data[i].next].c)
                    data[i].next = data[data[i].next].next;
                else
                    ahead(&data[i], &data[data[i].next]);
                break;
            }
            i = data[i].next;
        }

        // find the median
        std::nth_element(ax, ax + (j >> 1), ax + j + 1);
        tmp = ax[j>>1];
        if(tmp == xr)
            tmp -= 0.5;
        if(tmp == xl)
            tmp += 0.5;

        // find the intersection in median
        float alpha = -INFINITY, belta = INFINITY, alpha_m1, alpha_m2, belta_m1, belta_m2, tmp2;
        i = neg;
        while(-1 < i)
        {
            tmp2 = ((float)data[i].c - data[i].x * tmp) / data[i].y;
            if(tmp2 > alpha)
            {
                alpha = tmp2;
                alpha_m1 = (float)data[i].x / (-1 * data[i].y);
                alpha_m2 = alpha_m1;
            }
            else if(tmp2 == alpha)
                alpha_m2 = (float)data[i].x / (-1 * data[i].y);
            i = data[i].next;
        }
        i = pos;
        while(-1 < i)
        {
            tmp2 = ((float)data[i].c - data[i].x * tmp) / data[i].y;
            if(tmp2 < belta)
            {
                belta = tmp2;
                belta_m1 = (float)data[i].x / (-1 * data[i].y);
                belta_m2 = belta_m1;
            }
            else if(tmp2 == belta)
                belta_m2 = (float)data[i].x / (-1 * data[i].y);
            i = data[i].next;
        }

        // find the Xm
        if(alpha <= belta)
        {
            if(-INFINITY != alpha)
            {
                if(0 >= alpha_m1 * alpha_m2)
                {
                    printf("%d\n", QuickFist(alpha));
                    return 0;
                }
                else if(0 < alpha_m1)
                    xr = tmp;
                else
                    xl = tmp;
            }
            else
                printf("-INF\n");
        }
        else
        {
            if((alpha_m1 > alpha_m2 ? alpha_m1 : alpha_m2) < (belta_m1 < belta_m2 ? belta_m1 : belta_m2))
                xl = tmp;
            else if((alpha_m1 < alpha_m2 ? alpha_m1 : alpha_m2) > (belta_m1 > belta_m2 ? belta_m1 : belta_m2))
                xr = tmp;
            else
                printf("NA\n");
        }
    }
    // when line is 3, process it directly
    if(-INFINITY == xl || INFINITY == xr)
    {
        printf("-INF\n");
        return 0;
    }
    // concat all line in neg array
    i = neg;
    while(-1 < i && -1 < data[i].next)
        i = data[i].next;
    data[i].next = pos;
    i = neg;

    // find all intersection
    float inter_x[6], inter_y[6], min_y = INFINITY, tmp2;
    j = -1;
    i = neg;
    while(-1 < data[i].next)
    {
        ++j;
        inter_x[j] = 0;
        inter_y[j] = ((float)data[i].c) / data[i].y;
        if(2 == intersect2(&data[i], &data[data[i].next], &tmp, &tmp2))
        {
            ++j;
            inter_x[j] = tmp;
            inter_y[j] = tmp2;
        }
        i = data[i].next;
    }
    ++j;
    inter_x[j] = 0;
    inter_y[j] = ((float)data[i].c) / data[i].y;
    if(2 == intersect2(&data[i], &data[neg], &tmp, &tmp2))
    {
        ++j;
        inter_x[j] = tmp;
        inter_y[j] = tmp2;
    }

    // renew the lowest Y_value
    i=0;
    while(i <= j)
    {
        k = neg;
        while(-1 < k)
        {
            if(QuickFist(inter_x[i] * data[k].x + inter_y[i] * data[k].y) > data[k].c)
                goto out;
            k = data[k].next;
        }
        if(inter_y[i] < min_y)
            min_y = inter_y[i];
out:
        ++i;
    }
    if(INFINITY == min_y)
        printf("NA\n");
    else
        printf("%d\n", QuickFist(min_y));
    return 0;
}
