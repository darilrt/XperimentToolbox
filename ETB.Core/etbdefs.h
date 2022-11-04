#if defined(_MSC_VER)
	#ifdef XTB_BUILD
		#define DECLSPEC __declspec(dllexport)
	#else
		#define DECLSPEC __declspec(dllimport)
	#endif // ETB_BUILD
#elif defined(__GNUC__)
	//  GCC
	#ifdef XTB_BUILD
		#define DECLSPEC __attribute__((visibility("default")))
	#else
		#define DECLSPEC
	#endif // ETB_BUILD
#else
	#define DECLSPEC
	#define DECLSPEC
#endif

#define XTB_ENTRY(A) int main(int c, char* v[]) { return (new A())->Run(); }

#include <glm/glm.hpp>

#define IM_VEC2_CLASS_EXTRA \
    constexpr ImVec2(glm::vec2& f) : x(f.x), y(f.y) {} \
    operator glm::vec2() const { return glm::vec2(x, y); }

#define IM_VEC4_CLASS_EXTRA \
        constexpr ImVec4(const glm::vec4& f) : x(f.x), y(f.y), z(f.z), w(f.w) {} \
        operator glm::vec4() const { return glm::vec4(x,y,z,w); }
