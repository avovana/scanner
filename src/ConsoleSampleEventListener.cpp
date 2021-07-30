/*
 * ©2015 Symbol Technologies LLC. All rights reserved.
 */

#include "ConsoleSampleEventListener.h"
#include "ISO15434formatEnvelope.h"

/* standard C includes */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* standard template library includes */
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <errno.h>
#include <cstring>
#include <time.h>
#include "pugixml.hpp"


ScannerEventListener::ScannerEventListener()
{
    std::shared_ptr<TTransport> socket(new TSocket("localhost", 9090));
    std::shared_ptr<TTransport> transport(new TBufferedTransport(socket));
    std::shared_ptr<TProtocol> protocol(new TBinaryProtocol(transport));

    thrift_client.reset(new SlaveControllerClient(protocol));

    try {
        transport->open();

        thrift_client->scanner_status(ScannerStatus::Ready);
        cout << "scanner_status" << endl;
        thrift_client->scanner_status(ScannerStatus::Stop);
        cout << "scanner_status" << endl;
    }
    catch (TException &tx) {
        cout << "ERROR: " << tx.what() << endl;
    }

}

ScannerEventListener::~ScannerEventListener()
{
    transport->close();
	Close();
}

StatusID ScannerEventListener::Open()
{
    StatusID status;
    ::Open(this, SCANNER_TYPE_ALL, &status);
    if(status != STATUS_OK)
    {
        return status;
    }

    std::string inXml = "<inArgs><cmdArgs><arg-int>6</arg-int><arg-int>1,2,4,8,16,32</arg-int></cmdArgs></inArgs>";
    std::string outXml;
    ::ExecCommand(CMD_REGISTER_FOR_EVENTS, inXml, outXml, &status);   
    return status;
}

void ScannerEventListener::GetScanners()
{
    unsigned short count;
    vector<unsigned int> list;
    string outXml;
    StatusID eStatus;

    ::GetScanners(&count, &list, outXml, &eStatus);
    
     std:: cout  << "================================" << endl;

    if ( eStatus != STATUS_OK )
    {
        std:: cout  << "Get Scanners failed. Can't connect to the corescanner." << endl;
        return ;
    }

    std:: cout  << "Get Scanners command success. " << endl << endl;
    std:: cout  << "Scanner Count: " << count << endl;
    for(int x=0; x<count; x++)
    {
        std:: cout  << "Scanner IDs : " << list[x] << endl;
        scanner_attached = true;
        std:: cout  << "scanner_attached " << scanner_attached << endl;
    }
    std:: cout  << "Out XML : " << outXml.data() << endl;
    std:: cout  << "================================" << endl << endl;
}

void ScannerEventListener::GetDeviceTopology()
{
    string inXml;
    string outXml;
    StatusID sId;
    
    std:: cout  << "================================" << endl;
    
    ::ExecCommand(CMD_GET_DEVICE_TOPOLOGY, inXml, outXml, &sId);
    
    if(sId == STATUS_OK)
    {
        std:: cout  << "Get Device Topology command success. " << endl << endl;
        std:: cout  << "Out XML : " << outXml.data() << endl;
    }
    else
    {
        std:: cout << "Get Device Topology command failed. Error code : " << sId <<endl;
    }    
    
    std:: cout  << "================================" << endl << endl;
}

void ScannerEventListener::GetAttribute()
{
    std::string scannerID = "";
    std:: cout  << "Enter Scanner ID : " << endl;
    cin >> scannerID;
    std:: cout  << "Enter attribute number or comma separated attribute numbers : " ;
    std::string attribute_number = "";
    cin >> attribute_number;

    std::string inXml = "<inArgs><scannerID>" + scannerID + 
                        "</scannerID><cmdArgs><arg-xml><attrib_list>" + 
                        attribute_number + "</attrib_list></arg-xml></cmdArgs></inArgs>";
          
    StatusID sId;
    std::string outXml;
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_RSM_ATTR_GET, inXml, outXml, &sId);    
    
    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << "GetAttribute command success." << endl << endl;
         std:: cout  << "Out XML : " << outXml.data() << endl;
    }
    else
    {
        std:: cout  << "GetAttribute command failed. Error code : " << sId << endl;
    }
    std:: cout  << "================================" << endl<< endl;
}

void ScannerEventListener::GetAttributeNext()
{
    std::string scannerID = "";
    std:: cout  << "Enter Scanner ID : " << endl;
    cin >> scannerID;
    std:: cout  << "Enter current attribute number : " ;
    std::string attribute_number = "";
    cin >> attribute_number;

    std::string inXml = "<inArgs><scannerID>" + scannerID + 
                        "</scannerID><cmdArgs><arg-xml><attrib_list>" + 
                        attribute_number + "</attrib_list></arg-xml></cmdArgs></inArgs>";    
    
    StatusID sId;
    std::string outXml;
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_RSM_ATTR_GETNEXT, inXml, outXml, &sId);
    
    std:: cout  << "================================" << endl;
    
    if(sId == STATUS_OK)
    {
        std:: cout  << "GetAttributeNext command success. " << endl << endl;
         std:: cout  << "Out XML : " << outXml.data() << endl;
    }
    else
    {
         std:: cout  << "GetAttributeNext command failed. Error code : " << sId << endl;
    }
    
    std:: cout  << "================================" << endl << endl;
}

void ScannerEventListener::GetAllAttributes()
{    
    std::string scannerID = "";     
    
    std:: cout  << "Enter scanner ID: ";
    cin >> scannerID;
    
    std::string inXml = "<inArgs><scannerID>"+scannerID+"</scannerID></inArgs>";
    StatusID sId;
    std::string outXml;
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_RSM_ATTR_GETALL, inXml, outXml, &sId);
       
    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << "GetAllAttributes command success. " << endl << endl;
         std:: cout  << "Out XML : " << outXml.data() << endl;
    }
    else
    {
         std:: cout  << "GetAllAttributes command failed. Error code : " << sId << endl;
    }
    std:: cout  << "================================" << endl << endl;
}



void ScannerEventListener::SetAttribute()
{
    std::string scannerID = "";
    std:: cout  << "Enter scanner ID : " << endl;
    cin >> scannerID;
    std::string attributeNumber = "";
    std:: cout  << "Enter attribute number : " << endl;
    cin >> attributeNumber;
    std::string dataType = "";
    std:: cout  << "Enter data type : " << endl;
    cin >> dataType;
    std::string attributeValue = "";
    std:: cout  << "Enter attribute value : " << endl;
    cin >> attributeValue;
    
    std::string inXml = "<inArgs><scannerID>"+ scannerID +
                        "</scannerID><cmdArgs><arg-xml><attrib_list><attribute><id>" + attributeNumber + 
                        "</id><datatype>" + dataType + 
                        "</datatype><value>" + attributeValue + 
                        "</value></attribute></attrib_list></arg-xml></cmdArgs></inArgs>";
    
    StatusID sId;    
    std::string outXml;
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_RSM_ATTR_SET, inXml, outXml, &sId);
    
    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << "SetAttribute command success. " << endl << endl;
    }
    else
    {
         std:: cout  << "SetAttribute command failed. Error code : " << sId << endl;
    }
    
    std:: cout  << "================================" << endl << endl;

}

void ScannerEventListener::SetAttributeStore()
{
    std::string scannerID = "";
    std:: cout  << "Enter scanner ID : " << endl;
    cin >> scannerID;
    std::string attributeNumber = "";
    std:: cout  << "Enter attribute number : " << endl;
    cin >> attributeNumber;
    std::string dataType = "";
    std:: cout  << "Enter data type : " << endl;
    cin >> dataType;
    std::string attributeValue = "";
    std:: cout  << "Enter attribute value : " << endl;
    cin >> attributeValue;    

    std::string inXml = "<inArgs><scannerID>"+ scannerID +
                        "</scannerID><cmdArgs><arg-xml><attrib_list><attribute><id>" + attributeNumber + 
                        "</id><datatype>" + dataType + 
                        "</datatype><value>" + attributeValue + 
                        "</value></attribute></attrib_list></arg-xml></cmdArgs></inArgs>";
    
    StatusID sId;    
    std::string outXml;
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_RSM_ATTR_STORE, inXml, outXml, &sId);
   
    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << "StoreAttribute command success. " << endl << endl;
    }
    else
    {
         std:: cout  << "StoreAttribute command failed. Error code : " << sId << endl;
    }    
    std:: cout  << "================================" << endl << endl;
}

void ScannerEventListener::SetZeroWeight()
{
    std::string inXml = "<inArgs><scannerID>1</scannerID><cmdArgs><arg-xml><attrib_list><attribute><id>6019</id><datatype>X</datatype><value>0</value></attribute></attrib_list></arg-xml></cmdArgs></inArgs>";

    StatusID sId;
    std::string outXml;
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_RSM_ATTR_SET, inXml, outXml, &sId);
      
    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << "SetZeroWeight command success. " << endl << endl;
    }
    else
    {
         std:: cout  << "SetZeroWeight command failed. Error code : " << sId << endl;
    } 
    std:: cout  << "================================" << endl << endl;
}

//Event EventListener for get Get Version number of Core scanner
void ScannerEventListener::GetVersion() {
    
    std::string inXml = "<inArgs></inArgs>";   
    StatusID sId;
    std::string outXml;
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_GET_VERSION, inXml, outXml, &sId);
       
    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << "GetVersion command success. " << endl << endl;
         std:: cout  << "Out XML : " << outXml.data() << endl;
    }
    else
    {
         std:: cout  << "GetVersion command failed. Error code : " << sId << endl;
    } 
    std:: cout  << "================================" << endl << endl;
}

void ScannerEventListener::Close()
{
    StatusID status;
    ::Close(0, &status);
    std:: cout  << "close" << endl;

}

string getStringFromRawData(unsigned char* rawData,int startIndex, int endIndex){
    int numElements = endIndex-startIndex;
    char buffer [numElements];
    int j=0;
    for(int i=startIndex;i<endIndex;i++){
        sprintf (&buffer[j++], "%c", rawData[i]);
    }
    string str(buffer);
    return str;
}
void ScannerEventListener::OnImageEvent( short eventType, int size, short imageFormat, char* sfimageData, int dataLength, std::string& pScannerData )
{
    std:: cout  << "OnImageEvent" << endl;
}

void ScannerEventListener::OnBinaryDataEvent( short eventType, int size, short dataFormat, unsigned char* sfBinaryData, std::string&  pScannerData)
{    
     // Constants for ISO15434 messages
        const unsigned char ISO_RS = 0x1E;  // ISO15454 Format Trailer Character
//        const unsigned char ISO_GS = 0x1D;  // ISO15454 Data Element Separator
        const unsigned char ISO_EOT = 0x04;  // ISO15454 Message Trailer Character
        const unsigned char MSG_EASYCAP = 0;     // ISO15451 Message DocCap message number
        FILE *imgFile; 
        std:: cout  << "OnBinaryDataEvent" << endl;
		
        int packetLength = (sfBinaryData[0] << 24) |
                        (sfBinaryData[1] << 16) |
                        (sfBinaryData[2] << 8) |
                        sfBinaryData[3];
        
        if(packetLength+4!= size)
        {
            std:: cout  << "Incorrect packet size\n" << endl;
        }
        else
        {
            if(sfBinaryData[4]!= MSG_EASYCAP)
            {
                std:: cout  << "Incorrect Msg type\n" << endl;
            }
            else
            {
                // ISO15434 Envelope: is message header correct?
                if ((sfBinaryData[5] != '[') || (sfBinaryData[6] != ')') || (sfBinaryData[7] != '>') || (sfBinaryData[8] != ISO_RS))
                {
                    std:: cout  << "Incorrect message header\n" << endl;
                }
                else
                {
                     // ISO15434 Envelope: is message header correct?
                    if (sfBinaryData[size - 1] != ISO_EOT)
                    {
                        std:: cout  << "Incorrect message header ISO_EOT\n" << endl;
                    }
                    else
                    {
                        std:: cout  << "Correct packet received \n" << endl;
                        ISO15434formatEnvelope *anEnvelope = new ISO15434formatEnvelope(sfBinaryData,size, 9);
                        while (anEnvelope->getNext())
                        {
                            string fileType = anEnvelope->getFileType();

                            if (fileType == "BarCode")
                            {
                                string decodeData=getStringFromRawData(sfBinaryData,anEnvelope->getDataIndex(),anEnvelope->getDataIndex()+anEnvelope->getDataLength());
                                std:: cout  << "Barcode received " << endl;
                                std:: cout  << " Data type = "<<  (int)decodeData.at(0) << endl;
                                std:: cout  << " Data = "<< decodeData.substr(1,anEnvelope->getDataLength()).data()<< endl;
                            }else{
                                char filename[200];
                                string fileFormat = anEnvelope->getFileType();
                                time_t t = time(0);   // get time now
                                tm* now = localtime(&t);
                                sprintf(filename,"ZIMG-%d%d%d%d%d%d%s%s", now->tm_year + 1900, now->tm_mon + 1,now->tm_mday,now->tm_hour,now->tm_min,now->tm_sec,".",fileFormat.c_str());
                                imgFile = fopen(filename, "w");
                                if (!imgFile)
                                {
                                    std:: cout  << "Unable to open file " << filename<< endl;
                                    continue;
                                }
                                fwrite(&sfBinaryData[anEnvelope->getDataIndex()]+6,sizeof(unsigned char),anEnvelope->getDataLength()+6,imgFile);
                                fflush(imgFile);
                                fclose (imgFile);
                                std:: cout  << "ImageData saved in " <<filename<< endl;
                            }
                        }
                    }
                }
                
            }
        }
}

void ScannerEventListener::OnVideoEvent( short eventType, int size, char* sfvideoData, int dataLength, std::string& pScannerData )
{
    std:: cout  << "OnVideoEvent" << endl;
}

void ScannerEventListener::OnPNPEvent( short eventType, std::string ppnpData )
{
    string str;
    if (eventType == SCANNER_ATTACHED) {
        std:: cout  << "Scanner attached" << endl;
        str = ppnpData;
        scanner_attached = true;
        std:: cout  << "scanner_attached " << scanner_attached << endl;
    } else if (eventType == SCANNER_DETACHED) {
        std:: cout  << "Scanner detached" << endl;
        str =  ppnpData;
        scanner_attached = false;
    } else {
        str = " UNKNOWN PNP Event ";
    }
    std:: cout  << str.data() << endl;
}

void ScannerEventListener::OnCommandResponseEvent( short status, std::string& prspData )
{
    std:: cout  << endl << "Scanner data: " << prspData.data() << endl;
    std:: cout  << "OnCommandResponseEvent" << endl;
    std:: cout  << prspData.data() << endl;
}

void ScannerEventListener::OnScannerNotification( short notificationType, std::string& pScannerData )
{
    std:: cout  << endl << "Scanner event data: " << pScannerData.data() << endl;
    std:: cout  << "OnScannerNotification" << endl;
}

void ScannerEventListener::OnIOEvent( short type, unsigned char data )
{
    std:: cout  << "OnIOEvent" << endl;
}

void ScannerEventListener::OnScanRMDEvent( short eventType, std::string& prmdData )
{
    std:: cout  << "OnScanRMDEvent" << endl;
        std:: cout  << "Out XML " << endl;
        std:: cout  << prmdData.data() << endl;
}

void ScannerEventListener::OnDisconnect()
{
    std:: cout  << "OnDisconnect" << endl;
}

void ScannerEventListener::OnBarcodeEvent(short int eventType, std::string & pscanData)
{
    std:: cout  << "Barcode Detected" << endl;
    std:: cout  << "Out XML" << endl;


    std::string decoded_bar_code = get_decode_data(pscanData);
    cout << "bar_code:    " << decoded_bar_code << endl;

    std::ofstream outfile;

    outfile.open("test.txt", std::ios_base::app); // append instead of overwrite
    outfile << decoded_bar_code << endl;
    outfile.close();

    thrift_client->scan(decoded_bar_code);
}

// tokernize string for a given delimiter //
static char tokernize_buffer[ 256];
std::vector<std::string> ScannerEventListener::stringTokernize(std::string inStr,char cDelim )
{
    std:: cout  << ("function start");
    std::vector<std::string> _return;

    int iLength = inStr.size();
    int iCurrentIndex = 0;
    int iCurrentOutputIndex =0;
    while ( iCurrentIndex < iLength ){
        char cCurrentChar = inStr[iCurrentIndex++];
        if (cDelim == cCurrentChar  ){
            if ( iCurrentOutputIndex == 0 )
            {
                // just ignore//
            }else {
                tokernize_buffer[iCurrentOutputIndex] =0;
                _return .push_back( tokernize_buffer);
                iCurrentOutputIndex= 0;
            }
        }else{
            tokernize_buffer[iCurrentOutputIndex++] = (char)cCurrentChar;
        }
    }

    if ( iCurrentOutputIndex > 0){
        tokernize_buffer[iCurrentOutputIndex] = 0;
        _return.push_back(tokernize_buffer);
    }

    std:: cout  << ("function end");
    return _return;
}

static char buffer_decode_data [ 1024*256] ; // hope we don't have barcodes beyond 256 KB of length. //
std::string ScannerEventListener::get_decode_data(std::string outXml){
    std:: cout  << ("function start");
    // :TODO:
    pugi::xml_document doc;
    pugi::xml_parse_result parse_result = doc.load_string( outXml.c_str());
    if ( pugi::status_ok != parse_result.status)
    {
        std:: cout  << ("loading outXml to pugi failed.");
        return "";
    }

    pugi::xml_node nodeDataLabel = doc.child("outArgs").child("arg-xml").
            child("scandata").child("datalabel");
    const char * cstrDataLabel = nodeDataLabel.child_value();
    int iLength = strlen( cstrDataLabel);

    if (iLength < 1)
    {
        std:: cout  << ("get_decode_data :: outXml->datalabel has no data");
    }

    std::vector<std::string> vecStrTokernized = stringTokernize(cstrDataLabel, ' ');
    std::vector<std::string>::iterator itr;
    int iIndexOutput = 0;
    int cCurrentChar ;
    for( itr = vecStrTokernized.begin(); itr != vecStrTokernized.end();itr++){
        std::string strCurrentToken = *itr;
        int iRet = sscanf( strCurrentToken.c_str(), "%x" , &cCurrentChar);
        if ( iRet == 0){
            sscanf( strCurrentToken.c_str() , "%x" , &cCurrentChar);
        }
        buffer_decode_data[iIndexOutput++] = (char) cCurrentChar;
    }

    buffer_decode_data[iIndexOutput] = 0;

    std:: cout  << ("function end");

    return buffer_decode_data;
}


void ScannerEventListener::RebootScanner()
{
    
}

void ScannerEventListener::FirmwareUpdate()
{
    std::string inXml;
    std::string outXml;
    std::string datFilePath; 
    StatusID sId;
    std::string scannerID;
    std::string bulkOption;
    
    std:: cout  << "Enter Scanner ID : " << endl;
    std::cin >> scannerID;
    std:: cout  << "Enter Firmware DAT file path: " << endl;
    std::cin >> datFilePath;
    std:: cout  << "Enter USB communication mode 1=hid, 2=bulk : ";
    std::cin >> bulkOption;
    
    inXml = "<inArgs><scannerID>" + scannerID + "</scannerID><cmdArgs><arg-string>" + datFilePath + "</arg-string><arg-int>" + bulkOption + "</arg-int></cmdArgs></inArgs>";
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_DEVICE_UPDATE_FIRMWARE, inXml, outXml, &sId);
        
    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << "Firmware Update command success. " << endl << endl;
    }
    else
    {
         std:: cout  << "Firmware Update command failed. Error code : " << sId << endl;
    } 
    std:: cout  << "================================" << endl << endl;
}

void ScannerEventListener::FirmwareUpdateFromPlugin()
{
     std::string inXml;
    std::string outXml;
    std::string pluginFilePath=""; 
    StatusID sId;
    std::string scannerID;
    std::string bulkOption;
    
    std:: cout  << "Enter Scanner ID : " << endl;
    std::cin >> scannerID;
    std:: cout  << "Enter Firmware Plug-in file path: " << endl;
    //std::cin >>  pluginFilePath;

    while ( pluginFilePath.size() < 4 ){
        std::getline(std::cin, pluginFilePath);
    }
    
    if ( !(pluginFilePath.substr(pluginFilePath.find_last_of(".")+ 1) == "SCNPLG") ){
        std:: cout  << "Please Enter a file with extension .SCNPLG." << endl << endl;
        return;
    }
    
    std:: cout  << "Enter USB communication mode 1=hid, 2=bulk : ";
    std::cin >> bulkOption;
    
    inXml = "<inArgs><scannerID>" + scannerID + "</scannerID><cmdArgs><arg-string>" + pluginFilePath + "</arg-string><arg-int>" + bulkOption + "</arg-int></cmdArgs></inArgs>";
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_DEVICE_UPDATE_FIRMWARE_FROM_PLUGIN, inXml, outXml, &sId);
    
    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << "FirmwareUpdate From Plug-in command success. " << endl << endl;
    }
    else
    {
         std:: cout  << "FirmwareUpdate From Plug-in command failed. Error code : " << sId << endl;
    } 
    std:: cout  << "================================" << endl << endl;
}

void ScannerEventListener::StartNewFirmware()
{
    std::string inXml;
    std::string outXml;
    StatusID sId;
    std::string scannerID;
    
    std:: cout  << "Enter Scanner ID : " << endl;
    std::cin >> scannerID;
       
    inXml = "<inArgs><scannerID>" + scannerID + "</scannerID></inArgs>"; 
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_START_NEW_FIRMWARE, inXml, outXml, &sId);
    
    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << "Start New Firmware command success. " << endl << endl;
    }
    else
    {
         std:: cout  << "Start New Firmware command failed. Error code : " << sId << endl;
    } 
    std:: cout  << "================================" << endl << endl;
}

void ScannerEventListener::AbortFirmwareUpdate()
{
    std::string inXml;
    std::string outXml;
    StatusID sId;
    std::string scannerID;    
   
    std:: cout  << "Enter Scanner ID : " << endl;
    std::cin >> scannerID;
    
    inXml = "<inArgs><scannerID>" + scannerID + "</scannerID></inArgs>";
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(CMD_DEVICE_ABORT_UPDATE_FIRMWARE, inXml, outXml, &sId);
    
    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << "Abort Firmware Update command success. " << endl << endl;
    }
    else
    {
         std:: cout  << "Abort Firmware Update command failed. Error code : " << sId << endl;
    } 
    std:: cout  << "================================" << endl << endl;
}

/**
 * Method to execute action attribute related commands.
 * added to v1.3.0 release.
 * @param opCode
 */
void ScannerEventListener::ExecuteActionCommand(CmdOpcode opCode)
{
    std::string scannerID = "";
    std::string ledNumber = "";
    std::string beeperCode = "";
    std::string inXml;
    std::string commandName = "";
           
    switch (opCode)
    {
        case CMD_DEVICE_LED_ON:
        case CMD_DEVICE_LED_OFF:
        {
            commandName = "Device LED ON/OFF command ";
            std:: cout  << "Enter scanner ID : ";
            cin >> scannerID;
            std:: cout  << "Enter LED number : ";
            cin >> ledNumber;

            inXml = "<inArgs><scannerID>" + scannerID + 
                                "</scannerID><cmdArgs><arg-int>" + ledNumber +
                                "</arg-int></cmdArgs></inArgs>";
            break;
        }
        case CMD_DEVICE_BEEP_CONTROL:
        {
            commandName = "Beep command ";
            std:: cout  << "Enter scanner ID : ";
            cin >> scannerID;
            std:: cout  << "Enter Beeper code : ";
            cin >> beeperCode;

            inXml = "<inArgs><scannerID>" + scannerID + 
                                "</scannerID><cmdArgs><arg-int>" + beeperCode +
                                "</arg-int></cmdArgs></inArgs>";
            break;
        }
        case CMD_DEVICE_SCAN_ENABLE:
        case CMD_DEVICE_SCAN_DISABLE:
        {
            commandName = "Device Scan Enable/Disable command ";
            std:: cout  << "Enter scanner ID : ";
            cin >> scannerID;
            inXml = "<inArgs><scannerID>" + scannerID + "</scannerID></inArgs>";
            break;
        }
        case CMD_REBOOT_SCANNER:
        {
            commandName = "Reboot scanner command ";
            std:: cout  << "Enter scanner ID : ";
            cin >> scannerID;
            inXml = "<inArgs><scannerID>" + scannerID + "</scannerID></inArgs>";
            break;
        }
        case CMD_DEVICE_AIM_ON:
        case CMD_DEVICE_AIM_OFF:
        {
            commandName = "Device AIM ON/OFF command ";
            std:: cout  << "Enter scanner ID : ";
            cin >> scannerID;
            inXml = "<inArgs><scannerID>" + scannerID + "</scannerID></inArgs>";
            break;
        }
        default:
        {
            commandName = "Default Action command ";
            std:: cout  << "Enter scanner ID : ";
            cin >> scannerID;
            inXml = "<inArgs><scannerID>" + scannerID + "</scannerID></inArgs>";
            break;
        }
    }
      
    StatusID sId;
    std::string outXml;
    std:: cout  << "In XML  : " << inXml.data() << endl << endl;
    ::ExecCommand(opCode, inXml, outXml, &sId);

    std:: cout  << "================================" << endl;
    if(sId == STATUS_OK)
    {
        std:: cout  << commandName.data() << "success. " << endl << endl;
    }
    else
    {
         std:: cout  << commandName.data() << "failed. Error code : " << sId << endl;
    } 
    std:: cout  << "================================" << endl << endl;
}
