#include "checker.h"
#include "generate.h"
#include "sort.h"

#define TEST_COUNT 7

int N[] = {10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000, 20000, 50000};
int N_size = 9;

void view(int n, typ* a)
{
    for (int i = 0; i < n; i++)
        printf(OUT, a[i]);
    printf("\n");
}

long long comps[TEST_COUNT], movs[TEST_COUNT];

void show(int n, FILE* out)
{
    for (int i = 1; i < TEST_COUNT; i++)
        {
            comps[TEST_COUNT - i] -= comps[TEST_COUNT - i - 1];
            movs[TEST_COUNT - i] -= movs[TEST_COUNT - i - 1];
        }
        fprintf(out, "%d;Сравнения;", n);
        for(int i = 0; i < TEST_COUNT; i++)
            fprintf(out, "%lld;", comps[i]);
        fprintf(out, "%.2lf\n", comparasion * (double)1 / TEST_COUNT);
        fprintf(out, ";Перемещения;");
        for(int i = 0; i < TEST_COUNT; i++)
            fprintf(out, "%lld;", movs[i]);
        fprintf(out, "%.2lf\n", moving * (double)1 / TEST_COUNT);
}

void init(FILE* out)
{
    fprintf(out, "n;Параметр;Номер сгенерированного массива");
    for (int i = 0; i < TEST_COUNT; i++)
        fprintf(out, ";");
    fprintf(out, "Среднее значение\n;;");
    for (int i = 0; i < TEST_COUNT; i++)
        fprintf(out, "%d;", i + 1);
    fprintf(out, "\n");
}

void process(void (*func)(int, typ*), char* str)
{
    FILE* out = fopen(str, "w");
    init(out);
    int n;
    typ* a;
    for (int i = 0; i < N_size; i++)
    {
        n = N[i];
        a = malloc(sizeof(typ) * n);
        comparasion = 0;
        moving = 0;
        for (int test = 0; test < TEST_COUNT; test++)
        {
            certaingenerate(n, a, 3);
            func(n, a);
            comps[test] = comparasion;
            movs[test] = moving;
        }
        show(n, out);
    }
    free(a);
}

void process1(void (*func)(typ*, long long, long long), char* str)
{
    FILE* out = fopen(str, "w");
    init(out);
    int n;
    typ* a;
    for (int i = 0; i < N_size; i++)
    {
        n = N[i];
        a = malloc(sizeof(typ) * n);
        comparasion = 0;
        moving = 0;
        for (int test = 0; test < TEST_COUNT; test++)
        {
            certaingenerate(n, a, 3);
            func(a, 0, n - 1);
            comps[test] = comparasion;
            movs[test] = moving;
        }
        show(n, out);
    }
    free(a);
}

int main(void)
{
    srand(time(NULL));
    process(BubbleSort, "Stats/BubbleSort.csv");
    process(SelectionSort, "Stats/SelectionSort.csv");
    process(ShellSort, "Stats/ShellSort.csv");
    process1(QuickSort, "Stats/QuickSort.csv");
    return 0;
}