#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "MyLib.h"

Node* create_Parent(Node* first_node, Node* second_node)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->visited = 0;
    newNode->letter = NULL;
    newNode->addr = newNode;
    newNode->count = first_node->count + second_node->count;
    newNode->left = second_node->addr;
    newNode->right = first_node->addr;
    return newNode;
}

Node* create_Node(Node* Parent)
{
    Node* newNode = malloc(sizeof(Node));
    newNode->visited = 0;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->letter = NULL;
    newNode->addr = newNode;
    return newNode;
}

void DFS(Node* Tree)
{
    if (count_DFS != unique)
    {
        if (Tree->letter == NULL)
        {
            if (Tree->right->visited == 1)
            {
                Tree->visited = 1;
                deep--;
                for (int i = 0; i <= deep / 8; i++)
                {
                    Arr[i] = 0;
                }
                deep = 0;
                DFS(root);
            }
            if (Tree->left->visited == 1)
            {
                Arr[deep / 8] |= le_bit >> deep % 8;
                deep++;
                DFS(Tree->right);
            }
            else
            {
                deep++;
                DFS(Tree->left);
            }
        }
        else
        {
            code_table[Tree->letter].len = deep;
            deep--;
            for (int i = 0; i <= deep / 8; i++)
            {
                code_table[Tree->letter].key[i] = Arr[i];
            }
            for (int i = 0; i <= deep / 8; i++)
            {
                Arr[i] = 0;
            }
            count_DFS++;
            Tree->visited = 1;
            deep = 0;
            DFS(root);
        }
    }
}

void comb(Node* leaf, int size)
{
    double s = size;
    for (int i = size; i >= 1; i /= 1.247)
    {
        for (int j = 0; i + j <= 255; j++)
        {
            if (leaf[j].count > leaf[j + i].count)
            {
                Node t;
                t = leaf[j + i];
                leaf[j + i] = leaf[j];
                leaf[j] = t;
            }
        }
    }
}
