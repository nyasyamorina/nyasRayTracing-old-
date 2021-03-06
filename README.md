# nyasRayTracing

---

#### working......

Target: A fully functional render process.

---

## Current progress

+ Fully functional 2D-buffer for rendering and output an image.

+ Implemented two simple cameras.

+ Simple bidirectional reflectance distribution function extends from `BRDF`.

+ Simple object extends from `Object3D`.

+ Simple sky extends from `Sky`.

+ A ray tracer using hemisphere model without importance sampling.

---

## Update Log

### 14-09-21

+ Add some necessary file for ray tracing, include [brdfs](https://github.com/nyasyamorina/nyasRayTracing/tree/master/brdfs)
, [objects](https://github.com/nyasyamorina/nyasRayTracing/tree/master/objects), and more.

+ Add a simple ray tracer [HemisphereModel](https://github.com/nyasyamorina/nyasRayTracing/blob/master/tracers/HemisphereModel.hpp).

+ Add [World](https://github.com/nyasyamorina/nyasRayTracing/blob/master/World.hpp) store objects, sky and camera, and render scenes.

+ Add a simple rendering example `example_simple_scenes`, see output in [outputs](https://github.com/nyasyamorina/nyasRayTracing/tree/master/outputs).

### 05-09-21

+ Deleted `CMakeLists.txt`, because there is only one source file in the entire project.

+ An unknown issue: the camera outputs changed when I changed the compiler. see [outputs/camera](https://github.com/nyasyamorina/nyasRayTracing/tree/master/outputs/camera).

+ Add [common/setup.h](https://github.com/nyasyamorina/nyasRayTracing/blob/master/common/setup.h) to control some functions.

### 03-09-21

+ Use more general `Buffer2D` instead of `GraphicsBuffer`.

+ Gamma correction is not used in [examples.hpp](https://github.com/nyasyamorina/nyasRayTracing/blob/master/examples.hpp) now.

+ add [samplers/test.py](https://github.com/nyasyamorina/nyasRayTracing/blob/master/samplers/test.py) for showing samplers.

### 31-08-21

+ Add `cameras`: `Parallel` and `Pinhole`.

+ Add example `example_cameras`, see outputs in [outputs/camera](https://github.com/nyasyamorina/nyasRayTracing/tree/master/outputs/camera).

+ refectory output directory.

### 18-08-21

+ Fix `NRooks` sampler cannot generate samples correctly.

+ Add `RenderPlane` and `Camera` class to simulate simple camera.

+ Add `Hammersley` sampler and add its example in [examples.hpp](https://github.com/nyasyamorina/nyasRayTracing/blob/master/examples.hpp).

### 11-08-21

+ Add samplers: `NRooks` and `MultiJittered`, and add corresponding examples in `example_samplers()`.

### 10-08-21

+ Add random number method in [common/randoms.hpp](https://github.com/nyasyamorina/nyasRayTracing/blob/master/common/randoms.hpp).

+ Add 3 different sampler: `Regular`, `PureRandom` and `Jittered`.

+ Add example `example_samplers`, see outputs in [outputs/sampler](https://github.com/nyasyamorina/nyasRayTracing/tree/master/outputs/sampler).

### 06-08-21

+ Add rvalue reference in `GraphicsBuffer`, and add method `cast<U>` and `map<U>`.

+ Make example `example_rendering_output` easier.

+ Add `samplers`.

### 03-08-21

+ Fixed error `there are no arguments to 'is_float' that depend on a template parameter` with `G++` compiler.

+ To fix warning `compound assignment with 'volatile'-qualified left operand is deprecated`
, you must manually changing `f*=f` to `f=f*f` in glm file `glm/detail/type_half.inl:9`.

+ Unused `::glm::qualifier` in exposed template type `vec`.

+ Add [examples.hpp](https://github.com/nyasyamorina/nyasRayTracing/blob/master/examples.hpp).

### 02-08-21

+ Added 2D graphics buffer in `GraphicsBuffer.hpp`. now it can render and output a simple [outputs](https://github.com/nyasyamorina/nyasRayTracing/tree/master/outputs).

### 01-08-21

+ Added fast inverse square root in [common/fast_inversesqrt.hpp](https://github.com/nyasyamorina/nyasRayTracing/blob/master/common/fast_inversesqrt.hpp).

---

**Using C++20.**

**Using third-party libraries [glm](https://github.com/g-truc/glm) to provide math support.**
