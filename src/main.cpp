#include <tundra/startup.hpp>
#include <tundra/core/fixed.hpp>

#include <tundra/assets/model/model-asset.hpp>
#include <tundra/engine/entity-system/entity.hpp>
#include <tundra/engine/entity-system/component-ref.hpp>
#include <tundra/engine/dynamic-transform.hpp>
#include <tundra/rendering/model.hpp>
#include <tundra/rendering/camera.hpp>
#include <tundra/rendering/render-system.hpp>

#include "assets.hpp"


const td::EngineSettings ENGINE_SETTINGS {
    30000 // Size of primitive buffer
};

const td::uint32 MAIN_LAYER_DEPTH_RESOLUTION = 2048;
const td::uint32 LAYER_WORLD = 1;

namespace assets::models {
    const td::ModelAsset* white_box;
}

td::Camera* camera;


class Box : public td::Component<Box> {
public:

    Box(td::DynamicTransform* transform) : transform(transform) { }

    static Box* create() {
        td::Entity* entity = td::Entity::create();
        td::DynamicTransform* transform = entity->add_component<td::DynamicTransform>();
        auto m = entity->add_component<td::Model>(*assets::models::white_box, LAYER_WORLD, transform);
        return entity->add_component<Box>(transform);
    }

    const td::ComponentRef<td::DynamicTransform> transform;

};


extern void initialize(td::EngineSystems& engine_systems) {

    // Setup lighting
    engine_systems.render.set_light_direction(0, { td::to_fixed(-0.577), td::to_fixed(-0.577), td::to_fixed(0.577) });
    engine_systems.render.set_light_color(0, { 255, 255, 255 });

    // Setup layer settings
    td::List<td::CameraLayerSettings> layer_settings;
    layer_settings.add({LAYER_WORLD, MAIN_LAYER_DEPTH_RESOLUTION});

    // Create camera
    td::Entity* camera_entity = td::Entity::create();
    td::DynamicTransform* camera_transform = camera_entity->add_component<td::DynamicTransform>();
    camera_transform->set_translation({td::to_fixed(0), td::to_fixed(0.5), td::to_fixed(-0.5)});
    td::Camera* camera = camera_entity->add_component<td::Camera>(camera_transform, layer_settings);
    camera->look_at({0,0,0});

    // Load assets
    assets::models::white_box = engine_systems.asset_load.load_model(asset_data::mdl_white_box);

    // Create box
    Box::create()->transform->set_scale({ 2, 2, 2 });

    td::Entity* e = td::Entity::create();
    td::Text* text = e->add_component<td::Text>(LAYER_FOREGROUND);
    text->text = "Hello, world!";
    position = td::Vec2<Fixed32<12>>{140, 200};

}

extern void update(td::EngineSystems& engine_systems, const td::FrameTime& frame_time) {
    for( Box* box : Box::get_all() ) {
        box->transform->add_rotation({0, td::to_fixed(0.005), 0});
    }

    td::Duration start = engine_systems.time.get_duration_since_start();

    td::Duration end = engine_systems.time.get_duration_since_start();
    td::Duration length = end - start;

    TD_DEBUG_LOG("%d", length.to_milliseconds());
}