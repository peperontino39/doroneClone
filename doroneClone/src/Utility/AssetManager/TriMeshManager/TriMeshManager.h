#pragma once
#include "../../CinderFwd.h"

#include <unordered_map>



class TriMeshManager
{
public:
	TriMeshManager();
	~TriMeshManager();

	void set(std::string, std::string);
	TriMeshRef get(std::string);
	bool isHave(std::string);


	static TriMeshManager & single() {
		static TriMeshManager tri_mesh_manager;
		return tri_mesh_manager;
	}

private:
	std::unordered_map<std::string, TriMeshRef> trimeshs;
};


#define TriMeshs TriMeshManager::single()
