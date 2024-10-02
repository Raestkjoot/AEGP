#pragma once

class Shader {
public:
	void Load(const char* vertexPath, const char* fragmentPath);
	void Use();
	unsigned int GetID();

private:
	unsigned int _id;
};