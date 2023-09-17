#pragma once

class Physics {

private:

	double g = -9.8067;
	double earthRadious = 6378000;
	double t = 48;
	double angle;
	double height;
	double dx;
	double dy;
	double ddx;
	double ddy;
	double gH;


	void computeHeight();
	void computeGH();
	void computeDdx();
	void computeDdy();
	void computeDx();
	void computeDy();
	void computeX();
	void computeY();
	void computeNewAngle();

public:
	Physics(double x, double y, double dx, double dy, double angle);
	void computeAll();
	double getX();
	double getY();
	double x;
	double y;
};