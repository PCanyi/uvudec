/*
UVNet Universal Decompiler (uvudec)
Copyright 2010 John McMaster <JohnDMcMaster@gmail.com>
Licensed under the terms of the LGPL V3 or later, see COPYING for details
*/

#include "uvdobjbin/object.h"
#include <typeinfo>

UVDBinaryObject::UVDBinaryObject()
{
}

UVDBinaryObject::~UVDBinaryObject()
{
	//Since we directly map the data into the section, prevent double free
	if( !m_sections.empty() )
	{
		//We own the data object and there are some other hacks that make it best to remove it the section instead of us
		(*m_sections.begin())->m_data = NULL;
	}
}
uv_err_t UVDBinaryObject::init(UVDData *data)
{
	//We have a single section, a raw binary blob
	UVDSection *section = NULL;

	uv_assert_err(UVDObject::init(data));

	section = new UVDSection();
	uv_assert(section);
	section->m_data = data;
	
	//Basic assumptions for a ROM image.  W is probably most debatable as we could be in flash or ROM
	section->m_R = UVD_TRI_TRUE;
	section->m_W = UVD_TRI_FALSE;
	section->m_X = UVD_TRI_TRUE;
	
	m_sections.push_back(section);
	
	return UV_ERR_OK;

error:
	m_data = NULL;
	return UV_DEBUG(UV_ERR_GENERAL);
}

uv_err_t UVDBinaryObject::canLoad(const UVDData *data, const UVDRuntimeHints &hints, uvd_priority_t *confidence,
		void *user)
{
	//While this may work, likely its not a good loader and should be a last resort
	//By convention though, if its a file and ends in .bin, seems likely its a binary image
	if( typeid(*data) == typeid(UVDDataFile) )
	{
		const UVDDataFile *dataFile = static_cast<const UVDDataFile *>(data);
		
		if( dataFile->m_sFile.find(".bin") != std::string::npos )
		{
			*confidence = UVD_MATCH_ACCEPTABLE;
			return UV_ERR_OK;
		}
	}
	*confidence = UVD_MATCH_POOR;
	return UV_ERR_OK;
}

uv_err_t UVDBinaryObject::tryLoad(UVDData *data, const UVDRuntimeHints &hints, UVDObject **out,
		void *user)
{
	UVDBinaryObject *binaryObject = NULL;
	
	binaryObject = new UVDBinaryObject();
	uv_assert_ret(binaryObject);
	uv_assert_err_ret(binaryObject->init(data));
	
	uv_assert_ret(out);
	*out = binaryObject;
	return UV_ERR_OK;
}

