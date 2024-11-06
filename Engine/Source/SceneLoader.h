#pragma once

#include <string>

class SystemFactory;
class ComponentFactory;
class Scene;

class SceneLoader {
public:
	SceneLoader(SystemFactory* systemFactory, ComponentFactory* componentFactory);

	Scene LoadScene(std::string filename);

private:
	SystemFactory* _systemFactory;
	ComponentFactory* _componentFactory;
};