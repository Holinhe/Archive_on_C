#pragma once

typedef unsigned char byte;

//��������� ������� 
typedef struct huffman_table
{
	byte letter;
	byte len;
	unsigned int count;
	byte key[32];
}table;

//��������� ������ 
typedef struct huffman_Node
{
	byte letter;
	int visited;
	unsigned int count;
	struct huffman_Node* addr;
	struct huffman_Node* left;
	struct huffman_Node* right;
}Node;

//���������� ���������� ������ ��� DFS
extern int count_DFS;
extern byte unique;
extern byte deep;
extern byte le_bit;
extern byte Arr[32];
extern table code_table[256];
extern Node* root;

//�������� ������������� ����
Node* create_Parent(Node* first_node, Node* second_node);

//�������� �������
Node* create_Node(Node* Parent);

//����� � �������
void DFS(Node* Tree);

//���������� ���������
void comb(Node* leaf, int size);