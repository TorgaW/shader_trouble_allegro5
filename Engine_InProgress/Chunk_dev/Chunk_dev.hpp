#ifndef BEA9B3D9_2064_440F_B959_F0A8021F8D87
#define BEA9B3D9_2064_440F_B959_F0A8021F8D87

#include "../SceneManager/SceneManager.hpp"
#include "../ShaderManager/ShaderManager.hpp"
#include "../BitmapManager/BitmapManager.hpp"

class Chunk_dev : public SceneObject
{
private:
    Bitmap *grass_tex {nullptr};
    Bitmap *dirt_tex {nullptr};
    Shader *noise_shader {nullptr};
    Shader *terrain_shader {nullptr};

    Bitmap *result_bitmap;

public:
    Chunk_dev(const std::string& _obj_class, const ObjectSignature& obj_sign) : 
    SceneObject(_obj_class, obj_sign)
    {};
    virtual ~Chunk_dev(){};

    virtual void Begin()
    {
        grass_tex = BitmapManager::LoadBitmap("Resources/Sprites/Ground/Grass_pp.png");
        dirt_tex = BitmapManager::LoadBitmap("Resources/Sprites/Ground/Dirt_pp.png");
        noise_shader = ShaderManager::GetShader("PerlinNoise");
        result_bitmap = al_create_bitmap(512, 512);
        al_set_target_bitmap(result_bitmap);
        al_clear_to_color(al_map_rgb_f(1.0, 1.0, 1.0));
        Render::SetViewportAsRenderTarget();
    }

    virtual void Draw(float delta)
    {   
        // al_set_target_bitmap(result_bitmap);
        // al_clear_to_color(al_map_rgb(0,0,0));
        al_use_shader(noise_shader);
        al_set_shader_sampler("tex1", grass_tex, 1);
        al_set_shader_sampler("tex2", dirt_tex, 2);
        // al_set_shader_sampler("dirt_texture", dirt_tex, 2);
        al_draw_bitmap(result_bitmap, 0, 0, 0);
        // al_draw_scaled_bitmap(result_bitmap, 0, 0, 32, 32, 1024, 512, 256, 256, 0);
        // Render::SetViewportAsRenderTarget();
        al_use_shader(nullptr);
        // al_use_shader(terrain_shader);
        // al_set_shader_sampler("noise_texture", result_bitmap, 1);
        // al_draw_bitmap(result_bitmap, 0, 0, 0);
        // al_draw_scaled_bitmap(dirt_tex, 0, 0, 32, 32, 0, 0, 256, 256, 0);
        // Render::SetViewportAsRenderTarget();
        // al_use_shader(nullptr);
        // al_set_target_bitmap(result_bitmap);
        // al_draw_bitmap(result_bitmap, 0, 512, 0);
        // al_clear_to_color(al_map_rgb(0,0,0));
        // Render::SetViewportAsRenderTarget();
    }
};


#endif /* BEA9B3D9_2064_440F_B959_F0A8021F8D87 */
