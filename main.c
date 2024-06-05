#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "MyLib.h"

FILE* input;
FILE* output;

int count_DFS = 0;
byte unique = 0;
byte deep = 0;
byte le_bit = 128;
byte Arr[32] = { 0 };
table code_table[256] = { 0 };
Node* root;

main()
{
    setlocale(LC_ALL, "Russian");
    char in[200], out[200];
    int mode, z;
    printf("������� ����� ������ ���������� (0 - ����� ����, 1 - ����������� ����, 2 - ������� ���������) ");
    z = scanf("%d", &mode);
    setlocale(LC_ALL, "Russian");
    if (mode == 0)
    {
        printf("\n������� �������� �����, ������� ������ �����, � ��� ���������� ");
        z = scanf("%s", &in);
        input = fopen(in, "r");
        if (input == NULL)
        {
            printf("������� ����� �� ���������� ��� �� ������ ������� ��� ����������. ���������� ��� ���\n\n");
            main();
        }
        printf("\n������� �������� ��� ��� ������� ����� (���� ������ ����� ������ .bin) ");
        z = scanf("%s", &out);
        output = fopen(out, "wb");
        if (output == NULL)
            printf("pizdec\n");
        coder();
        printf("������ ������ �������\n");
        fclose(input);
        fclose(output);
        main();
    }
    if (mode == 1)
    {
        printf("\n������� �������� �����, ������� ����� ����������� (���� ������ ����� ������ .bin) ");
        scanf("%s", &in);
        input = fopen(in, "rb");
        if (input == NULL)
        {
            printf("������� ����� �� ���������� ��� �� ������ ������� ��� ����������. ���������� ��� ���\n\n");
            main();
        }
        printf("\n������� �������� �����, � ������� ��� ���� �����������, � ��� ���������� ");
        scanf("%s", &out);
        output = fopen(out, "w");
        decoder();
        printf("���������� ������ �������\n");
        fclose(input);
        fclose(output);
        main();
    }
    if (mode == 2)
    {
        exit(0);
    }
}
