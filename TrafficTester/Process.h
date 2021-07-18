#pragma once
#include "stdafx.h"

extern CList <CVehicle*> theVehiclesList;
extern CCrossHost theCrossHost;
extern CTLight_T0 theTrafficLight;
extern CPedestrianLight thePedestrianLight;

extern ICAN_Bus  *pTheCanBus;
extern ICAN_Node *pTheCrossHost;
extern ICAN_Node *pTheTrafficLight;
extern ICAN_Node *pThePedestrianLight;

bool InitProcess();
void Master_Tick();
void ReleaseProcess();
bool CAN_Connect();
bool CAN_CleanUp();



