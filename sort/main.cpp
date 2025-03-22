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
    void Heap_sort(vector <long long> &v)
    {
        int n = v.size();
        for(int i = n / 2 - 1; i >= 0; i --)
            heapify(v, n, i);
        for(int i = n - 1; i > 0; i --)
            swap(v[0], v[i]), heapify(v, i, 0);
    }
    void quick_sort(vector <long long> &v, int st, int dr)
    {
        if(dr <= st)
            return;
        int poz = st + rand() % (dr - st + 1);
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
        quick_sort(v, l, st - 1);
        quick_sort(v, dr + 1, r);

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
};
int main()
{
    vector <long long> v = {5, 2, 3, 6, 1, 44, 4, 4, 4, 46, 4, 4, 2, 4, 7, 8, 1, 3, 4, 7, 3, 1};
    Sortings a;
    a.radix_sort(v, 46, 10);
   // for(int i = 0; i < v.size(); i ++)
     //   cout << v[i] <<" ";
    return 0;
}
