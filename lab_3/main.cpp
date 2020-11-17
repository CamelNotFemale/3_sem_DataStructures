#include <iostream>
#include <cstring>
#include <time.h>

using namespace std;
//класс "узел дерева"
class Node {
    char d; //тег узла
    Node *lft;
    Node *mdl;
    Node *rgt;
public:
    Node():lft(nullptr), mdl(nullptr), rgt(nullptr) {} // конструктор узла по-умолчанию
    ~Node(){ //деструктор, уничтожающий поддерево
    if (lft) delete lft;
    if (mdl) delete mdl;
    if (rgt) delete rgt; }
friend class Tree;
};

class Tree {
    Node *root; // указатель на корень дерева
    char num, maxnum; // счётчик тегов и максимальный тег
    int maxrow, offset; // максимальная глубина, смещение корня
    char **SCREEN; // память для вывода на экран
    void clrscr(); // очистка рабочей памяти
    Node* MakeNode(int depth); // создание поддерева
    void OutNodes(Node* v, int r, int c); // выдача поддерева
    //Tree(const Tree&); // фиктивный конструктор копии
    //Tree(Tree&&); // копия с переносом(с++11)
    //Tree operator = (const Tree&) const = delete; // присваивание
    //Tree operator = (Tree&&) const = delete; // присваивание с переносом
    void traversal(Node *, int &rgt_leaves); // Продолжение симметричного обхода
    // Перегрузкой traversal была решена проблема того, что члены класса не могут использоваться в качестве аргументов по умолчанию
    // иначе была бы одна функций void traversal(Node *node=root);
public:
    Tree(char num, char maxnum, int maxrow);
    ~Tree();
    void MakeTree() {root = MakeNode(0);} // ввод - генерация дерева
    bool exist() {return root != nullptr;} // проверка на пустоту дерева
    int traversal(); // Начало симметричного обхода
    void OutTree(); // выдача на экран
};
Tree:: Tree(char nm, char mnm, int mxr): // Конструктор, создающий матрицу символов, необх. для выдачи изображения на экран
    num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr), SCREEN(new char *[maxrow])
    { for (int i=0;i<maxrow;i++) SCREEN[i] = new char[80]; }
Tree:: ~Tree() { // Деструктор дерева уничтожает матрицу символов и запускает деструктор узла для корня
    for (int i=0;i<maxrow;i++) delete[] SCREEN[i];
    delete[] SCREEN; delete root; }
Node *Tree::MakeNode(int depth)
{
    Node *v=nullptr;
    int Y = (depth < rand()%4+1) && (num<=maxnum);
    if (Y) {
        v = new Node;
        //v->d = num++; // Разметка в прямом порядке
        v->lft = MakeNode(depth+1);
        v->mdl = MakeNode(depth+1);
        //v->d = num++; // Разметка во внутреннем порядке
        v->rgt = MakeNode(depth+1);
        v->d = num++; // Разметка в обратном порядке
    }
    return v;
}
void Tree::OutTree()
{
    clrscr();
    OutNodes(root, 1, offset);
    for (int i=0; i<maxrow; i++)
    {
        SCREEN[i][79]=0;
        cout << '\n' << SCREEN[i];
    }
    cout << '\n';
}
void Tree::clrscr() {
    for (int i=0; i<maxrow; i++) memset(SCREEN[i], '.', 80); }
void Tree::OutNodes(Node *v, int r, int c)
{
    if (r&&c&&(c<80)) SCREEN[r-1][c-1] = v->d; //вывод метки
    if (r<maxrow) {
        if (v->lft) OutNodes(v->lft, r+1, c-(offset >> r));
        if (v->mdl) OutNodes(v->mdl, r+1, c);
        if (v->rgt) OutNodes(v->rgt, r+1, c+(offset >> r));
    }
}
int Tree::traversal()
{
    int rgt_leaves=0;
    Node *node = root;
    if (node)
    {
        if (node->lft) traversal(node->lft,rgt_leaves);
        if (node->mdl) traversal(node->mdl,rgt_leaves);
        cout << node->d << '_';
        if (node->rgt) {
            traversal(node->rgt,rgt_leaves);
            rgt_leaves++;
        }
    }
    return rgt_leaves;
}
void Tree::traversal(Node *node, int &rgt_leaves)
{
    if (node->lft) traversal(node->lft,rgt_leaves);
    if (node->mdl) traversal(node->mdl,rgt_leaves);
    cout << node->d << '_';
    if (node->rgt) {
            traversal(node->rgt,rgt_leaves);
            rgt_leaves++;
        }
}

int main()
{
    Tree root('A', 'Z', 8);
    int rgt_leaves;
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");

    root.MakeTree();
    if (root.exist())
    {
        root.OutTree();
        cout << '\n' << "Внутренний(симметричный) обход: ";
        rgt_leaves = root.traversal();
        cout << "\nДерево содержит " << rgt_leaves << " правых листа(-ев)\n";
    }
    else cout << "Дерево пусто!";
    return 0;
}
