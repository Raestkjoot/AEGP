#pragma once

class Texture {
public:
	Texture();

	void Load(const char* filepath);
	void Use();
	unsigned int GetID() const;

private:
	unsigned int _id;
};