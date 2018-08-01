#pragma once

#include <vector>

#include "Card.h"

class CColumn {

public:
	CColumn();
	~CColumn();
	void AddCard(CCard*);
	void RemoveCard(CCard*);
private:
	std::vector<CCard*>* CardColumn;
};

