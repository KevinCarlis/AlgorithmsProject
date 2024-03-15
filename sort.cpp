#include <iostream>
#include <sstream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <stdlib.h>

using namespace std;

void printArr (int* arr, size_t size)
{
  for (size_t i = 0; i < size - 1; i++)
  {
    cout << arr[i] << ", ";
  }
  cout << arr[size - 1] << endl;
}


void SelectionSort(int* arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        int min = i;
        for (size_t j = i + 1; j < n; j++)
        {
            if (arr[j] < arr[min])
            {
                min = j;
            }
        }
        std::swap(arr[i],arr[min]);
    }
}

void Merge (int* arr, size_t left, size_t middle, size_t right)
{
    size_t i, j, k, n1, n2;
    n1 = middle - left + 1;
    n2 = right - middle;

    int L[n1], R[n2];
    for (i = 0; i < n1; i++)
    {
        L[i] = arr[left + i];
    }
    for (j = 0; j < n2; j++)
    {
        R[j] = arr[middle + 1 + j];
    }

    i = 0;
    j = 0;
    for (k = left; k <= right; k++)
    {
        if ((L[i] <= R[j] && i < n1) || j >= n2 )
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
    }
}

void MergeSort (int* arr, size_t left, size_t right)
{
    if (left < right)
    {
        size_t middle = (right + left)/2;
        MergeSort(arr, left, middle);
        MergeSort(arr, middle + 1, right);
        Merge(arr, left, middle, right);
    }
}

class Heap 
{
    Heap()
    {
        Arr = new int[1000];
        N = 0;
    }
    
    Heap(int a[], int n)
    {
        Arr = new int[1000];
        for(size_t i = 0; i < n; i++)
        {
            Arr[i] = a[i];
        }
        N = n;
    }
    
    ~Heap()
    {
        delete[] Arr;
    }
    
    void printArray()
    {
        for (int i = 0; i < N; i++)
        {
            cout << Arr[i];
            if (i < N - 1)
                cout << ' ';
        }
        cout << endl;
    }
    
    void max_heapify(int i) //Maintains the max heap property
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int largestNode = i;
        if (left < N && Arr[left] > Arr[largestNode])
            largestNode = left;
        if (right < N && Arr[right] > Arr[largestNode])
            largestNode = right;
        if (largestNode != i)
        {
            swap(Arr[i],Arr[largestNode]);
            max_heapify(largestNode);
        }
    }
    void ascendingHeapSort() //Prints the array in ascending order
    {
        int origN = N;
        buildMaxHeap();
        for (int i = N - 1; i >= 0; i--)
        {
            swap(Arr[i], Arr[0]);
            N--;
            max_heapify(0);
        }
        N = origN;
    }
    void buildMaxHeap() //Heapifies entire list
    {
        for (int i = (N / 2) - 1; i >= 0; i--)
        {
            max_heapify(i);
        }
    }
    
    void min_heapify(int i) //Maintains min heap property
    {
        int left = 2 * i + 1;
        int right = 2 * i + 2;
        int smallestNode = i;
    
        if (left < N && Arr[left] < Arr[smallestNode])
            smallestNode = left;
        if (right < N && Arr[right] < Arr[smallestNode])
            smallestNode = right;
        if (smallestNode != i)
        {
            swap(Arr[i], Arr[smallestNode]);
            min_heapify(smallestNode);
        }
    }
    void descendingHeapSort() //Prints the array in descending order
    {
        int origN = N;
        buildMinHeap();
        for (int i = N - 1; i >= 0; i--)
        {
            swap(Arr[i], Arr[0]);
            N--;
            min_heapify(0);
        }
        N = origN;
    }
    void buildMinHeap() //Heapifies entire list
    {
        for (int i = (N/2) - 1; i >= 0; i--)
        {
            min_heapify(i);
        }
    }
};


void countSort(int* arr, size_t n)
{
    if (n < 1)
        return;
    int max = arr[0];
    for (size_t i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    int auxArr[max + 1] = { 0 };
    for (size_t i = 0; i < n; i++)
    {
        auxArr[arr[i]] += 1;
    }
    for (size_t i = 1; i < max + 1; i++)
    {
        auxArr[i] = auxArr[i] + auxArr[i - 1];
    }
    int ret[n];
    int x;
    for (int i = n - 1; i >= 0; i--)
    {
        x = arr[i];
        auxArr[x] -= 1;
        ret[auxArr[x]] = arr[i];
    }
    for (size_t i = 0; i < n; i++)
    {
        arr[i] = ret[i];
    }
}

void radixSort(int* arr, size_t n)
{
  if (n < 1)
        return;
    int max = arr[0];
    for (size_t i = 1; i < n; i++)
    {
        if (arr[i] > max)
        {
            max = arr[i];
        }
    }
    int d = 0;
    do {
      max = max / 10;
      d++;
    }
    while (max != 0);
    
    int dx = 1;
    for (int i = 0; i < d; i++)
    {
      int auxArr[10] = { 0 };
      for (int j = 0; j < n; j++)
      {
        auxArr[(arr[j] / dx) % 10] += 1;
      }
      for (int j = 1; j < 10; j++)
      {
        auxArr[j] += auxArr[j - 1];
      }
      int ret[n];
      int x;
      for (int i = n - 1; i >= 0; i--)
      {
          x = arr[i];
          x = (x / dx) % 10;
          auxArr[x] -= 1;
          ret[auxArr[x]] = arr[i];
      }
      for (size_t i = 0; i < n; i++)
      {
          arr[i] = ret[i];
      }
      dx *= 10;
    }
}



enum Pivot { First, Random, Median };

int partition(int* arr, int low, int high, Pivot p)
{
    int pivot = arr[low];
    if (p == Random)
    {
        pivot = arr[(rand() % (high - low)) + low];
    }
    else if (p == Median)
    {
        int mid = (high + low) / 2;
        if  ((arr[high] > pivot) != (arr[high] > arr[mid]))
        {
            pivot = arr[high];
        }
        else if ((arr[mid] < pivot) != (arr[mid] < arr[high]))
        {
            pivot = arr[mid];
        }
    }
    int i = low - 1;
    int j = high + 1;
    while (true)
    {
        do
        {
            j--;
        } while (j > low && arr[j] > pivot);
        do
        {
            i++;
        } while (i < high && arr[i] < pivot);
        if (i < j)
            swap(arr[i], arr[j]);
        else
            return j;
    }
}

void quickSort(int* arr, int l, int r, Pivot p)
{
    if (l < r)
    {
        int q = partition(arr, l, r, p);
        quickSort(arr, l, q, p);
        quickSort(arr, q + 1, r, p);
    }
}


char* getCmdOption(char ** begin, char ** end, const std::string & option)
{
    char ** itr = std::find(begin, end, option);
    if (itr != end && ++itr != end)
    {
      return *itr;
    }
    return 0;
}
bool cmdOptionExists(char** begin, char** end, const std::string& option)
{
    return std::find(begin, end, option) != end;
}


int main(int argc, char **argv)
{
    std::vector<int> v;
    int *arr;
    size_t size;
    int max = 0;
    bool print = cmdOptionExists(argv, argv+argc, "-print") ||
                 cmdOptionExists(argv, argv+argc, "-p");
                 
    bool insert = cmdOptionExists(argv, argv+argc, "-insert") ||
                 cmdOptionExists(argv, argv+argc, "-i");
    bool select = cmdOptionExists(argv, argv+argc, "-select") ||
                  cmdOptionExists(argv, argv+argc, "-s")
    bool bubble = cmdOptionExists(argv, argv+argc, "-bubble") ||
                 cmdOptionExists(argv, argv+argc, "-b");
    bool merge = cmdOptionExists(argv, argv+argc, "-merge") || 
                 cmdOptionExists(argv, argv+argc, "-m")
    bool heap = cmdOptionExists(argv, argv+argc, "-heap") ||
                 cmdOptionExists(argv, argv+argc, "-h");
    bool count = cmdOptionExists(argv, argv+argc, "-count") ||
                 cmdOptionExists(argv, argv+argc, "-c");
    bool radix = cmdOptionExists(argv, argv+argc, "-radix") ||
                 cmdOptionExists(argv, argv+argc, "-r");
    
    bool quick = cmdOptionExists(argv, argv+argc, "-quick") ||
                 cmdOptionExists(argv, argv+argc, "-q");
    bool first = cmdOptionExists(argv, argv+argc, "-first");
    bool rand = cmdOptionExists(argv, argv+argc, "-random") ||
                cmdOptionExists(argv, argv+argc, "-rand");
    bool median = cmdOptionExists(argv, argv+argc, "-median") ||
                  cmdOptionExists(argv, argv+argc, "-med");
    if (quick && !first && !rand && !median)
    {
        std::cout << "quicksort: missing pivot operand\n";
        return 0;
    }
    if (cmdOptionExists(argv, argv+argc, "-size"))
    {
        char *s = getCmdOption(argv, argv+argc, "-size");
        if (s == 0)
        {
            size = 10000;
        }
        else
        {
            size = atoi(s);
        }
        if (cmdOptionExists(argv, argv+argc, "-max"))
        {
            s = getCmdOption(argv, argv+argc, "-max");
            if (s != 0)
            {
                max = atoi(s) + 1;
            }
        }
    }
    if (cmdOptionExists(argv, argv+argc, "-sorted"))
    {
        arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            if (max > 1)
            {
                arr[i] = (i + 1) % max;
            }
            else
            {
                arr[i] = i + 1;
            }
        }
    }
    else if (cmdOptionExists(argv, argv+argc, "-half"))
    {
        arr = new int[size];
        int half = size/2;
        for (int i = 0; i < half; i++)
        {
            arr[i] = i;
        }
        for (int i = half; i < size; i++)
        {
            arr[i] = size - (i - half);
        }
    }
    else if (cmdOptionExists(argv, argv+argc, "-reverse"))
    {
        arr = new int[size];
        for (int i = 0; i < size; i++)
        {
            if (max > 1)
            {
                arr[i] = (size - i) % max;
            }
            else
            {
                arr[i] = size - i;
            }
        }
    }
    else
    {
        std::cout << "Custom Input:\n";
        string s;
        getline(cin, s);
        stringstream inArr(s);
        vector<int> a;
        int x;
        while(inArr >> x)
        {
            v.push_back(x);
        }
        size = v.size();
        arr = &v[0];
    }
    
    if (insert)
    {
      if (print)
            printArr(arr, size);
        auto start = std::chrono::high_resolution_clock::now();
        // TODO
        //insertSort(arr, 0, size - 1, p);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << duration.count() << endl;
        if (print)
            printArr(arr, size);
    }
    if (select)
    {
      if (print)
            printArr(arr, size);
        auto start = std::chrono::high_resolution_clock::now();
        SelectionSort(arr, size - 1);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << duration.count() << endl;
        if (print)
            printArr(arr, size);
    }
    if (bubble)
    {
      if (print)
            printArr(arr, size);
        auto start = std::chrono::high_resolution_clock::now();
        // TODO
        //bubbleSort(arr, 0, size - 1, p);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << duration.count() << endl;
        if (print)
            printArr(arr, size);
    }
    if (merge)
    {
      if (print)
            printArr(arr, size);
        auto start = std::chrono::high_resolution_clock::now();
        MergeSort(arr, 0, size - 1);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << duration.count() << endl;
        if (print)
            printArr(arr, size);
    }
    if (heap)
    {
      if (print)
            printArr(arr, size);
        Heap h(arr, size);
        auto start = std::chrono::high_resolution_clock::now();
        h.buildMaxHeap();
        h.ascendingHeapSort();
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << duration.count() << endl;
        if (print)
            printArr(arr, size);
    }
    if (count)
    {
      if (print)
            printArr(arr, size);
        auto start = std::chrono::high_resolution_clock::now();
        countSort(arr, size);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << duration.count() << endl;
        if (print)
            printArr(arr, size);
    }
    if (radix)
    {
      if (print)
            printArr(arr, size);
        auto start = std::chrono::high_resolution_clock::now();
        radixSort(arr, size);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << duration.count() << endl;
        if (print)
            printArr(arr, size);
    }
    if (quick) 
    {
        Pivot p = First;
        if (rand)
          p = Random;
        else if (median)
          p = Median;
        if (print)
            printArr(arr, size);
        auto start = std::chrono::high_resolution_clock::now();
        quickSort(arr, 0, size - 1, p);
        auto stop = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop-start);
        std::cout << duration.count() << endl;
        if (print)
            printArr(arr, size);
    }
    return 0;
}
