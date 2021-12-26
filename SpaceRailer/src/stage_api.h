extern Stage * currentStage;

static PyObject * script_API(PyObject * self, PyObject * args, string method)
{
	return currentStage->processAPI(self, args, method);
}


static PyObject * script_NumArgs(PyObject * self, PyObject * args) { return script_API(self, args, "numargs"); }
static PyObject * script_getMapX(PyObject * self, PyObject * args) { return script_API(self, args, "getMapX"); }
static PyObject * script_getMapY(PyObject * self, PyObject * args) { return script_API(self, args, "getMapY"); }
static PyObject * script_getPlayerX(PyObject * self, PyObject * args) { return script_API(self, args, "getPlayerX"); }
static PyObject * script_getPlayerY(PyObject * self, PyObject * args) { return script_API(self, args, "getPlayerY"); }
static PyObject * script_getPlayerHP(PyObject * self, PyObject * args) { return script_API(self, args, "getPlayerHP"); }
static PyObject * script_getPlayerWidth(PyObject * self, PyObject * args) { return script_API(self, args, "getPlayerWidth"); }
static PyObject * script_getPlayerHeight(PyObject * self, PyObject * args) { return script_API(self, args, "getPlayerHeight"); }
static PyObject * script_setPlayerX(PyObject * self, PyObject * args) { return script_API(self, args, "setPlayerX"); }
static PyObject * script_setPlayerY(PyObject * self, PyObject * args) { return script_API(self, args, "setPlayerY"); }
static PyObject * script_getStageScrollPixelsPerInterval(PyObject * self, PyObject * args) { return script_API(self, args, "getStageScrollPixelsPerInterval"); }
static PyObject * script_setStageScrollPixelsPerInterval(PyObject * self, PyObject * args) { return script_API(self, args, "setStageScrollPixelsPerInterval"); }
static PyObject * script_getStageScrollInterval(PyObject * self, PyObject * args) { return script_API(self, args, "getStageScrollInterval"); }
static PyObject * script_setStageScrollInterval(PyObject * self, PyObject * args) { return script_API(self, args, "setStageScrollInterval"); }
static PyObject * script_createMob(PyObject * self, PyObject * args) { return script_API(self, args, "createMob"); }
static PyObject * script_getMobX(PyObject * self, PyObject * args) { return script_API(self, args, "getMobX"); }
static PyObject * script_getMobY(PyObject * self, PyObject * args) { return script_API(self, args, "getMobY"); }
static PyObject * script_setMobX(PyObject * self, PyObject * args) { return script_API(self, args, "setMobX"); }
static PyObject * script_setMobY(PyObject * self, PyObject * args) { return script_API(self, args, "setMobY"); }
static PyObject * script_getMobWidth(PyObject * self, PyObject * args) { return script_API(self, args, "getMobWidth"); }
static PyObject * script_getMobHeight(PyObject * self, PyObject * args) { return script_API(self, args, "getMobHeight"); }
static PyObject * script_setMobWidth(PyObject * self, PyObject * args) { return script_API(self, args, "setMobWidth"); }
static PyObject * script_setMobHeight(PyObject * self, PyObject * args) { return script_API(self, args, "setMobHeight"); }
static PyObject * script_getMobAngle(PyObject * self, PyObject * args) { return script_API(self, args, "getMobAngle"); }
static PyObject * script_setMobAngle(PyObject * self, PyObject * args) { return script_API(self, args, "setMobAngle"); }
static PyObject * script_getMobParent(PyObject * self, PyObject * args) { return script_API(self, args, "getMobParent"); }
static PyObject * script_setMobParent(PyObject * self, PyObject * args) { return script_API(self, args, "setMobParent"); }
static PyObject* script_getMobIsComponent(PyObject* self, PyObject* args) { return script_API(self, args, "getMobIsComponent"); }
static PyObject* script_setMobIsComponent(PyObject* self, PyObject* args) { return script_API(self, args, "setMobIsComponent"); }
static PyObject* script_getMobIsStationary(PyObject* self, PyObject* args) { return script_API(self, args, "getMobIsStationary"); }
static PyObject* script_setMobIsStationary(PyObject* self, PyObject* args) { return script_API(self, args, "setMobIsStationary"); }
static PyObject * script_checkMobCollisionAt(PyObject * self, PyObject * args) { return script_API(self, args, "checkMobCollisionAt"); }

static PyMethodDef pySpaceRailerMethods[] = {
	{"numargs", script_NumArgs, METH_VARARGS, "Return the number of arguments received by the process."},
	{"getMapX", script_getMapX, METH_VARARGS, "Return the x-coordinate of the left edge of the viewport."},
	{"getMapY", script_getMapY, METH_VARARGS, "Return the y-coordinate of the top edge of the viewport."},
	{"getPlayerX", script_getPlayerX, METH_VARARGS, "Return the x-coordinate of the player."},
	{"getPlayerY", script_getPlayerY, METH_VARARGS, "Return the y-coordinate of the player."},
	{"setPlayerX", script_setPlayerX, METH_VARARGS, "Sets the x-coordinate of the player."},
	{"setPlayerY", script_setPlayerY, METH_VARARGS, "Sets the y-coordinate of the player."},
	{"getPlayerHP", script_getPlayerHP, METH_VARARGS, "Return the current HP of the player."},
	{"getPlayerWidth", script_getPlayerWidth, METH_VARARGS, "Return the width of the player sprite/object."},
	{"getPlayerHeight", script_getPlayerHeight, METH_VARARGS, "Return the height of the player sprite/object."},
	{"getStageScrollPixelsPerInterval", script_getStageScrollPixelsPerInterval, METH_VARARGS, "Return the number of pixels the stage scrolls each interval."},
	{"setStageScrollPixelsPerInterval", script_setStageScrollPixelsPerInterval, METH_VARARGS, "Sets the number of pixels to scroll the stage map for every interval."},	
	{"getStageScrollInterval", script_getStageScrollInterval, METH_VARARGS, "Return number of ms between stage scroll events."},
	{"setStageScrollInterval", script_setStageScrollInterval, METH_VARARGS, "Sets the number of ms between stage scroll events."},
	{"createMob", script_createMob, METH_VARARGS, "Create a new mob and return its ID."},
	{"getMobX", script_getMobX, METH_VARARGS, "Return a mob's x-coordinate."},
	{"getMobY", script_getMobY, METH_VARARGS, "Return a mob's y-coordinate."},
	{"setMobX", script_setMobX, METH_VARARGS, "Set a mob's x-coordinate."},
	{"setMobY", script_setMobY, METH_VARARGS, "Set a mob's y-coordinate."},
	{"getMobWidth", script_getMobWidth, METH_VARARGS, "Return a mob's current width."},
	{"getMobHeight", script_getMobHeight, METH_VARARGS, "Return a mob's current height."},
	{"setMobWidth", script_setMobWidth, METH_VARARGS, "Set a mob's width."},
	{"setMobHeight", script_setMobHeight, METH_VARARGS, "Set a mob's height."},
	{"setMobAngle", script_setMobAngle, METH_VARARGS, "Set a mob's angle."},
	{"getMobAngle", script_getMobAngle, METH_VARARGS, "Get a mob's angle."},
	{"getMobParent", script_getMobParent, METH_VARARGS, "Get a mob's parent mob ID."},
	{"setMobParent", script_setMobParent, METH_VARARGS, "Set a mob's parent mob ID."},
	{"getMobIsComponent", script_getMobIsComponent, METH_VARARGS, "Get a mob's comopnent status."},
	{"setMobIsComponent", script_setMobIsComponent, METH_VARARGS, "Set a mob's component status."},
	{"getMobIsStationary", script_getMobIsStationary, METH_VARARGS, "Get a mob's stationary status."},
	{"setMobIsStationary", script_setMobIsStationary, METH_VARARGS, "Set a mob's stationary status."},
	{"checkMobCollisionAt", script_checkMobCollisionAt, METH_VARARGS, "Check if a mob will collide with another object at a given x,y."},
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

