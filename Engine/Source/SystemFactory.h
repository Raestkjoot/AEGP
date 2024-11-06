#pragma once

#include "ECS/System.h"

#include <memory>
#include <string>
#include <map>

class SystemFactory {
public:
	std::unique_ptr<System> GetSystem(const std::string& name);

	void RegisterSystem(std::string name, std::function<std::unique_ptr<System>()> builder);

private:
	std::map<std::string, std::function<std::unique_ptr<System>()>> _systemMap;
};