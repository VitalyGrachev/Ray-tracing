#include <memory>
#include <cmath>
#include <QImage>

#include "rt/render.h"
#include "scene/scene.h"
#include "geometry/mesh/mesh.h"
#include "geometry/primitive/sphere.h"
#include "scene/light/light-source/point_light_source.h"
#include "scene/object/material/pbr/pbr_solid_material.h"
#include "scene/object/material/phong/phong_solid_material.h"

std::shared_ptr<Geometry> create_cube_mesh() {
    const std::vector<Vec3> v = {
            Vec3(-0.5f, 0.5f, 0.5f),
            Vec3(-0.5f, -0.5f, 0.5f),
            Vec3(0.5f, 0.5f, 0.5f),
            Vec3(0.5f, -0.5f, 0.5f),
            Vec3(-0.5f, 0.5f, -0.5f),
            Vec3(-0.5f, -0.5f, -0.5f),
            Vec3(0.5f, 0.5f, -0.5f),
            Vec3(0.5f, -0.5f, -0.5f),
    };

    return std::make_shared<Mesh>(std::vector<Triangle>{
            Triangle(v[0], v[1], v[2]), Triangle(v[1], v[3], v[2]), // top side
            Triangle(v[4], v[6], v[5]), Triangle(v[5], v[6], v[7]), // bottom side
            Triangle(v[0], v[2], v[4]), Triangle(v[2], v[6], v[4]), // left side
            Triangle(v[1], v[5], v[3]), Triangle(v[3], v[5], v[7]), // right side
            Triangle(v[2], v[3], v[6]), Triangle(v[3], v[7], v[6]), // forward side
            Triangle(v[0], v[4], v[1]), Triangle(v[1], v[4], v[5]), // backward side
    });
}

std::shared_ptr<Geometry> create_square_mesh() {
    const std::vector<Vec3> v = {
            Vec3(-0.5f, 0.5f, 0.0f),
            Vec3(-0.5f, -0.5f, 0.0f),
            Vec3(0.5f, 0.5f, 0.0f),
            Vec3(0.5f, -0.5f, 0.0f),
    };

    return std::make_shared<Mesh>(std::vector<Triangle>{
            Triangle(v[0], v[1], v[2]), Triangle(v[1], v[3], v[2]),
    });
}

inline Color hdr_correction(const Color & c, float exposure) {
    Color ret = c;
    ret.r() = std::clamp(1.0f - std::exp(-c.r() * exposure), 0.0f, 1.0f);
    ret.g() = std::clamp(1.0f - std::exp(-c.g() * exposure), 0.0f, 1.0f);
    ret.b() = std::clamp(1.0f - std::exp(-c.b() * exposure), 0.0f, 1.0f);
    return ret;
}

QImage frame_to_image(const FrameBuffer & frame) {
    const FrameBuffer::Size frame_size = frame.size();
    QImage image(QSize(frame_size.cols, frame_size.rows), QImage::Format::Format_RGB32);

    const float exposure = 0.8f;
    QColor im_color;
    for (unsigned r = 0; r < frame_size.rows; ++r) {
        for (unsigned c = 0; c < frame_size.cols; ++c) {
            const FrameBuffer::Position pos = {c, r};
            const Color & color = hdr_correction(frame.color_at(pos), exposure);
            im_color.setRed(255 * color.r());
            im_color.setGreen(255 * color.g());
            im_color.setBlue(255 * color.b());
            image.setPixelColor(c, r, im_color);
        }
    }

    return image;
}

void render_scene() {
    auto scene = std::make_shared<Scene>();
    auto material1 = std::make_shared<PBRSolidMaterial>(Color(0.005f, 0.005f, 0.005f), Color(0.05f, 0.2f, 0.2f), 0.3f);
    auto material2 = std::make_shared<PBRSolidMaterial>(Color(0.6f, 0.5f, 0.1f), Color(0.0f, 0.0f, 0.0f), 0.99f);
    auto material3 = std::make_shared<PBRSolidMaterial>(Color(0.8f, 0.3f, 0.8f), Color(0.0f, 0.0f, 0.0f), 0.99f);
    auto material7 = std::make_shared<PhongSolidMaterial>(Color(0.8f, 0.8f, 0.8f), Color(0.4f, 0.3f, 0.2f), 7.0f);
    auto sphere_mesh = std::make_shared<Sphere>();
    auto square_mesh = create_square_mesh();
    auto cube_mesh = create_cube_mesh();

    Camera & camera = scene->get_camera();
    camera.transform().translate(Vec3(-4.0f, 1.5f, 3.0f)).rotate(0.5f, Vec3(0, 1, 0)).rotate(-0.25f, Vec3(0, 0, 1));
    camera.set_field_of_view(Vec2(1.159f, 1.0f));

    Object floor(square_mesh, material7);
    floor.transform().translate(Vec3(1.5f, 0.0f, -0.8f)).scale(40);
    scene->add_object(floor);

    Object sphere1(sphere_mesh, material2);
    sphere1.transform().translate(Vec3(2.0f, 0.4f, 0.0f)).scale(1.6f);
    scene->add_object(sphere1);

    Object sphere2(sphere_mesh, material3);
    sphere2.transform().translate(Vec3(2.45f, -0.6f, 0.0f)).scale(2.0f);
    scene->add_object(sphere2);

    Object sphere3(sphere_mesh, material3);
    sphere3.transform().translate(Vec3(0.0f, -1.5f, 0.4f)).scale(1.0f);
    scene->add_object(sphere3);

    Object cube(cube_mesh, material3);
    cube.transform().translate(Vec3(0.4f, 1.6f, 0.7f)).scale(0.5f).rotate(2.0f, Vec3(0, 0, 1.0f));
    scene->add_object(cube);

    auto light1 = std::make_unique<PointLightSource>(Color(1.0f, 1.0f, 1.0f), 2.2f);
    light1->transform().translate(Vec3(0.1f, -1.1f, 1.3f));
    scene->add_light_source(std::move(light1));

    auto light2 = std::make_unique<PointLightSource>(Color(0.7f, 0.7f, 1.0f), 1.1f);
    light2->transform().translate(Vec3(1.0, 2.0f, 1.0f));
    scene->add_light_source(std::move(light2));

    const FrameBuffer::Size frame_size = {1600, 1200};
    FrameBuffer frame(frame_size);
    auto future = render(scene, std::move(frame));

    frame = std::move(future.get());

    QImage image = frame_to_image(frame);
    image.save("result.png");
}

int main(int argc, char ** argv) {
    render_scene();
    return 0;
}