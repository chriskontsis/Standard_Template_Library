#include <vector>
#include <iostream>
template<typename T>
class MinHeap {
    private:
        std::vector<T> heap;

        void heapifyUp(int idx)
        {
            int parent = (idx - 1) / 2;
            while(idx && heap[idx] < heap[parent]) {
                std::swap(heap[idx], heap[parent]);
                idx = parent;
                parent = (idx-1)/2;
            }
        }
        void heapifyDown(int idx)
        {
            int sz = heap.size();
            int leftChild = 2 * idx + 1;
            int rightChild = 2*idx + 2;
            int smallest = idx;

            while(leftChild < sz && heap[leftChild] < heap[smallest])
                smallest = leftChild;
            while(rightChild < sz && heap[rightChild] < heap[smallest])
                smallest = rightChild;
            
            if(smallest != idx)
            {
                std::swap(heap[idx], heap[smallest]);
                heapifyDown(smallest);
            }
        }
    public:
        void insert(const T& v) {
            heap.push_back(v);
            heapifyUp(heap.size()-1);
        }
        T popMin() {
            if(heap.empty())
                throw::std::out_of_range("Heap is empty");

            T minElement = heap[0];
            heap[0] = heap.back();
            heap.pop_back();
            heapifyDown(0);
            return minElement;
        }
        T& top() {
            if(heap.empty())
                throw::std::out_of_range("Heap is empty");
            return heap[0]; 
        }
        void printHeap() const {
            for (const auto& value : heap) {
                std::cout << value << " ";
            }
            std::cout << std::endl;
        }
};

int main() {
    MinHeap<int> heap;
    heap.insert(4);
    heap.insert(2);
    heap.insert(3);
    heap.insert(1);
    heap.insert(7);

    heap.printHeap();
    std::cout << heap.top() << '\n';
    heap.popMin();
    std::cout << heap.top() << '\n';
}