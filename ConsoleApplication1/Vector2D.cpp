#include "Vector2D.h" //MatveyPidor

Vector2D::Vector2D() : Vector2D(0, 0) {};

Vector2D::Vector2D(int X, int Y)
{
	pos_x = X;
	pos_y = Y;
}


//For everyone
int Vector2D::get_pos_x()
{
	return this->pos_x;
}

int Vector2D::get_pos_y()
{
	return this->pos_y;
}

double Vector2D::get_distance(int position_x, int position_y)
{
	return sqrt(pow((position_x - pos_x), 2) + pow((position_y - pos_y), 2));
}

double Vector2D::get_distance()
{
	return sqrt(pow((pos_x), 2) + pow((pos_y), 2));
}

NormalizedVec Vector2D::get_normalized_vec(Vector2D destination)
{
	float length;
	float invlength;

	length = this->get_distance(destination.get_pos_x(), destination.get_pos_y());
	invlength = 1 / length;

	return NormalizedVec(invlength*(abs(destination.get_pos_x() - pos_x)), invlength*(abs(destination.get_pos_y() - pos_y)));
}

Vector2D Vector2D::operator+(const Vector2D & v2)
{
	Vector2D result_vec = *this;
	result_vec.pos_x += v2.pos_x;
	result_vec.pos_y += v2.pos_y;

	return result_vec;
}

Vector2D Vector2D::operator-(const Vector2D & v2)
{
	Vector2D result_vec = *this;
	result_vec.pos_x -= v2.pos_x;
	result_vec.pos_y -= v2.pos_y;

	return result_vec;
}

bool Vector2D::operator<=(const Vector2D & v2)
{
	if (this->pos_x <= v2.pos_x && this->pos_y <= v2.pos_y)
		return true;
	return false;
}

bool Vector2D::operator>=(const Vector2D & v2)
{
	if (this->pos_x >= v2.pos_x && this->pos_y >= v2.pos_y)
		return true;
	return false;
}

bool Vector2D::operator==(const Vector2D & v2)
{
	return (this->pos_x == v2.pos_x && this->pos_y == v2.pos_y);
}

NormalizedVec::NormalizedVec(float pos_xi, float pos_yi)
{
	pos_x = pos_xi;
	pos_y = pos_yi;
}

bool NormalizedVec::operator==(const NormalizedVec & v2)
{
	float x1 = this->pos_x;
	float y1 = this->pos_y;
	float x2 = v2.pos_x;
	float y2 = v2.pos_y;

	x1 = x1 * 100;
	y1 = y1 * 100;
	x2 = x2 * 100;
	y2 = y2 * 100;

	if (abs(x1 - x2) <= 12 && abs(y1 - y2) <= 12) return true;
	else return false;

}
