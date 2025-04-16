#include <bits/stdc++.h>
#define MAX 1000000000
using namespace std;
vector<long long> v;
namespace fs = std::filesystem;
int getRandomNumber(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}
class Timer {
    chrono::time_point<chrono::system_clock> begin;
    chrono::time_point<chrono::system_clock> end;
    public:

    void startTimer() {
        begin = chrono::high_resolution_clock::now();;
    }
    void endTimer() {
        end = chrono::high_resolution_clock::now();
    }
    float getElapsedTime() {
        chrono::duration<float> diff = end - begin;
        return diff.count();
    }
};
class Sortings
{

    int *temp, *fr;
    Timer t;

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
        for(int i = n/ 2 - 1; i >= 0; i --)
            heapify(v, n, i);
        for(int i = n - 1; i > 0; i --)
            swap(v[0], v[i]), heapify(v, i,0);
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
        long long *p=v.data();
        n = n - st;
        p = p + st;
        n++;
        for(int i = n / 2 - 1; i >= 0; i --)
            heapify1(p, n, i);
        for(int i = n - 1; i > 0; i --)
            swap(p[0], p[i]), heapify1(p, i, 0);
    }
    void partitie(vector <long long> &v, int &st, int &dr)
    {
        int poz = st + getRandomNumber(0,dr-st);
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
        memset(fr, 0, sizeof(int)*b);
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
        for(long long i = 1; i <= maxx; i *= b)
            count_sort(v, i, b);
    }
    void Bit_count_sort(vector <long long> &v, long long div, long long b)
    {
        memset(fr, 0, sizeof(int)*(1<<b));
        int n = v.size();
        for(int i = 0; i < n; i ++)
            fr[(v[i] >> div) & ((1<<b)-1)] ++;
        for(int i = 1; i < (1<<b); i ++)
            fr[i] += fr[i - 1];

        for(int i = n - 1; i >= 0; i --)
            temp[fr[(v[i]>> div)& ((1<<b)-1)] - 1] = v[i], fr[(v[i] >> div) & ((1<<b)-1)] --;
        for(int i = 0; i < n; i ++)
            v[i] = temp[i];
    }
    void Bit_Radix_sort(vector <long long> &v, long long maxx, long long power)
    {
        for(long long i = 0; (1ll<<i) <=maxx; i+=power)
            Bit_count_sort(v, i, power);
    }
    void stlsort(vector <long long> &v) {
        sort(v.begin(), v.end());
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
    Sortings() {
        temp=new int[MAX];
        fr=new int[67000];
    }
    float stl_sort(vector <long long> v) {
        t.startTimer();

        stlsort(v);
        t.endTimer();
        return t.getElapsedTime();
    }
    float quick_sort(vector <long long> v)
    {
        t.startTimer();

        quick_sort(v, 0, v.size() - 1);
        t.endTimer();
        return t.getElapsedTime();
    }
    float merge_sort(vector <long long> v)
    {        t.startTimer();

        merge_sort(v, 0, v.size() - 1);

        t.endTimer();
        return t.getElapsedTime();
    }
    float heap_sort(vector <long long> v)
    {
        t.startTimer();
        Heap_sort(v);
        t.endTimer();
        return t.getElapsedTime();
    }

    float shell_sort(vector <long long> v)
    {        t.startTimer();

        Shell_sort(v);

        t.endTimer();
        return t.getElapsedTime();
    }
    float radix_sort(vector <long long> v, long long b)
    {
        t.startTimer();
        long long mx=0;
        for (long long i:v) {
            mx=std::max(mx,i);
        }
        Radix_sort(v, mx, b);

        t.endTimer();
        return t.getElapsedTime();
    }
    float intro_sort(vector <long long> v)
    {        t.startTimer();

        intro_sort(v, 2 * log2(v.size()), 0, v.size() - 1);

        t.endTimer();
        return t.getElapsedTime();
    }
    float bit_Radix_sort(vector <long long> v, long long power) {

        t.startTimer();
        long long mx=0;
        for (long long i:v) {
            mx=max(mx,i);
        }
        Bit_Radix_sort(v, mx, power);
        t.endTimer();
        return t.getElapsedTime();

    }
};
int main()
{

    Sortings a;
    std::string path = "sort/Tests";
    for (const auto & entry : fs::directory_iterator(path)) {
        int64_t n;
        ifstream input(entry.path());
        input>>n;
        std::vector<long long> v;
        int x;
        while (input>>x) {
            v.push_back(x);
        }
        cout<<"--------------------------\n";
        cout<<std::filesystem::path(entry).filename()<<"\n";
        cout<<"--------------------------\n";
        std::cout<<"shellSort:"<<a.shell_sort(v)<<'\n';
        std::cout<<"quickSort:"<<a.quick_sort(v)<<'\n';
        std::cout<<"heap_sort:"<<a.heap_sort(v)<<'\n';
        std::cout<<"merge_sort:"<<a.merge_sort(v)<<'\n';
        std::cout<<"bitRadixSort_B2^16:"<<a.bit_Radix_sort(v,16)<<'\n';
        std::cout<<"radixSort_B2^16:"<<a.radix_sort(v,1<<16)<<'\n';
        std::cout<<"radixSort_B10:"<<a.radix_sort(v,10)<<'\n';
        std::cout<<"introSort:"<<a.intro_sort(v)<<'\n';
        std::cout<<"stlSort:"<<a.stl_sort(v)<<'\n';
    }
    return 0;
}
