#pragma once
class Algorithm {
private:
	static Algorithm* mInstance;

public:
	static Algorithm* GetInstance();
	char* GenBinaryString(int length);
};

