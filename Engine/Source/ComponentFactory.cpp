#include "ComponentFactory.h"

#include "Logger.h"

void ComponentFactory::GetComponent(const std::string& name) {
	Logger::Print("Get Component {}", name);
}