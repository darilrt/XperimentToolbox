#include <etb.h>
#include <filesystem>
#include <stdlib.h>

#include "Python.h"
#include "EditorCamera.h"

using namespace ETB;

namespace xge {
	namespace python {

		std::string CaputreError() {
			PyObject* err = PyErr_Occurred();
			if (err == NULL) return "";
			Py_DECREF(err);

			// capture error
			PyObject *pType, *pValue, *pTraceback;
			PyErr_Fetch(&pType, &pValue, &pTraceback);
			
			// import traceback
			PyObject* tracebackStr = PyUnicode_FromString("traceback");
			PyObject* tracebackModule = PyImport_Import(tracebackStr);
			Py_DECREF(tracebackStr);
			
			// format_exception
			PyObject* formatExceptionFunc = PyObject_GetAttrString(tracebackModule, "format_exception");

			std::string backtrace;

			if (formatExceptionFunc != NULL) {
				PyObject* exceptionList = PyObject_CallFunctionObjArgs(formatExceptionFunc, pType, pValue, pTraceback, NULL);

				// exceptionStr = "".join(exceptionList)
				PyObject* str = PyUnicode_FromString("");
				PyObject* joinMethod = PyUnicode_FromString("join");
				PyObject* exceptionStr = PyObject_CallMethodObjArgs(str, joinMethod, exceptionList, NULL);
				Py_DECREF(joinMethod);
				Py_DECREF(str);
				Py_DECREF(exceptionList);

				backtrace = std::string(PyUnicode_AsUTF8(exceptionStr));
				
				Py_DECREF(exceptionStr);
				Py_DECREF(formatExceptionFunc);
			}

			Py_DECREF(tracebackModule);
			Py_DECREF(pType); Py_DECREF(pValue); Py_DECREF(pTraceback);

			return backtrace;
		}

		PyObject* LoadComponentFromFile(const std::string& pathString) {
			PyObject* moduleName = PyUnicode_FromString("Assets.Scripts");

			std::filesystem::path path(pathString);
			
			if (path.extension() != ".py") return NULL;
			if (path.nam)

		}

		void ScriptDebugGUI() {
			ImGui::Begin("Script Debug");

			static std::string filePath("Assets/Scripts/TestScript.py");
			ImGui::InputText("Script Path", (char*) filePath.c_str(), filePath.size());

			if (ImGui::Button("Load")) {

			}

			ImGui::End();
		}

	}
}

class App : public Application {
public:
	Transform t;

	App() : Application("Hello, World", 1140, 620) {
		window.SetVSync(Core::VSyncMode::On);

		Py_Initialize();
	}

	~App() {
		Py_Finalize();
	}

	void Start() {
	}
	
	void Update() {
	}

	void Render() {
	}

	void GUI() {

		xge::python::ScriptDebugGUI();

	}
};

ETB_ENTRY(App);