#pragma once
#ifndef IBKR_ALGO_STRATEGY_IBKR_ALGO_CLIENT_H
#define IBKR_ALGO_STRATEGY_IBKR_ALGO_CLIENT_H

#include "EWrapper.h"
#include "EReaderOSSignal.h"
#include "EReader.h" 

#include <memory>

class EClientSocket;

class IBKR_Algo_Client : public EWrapper
{
public:
	IBKR_Algo_Client();
	~IBKR_Algo_Client();

	void setConnectOptions(const std::string&);
	void processMessages();

public: 
	bool connect(const std::string& host, int port, int clientId = 0);
	bool isConnected() const;

public: 
	void requestHistoricalData(int reqId, const Contract& contract, const std::string& endDateTime, const std::string& durationTime, const std::string& barSizeSetting,
		const std::string whatToShow, int useRTH, int formatDate, bool keepUpToDate, const TagValueListSPtr& chartOptions);

public:
	// --- Virtual Overrides for EWrapper interface methods ---
	#include "EWrapper_prototypes.h"

private: 
	void printContractMsg(const Contract& contract);
	void printContractDetailsMsg(const ContractDetails& contractDetails);
	void printContractDetailsSecIdList(const TagValueListSPtr& secIdList);
	void printContractDetailsIneligibilityReasonList(const IneligibilityReasonListSPtr& ineligibilityReasonList);
	void printBondContractDetailsMsg(const ContractDetails& contractDetails);
	void printSoftDollarTier(const SoftDollarTier& softDollarTier);

private:
	EReaderOSSignal m_osSignal;
	 EClientSocket* const m_pClient;
	std::unique_ptr<EReader> m_pReader;

	int m_orderId;
	bool m_extraAuth;

};



#endif // !IBKR_ALGO_STRATEGY_IBKR_ALGO_CLIENT_H
