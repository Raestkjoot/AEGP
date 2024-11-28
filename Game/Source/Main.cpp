#include "PrototypeApplication.h"

#include "TestLevelGeneration.h"

int main() {
	TestLevelGeneration test;
	test.GenerateLevel();

	PrototypeApplication prototype;
	prototype.Run();
}