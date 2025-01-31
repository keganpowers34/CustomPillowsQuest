#include "CustomTypes/Pillow.hpp"
#include "UnityEngine/SkinnedMeshRenderer.hpp"
#include "UnityEngine/Material.hpp"
#include "UnityEngine/Shader.hpp"
#include "UnityEngine/Texture.hpp"
#include "UnityEngine/Sprite.hpp"
#include "static-defines.hpp"

#include "TexturePool.hpp"

#include "questui/shared/BeatSaberUI.hpp"
#include "FileUtils.hpp"

DEFINE_TYPE(MenuPillow, Pillow);

using namespace UnityEngine;

static ConstString mainTex{"_mainTex"};
extern Logger& getLogger();
int id = 0;
namespace MenuPillow
{
    void Pillow::Awake()
    {
        std::string name = TexturePool::GetTextureName();
        if (name != "")
            InitFromName(name);
    }

    // not really used
    void Pillow::Init(UnityEngine::Texture2D* texture)
    {
        SkinnedMeshRenderer* renderer = GetComponent<SkinnedMeshRenderer*>();
        Material* mat = renderer->get_material();
        mat->SetTexture(mainTex, reinterpret_cast<Texture*>(texture));
    }

    // set texture by loading the sprite from file, and immediately destroy the sprite again
    void Pillow::InitFromName(std::string texName)
    {
        // get path
        std::string imagePath = IMAGEPATH + texName;
        // get sprite
        Texture2D* tex = FileUtils::FileToTexture(imagePath);
        // get renderer & mat
        SkinnedMeshRenderer* renderer = GetComponent<SkinnedMeshRenderer*>();
        Material* mat = renderer->get_material();
        if (!id) id = Shader::PropertyToID(mainTex);
        // set main tex
        Object::Destroy(mat->GetTexture(id));

        mat->SetTexture(mainTex, tex);
    }
}