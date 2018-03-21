#include"Matrix.h"
#include"Matrix.h"
#include<fstream>
#include<cstdlib>

void error(const char*p, const char* p2 = ""){ 
    std::cerr << "Error: " << p << ' ' << p2 << '\n';
    getchar();
    std::exit(1);
}

int main() {
    char file_name[] = "Matrices.txt";
    std::ifstream fin(file_name);
    if (!fin) error("output file does not open", file_name);

    SquareMatrix a, b, c, d;
    fin >> a >> b >> c >> d;
    std::cout << "a:\n" << a << "b:\n" << b << "c:\n"  << c << "d:\n" << d;
    std::cout << "det(a):\n" << det(a) << '\n';
    std::cout << "inv(a):\n" << inv(a) << '\n';
    std::cout << "inv(a) * a:\n" << inv(a) * a << '\n';
    a = a * a;
    std::cout << "a = a * a:\n" << a << '\n';
    b = c * 4;
    std::cout << "b = c * 4:\n" << b << '\n';
    b *= 4;
    std::cout << "b *= 4:\n" << b << '\n';
    b = 4 * d;
    std::cout << "b = 4 * d:\n" << b << '\n';
    d = -d;
    std::cout << "d -= d:\n" << d << '\n';
    b -= b;
    std::cout << "b -= b:\n" << b << '\n';
    c = c + c - c;
    a = a + a;
    a += a;
    std::cout << "IsConcerted(a, b):\n" << IsConcerted(a, b, "addition") << '\n';
    std::cout << "c:\n" << c << '\n';
    std::cout << "tranaspose(c):\n" << trans(c) << '\n';

    std::cout << "a:\n" << a << '\n';
    a(0, 0) = 4;
    std::cout << "a(0, 0) = 4:\n" << a << '\n';
    double q = a(0, 1);
    std::cout << "q = a(0, 3) = " << q << "\n\n";
    SquareMatrix x, y, z;
    x(0, 0) = 5;
    y(0, 0) = 6;
    x = y;
    std::cout << "x = y:\n" << x << '\n';
    z = x + y;
    std::cout << "z = x + y:\n" << z << '\n';
    
    std::cout << "det(a):\n" << det(a) << '\n';

    std::cout << "\nPut \"Enter\" for exit\n";
    getchar();
    return 0;
}