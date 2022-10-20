#include <etb.h>
#include <filesystem>
#include <stdlib.h>

#include "Python.h"
#include "EditorCamera.h"

using namespace ETB;

class App : public Application {
public:
	Transform t;

	App() : Application("Hello, World", 1140, 620) {
		window.SetVSync(Core::VSyncMode::On);

		Py_Initialize();

		PyObject* pName = PyUnicode_FromString((char*)"Assets.Scripts");
		PyObject* assetsModule = PyImport_Import(pName);

		PyObject* testScript = PyObject_GetAttrString(assetsModule, (char*)"TestScript");
		PyObject* obj = PyObject_CallObject(testScript, NULL);

		PyObject_CallMethod(obj, "start", NULL);

		Py_DECREF(pName);
		Py_DECREF(assetsModule);
		Py_DECREF(testScript);
		Py_DECREF(obj);

		Py_Finalize();
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