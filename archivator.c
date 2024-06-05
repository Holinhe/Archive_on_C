#include <stdio.h>
#include <stdlib.h>
#include "MyLib.h"
#include "archivator.h"

extern FILE* input;
extern FILE* output;

void coder()
{
    int num;
    unsigned int max = INT_MAX, count = 0;
    byte symbol, last;

    //Создание таблицы кодов
    num = fgetc(input);
    while (num!=EOF)
    {
        count++;
        symbol = num;
        if (code_table[num].letter == NULL)
        {
            code_table[num].letter = symbol;
            unique++;
            last = symbol;
        }
        code_table[num].count++;
        num = fgetc(input);
    }
    Node leaf[256] = { 0 };
    Node* voidNode = malloc(sizeof(Node));
    voidNode->addr = voidNode;
    voidNode->count = max;
    voidNode->letter = NULL;

    //Создание листов дерева
    for (int i = 0; i < 256; i++)
    {
        if (code_table[i].count != 0)
        {
            Node* n = malloc(sizeof(Node));
            n->visited = 0;
            n->addr = n;
            n->count = code_table[i].count;
            n->letter = code_table[i].letter;
            leaf[i] = *n;
        }
        else
        {
            leaf[i] = *voidNode;
        }
        leaf[i].left = NULL;
        leaf[i].right = NULL;
    }

    //Построение дерева
    comb(leaf, 255);
    if (unique == 1)
    {
        leaf[1] = leaf[0];
    }
    while (leaf[1].count != max)
    {
        Node* first = &leaf[0];
        Node* second = &leaf[1];
        Node* newNode = create_Parent(first, second);
        leaf[0] = *newNode;
        leaf[1] = *voidNode;
        comb(leaf, 255);
    }
    root = &leaf[0];

    //Вызов поиска в глубину
    if (unique > 1)
    {
        DFS(&leaf[0]);
    }
    if (unique == 1)
    {
        code_table[last].len = 1;
    }

    //Вывод значений из таблицы
    fwrite(&unique, 1, sizeof(byte), output);
    for (int i = 0; i < 256; i++)
    {
        if (code_table[i].count > 0)
        {
            fwrite(&code_table[i].letter, 1, sizeof(byte), output);
            fwrite(&code_table[i].len, 1, sizeof(byte), output);
            for (int j = 0; j <= (code_table[i].len - 1) / 8; j++)
            {
                fwrite(&code_table[i].key[j], 1, sizeof(byte), output);
            }
        }
    }

    fwrite(&count, sizeof(int), 1, output);
    byte code = 0;
    int range = 0;

    //Кодировка изначального файла
    rewind(input);
    num = fgetc(input);
    while (num != EOF)
    {
        symbol = num;
        for (int i = 0; i <= (code_table[num].len - 1) / 8; i++)
        {
            code |= code_table[num].key[i] >> range;
            if (8 * (i + 1) < code_table[num].len)
            {
                fwrite(&code, sizeof(byte), 1, output);
                code = 0;
                code |= code_table[num].key[i] << (8 - range);
            }
            else
            {
                range += code_table[num].len - 8 * i;
            }
            if (range > 7)
            {
                fwrite(&code, sizeof(byte), 1, output);
                code = 0;
                code |= (code_table[num].key[i] << (8 - range + code_table[num].len - 8 * i));
                range -= 8;
            }
        }
        num = fgetc(input);
    }
    fwrite(&code, sizeof(byte), 1, output);
}

void decoder()
{
    //Получение таблицы из файла
    rewind(input);
    byte c;
    fread(&c, sizeof(byte), 1, input);
    table* decode_table = malloc(c * sizeof(table));
    for (int i = 0; i < c; i++)
    {
        fread(&decode_table[i].letter, sizeof(byte), 1, input);
        fread(&decode_table[i].len, sizeof(byte), 1, input);
        for (int j = 0; j <= (decode_table[i].len - 1) / 8; j++)
        {
            fread(&decode_table[i].key[j], sizeof(byte), 1, input);
        }
    }

    //Создание дерева по таблице
    Node* Tree = malloc(sizeof(Node));
    root = Tree;
    Tree->addr = Tree;
    Tree->count = NULL;
    Tree->left = NULL;
    Tree->letter = NULL;
    Tree->right = NULL;
    Tree->visited = 0;
    for (int i = 0; i < c; i++)
    {
        for (int co = 0; co < decode_table[i].len; co++)
        {
            if (((decode_table[i].key[co / 8] << (co - co / 8 * 8) & le_bit) == 0))
            {
                if (Tree->left == NULL)
                {
                    Node* newNode = create_Node(Tree);
                    Tree->left = newNode;
                    Tree = Tree->left;
                }
                else
                {
                    Tree = Tree->left;
                }
            }
            if (((decode_table[i].key[co / 8] << (co - co / 8 * 8) & le_bit) == 128))
            {
                if (Tree->right == NULL)
                {
                    Node* newNode = create_Node(Tree);
                    Tree->right = newNode;
                    Tree = Tree->right;
                }
                else
                {
                    Tree = Tree->right;
                }
            }
        }
        Tree->letter = decode_table[i].letter;
        Tree = root;
    }

    //Декодинг сжатого файла
    unsigned int decode_count = 0, counter, i = 0;
    byte decode, magic_number = 128;
    Node* search = Tree;
    fread(&counter, sizeof(int), 1, input);
    while (decode_count < counter)
    {
        if (i % 8 == 0)
        {
            fread(&decode, sizeof(byte), 1, input);
            i = 0;
        }
        if ((decode << i & magic_number) == 0)
        {
            search = search->left;
        }
        if ((decode << i & magic_number) == 128)
        {
            search = search->right;
        }
        if (search->letter != NULL)
        {
            fwrite(&search->letter, 1, sizeof(byte), output);
            search = root;
            decode_count++;
        }
        i++;
    }
}
