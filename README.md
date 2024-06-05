Проект Путилова Артёма 23933

Проект - приложение, которое способно кодировать текстовые файлы и декодировать бинарные. Для этого используется алгоритм Хаффмана.
Приложение принимает на вход файл с расширением txt и на его основе создаёт bin-файл, из которого можно получить исходный файл.
Проект состоит из 3 файлов на языке Си.
1) MyLib.c
2) archivator.c
3) main.c

• MyLib.c
Данный файл содержит:
1) определние типа данных byte (unsigned char)
2) Структуру table, которая содержит параметры элементов таблицы кодов
3) Структуру Node, которая содержит параметры элементов  бинарного дерева
4) функцию create_Parent, которая используется для создания родительской вершины в бинарном дереве
5) функцию create_Node, которая создаёт потомка от родительской вершины
6) функцию DFS, которая позволяет выполнить поиск в глубину в бинарном дереве
7) функцию comb - соритровка "расчёской"

• archivator.c
Данный файл содержит:
1. функцию coder, которая действует по следующему алгоритму
   1) Считывает данные из файла и на их основе составляет таблицу
   2) На основе каждого элемента таблицы создаются листы, которые заносятся в массив листов бинарного дерева
   3) Массив сортируется. Далее для первого и второго элемента созаётся общая вершина (create_Parent). Эта вершина заменяет одного из своих потомков (второй потомок "зануляется"), затем массив вновь сортируется
   4) При помощи поиска в глубину в полученном бинарном дереве создаются коды для каждого символа
   5) Коды заносятся в таблицу. Полученная таблица заносится в bin-файл
   6) Изначальный файл кодируется по таблице
2. функцию decoder, которая действует по следующему алгоритму
   1) Считывает таблицы из bin-файла
   2) По полученной таблице составляется бинарное дерево
   3) По дереву декодируется bin-файл

  Для компиляции используется GCC, в котором сначала нужно указать расположение нужных файлов (например: cd C:\Users\Documents\project), 
  а затем ввести команду для создания приложения (например: gcc -o archive main.c archivator.c MyLib.c).
  Приложение имеет 3 команды: 0 - кодирнование текстового файла, 1 - декодирование bin-файла, 2 - выход из приложения. 
  После получения команды 0 или 1 нужно ввести название (или расположение) входного и выходного файлов.
  Пример:
  0
  input.txt
  a.bin
  Пример input.txt и a.bin можно посмотреть в репозитории.
