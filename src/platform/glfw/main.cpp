#include <chronicle/common.h>

#include "glfw_platform.h"

auto main() -> int {
  chr::log::set_level(chr::log::level::trace);

  chr::GlfwPlatform platform;
  return platform.run();
}

//#include <entt/entt.hpp>
//
//struct NonCopyable {
//  NonCopyable() = default;
//  NonCopyable(const NonCopyable &) = delete;
//  NonCopyable &operator=(const NonCopyable &) = delete;
//};
//
//struct TestI : entt::type_list<> {
//  template <typename Base> struct type : Base {
//    void test() { this->template invoke<0>(*this); }
//  };
//
//  template <typename Type> using impl = entt::value_list<&Type::test>;
//};
//
//struct ItNotWork : TestI, NonCopyable {
//  auto test() -> void { std::cout << "It doesn't work" << std::endl; }
//};
//
//struct ItWork : TestI {
//  ItWork() = default;
//  ItWork(const ItWork &) = delete;
//  ItWork &operator=(const ItWork &) = delete;
//
//  auto test() -> void { std::cout << "It work" << std::endl; }
//};
//
//auto main() -> int {
//  entt::poly<TestI> test{};
//
//  test.emplace<ItNotWork>();
//  test->test();   // fail here
//
//  return EXIT_SUCCESS;
//}