#pragma once
#include <list> 
#include <map>
#include <iterator> 
using namespace std;
#include "Vehicle.h"
#include "TrafficLib_Globals.h"

namespace TrafficLib
{
	
	class TRAFFICLIB_API CWiFi
	{
	protected:
		CWiFi();
		~CWiFi();
		static CWiFi* theWifi;
//		static int   theIndexer;

	public:
		int  AddInternetObject(IInternetObject* newVal);
		void  DeleteVehicle(int nKey);
		void  receiveTcpTelegram(const sTCP_IP_TLG& tlg);


		static CWiFi* GetWifi();
		static void KillWifi();

	protected:
		map<int, IInternetObject*> * m_plistOfInOj;
		map<int, IInternetObject*>::iterator *m_pIt;
	
	};
}	// name space

