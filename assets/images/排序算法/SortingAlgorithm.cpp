#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>
#include <thread>
#include <mutex>
#include <barrier>
#include <random>
#include <chrono>

using namespace std;

// ѡ������(Selection Sort)
void SelectionSort(vector<int>& nums)
{
    cout << "Selection Sort\n";
    for (int i = 0; i < nums.size(); i++)
    {
        int minPos = i;
        for (int j = i + 1; j < nums.size(); j++)
        {
            if (nums[j] < nums[minPos])
            {
                minPos = j;
            }
        }

        swap(nums[i], nums[minPos]);
    }
}

// ������(Heap Sort)
void HeapSort(vector<int>& nums)
{
    cout << "Heap Sort\n";
    auto HeapAdjust = [&](int start, int end){ 
        int fatherNode = start;
        int sonNode = 0;

        for (sonNode = start * 2 + 1; sonNode <= end; sonNode = sonNode * 2 + 1)
        {
            if (sonNode + 1 < end && nums[sonNode] < nums[sonNode + 1])
            {
                sonNode++;
            }

            if (nums[sonNode] < nums[fatherNode])
            {
                return;
            }
            else
            {
                swap(nums[fatherNode], nums[sonNode]);
                fatherNode = sonNode;
            }
        }
        };
    
    for (int sonNode = nums.size() / 2 - 1; sonNode >= 0 ; sonNode--)
    {
        HeapAdjust(sonNode, nums.size() - 1);
    }

    for (int i = nums.size() - 1; i >= 0; i--)
    {
        swap(nums[0], nums[i]);
        HeapAdjust(0, i - 1);
    }
}

// ��������-ֱ�Ӳ���(Insertion Sort)
void InsertionSort(vector<int>& nums)
{
    cout << "Insertion Sort\n";
    for (int i = 0; i < nums.size(); i++)
    {
        int tmp = i;

        for (int j = i - 1; j >= 0 && nums[j] > nums[tmp]; j--)
        {
            swap(nums[j], nums[tmp]);
            tmp = j;
        }
    }
}

// ��������-ϣ������(Shell Sort)
void ShellSort(vector<int>& nums)
{
    cout << "Shell Sort\n";
    // Sedgewick����.
    auto GetGaps = [&](int n) {
        vector<int> ret;
        int idx = 0;
        while (true)
        {
            // 9*4^i-9*2^i+1
            int tmp = 9 * ((1 << (2 * idx)) - (1 << idx)) + 1;
            if (tmp <= n)
            {
                ret.push_back(tmp);
            }
            else
            {
                break;
            }
            // 4^(i+2)-3*2^(i + 2)+1
            tmp = (1 << (2 * idx + 4)) - 3 * (1 << (idx + 2)) + 1;
            if (tmp <= n)
            {
                ret.push_back(tmp);
            }
            else
            {
                break;
            }

            idx++;
        }
        
        return ret;
        };

    vector<int> gaps = GetGaps(nums.size());
    reverse(gaps.begin(), gaps.end());

    for (int gapIdx = 0; gapIdx < gaps.size() && gaps[gapIdx] > 0; gapIdx++)
    {
        for (int i = gaps[gapIdx]; i < nums.size(); i++)
        {
            int tmp = nums[i];
            int pos = i;

            while (pos - gaps[gapIdx] >= 0 && tmp < nums[pos - gaps[gapIdx]])
            {
                pos -= gaps[gapIdx];
            }

            for (int j = i - gaps[gapIdx]; j >= pos; j -= gaps[gapIdx])
            {
                nums[j + gaps[gapIdx]] = nums[j];
            }

            nums[pos] = tmp;
        }
    }
}

// ð������(Bubble Sort)
void BubbleSort(vector<int>& nums)
{
    cout << "Bubble Sort\n";
    for (int i = 1; i < nums.size(); i++)
    {
        for (int j = 0; j < nums.size() - i; j++)
        {
            if (nums[j] > nums[j + 1])
            {
                swap(nums[j], nums[j + 1]);
            }
        }
    }
}

// ��������
void LomutoQuickSort(vector<int>& nums, int l, int r)
{
    // Lomuto partition.
    auto LomutoPartition = [&](int l, int r)->int {
        int pivot = nums[r];
        int i = l;
        for (int j = l; j < r; ++j) {
            if (nums[j] < pivot) {
                swap(nums[i], nums[j]);
                ++i;
            }
        }
        swap(nums[i], nums[r]);
        return i;
        };

    // Quick sort.
    if (l < r)
    {
        int p = LomutoPartition(l, r);
        LomutoQuickSort(nums, l, p - 1);
        LomutoQuickSort(nums, p + 1, r);
    }
}
void HoareQuickSort(vector<int>& nums, int l, int r)
{
    // Hoare partition.
    auto HoarePartition = [&](int l, int r)->int {
        int pivot = nums[(l + r) / 2];
        int i = l, j = r;
        while (true) {
            while (nums[i] < pivot) i++;
            while (nums[j] > pivot) j--;
            if (i >= j) return j;
            swap(nums[i++], nums[j--]);
        }
        };

    // Quick sort.
    if (l < r)
    {
        int p = HoarePartition(l, r);
        HoareQuickSort(nums, l, p);
        HoareQuickSort(nums, p + 1, r);
    }
}
void ThreeWayQuickSort(vector<int>& nums, int l, int r)
{
    auto ThreeWayPartition = [&](int l, int r)->pair<int, int> {
        int pivot = nums[l];
        int lt = l, i = l, gt = r;

        while (i <= gt) {
            if (nums[i] < pivot) {
                swap(nums[lt], nums[i]);
                ++lt;
                ++i;
            }
            else if (nums[i] > pivot) {
                swap(nums[i], nums[gt]);
                --gt;
            }
            else {
                ++i;
            }
        }

        return { lt, gt };
        };
    
    if (l < r)
    {
        int lt = 0;
        int gt = 0;
        tie(lt, gt) = ThreeWayPartition(l, r);
        ThreeWayQuickSort(nums, l, lt - 1);
        ThreeWayQuickSort(nums, gt + 1, r);
    }
}
void QuickSort(vector<int>& nums)
{
    cout << "Quick Sort\n";
    // Quick sort.
    //LomutoQuickSort(nums, 0, nums.size() - 1);
    HoareQuickSort(nums, 0, nums.size() - 1);
    //ThreeWayQuickSort(nums, 0, nums.size() - 1);
}

// ��������(Counting Sort)
void CountingSort(vector<int>& nums)
{
    cout << "Counting Sort\n";

    // Find max element.
    int max_val = *max_element(nums.begin(), nums.end());
    vector<int> count(max_val + 1, 0);

    // Counting.
    for (int num : nums)
    {
        count[num]++;
    }

    // Accumulate counting.
    for (int i = 1; i <= max_val; ++i)
    {
        count[i] += count[i - 1];
    }

    // Fill.
    vector<int> output(nums.size());
    for (int i = nums.size() - 1; i >= 0; --i)
    {
        int num = nums[i];
        output[count[num] - 1] = num;
        count[num]--;
    }

    nums = output;
}

// ��������(Radix Sort)
void RadixSort(vector<int>& nums)
{
    cout << "Radix Sort\n";

    auto GetDigit = [&](int n, int d)->int {
        int divisor = 1;
        for (int i = 0; i < d; ++i) {
            divisor *= 10;
        }
        return (n / divisor) % 10;
        };

    // Get max element.
    int maxNum = *max_element(nums.begin(), nums.end());
    int maxDigits = 0;
    while (maxNum > 0)
    {
        maxNum /= 10;
        maxDigits++;
    }

    // From lowest digit to highest digit.
    for (int d = 0; d < maxDigits; ++d)
    {
        // Sort with radix.
        vector<int> count(10, 0);

        // Count.
        for (int num : nums)
        {
            int digit = GetDigit(num, d);
            count[digit]++;
        }

        // Accumulate.
        for (int i = 1; i < 10; ++i)
        {
            count[i] += count[i - 1];
        }

        // Fill.
        vector<int> output(nums.size());
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            int digit = GetDigit(nums[i], d);
            output[count[digit] - 1] = nums[i];
            count[digit]--;
        }

        // Update.
        nums = output;
    }
}

// Ͱ����(Bucket Sort)
void BucketSort(vector<int>& nums)
{
    cout << "Bucket Sort\n";

    // Initial buckets.
    const int bucketNum = sqrt(nums.size()) + 1;
    vector<vector<int>> buckets(bucketNum);
    int maxNum = *max_element(nums.begin(), nums.end());
    int minNum = *min_element(nums.begin(), nums.end());
    int range = maxNum - minNum + 1;

    // Put numbers into bucket.
    for (int num : nums)
    {
        // Calculate index.
        int bucket_idx = float(num - minNum) / range * bucketNum;
        buckets[bucket_idx].push_back(num);
    }

    // Sort number in each bucket.
    for (auto& bucket : buckets)
    {
        sort(bucket.begin(), bucket.end());
    }

    // Merge.
    int idx = 0;
    for (const auto& bucket : buckets)
    {
        for (float num : bucket)
        {
            nums[idx++] = num;
        }
    }
}

// �鲢����(Merge Sort)
void MergeSortRecu(vector<int>& nums, int l, int r)
{
    auto Merge = [&](int l, int mid, int r) {
        vector<int> temp(r - l + 1);

        int i = l;
        int j = mid + 1;
        int k = 0;

        // Merge.
        while (i <= mid && j <= r)
        {
            if (nums[i] <= nums[j])
            {
                temp[k++] = nums[i++];
            }
            else
            {
                temp[k++] = nums[j++];
            }
        }

        while (i <= mid)
        {
            temp[k++] = nums[i++];
        }
        while (j <= r)
        {
            temp[k++] = nums[j++];
        }

        for (int p = 0; p < k; p++)
        {
            nums[l + p] = temp[p];
        }
        };

    if (l >= r)
    {
        return;
    }

    int mid = (l + r) / 2;
    MergeSortRecu(nums, l, mid);
    MergeSortRecu(nums, mid + 1, r);
    Merge(l, mid, r);
}

void MergeSort(vector<int>& nums)
{
    cout << "Merge Sort\n";

    MergeSortRecu(nums, 0, nums.size() - 1);
}

// ��ż����(Odd - Even Sort)
void OddEvenSort(vector<int>& nums)
{
    cout << "Odd-Even Sort\n";

    bool isSorted = false;
    int n = nums.size();

    while (!isSorted)
    {
        isSorted = true;

        // Odd Stage��Compare (1,2), (3,4), ...��
        for (int i = 1; i < n - 1; i += 2)
        {
            if (nums[i] > nums[i + 1])
            {
                std::swap(nums[i], nums[i + 1]);
                isSorted = false;
            }
        }

        // Even Stage��Compare (0,1), (2,3), ...��
        for (int i = 0; i < n - 1; i += 2)
        {
            if (nums[i] > nums[i + 1])
            {
                std::swap(nums[i], nums[i + 1]);
                isSorted = false;
            }
        }
    }
}

void ParallelOddEvenSort(vector<int>& nums)
{
    const int n = nums.size();
    bool isSorted = false;
    int phase = 0; // 0: even, 1: odd

    // Barrier��as C++20 std::barrier��
    int threadCount = thread::hardware_concurrency();
    threadCount = max(1, min(threadCount, n / 10));
    cout << "Count of threads:" << threadCount << endl;

    mutex mtx;
    condition_variable cv;
    int waitingThreads = 0;
    barrier br(threadCount);

    auto worker = [&](int start, int end) {
        while (!isSorted)
        {

            bool localSorted = true;

            // Odd or Even phase.
            for (int i = start + phase; i < end; i += 2)
            {
                if (i + 1 < n && nums[i] > nums[i + 1])
                {
                    swap(nums[i], nums[i + 1]);
                    localSorted = false;
                }
            }



            // Wait all threads completed.
            {
                unique_lock<mutex> lock(mtx);
                ++waitingThreads;

                if (waitingThreads == 1) {
                    isSorted = true;
                }
                else if (waitingThreads == threadCount)
                {
                    phase ^= 1;
                    waitingThreads = 0;
                }

                isSorted &= localSorted;
            }

            br.arrive_and_wait();
        }
        };

    // Create threads.
    vector<thread> threads;
    const int chunkSize = (n + threadCount - 1) / threadCount;

    for (int i = 0; i < threadCount; ++i)
    {
        int start = i * chunkSize;
        int end = min(start + chunkSize, n);
        threads.emplace_back(worker, start, end);
    }

    // Wait all thread completed.
    for (auto& t : threads)
    {
        t.join();
    }
}


int main()
{
    // Init numbers.
    //vector<int> nums({ 3, 2, 1, 4, 5, 7, 9, 8, 6, 0 });
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 100);

    std::vector<int> nums(100);
    for (auto& num : nums) {
        num = dist(gen);
    }
    vector<function<void(vector<int>&)>> funcVec = { SelectionSort, HeapSort, InsertionSort, ShellSort, 
        BubbleSort, QuickSort, CountingSort, RadixSort, BucketSort, MergeSort, OddEvenSort, ParallelOddEvenSort};

    // Sort.
    function<void(vector<int>&)> SortFunction = funcVec[11];
    SortFunction(nums);

    // Show nums.
    for (int i : nums)
    {
        cout << i << " ";
    }

    cout << endl;

    return 0;
}

