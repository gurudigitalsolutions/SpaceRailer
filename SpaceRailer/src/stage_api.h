static PyObject * script_NumArgs(PyObject * self, PyObject * args)
{
	if(!PyArg_ParseTuple(args, ":numargs"))
	{
		return NULL;
	}
	
	return PyLong_FromLong(420);
}

static PyMethodDef pySpaceRailerMethods[] = {
	{"numargs", script_NumArgs, METH_VARARGS, "Return the number of arguments received by the process."},
	{NULL, NULL, 0, NULL}
};

static PyModuleDef pySpaceRailerModule = {
	PyModuleDef_HEAD_INIT,
	"spacerailer",
	NULL,
	-1,			// <<<-- Sets interpreter to global state.  We may want many sub-interpreters!
	pySpaceRailerMethods,
	NULL, NULL, NULL, NULL
};

static PyObject * PyInit_pySpaceRailerModule()
{
	return PyModule_Create(&pySpaceRailerModule);
}
