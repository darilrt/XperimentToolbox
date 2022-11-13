#include <etb.h>
#include <iostream>
#include <string>

#include "MaterialAssetInspector.h"
#include "EditorCamera.h"
#include "CubeActor.h"
#include "EditorGUI.h"

class PreviewObject : public xtb::Actor {
public:
    xtb::Material* material;

    void Render() {
        xtb::Graphics::DrawMesh(xtb::Primitives::sphere, transform.GetMatrix(), *material);
    }
} *a;

MaterialAssetInspector::MaterialAssetInspector() {
}

void MaterialAssetInspector::Start() {
    if (cam == NULL) cam = scene.Instance<EditorCamera>();
    cam->cam.transform.position = glm::vec3(0, 0, 5.0f);
    
    if (a == NULL) a = scene.Instance<PreviewObject>();
    a->name = "Qbito";
	
	std::string uuid = xtb::AssetDatabase::GetUUIDByPath(resourcePath);
    a->material = xtb::AssetDatabase::GetAssetByUUID<xtb::Material>(uuid);

    scene.Start();
}

void MaterialAssetInspector::GUI() {
    static ImGuiTabBarFlags tableFlags = ImGuiTableFlags_Resizable | 
        ImGuiTableFlags_NoBordersInBodyUntilResize;

    if (ImGui::BeginTable("MaterialEditor", 2, tableFlags))
    {
        ImGui::TableNextColumn();

        EditorGUI::InteractivePreview(NULL, a->material);

        ImGui::TableNextColumn();
        ImGui::Text(resourcePath.stem().string().c_str());

		std::string uuid = "";

        if (a->material->shader) {
            uuid = a->material->shader->GetUUID();
        }

		bool changed = EditorGUI::InputAsset<xtb::Shader>("Shader", uuid);
		
        if (changed) {
			a->material->shader = xtb::Asset::GetAsset<xtb::Shader>(uuid);
            a->material->SaveAsset();
        }
		
        ImGui::Separator();

        if (a->material->shader == NULL) {
			ImGui::EndTable();
			return;
        }

        xtb::Shader& sh = *a->material->shader;
		
        sh.Reload();
        
        if (sh.GetId() != 0) {
            static std::string uuid;
            for (xtb::Uniform& m : sh.GetUniforms()) {
                if (m.name.find("XTB_", 0) == 0 || m.name.find("xtb_", 0) == 0) {
                    continue;
                }

                static float n = 0;
                static bool v = false;
				
                switch (m.type) {
					
                case xtb::Uniform::Bool: ImGui::Checkbox(m.name.c_str(), &v); break;

                case xtb::Uniform::Float: ImGui::DragFloat(m.name.c_str(), &n, 0.01f); break;
                
                case xtb::Uniform::Sampler2D: {
                    xtb::TextureUniformInfo* info = dynamic_cast<xtb::TextureUniformInfo*>(a->material->Get(m.name));

                    std::string newUuid = "";

                    if (info && info->texture) {
                        newUuid = info->texture->GetUUID();
                    }
					
					changed |= EditorGUI::InputAsset<xtb::Texture>(m.name.c_str(), newUuid);
                    
                    if (changed) {
                        xtb::Texture* asset = xtb::Asset::GetAsset<xtb::Texture>(newUuid);
                        a->material->SetTexture(m.name, asset);
                    }

                    break;
                }
				
                default:
                    break;
				
                }
            }
        }
        
		if (changed) {
			a->material->SaveAsset();
		}

        ImGui::EndTable();
    }
}
