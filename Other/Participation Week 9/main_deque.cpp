// Participation Week 09, Conor & Gabrielle Dowdell

#include <iostream>
#include <deque> 
#include <vector>
using namespace std;

void printKMax(const vector<int>& arr, int n, int k)
{
    std::deque<int> dq;  
    for (int i = 0; i < k; ++i) {
        while (!dq.empty() && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    
    for (int i = k; i < n; ++i) {
        std::cout << arr[dq.front()] << " ";
        while (!dq.empty() && dq.front() <= i - k) {
            dq.pop_front();
        }
        while (!dq.empty() && arr[i] >= arr[dq.back()]) {
            dq.pop_back();
        }
        dq.push_back(i); 
    }
    
    // Print the maximum for the last window
    std::cout << arr[dq.front()] << std::endl;
}

int main() {
    int t;
    cin >> t;  // Number of test cases

    while (t > 0) {
        t--;
        
        int n, k;
        cin >> n >> k;  // Read the size of the array and subarray size

        vector<int> arr(n);
        for (int i = 0; i < n; ++i) {
            cin >> arr[i];  // Read the array elements
        }

        printKMax(arr, n, k);  // Print the maximums for each subarray of size k
    }

    return 0;
}
