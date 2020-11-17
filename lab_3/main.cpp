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
    //Tree(const Tree&); // ��������� ����������� �����
    //Tree(Tree&&); // ����� � ���������(�++11)
    //Tree operator = (const Tree&) const = delete; // ������������
    //Tree operator = (Tree&&) const = delete; // ������������ � ���������
    void traversal(Node *, int &rgt_leaves); // ����������� ������������� ������
    // ����������� traversal ���� ������ �������� ����, ��� ����� ������ �� ����� �������������� � �������� ���������� �� ���������
    // ����� ���� �� ���� ������� void traversal(Node *node=root);
public:
    Tree(char num, char maxnum, int maxrow);
    ~Tree();
    void MakeTree() {root = MakeNode(0);} // ���� - ��������� ������
    bool exist() {return root != nullptr;} // �������� �� ������� ������
    int traversal(); // ������ ������������� ������
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
        cout << '\n' << "����������(������������) �����: ";
        rgt_leaves = root.traversal();
        cout << "\n������ �������� " << rgt_leaves << " ������ �����(-��)\n";
    }
    else cout << "������ �����!";
    return 0;
}
