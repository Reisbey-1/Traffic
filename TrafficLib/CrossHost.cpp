
#include "stdafx.h"
#include "CrossHost.h"

namespace TrafficLib
{
	CCrossHost::CCrossHost()
	{
		m_pICAN_Nod = NULL;
		for (int i = 0;i< NUM_CAN_OBJECTS; i++)
			for (int j = 0; j < 8; j++)
			m_PDO[i][j] = 0;		
	}
	CCrossHost::~CCrossHost()
	{
	}

	void CCrossHost::InsertNodeInterface(ICAN_Node** pNodeInterface)
	{
		m_pICAN_Nod = *pNodeInterface;
	}

	void CCrossHost::CallBackFunction(void** ppObject, BYTE* f, BYTE size)
	{
		CCrossHost * self = static_cast<CCrossHost*>(*ppObject);
		self->CAN_execute(f, size);
	}

	void CCrossHost::CAN_execute(BYTE * msg, BYTE size)
	{
		/*
		//			BYTE 0		: node Id  				    :	sending node id
		//			BYTE 1		: command  				    :	sending node id
		*/
		BYTE sendingNodId = msg[0];
		BYTE type = msg[1];

		// if I did send the message  then quit
		if (sendingNodId == m_nState.nId ) 
			return;
		////////////////////////////////////////////////////////////////////////////

		if (type >= CMS_COMMAND)
		{
			;
		}
		else if (type == CMS_BROADCAST)
		{
			for (int i = 0; i < 8; i++)
				m_PDO[sendingNodId][i] = msg[i];
		}

	}
	void CCrossHost::decide()
	{


	}

	//////////////////////////////////////////////////////////////////
	// IInternetObject  S T A R T
	//////////////////////////////////////////////////////////////////
	
	sTCP_IP_ADDRESS CCrossHost::get_IP_adress()
	{
		return m_tcp_ip_address;
	}

	// call execute member function of internet objet
	// when a tcp/ip telegram is received targeting the internet object
	void CCrossHost::RcvTlg(sTCP_IP_TLG tlg)
	{
		sTCP_IP_ADDRESS adrTarget = tlg.m_nTarget_TCP_IP_address;

		// has telegram landed to correct address ?
		// here tcp/ip telegram must be decoded and processed !!
		// 
		if (m_tcp_ip_address == adrTarget)
		{
			TCP_execute(tlg);							// yes, execute objects function
		}
		// wifi tlg is received 
		// do necessary service !!

	}

	// telegram must be praperd outside the member function
	// only put the telegram on global singleton wifi object
	void CCrossHost::RlsTlg(sTCP_IP_TLG& tlg)
	{
		CWiFi::GetWifi()->receiveTcpTelegram(tlg);
	}
	
	void CCrossHost::TCP_execute(sTCP_IP_TLG& tlg)
	{

	}
	//////////////////////////////////////////////////////////////////
	// IInternetObject  E N D
	//////////////////////////////////////////////////////////////////
	// ICrossHost  S T A R T
	//////////////////////////////////////////////////////////////////


	void CCrossHost::get_Telegram(sTCP_IP_TLG& tlg)
	{
		tlg.m_nTelegramId = 0;
		tlg.m_nSouece_TCP_IP_address = m_tcp_ip_address;
		for (int i = 0; i < SIZE_TCP_TELEGRAM; i++)
			tlg.m_data[i] = 0;
	}

	/*
	 ICrossHost  E N D
	*/
	void CCrossHost::sycroniseLOCALS()
	{
		bool bset = true;
		tCAN can_sMsgBroadCast;
		tCAN* pCan_sMsgBroadCast = &can_sMsgBroadCast;
		CCH_State chs = GetState();											// from objetc to locale state 
		chs.GetCanState(can_sMsgBroadCast);										// from state to can-msg
		can_sMsgBroadCast.id = CMS_BROADCAST;
		setget_PDO(can_sMsgBroadCast, bset);									    // Update its local part 
		if (m_pICAN_Nod)
		{
			//m_pICAN_Nod->Out(&can_sMsgBroadCast);									// Update its part in other's PDO  throgh can bus
			m_pICAN_Nod->Out(&pCan_sMsgBroadCast);									// Update its part in other's PDO  throgh can bus
		}
	}
	bool CCrossHost::setget_PDO(tCAN& msg, bool set)
	{
		BYTE ndId = msg.data[0] & 0x0F;
		if (set)
		{
			// if the class object is to be syncronised  to msg, msg must be of wright type !
			if (!((msg.data[0] & 0xE0) == CMS_BROADCAST))				// 1110 0000 = 0xE0
				return false;										// wrong message type
			else
				for (int i = 0; i < 8; i++)
					m_PDO[ndId][i] = msg.data[i];
		}
		else
		{
			for (int i = 0; i < 8; i++)
				msg.data[i] = m_PDO[ndId][i];
		}
		return true;
	}
	CCH_State& CCrossHost::GetState()
	{
		// get ls
		return m_nState;
	}

}	// name space