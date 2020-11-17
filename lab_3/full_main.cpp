#include <iostream>
#include <cstring>
#include <time.h>

using namespace std;
//����� "���� ������"
class Node {
    char d; //��� ����
    Node *lft;
    Node *mdl;
    Node *rgt;
public:
    Node():lft(nullptr), mdl(nullptr), rgt(nullptr) {} // ����������� ���� ��-���������
    ~Node(){ //����������, ������������ ���������
    if (lft) delete lft;
    if (mdl) delete mdl;
    if (rgt) delete rgt; }
friend class Tree;
};

class Tree {
    Node *root; // ��������� �� ������ ������
    char num, maxnum; // ������� ����� � ������������ ���
    int maxrow, offset; // ������������ �������, �������� �����
    char **SCREEN; // ������ ��� ������ �� �����
    void clrscr(); // ������� ������� ������
    Node* MakeNode(int depth); // �������� ���������
    void OutNodes(Node* v, int r, int c); // ������ ���������
    Tree(const Tree&); // ��������� ����������� �����
    Tree(Tree&&); // ����� � ���������(�++11)
    Tree operator = (const Tree&) const = delete; // ������������
    Tree operator = (Tree&&) const = delete; // ������������ � ���������
    void traversal(Node *, int &rgt_leaves); // ����������� ������������� ������
    // ����������� traversal ���� ������ �������� ����, ��� ����� ������ �� ����� �������������� � �������� ���������� �� ���������
    // ����� ���� �� ���� ������� void traversal(Node *node=root);
public:
    Tree(char num, char maxnum, int maxrow);
    ~Tree();
    void MakeTree() {root = MakeNode(0);} // ���� - ��������� ������
    bool exist() {return root != nullptr;} // �������� �� ������� ������
    void traversal(int &rgt_leaves); // ������ ������������� ������
    int DFS();// ����� � �������
    int BFS(); // ����� � ������
    void OutTree(); // ������ �� �����
};
Tree:: Tree(char nm, char mnm, int mxr): // �����������, ��������� ������� ��������, �����. ��� ������ ����������� �� �����
    num(nm), maxnum(mnm), maxrow(mxr), offset(40), root(nullptr), SCREEN(new char *[maxrow])
    { for (int i=0;i<maxrow;i++) SCREEN[i] = new char[80]; }
Tree:: ~Tree() { // ���������� ������ ���������� ������� �������� � ��������� ���������� ���� ��� �����
    for (int i=0;i<maxrow;i++) delete[] SCREEN[i];
    delete[] SCREEN; delete root; }
Node *Tree::MakeNode(int depth)
{
    Node *v=nullptr;
    int Y = (depth < rand()%4+1) && (num<=maxnum);
    if (Y) {
        v = new Node;
        //v->d = num++; // �������� � ������ �������
        v->lft = MakeNode(depth+1);
        v->mdl = MakeNode(depth+1);
        //v->d = num++; // �������� �� ���������� �������
        v->rgt = MakeNode(depth+1);
        v->d = num++; // �������� � �������� �������
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
    if (r&&c&&(c<80)) SCREEN[r-1][c-1] = v->d; //����� �����
    if (r<maxrow) {
        if (v->lft) OutNodes(v->lft, r+1, c-(offset >> r));
        if (v->mdl) OutNodes(v->mdl, r+1, c);
        if (v->rgt) OutNodes(v->rgt, r+1, c+(offset >> r));
    }
}
template <class Item> class STACK // ������ ��� ������ ����
{
    Item *S;
    int t;
public:
    STACK(int maxt): S(new Item[maxt]), t(0) {}
    int empty() const { return t==0; }
    void push(Item item) { S[t++] = item; }
    Item pop() { return (t ? S[--t] : 0); }
};
template <class Item> class QUEUE // ������ ��� ������ �������
{
    Item *Q;
    int h,N,t;
public:
    QUEUE(int maxQ):Q(new Item[maxQ+1]), t(0), N(maxQ), h(0) {}
    int empty() const { return (h%N)==t; }
    void push(Item item) { Q[t++] = item; t %=N; }
    Item pop() { h%=N; return Q[h++]; }
};
void Tree::traversal(int &rgt_leaves)
{
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
int Tree::DFS()
{
    const int MaxS=20; // ������������ ������ �����
    int count=0;
    STACK <Node*> S(MaxS); // �������� ����� ���������� �� ����
    S.push(root);
    while (!S.empty())
    {
        Node *v = S.pop();
        cout << v->d << '_'; count++;
        if (v->rgt) S.push(v->rgt);
        if (v->mdl) S.push(v->mdl);
        if (v->lft) S.push(v->lft);
    }
    return count;
}
int Tree::BFS()
{
    const int MaxQ=20; // ������������ ������ �������
    int count=0;
    QUEUE <Node*> Q(MaxQ); // �������� ������� ���������� �� ����
    Q.push(root);
    while (!Q.empty())
    {
        Node *v = Q.pop();
        cout << v->d << '_'; count++;
        if (v->rgt) Q.push(v->rgt);
        if (v->mdl) Q.push(v->mdl);
        if (v->lft) Q.push(v->lft);
    }
    return count;
}

int main()
{
    Tree root('A', 'Z', 8);
    srand(time(NULL));
    setlocale(LC_ALL, "Russian");
    int rgt_leaves=0;
    root.MakeTree();
    if (root.exist())
    {
        root.OutTree();
        cout << '\n' << "����������(������������) �����: ";
        root.traversal(rgt_leaves);
        cout << "\n������ �������� " << rgt_leaves << " ������ �������\n";
        /*cout << '\n' << "����� � �������: ";
        root.DFS();
        cout << '\n' << "����� � ������: ";
        root.BFS();*/
    }
    else cout << "������ �����!";
    return 0;
}
