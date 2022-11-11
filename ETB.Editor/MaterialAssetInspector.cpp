#include <etb.h>
#include <iostream>
#include <string>

#include "MaterialAssetInspector.h"
#include "EditorCamera.h"
#include "CubeActor.h"
#include "EditorGUI.h"
#include "ShaderAsset.h"

class PreviewObject : public xtb::Actor {
public:
    xtb::Material material;

    void Render() {
        xtb::Graphics::DrawMesh(xtb::Primitives::sphere, transform.GetMatrix(), material);
    }
} *a;

MaterialAssetInspector::MaterialAssetInspector() {
}

void MaterialAssetInspector::Start() {
    if (cam == NULL) cam = scene.Instance<EditorCamera>();
    cam->cam.transform.position = glm::vec3(0, 0, 5.0f);
    
    if (a == NULL) a = scene.Instance<PreviewObject>();
    a->name = "Qbito";
    a->material.LoadFromFile(resourcePath.string());

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

		static std::string uuid = "";
        EditorGUI::InputAsset<xtb::ShaderAsset>("Shader", uuid);
		
        ImGui::Separator();

        xtb::Shader& sh = *a->material.shader;
        
        /*
        if (ImGui::Button("Edit Shader")) {
            system(("start \"C:\\Program Files (x86)\\Notepad++\\notepad++.exe\" " + sh.GetPath()).c_str());
        }
        */

        sh.Reload();
        
        if (sh.GetId() != 0) {
            static std::string uuid;
            for (xtb::Uniform& m : sh.GetUniforms()) {
                if (m.name.find("XTB_", 0) == 0 || m.name.find("xtb_", 0) == 0) {
                    continue;
                }

                static float n = 0;
                static bool v = false;
                switch (m.type)
                {
                case xtb::Uniform::Bool: ImGui::Checkbox(m.name.c_str(), &v); break;

                case xtb::Uniform::Float: ImGui::DragFloat(m.name.c_str(), &n, 0.01f); break;
                
                case xtb::Uniform::Sampler2D: {
                    xtb::Material::TextureUniformInfo* info = dynamic_cast<xtb::Material::TextureUniformInfo*>(a->material.Get(m.name));

                    std::string newUuid = "";

                    if (info) {
                        newUuid = info->texture->GetUUID();
                    }
                    
                    if (EditorGUI::InputAsset<xtb::TextureAsset>(m.name.c_str(), newUuid)) {
                        xtb::TextureAsset* asset = xtb::AssetDatabase::GetAssetByUUID<xtb::TextureAsset>(newUuid);
                        if (asset) a->material.SetTexture(m.name, asset);
                    }

                    break;
                }

                default: break;
                }
            }
        }
        
        ImGui::EndTable();
    }
}
