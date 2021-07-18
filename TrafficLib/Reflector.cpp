#include "stdafx.h"
#include "Reflector.h"
namespace TrafficLib
{
	CReflector* CReflector::me = NULL;

	CReflector* CReflector::GetReflector()
	{
		if (!me)
			me = new CReflector;
		return me;
	}
	void CReflector::KillReflector(bool bDeleteObj)
	{
		if (bDeleteObj)
			CReflector::DeleteObjectList();
	
		if (me)
		{
			CNode<CVehicle> *Node = NULL;
			Node = me->m_linked_List.GetLast();
			while (Node)
			{
				me->m_linked_List.RemoveTail();
				Node = me->m_linked_List.GetLast();
			}
			delete me;
		}
		me = NULL;
	}


	void CReflector::DeleteObjectList()
	{
		if (me)
		{
			CVehicle *t = NULL;
			t= me->m_linked_List.GetFirstObject();
			while (t)
			{
				delete t;
				t = NULL;
				t = me->m_linked_List.GetNextObject();
			}
		}

	}
	CReflector::CReflector()
	{
		m_pTls = NULL;
	}
	CReflector::~CReflector()
	{

	}
	
	void CReflector::addObstruction(CVehicle& rV, bool bHead)
	{
		if (bHead)
			m_linked_List.AddHead(rV);
		else
			m_linked_List.AddTail(rV);
	}
	CVehicle* CReflector::GetFirst()
	{
		//m_linked_List.AddHead(rV);
		if (m_linked_List.GetFirst())
		{
			return m_linked_List.GetFirst()->pObj;

		}
		else return NULL;
	}
	CVehicle* CReflector::GetLast()
	{
		//m_linked_List.AddHead(rV);
		if (m_linked_List.GetLast())
		{
			return m_linked_List.GetLast()->pObj;

		}
		else return NULL;
	}
	CVehicle* CReflector::Next()
	{
		CNode<CVehicle>* pdNode = m_linked_List.GetNext();
		if (pdNode)
		{
			return pdNode->pObj;
		}
		else return NULL;
	}
	void CReflector::Set_TLS(CTL_State& rTL)
	{
		m_pTls = &rTL;
	}
	CTL_State& CReflector::Get_TLS()
	{
		return *m_pTls;
	}
	bool CReflector::Measure(CVehicle * pRefVehicle, int& nBackDistance, int& nFortDistance)
	{
		// find node for pRefVehicle
		// from this node find previous and next data(vehicles object)
		// calculate m_nPos members the differences.
		// that's all !!!
		
		nFortDistance = 10000;
		nBackDistance = 10000;
		CNode<CVehicle> *Node = NULL;
		CNode<CVehicle> *Next = NULL;
		
		CVehicle * pnext = NULL;
		CVehicle * ppre = NULL;

		bool bfound = false;
		Node = m_linked_List.GetFirst();
		if (Node)
		{
			while (Node->pNext)
			{
				if (Node->pObj == pRefVehicle)
				{
					bfound = true;
					break;
					}
				Node = Node->pNext;
			}  // while

			if (bfound)
			{

					if ((Node->pNext))
					{
						pnext = (Node->pNext->pObj);
						if (pnext)
							nFortDistance = (pnext->m_nPos)- (pRefVehicle->m_nPos) ;
					}
					if ((Node->pPrev))
					{ 
						ppre = (Node->pPrev->pObj);
					if (ppre)
						nBackDistance = (pRefVehicle->m_nPos) - ((Node->pPrev)->pObj->m_nPos);
					}
	/**/	

			}

		}
		return bfound;
	}
	
} // name space
