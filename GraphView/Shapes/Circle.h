#pragma once

class Circle
{
public:
	Circle(const int radius) : m_radius{ radius } {}

	int radius() const { return m_radius; }
private:
	int m_radius;
};