/*

implement a hierarchy of classes for arithmetic expression manipulations:
    - the classes holds, evaluates and prints arithmetic expressions
    - print in infix, prefix or postfix notation

Additional work:
   - note that the postfix notation is also called Reverse Polish notation (RPN)
   - it is a mathematical notation in which operators follow their operands
   - this notation does not need any parentheses i.e. this notation is non ambigu
   - => you can read (easily) RPN expressions using a stacks
  implement a code to read RPN expression and store them with your class objects
  RPN arithmetic expression are passed as main command-line arguments

./main 87 12 - + 75 -
*/
#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

//classe de base
class Expr {
public : 
    virtual ~Expr() {} //destructeur virtuel
    virtual double eval() const = 0;
    virtual void print() const = 0;
};

class Constant : public Expr {
    double val;
public : 
    Constant(double v) : val(v) {}
    double eval() const {return val;}
    void print() const {std::cout<<val;}

};

class UnaryMinus : public Expr {
    const Expr& exp;
public : 
    UnaryMinus(const Expr& e) : exp(e) {}
    double eval() const {
        return -exp.eval();
    }
    void print() const {
        exp.print();
        std::cout<<" -",
    }
 };

 //classe pr l'addidtion
 class Plus : public Expr {
    const Expr& g;
    const Expr& d;
public:
    //constructeur
    Plus(const Expr& gauche, const Expr& droite) : g(gauche), d(droite) {}

    double eval() const {
        return g.eval() + d.eval();
    }
    void print() const {
        g.print();
        std::cout << " ";
        d.print();
        std::cout << " +";
    }
};

//classe pr la soustraction
class Minus : public Expr {
    const Expr& g;
    const Expr& d;
public:
    Minus(const Expr& gauche, const Expr& droite) : g(gauche), d(droite) {}
    double eval() const {
        return g.eval() - d.eval();
    }
    void print() const {
        g.print();
        std::cout << " ";
        d.print();
        std::cout << " -";
    }
};

//classe pr la division
class Divide : public Expr {
    const Expr& g;
    const Expr& d;
public:
    Divide(const Expr& gauche, const Expr& droite) : g(gauche), d(droite) {}
    double eval() const {
        return g.eval() / d.eval();
    }
    void print() const {
        g.print();
        std::cout << " ";
        d.print();
        std::cout << " /";
    }
};

int main()
{
    try
    {
        // Constant c1(12), c2(-87), c3(23); // try it (-87 is not an unsigned int)
        Constant c1(12), c2(87), c3(75);

        c1.print(); // affiche 12
        std::cout << std::endl;
        std::cout << "eval " << c1.eval() << std::endl; // affiche 12

        UnaryMinus u1(c1);
        u1.print(); // affiche 12 -
        std::cout << std::endl;
        std::cout << "eval " << u1.eval() << std::endl; // affiche -12

        Plus p1(c2, u1);
        p1.print(); // affiche 87 12 -+
        std::cout << std::endl;
        std::cout << "eval " << p1.eval() << std::endl; // affiche 75

        Minus m1(p1, c3);
        m1.print(); // 87 12 -+75 -
        std::cout << std::endl;
        std::cout << "eval " << m1.eval() << std::endl; // affiche 0

        Divide d1(p1, m1);
        std::cout << std::endl;
        std::cout << d1.eval() << std::endl; // throws an instance of 'std::runtime_error'

        std::vector<Expr**> expr;
        expr.push_back(&c1);
        expr.push_back(&u1);
        // parcourez le vecteur
        for (Expr* e : expr) {
            e->print();
            std::cout<<" = "<<e->eval()<<std::endl;
        }
    }
    catch (std::runtime_error &e)
    {
        // affiche zero divide error
        std::cout << e.what() << std::endl;
    }
    return 0;
}
