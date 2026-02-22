#include <iostream>
#include <stdexcept>


class Buffer {
    friend class Matrix;

private:
    int size;
    double *tab;
    int counter;

public:
    Buffer(int size, double init = 0.0)
        : size(size), counter(0) {
        tab = new double[size];
        reset(init);
    }

    void reset(double value) {
        for (int i = 0; i < size; i++) {
            tab[i] = value;
        }
    }

    bool valid_index(int i) const {
        return (i >= 0) && (i < size);
    }

    void set(int i, double value) {
        tab[i] = value;
    }

    double get(int i) const {
        return tab[i];
    }

    void incr_counter() { counter++; }
    void decr_counter() { counter--; }
    int get_counter() const { return counter; }

    ~Buffer() {
        delete[] tab;
    }
};

class Matrix {
    Buffer *buffer_ptr;
    int rows;
    int columns;

    int flatten_indices(int i, int j) const {
        return i * columns + j;
    }

    bool valid_indices(int i, int j) const {
        return (i >= 0 && i < rows && j >= 0 && j < columns);
    }

//constructeur privé
    Matrix(int r, int c, Buffer *ptr)
        : buffer_ptr(ptr), rows(r), columns(c) {
        if (buffer_ptr) buffer_ptr->incr_counter();
    }

public:
    Matrix(int r, int c, double init = 0.0)
        : rows(r), columns(c) {
        buffer_ptr = new Buffer(rows * columns, init);
        buffer_ptr->incr_counter();
    }

//constructeur de copie
    Matrix(const Matrix& other) 
        : buffer_ptr(other.buffer_ptr), rows(other.rows), columns(other.columns) {
        if (buffer_ptr) buffer_ptr->incr_counter();
    }

//opérateur d'affectation
    Matrix& operator=(const Matrix& other) {
        if (this != &other) {
            decr_buffer();  
            
            buffer_ptr = other.buffer_ptr;
            rows = other.rows;
            columns = other.columns;
            
            if (buffer_ptr) buffer_ptr->incr_counter();
        }
        return *this;
    }

    void print() const {
        std::cout << "Refs: [" << buffer_ptr->get_counter() << "]" << std::endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                std::cout << buffer_ptr->tab[flatten_indices(i, j)] << " ";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void set(int i, int j, double elem) {
            buffer_ptr->set(flatten_indices(i, j), elem);
    }

    double get(int i, int j) const {
        return buffer_ptr->get(flatten_indices(i, j));
    }

    Matrix reshape(int i, int j) {
        return Matrix(i, j, buffer_ptr);
    }

private:
    void decr_buffer() {
        if (buffer_ptr) {
            buffer_ptr->decr_counter();
            if (buffer_ptr->get_counter() == 0) {
                delete buffer_ptr;
                buffer_ptr = nullptr;
            }
        }
    }

public:
    ~Matrix() {
        decr_buffer();
    }
};

int main() {
    Matrix m1(4, 3);
    m1.set(0, 0, 17.2);
    m1.print();

    {
        Matrix m2 = m1.reshape(2, 6);
        m2.set(1, 1, 2025);
        m2.print();
        m1.print();
    }

    Matrix m3 = m1.reshape(6, 2);
    m3.set(0, 0, 2026);

    Matrix m4(2, 4);
    Matrix m5(m4);  
    
    Matrix m6(4, 6);
    Matrix m7(2, 3);
    m6 = m7;        
    return 0;
}