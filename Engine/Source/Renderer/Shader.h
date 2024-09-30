#pragma once

class Shader {
public:
	void Load(const char* vertexPath, const char* fragmentPath);
	void Use();

private:
	unsigned int _id;
};