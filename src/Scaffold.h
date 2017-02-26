#pragma once

class Scaffold
{
public:
	Scaffold();
	Scaffold(bool, int);
	bool getIsSolid();
	void setIsSolid(bool);
	int getTextureOffset();
	void setTextureOffset(int);
private:
	bool m_IsSolid;
	int m_TextureOffset;
};