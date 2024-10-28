#pragma once

class Texture {
public:
	void Load(const char* filepath);
	void Use();
	unsigned int GetID() const;

private:
	unsigned int _id;
};