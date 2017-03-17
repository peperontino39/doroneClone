#pragma once
#include "../CinderFwd.h" 

void drawGrid(float size, float step);

//階層なしのファイル名
std::string FileName(const std::string& _path);

//拡張子なしファイル名
std::string NonExtensionFileName(const std::string& _path);

ci::Vec3f JtoVec3f(ci::JsonTree& _json);

ci::Matrix44f getLookMatrix(const ci::Vec3f& vec);

ci::Matrix44f getLookMatrixY(const ci::Vec3f& vec);

void drawQuad(const ci::Vec2f&, const ci::Vec2f&);



