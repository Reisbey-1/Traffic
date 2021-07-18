#include "stdafx.h"
#include "WiFi.h"
#include "TrafficLib_Globals.h"

namespace TrafficLib
{

	CWiFi* CWiFi::theWifi = NULL;
//	int    CWiFi::theIndexer = 0;

	CWiFi* CWiFi::GetWifi()
	{
		if (!theWifi)
		{
			theWifi = new CWiFi;
		}
		return theWifi;

	}
	void CWiFi::KillWifi()
	{
		if (theWifi)
		{
			delete theWifi;
			theWifi = NULL;
		}

	 }
	CWiFi::CWiFi()
	{
		m_plistOfInOj = new map<int, IInternetObject*> ();
		m_pIt = new map<int, IInternetObject*>::iterator ();
	
	}
	CWiFi::~CWiFi()
	{
		delete m_plistOfInOj;
		delete m_pIt;
	}
	
	// returns positive if it is added to map
	// returns 0 if there is an entity with given key and it is not added to map
	int  CWiFi::AddInternetObject(IInternetObject* newVal)
	{
		// create a key here
		int nReturn = 0;
		int nKey = newVal->get_IP_adress().adress;
		if (m_plistOfInOj->find(nKey) == m_plistOfInOj->end()) {
			// not found
			// add here
			m_plistOfInOj->insert(make_pair(nKey,newVal));
			nReturn = nKey;
		}
		else {
			// found
			//theIndexer--;
		}


		
		return nKey;
	}
	void  CWiFi::DeleteVehicle(int nKey)
	{
		*m_pIt = m_plistOfInOj->find(nKey);
		m_plistOfInOj->erase(*m_pIt);
	}

	// as soon as tcp/ip telegram is received, it is forwarded to target object
	void  CWiFi::receiveTcpTelegram(const sTCP_IP_TLG& tlg)
	{
		int nKey = tlg.m_nTarget_TCP_IP_address.adress;
		IInternetObject * pTarget = 0;

		if (m_plistOfInOj->find(nKey) == m_plistOfInOj->end()) {
			// not found
		}
		else {
			// found
			pTarget = m_plistOfInOj->at(nKey);			// get target object				
			pTarget->RcvTlg(tlg);						// put tcp/ip telegram on target object
		}
	}
	

}	// name space