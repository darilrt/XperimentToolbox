#pragma once

#include <etb.h>
#include <map>
#include <iostream>
#include <string>

#include "AssetInspector.h"
#include "EditorCamera.h"

class MaterialAssetInspector : public AssetInspector {
public:
	ETB::Scene scene;
	EditorCamera* cam;

	MaterialAssetInspector();
	
	void Start();
	void GUI();
};