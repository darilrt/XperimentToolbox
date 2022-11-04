#include <etb.h>
#include <iostream>
#include <string>

#include "MaterialAssetInspector.h"
#include "EditorCamera.h"
#include "CubeActor.h"
#include "EditorGUI.h"

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
        ImGui::Text(resourcePath.filename().string().c_str());
        ImGui::Separator();

        xtb::Shader& sh = *a->material.shader;
        
        if (ImGui::Button("Edit Shader")) {
            system(("start \"C:/Program Files/Notepad++/notepad++.exe\" " + sh.GetPath()).c_str());
        }

        sh.Reload();
        
        if (sh.GetId() != 0) {
            for (xtb::Uniform& m : sh.GetUniforms()) {
                static float n = 0;
                switch (m.type)
                {
                case xtb::Uniform::Float: ImGui::DragFloat(m.name.c_str(), &n, 0.01f); break;
                default: break;
                }
            }
        }
        
        ImGui::EndTable();
    }
}
