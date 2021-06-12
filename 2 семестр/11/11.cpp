#include <iostream>
#include <cmath>
using namespace std;
namespace Geometry {
	namespace d_3 {
		class Point { //класс точек 
		public:
			double x;
			double y;
			double z;
			Point(double v1, double v2, double v3) {
				x = v1;
				y = v2;
				z = v3;
			}
			Point(double v1, double v2) {
				x = v1;
				y = v2;
				z = 0;
			}
			Point(double v1) {
				x = v1;
				y = 0;
				z = 0;
			}
			Point() {
				x = 0;
				y = 0;
				z = 0;
			}
			Point& operator=(Point& A) {
				x = A.x;
				y = A.y;
				z = A.z;
				return *this;
			}
			Point& operator+(Point& A) { // сумма 2х точек
				x = x + A.x;
				y = y + A.y;
				z = z + A.z;
				return *this;
			}
		};
		double d(Point& A, Point& B) { // вычислление расстояния между точками 
			return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y) + (A.z - B.z) * (A.z - B.z));
		}
		double sp(Point& A, Point& B) { // скалярное произведение
			return (A.x * B.x + A.y * B.y + A.z * B.z);
		}
		class Straight_3_d {
		public:
			Point A; 
			Point B;
			double length;
			Straight_3_d(Point& C, Point& D) {
				length = d(C, D);
				A = C;
				B = D;
			}
			friend std::ostream& operator<<(std::ostream& out, const Straight_3_d& S) { //вывод прямой в каноническом виде
				if ((S.A.x > 0)&&(S.A.y>0)&&(S.A.z>0)) out << "(x-" << S.A.x << ")/(" << S.B.x +S.A.x<<")"<< "="<< "(y-" << S.A.y << ")/(" << S.B.y + S.A.y << ")" << "=" << "(z-" << S.A.z << ")/(" << S.B.z+ S.A.z << ")" << '\n' ;
				else if ((S.A.x < 0) && (S.A.y > 0) && (S.A.z > 0)) out << "(x+" << -S.A.x << ")/(" << S.B.x + S.A.x << ")" << "=" << "(y-" << S.A.y << ")/(" << S.B.y + S.A.y << ")" << "=" << "(z-" << S.A.z << ")/(" << S.B.z + S.A.z << ")" << '\n';
				else if ((S.A.x > 0) && (S.A.y < 0) && (S.A.z > 0)) out << "(x-" << S.A.x << ")/(" << S.B.x + S.A.x << ")" << "=" << "(y+" << -S.A.y << ")/(" << S.B.y + S.A.y << ")" << "=" << "(z-" << S.A.z << ")/(" << S.B.z + S.A.z << ")" << '\n';
				else if ((S.A.x > 0) && (S.A.y > 0) && (S.A.z < 0)) out << "(x-" << S.A.x << ")/(" << S.B.x + S.A.x << ")" << "=" << "(y-" << S.A.y << ")/(" << S.B.y + S.A.y << ")" << "=" << "(z+" << -S.A.z << ")/(" << S.B.z + S.A.z << ")" << '\n';
				else if ((S.A.x < 0) && (S.A.y < 0) && (S.A.z > 0)) out << "(x+" << -S.A.x << ")/(" << S.B.x + S.A.x << ")" << "=" << "(y+" << -S.A.y << ")/(" << S.B.y + S.A.y << ")" << "=" << "(z-" << S.A.z << ")/(" << S.B.z + S.A.z << ")" << '\n';
				else if ((S.A.x < 0) && (S.A.y > 0) && (S.A.z < 0)) out << "(x+" << -S.A.x << ")/(" << S.B.x + S.A.x << ")" << "=" << "(y-" << S.A.y << ")/(" << S.B.y + S.A.y << ")" << "=" << "(z+" << -S.A.z << ")/(" << S.B.z + S.A.z << ")" << '\n';
				else if ((S.A.x > 0) && (S.A.y < 0) && (S.A.z < 0)) out << "(x-" << S.A.x << ")/(" << S.B.x + S.A.x << ")" << "=" << "(y+" << -S.A.y << ")/(" << S.B.y + S.A.y << ")" << "=" << "(z+" << -S.A.z << ")/(" << S.B.z + S.A.z << ")" << '\n';
				else if ((S.A.x < 0) && (S.A.y > 0) && (S.A.z < 0)) out << "(x+" << -S.A.x << ")/(" << S.B.x + S.A.x << ")" << "=" << "(y+" << -S.A.y << ")/(" << S.B.y + S.A.y << ")" << "=" << "(z+" << -S.A.z << ")/(" << S.B.z + S.A.z << ")" << '\n';
				return out;
			}
		};
		class Plane { //класс плоскостей 
		public:
			Point A;
			Point B;
			Point C;
			double a,b,c,d;
			Plane(Point& X, Point& Y, Point& Z) {
				A = X;
				B = Y;
				C = Z;
				a = ((B.y - A.y) * (C.z - A.z) - (C.y - A.y) * (B.z - A.z));
				b = -((B.x - A.x) * (C.z - A.z) - (C.x - A.x) * (B.z - A.z));
				c = ((B.x - A.x) * (C.y - A.y) - (C.x - A.x) * (B.y - A.y));
				d = -A.x * a - A.y * b - A.z * c;
			}
			friend std::ostream& operator<<(std::ostream& out, const Plane& P) {
				if (P.d > 0) out <<"("<<P.a<<")x+("<<P.b<<")y+"<<P.c<<")z+"<<P.d<<"=0" << '\n';
				else out << "(" << P.a << ")x+(" << P.b << ")y+(" << P.c << ")z" << P.d << "=0" << '\n';
				return out;
			}
		};
		namespace d_2 {
			double l(Point& A, Point& B) { // вычислление расстояния между точками на плоскости
				return sqrt((A.x - B.x) * (A.x - B.x) + (A.y - B.y) * (A.y - B.y));
			}
			class Straight_2_d { //прямая на плоскости
			public:
				double k;
				double b;
				double length;
				Straight_2_d(Point& A, Point& B) {
					length = l(A, B);
					k = (A.y - B.y) / (A.x - B.x);
					b = B.y - k * B.x;
				}
				friend std::ostream& operator<<(std::ostream& out, const Straight_2_d& A) {
					if (A.b > 0) out << "y=" << A.k << "x+" << A.b << '\n';
					else out << "y=" << A.k << "x" << A.b << '\n';
					return out;
				}
			};
			double tg(Straight_2_d& A, Straight_2_d& B) { //тангенс угла между двумя прямыми на плоскости
				return ((A.k - B.k) / (1 + A.k * B.k));
			}
			namespace d_1 {
				class Segment { // класс отрезков
				public:
					Point A;
					Point B;
					double lenght;
					Segment(Point& C, Point& D) {
						A = C;
						B = D;
						lenght = abs(A.x-B.x);
					}
				};
				Segment& operator+(Segment& L, Segment& M) { // сумма 2х отрезков 
					Segment C(L.A+M.A, L.B+M.B);
					return C;
				}
				namespace d_0 {
					class Point { //класс точек-значений
					public:
						double x;
						Point(double a) {
							x = a;
						}
						bool same(Point& A, Point& B) {
							return A.x == B.x;
						}
						friend std::ostream& operator<<(std::ostream& out, const Point& P) {
							out << "Value is " << P.x << '\n';
								return out;
						}
					};
				}
			}
		}
	}
}
int main() {
	Geometry::d_3::Point A(3.4, 6, -9.7);
	Geometry::d_3::Point B(7, 8.5, 5);
	std::cout<<Geometry::d_3::d(A,B)<<'\n';
	Geometry::d_3::Point C;
	C = A;
	C + B;
	std::cout << C.x<<'\n';
	std::cout << Geometry::d_3::sp(A, B) << '\n';
	Geometry::d_3::d_2::Straight_2_d L(A,B);
	std::cout << L;
	Geometry::d_3::Straight_3_d M(A, B);
	std::cout<<M;
	Geometry::d_3::Plane P(A,B,C);
	std::cout << P;
	Geometry::d_3::d_2::d_1::d_0:: Point K(d(A, B));
	std::cout << K;
}