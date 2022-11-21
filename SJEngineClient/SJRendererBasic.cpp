#include "SJRendererBasic.h"
#include <SJDebug.h>
#include <SJWindow.h>
#include "SJWindowResMgr.h"

// Static Var
// Static Func

// member Var
SJRendererBasic::SJRendererBasic()
	:  m_Image(nullptr)
{

}

SJRendererBasic::~SJRendererBasic()
{
}

// member Func

void SJRendererBasic::Render()
{
	RenderImage(m_Image);
}

void SJRendererBasic::TransSetting(const SJString& _Image, float4 _Scale, float4 _PivotPos/*,int _TransRGB*/)
{
	m_Image = SJWindowResMgr::Inst().FindImage(_Image);

	if (nullptr == m_Image)
	{
		SJDebug::AssertMsg("if (nullptr == m_Image)");
	}

	m_RenderScale = _Scale;
	// m_TransColor = _TransRGB;
	m_RenderingType = RENDERINGMODE::TRANS;
	m_PivotPos = _PivotPos;
}


