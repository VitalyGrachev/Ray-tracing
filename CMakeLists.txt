cmake_minimum_required(VERSION 3.12)
project(ray-tracing)

set(CMAKE_CXX_STANDARD 17)
find_package(Qt5Widgets REQUIRED)
find_package (Threads REQUIRED)

add_executable(ray-tracing
        src/util/color.h
        src/util/color.cpp
        src/util/vector.h
        src/util/matrix.h
        src/util/enumeration.h
        src/util/transform.cpp src/util/transform.h
        src/geometry/geometry.h
        src/geometry/ray.cpp src/geometry/ray.h
        src/geometry/ray_transform.h src/geometry/ray_transform.cpp
        src/geometry/intersection.h src/geometry/intersection.cpp
        src/geometry/primitive/sphere.cpp src/geometry/primitive/sphere.h
        src/geometry/primitive/triangle.cpp src/geometry/primitive/triangle.h
        src/geometry/mesh/mesh.cpp src/geometry/mesh/mesh.h
        src/scene/object/object.cpp src/scene/object/object.h
        src/scene/camera/camera.cpp src/scene/camera/camera.h
        src/scene/scene.cpp src/scene/scene.h
        src/scene/light/light_source.h
        src/scene/light/illuminance.h
        src/scene/light/illuminance.cpp
        src/scene/light/light-source/point_light_source.cpp src/scene/light/light-source/point_light_source.h
        src/scene/object/material/material.h
        src/scene/object/material/BRD_function.h
        src/scene/object/material/phong/phong_shading_material.cpp src/scene/object/material/phong/phong_shading_material.h
        src/scene/object/material/phong/phong_solid_material.h
        src/scene/object/material/pbr/pbr_material.cpp src/scene/object/material/pbr/pbr_material.h
        src/scene/object/material/pbr/pbr_solid_material.h
        src/rt/frame/fragment.h
        src/rt/frame/frame_buffer.cpp src/rt/frame/frame_buffer.h
        src/rt/eye_ray_generator.cpp src/rt/eye_ray_generator.h
        src/rt/ray-tracer/ray_tracer.h
        src/rt/ray-tracer/ray-trace-task/ray_trace_task.h
        src/rt/ray-tracer/ray-trace-task/shadow_ray_trace_task.cpp src/rt/ray-tracer/ray-trace-task/shadow_ray_trace_task.h
        src/rt/ray-tracer/ray-trace-task/air_ray_trace_task.cpp src/rt/ray-tracer/ray-trace-task/air_ray_trace_task.h
        src/rt/ray-tracer/ray-trace-task/base_ray_trace_task.h src/rt/ray-tracer/ray-trace-task/base_ray_trace_task.cpp
        src/rt/ray-tracer/render_worker.cpp src/rt/ray-tracer/render_worker.h
        src/rt/ray-tracer/frame_renderer.cpp src/rt/ray-tracer/frame_renderer.h
        src/rt/ray-tracer/util/fragment_render_task.cpp src/rt/ray-tracer/util/fragment_render_task.h
        src/rt/ray-tracer/util/finished_fragment_counter.h src/rt/ray-tracer/util/eye_ray_trace_task_factory.cpp
        src/rt/ray-tracer/util/eye_ray_trace_task_factory.h
        src/rt/ray-tracer/util/finished_fragment_counter.cpp
        src/rt/render.cpp src/rt/render.h
        src/main.cpp
        )

target_link_libraries(ray-tracing Qt5::Widgets Threads::Threads)
