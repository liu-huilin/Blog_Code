#ifndef __LIST_HPP__
#define __LIST_HPP__

#include<iostream>


// 先声明链表类，便于node将其声明为友元
template<typename T> class list;

// 链表节点类
template<typename T>
class node
{
public:
    node() : next(nullptr){}
    node(T val) : data(val), next(nullptr) {}
private:
    T data;
    node* next;
    friend class list<T>;
};

/*
链表操作
1、删除节点
2、添加节点
3、
*/

template<typename T>
class list
{
public:
    list(); // 构造函数
    list(const list<T>& l); // 拷贝构造
    list<T>& operator= (const list<T>& l); // 拷贝赋值 
    void insert_node(int index, T val); // 在index处插入结点
    void del_node(int index); // 删除index处结点
    T get_node(int index); // 获取index处结点值
    int find(int value); // 查找值value，找到返回index，找不到返回-1
    int get_length(); // 获取链表长度
    void push_back(T val); // 在链表尾部插入数据
    ~list(); // 析构函数

private:
    node<T>* head_ptr; // 链表头指针
    int length; // 链表长度
};

 // 构造函数
template<typename T>
list<T>::list()
{
    this->head_ptr = nullptr;
    this->length = 0;
}

// 拷贝构造
template<typename T>
list<T>::list(const list<T>& l)
{
    if(l.head_ptr == nullptr)
    {
        this->head_ptr = nullptr;
        this->length = 0;
    }
    else
    {
        this->head_ptr = new node<T>;
        node<T>* p1 = this->head_ptr;
        node<T>* p2 = nullptr;
        // 拷贝链表
        for(p2 = l.head_ptr; p2->next != nullptr; p2 = p2->next)
        {
            p1->data = p2->data;
            p1->next = new node<T>;
            p1 = p1->next;
        }
        p1->data = p2->data;
        p1->next = nullptr;
        this->length = l.length;
    }
    

}

// 拷贝赋值 
template<typename T>
list<T>& list<T>::operator= (const list<T>& l)
{
    if(this->head_ptr == nullptr) // 原链表空
    {
        if(l.head_ptr == nullptr)
        {
            this->head_ptr = nullptr;
            this->length = 0;
        }
        else
        {
            this->head_ptr = new node<T>;
            node<T>* p1 = this->head_ptr;
            node<T>* p2 = nullptr;
            // 拷贝链表
            for(p2 = l.head_ptr; p2->next != nullptr; p2 = p2->next)
            {
                p1->data = p2->data;
                p1->next = new node<T>;
                p1 = p1->next;
            }
            p1->data = p2->data;
            p1->next = nullptr;
            this->length = l.length;
        }
    }
    else //  原链表非空
    {
        if(l.head_ptr == nullptr)
        {
            // 清空链表
            node<T>* p1 = this->head_ptr;
            node<T>* p2 = p1->next;
            while(p2 != nullptr)
            {
                delete p1;
                p1 = p2;
                p2 = p2->next;
            }
            delete p1;
            this->length = 0;           
        }
        else
        {
            if(l.length > this->length) // 待复制的链表更长，先将原链表填满再申请空间
            {
                node<T>* p1 = this->head_ptr;
                node<T>* p2 = l.head_ptr;
                for(int i = 0; i < this->length - 1; i++)
                {
                    p1->data = p2->data;
                    p1 = p1->next;
                    p2 = p2->next;
                }
                p1->next = new node<T>;
                for(int i = this->length - 1; i < l.length - 1; i++)
                {
                    p1->data = p2->data;
                    p1->next = new node<T>;
                    p1 = p1->next;
                    p2 = p2->next;
                }
                p1->data = p2->data;
                p1->next = nullptr;
            }
            else // 待复制的链表更短或相等，更短时需要释放原链表多余空间
            {
                node<T>* p1 = this->head_ptr;
                node<T>* p2 = l.head_ptr;
                // 复制数据
                for(int i = 0; i < l.length; i++)
                {
                    p1->data = p2->data;
                    p1 = p1->next;
                    p2 = p2->next;
                }
                // 删除多余结点               
                while(p1 != nullptr)
                {
                    p2 = p1->next;
                    delete p1;
                    p1 = p2;
                }
            }
        }
        this->length = l.length;
    }

    return *this;
}

// 在index处插入结点
template<typename T>
void list<T>::insert_node(int index, T val)
{
    if((index > this->length)) // 超过索引，最多可以插到当前结点的下一个结点，否则就是超过索引
    {
        throw runtime_error("index out of this list`s range");
    }
    else if((this->head_ptr == nullptr) && (index == 0)) // 插在空链表的头
    {
        this->head_ptr = new node<T>;
        this->head_ptr->next = nullptr;
        this->head_ptr->data = val;
        this->length++;
    } 
    else // 一般情况
    {
        node<T>* p1 = this->head_ptr;
        node<T>* p2 = new node<T>;
        for(int i = 0; i < index - 1; i++)
        {
            p1 = p1->next;
        }
        p2->data = val;
        p2->next = p1->next;
        p1->next = p2;
        this->length++;
    }
}

// 删除index处结点
template<typename T>
void list<T>::del_node(int index)
{
    node<T>* p1 = this->head_ptr;
    node<T>* p2 = nullptr;
    for(int i = 0; i < index - 1; i++)
    {
        p1 = p1->next;
    }
    p2 = p1->next->next;
    delete p1->next;
    p1->next = p2;
    this->length--;
}

// 获取index处结点值
template<typename T>
T list<T>::get_node(int index)
{
    if(index > this->length - 1) // 超过索引
    {
        throw runtime_error("index out of this list`s range");
    }
    
    node<T>* p1 = this->head_ptr;
    for(int i = 0; i < index; i++)
    {
        p1 = p1->next;
    }

    return p1->data;
}

// 查找值value，找到返回index，找不到返回-1
template<typename T>
int list<T>::find(int value)
{
    node<T>* p1 = this->head_ptr;
    for(int i = 0; i < this->length; i++)
    {
        if(p1->data == value)
        {
            return i;
        }
        p1 = p1->next;
    }

    return -1;
}

// 获取链表长度
template<typename T>
int list<T>::get_length()
{
    return this->length;
}

// 在链表尾部插入数据
template<typename T>
void list<T>::push_back(T val)
{ 
    if(this->head_ptr == nullptr) // 链表为空
    {
        this->head_ptr = new node<T>;
        this->head_ptr->data = val;
        this->head_ptr->next = nullptr;
    }
    else
    {
        node<T>* p1 = this->head_ptr;
        node<T>* p2 = new node<T>;
        p2->data = val;
        p2->next = nullptr;
        while(p1->next != nullptr)
        {
            p1 = p1->next;
        }
        p1->next = p2;
    }
    this->length++;

}

// 析构函数
template<typename T>
list<T>::~list()
{
    // 清空链表
    node<T>* p1 = this->head_ptr;
    node<T>* p2 = p1->next;
    while(p2 != nullptr)
    {
        delete p1;
        p1 = p2;
        p2 = p2->next;
    }
    delete p1;
    this->length = 0;
    this->head_ptr = nullptr;

} 

#endif