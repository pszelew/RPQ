#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdlib.h> 
#include <string>
#include <list>
#include <queue> 


using namespace std;

struct zadanie {
    int id;
    int R;
    int P;
    int Q;
};


struct CompareR {
    bool operator()(zadanie const& p1, zadanie const& p2)
    {
        // return "true" if "p1" is ordered  
        // before "p2", for example: 
        return p1.R > p2.R;
    }
};

struct CompareQ {
    bool operator()(zadanie const& p1, zadanie const& p2)
    {
        // return "true" if "p1" is ordered  
        // before "p2", for example: 
        return p1.Q < p2.Q;
    }
};




int sprawdz_czas(int n, zadanie tab[])
{
    int m = 0;
    int c = 0;
    int i = 0;

    for (int i = 0; i < n; i++)
    {
        m = max(m, tab[i].R) + tab[i].P;
        c = max(m + tab[i].Q, c);
    }
    return c;
}

int comparer(const void* a, const void* b)
{
   
     if ((*(zadanie*)a).R < (*(zadanie*)b).R) return -1;
     if ((*(zadanie*)a).R == (*(zadanie*)b).R) return 0;
     if ((*(zadanie*)a).R > (*(zadanie*)b).R) return 1;
}
int compareq(const void* a, const void* b)
{

    if ((*(zadanie*)a).Q < (*(zadanie*)b).Q) return -1;
    if ((*(zadanie*)a).Q == (*(zadanie*)b).Q) return 0;
    if ((*(zadanie*)a).Q > (*(zadanie*)b).Q) return 1;
}



zadanie* schrage(int n, zadanie tab[])
{
    int t = 0;
    int k = 0;
    zadanie e;
    int pe = 0;
    zadanie* dynamiczna = new zadanie[n];
    priority_queue<zadanie, vector<zadanie>, CompareR> N;
    priority_queue<zadanie, vector<zadanie>, CompareQ> G;
    for (int i = 0; i < n; i++)
    {
        N.push(tab[i]);   
    }

    while (!G.empty() || !N.empty())
    {
        while (!N.empty() && N.top().R <= t)
        {
            e = N.top();
            pe = N.top().P;
            G.push(N.top());
            N.pop();
        }

        if (G.empty())
        {
            t = N.top().R;
        }
        else
        {
            e = G.top();
            pe = G.top().P;
            G.pop();
            dynamiczna[k] = e;
            k = k + 1;
            t = t + pe;
        }
    }
 

    return dynamiczna;
}
void sort_r(int n, zadanie tab[])
{
    qsort(tab, n, sizeof(zadanie), comparer);
}


void sort_q(int n, zadanie tab[])
{
    qsort(tab, n, sizeof(zadanie), compareq);
}



zadanie* perfect(int n, zadanie tab[])
{
    int i,j,k;
    k = 2;
    zadanie* tablica = new zadanie[n];
    zadanie* tablica_2 = new zadanie[n];
    for (int h = 0; h < n; h++)
    {
        tablica[h] = tab[h];
    }
    
    // sort_q(n, tablica);

    j= tablica[n - k].P;
    while (j < tablica[n - 1].Q) // najwiekszy element
    {
        j += tablica[n - (++k)].P;
    }

   
    for (i=0; i < n - k; i++)
    {
        tablica_2[i] = tablica[i];
    }
    tablica_2[i++] = tablica[n-1];

    for (i; i < n; i++)
    {
        tablica_2[i] = tablica[i-1];
    }
    

    return tablica_2;
}


int compare_intelligent(const void* a, const void* b)
{
    float x, y;
    float waga_1, waga_2;
    waga_1 = 0.00005;
    if ((*(zadanie*)a).Q != 0)
    {
        x = float((*(zadanie*)a).R) / float((*(zadanie*)a).Q) + waga_1* float((*(zadanie*)a).R);
    }
    else
        x = INT_MAX;

    if ((*(zadanie*)b).Q != 0)
    {
        y = float((*(zadanie*)b).R) / float((*(zadanie*)b).Q) + waga_1 * float((*(zadanie*)b).R);
    }
    else
        y = INT_MAX;
        
    if (x < y) return -1;
    if (x == y) return 0;
    if (x > y) return 1;
}  
    



void sort_intelligent(int n, zadanie tab[])
{
    qsort(tab, n, sizeof(zadanie), compare_intelligent);
}



zadanie* combine(int n, zadanie tab[])
{
    zadanie* dynamiczna_1 = new zadanie[n];
    for (int i = 0; i < n; i++)
    {
        dynamiczna_1[i] = tab[i];
    }
    zadanie * dynamiczna_2 = schrage(n, tab);
    zadanie* dynamiczna_3 = perfect(n, tab);
    int schr = sprawdz_czas(n, dynamiczna_2);
    int perfec = sprawdz_czas(n, dynamiczna_3);
    sort_intelligent(n, dynamiczna_1);
    int sort = sprawdz_czas(n, dynamiczna_1);

    if (schr < sort)
        if (schr < perfec)
            return dynamiczna_2;
        else
            return dynamiczna_3;
    if (schr > sort)
        if(sort< perfec)
            return dynamiczna_1;
        else
            return dynamiczna_3;
}


int main()
{
    int n;
    int temp;
    int pi[99];
    zadanie tab[99];
    zadanie* dynamiczna;

    int total = 0;
    for(int g=0;g<4;g++)
    {
    ifstream data("data.txt");
    string s = "";
    string nazwa = "data." + to_string(g+1);
    while (s != nazwa)
    {
        data >> s;
    }
    data >> n;
    for (int i = 0; i < n; i++)
    {
        tab[i].id = i + 1;
        data >> tab[i].R;
        data >> tab[i].P;
        data >> tab[i].Q;
    }

    //////////////////////////////////////////////////////////////

    //sort_r(n, tab);
    //sort_intelligent(n, tab);
    //dynamiczna = schrage(n, tab);
    dynamiczna = combine(n, tab);

    


    //////////////////////////////////////////////////////////////
    /*
    for (int i = 0; i < n; i++)
    {
        cout << tab[i].R << " ";
        cout << tab[i].P << " ";
        cout << tab[i].Q << " ";
        cout << endl;
    }
     */
    cout << "czas: ";
    temp = sprawdz_czas(n, dynamiczna);
    cout << temp<<endl;
    total += temp;
    }
    cout << "Calkowity czas:" << total << endl;
}
