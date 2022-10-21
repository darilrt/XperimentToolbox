#include <etb.h>
#include <filesystem>
#include <stdlib.h>

#include "Python.h"
#include "EditorCamera.h"

using namespace ETB;

namespace py {
	inline void Initialize() { Py_Initialize(); }
	inline void Finalize() { Py_Finalize(); }

	class Object {
	public:
		PyObject* ptr;

		inline Object() : ptr(NULL) { }
		inline Object(PyObject* obj) : ptr(obj) { }

		inline void DecRef() { Py_DECREF(ptr); }

		inline Object GetAttr(const std::string& attrName) { return Object(PyObject_GetAttrString(this->ptr, attrName.c_str())); }
		inline Object Str() { return Object(PyObject_Str(this->ptr)); }
		inline const char* UnicodeAsString() { return PyUnicode_AsUTF8(ptr); }
		
		inline int IsCallable() { return PyCallable_Check(ptr); }

		inline bool IsNull() { return ptr == NULL; }
		inline bool IsNotNull() { return ptr != NULL; }

		template<typename... T>
		inline Object CallMethod(const std::string& methodName, const char* format, T ...t) { return Object(PyObject_CallMethod(this->ptr, methodName.c_str(), format, t...)); }

		template<class... T>
		inline Object CallMathodObjArgs(Object name, T... t) { return Object(PyObject_CallMethodObjArgs(ptr, name.ptr, t..., NULL)); }

		template<class... T>
		inline Object CallFunctionObjArgs(T... t) { return Object(PyObject_CallFunctionObjArgs(ptr, t..., NULL)); }
	
		inline void operator =(PyObject* pObj) { ptr = pObj; }
	};
	
	inline Object Unicode(const std::string& str) { return PyUnicode_FromString(str.c_str()); }

	inline Object Import(Object name) { return Object(PyImport_Import(name.ptr)); }
}

class App : public Application {
public:
	Transform t;

	App() : Application("Hello, World", 1140, 620) {
		window.SetVSync(Core::VSyncMode::On);

		py::Initialize();

		PyObject* pName = PyUnicode_FromString((char*)"Assets.Scripts");
		PyObject* assetsModule = PyImport_Import(pName);
		
		if (assetsModule == NULL) {
			PyObject* err = PyErr_Occurred();

			py::Object extype, value, traceback;

			PyErr_Fetch(&extype.ptr, &value.ptr, &traceback.ptr);

			auto tb = py::Import(py::Unicode("traceback"));
			auto func = tb.GetAttr("format_exception");
			
			if (func.IsNotNull() && func.IsCallable()) {
				auto val = func.CallFunctionObjArgs(extype, value, traceback);

				auto s = py::Unicode("");
				auto val2 = s.CallMathodObjArgs(py::Unicode("join"), val);
				val.DecRef();
				
				auto pystr = val2.Str();
				std::string full_backtrace(pystr.UnicodeAsString());
				pystr.DecRef();

				Debug::Print(full_backtrace);
			}
			// PyErr_Print();
			
			// Debug::Print(TO_STR(value));

			return;
		}

		PyObject* testScript = PyObject_GetAttrString(assetsModule, (char*)"TestScript");
		PyObject* obj = PyObject_CallObject(testScript, NULL);

		PyObject_CallMethod(obj, "start", NULL);
		
		Py_DECREF(pName);
		Py_DECREF(assetsModule);
		Py_DECREF(testScript);
		Py_DECREF(obj);

		py::Finalize();
	}

	~App() {
	}

	void Start() {
		Application::Quit();
	}
	
	void Update() {
	}

	void Render() {
	}

	void GUI() {
	}
};

ETB_ENTRY(App);