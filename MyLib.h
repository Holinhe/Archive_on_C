#pragma once

typedef unsigned char byte;

//Структура таблицы 
typedef struct huffman_table
{
	byte letter;
	byte len;
	unsigned int count;
	byte key[32];
}table;

//Структура дерева 
typedef struct huffman_Node
{
	byte letter;
	int visited;
	unsigned int count;
	struct huffman_Node* addr;
	struct huffman_Node* left;
	struct huffman_Node* right;
}Node;

//Глобальные переменные нужные для DFS
extern int count_DFS;
extern byte unique;
extern byte deep;
extern byte le_bit;
extern byte Arr[32];
extern table code_table[256];
extern Node* root;

//Создание родительского узла
Node* create_Parent(Node* first_node, Node* second_node);

//Создание потомка
Node* create_Node(Node* Parent);

//Поиск в глубину
void DFS(Node* Tree);

//Сортировка расчёской
void comb(Node* leaf, int size);