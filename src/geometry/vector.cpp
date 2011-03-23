/**
 * This code is part of libcity library.
 *
 * @file geometry/vector.cpp
 * @date 05.03.2011
 * @author Radek Pazdera (xpazde00@stud.fit.vutbr.cz)
 *
 * @see geometry/vector.h
 *
 */

#include "vector.h"
#include "units.h"

#include "point.h"
#include "../debug.h"

#include <sstream>
#include <cmath>

Vector::Vector()
  : xDirection(0.0), yDirection(0.0), zDirection(0.0)
{}

Vector::Vector(double x)
  : xDirection(x), yDirection(0.0), zDirection(0.0)
{}

Vector::Vector(double x, double y)
  : xDirection(x), yDirection(y), zDirection(0.0)
{}

Vector::Vector(double x, double y, double z)
  : xDirection(x), yDirection(y), zDirection(z)
{}

Vector::~Vector()
{}

double Vector::x() const
{
  return xDirection;
}

double Vector::y() const
{
  return yDirection;
}

double Vector::z() const
{
  return zDirection;
}

void Vector::setX(double coordinate)
{
  xDirection = coordinate;
}

void Vector::setY(double coordinate)
{
  yDirection = coordinate;
}

void Vector::setZ(double coordinate)
{
  zDirection = coordinate;
}

void Vector::rotateAroundX(double degrees)
{
  double radians = degrees * (libcity::PI/180.0);
  double newX, newY, newZ;

  newX = 1.0*xDirection;
  newY = yDirection*cos(radians) - zDirection*sin(radians);
  newZ = yDirection*sin(radians) + zDirection*cos(radians);

  xDirection = newX;
  yDirection = newY;
  zDirection = newZ;
}

void Vector::rotateAroundY(double degrees)
{
  double radians = degrees * (libcity::PI/180.0);
  double newX, newY, newZ;

  newX = zDirection*sin(radians) + xDirection*cos(radians);
  newY = 1.0*yDirection;
  newZ = zDirection*cos(radians) - xDirection*sin(radians);

  xDirection = newX;
  yDirection = newY;
  zDirection = newZ;
}

void Vector::rotateAroundZ(double degrees)
{
  double radians = degrees * (libcity::PI/180.0);
  double newX = 0.0,
         newY = 0.0,
         newZ = 0.0;

  newX = xDirection*cos(radians) - yDirection*sin(radians);
  newY = xDirection*sin(radians) + yDirection*cos(radians);
  newZ = 1.0*zDirection;

  xDirection = newX;
  yDirection = newY;
  zDirection = newZ;
}

void Vector::normalize()
{
  double vectorLength = length();

  xDirection /= vectorLength;
  yDirection /= vectorLength;
  zDirection /= vectorLength;
}

double Vector::length()
{
  return sqrt(xDirection*xDirection + yDirection*yDirection + zDirection*zDirection);
}

void Vector::set(double xCoord, double yCoord, double zCoord)
{
  xDirection = xCoord;
  yDirection = yCoord;
  zDirection = zCoord;
}

std::string Vector::toString()
{
  std::stringstream convertor;
  convertor << "Vector(" << xDirection << ", " << yDirection << ", " << zDirection << ")";
  return convertor.str();
}

bool   Vector::operator==(Vector second)
{
  return (xDirection - second.x()) < libcity::EPSILON &&
         (yDirection - second.y()) < libcity::EPSILON &&
         (zDirection - second.z()) < libcity::EPSILON;
}

Vector Vector::operator*(double constant)
{
  return Vector(constant*xDirection, constant*yDirection, constant*zDirection);
}

Vector Vector::operator/(double constant)
{
  return Vector(xDirection/constant, yDirection/constant, zDirection/constant);
}

Vector Vector::operator+(Vector vector)
{
  return Vector(xDirection + vector.x(), yDirection + vector.y(), zDirection + vector.z());
}

Vector::Vector(Point const& first, Point const& second)
{
  xDirection = second.x() - first.x();
  yDirection = second.y() - first.y();
  zDirection = second.z() - first.z();
}