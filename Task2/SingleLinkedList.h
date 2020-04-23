#pragma once
#ifndef SINGLELINKEDLIST_H
#define SINGLELINKEDLIST_H

template<typename T>
struct SingleLinkedList
{
    template<typename T>
    struct SLListNode
    {
        T value;
        SLListNode<T>* next = nullptr;
        SLListNode(T value) : value(value) {}
    };
    int count = 0;
    SLListNode<T>* head = nullptr;
    SLListNode<T>* tail = nullptr;
    void append(const T value)
    {
        SLListNode<T>* newTail = new SLListNode<T>(value);
        if (head)
        {
            tail->next = newTail;
            tail = newTail;
        }
        else head = tail = newTail;
        count++;
    }
    void distinct()
    {
        SLListNode<T>* selected = head;
        while (selected)
        {
            SLListNode<T>* node1 = selected;
            while (node1->next)
            {
                if (selected->value == node1->next->value)
                {
                    count--;
                    if (node1->next->next)
                    {
                        node1->next = node1->next->next;
                    }
                    else
                    {
                        node1->next = nullptr;
                        tail = node1;
                        break;
                    }
                }
                else node1 = node1->next;
            }
            selected = selected->next;
        }
    }
    T elementFromTheEnd(const int number) const
    {
        int index = count - number;
        return element(index);
    }
    T element(const int index) const
    {
        auto node1 = head;
        for (int i = 0; i < index; i++)
        {
            node1 = node1->next;
        }
        return node1->value;
    }
};

#endif // !SINGLELINKEDLIST_H
