/*
UVNet Universal Decompiler (uvudec)
Copyright 2010 John McMaster <JohnDMcMaster@gmail.com>
Licensed under the terms of the LGPL V3 or later, see COPYING for details
*/

#ifndef UVD_ANALYSIS_ACTION
#define UVD_ANALYSIS_ACTION

class UVDAnalysisAction
{
public:
	UVDAnalysisAction();
	virtual ~UVDAnalysisAction();

public:
};

//Do initial analysis
class UVDAnalysisActionBegin : public UVDAnalysisAction
{
};

//Re-analyze the strings database
class UVDAnalysisActionAnalyzeStrings : public UVDAnalysisAction
{
};

#endif

