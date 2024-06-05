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
    printf("Укажите режим работы архиватора (0 - сжать файл, 1 - распоковать файл, 2 - закрыть архиватор) ");
    z = scanf("%d", &mode);
    setlocale(LC_ALL, "Russian");
    if (mode == 0)
    {
        printf("\nУкажите название файла, который хотите сжать, и его расширение ");
        z = scanf("%s", &in);
        input = fopen(in, "r");
        if (input == NULL)
        {
            printf("Данного файла не существует или вы забыли указать его расширение. Попробуйте ещё раз\n\n");
            main();
        }
        printf("\nУкажите название для уже сжатого файла (файл должен иметь формат .bin) ");
        z = scanf("%s", &out);
        output = fopen(out, "wb");
        if (output == NULL)
            printf("pizdec\n");
        coder();
        printf("Сжатие прошло успешно\n");
        fclose(input);
        fclose(output);
        main();
    }
    if (mode == 1)
    {
        printf("\nУкажите название файла, который нужно распоковать (файл должен иметь формат .bin) ");
        scanf("%s", &in);
        input = fopen(in, "rb");
        if (input == NULL)
        {
            printf("Данного файла не существует или вы забыли указать его расширение. Попробуйте ещё раз\n\n");
            main();
        }
        printf("\nУкажите название файла, в который его надо распаковать, и его расширение ");
        scanf("%s", &out);
        output = fopen(out, "w");
        decoder();
        printf("Распаковка прошла успешно\n");
        fclose(input);
        fclose(output);
        main();
    }
    if (mode == 2)
    {
        exit(0);
    }
}
