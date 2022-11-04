#pragma once

#include <string>
#include <etb.h>

class Resource {

};

namespace EditorGUI {
	
	void InteractivePreview(xtb::Mesh* mesh, xtb::Material& material);

	void InputResource(const std::string& label, Resource* resource);

}
	