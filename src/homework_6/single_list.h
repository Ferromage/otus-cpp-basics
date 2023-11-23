#pragma once
#include <iostream>

template<typename T>
class SingleList {
    struct Node {
        Node() : next{nullptr}, value{} {}
        Node* next;
        T value;
    };

public:
    SingleList() : m_head{nullptr}, m_size{0} {}

    SingleList(const SingleList& other) : SingleList() {
        readOther(other);
    }

    SingleList(SingleList&& other) : SingleList() {
        readOther(std::move(other));
    }

    virtual ~SingleList() {
        clear();
    }

    SingleList& operator= (const SingleList& other) {
        if (this != &other) {
            clear();
            readOther(other);
        }
        return *this;
    }

    SingleList& operator= (SingleList&& other) {
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
        }
        m_size++;
    }

    void insert(size_t pos, const T& value) {
        if (m_size == 0 || pos >= m_size) {
            push_back(value);
        } else {
            Node* node = m_head;
            Node* prev = nullptr;
            for (size_t i = 0; i < pos; i++) {
                prev = node;
                node = node->next;
            }
            
            Node* newNode = new Node;
            newNode->value = value;
            newNode->next = node;

            if (prev) {
                prev->next = newNode;
            } else {
                m_head = newNode;
            }
            m_size++;
        }
    }

    void insert(size_t pos, T&& value) {
        if (m_size == 0 || pos >= m_size) {
            push_back(std::move(value));
        } else {
            Node* node = m_head;
            Node* prev = nullptr;
            for (size_t i = 0; i < pos; i++) {
                prev = node;
                node = node->next;
            }
            
            Node* newNode = new Node;
            newNode->value = std::move(value);
            newNode->next = node;

            if (prev) {
                prev->next = newNode;
            } else {
                m_head = newNode;
            }
            m_size++;
        }
    }

    void erase(size_t pos) {
        if (pos >= m_size) {
            return;
        }

        Node* node = m_head;
        Node* prev = nullptr;
        for (size_t i = 0; i < pos; i++) {
            prev = node;
            node = node->next;
        }

        if (prev) {
            prev->next = node->next;
        } else {
            m_head = node->next;
        }

        delete node;        
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
    void readOther(const SingleList& other) {
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
                node = node->next;
            }
            src = src->next;
        }
        m_size = other.m_size;
    }

    void readOther(SingleList&& other) {
        m_head = other.m_head;
        m_size = other.m_size;
        other.m_head = nullptr;
        other.m_size = 0;
    }

    Node* m_head;
    size_t m_size;
};

template<typename T>
std::ostream& operator<< (std::ostream& stream, const SingleList<T>& obj) {    
    for (auto it = obj.begin(); it != obj.end(); ++it) {
        stream << *it << ", ";
    }
    return stream;
}