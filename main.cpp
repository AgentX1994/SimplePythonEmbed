#define PY_SSIZE_T_CLEAN
#include <python3.8/Python.h>

#include <fmt/format.h>

int main(int argc, char** argv)
{
    if (argc < 3) {
        fmt::print(stderr, "Usage: {} <python file> <function> [args...]\n", argv[0]);
        return 1;
    }

    Py_Initialize();
    PyObject* pName = PyUnicode_DecodeFSDefault(argv[1]);
    /* error check pName */
    if (!pName) {
        PyErr_Print();
        fmt::print(stderr, "Could not decode filename \"{}\"\n", argv[1]);
    }

    PyObject* pModule = PyImport_Import(pName);
    Py_DECREF(pName);

    if (pModule != nullptr) {
        PyObject* pFunc = PyObject_GetAttrString(pModule, argv[2]);
        /* pFunc is a new reference */

        if (pFunc && PyCallable_Check(pFunc)) {
            PyObject* pArgs = PyTuple_New(argc - 3);
            for (int i = 0; i < argc - 3; ++i) {
                PyObject* pValue = PyLong_FromLong(atoi(argv[i + 3]));
                if (!pValue) {
                    Py_DECREF(pArgs);
                    Py_DECREF(pModule);
                    fmt::print(stderr, "Cannot convert argument\n");
                    return 1;
                }
                /* pValue reference stolen here: */
                PyTuple_SetItem(pArgs, i, pValue);
            }
            PyObject* pRet = PyObject_CallObject(pFunc, pArgs);
            Py_DECREF(pArgs);
            if (pRet != nullptr) {
                fmt::print("Result of call: {}\n", PyLong_AsLong(pRet));
                Py_DECREF(pRet);
            } else {
                Py_DECREF(pFunc);
                Py_DECREF(pModule);
                PyErr_Print();
                fmt::print(stderr, "Call failed\n");
                return 1;
            }
        }
        Py_XDECREF(pFunc);
        Py_DECREF(pModule);
    } else {
        PyErr_Print();
        fmt::print(stderr, "Failed to load \"{}\"\n", argv[1]);
        return 1;
    }
    if (Py_FinalizeEx() < 0) {
        return 120;
    }
    return 0;
}
