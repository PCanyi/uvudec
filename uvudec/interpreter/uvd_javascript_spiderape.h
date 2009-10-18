/*
Universal Decompiler (uvudec)
Copyright 2008 John McMaster
JohnDMcMaster@gmail.com
Licensed under terms of the three clause BSD license, see LICENSE for details
*/

#pragma once

#ifdef USING_SPIDERAPE

#include "uvd_interpreter.h"

/*
Wrapper on top of Mozilla's Javascript engine
*/

#include <sf.net/ape/spiderape.hpp>
#include <sf.net/ape/scriptable_base.hpp>

class UVDJavascriptSpiderapeInterpreter : public UVDInterpreter
{
public:
	UVDJavascriptSpiderapeInterpreter();
	virtual ~UVDJavascriptSpiderapeInterpreter();
	
	virtual uv_err_t init();

	virtual uv_err_t interpret(const UVDInterpreterExpression &exp, const UVDVariableMap &environment, std::string &sRet);
public:
	ape::MonkeyWrapper m_monkeyWrapper;
};

#endif //USING_SPIDERAPE
