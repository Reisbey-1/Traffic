#include "stdafx.h"
#include "Process.h"
#include "theClock.h"
#include "TrafficTesterDlg.h"
CList <CVehicle*> theVehiclesList;
CCrossHost theCrossHost;
CCrossHost * pD1 = &theCrossHost;

CTLight_T0 theTrafficLight;
CTLight_T0 * pD2 = &theTrafficLight;

CPedestrianLight thePedestrianLight;
CPedestrianLight * pD3 = &thePedestrianLight;

ICAN_Bus	*pTheCanBus = NULL;
ICAN_Node	*pTheCrossHost = NULL;
ICAN_Node	*pTheTrafficLight = NULL;
ICAN_Node	*pThePedestrianLight = NULL;

bool InitProcess()
{
	CWiFi *pwifi = CWiFi::GetWifi();
	pwifi->AddInternetObject(&theCrossHost);
	CReflector::GetReflector()->Set_TLS(theTrafficLight.GetState());		// add tl object to reflector.

	if (!CAN_Connect())
		return false;
	
	// clok
	typedef  LONG(*f)();
	f func = &clock_tick;
	myClock.AddCallBackFunction((LONG*)func);
	myClock.StartThread();
	
	return true;
}
void Master_Tick()
{
	// can bus objects 
	
	//theCrossHost.sy
	theCrossHost.sycroniseLOCALS();						// syncronise cross-host (schedular)
	theTrafficLight.sycroniseLOCALS();					// syncronise traffic light
	thePedestrianLight.sycroniseLOCALS();				// syncronise pedestrian light
	// 
	theTrafficLight.decide();

	CVehicle * pV =NULL;
	POSITION pos = theVehiclesList.GetHeadPosition();
	while (pos)
	{
		pV = theVehiclesList.GetNext(pos);
		if (pV)
			pV->run();
		//pV->move_forward();
		//pV->move_backward();			// only for testing
	}
	
	CTrafficTesterDlg::theObjectPtr->Invalidate();

}
void ReleaseProcess()
{
	myClock.KillThread();					// kill timer
	CAN_CleanUp();							// clean up can
	CWiFi::KillWifi();						// clean wifi
	CReflector::KillReflector(true);		// vehicle objects are deleted in reflector
	CVerkehr_Maler::KillMaler();			// kill painter
}
bool CAN_Connect()
{
	// ==================================
	// create CAN_Bus objects:
	// ==================================
	// ICAN_Bus *	pTheCanBus;					
	// ICAN_Nod *	pTheCrossHost
	// ICAN_Nod *	pTheTrafficLight
	// ICAN_Nod *	pThePedestrianLight
	// ==================================

	LONG cookie;									// dumy local

	/////////////////////////////////////////////////////////////////////////////
	// create theCanBus object
	HRESULT hr = CoCreateInstance(
		CLSID_CAN_Bus,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ICAN_Bus,
		(void **)&pTheCanBus);
	
	if (hr != S_OK)
		return false;
	// theCrossHost
	hr = S_FALSE;
	hr = CoCreateInstance(
		CLSID_CAN_Node,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ICAN_Node,
		(void **)&pTheCrossHost);

	if (hr != S_OK)
		return false;
	
	// theTrafficLight
	hr = S_FALSE;
	hr = CoCreateInstance(
		CLSID_CAN_Node,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ICAN_Node,
		(void **)&pTheTrafficLight);

	if (hr != S_OK)
		return false;

	
	// thePedestrianLight
	hr = S_FALSE;
	hr = CoCreateInstance(
		CLSID_CAN_Node,
		NULL,
		CLSCTX_INPROC_SERVER,
		IID_ICAN_Node,
		(void **)&pThePedestrianLight);

	if (hr != S_OK)
		return false;

	/// CrossHost
	
	p_CanCallBack_Function pcb = &CCrossHost::CallBackFunction;	
	//CCrossHost * pD1 = &theCrossHost;
	pTheCrossHost->AddCallBack((long**)&pcb, (long**)&pD1);
	pTheCrossHost->put_me(theCrossHost.GetState().nId);				// can node id from object id
	theCrossHost.InsertNodeInterface(&pTheCrossHost);
	pTheCanBus->Advice((IUnknown **)&pTheCrossHost, &cookie);
	pTheCrossHost->put_CanBus((IUnknown*)pTheCanBus);

	/// TrafficLight
	pcb = &CTLight_T0::CallBackFunction;
	//CTLight_T0 * pD2 = &theTrafficLight;
	pTheTrafficLight->AddCallBack((long**)&pcb, (long**)&pD2);
	pTheTrafficLight->put_me(theTrafficLight.GetState().nId);				// can node id from object id
	theTrafficLight.InsertNodeInterface(&pTheCrossHost);
	pTheCanBus->Advice((IUnknown **)&pTheTrafficLight, &cookie);
	pTheTrafficLight->put_CanBus((IUnknown*)pTheCanBus);

	/// PedestrianLight
	pcb = &CPedestrianLight::CallBackFunction;
	//CPedestrianLight * pD3 = &thePedestrianLight;
	pThePedestrianLight->AddCallBack((long**)&pcb, (long**)&pD3);
	pThePedestrianLight->put_me(thePedestrianLight.GetState().nId);				// can node id from object id
	thePedestrianLight.InsertNodeInterface(&pThePedestrianLight);
	pTheCanBus->Advice((IUnknown **)&pThePedestrianLight, &cookie);
	pThePedestrianLight->put_CanBus((IUnknown*)pTheCanBus);
	return true;

}
bool CAN_CleanUp()
{

	// clear up
	long l = 1;
	if (pTheCrossHost)
		while (l)
			l = pTheCrossHost->Release();


	// pTheTrafficLight
	l = 1;
	if (pTheTrafficLight)
		while (l)
			l = pTheTrafficLight->Release();
	

	// pThePedestrianLight
	l = 1;
	if (pThePedestrianLight)
		while (l)
			l = pThePedestrianLight->Release();

	//pTheCanBus
	l = 1;
	if (pTheCanBus)
		while (l)
			l = pTheCanBus->Release();
	return true;
}
 