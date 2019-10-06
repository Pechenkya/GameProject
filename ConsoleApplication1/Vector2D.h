#pragma once
#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <math.h>
#include <iomanip>

//Class for battlefield. Movement
struct NormalizedVec
{
	float pos_x{};
	float pos_y{};

	NormalizedVec(float pos_xi, float pos_yi);

	bool operator==(const NormalizedVec & v2);
};

class Vector2D  //�������� � Character

{
	//Info about position on Battle Field
private:
	int pos_x{ 0 };
	int pos_y{ 0 };
	//Movements methods
public:
	//Movement commands
	Vector2D();
	Vector2D(int X, int Y);
	//Distance parametres
	int get_pos_x();
	int get_pos_y();
	double get_distance(int position_x, int position_y);

	double get_distance();

	NormalizedVec get_normalized_vec(Vector2D destination);

	Vector2D operator+(const Vector2D & v2);
	Vector2D operator-(const Vector2D & v2);

	bool operator<=(const Vector2D & v2);
	bool operator>=(const Vector2D & v2);
	bool operator==(const Vector2D & v2);
	//void operator=(const Vector2D && v2);
	//void operator=(const Vector2D & v2);
	//void operator=(const Vector2D  v2);
	//Vector2D(Vector2D & vec_in);
	//Vector2D(Vector2D && vec_in);
};

#endif // VECTOR2D_H
