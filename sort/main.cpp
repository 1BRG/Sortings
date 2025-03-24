#include <bits/stdc++.h>
using namespace std;
const int n = 1e6;
vector<long long> v;
class Sortings
{
    /// merge_sort, shell_sort, heap_sort, quick_sort, radix_sort(maxx, b)
    int temp[10005] = {0}, fr[65536];
    void merge_sort(vector <long long> &v, int st, int dr)
    {
        if(st < dr)
        {
            int mij = st + (dr - st) / 2;
            merge_sort(v, st, mij);
            merge_sort(v, mij + 1, dr);
            int p1 = st, p2 = mij + 1, k = 0;
            while(p1 <= mij && p2 <= dr)
            {
                if(v[p1] <= v[p2])
                    temp[++k] = v[p1], p1 ++;
                else temp[++k] = v[p2], p2 ++;
            }
            while(p1 <= mij)
                temp[++k] = v[p1], p1 ++;
            while(p2 <= dr)
                temp[++k] = v[p2], p2 ++;
            for(int i = st; i <= dr; i ++)
                v[i] = temp[i - st + 1];
        }
    }
    void heapify(vector <long long> &v, int n, int i)
    {
        int st = 2 * i + 1, dr = 2 * i + 2, nod = i;
        if(st < n && v[st] > v[nod])
            nod = st;
        if(dr < n && v[dr] > v[nod])
            nod = dr;
        if(nod != i)
            swap(v[i], v[nod]), heapify(v, n, nod);
    }
    void Heap_sort(vector <long long> &v, int n = -1, int st = 0)
    {

        if(n == -1)
        n = v.size();


        for(int i = n/ 2 - 1; i >= st; i --)
            heapify(v, n, i);
        for(int i = n - 1; i > st; i --)
            swap(v[st], v[i]), heapify(v, i, st);
    }
    void heapify1(long long v[], int n, int i)
    {
        int st = 2 * i + 1, dr = 2 * i + 2, nod = i;
        if(st < n && v[st] > v[nod])
            nod = st;
        if(dr < n && v[dr] > v[nod])
            nod = dr;
        if(nod != i)
            swap(v[i], v[nod]), heapify1(v, n, nod);
    }
     void Heap_sort2(vector <long long> &v, int n = -1, int st = 0)
    {
        long long *p=(long long*)v.data();
        n = n - st;
        p = p + st;
        if(n == -1)
        n = v.size();


        for(int i = n / 2 - 1; i >= 0; i --)
            heapify1(p, n, i);
        for(int i = n - 1; i > 0; i --)
            swap(p[0], p[i]), heapify1(p, i, 0);
    }
    void partitie(vector <long long> &v, int &st, int &dr)
    {
        int poz = st + rand() % (dr - st + 1);
        //int poz = dr;
        int pivot = v[poz], i = st + 1, l = st, r = dr;
        swap(v[st], v[poz]);
        while(i <= dr)
        {
            if(v[i] < pivot)
            {
                swap(v[i], v[st]);
                st ++;
                i ++;
            }
            else if(v[i] > pivot)
                swap(v[i], v[dr]), dr --;
            else i ++;
        }
    }
    void quick_sort(vector <long long> &v, int st, int dr)
    {
        int l = st, r = dr;
        if(dr <= st)
            return;
        partitie(v, st, dr);
        quick_sort(v, l, st - 1);
        quick_sort(v, dr + 1, r);

    }
    void insertion_sort(vector <long long> &v, int st, int dr)
    {
        for(int i = st + 1; i <= dr; i ++)
        {
            long long val = v[i];
            int j = i;
            while(j >= 1 && v[j - 1] > val)
                v[j] = v[j - 1], j --;
            v[j] = val;
        }
    }
    void Shell_sort(vector <long long> &v)
    {
        int n = v.size();
        for(int gap = n / 2; gap >= 1; gap /= 2)
        {
            for(int i = gap; i < n; i ++)
            {
                long long val = v[i];
                int j = i;
                while(j >= gap && v[j - gap] > val)
                {
                    v[j] = v[j - gap];
                    j -= gap;
                }
                v[j] = val;
            }
        }
    }
    void count_sort(vector <long long> &v, long long div, long long b)
    {
        if(b % 10 == 0)
            {
                for(int i = 0; i <= 10; i ++)
                    fr[i] = 0;
            }
        else memset(fr, 0, sizeof(fr));
        int n = v.size();
        for(int i = 0; i < n; i ++)
                fr[v[i] / div % b] ++;
        for(int i = 1; i <= b; i ++)
            fr[i] += fr[i - 1];
        for(int i = n - 1; i >= 0; i --)
            temp[fr[v[i] / div % b] - 1] = v[i], fr[v[i] / div % b] --;
        for(int i = 0; i < n; i ++)
            v[i] = temp[i];
    }
    void Radix_sort(vector <long long> &v, long long maxx, long long b)
    {
        for(int i = 1; i <= maxx; i *= b)
            count_sort(v, i, b);
    }
    bool test_sort(vector <long long> &v)
    {
        for(int i = 1; i < v.size(); i++)
            if(v[i] < v[i - 1])
            return false;
        return 1;
    }
    void intro_sort(vector <long long> &v, int depth, int st, int dr)
    {
        if(dr <= st)
            return;
        if(dr - st < 16)
        {
            insertion_sort(v, st, dr);
            return;
        }
        if(depth == 0)
        {
            Heap_sort2(v, dr, st);
            return;
        }
        int l = st, r = dr;
        partitie(v, st, dr);
        intro_sort(v, depth - 1, l, st - 1);
        intro_sort(v, depth - 1, dr + 1, r);
    }

public:
    void quick_sort(vector <long long> v)
    {
        quick_sort(v, 0, v.size() - 1);
    }
    void merge_sort(vector <long long> v)
    {
        merge_sort(v, 0, v.size() - 1);
    }
    void heap_sort(vector <long long> v)
    {
        Heap_sort(v);
    }
    void shell_sort(vector <long long> v)
    {
        Shell_sort(v);
    }
    void radix_sort(vector <long long> v, long long maxx, long long b)
    {
        Radix_sort(v, maxx, b);
    }
    void intro_sort(vector <long long> v)
    {
        intro_sort(v, 2 * log2(v.size()), 0, v.size() - 1);
        for(int i = 0; i < v.size(); i ++)
                cout << v[i] << " ";
            cout << "\n";
    }
};
int main()
{
    vector <long long> v = {100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    Sortings a;
    a.intro_sort(v);
   // for(int i = 0; i < v.size(); i ++)
     //   cout << v[i] <<" ";
    return 0;
}
