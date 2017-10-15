#include<stdio.h>
#include<vector>
#include<iostream>
#include<algorithm>

int len, len1, len2, lcs[101][101];
char data[101];
std::string input1, input2;
std::vector<std::string> output;

void printAll(int index1, int index2, int currlcs)
{
    char k;
    int i, j;
    if(currlcs == len)
    {
        data[currlcs] = '\0';
        output.push_back(data);
        return;
    }
    if(index1==len1 || index2==len2)
        return;

    for(i=index1; i<len1; ++i)
    {
        k = input1[i];
        for(j=index2; j<len2; ++j)
            if(k == input2[j] && lcs[i+1][j+1] == currlcs + 1)
            {
                data[currlcs] = k;
                printAll(i+1, j+1, currlcs+1);
            }
    }
}

int main()
{
    int i,j;
    getline(std::cin, input1);
    getline(std::cin, input2);
    len1 = input1.length();
    len2 = input2.length();
    for(i=0; i<=len1; ++i)
        lcs[i][0] = 0;
    for(i=0; i<=len2; ++i)
        lcs[0][i] = 0;
    for(i=1; i<=len1; ++i)
        for(j=1; j<=len2; ++j)
            if(input1[i-1] == input2[j-1])
                lcs[i][j] = lcs[i-1][j-1] + 1;
            else
            {
                if(lcs[i-1][j] > lcs[i][j-1])
                    lcs[i][j] = lcs[i-1][j];
                else
                    lcs[i][j] = lcs[i][j-1];
            }
    printf("%d ", len = lcs[len1][len2]);
    printAll(0, 0, 0);
    len = output.size();
    printf("%d\n", len);
    std::sort(output.begin(), output.end());
    for(i=0; i<len; ++i)
        std::cout << output[i] << std::endl;
    return 0;
}
