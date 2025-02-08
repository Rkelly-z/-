//
//  main.cpp
//  动态数组
//
//  Created by 吴皓 on 2025/2/5.
//

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename E>

class MyArrayList {
private:
    // 底层数组
    E* data;
    
    // 当前元素个数
    int size;
    
    // 最大元素容量
    int cap;
    
    // 默认初始容量
    static const int INIT_CAP = 1;
    
public:
    MyArrayList() {
        this->data = new E[INIT_CAP];
        this->size = 0;
        this->cap = INIT_CAP;
    }
    
    MyArrayList(int initCapacity) {
        this->data = new E[initCapacity];
        this->size = 0;
        this->cap = initCapacity;
    }
    
    // 增
    void addLast(E e) {
        add(size, e);
    }
     
    void add(int index, E e){
        // 检查索引越界
        checkPositionIndex(index);
        
        // 如果容量已满，则扩充一倍长度
        if (size == cap)
            resize(2 * cap);
        
        // 搬移数据 data[index..] -> data[index+1..]
        // 从最后一个元素开始向前遍历，每个元素向后搬移一个位置
        for (int i = size - 1; i >= index; i--)
            data[i + 1] = data[i];
        
        data[index] = e;
        size++;
    }
    
    void addFirst(E e) {
        add(0, e);
    }
    
    // 删
    E removeLast() {
        E deletedVal = remove(size - 1);
        
        return deletedVal;
    }
    
    E remove(int index) {
        if (size == 0)
            throw std::out_of_range("NoSuchElementException");
        
        // 检查索引越界
        checkElementIndex(index);
        
        // 如果当前元素个数小于最大容量的1/4，则数组容量减小一半
        if (size == cap / 4)
            resize(cap / 2);
        
        E deletedVal = data[index];
        
        // 搬移数据 data[index+1..] -> data[index..]
        // 从index + 1开始向后遍历，每个元素向前移搬移个位置
        for (int i = index + 1; i < size; i++)
            data[i - 1] = data[i];
        
        data[size - 1] = NULL;
        size--;
        
        return deletedVal;
    }
    
    E removeFirst() {
        return remove(0);
    }
    
    // 查
    E get(int index) {
        // 检查索引越界
        checkElementIndex(index);
        
        return data[index];
    }
    
    // 改
    E set(int index, E element) {
        // 检查索引越界
        checkElementIndex(index);
        
        E oldVal = data[index];
        data[index] = element;
        
        return oldVal;
    }
    
    // 获取元素个数
    int getSize() {
        return size;
    }
    
    // 判断是否为空
    bool isEmpty() {
        return size == 0;
    }
    
    //修改容量
    void resize(int newCap) {
        E* temp = new E[newCap];
        
        for (int i = 0; i < size; i++)
            temp[i] = data[i];
        
        // 释放原数组内存
        delete[] data;
        // 指向新数组
        data = temp;
        cap = newCap;
    }
    
    // 检查 index 索引位置是否可以存在元素
    void checkElementIndex(int index) {
        if (!(index >= 0 && index < size))
            throw out_of_range("Index out of bounds");
    }
    
    // 检查 index 索引位置是否可以添加元素
    void checkPositionIndex(int index) {
        // 可插入的元素位置包括第size的位置
        if (!(index >= 0 && index <= size))
            throw out_of_range("Index out of bounds");
    }
    
    // 现实元素
    void display() {
        cout << "size = " << size << " cap = " << cap << std::endl;
        
        for (int i = 0; i < size; i++)
            cout << data[i] << " ";
        
        cout << endl << endl;
    }
    
    ~MyArrayList() {
        delete[] data;
    }
    
};

int main(int argc, const char * argv[]) {
    // 构造测试数据
    MyArrayList<int> arr(3);
    arr.display();
    
    // arr.removeLast();
    
    for (int i = 1; i <= 5; i++)
        arr.addLast(i);
    arr.display();
    
    arr.remove(3);
    arr.display();
    
    arr.add(1, 9);
    arr.display();
    
    arr.addFirst(100);
    arr.display();
    
    (void)arr.removeLast();
    arr.display();
    
        
    return 0;
}
