#include "CollisionManager.h"

CollisionManager::CollisionManager()
{
}


CollisionManager::~CollisionManager()
{
}

vector<POINT> CollisionManager::getAxies(Subject* su)
{
	vector<POINT> axies;
	int count = su->getIcount();
	POINT* apt = (POINT*)malloc(count * sizeof(POINT));
	su->getApt(apt);

	for ( int i = 0; i < count-1;  i++)
	{
		POINT axie;
		int edge_x = apt[i + 1].x - apt[i].x;
		int edge_y = apt[i + 1].y - apt[i].y;
		axie.x = edge_y;
		axie.y = -edge_x;
		axies.push_back(axie);
	}
	POINT axie;
	int edge_x = apt[count-1].x - apt[0].x;
	int edge_y = apt[count - 1].y - apt[0].y;
	axie.x = edge_y;
	axie.y = -edge_x;
	axies.push_back(axie);
	delete apt;
	return axies;
}
vector<int> CollisionManager::getProjectionsOn(POINT axis, Subject* su1, Subject* su2)
{
	int count1 = su1->getIcount();
	POINT* apt1 = (POINT*)malloc(count1 * sizeof(POINT));
	su1->getApt(apt1);
	POINT offset = su1->getOffset();
	for (int i = 0; i<count1; i++)
	{
		apt1[i].x = apt1[i].x + offset.x;
		apt1[i].y = apt1[i].y + offset.y;
		Util::myprintf(L"temp[%d].x:%d,temp[%d].x:%d\n", i, apt1[i].x, i, apt1[i].y);
	}


	int count2 = su2->getIcount();
	POINT* apt2 = (POINT*)malloc(count2 * sizeof(POINT));
	su2->getApt(apt2);
	offset = su2->getOffset();
	for (int i = 0; i<count2; i++)
	{
		apt2[i].x = apt2[i].x + offset.x;
		apt2[i].y = apt2[i].y + offset.y;
		Util::myprintf(L"temp[%d].x:%d,temp[%d].x:%d\n", i, apt2[i].x, i, apt2[i].y);
	}

	vector<int> projections;
	int n0, n1;
	n0 = axis.x*apt1[0].x + axis.y*apt1[0].y;
	n1 = axis.x*apt1[1].x + axis.y*apt1[1].y;
	if (n0 <= n1)
	{
		projections.push_back(n0);
		projections.push_back(n1);
	}
	if (n0 > n1)
	{
		projections.push_back(n1);
		projections.push_back(n0);
	}
	for (int  i = 2; i < count1; i++)
	{
		int n = axis.x*apt1[i].x + axis.y*apt1[i].y;
		if (n < projections.at(0))
		{
			projections[0] = n;
		}
		if (n > projections.at(1))
		{
			projections[1] = n;
		}
	}

	n0 = axis.x*apt2[0].x + axis.y*apt2[0].y;
	n1 = axis.x*apt2[1].x + axis.y*apt2[1].y;
	if (n0 <= n1)
	{
		projections.push_back(n0);
		projections.push_back(n1);
	}
	if (n0 > n1)
	{
		projections.push_back(n1);
		projections.push_back(n0);
	}
	for (int i = 2; i < count1; i++)
	{
		int n = axis.x*apt2[i].x + axis.y*apt2[i].y;
		if (n < projections.at(2))
		{
			projections[2] = n;
		}
		if (n > projections.at(3))
		{
			projections[3] = n;
		}
	}
	delete apt1;
	delete apt2;
	return projections;
}
bool CollisionManager::isCollision(Subject* su1, Subject* su2)
{
	vector<POINT> axies = getAxies(su1);
	vector<POINT> axies2 = getAxies(su2);
	axies.insert(axies.end(),axies2.begin(),axies2.end());

	
	for (int i = 0; i < axies.size(); i++)
	{
		vector<int> projections;
		projections = getProjectionsOn(axies.at(i), su1, su2);
		if (projections.at(0) > projections.at(3) || projections.at(1) < projections.at(2))
			return false;
	}
	return true;
}

void CollisionManager::addSubject(Subject* su)
{
	subjects.push_back(su);
}
void CollisionManager::checkCollision()
{
	for (int i = 0; i < subjects.size()-1; i++)
	{
		for (int j = i+1; j < subjects.size();j++)
		{
			if (isCollision(subjects.at(i), subjects.at(j)))
			{
				onCollision(subjects.at(i), subjects.at(j));
			}
		}
	}
}
void CollisionManager::onCollision(Subject* su1, Subject* su2)
{
	su1->setColor(RGB(0,255,0));
	su2->setColor(RGB(0, 255, 0));
}