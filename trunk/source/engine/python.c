#if 0

#include "python.h"
#include "server.h"

static qboolean python_inited = qfalse;
static void Python_Init(void)
{
	if(python_inited)
		return;

	Py_Initialize();

	python_inited = qtrue;
}

static long PullLong(PyObject *o)
{
	long l = PyInt_AsLong(o);
	Py_DECREF(o);
	return l;
}

typedef struct {
    PyObject_HEAD
    gentity_t *ent;
} svEntity_t;

static PyObject *svEntity_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	svEntity_t *self = (svEntity_t *)type->tp_alloc(type, 0);

	if (self != NULL) {
		self->ent = G_Spawn();
		if(self->first == NULL)
		{
			Py_DECREF(self);
			return NULL;
		}
	}

	return (PyObject *)self;
}

static void svEntity_dealloc(svEntity_t *self)
{
	G_FreeEntity(self->ent);
    self->ob_type->tp_free((PyObject *)self);
}

static PyMethodDef svEntity_methods[] = {
    {"setPosition", (PyCFunction)0, 0, "setPosition(type, position, velocity, time_bias=0, duration=0)"},
	{"getPosition", (PyCFunction)0, 0, "([fff][fff]) getPosition()"},
	{"addEvent", (PyCFunction)0, 0, "addEvent(event, param, predict=false)"}, // events get bothgame support?
	
    {NULL}  /* Sentinel */
};

static PyTypeObject svEntity_type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "server.entity",           /*tp_name*/
    sizeof(svEntity),          /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)svEntity_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "Server entitys",           /* tp_doc */
    0,		               /* tp_traverse */
    0,		               /* tp_clear */
    0,		               /* tp_richcompare */
    0,		               /* tp_weaklistoffset */
    0,		               /* tp_iter */
    0,		               /* tp_iternext */
    svEntity_methods,          /* tp_methods */
    svEntity_members,          /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    0,      /* tp_init */
    0,                         /* tp_alloc */
    svEntity_new,                 /* tp_new */
};

static PyMethodDef server_methods[] = {
    {NULL}  /* Sentinel */
};

void Python_InitServerTypes(void)
{
    PyObject* m;

	Python_Init();

    svEntity_type.tp_new = PyType_GenericNew;
    if (PyType_Ready(&svEntity_type) < 0)
        return;

    m = Py_InitModule3("server", server_methods, "Server module takes care of all game logic.");

    Py_INCREF(&svEntity_type);
    PyModule_AddObject(m, "entity", (PyObject *)&svEntity_type);
}

#endif
