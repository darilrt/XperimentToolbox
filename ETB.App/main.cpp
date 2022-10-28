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
			std::filesystem::path path(pathString);
			
			if (path.extension().string() != ".py") return NULL;
			
			std::string className = path.stem().string();
			std::string modulesPath = path.parent_path().string();
			
			std::replace(modulesPath.begin(), modulesPath.end(), '/', '.');

			PyObject* moduleName = PyUnicode_FromString(modulesPath.c_str());
			PyObject* module = PyImport_Import(moduleName);
			Py_DECREF(moduleName);
			
			if (module == NULL) return NULL;

			PyObject* pClass = PyObject_GetAttrString(module, className.c_str());

			Py_DECREF(module);

			return pClass;
		}

		void ScriptDebugGUI() {
			ImGui::Begin("Script Debug");

			static std::string filePath("Assets/Scripts/TestScript.py");
			ImGui::InputText("Script Path", (char*) filePath.c_str(), filePath.size());

			static std::string error;

			if (ImGui::Button("Load")) {
				PyObject* classRef = xge::python::LoadComponentFromFile(filePath);
				
				if (classRef != NULL) {
					Py_DECREF(classRef);
				}
				else {
					error = xge::python::CaputreError();
				}
			}

			ImGui::Text(error.c_str());

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