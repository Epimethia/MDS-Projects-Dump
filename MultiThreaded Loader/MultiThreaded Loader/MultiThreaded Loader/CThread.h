#pragma once

enum ThreadType {
	IMAGE,
	SOUND
};

class CThread {
	public:
		CThread();
		~CThread();

		void ThreadFunction(ThreadType _ThreadType);
	private:
		
};

