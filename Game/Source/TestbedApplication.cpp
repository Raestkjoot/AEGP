#include "TestbedApplication.h"

#include "Logger.h"

TestbedApplication::TestbedApplication() : Application(512, 512, "Hello") {

}

void TestbedApplication::Initialize() {
	Logger::Print("Hello, world!");
}

void TestbedApplication::Update() {
	
}

void TestbedApplication::Render() {
	Application::Render();
}

void TestbedApplication::Cleanup() {

}