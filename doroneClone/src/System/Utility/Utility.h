#pragma once
#include "../CinderFwd.h" 

void drawGrid(float size, float step);

//�K�w�Ȃ��̃t�@�C����
std::string FileName(const std::string& _path);

//�g���q�Ȃ��t�@�C����
std::string NonExtensionFileName(const std::string& _path);

ci::Vec3f JtoVec3f(ci::JsonTree& _json);

