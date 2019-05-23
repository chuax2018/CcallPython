//https://blog.csdn.net/lcwyan/article/details/50502368 

#include <Python.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

string PyString2CString(PyObject* pystring)
{
    PyObject * ascii_string = PyUnicode_AsASCIIString(pystring);
    PyObject* bytes_string = PyBytes_FromObject(ascii_string);
    char* c_string = PyBytes_AsString(bytes_string);
    return c_string;
}

bool call_python_module_func()
{
    PyObject* Pmodule = PyImport_ImportModule("CDemo");
    if (!Pmodule)
        return false;

    // call python func with no args no return
    PyObject* func_say_hello = PyObject_GetAttrString(Pmodule, "func_say_hello");
    PyObject_CallFunction(func_say_hello, nullptr);

    // call python func with no args but return (cov string)
    PyObject* func_return_string = PyObject_GetAttrString(Pmodule, "func_return_string");
    PyObject* some_string = PyObject_CallFunction(func_return_string, nullptr);

    PyObject * ascii_string = PyUnicode_AsASCIIString(some_string);
    PyObject* bytes_string = PyBytes_FromObject(ascii_string);
    char* c_string = PyBytes_AsString(bytes_string);
    cout << "c get string from python: " << c_string << endl;

    // call python func with args and return
    PyObject* func_add = PyObject_GetAttrString(Pmodule, "func_add");
    //PyObject *args = Py_BuildValue("ii", -5987, -5980);
    //PyObject *b = Py_BuildValue("i", -5980);
    PyObject* result = PyObject_CallFunction(func_add, "ii", -5987, -5980);
    PyObject_Print(result, stdout, 0);
    long result_long = PyLong_AsLong(result);
    cout << "result_long is: " << result_long << endl;

    // how to handle returned python list.
    PyObject* get_filepath_in_dir = PyObject_GetAttrString(Pmodule, "get_filepath_in_dir");
    PyObject* filepaths_list = PyObject_CallFunction(get_filepath_in_dir, "s", "./");
    if (PyList_Check(filepaths_list))
    {
        Py_ssize_t n = PyList_Size(filepaths_list);
        vector<string> filepaths;
        for (Py_ssize_t i = 0; i < n; i++)
        {
            PyObject* filepath = PyList_GetItem(filepaths_list, i);

            if (!filepath)
            {
                cout << "filepath get nullptr" << endl;
            }

            filepaths.push_back(PyString2CString(filepath));
        }

        for (auto filepath : filepaths)
            cout << "filepath: " << filepath << endl;
    }
    else
    {
        cout << "err:not a list!\n";
        return false;
    }
    return true;
}

bool call_python_module_class()
{
    PyObject* Pmodule = PyImport_ImportModule("CDemo");
    PyObject* PStudent = PyObject_GetAttrString(Pmodule, "Student");
    PyObject *args = Py_BuildValue("ssiis", "LiLei", "Male", 19, 12, "race");
    PyObject *pstu = PyObject_Call(PStudent, args, nullptr);

    // call python class method with no args no return
    PyObject_CallMethod(pstu, "tell_info", nullptr);

    // call python class method with no args and return
    PyObject *str_talent_result = PyObject_CallMethod(pstu, "show_the_talent", nullptr);
    PyObject_Print(str_talent_result, stdout, 0);
    cout << PyString2CString(str_talent_result) << endl;

    // call python class method with args and return
    // cov int
    PyObject *int_add_result = PyObject_CallMethod(pstu, "do_calculation_add", "ii", 19 , 80);
    cout << PyLong_AsLong(int_add_result) << endl;

    //cov float
    PyObject *float_add_result = PyObject_CallMethod(pstu, "do_calculation_add", "ff", 19.0053, 80.001);
    cout << PyFloat_AsDouble(float_add_result) << endl;

    // todo: how to pass list from c to python.
    //PyObject *show_list_result = PyObject_CallMethod(pstu, "pass_list_get_string", "[ssisi]", "XIAOHONG", "is", 18, "at", 2019);
    //PyObject_Print(show_list_result, stdout, 0);
    //cout << PyString2CString(show_list_result) << endl;


    return true;
}

int main()
{
    Py_Initialize();

    call_python_module_func();

    call_python_module_class();

    Py_Finalize();
    return 0;
}
