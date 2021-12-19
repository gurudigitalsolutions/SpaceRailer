extern Stage * currentStage;

static PyObject * script_API(PyObject * self, PyObject * args, string method)
{
	return currentStage->processAPI(self, args, method);
}

/*static PyObject * script_NumArgs(PyObject * self, PyObject * args)
{
	if(!PyArg_ParseTuple(args, ":numargs"))
	{
		return NULL;
	}
	
	return PyLong_FromLong(420);
}*/

static PyObject * script_NumArgs(PyObject * self, PyObject * args) { return script_API(self, args, "numargs"); }
static PyObject * script_getMapX(PyObject * self, PyObject * args) { return script_API(self, args, "getMapX"); }
static PyObject * script_getMapY(PyObject * self, PyObject * args) { return script_API(self, args, "getMapY"); }
static PyObject * script_getPlayerX(PyObject * self, PyObject * args) { return script_API(self, args, "getPlayerX"); }
static PyObject * script_getPlayerY(PyObject * self, PyObject * args) { return script_API(self, args, "getPlayerY"); }

/*static PyObject * script_getMapX(PyObject * self, PyObject * args) { return PyLong_FromLong(currentStage->getMapX()); }
static PyObject * script_getMapY(PyObject * self, PyObject * args) { return PyLong_FromLong(currentStage->getMapY()); }
static PyObject * script_getPlayerX(PyObject * self, PyObject * args) { return PyLong_FromLong(currentStage->_player.getX()); }
static PyObject * script_getPlayerY(PyObject * self, PyObject * args) { return PyLong_FromLong(currentStage->_player.getY()); }
*/


static PyMethodDef pySpaceRailerMethods[] = {
	{"numargs", script_NumArgs, METH_VARARGS, "Return the number of arguments received by the process."},
	{"getMapX", script_getMapX, METH_VARARGS, "Return the x-coordinate of the left edge of the viewport."},
	{"getMapY", script_getMapY, METH_VARARGS, "Return the y-coordinate of the top edge of the viewport."},
	{"getPlayerX", script_getPlayerX, METH_VARARGS, "Return the x-coordinate of the player."},
	{"getPlayerY", script_getPlayerY, METH_VARARGS, "Return the y-coordinate of the player."},
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

