
#include "Vector3.h"

using namespace RayTracerSpace;

Vector3::Vector3() {
	this->X = 0;
	this->Y = 0;
	this->Z = 0;
}

Vector3::Vector3(double x, double y, double z) {
	this->X = (float) x;
	this->Y = (float) y;
	this->Z = (float) z;
}

Vector3::~Vector3() {}

Vector3* Vector3::ZERO() { // static
	return new Vector3();
}
Vector3* Vector3::ZEROW() { // static
	Vector3* v = Vector3::ZERO();
	v->Z = 1;
	return v;
}
Vector3* Vector3::plus(Vector3& v1, Vector3& v2) { // static
	return new Vector3(v1.X + v2.X, v1.Y + v2.Y, v1.Z + v2.Z);
}
Vector3& Vector3::plus(Vector3& v) {
	this->X += v.X;
	this->Y += v.Y;
	this->Z += v.Z;
	return *this;
}

Vector3* Vector3::minus(Vector3& v1, Vector3& v2) { // static
	return new Vector3(v1.X - v2.X, v1.Y - v2.Y, v1.Z - v2.Z);
}
Vector3& Vector3::minus(Vector3& v) {
	this->X += v.X;
	this->Y += v.Y;
	this->Z += v.Z;
	return *this;
}
Vector3* Vector3::negate(Vector3& v) { // static
	return new Vector3(-v.X, -v.Y, -v.Z);
}
Vector3& Vector3::negate() {
	this->X = -this->X;
	this->Y = -this->Y;
	this->Z = -this->Z;
	return *this;
}
Vector3* Vector3::scale(Vector3& v, float f) { // static
	return new Vector3(v.X * f, v.Y * f, v.Z * f);
}
Vector3& Vector3::scale(float f) {
	this->X *= f;
	this->Y *= f;
	this->Z *= f;
	return *this;
}
Vector3* Vector3::normalize(Vector3& v) { // static
	float length = v.length();
	return new Vector3(v.X / length, v.Y / length, v.Z / length);
}
Vector3& Vector3::normalize() {
	float length = this->length();
	this->X /= length;
	this->Y /= length;
	this->Z /= length;
	return *this;
}
Vector3* Vector3::cross(Vector3& v1, Vector3& v2) { // static
	float one = v1.Y * v2.Z - v1.Z * v2.Y;
	float two = v1.Z * v2.X - v1.X * v2.Z;
	float thr = v1.X * v2.Y - v1.Y * v2.X;
	return new Vector3(one, two, thr);
}
Vector3& Vector3::cross(Vector3& v) {
	float one = this->Y * v.Z - this->Z * v.Y;
	float two = this->Z * v.X - this->X * v.Z;
	float thr = this->X * v.Y - this->Y * v.X;
	this->X = one; this->Y = two; this->Z = thr;
	return *this;
}
Vector3* Vector3::clamp(Vector3& v, float min, float max) { //static
	return new Vector3(
		std::max(min, std::min(max, v.X)),
		std::max(min, std::min(max, v.Y)),
		std::max(min, std::min(max, v.Z))
	);
}
Vector3& Vector3::clamp(float min, float max) {
	this->X = std::max(min, std::min(max, this->X));
	this->Y = std::max(min, std::min(max, this->Y));
	this->Z = std::max(min, std::min(max, this->Z));
	return *this;
}
Vector3* Vector3::reflect(Vector3& v1, Vector3& v2) { // staic
	Vector3* neg = Vector3::negate(v1);
	Vector3* scaled = Vector3::scale(v2, 2 * v1.dot(v2));
	neg->plus(*scaled);
	free(scaled);
	return neg;
}
Vector3& Vector3::reflect(Vector3& v) {
	Vector3* scaled = Vector3::scale(v, 2 * this->dot(v));
	this->negate();
	this->plus(*scaled);
	free(scaled);
	return *this;
}
Vector3& Vector3::setAt(uint8_t i, float v) {
	switch (i) {
	case 0:
		this->X = v;
		break;
	case 1:
		this->Y = v;
		break;
	case 2:
		this->Z = v;
	}
	return *this;
}
float Vector3::length(Vector3& v) { // static
	return v.length();
}
float Vector3::length() const {
	return (float) sqrt(this->lengthSquared());
}
float Vector3::lengthSquared(Vector3& v) { // static
	return v.lengthSquared();
}
float Vector3::lengthSquared() const {
	return this->X * this->X + this->Y * this->Y + this->Z * this->Z;
}
float Vector3::dot(Vector3& v1, Vector3& v2) { // static
	return v1.dot(v2);
}
float Vector3::dot(Vector3& v) const {
	return this->X * v.X + this->Y * v.Y + this->Z * v.Z;
}
bool Vector3::equals(Vector3& v1, Vector3& v2) { // static
	return v1.equals(v2);
}
bool Vector3::equals(Vector3& v) const {
	return this->X == v.X && this->Y == v.Y && this->Z == v.Z;
}
float Vector3::absoluteDifference(Vector3& v1, Vector3& v2) { // static
	return v1.absoluteDifference(v2);
}
float Vector3::absoluteDifference(Vector3& v) const {
	return abs(this->X - v.X) + abs(this->Y - v.Y) + abs(this->Z - v.Z);
}
bool Vector3::nearlyEquals(Vector3& v1, Vector3& v2) { // static
	return v1.nearlyEquals(v2);
}
bool Vector3::nearlyEquals(Vector3& v) const {
	return this->absoluteDifference(v) < 0.0001;
}
Vector3 Vector3::fromVector2(Vector2 v2) {
	return Vector3(v2.X, v2.Y, 0);
}
//float* Vector3::asArray() {
//	float arr[3] = { this->X, this->Y, this->Z };
//	return arr; // returning local var
//}
float Vector3::at(uint8_t i) const {
	return i == 0
		? this->X
		: (i == 1
			? this->Y
			: this->Z);
}
float Vector3::getW() const {
	return this->Z;
}
void Vector3::setW(float w) {
	this->Z = w;
}
