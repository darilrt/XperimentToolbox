#include "Debug.h"
#include "ShaderAsset.h"

namespace xtb {
    REGISTER_ASSET(ShaderAsset, ".gl");

    nlohmann::json ShaderAsset::Serialize() {
		nlohmann::json json = Asset::Serialize();
		
        return nlohmann::json();
    }

    void ShaderAsset::LoadAsset() {
		shader = new Shader(path.string());
        
        shader->Compile();
    }

    std::string ShaderAsset::GetTypeName() {
        return std::string(typeid(xtb::ShaderAsset).raw_name());
    }

    Asset* ShaderAsset::Create() {
        return new ShaderAsset();
    }
}