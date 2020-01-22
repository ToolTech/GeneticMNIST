//*****************************************************************************
// File			: ctxVirtualMachine.h (stand alone)
// Description	: Execution of the neural network
// Author		: Anders Modén
// Product		: CorTeX 1.0.15
//		
// Copyright © 2015- ToolTech Software, Sweden
//			
// NOTE:	CorTeX is a software development kit (SDK) 
//			for neural networks and genetic programming. 
//			Licensed by ToolTech Software (Anders Modén).
//
//
// Revision History...							
//									
// Who	Date	Description						
//									
// AMO	150708	Created file 	(1.0.0)
//
//******************************************************************************
#ifndef __CTX_VIRTUAL_MACHINE_H__
#define __CTX_VIRTUAL_MACHINE_H__

#include <math.h>

#ifndef CTX_SKIP_TYPEDEFS

// Type definitions. Change these types to use your own

typedef float					gzFloat;
typedef unsigned int			gzUInt32;
typedef unsigned char			gzBool;	
typedef void					gzVoid;

// Boolean definitions. change to use your own

#define TRUE	1
#define FALSE	0

#endif	// CTX_SKIP_TYPEDEFS

#define SELU_ALPHA			1.6732632423544f
#define SELU_SCALE			1.0507009873555f
#define SELU_ALPHA_SCALE	1.7580993408474f

// ---------------- Built in neuron function ---------------

inline gzVoid ctxNeuronFunc_6(gzFloat *s)
{
	*s = (*s>0 ? *s : 0);
}

inline gzVoid ctxNeuronFunc_7(gzFloat *s)
{
	*s = (*s > 0 ? *s : expf(*s) - 1.0f);
}

inline gzVoid ctxNeuronFunc_8(gzFloat *s)
{
	*s = (*s > 0 ? SELU_SCALE * *s : SELU_ALPHA_SCALE * (expf(*s) - 1.0f));
}

// --------------- Built in utility functions ----------

inline gzFloat gzMax(gzFloat &s1,gzFloat &s2)
{
	return s1 > s2 ? s1 : s2;
}
// ----------------------------------- ctxVirtualMachineProgram -------------------

class ctxVirtualMachineProgram 
{
public:

	// ------ public attributes ------------

	gzFloat						*parameters;					// All registers are shared memory
	gzUInt32					*parameter_updateID;			// Parameter attributes. Update_Id is a id to enfoce update

	gzFloat						*input;
	gzUInt32					*input_updateID;

	gzFloat						*values;
	gzUInt32					*value_updateID;
};

//---------------- Callback structures ------------------------------------------------

typedef gzBool(*ctxVirtualMachineProgramFunc)(ctxVirtualMachineProgram *program);

typedef struct { ctxVirtualMachineProgramFunc *func; gzUInt32 length; } ctxVirtualMachineProgramInfo;

#endif //__CTX_VIRTUAL_MACHINE_H__



