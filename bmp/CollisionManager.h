#pragma once
#include "Poly.h"
class CollisionManager
{
	vector<Subject*> subjects;
public:
	CollisionManager();
	~CollisionManager();

	vector<POINT> getAxies(Subject*);
	vector<int> getProjectionsOn(POINT axis, Subject* su1, Subject* su2);
	bool isCollision(Subject*, Subject*);
	void addSubject(Subject* su1);
	void checkCollision();
	void onCollision(Subject* su1, Subject* su2);
};

