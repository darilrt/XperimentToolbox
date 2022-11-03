#include <etb.h>
#include <iostream>
#include <string>

#include "MaterialAssetInspector.h"
#include "EditorCamera.h"
#include "CubeActor.h"

class PreviewObject : public ETB::Actor {
public:
    ETB::Material material;

    void Render() {
        ETB::Graphics::DrawMesh(ETB::Primitives::sphere, transform.GetMatrix(), material);
    }
} *a;


MaterialAssetInspector::MaterialAssetInspector() {
}

void MaterialAssetInspector::Start() {
    if (cam == NULL) cam = new EditorCamera();
    cam->Start();
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

        ImVec2 size = ImGui::GetContentRegionAvail();
        size.y -= 4;
        
        scene.Update();
        cam->Update();
        cam->SetSize(size.x, size.y);
        scene.Render(cam->cam);

        ImGui::Image((ImTextureID) cam->cam.renderTexture.color.GetTextureId(), size, ImVec2(0, 1), ImVec2(1, 0));
        
        ImGui::TableNextColumn();
        ImGui::Text(resourcePath.filename().string().c_str());
        ImGui::Separator();

        ETB::Shader& sh = *a->material.shader;
        
        if (ImGui::Button("Edit Shader")) {
            system(("start \"C:/Program Files/Notepad++/notepad++.exe\" " + sh.GetPath()).c_str());
        }

        sh.Reload();
        
        if (sh.GetId() != 0) {
            for (ETB::Uniform& m : sh.GetUniforms()) {
                static float n = 0;
                switch (m.type)
                {
                case ETB::Uniform::Float: ImGui::DragFloat(m.name.c_str(), &n, 0.01f); break;
                default: break;
                }
            }
        }
        
        ImGui::EndTable();
    }
}
