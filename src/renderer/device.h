#pragma once

namespace chr::renderer {

struct DeviceI : entt::type_list<> {
  template <typename Base> struct type : Base {
    auto test() -> void { this->template invoke<0>(*this); }
  };

  template <typename Type> using impl = entt::value_list<&Type::test>;
};

struct Device : NonCopyable {
  explicit Device();

  auto test() -> void { instance_->test(); }

private:
  entt::basic_poly<DeviceI, 32> instance_{};
};

} // namespace chr::renderer