#include<stdio.h>
#include<limits.h>
#include<algorithm>
#include<math.h>

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

    //printf("%d %d %d\n", delta, delta_x, delta_y);
    if(0 != delta)
    {
        (*tmp) = (float)delta_x / delta;
        return 2;
    }
    else if(delta_x == 0 && delta_y == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int intersect2(struct linear* p1, struct linear* p2, float* tmp, float* tmp2)
{
    int delta = p1->x * p2->y - p2->x * p1->y;
    int delta_x = p1->c * p2->y - p2->c * p1->y;
    int delta_y = p1->x * p2->c - p2->x * p1->c;

    //printf("%d %d %d\n", delta, delta_x, delta_y);
    if(0 != delta)
    {
        (*tmp) = (float)delta_x / delta;
        (*tmp2) = (float)delta_y / delta;
        return 2;
    }
    else if(delta_x == 0 && delta_y == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int main()
{
    int i, j, k, line;
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
    int pos = -1, neg = -1;
    for(i=0; i<line; ++i)
    {
        if(data[i].y < 0)
        {
            if(neg < 0)
                neg = i;
            else
                data[k].next = i;
            k = i;
        }
        else
        {
            if(pos < 0)
                pos = i;
            else
                data[j].next = i;
            j = i;
        }
    }
///////////////////////////////
    float xl = -INFINITY, xr = INFINITY;
    //printf("\n");
    while(line > 3)
    {
        j = -1;
        i = neg;
        while(i > -1 && data[i].next > -1)
        {
            switch(intersect(&data[i], &data[data[i].next], &tmp))
            {
            case 2:
                //移除大的
                if(xr < tmp)
                {
                    --line;
                    if((double)data[i].x / data[i].y > (double)data[data[i].next].x / data[data[i].next].y)
                    {
                        data[i].next = data[data[i].next].next;
                    }
                    else
                    {
                        data[i].x = data[data[i].next].x;
                        data[i].y = data[data[i].next].y;
                        data[i].c = data[data[i].next].c;
                        data[i].next = data[data[i].next].next;
                    }
                }
                //移除小的
                else if(tmp < xl)
                {
                    --line;
                    if((double)data[i].x / data[i].y > (double)data[data[i].next].x / data[data[i].next].y)
                    {
                        data[i].x = data[data[i].next].x;
                        data[i].y = data[data[i].next].y;
                        data[i].c = data[data[i].next].c;
                        data[i].next = data[data[i].next].next;
                    }
                    else
                    {
                        data[i].next = data[data[i].next].next;
                    }
                }
                else
                {
                    ax[++j] = tmp;
                    i = data[i].next;
                }
                break;
            case 1:
                --line;
                data[i].next = data[data[i].next].next;
                break;
            case 0:
                --line;
                if(data[i].c > data[data[i].next].c)
                {
                    data[i].next = data[data[i].next].next;
                }
                else
                {
                    data[i].x = data[data[i].next].x;
                    data[i].y = data[data[i].next].y;
                    data[i].c = data[data[i].next].c;
                    data[i].next = data[data[i].next].next;
                }
                break;
            }
            i = data[i].next;
        }
        //////////////////////////
        i = pos;
        while(i > -1 && data[i].next > -1)
        {
            switch(intersect(&data[i], &data[data[i].next], &tmp))
            {
            case 2:
                //移除小的
                if(xr < tmp)
                {
                    --line;
                    if((double)data[i].x / data[i].y < (double)data[data[i].next].x / data[data[i].next].y)
                    {
                        data[i].next = data[data[i].next].next;
                    }
                    else
                    {
                        data[i].x = data[data[i].next].x;
                        data[i].y = data[data[i].next].y;
                        data[i].c = data[data[i].next].c;
                        data[i].next = data[data[i].next].next;
                    }
                }
                //移除大的
                else if(tmp < xl)
                {
                    --line;
                    if((double)data[i].x / data[i].y < (double)data[data[i].next].x / data[data[i].next].y)
                    {
                        data[i].x = data[data[i].next].x;
                        data[i].y = data[data[i].next].y;
                        data[i].c = data[data[i].next].c;
                        data[i].next = data[data[i].next].next;
                    }
                    else
                    {
                        data[i].next = data[data[i].next].next;
                    }
                }
                else
                {
                    ax[++j] = tmp;
                    i = data[i].next;
                }
                break;
            case 1:
                --line;
                data[i].next = data[data[i].next].next;
                break;
            case 0:
                --line;
                if(data[i].c < data[data[i].next].c)
                {
                    data[i].next = data[data[i].next].next;
                }
                else
                {
                    data[i].x = data[data[i].next].x;
                    data[i].y = data[data[i].next].y;
                    data[i].c = data[data[i].next].c;
                    data[i].next = data[data[i].next].next;
                }
                break;
            }

            i = data[i].next;

        }
        //printf("%d\n", line);
        /////////////////// 4 -1 1 2 -1 3 2 1 -1 6 1 -4 6
        /*printf("%d\n", j);
        i = pos;
        while(i > -1)
        {
            printf("%d %d %d\n", data[i].x, data[i].y, data[i].c);
            i = data[i].next;
        }*/

        std::nth_element(ax, ax+(j>>1), ax+j+1);
        //printf("%f %f\n", ax[0], ax[1]);

        tmp = ax[j>>1];
        if(tmp == xr)
            tmp -= 0.5;
        if(tmp == xl)
            tmp += 0.5;

        //printf("%f\n", tmp);

        float alpha = -INFINITY, belta = INFINITY;
        float alpha_m1, alpha_m2, belta_m1, belta_m2, tmp2;

        i = neg;
        while(i > -1)
        {
            tmp2 = ((float)data[i].c - data[i].x * tmp) / data[i].y;
            if(tmp2 > alpha)
            {
                alpha = tmp2;
                alpha_m1 = (float)data[i].x / (-1 * data[i].y);
                alpha_m2 = alpha_m1;
            }
            else if(tmp2 == alpha)
            {
                alpha_m2 = (float)data[i].x / (-1 * data[i].y);
            }
            i = data[i].next;
        }
        //printf("%f %f %f\n", alpha, alpha_m1, alpha_m2);
        i = pos;
        while(i > -1)
        {
            tmp2 = ((float)data[i].c - data[i].x * tmp) / data[i].y;
            if(tmp2 < belta)
            {
                belta = tmp2;
                belta_m1 = (float)data[i].x / (-1 * data[i].y);
                belta_m2 = belta_m1;
            }
            else if(tmp2 == belta)
            {
                belta_m2 = (float)data[i].x / (-1 * data[i].y);
            }
            i = data[i].next;
        }
        //printf("%f %f %f\n", belta, belta_m1, belta_m2);

        if(alpha <= belta)
        {
            if(alpha != -INFINITY)
            {
                if(alpha_m1 * alpha_m2 <= 0)
                {
                    if(alpha >= 0)
                        printf("%d\n", (int)(alpha + 0.5));
                    if(alpha < 0)
                        printf("%d\n", (int)(alpha - 0.5));
                    return 0;
                }
                else if(alpha_m1 > 0)
                {
                    xr = tmp;
                }
                else
                {
                    xl = tmp;
                }
            }
            else
            {
                printf("-INF\n");
            }
        }
        else
        {
            if((alpha_m1 > alpha_m2 ? alpha_m1 : alpha_m2) < (belta_m1 < belta_m2 ? belta_m1 : belta_m2))
            {
                xl = tmp;
            }
            else if((alpha_m1 < alpha_m2 ? alpha_m1 : alpha_m2) > (belta_m1 > belta_m2 ? belta_m1 : belta_m2))
            {
                xr = tmp;
            }
            else
            {
                printf("NA\n");
            }
        }
        //printf("%f %f\n\n", xl, xr);
        //scanf("%d", &i);
    }
    //float tmp2;
    if(xl == -INFINITY || xr == INFINITY)
    {
        printf("-INF\n");
        return 0;
    }

    //printf("%f %f\n", xl, xr);
    i = neg;
    while(i > -1 && data[i].next > -1)
    {
        i = data[i].next;
    }
    data[i].next = pos;
    i = neg;


    /*i = neg;
    while(i > -1)
    {
        printf("%d %d %d\n",  data[i].x,  data[i].y, data[i].c);
        i = data[i].next;
    }*/









    float inter_x[6], inter_y[6], min_y = INFINITY;
    j = -1;
    float tmp2;
    i = neg;
    while(data[i].next > -1)
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

    //for(i=0; i<=j; ++i)
        //printf("%f %f\n", inter_x[i], inter_y[i]);


    //printf("::%f %d \n", inter_x[3] * data[0].x + inter_y[3] * data[0].y,data[0].c);
    //printf("::%f %d \n", inter_x[3] * data[1].x + inter_y[3] * data[1].y,data[1].c);
    //printf("::%f %d \n", inter_x[3] * data[2].x + inter_y[3] * data[2].y,data[2].c);
    i=0;
    while(i <= j)
    {
        k = neg;
        while(k > -1)
        {
            if((int)(inter_x[i] * data[k].x + inter_y[i] * data[k].y) > data[k].c)
            {
                //printf("%f %d\n", inter_x[i] * data[k].x + inter_y[i] * data[k].y, data[k].c);
                goto out;
            }
            k = data[k].next;
        }
        if(inter_y[i] < min_y)
            min_y = inter_y[i];
    out:
        ++i;
    }
    if(min_y == INFINITY)
    printf("NA\n");
    else
    {
if(min_y >= 0)
                        printf("%d\n", (int)(min_y + 0.5));
                    if(min_y < 0)
                        printf("%d\n", (int)(min_y - 0.5));
    }
    //printf("\n%f\n", min_y);
    return 0;
}
//4 6 -4 36 -1 -1 -20 6 7 54 -5 9 36
