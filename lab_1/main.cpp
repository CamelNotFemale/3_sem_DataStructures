#include <iostream>
#include <stdlib.h>
#include <time.h>
/*  Формула E = ((A\B)\C)\D
    Контрольный тест:
    A={'a','b','c','d'}
    B={'b','e','f'}
    C={'d','g','h'}
    D={'b','d', 'c'}
    Ожидаемый ответ:
    E={'a'}
*/
using namespace std;
const int N=26;
struct NODE
{
    NODE *next;
    char el;
};

// Функции для работы со статичным массивом
void process(char A[], char B[], char E[])
{
    int i=0, j=0, k=0;
    bool flag;
    while (A[i]!= 0) {
        flag=true;
        j=0;
        while (B[j] != 0){
            //cout << A[i] << ' ' << B[j] << endl;
            if (A[i]==B[j]) flag=false;
            j++;
        }
        if (flag) {
            E[k]=A[i];
            (k)++;
        }
        i++;
    }
    E[k]=0;
}
void print(char E[])
{
    int i=0;
    cout << "{ ";
    while (E[i] != 0) printf("%c ", E[i++]);
    printf("}\n");
}
// Функции для осуществления работы со списком
NODE *make_head()
{
    NODE *HEAD = NULL;
    HEAD = (NODE*)malloc(sizeof(NODE));
    if (HEAD) HEAD->next=NULL;
    return HEAD;
}
NODE *create(char sym)
{
    NODE *node=NULL;
    node = (NODE*)malloc(sizeof(NODE));
    if (node) {
        node->el=sym;
        node->next=NULL;
    }
    return node;
}
void add(NODE *head, NODE *node)
{
    NODE *p=head;
    if (!(head->next)) head->next=node;
    else {
        while (p->next != NULL) p = p->next;
        p->next = node;
    }
}
void strToList(NODE *HEAD, char A[])
{
    int i=0;
    NODE *p=NULL;
    while (A[i] != 0) {
        p=create(A[i]);
        add(HEAD, p);
        i++;
    }
}
NODE *process(NODE *HEAD_A, NODE *HEAD_B)
{
    bool flag;
    NODE *p_a, *p_b, *HEAD_E, *p_e;

    HEAD_E = make_head();
    p_a = HEAD_A->next;
    while (p_a) {
        flag=true;
        p_b=HEAD_B->next;
        while (p_b){
            //cout << p_a->el << ' ' << p_b->el << endl;
            if (p_a->el==p_b->el) flag=false;
            p_b=p_b->next;
        }
        if (flag) {
            p_e = create(p_a->el);
            add(HEAD_E, p_e);
        }
        p_a=p_a->next;
    }
    return HEAD_E;
}
void print(NODE *HEAD)
{
    NODE *p=HEAD;
    cout << "{ ";
    if (!(HEAD->next)) cout << "List is empty" << endl;
    else {
        do {
            p = p->next;
            cout << p->el << " ";
        } while (p->next);
    }
    cout << "}" << endl;
}
void clean(NODE *node)
{

}
// Функции для работы с массивом boolean'ов
void strToUniverse(char A[], bool U[])
{
    int i=0;
    while (A[i] != 0) {
        U[(int)A[i]-'a']=1;
        i++;
    }
}
void process(bool U[], char A[])
{
    int i=0;
    while (A[i]!=0) {
        U[(int)A[i]-'a']=0;
        i++;
    }
}

void print(bool U[])
{
    int i;
    cout << "{ ";
    for (i=0; i<N; i++)
        if (U[i]!=0) cout << (char)(i+'a') << " ";
    cout << "}" << endl;
}

// Функции для работы с машинным словом
void strToWord(int *word, char A[])
{
    int i=0;
    while (A[i] != 0) {
        *word = *word | (1 << (int)(A[i]-'a'));
        i++;
    }
}
void print(int word)
{
    int i;
    cout << "{ ";
    for (int i=0; i<N; i++)
        if (word & (1 << i)) cout << (char)(i+'a') << " ";
    cout << "}" << endl;
}

// Общие функции
int Menu(int i)
{
    char c;
    int Q;
    system("cls");
    printf("What you want to do?\n");
    switch (i)
    {
        case 0:
            printf("1 - Input data\n");
            printf("2 - Processing method\n");
            printf("3 - Output initial data\n");
            printf("0 - Exit\n");
            break;
        case 11:
            printf("1 - Enter data\n");
            printf("2 - Generate data\n");
            printf("0 - Back\n");
            break;
        case 12:
            printf("1 - Use static array\n");
            printf("2 - Use a list\n");
            printf("3 - Use array of boolean\n");
            printf("4 - Use machine word\n");
            printf("0 - Back\n");
            break;
    }

    printf("Your choise - ");
    scanf("%d", &Q);
    while ((c=getchar())!='\n');
    return Q;
}
void generateData(char A[])
{
    int gen, i, k=0;
    gen = rand() % 0x3FFFFFF;
    for (i=0; i<N; i++)
    {
        if (gen & 1<<i) A[k++] = (char)(i+'a');
    }

    A[k]='\0';
    print(A);
    system("pause");
}
int main()
{
    srand(time(NULL));
    NODE *HEAD_A=NULL, *HEAD_B=NULL, *HEAD_C=NULL, *HEAD_D=NULL, *HEAD_E=NULL;
    int wA=0, wB=0, wC=0, wD=0, wE=0, Q, Q11, Q12;
    char A[N+1]={'a','b','c','d'};
    char B[N+1]={'b','e','f'};
    char C[N+1]={'d','g','h'};
    char D[N+1]={'b','d'};
    char E[N+1]={};
    bool U[N] = {};
    int rolls = 1000000;
    clock_t ticks;

    do
    {
        Q = Menu(0);
        switch (Q)
        {
        case 1:
            do
            {
                Q11 = Menu(11);
                switch (Q11)
                {
                case 1:
                    cout << "Input A: "; cin >> A;
                    cout << "Input B: "; cin >> B;
                    cout << "Input C: "; cin >> C;
                    cout << "Input D: "; cin >> D;
                    Q11=0;
                    break;
                case 2:
                    generateData(A);
                    generateData(B);
                    generateData(C);
                    generateData(D);
                    Q11=0;
                case 0:
                    break;
                default:
                    printf("Error. Try again...\n");
                }
            } while (Q11 != 0);
            break;
        case 2:
            do
            {
                Q12 = Menu(12);
                switch (Q12)
                {
                case 1:
                    process(A, B, E); // Преобразования статичными массивами
                    process(E, C, E);
                    process(E, D, E);
                    cout << "Result using a static array:" << endl;
                    cout << "E = "; print(E);
                    Q12=0;
                    break;
                case 2: // !!!! ДОБАВИТЬ ОЧИСТКУ ПАМЯТИ !!!! //
                    HEAD_A = make_head();
                    strToList(HEAD_A, A); // Преобразование строки в список
                    HEAD_B = make_head();
                    strToList(HEAD_B, B);
                    HEAD_C = make_head();
                    strToList(HEAD_C, C);
                    HEAD_D = make_head();
                    strToList(HEAD_D, D);
                    HEAD_E = process(HEAD_A, HEAD_B); // Преобразования списком
                    HEAD_E = process(HEAD_E, HEAD_C);
                    HEAD_E = process(HEAD_E, HEAD_D);
                    cout << "Result using a List:" << endl;
                    cout << "E = "; print(HEAD_E); // Вывод в виде списка
                    Q12=0;
                    break;
                case 3:
                    strToUniverse(A, U); // Преобразование строки в универсум
                    process(U, B); // Преобразования при помозщи универсума
                    process(U, C);
                    process(U, D);
                    cout << "Result using a Universum:" << endl;
                    cout << "E = "; print(U); // Вывод по составленному универсуму
                    Q12=0;
                    break;
                case 4:
                    strToWord(&wA, A); // Преобразование строки в машинное слово
                    strToWord(&wB, B);
                    strToWord(&wC, C);
                    strToWord(&wD, D);
                    wE = ((wA & ~wB) & ~wC) & ~wD; // Преобразование машинным слово
                    cout << "Result using a Machine word:" << endl;
                    cout << "E = "; print(wE); // Вывод по машинному слову
                    Q12=0;
                    break;
                case 0:
                    break;
                default:
                    printf("Error. Try again...\n");
                }
                system("pause");
            } while (Q12!=0);
            break;
        case 3:
            cout << "A = "; print(A);
            cout << "B = "; print(B);
            cout << "C = "; print(C);
            cout << "D = "; print(D);
            system("pause");
            break;
        case 0:
            printf("Exit...");
            break;
        default:
            printf("Error. Try again...\n");
        }
    } while (Q !=0);
    if (HEAD_A)
    {
        clean(HEAD_A);
        clean(HEAD_B);
        clean(HEAD_C);
        clean(HEAD_D);
        clean(HEAD_E);
    }
    return 0;
}
