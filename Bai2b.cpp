#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// C++(STL) program for Huffman Coding with STL
#include <bits/stdc++.h>
using namespace std;

// A Huffman tree node
struct MinHeapNode
{
    // One of the input characters
    char data;

    // Frequency of the character
    unsigned freq;

    // Left and right child
    MinHeapNode *left, *right;

    MinHeapNode(char data, unsigned freq)
    {
        left = right = NULL;
        this->data = data;
        this->freq = freq;
    }
};

// For comparison of two heap nodes (needed in min heap)
struct compare
{
    bool operator()(MinHeapNode *l, MinHeapNode *r)
    {
        return (l->freq > r->freq);
    }
};

// Prints huffman codes from the root of Huffman Tree.
void printCodes(struct MinHeapNode *root, string str)
{
    if (!root)
        return;

    if (root->data != '$')
        cout << root->data << ": " << str << "\n";

    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// The main function that builds a Huffman Tree and print codes by traversing the built Huffman Tree
void HuffmanCodes(char data[], int freq[], int size)
{
    struct MinHeapNode *left, *right, *top;

    // Create a min heap & inserts all characters of data[]
    priority_queue<MinHeapNode *, vector<MinHeapNode *>, compare> minHeap;

    for (int i = 0; i < size; ++i)
        minHeap.push(new MinHeapNode(data[i], freq[i]));

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1)
    {
        // Extract the two minimum freq items from min heap
        left = minHeap.top();
        minHeap.pop();

        right = minHeap.top();
        minHeap.pop();

        // Create a new internal node with frequency equal to the sum of the two nodes frequencies.
        // Make the two extracted node as left and right children of this new node.
        // Add this node to the min heap '$' is a special value for internal nodes, not used
        top = new MinHeapNode('$', left->freq + right->freq);

        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // Print Huffman codes using the Huffman tree built above
    printCodes(minHeap.top(), "");
}

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
        init[j] += 1.0;
    }

    char diffChar[128];
    int freq[128];
    int pos = 0;

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

    HuffmanCodes(diffChar, freq, pos);
}
