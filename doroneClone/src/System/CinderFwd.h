#pragma once
#include "cinder/Cinder.h"


namespace cinder {
	namespace params {
		class InterfaceGl;
		typedef std::shared_ptr<InterfaceGl> InterfaceGlRef;
	}

	template<typename T>
	class Vec2;
	template<typename T>
	class Vec3;
	template<typename T>
	class Vec4;

	typedef Vec2<int>		Vec2i;
	typedef Vec2<float>		Vec2f;
	typedef Vec2<double>	Vec2d;
	typedef Vec3<int>		Vec3i;
	typedef Vec3<float>		Vec3f;
	typedef Vec3<double>	Vec3d;
	typedef Vec4<int>		Vec4i;
	typedef Vec4<float>		Vec4f;
	typedef Vec4<double>	Vec4d;
	
	class Ray;
	class AxisAlignedBox3f;
	class Sphere;

	template< typename T >
	class Matrix44;
	typedef Matrix44<float>	 Matrix44f;
	typedef Matrix44<double> Matrix44d;
	
	template< typename T >
	class Matrix33;
	typedef Matrix33<float>	 Matrix33f;
	typedef Matrix33<double> Matrix33d;

	template< typename T >
	class Matrix22;
	typedef Matrix22<float>	 Matrix22f;
	typedef Matrix22<double> Matrix22d;

	template<typename T>
	class Quaternion;
	typedef Quaternion<float>	Quatf;
	typedef Quaternion<double>	Quatd;

	template<typename T>
	class ColorT;

	typedef ColorT<float>		Color;
	typedef ColorT<float>		Colorf;
	typedef ColorT<uint8_t>		Color8u;
	template<typename T>
	class ColorAT;
	typedef ColorAT<float>		ColorA;
	typedef ColorAT<float>		ColorAf;
	typedef ColorAT<uint8_t>	ColorA8u;

	class CameraPersp;
	class TriMesh;
	namespace gl {
		class Texture;
		class Material;
		class Light;
		typedef std::shared_ptr<Texture>	TextureRef;
	}
	namespace app {
		class MouseEvent;
		class KeyEvent;
		class FileDropEvent;
		class TouchEvent;
	}
	class MayaCamUI;
	class JsonTree;
}

class GameObject;
typedef std::shared_ptr<ci::TriMesh>	TriMeshRef;
typedef std::shared_ptr<GameObject> GameObjectRef;
typedef std::shared_ptr<ci::gl::Material> MaterialRef;