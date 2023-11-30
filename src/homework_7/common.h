#pragma once

class TestElement {
public:
    TestElement() : m_counter(nullptr) {}

    TestElement(const TestElement&) = delete;
    
    TestElement(TestElement&& other) {
        m_counter = other.m_counter; 
        other.m_counter = nullptr;
    }            

    TestElement(int* counter) : m_counter(counter) {
        *m_counter += 1;
    }

    ~TestElement() {
        if (m_counter) {
            *m_counter -= 1;
        }
    }

    TestElement& operator= (TestElement&& other) {
        if (this != &other) {
            m_counter = other.m_counter;
            other.m_counter = nullptr;
        }            
        return *this;
    }

    TestElement& operator= (const TestElement& other) = delete;

private:
    int* m_counter;
};