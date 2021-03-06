#pragma once

#include <string>
#include <iostream>
#include <sstream>

#include <stdio.h>
#include <stdlib.h>

#include "CsIEventListenerXml.h"
#include "CsUserDefs.h"
#include "CsBarcodeTypes.h"
#include "Cslibcorescanner_xml.h"

#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/transport/TSocket.h>
#include <thrift/transport/TTransportUtils.h>

#include "../gen-cpp/SlaveController.h"

using namespace apache::thrift;
using namespace apache::thrift::protocol;
using namespace apache::thrift::transport;

using namespace slave_controller;

using namespace std;

class ScannerEventListener : public IEventListenerXml {
public:
    explicit ScannerEventListener(const bool &done);
    virtual ~ScannerEventListener();

    virtual void OnImageEvent( short eventType, int size, short imageFormat, char* sfimageData, int dataLength, std::string& pScannerData );
    virtual void OnVideoEvent( short eventType, int size, char* sfvideoData, int dataLength, std::string& pScannerData );
    virtual void OnBarcodeEvent( short eventType, std::string& pscanData );
    virtual void OnPNPEvent( short eventType, std::string ppnpData );
    virtual void OnCommandResponseEvent( short status, std::string& prspData );
    virtual void OnScannerNotification( short notificationType, std::string& pScannerData );
    virtual void OnIOEvent( short type, unsigned char data );
    virtual void OnScanRMDEvent( short eventType, std::string& prmdData );
    virtual void OnDisconnect();
    virtual void OnBinaryDataEvent( short eventType, int size, short dataFormat, unsigned char* sfBinaryData, std::string&  pScannerData);

    StatusID Open();
    void GetScanners();
    void GetAttribute();
    void GetAttributeNext();
    void GetAllAttributes();
    void SetAttribute();
    void SetAttributeStore();
    void SetZeroWeight();

    void RebootScanner();
    void ExecuteActionCommand(CmdOpcode opCode);
    void GetDeviceTopology();
    void FirmwareUpdate();
    void FirmwareUpdateFromPlugin();
    void StartNewFirmware();
    void AbortFirmwareUpdate();
    void GetVersion();

    std::string get_decode_data(std::string outXml);
    std::vector<std::string> stringTokernize(std::string inStr, char cDelim);

    bool scanner_attached = false;
    std::shared_ptr<TTransport> transport;
    std::shared_ptr<SlaveControllerClient> thrift_client;
};
