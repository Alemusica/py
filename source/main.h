/* 

pyext - python script object for PD and MaxMSP

Copyright (c) 2002 Thomas Grill (xovo@gmx.net)
For information on usage and redistribution, and for a DISCLAIMER OF ALL
WARRANTIES, see the file, "license.txt," in this distribution.  

-------------------------------------------------------------------------

*/

#ifndef __MAIN_H
#define __MAIN_H

#include <flext.h>
#include <Python.h>
#ifndef NT
#include <unistd.h>
#endif

#if !defined(FLEXT_VERSION) || (FLEXT_VERSION < 203)
#error You need at least flext version 0.2.3
#endif

#define PY__VERSION "0.0.3pre"


#define I int
#define C char
#define V void
#define BL bool
#define F float
#define D double


#include "main.h"

class py:
	public flext_base
{
	FLEXT_HEADER(py,flext_base)

public:
	py();
	~py();

protected:
	C *sName;
	I hName;

	class lookup {
	public:
		lookup(I hash,PyObject *mod);
		~lookup();

		V Set(PyObject *mod);
		V Add(lookup *l);

		I modhash;
		PyObject *module,*dict;
		lookup *nxt;
	};

	static lookup *modules;
	static I pyref;

	V SetArgs(I argc,t_atom *argv);
	V ImportModule(const C *name);
	V SetModule(I hname,PyObject *module);
	V ReloadModule();
	PyObject *GetModule();
	PyObject *GetFunction(const C *func);
	static PyObject *MakePyArgs(const t_symbol *s,I argc,t_atom *argv);
	static t_atom *GetPyArgs(int &argc,PyObject *pValue);

	static C *strdup(const C *s);

	enum retval { nothing,atom,tuple,list };
};

#endif