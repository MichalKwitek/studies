#include <iostream>
#include <cstdio>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

template <typename T>
class Array {
private:
    T* data;
    size_t size;

public:
    Array() {}

    Array(size_t size) : size(size) {
        data = new T[size];
    }

    Array(size_t size, T value) : size(size) {
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = value;
        }
    }

    ~Array() {
        delete[] data;
    }

    Array(const Array& other) : size(other.size) {
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
    }

    Array(Array&& other) noexcept : data(other.data), size(other.size) {
        other.data = nullptr;
        other.size = 0;
    }

    Array& operator=(const Array& other) {
        if (this == &other) return *this;
        delete[] data;
        size = other.size;
        data = new T[size];
        for (size_t i = 0; i < size; ++i) {
            data[i] = other.data[i];
        }
        return *this;
    }

    Array& operator=(Array&& other) noexcept {
        if (this == &other) return *this;
        delete[] data;
        data = other.data;
        size = other.size;
        other.data = nullptr;
        other.size = 0;
        return *this;
    }

    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    size_t getSize() const {
        return size;
    }

    T* begin() {
        return data;
    }

    const T* begin() const {
        return data;
    }

    T* end() {
        return data + size;
    }

    const T* end() const {
        return data + size;
    }
};

template<typename T>
class Vector {
private:
    T* data;         // Pointer to the data array
    size_t capacity; // Capacity of the vector
    size_t size;     // Number of elements in the vector

public:
    // Constructor
    Vector() : data(nullptr), capacity(0), size(0) {}

    // Constructor to initialize vector with a specific size
    Vector(size_t n) : size(n), capacity(n) {
        data = new T[capacity];
    }

    // Constructor to initialize vector with a specific size and value
    Vector(size_t n, const T& value) : size(n), capacity(n) {
        data = new T[capacity];
        for (size_t i = 0; i < size; ++i) {
            data[i] = value;
        }
    }

    // Destructor
    ~Vector() {
        delete[] data;
    }

    // Function to resize the internal array
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];

        // Manually copy elements from old array to new array
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[i];
        }

        // Deallocate old memory
        delete[] data;

        // Update data pointer and capacity
        data = newData;
        capacity = newCapacity;
    }

    // Add an element to the end of the vector
    void push_back(const T& value) {
        if (size == capacity) {
            resize(capacity == 0 ? 1 : capacity * 2);
        }
        data[size++] = value;
    }

    // Remove the last element from the vector
    void pop_back() {
        if (size == 0) {
            // Custom error handling for underflow
            cerr << "Error: Vector is empty, cannot pop back." << std::endl;
            exit(EXIT_FAILURE); // Terminate the program
        }
        --size;
    }

    // Access element at a specific index with bounds checking
    T& at(size_t index) {
        if (index >= size) {
            // Custom error handling for out of range
            std::cerr << "Error: Index " << index << " is out of range." << std::endl;
            exit(EXIT_FAILURE); // Terminate the program
        }
        return data[index];
    }

    const T& at(size_t index) const {
        if (index >= size) {
            // Custom error handling for out of range
            std::cerr << "Error: Index " << index << " is out of range." << std::endl;
            exit(EXIT_FAILURE); // Terminate the program
        }
        return data[index];
    }

    // Access element at a specific index without bounds checking
    T& operator[](size_t index) {
        return data[index];
    }

    const T& operator[](size_t index) const {
        return data[index];
    }

    // Return pointer to data
    T* getData() const {
        return data;
    }

    // Return the number of elements in the vector
    size_t getSize() const {
        return size;
    }

    // Return the capacity of the vector
    size_t getCapacity() const {
        return capacity;
    }

    // Check if the vector is empty
    bool empty() const {
        return size == 0;
    }

    // Clear the vector
    void clear() {
        size = 0;
    }
};

template<typename T>
class Queue {
private:
    T* data;          // Array to store elements
    size_t capacity;  // Capacity of the queue
    size_t size;      // Number of elements in the queue
    size_t frontIndex;// Index of the front element
    size_t rearIndex; // Index of the rear element

public:
    // Constructor
    Queue() : capacity(10), size(0), frontIndex(0), rearIndex(0) {
        data = new T[capacity];
    }

    // Destructor
    ~Queue() {
        delete[] data;
    }

    // Push an element to the back of the queue
    void push(const T& value) {
        if (size == capacity) {
            resize(capacity * 2); // Double the capacity if full
        }
        data[rearIndex] = value;
        rearIndex = (rearIndex + 1) % capacity;
        ++size;
    }

    // Remove the front element from the queue
    void pop() {
        if (size == 0) {
            throw "Queue is empty"; // Custom exception
        }
        frontIndex = (frontIndex + 1) % capacity;
        --size;
    }

    // Get the front element of the queue
    T& front() {
        if (size == 0) {
            throw "Queue is empty"; // Custom exception
        }
        return data[frontIndex];
    }

    // Check if the queue is empty
    bool empty() const {
        return size == 0;
    }

private:
    // Resize the internal array
    void resize(size_t newCapacity) {
        T* newData = new T[newCapacity];
        for (size_t i = 0; i < size; ++i) {
            newData[i] = data[(frontIndex + i) % capacity];
        }
        delete[] data;
        data = newData;
        capacity = newCapacity;
        frontIndex = 0;
        rearIndex = size;
    }
};

// Simple hash function for integers
size_t hashFunc(int key) {
    return key;
}

// Node structure for linked list (chaining)
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

class UnorderedSet {
private:
    static const int TABLE_SIZE = 10;
    Node* table[TABLE_SIZE];
    size_t size;

    // Function to find the previous node of a given key in a linked list
    Node* findPrev(Node* head, int key) const {
        Node* curr = head;
        Node* prev = nullptr;
        while (curr) {
            if (curr->data == key)
                return prev;
            prev = curr;
            curr = curr->next;
        }
        return nullptr;
    }

public:
    // Constructor
    UnorderedSet() : size(0) {
        for (int i = 0; i < TABLE_SIZE; ++i)
            table[i] = nullptr;
    }

    // Destructor
    ~UnorderedSet() {
        clear();
    }

    // Insert a key into the set
    void insert(int key) {
        size_t index = hashFunc(key) % TABLE_SIZE;
        if (!contains(key)) {
            Node* newNode = new Node(key);
            newNode->next = table[index];
            table[index] = newNode;
            ++size;
        }
    }

    // Check if the set contains a given key
    bool contains(int key) const {
        size_t index = hashFunc(key) % TABLE_SIZE;
        Node* curr = table[index];
        while (curr) {
            if (curr->data == key)
                return true;
            curr = curr->next;
        }
        return false;
    }

    // Remove a key from the set
    void erase(int key) {
        size_t index = hashFunc(key) % TABLE_SIZE;
        Node* prev = nullptr;
        Node* curr = table[index];
        while (curr) {
            if (curr->data == key) {
                if (prev)
                    prev->next = curr->next;
                else
                    table[index] = curr->next;
                delete curr;
                --size;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    // Check if the set is empty
    bool empty() const {
        return size == 0;
    }

    // Get the number of elements in the set
    size_t getSize() const {
        return size;
    }

    // Clear the set
    void clear() {
        for (int i = 0; i < TABLE_SIZE; ++i) {
            Node* curr = table[i];
            while (curr) {
                Node* temp = curr;
                curr = curr->next;
                delete temp;
            }
            table[i] = nullptr;
        }
        size = 0;
    }
};

void printVoid() {
    printf("?\n");
}

// Function to merge two halves into a sorted array
void merge(int* arr, int left, int mid, int right) {
    // Sizes of two subarrays to be merged
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Create temporary arrays
    int* L = new int[n1];
    int* R = new int[n2];

    // Copy data to temporary arrays L[] and R[]
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + j];

    // Initial indices of the two subarrays
    int i = 0, j = 0;

    // Initial index of merged subarray array
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i] > R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    // Free the temporary arrays
    delete[] L;
    delete[] R;
}

// Function to implement merge sort
void mergeSort(int* arr, int left, int right) {
    if (left >= right) return; // Base case: If the array contains 0 or 1 element

    int mid = left + (right - left) / 2;

    // Recursively sort the first and second halves
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Merge the sorted halves
    merge(arr, left, mid, right);
}

// Function to compute and print the degree sequence of a graph
int degreeSequence(int** graph, int* degrees, int& n) {
    long long edgeCount = 0;
    for (int i = 1; i <= n; ++i) {
        edgeCount += degrees[i];
    }
    int* degreesCopy = new int[n];
    for (int i = 1; i <= n; ++i)
    {
        degreesCopy[i - 1] = degrees[i];
    }
    mergeSort(degreesCopy, 0, n - 1);
    for (int i = 0; i < n; ++i) {
        printf("%d ", degreesCopy[i]);
    }
    printf("\n");
    delete[] degreesCopy;
    return edgeCount / 2;
}

// Function to perform BFS and mark all reachable vertices
void bfs(int start, int** graph, int* degrees, int& n, Array<int>& visited, Vector<Vector<int>*>& components, int* componentsSize) {
    Queue<int> q;
    q.push(start);
    visited[start] = 1;
    int componentSize = 1;
    Vector<int>* component = new Vector<int>(); // memory deallocated at the end of main function
    component->push_back(start);

    while (!q.empty()) {
        int v = q.front();
        q.pop();
        for (int i = 0; i < degrees[v]; ++i) {
            int neighbor = graph[v][i];
            if (!visited[neighbor]) {
                visited[neighbor] = 1;
                component->push_back(neighbor);
                componentSize++;
                q.push(neighbor);
            }
        }
    }
    for (int i = 0; i < component->getSize(); ++i) {
        int vertex = (*component)[i];
        componentsSize[vertex] = componentSize;
    }
    components.push_back(component);
}

// Function to count the number of connected components in a graph
void connectedComponents(int** graph, int* degrees, int& n, Vector<Vector<int>*>& components, int* componentsSize) {
    Array<int> visited(n + 1, 0);
    int componentCount = 0;

    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            bfs(i, graph, degrees, n, visited, components, componentsSize);
            componentCount++;
        }
    }

    printf("%d\n", componentCount);
}

// Function to print the number of edges in a complimentary graph
void complimentaryEdges(int& n, long long& edgeCount) {
    long long n_minus_1 = n - 1;
    long long num_pairs = n * n_minus_1;
    long long result = num_pairs / 2 - edgeCount;
    printf("%lld\n", result);
}

// Function to check if a graph is bipartite using BFS
bool isBipartite(int** graph, int* degrees, int& n, int start, Array<int>& colors) {
    Queue<int> q;
    q.push(start);
    colors[start] = 1; // Start coloring with 1

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < degrees[v]; ++i) {
            int neighbor = graph[v][i];
            if (colors[neighbor] == -1) {
                // Color with opposite color
                colors[neighbor] = 1 - colors[v];
                q.push(neighbor);
            }
            else if (colors[neighbor] == colors[v]) {
                // Conflict in coloring
                return false;
            }
        }
    }
    return true;
}

// Function to check if the entire graph is bipartite
bool checkBipartite(int** graph, int* degrees, int& n) {
    Array<int> colors(n + 1, -1); // -1 means uncolored

    for (int i = 1; i <= n; ++i) {
        if (colors[i] == -1) {
            if (!isBipartite(graph, degrees, n, i, colors)) {
                return false;
            }
        }
    }
    return true;
}

// Function to print info if the entire graph is bipartite
void bipartite(int** graph, int* degrees, int& n) {
    if (checkBipartite(graph, degrees, n))
        printf("T\n");
    else printf("F\n");
}

// Function to perform greedy coloring of the graph
void greedyColoring(int** graph, int* degrees, int& n) {
    Array<int> colors(n + 1, 0); // Color assignments, 0 means uncolored

    // Traverse each vertex
    for (int u = 1; u <= n; ++u) {
        UnorderedSet neighborColors;

        // Collect colors of adjacent vertices
        for (int i = 0; i < degrees[u]; ++i) {
            int neighbor = graph[u][i];
            if (colors[neighbor] != 0) {
                neighborColors.insert(colors[neighbor]);
            }
        }

        // Assign the smallest available color
        int color = 1;
        while (neighborColors.contains(color)) {
            color++;
        }
        colors[u] = color;
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d ", colors[i]);
    }
    printf("\n");
}

// Merge function for lf coloring merge sort
void merge(Array<int>& vertices, int* degrees, int& n, int* temp, int left, int mid, int right) {
    int i = left;
    int j = mid + 1;
    int k = left;

    while (i <= mid && j <= right) {
        if (degrees[vertices[i]] >= degrees[vertices[j]]) {
            temp[k++] = vertices[i++];
        }
        else {
            temp[k++] = vertices[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = vertices[i++];
    }

    while (j <= right) {
        temp[k++] = vertices[j++];
    }

    for (int l = left; l <= right; ++l) {
        vertices[l] = temp[l];
    }
}

// Recursive lf coloring merge sort function
void mergeSort(Array<int>& vertices, int* degrees, int& n, int* temp, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vertices, degrees, n, temp, left, mid);
        mergeSort(vertices, degrees, n, temp, mid + 1, right);
        merge(vertices, degrees, n, temp, left, mid, right);
    }
}

// Function to perform stable sort on vertices based on degrees
void stableSort(Array<int>& vertices, int* degrees, int& n) {
    int* temp = new int[n];
    mergeSort(vertices, degrees, n, temp, 0, n - 1);
    delete[] temp;
}

// Function to perform LF coloring of the graph
void lfColoring(int** graph, int* degrees, int& n) {
    Array<int> colors(n + 1, 0); // Color assignments, 0 means uncolored

    // Create a list of vertices and sort them by degree in descending order
    Array<int> vertices(n);
    for (int i = 0; i < n; ++i) {
        vertices[i] = i + 1;
    }

    stableSort(vertices, degrees, n);

    // Traverse each vertex in sorted order
    for (int j = 0; j < n; ++j) {
        int u = vertices[j];
        UnorderedSet neighborColors;

        // Collect colors of adjacent vertices
        for (int i = 0; i < degrees[u]; ++i) {
            int neighbor = graph[u][i];
            if (colors[neighbor] != 0) {
                neighborColors.insert(colors[neighbor]);
            }
        }

        // Assign the smallest available color
        int color = 1;
        while (neighborColors.contains(color)) {
            color++;
        }
        colors[u] = color;
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d ", colors[i]);
    }
    printf("\n");
}

// Function to perform BFS and return the maximum distance (eccentricity) from the source vertex
int bfs(int** graph, int* degrees, int& n, int source, int componentSize) {
    Array<int> distance(n + 1, -1); // Distance from source to each vertex
    Queue<int> q;
    distance[source] = 0;
    q.push(source);

    int max_distance = 0;
    int counter = 1;

    while (counter < componentSize) {
        int u = q.front();
        q.pop();
        for (int i = 0; i < degrees[u]; ++i) {
            int neighbor = graph[u][i];
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[u] + 1;
                if (distance[neighbor] > max_distance) {
                    max_distance = distance[neighbor];
                }
                counter++;
                q.push(neighbor);
            }
        }
    }
    return max_distance;
}

// Function to print eccentricity of each vertex
void eccentricity(int** graph, int* degrees, int& n, int* componentsSize) {
    for (int i = 1; i <= n; ++i) {
        if (componentsSize[i] > 1)
            printf("%d ", bfs(graph, degrees, n, i, componentsSize[i]));
        else printf("0 ");
    }
    printf("\n");
}

void bitByBit(int** graph, int* degrees, int& n, Vector<int>& component, Array<int>& colors, Array<int>& saturation, Array<bool>& colored, Array<UnorderedSet>& neighborColors) {
    int m = component.getSize();

    // function to find the vertex with the highest saturation and then highest degree
    auto selectvertex = [&]() {
        int maxsaturation = -1;
        int maxdegree = -1;
        int selectedvertex = -1;

        for (int u = 0; u < m; ++u) {
            int v = component[u];
            if (!colored[v]) {
                if (saturation[v] > maxsaturation) {
                    maxsaturation = saturation[v];
                    maxdegree = degrees[v];
                    selectedvertex = v;
                }
                else if (saturation[v] == maxsaturation && degrees[v] > maxdegree) {
                    maxsaturation = saturation[v];
                    maxdegree = degrees[v];
                    selectedvertex = v;
                }
            }
        }
        return selectedvertex;
        };

    // traverse and color each vertex dynamically based on the saturation degree
    for (int j = 0; j < m; ++j) {
        // Select the vertex with the highest priority
        int u = selectvertex();
        colored[u] = true;

        UnorderedSet neighborcolors;
        for (int i = 0; i < degrees[u]; ++i) {
            int neighbor = graph[u][i];
            if (colors[neighbor] != 0) {
                neighborcolors.insert(colors[neighbor]);
            }
        }

        // assign the smallest available color
        int color = 1;
        while (neighborcolors.contains(color)) {
            color++;
        }
        colors[u] = color;

        // update saturation degrees of the neighbors
        for (int i = 0; i < degrees[u]; ++i) {
            int neighbor = graph[u][i];
            if (!colored[neighbor]) {
                neighborColors[neighbor].insert(color);
                saturation[neighbor] = neighborColors[neighbor].getSize();
            }
        }
    }
}

void reverseVector(Vector<int>& vec) {
    int n = vec.getSize();
    for (size_t i = 0; i < n / 2; ++i) {
        int temp = vec[i];
        vec[i] = vec[n - 1 - i];
        vec[n - 1 - i] = temp;
    }
}

// Function to perform slf (dsatur) coloring of the graph
void slfColoring(int** graph, int* degrees, int& n, Vector<Vector<int>*>& components) {
    Array<int> colors(n + 1, 0); // color assignments, 0 means uncolored
    Array<int> saturation(n + 1, 0); // saturation degree of each vertex
    Array<bool> colored(n + 1, false); // keep track of colored vertices
    Array<UnorderedSet> neighborColors(n + 1);

    for (int i = 0; i < components.getSize(); ++i) {
        Vector<int>* component = components[i];
        if (component->getSize() > 1) {
            mergeSort(component->getData(), 0, component->getSize() - 1);
            reverseVector(*component);
            bitByBit(graph, degrees, n, *component, colors, saturation, colored, neighborColors);
        }
        else {
            colored[(*component)[0]] = true;
            colors[(*component)[0]] = 1;
        }
    }

    for (int i = 1; i <= n; ++i) {
        printf("%d ", colors[i]);
    }
    printf("\n");
}

int** createGraph(int n, int* degrees) {
    int** graph = new int* [n + 1];
    for (int i = 1; i <= n; ++i) {
        int s;
        scanf("%d", &s);
        degrees[i] = s;
        graph[i] = new int[s];
        for (int j = 0; j < s; ++j) {
            scanf("%d", &graph[i][j]);
        }
    }
    return graph;
}

void deleteGraph(int** graph, int& n) {
    for (size_t i = 1; i <= n; ++i) {
        delete[] graph[i];
    }
    delete[] graph;
}

int main() {

    std::ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    scanf("%d", &k);

    for (int i = 0; i < k; ++i) {
        int n;
        scanf("%d", &n);
        int* degrees = new int[n + 1];
        int* componentsSize = new int[n + 1];
        int** graph = createGraph(n, degrees);
        Vector<Vector<int>*> components;

        long long edgeCount = degreeSequence(graph, degrees, n);
        connectedComponents(graph, degrees, n, components, componentsSize);
        bipartite(graph, degrees, n);
        eccentricity(graph, degrees, n, componentsSize);
        printVoid();
        greedyColoring(graph, degrees, n);
        lfColoring(graph, degrees, n);
        slfColoring(graph, degrees, n, components);
        printVoid();
        complimentaryEdges(n, edgeCount);

        deleteGraph(graph, n);
        delete[] degrees;
        delete[] componentsSize;
        for (size_t i = 0; i < components.getSize(); ++i) {
            delete components[i]; // deallocate memory allocated in connectedComponents function 
        }
        components.clear();
    }

    return 0;
}
