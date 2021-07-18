#include "stdafx.h"
#include "Vehicle.h"
namespace TrafficLib
{

	CVehicle::CVehicle()
	{
		m_nSpeed	= 0;
		m_nPos		= 0;
		m_nAxis		= 0;
		m_tcp_ip_address = sTCP_IP_ADDRESS{ 0 };
		m_pSensor = new CDistanceSensor(this);
	}
	CVehicle::CVehicle(sTCP_IP_ADDRESS& adr, int Pos, int axis, int velocity)
	{
		m_nSpeed = velocity;
		m_nPos = Pos;
		m_nAxis = axis;
		m_tcp_ip_address = adr; // sTCP_IP_ADDRESS{ 0 };
		m_pSensor = new CDistanceSensor(this);
	}

	CVehicle::~CVehicle()
	{
		// remove itself from reflector list

		// delete front sensor
		delete m_pSensor;
	}
	void CVehicle::get_state(CVehicleState &s)
	{
		s.m_nPos	= m_nPos;;
		s.m_nSpeed	= m_nSpeed;;
		s.m_nAxis	= m_nAxis;;
	}



	//////////////////////////////////////////////////////////////////////////////
	void CVehicle::get_Telegram(sTCP_IP_TLG& tlg)
	{
		tlg.m_nTelegramId = 0;
		tlg.m_nSouece_TCP_IP_address = m_tcp_ip_address;
		for (int i = 0; i < SIZE_TCP_TELEGRAM; i++)
			tlg.m_data[i] = 0;
	}

	sTCP_IP_ADDRESS CVehicle::get_IP_adress()
	{
		return m_tcp_ip_address;
	}

	// - it calls execute member function of internet objet
	//   when a tcp/ip telegram is received targeting the internet object
	// - it is called by Wifi object
	void CVehicle::RcvTlg(sTCP_IP_TLG tlg )
	{
		sTCP_IP_ADDRESS adrTarget = tlg.m_nTarget_TCP_IP_address ;
		
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
	void CVehicle::TCP_execute(sTCP_IP_TLG& tlg)
	{
		// do whatever must be done
		Beep(1000, 300);
	}
	
	// telegram must be praperd outside the member function
	// only put the telegram on global singleton wifi object
	void CVehicle::RlsTlg(sTCP_IP_TLG& tlg)
	{
		CWiFi::GetWifi()->receiveTcpTelegram(tlg);
	}
	////////////////////////////////////////////////////////////////////////////////


	/// interface implementation
	void CVehicle::move_forward()
	{
		
		//return;
		if (m_nAxis == 0)
			m_nPos += m_nSpeed;
		else
			m_nPos -= m_nSpeed;
	}
	void CVehicle::move_backward()
	{
		//return;
		if (m_nAxis == 0)
			m_nPos -= m_nSpeed;
		else
			m_nPos += m_nSpeed;
	}
	void CVehicle::halt()
	{
		//Beep(1000, 20);
	}

	void CVehicle::run()
	{
		// to do 
		// 1) get statete of traffic light ( *over wifi-net via cross-host in simulation *, by eye of driver in reality, by sensor in autonomus cars)
		// 2) get distance to for and back vehicle (*over distance simulation*)
		// 3) calculate forward distance to traffic light (from its state)

		int nfortDistance;	// fort distance
		int nbackDistance;	// back distance
		int nDistanceToTL;	// its distance to traffic light
		
		// need any other !!!
		// 
		

		// 4) decide what to do (contruct process state machine)

		// locals
		float nTrafficLightVicinity = 100;	    // traffic light vicinity
		float nTrafficLightposition = 300;	// !! dynamic ?
		BYTE nTLState = NONE;				// may have value of #define NONE 0, RED,  YELLOW  GREEN
		             				        // update it from CTLighht_T0    CAN object   !!!!!!!!!!!!
											// read PDO 
		CTL_State &rtl = CReflector::GetReflector()->Get_TLS();
		nTLState = rtl.nlamp;
		float nPos = 1.0* m_nPos; 				    // vehicle position
		float nsensor_measure = m_pSensor->measure_front_distance();		    // sensor measure get from distance sensor
		float ntolerance = 30.0;					// tolerance
	
		bool bIsApproacing = false;			// 
		bool bAtTrafficLight = false;		// 
		bool bAfterTrafficLight = false;	// 
		bool bSubCase_1 = false;
		bool bSubCase_2 = false;
		bool bSubCase_3 = false;
		bool bSubCase_4 = false;
		bool bSubCase_5 = false;
	
		bool bCase_A = false;
		bool bCase_B = false;
		bool bCase_C = false;
		bool bCase_D = false;

		bIsApproacing = nPos < (nTrafficLightposition - (nTrafficLightVicinity / 2));
		bAtTrafficLight = abs(nTrafficLightposition - nPos) <= (nTrafficLightVicinity / 2);
		bAfterTrafficLight = (nPos > nTrafficLightposition);
		bSubCase_1 = bIsApproacing && (nsensor_measure > ntolerance);
		bSubCase_2 = bIsApproacing && (nsensor_measure <= ntolerance);
		bSubCase_3 = bAtTrafficLight;
		bSubCase_4 = nsensor_measure > ntolerance;
		bSubCase_5 = nsensor_measure <= ntolerance;

		bCase_A = (nTLState == RED)     && (bIsApproacing || bAtTrafficLight);
		bCase_B = (nTLState == YELLOW) && (bIsApproacing || bAtTrafficLight);
		bCase_C = (nTLState == GREEN) && (bIsApproacing || bAtTrafficLight);
		bCase_D = bAfterTrafficLight;

		if (bCase_A)
		{
			if (bSubCase_1)
				move_forward();
			else if(bSubCase_2 || bSubCase_3)
				halt();
			return;
		}
		if (bCase_B)
		{
			if (bSubCase_1|| bSubCase_3)
				move_forward();
			else if (bSubCase_2 )
				halt();
			return;
		}
		if (bCase_C)
		{
			if (bSubCase_1 || bSubCase_3)
				move_forward();
			else if (bSubCase_2)
				halt();
			return;
		}
		if (bCase_D)
		{
			if (bSubCase_4)
				move_forward();
			else if (bSubCase_5)
				halt();
			return;
		}
		return;
	}



} // name space
