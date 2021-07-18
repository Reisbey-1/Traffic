#pragma once
#define SIZE_TCP_TELEGRAM 100
#define NONE 0
#define RED	1
#define YELLOW	2
#define GREEN	3
#define NUM_CAN_OBJECTS 5

#define CMS_BROADCAST		20    /// cms brocast traffic light
#define CMS_COMMAND			30    /// cms brocast pedestrian light

typedef  void(*p_CanCallBack_Function) (void** ppObject,  BYTE * msg, BYTE size);

struct TRAFFICLIB_API sTCP_IP_ADDRESS
{
	sTCP_IP_ADDRESS() {};
	sTCP_IP_ADDRESS(long va) { adress = va; }
	long adress;
	bool					operator == (const sTCP_IP_ADDRESS& st)
	{
		if (this == &st)
			return true;

		if(adress == st.adress)
			return true;
		else
			return false;
	}
	sTCP_IP_ADDRESS&		operator =	(const sTCP_IP_ADDRESS& st)
	{
		if (this == &st)
			return *this;
		adress = st.adress;
		return *this;
	}
	/**/
};
struct sTCP_IP_TLG
{
	//enum sz_tlg { SIZE_TCP_TELEGRAM = 100 };
	int m_nTelegramId;
	sTCP_IP_ADDRESS m_nSouece_TCP_IP_address;
	sTCP_IP_ADDRESS m_nTarget_TCP_IP_address;
	BYTE m_data[SIZE_TCP_TELEGRAM];
	/*
	sTCP_IP_TLG() 
	{
		m_nTelegramId = 0;
		m_nSouece_TCP_IP_address.adress = 0;
		m_nTarget_TCP_IP_address.adress = 0;
	};
	*/
};

class TRAFFICLIB_API CTcp_IP_Telegram
{
public:
	CTcp_IP_Telegram()
	{
		m_tlg.m_nSouece_TCP_IP_address = sTCP_IP_ADDRESS{ 0 };
		m_tlg.m_nTarget_TCP_IP_address = sTCP_IP_ADDRESS{ 0 };
		for (int i = 0; i < SIZE_TCP_TELEGRAM; i++)
			m_tlg.m_data[i] = 0;
	};
	~CTcp_IP_Telegram() {};
	sTCP_IP_ADDRESS Get_TargetTcpAddress() { return m_tlg.m_nTarget_TCP_IP_address; }
	sTCP_IP_ADDRESS Get_SourceTcpAddress() { return m_tlg.m_nSouece_TCP_IP_address; }
protected:
	/*
	int m_nTelegramId;
	sTCP_IP_ADDRESS m_nSouece_TCP_IP_address;
	sTCP_IP_ADDRESS m_nTarget_TCP_IP_address;
	BYTE m_data[SIZE_TCP_TELEGRAM];
*/
	sTCP_IP_TLG m_tlg;

};
class TRAFFICLIB_API IInternetObject
{
public:
	virtual void RcvTlg(const sTCP_IP_TLG tlg) = 0;
	virtual void RlsTlg(sTCP_IP_TLG& tlg) =0;
	virtual sTCP_IP_ADDRESS get_IP_adress() = 0;
protected:
	sTCP_IP_ADDRESS  m_tcp_ip_address;
	virtual void TCP_execute(sTCP_IP_TLG& tlg) = 0;
};
