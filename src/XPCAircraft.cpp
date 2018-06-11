#include "XPCAircraft.h"

XPCAircraft::XPCAircraft(
		const char *			inICAOCode,
		const char *			inAirline,
		const char *			inLivery)
{
	mPlane = XPMPCreatePlane(inICAOCode, inAirline, inLivery, AircraftCB, nullptr,
							 static_cast<void *>(this));
}

XPCAircraft::~XPCAircraft()
{
	XPMPDestroyPlane(mPlane);
}

XPMPPlaneCallbackResult	XPCAircraft::AircraftCB(
		XPMPPlaneID			/*inPlane*/,
		XPMPPlaneDataType	inDataType,
		void *				ioData,
		void *				inRefcon)
{
	XPCAircraft * me = static_cast<XPCAircraft *>(inRefcon);
	switch(inDataType) {
	case xpmpDataType_Position:
		return me->GetPlanePosition((XPMPPlanePosition_t *) ioData);
	case xpmpDataType_Surfaces:
		return me->GetPlaneSurfaces((XPMPPlaneSurfaces_t *) ioData);
	case xpmpDataType_Radar:
		return me->GetPlaneRadar((XPMPPlaneRadar_t *) ioData);
	default:
		return xpmpData_Unavailable;
	}
}
