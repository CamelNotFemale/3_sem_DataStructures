#ifndef SET_H_INCLUDED
#define SET_H_INCLUDED
#include <cstring>

//****************************************Array***********************************
/*
class Set {
private: // �������� ����� ������ � ������
    static int N, cnt; // �������� ����������
    int n; // �������� ���������
    char S, * A; // ��� � ������ ��� ���������
public: // �������� ����� � ������� ��� ������ � ����������
    //������������ � ����������
    Set(char); // ����������� ���������
    Set(); // ����������� �� ���������
    Set(const Set&); // ����������� �����
    Set& operator = (const Set&); // ���������� ��������� ������������
    ~Set() { delete[] A; } // ����������

    //�������� ��� ����������
    Set operator | (const Set&) const;
    Set operator & (const Set&) const;
    Set & operator &= (const Set& B);
    Set & operator |= (const Set& B);
    Set operator ~ () const;

    //���������
    void Show(); //����� ��������� �� �����
    void Show(char c); //����� � ������������� �����
    int power( ) { return n; } //��������
    void rewrite(char str[]); //������������ ���������
};

Set& Set :: operator &= (const Set& B)
{
    Set C(*this);
    n = 0;
    for (int i = 0; i < C.n; i++)
    {
        for (int j = 0; j < B.n; j++)
            if (C.A[i] == B.A[j]) A[n++] = C.A[i];
    }
    A[n] = 0;
    return *this;
}

Set Set :: operator & (const Set& B) const
{
    Set C(*this);
    return (C &= B);
}

Set& Set :: operator |= (const Set& B)
{
    for (int i = 0; i < B.n; i++)
    {
        bool f = true;
        for (int j = 0; j < n; j++)
            if (B.A[i] == A[j]) f = false;
        if (f) A[n++] = B.A[i];
    }
    A[n] = 0;
    return *this;
}

Set Set :: operator | (const Set& B) const
{
    Set C = *this;
    return (C |= B);
}

Set Set :: operator ~ () const
{
    Set C;
    for (char l = 'a'; l <= 'z'; ++l)
    {
        bool f = true;
        for (int j = 0; j < n; j++)
            if (l == A[j]) { f = false; break; }
        if (f) C.A[C.n++] = l;
    }
    C.A[C.n] = 0;
    return C;
}

Set::Set() : n(0), S('A' + cnt++), A(new char[N + 1]) // ����������� ������� ���������
{
    A[0] = '\0';
}

Set::Set(char s) : S('A' + cnt++), n(0), A(new char[N + 1]) // ����������� ���������� ���������
{
    for (int i = 0; i < N; i++)
        if (rand() % 2) A[n++] = i + 'a';
    A[n] = '\0';
    cout << '\n' << S << " = [" << A << "] " << "|" << this->power() << "|";
}

Set :: Set(const Set & B): S('A'+ cnt++), n(B.n), A(new char[N+1]) // ����������� �����������
{
    char *dst(A), *src(B.A);
    while (*dst++ = *src++);
}

Set& Set :: operator = (const Set& B)
{
    if (this != &B)
    {
        char *dst(A), *src(B.A);
        n = B.n;
        while (*dst++ = *src++); S = 'A'+cnt++;
    }
    return *this;
}

void Set::rewrite(char str[])
{
    n = 0;
    for (int i = 0; i < strlen(str); i++)
        A[n++] = str[i];
    A[n] = '\0';
    Show();
}

void Set::Show()
{
    cout << '\n' << S << " = [" << A << "] " << "|" << power() << "|" << endl;
}

void Set::Show(char c)
{
    cout << '\n' << c << " = [" << A << "] " << "|" << power() << "|" << endl;
}
*/
//****************************************Array***********************************


//*********************************************Machine Word***********************
/*
class Set
{
private:
    static int N, cnt; // �������� ���������� � ���������� ��������
    char name; // �������� ���������
    unsigned int S; // ������ ��� ���������
public:
    Set(char); // ����������� ������
    Set(): name('A' + cnt++), S(0){} // ����������� �� ���������
    Set(const Set& other): name('A' + cnt++), S(other.S){} // ���������� �����������

    // �������� ��� �����������
    Set& operator = (const Set&);
    Set operator & (const Set&) const;
    Set operator | (const Set&) const;
    Set operator / (const Set&) const;
    Set operator ~ () const;

    // ���������
    inline char get_name() {return name;}
    int power();
    void rewrite(char str[]); //������������ ���������
    void Show();
    void Show(char);
};

// ���������� �� ��������� �����������
Set::Set(char tag): name(tag), S(rand()%0x3ffffff)
{
    cnt++;
    Show();
}

// ��������

Set & Set::operator = (const Set& other)
{
    if (this != &other)
        S = other.S;
    return *this;
}

Set Set::operator & (const Set& other) const
{
    Set C;
    C.S = S & other.S;
    return C;
}


Set Set::operator | (const Set& other) const
{
    Set C;
    C.S = S | other.S;
    return C;
}

Set Set::operator / (const Set& other) const
{
    Set C;
    C.S = S & ~other.S;
    return C;
}

Set Set::operator ~ () const
{
    Set C;
    C.S = ~S & 0x3ffffff;
    return C;
}

// ���������
int Set::power()
{
    int pow = 0;
    unsigned int n = S;
    while(n != 0)
    {
        pow++;
        n &= (n-1);
    }
    return pow;
}

void Set::rewrite(char str[])
{
    S = 0;
    for (int i = 0; i < strlen(str); i++)
        S = S | 1 << str[i] - 'a';
    Show();
}

void Set::Show()
{
    char* result = new char[N+1];
    int i,j;

    for(i = 0, j = 0; i < N; ++i)
        if(1 << i & S)
            result[j++] = i + 'a';
    result[j] = '\0';

    std::cout << name << " = {" << result << "}, |" << name << "| = " << this->power() << std::endl;
    delete [] result;
}

void Set::Show(char c)
{
    char* result = new char[N+1];
    int i,j;

    for(i = 0, j = 0; i < N; ++i)
        if(1 << i & S)
            result[j++] = i + 'a';
    result[j] = '\0';

    std::cout << c << " = {" << result << "}, |" << name << "| = " << this->power() << std::endl;
    delete [] result;
}
*/
//*********************************************Machine Word************************


//*********************************************Boolean*****************************
/*
class Set
{
private:
    static int N, cnt; // �������� ���������� � ���������� ��������
    char name; // �������� ���������
    bool *S; // ������ ��� ���������
public:
    Set(char); // ����������� ������
    Set(); // ����������� �� ���������
    Set(const Set&); // ���������� �����������
    ~Set(){delete [] S;} // ���������� ������

    // �������� ��� �����������
    Set& operator = (const Set&);
    Set operator & (const Set&) const;
    Set operator | (const Set&) const;
    Set operator / (const Set&) const;
    Set operator ~ () const;

    // ���������
    inline char get_name() {return name;}
    int power();
    void rewrite(char str[]); //������������ ���������

    void Show();
    void Show(char c);
};

Set::Set(): name('A' + cnt++), S(new bool[N]) // ���������� ������� ���������
{
    for (int i = 0; i < N; ++i)
        S[i] = 0;
}

Set::Set(char tag): name(tag), S(new bool[N]) // ���������� ���������� ���������
{
    cnt++;
    for (int i = 0; i < N; ++i)
        S[i] = rand()%2;
    Show();
}

Set::Set(const Set& other): name('A' + cnt++), S(new bool[N]) // ���������� �����������
{
    for (int i = 0; i < N; ++i)
        S[i] = other.S[i];
}


// ��������
Set & Set::operator = (const Set& other)
{
    if (this != &other)
    {
        for (int i = 0; i < N; ++i)
            S[i] = other.S[i];
    }
    return *this;
}

Set Set::operator & (const Set& other) const
{
    Set C;
    for (int i = 0; i < N; ++i)
        C.S[i] = S[i] && other.S[i];
    return C;
}

Set Set::operator | (const Set& other) const
{
    Set C;
    for (int i = 0; i < N; ++i)
        C.S[i] = S[i] || other.S[i];
    return C;
}

Set Set::operator / (const Set& other) const
{
    Set C;
    for (int i = 0; i < N; ++i)
        C.S[i] = S[i] && !other.S[i];
    return C;
}

Set Set::operator ~ () const
{
    Set C;
    for (int i = 0; i < N; ++i)
        C.S[i] = !S[i];
    return C;
}

// ���������
int Set::power()
{
    int counter = 0;
    for (int i = 0; i < N; ++i)
        if (S[i])
            counter++;
    return counter;
}

void Set::rewrite(char str[])
{
    for (int i = 0; i < N; ++i)
        S[i] = false;
    for (int i = 0; i < strlen(str); i++)
        S[str[i]-'a'] = true;
    Show();
}

void Set::Show()
{
    char* result = new char[N+1];
    int i,j;

    for(i = 0, j = 0; i < N; ++i)
        if(S[i])
            result[j++] = i + 'a';

    result[j] = '\0';

    std::cout << name << " = {" << result << "}, |" << name << "| = " << this->power() << std::endl;

    delete [] result;
}

void Set::Show(char c)
{
    char* result = new char[N+1];
    int i,j;

    for(i = 0, j = 0; i < N; ++i)
        if(S[i])
            result[j++] = i + 'a';

    result[j] = '\0';

    std::cout << c << " = {" << result << "}, |" << name << "| = " << this->power() << std::endl;

    delete [] result;
}
*/
//****************************************Boolean*********************************


//*************************************List***************************************

class El{ //������� ���������(����)
    char e;
    El *next;
public:
    El(): e('!'), next(nullptr){ }
    El(char e, El *n = nullptr): e(e), next(n) { }
    ~El(){ if(this) delete next; } //����������
    friend class Set;
    friend std::ostream & operator << ( std::ostream & o, El & S); //���������� << ��� ������
};
std::ostream & operator << (std::ostream & o, El & S)
{
    for (El* p = &S; p; p = p->next) o << p->e;
    return o;
}


class Set
{
private:
    static int N; //�������� ����������
    static int cnt;       //���������� ����� ���������
    int n; //�������� ���������
    char S;    //���
    El *A; //������ ���������

public:
    //������������ � ����������
    Set(); //������ ���������
    Set(char); //��������� ������������ �������� (�������� ������������)
    Set(char, char[]); //����������� ��� ��������� ��������� � ����������
    Set(const Set &); //���������� �����������
    Set(Set &&); //����������� � ���������
    ~Set() { A->El::~El(); } //����������

    //��������
    Set & operator = (const Set&); //���������� ������������
    Set & operator = (Set &&); //������������ � ���������
    void swap(Set & other) { std::swap(S, other.S); std::swap(n, other.n); std::swap(A, other.A);}
    Set & operator |= (const Set&);
    Set & operator &= (const Set&);
    Set operator | (const Set&) const;
    Set operator & (const Set&) const;
    Set operator ~ () const;

    //���������
    void Show();
    void Show(char);
    int power() { return n; }
    void rewrite(char str[]); //������������ ���������
};

Set::Set() : n(0), S('A'+cnt++), A(nullptr) {}

Set::Set(char) : S('A'+cnt++), n(0)
{
    A = nullptr;
    for (int i = 0; i < N; i++)
        if (rand()%2) A = new El(i + 'a', A), ++n;
    std::cout << "-> Created " << S << "(" << n << ") = [" << *A << "] \n";
}

Set::Set(char c, char str[]) : S('A'+cnt++), n(0)
{
    A = nullptr;
    N = strlen(str);
    for (int i = 0; i < N; i++)
        A = new El(str[i], A), ++n;
    std::cout << "-> Created " << S << "(" << n << ") = [" << *A << "] \n";
}

Set::Set(const Set & B) : n(B.n), S('A'+cnt++), A(nullptr)
{
    for(El * p = B.A; p; p = p->next) A = new El(p->e, A);
}

Set::Set( Set && B) : n(B.n), S('A'+cnt++), A(B.A)
{
    B.A = nullptr;
}

Set & Set::operator &= (const Set& B)
{
    Set C;
    for (El * i = A; i; i = i->next)
    {
        for (El * j = B.A; j; j = j->next)
            if (i->e == j->e)
                C.A = new El(i->e, C.A), ++C.n;
    }
    swap(C);
    return *this;
}
Set Set::operator & (const Set& B) const
{
    Set C(*this);
    return C &= B;
}

Set & Set::operator |= (const Set & B)
{
    Set C(*this);
    for (El * i = B.A; i; i = i->next)
    {
        bool f = true;
        for (El * j = A; f && j; j = j->next)
            f = f && (i->e != j->e);
        if (f)
            C.A = new El(i->e, C.A), ++C.n;
    }
    swap(C);
    return *this;
}
Set Set::operator | (const Set& B) const
{
    Set C(*this);
    return C |= B;
}
Set Set::operator ~ ()const
{
    Set C;
    for (char c = 'a'; c <= 'z'; ++c)
    {
        bool f = true;
        for (El * j = A; j && f; j = j->next)
            if(c == j->e) f = false;
        if (f)
            C.A = new El(c, C.A) , ++C.n;
    }
    return C;
}

Set& Set::operator = (const Set & B)
{
    if (this != &B)
    {
        delete A;
        A = nullptr;
        n = 0;
        for(El * p = B.A; p; p = p->next)
            A = new El(p->e, A), ++n;
        S = 'A'+cnt++;
    }
    return *this;
}

Set& Set::operator = (Set && B)
{
    swap(B);
    delete B.A; B.A = nullptr;
    S = 'A'+cnt++;
    return *this;
}

void Set::rewrite(char str[])
{
    delete A;
    A = nullptr;
    n=0;
    N = strlen(str);
    for (int i = 0; i < N; i++)
        A = new El(str[i], A), ++n;
    std::cout << "-> Created " << S << "(" << n << ") = [" << *A << "] \n";
}

void Set::Show()
{
    std::cout<<'\n'<< S << "(" << n << ") = [ ";
    for(El * p = A; p; p = p->next) std:: cout << p->e << " ";
    std::cout << "]";
}

void Set::Show(char c)
{
    std::cout<<'\n'<< c << "(" << n << ") = [ ";
    for(El * p = A; p; p = p->next) std:: cout << p->e << " ";
    std::cout << "]";
}

//*************************************List***************************************

#endif // SET_H_INCLUDED
