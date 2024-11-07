#include "SystemFactory.h"

#include "Logger.h"
#include "ECS/System.h"

std::unique_ptr<System> SystemFactory::GetSystem(const std::string& name) {
	auto system = _systemMap.find(name);
	if (system != _systemMap.end()) {
		return system->second();
	}

	Logger::PrintError("SystemFactory::GetSystem: '{}' not found", name);
	return std::unique_ptr<System>(nullptr);
}

void SystemFactory::RegisterSystem(std::string name, std::function<std::unique_ptr<System>()> builder) {
	_systemMap[name] = builder;
}
