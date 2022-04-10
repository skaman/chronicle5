#pragma once

namespace chr::renderer {

struct SurfaceI : entt::type_list<> {
  template <typename Base> struct type : Base {
    auto test() -> void { this->template invoke<0>(*this); }
  };

  template <typename Type> using impl = entt::value_list<&Type::test>;
};

struct Instance;

struct SurfaceInfo {
  std::function<void*(void*)> init_callback{};
  void *hwnd{nullptr};
};

struct Surface : NonCopyable {
  explicit Surface(const Instance &instance, const SurfaceInfo &info);

  auto test() -> void { surface_->test(); }

private:
  entt::basic_poly<SurfaceI, 32> surface_{};
};

} // namespace chr::renderer