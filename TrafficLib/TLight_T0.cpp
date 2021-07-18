#include "stdafx.h"
#include "TLight_T0.h"
namespace TrafficLib
{

	CTLight_T0::CTLight_T0()
	{
		m_pICAN_Nod = NULL;
		m_pICAN_Nod = NULL;
		for (int i = 0; i< NUM_CAN_OBJECTS; i++)
			for (int j = 0; j < 8; j++)
				m_PDO[i][j] = 0;
		
		m_nGreenCounter = 0;
		m_nRedCounter = 50;

	}
	CTLight_T0::~CTLight_T0()
	{
	}
	CTL_State& CTLight_T0::GetState()
	{
		// get ls
		return m_nState	;
	}

	void CTLight_T0::InsertNodeInterface(ICAN_Node** pNodeInterface)
	{
		m_pICAN_Nod = *pNodeInterface;
	}
	void CTLight_T0::CallBackFunction(void** ppObject, BYTE* f, BYTE size)
	{
		CTLight_T0 * self = static_cast<CTLight_T0*>(*ppObject);
		self->CAN_execute(f, size);
	}

	void CTLight_T0::CAN_execute(BYTE * msg, BYTE size)
	{
		/*
		//			BYTE 0		: node Id  				    :	sending node id
		//			BYTE 1		: command  				    :	sending node id
		*/
		BYTE sendingNodId = msg[0];
		BYTE cmd = msg[1];

		// if I did send the message  then quit
		if (sendingNodId == m_nState.nId)
			return;
		////////////////////////////////////////////////////////////////////////////

		if (cmd >= CMS_COMMAND)
		{
			;
		}
		else if (cmd == CMS_BROADCAST)
		{
			for (int i = 0; i < 8; i++)
				m_PDO[sendingNodId][i] = msg[i];
		}


	}
	void CTLight_T0::decide()
	{
		return;
		if (m_nRedCounter)
		{
			m_nState.nlamp = RED;
			m_nRedCounter--;
			m_nGreenCounter = 50;
		}
		else {
			m_nState.nlamp = GREEN;
			m_nGreenCounter--;
			if (m_nGreenCounter == 0)
				m_nRedCounter = 50;
		}

	}

	void CTLight_T0::sycroniseLOCALS()
	{
		bool bset = true;
		tCAN can_sMsgBroadCast;
		tCAN* pCan_sMsgBroadCast;
		pCan_sMsgBroadCast = &can_sMsgBroadCast;
		CTL_State ls = GetState();											// from objetc to locale state 
		ls.GetCanState(can_sMsgBroadCast);									// from state to can-msg
		can_sMsgBroadCast.id = CMS_BROADCAST;								// id is the same can message type
		setget_PDO(can_sMsgBroadCast, bset);							    // Update its local part 
		if (m_pICAN_Nod)
		{
			//m_pICAN_Nod->Out(&can_sMsgBroadCast);							// Update its part in other's PDO  throgh can bus
			m_pICAN_Nod->Out(&pCan_sMsgBroadCast);							// Update its part in other's PDO  throgh can bus
		}
	}
	bool CTLight_T0::setget_PDO(tCAN& msg, bool set)
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
}	// name space
