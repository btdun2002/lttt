#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <map>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

// Function to swap two integers
void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}

// Map to store the result of Shanon-Fano encoding
static map<char, string> resultMap;

// Function to perform Shanon-Fano encoding
void Shanon_Fano(float *freq, char *diffChar, int size);

// Driver Code
int main()
{
    char buf[1024];

    // Input
    printf("Nhap vao Chuoi ki tu\n");
    fgets(buf, sizeof(buf), stdin);
    unsigned int len = strlen(buf) - 1;

    if (len < 1024)
        buf[len] = 0;

    // Convert to lowercase
    for (int i = 0; buf[i]; i++)
    {
        buf[i] = tolower(buf[i]);
    }

    float init[128] = {0};
    for (int i = 0; buf[i]; i++)
    {
        int j = (int)buf[i];
        init[j] += 1.0 / len;
    }

    float freq[128];
    int pos = 0;
    char diffChar[128];

    // Build different Char array and freq array
    for (int i = 0; i < 128; i++)
    {
        if (init[i] != 0)
        {
            diffChar[pos] = i;
            freq[pos] = init[i];
            pos++;
        }
    }

    // Arrange freq and diffChar in descending order
    bool swapped = false;
    for (int i = 0; i < pos; i++)
    {
        swapped = false;
        for (int j = 0; j < pos - 1 - i; j++)
        {
            if (freq[j] < freq[j + 1])
            {
                swap(freq[j], freq[j + 1]);
                char temp = diffChar[j];
                diffChar[j] = diffChar[j + 1];
                diffChar[j + 1] = temp;
                swapped = true;
            }
        }
        if (swapped == false)
        {
            break;
        }
    }

    // Display the sorted characters and their frequencies
    for (int i = 0; i < pos; i++)
    {
        cout << diffChar[i] << endl;
        cout << freq[i] << endl;
    }

    // Perform Shanon-Fano encoding
    Shanon_Fano(freq, diffChar, pos);

    // Calculate the entropy and average length of the encoded message
    float h = 0;
    float h1 = 0;
    for (int i = 0; i < pos; i++)
    {
        h -= freq[i] * log2(freq[i]);
        h1 += freq[i] * resultMap[diffChar[i]].size();
    }

    cout << "Hieu Suat: " << h / h1 << endl;
    cout << "Tinh du thua: " << 1 - h / h1 << endl;
}

// Function to perform Shanon-Fano encoding
void Shanon_Fano(float *freq, char *diffChar, int size)
{
    // Base case: If only one character is left
    if (size == 1)
    {
        cout << diffChar[0] << " " << resultMap[diffChar[0]] << endl;
        return;
    }

    // Divide the characters into two groups
    list<float> one;
    list<float> zero;
    list<char> oneChar;
    list<char> zeroChar;
    int zeroLen = 0;
    int oneLen = 0;

    float leftSum = freq[0];
    zero.push_back(freq[0]);
    zeroChar.push_back(diffChar[0]);
    zeroLen++;
    float rightSum = 0;

    for (int i = 1; i < size; i++)
    {
        rightSum += freq[i];
        one.push_back(freq[i]);
        oneChar.push_back(diffChar[i]);
        oneLen++;
    }

    float min = fabsf(rightSum - leftSum);
    int pos = 1;

    while (1)
    {
        leftSum += freq[pos];
        rightSum -= freq[pos];

        // Check if the current division yields a better balance
        if (leftSum >= rightSum)
        {
            if (min >= fabsf(leftSum - rightSum))
            {
                zeroChar.push_back(diffChar[pos]);
                zero.push_back(freq[pos]);
                oneChar.pop_front();
                one.pop_front();
                oneLen--;
                zeroLen++;
            }
            break;
        }

        zero.push_back(freq[pos]);
        zeroChar.push_back(diffChar[pos]);
        one.pop_front();
        oneChar.pop_front();
        min = fabs(leftSum - rightSum);
        pos++;
        oneLen--;
        zeroLen++;
    }

    float zeroA[128];
    float oneA[128];
    char zeroCharA[128];
    char oneCharA[128];

    // Encode the characters in the zero group
    for (int i = 0; i < zeroLen; i++)
    {
        if (resultMap[zeroChar.front()].length() == 0)
        {
            resultMap[zeroChar.front()] = "";
        }
        zeroCharA[i] = zeroChar.front();
        resultMap[zeroChar.front()].append("0");
        zeroA[i] = zero.front();
        zero.pop_front();
        zeroChar.pop_front();
    }

    // Encode the characters in the one group
    for (int i = 0; i < oneLen; i++)
    {
        if (resultMap[oneChar.front()].length() == 0)
        {
            resultMap[oneChar.front()] = "";
        }

        resultMap[oneChar.front()].append("1");
        oneCharA[i] = oneChar.front();
        oneA[i] = one.front();
        one.pop_front();
        oneChar.pop_front();
    }

    // Recursively perform Shanon-Fano encoding on each group
    Shanon_Fano(oneA, oneCharA, oneLen);
    Shanon_Fano(zeroA, zeroCharA, zeroLen);
}
