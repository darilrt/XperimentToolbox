#if defined(_MSC_VER)
	#ifdef ETB_BUILD
		#define DECLSPEC __declspec(dllexport)
	#else
		#define DECLSPEC __declspec(dllimport)
	#endif // ETB_BUILD
#elif defined(__GNUC__)
	//  GCC
	#ifdef ETB_BUILD
		#define DECLSPEC __attribute__((visibility("default")))
	#else
		#define DECLSPEC
	#endif // ETB_BUILD
#else
	#define DECLSPEC
	#define DECLSPEC
#endif

#define ETB_ENTRY(A) int main(int c, char* v[]) { return (new A())->Run(); }