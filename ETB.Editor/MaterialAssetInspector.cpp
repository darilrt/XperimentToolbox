#include <etb.h>
#include <iostream>
#include <string>

#include "MaterialAssetInspector.h"
#include "EditorCamera.h"
#include "CubeActor.h"

MaterialAssetInspector::MaterialAssetInspector() {
}

void MaterialAssetInspector::Start() {
    // width assets manager could be
    // AssetsManager::Get<Material>(resourcePath.string());
    
    // Start preivew
    cam = new EditorCamera();
    cam->cam.transform.position = glm::vec3(0, 0, 5.0f);
    cam->Start();

    CubeActor* a = scene.Instance<CubeActor>();
    a->name = "Qbito";
    a->material.LoadFromFile(resourcePath.string());

    scene.Start();
}

void MaterialAssetInspector::GUI() {
    static ETB::Texture texture("Built-In/Textures/color.png");

    if (ImGui::BeginTable("MaterialEditor", 2, ImGuiTableFlags_Resizable))
    {
        ImGui::TableNextColumn();
        ImVec2 size = ImGui::GetContentRegionAvail();

        scene.Update();
        cam->Update();

        cam->SetSize(size.x, size.y);

        scene.Render(cam->cam);

        ImGui::Image((ImTextureID) cam->cam.renderTexture.color.GetTextureId(), size, ImVec2(0, 1), ImVec2(1, 0));
        
        ImGui::TableNextColumn();

        ETB::Shader& sh = ETB::ShaderLoader::Get("Built-In/Shaders/Test.glsl");
        
        for (ETB::Uniform& m : sh.GetUniforms()) {
            ImGui::Text(m.name.c_str());
        }

        ImGui::EndTable();
    }
}
