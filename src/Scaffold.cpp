#include "Scaffold.h"

Scaffold::Scaffold() : m_IsSolid(false),
m_TextureOffset(0) {}

Scaffold::Scaffold(bool isSolid, int offset)
	: m_IsSolid(isSolid),
	m_TextureOffset(offset) {}

bool Scaffold::getIsSolid() { return m_IsSolid; }
void Scaffold::setIsSolid(bool solid) {
	m_IsSolid = solid;
}
int Scaffold::getTextureOffset() { return m_TextureOffset; }
void Scaffold::setTextureOffset(int offset) {
	m_TextureOffset = offset;
}