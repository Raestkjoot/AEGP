#include "EditorApplication.h"

#include "EditorScene.h"
#include "Logger.h"

EditorApplication::EditorApplication() : Application(512, 512, "Hello") { }

void EditorApplication::Initialize() {
	Logger::Print("Hello, Editor!");
	_curScene = new EditorScene();

	Application::Initialize();
}