#pragma once
#include <iostream>

template<typename T>
class Array {
public:
    Array() {
        setupDefault();
    }

    Array(const Array& other) {
        readOther(other);
    }

    Array(Array&& other) {
        readOther(std::move(other));
    }

    virtual ~Array() {
        delete[] m_data;
        m_data = nullptr;
        m_size = m_capacity = 0;
    }    

    void push_back(const T& value) {
        pushBackImpl(value);
    }

    void push_back(T&& value) {
        pushBackImpl(std::move(value));
    }

    void insert(size_t pos, const T& value) {
        if (pos < m_size) {
            tryReallocate();
            for (size_t i = m_size; i > pos; i--) {
                m_data[i] = std::move(m_data[i - 1]);
            }
            m_data[pos] = value;
            m_size++;
        } else {
            push_back(value);
        }
    }

    void insert(size_t pos, T&& value) {
        if (pos < m_size) {
            tryReallocate();
            for (size_t i = m_size; i > pos; i--) {
                m_data[i] = std::move(m_data[i - 1]);
            }
            m_data[pos] = std::move(value);
            m_size++;
        } else {
            push_back(std::move(value));
        }
    }

    void erase(size_t pos) {
        if (m_size && pos < m_size) {
            for (size_t i = pos; i < m_size - 1; i++) {
                m_data[i] = std::move(m_data[i + 1]);
            }
            m_size--;
        }
    }

    size_t size() const {
        return m_size;
    }

    T& operator[] (size_t index) {
        return m_data[index];
    }

    const T& operator[] (size_t index) const {
        return m_data[index];
    }

    Array& operator= (const Array& other) {
        if (this != &other) {            
            delete[] m_data;
            readOther(other);            
        }
        return *this;
    }

    Array& operator= (Array&& other) {
        if (this != &other) {            
            delete[] m_data;
            readOther(std::move(other));
        }
        return *this;
    }

    class iterator {
    public:
        iterator(T* ptr) : data{ptr} {}

        T& operator* () {
            return *data;
        }

        iterator& operator++ () {
            data++;
            return *this;
        }

        bool operator!= (const iterator& other) const {
            return data != other.data;
        }

    private:
        T* data;

    };

    iterator begin() {
        return iterator(m_size ? m_data : nullptr);
    }

    iterator end() {
        return iterator(m_size ? m_data + m_size : nullptr);
    }

private:
    static constexpr size_t INIT_CAPACITY = 4;

    void tryReallocate() {
        if (m_size == m_capacity) {
            m_capacity = static_cast<size_t>(m_capacity * 1.5);
            T* newData = new T[m_capacity];            
            for (size_t i = 0; i < m_size; i++) {
                newData[i] = std::move(m_data[i]);
            }            
            delete[] m_data;
            m_data = newData;
        }
    }

    void readOther(const Array& other) {
        m_data = new T[other.m_capacity];
        for (size_t i = 0; i < other.m_size; i++) {
            m_data[i] = other.m_data[i];
        }
        m_size = other.m_size;
        m_capacity = other.m_capacity;
    }

    void readOther(Array&& other) {
        m_data = other.m_data;
        m_size = other.m_size;
        m_capacity = other.m_capacity;

        other.m_data = nullptr;
        other.m_size = 0;
        other.m_capacity = 0;
    }

    template<typename TT>
    void pushBackImpl(TT&& value) {
        if (m_capacity == 0 || !m_data) {
            setupDefault();
        }

        tryReallocate();
        m_data[m_size++] = std::forward<TT>(value);
    }
    
    void setupDefault() {
        m_size = 0;
        m_data = new T[INIT_CAPACITY];
        m_capacity = INIT_CAPACITY;       
    }

    size_t m_size;
    size_t m_capacity;
    T* m_data;
};

template<typename T>
std::ostream& operator<< (std::ostream& stream, const Array<T>& obj) {
    for (size_t i = 0; i < obj.size(); i++) {
        stream << obj[i] << ' ';
    }
    return stream;
}