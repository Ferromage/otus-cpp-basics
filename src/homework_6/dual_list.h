#pragma once
#include <iostream>

template<typename T>
class DualList {
    struct Node {
        Node() : prev{nullptr}, next{nullptr}, value{} {}
        Node* prev;
        Node* next;
        T value;
    };

public:
    DualList() : m_head{nullptr}, m_size{0} {}

    DualList(const DualList& other) : DualList() {
        readOther(other);
    }

    DualList(DualList&& other) : DualList() {
        readOther(std::move(other));
    }

    virtual ~DualList() {
        clear();
    }

    DualList& operator= (const DualList& other) {
        if (this != &other) {
            clear();
            readOther(other);
        }
        return *this;
    }

    DualList& operator= (DualList&& other) {
        if (this != &other) {
            clear();
            readOther(std::move(other));
        }
        return *this;
    }

    void clear() {
        Node* node = m_head;
        while (node) {
            Node* next = node->next;
            delete node;
            node = next;
        }
        m_head = nullptr;
        m_size = 0;
    }

    void push_back(const T& value) {
        if (m_size == 0) {
            m_head = new Node;
            m_head->value = value;            
        } else {        
            Node* node = m_head;
            while (node->next) {
                node = node->next;
            }
            node->next = new Node;
            node->next->value = value;
            node->next->prev = node;
        }
        m_size++;
    }

    void push_back(T&& value) {
        if (m_size == 0) {
            m_head = new Node;
            m_head->value = std::move(value);
        } else {        
            Node* node = m_head;
            while (node->next) {
                node = node->next;
            }
            node->next = new Node;
            node->next->value = std::move(value);
            node->next->prev = node;
        }
        m_size++;
    }

    void insert(size_t pos, const T& value) {
        if (m_size == 0 || pos >= m_size) {
            push_back(value);
        } else {
            if (pos == 0) {
                Node* newNode = new Node;
                newNode->value = value;
                newNode->next = m_head;
                m_head->prev = newNode;
                m_head = newNode;
            } else {
                Node* node = m_head;
                for (size_t i = 0; i < pos; i++) {
                    node = node->next;
                }

                Node* newNode = new Node;
                newNode->value = value;
                newNode->next = node;
                node->prev->next = newNode;
                node->prev = newNode;
            }            
            m_size++;
        }
    }

    void insert(size_t pos, T&& value) {
        if (m_size == 0 || pos >= m_size) {
            push_back(std::move(value));
        } else {
            if (pos == 0) {
                Node* newNode = new Node;
                newNode->value = std::move(value);
                newNode->next = m_head;
                m_head->prev = newNode;
                m_head = newNode;
            } else {
                Node* node = m_head;
                for (size_t i = 0; i < pos; i++) {
                    node = node->next;
                }

                Node* newNode = new Node;
                newNode->value = std::move(value);
                newNode->next = node;
                node->prev->next = newNode;
                node->prev = newNode;
            }            
            m_size++;
        }
    }

    void erase(size_t pos) {
        if (pos >= m_size) {
            return;
        }

        if (pos == 0) {
            Node* next = m_head->next;
            if (next) {
                next->prev = nullptr;
            }
            delete m_head;
            m_head = next;
        } else {
            Node* node = m_head;
            for (size_t i = 0; i < pos; i++) {
                node = node->next;
            }            
            node->prev->next = node->next;
            if (node->next) {
                node->next->prev = node->prev;
            }
            delete node;
        }        
        m_size--;
    }

    size_t size() const {
        return m_size;
    }

    T& operator[] (size_t index) {
        Node* node = m_head;
        for (size_t i = 0; i < index; i++) {
            node = node->next;
        }
        return node->value;
    }

    const T& operator[] (size_t index) const {
        Node* node = m_head;
        for (size_t i = 0; i < index; i++) {
            node = node->next;
        }
        return node->value;
    }

    class iterator {
    public:
        iterator(Node* ptr) : node(ptr) {}

        iterator& operator++ () {
            node = node->next;
            return *this;
        }

        T& operator* () {
            return node->value;
        }

        bool operator!= (const iterator& other) const {
            return node != other.node;
        }

    private:
        Node* node;
    };
    
    iterator begin() const {
        return iterator(m_head);
    }

    iterator end() const {
        return iterator(nullptr);
    }

private:
    void readOther(const DualList& other) {
        if (other.m_size == 0) {
            return;
        }
        m_head = new Node;
        Node* src = other.m_head;
        Node* node = m_head;
        while (src) {
            node->value = src->value;
            if (src->next) {
                node->next = new Node;
                node->next->prev = node;
                node = node->next;
            }
            src = src->next;
        }
        m_size = other.m_size;
    }

    void readOther(DualList&& other) {
        m_head = other.m_head;
        m_size = other.m_size;
        other.m_head = nullptr;
        other.m_size = 0;
    }

    Node* m_head;
    size_t m_size;
};

template<typename T>
std::ostream& operator<< (std::ostream& stream, const DualList<T>& obj) {    
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        stream << *it << ", ";
    }
    return stream;
}