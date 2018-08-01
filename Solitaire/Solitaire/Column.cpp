#include "Column.h"



CColumn::CColumn() {

}


CColumn::~CColumn() {

}

void CColumn::AddCard(CCard* _Card) {
	CardColumn->push_back(_Card);
}

void CColumn::RemoveCard(CCard* _Card) {
	CardColumn->pop_back();
}