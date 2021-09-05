# nyasRayTracing

---

#### working......

Target: A fully functional render process.

---

## Update Log

### 05-09-21

+ Deleted `CMakeLists.txt`, beacuse there is only one source file in the entire project.

+ There are some problems when using clang, see [utils.hpp](https://github.com/nyasyamorina/nyasRayTracing/blob/master/utils.hpp)

+ An unknown issue: the camera outputs changed when I changed the compiler.

### 03-09-21

+ Use more general `Buffer2D` instead of `GraphicsBuffer`.

+ Gamma correction is not used in [examples.hpp](https://github.com/nyasyamorina/nyasRayTracing/blob/master/examples.hpp) now.

+ add [samplers/test.py](https://github.com/nyasyamorina/nyasRayTracing/blob/master/samplers/test.py) for showing samplers.

### 31-08-21

+ Add `cameras`: `Parallel` and `Pinhole`.

+ Add example `example_cameras`, see outputs in [outputs/camera](https://github.com/nyasyamorina/nyasRayTracing/tree/master/outputs/camera).

+ refactory output directory.

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

+ Unuse `::glm::qualifier` in exposed template type `vec`.

+ Add [examples.hpp](https://github.com/nyasyamorina/nyasRayTracing/blob/master/examples.hpp).

### 02-08-21

+ Added 2D graphics buffer in `GraphicsBuffer.hpp`. now it can render and output a simple [outputs](https://github.com/nyasyamorina/nyasRayTracing/tree/master/outputs).

### 01-08-21

+ Added fast inverse square root in [common/fast_inversesqrt.hpp](https://github.com/nyasyamorina/nyasRayTracing/blob/master/common/fast_inversesqrt.hpp).

---

**Using C++20.**

**Using third-party libraries [glm](https://github.com/g-truc/glm) to provide math support.**
