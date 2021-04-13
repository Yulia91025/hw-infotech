#pragma once
class A{
int a;
double b;
char c;
long long d;
public:
A(int x, double y, char t, long long z) : a(x),b(y),c(t), d(z) {
	get_a();
	put_a(x);
	get_b();
	put_b(y);
	get_c();
	put_c(t);
	get_d();
	put_d(z);
}
 int get_a() {
 return a;
 }
void put_a(int x) {
  a = x;
}
int get_b() {
	return b;
}
void put_b(int y) {
	b = y;
} int get_c() {
	return c;
}
void put_c(int t) {
	c = t;
} int get_d() {
	return d;
}
void put_d(int z) {
	d = z;
}
};