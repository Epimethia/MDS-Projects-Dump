#include "CThread.h"



CThread::CThread() {
	//Constructor
}


CThread::~CThread() {
	//Destructor
}

void CThread::ThreadFunction(ThreadType _Type) {
	if (_Type == IMAGE) {
		//Clear buffer
		//Do image thread processing here
	} else {
		//Sound thread processing here
	}
}
