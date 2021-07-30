/**
 * Autogenerated by Thrift Compiler (0.14.2)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef SlaveController_H
#define SlaveController_H

#include <thrift/TDispatchProcessor.h>
#include <thrift/async/TConcurrentClientSyncInfo.h>
#include <memory>
#include "slave_controller_types.h"

namespace slave_controller {

#ifdef _MSC_VER
  #pragma warning( push )
  #pragma warning (disable : 4250 ) //inheriting methods via dominance 
#endif

class SlaveControllerIf {
 public:
  virtual ~SlaveControllerIf() {}
  virtual void scanner_status(const ScannerStatus::type status) = 0;
  virtual void scan(const std::string& scan) = 0;
};

class SlaveControllerIfFactory {
 public:
  typedef SlaveControllerIf Handler;

  virtual ~SlaveControllerIfFactory() {}

  virtual SlaveControllerIf* getHandler(const ::apache::thrift::TConnectionInfo& connInfo) = 0;
  virtual void releaseHandler(SlaveControllerIf* /* handler */) = 0;
};

class SlaveControllerIfSingletonFactory : virtual public SlaveControllerIfFactory {
 public:
  SlaveControllerIfSingletonFactory(const ::std::shared_ptr<SlaveControllerIf>& iface) : iface_(iface) {}
  virtual ~SlaveControllerIfSingletonFactory() {}

  virtual SlaveControllerIf* getHandler(const ::apache::thrift::TConnectionInfo&) {
    return iface_.get();
  }
  virtual void releaseHandler(SlaveControllerIf* /* handler */) {}

 protected:
  ::std::shared_ptr<SlaveControllerIf> iface_;
};

class SlaveControllerNull : virtual public SlaveControllerIf {
 public:
  virtual ~SlaveControllerNull() {}
  void scanner_status(const ScannerStatus::type /* status */) {
    return;
  }
  void scan(const std::string& /* scan */) {
    return;
  }
};

typedef struct _SlaveController_scanner_status_args__isset {
  _SlaveController_scanner_status_args__isset() : status(false) {}
  bool status :1;
} _SlaveController_scanner_status_args__isset;

class SlaveController_scanner_status_args {
 public:

  SlaveController_scanner_status_args(const SlaveController_scanner_status_args&);
  SlaveController_scanner_status_args& operator=(const SlaveController_scanner_status_args&);
  SlaveController_scanner_status_args() : status((ScannerStatus::type)0) {
  }

  virtual ~SlaveController_scanner_status_args() noexcept;
  /**
   * 
   * @see ScannerStatus
   */
  ScannerStatus::type status;

  _SlaveController_scanner_status_args__isset __isset;

  void __set_status(const ScannerStatus::type val);

  bool operator == (const SlaveController_scanner_status_args & rhs) const
  {
    if (!(status == rhs.status))
      return false;
    return true;
  }
  bool operator != (const SlaveController_scanner_status_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SlaveController_scanner_status_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class SlaveController_scanner_status_pargs {
 public:


  virtual ~SlaveController_scanner_status_pargs() noexcept;
  /**
   * 
   * @see ScannerStatus
   */
  const ScannerStatus::type* status;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class SlaveController_scanner_status_result {
 public:

  SlaveController_scanner_status_result(const SlaveController_scanner_status_result&);
  SlaveController_scanner_status_result& operator=(const SlaveController_scanner_status_result&);
  SlaveController_scanner_status_result() {
  }

  virtual ~SlaveController_scanner_status_result() noexcept;

  bool operator == (const SlaveController_scanner_status_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const SlaveController_scanner_status_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SlaveController_scanner_status_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class SlaveController_scanner_status_presult {
 public:


  virtual ~SlaveController_scanner_status_presult() noexcept;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

typedef struct _SlaveController_scan_args__isset {
  _SlaveController_scan_args__isset() : scan(false) {}
  bool scan :1;
} _SlaveController_scan_args__isset;

class SlaveController_scan_args {
 public:

  SlaveController_scan_args(const SlaveController_scan_args&);
  SlaveController_scan_args& operator=(const SlaveController_scan_args&);
  SlaveController_scan_args() : scan() {
  }

  virtual ~SlaveController_scan_args() noexcept;
  std::string scan;

  _SlaveController_scan_args__isset __isset;

  void __set_scan(const std::string& val);

  bool operator == (const SlaveController_scan_args & rhs) const
  {
    if (!(scan == rhs.scan))
      return false;
    return true;
  }
  bool operator != (const SlaveController_scan_args &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SlaveController_scan_args & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class SlaveController_scan_pargs {
 public:


  virtual ~SlaveController_scan_pargs() noexcept;
  const std::string* scan;

  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class SlaveController_scan_result {
 public:

  SlaveController_scan_result(const SlaveController_scan_result&);
  SlaveController_scan_result& operator=(const SlaveController_scan_result&);
  SlaveController_scan_result() {
  }

  virtual ~SlaveController_scan_result() noexcept;

  bool operator == (const SlaveController_scan_result & /* rhs */) const
  {
    return true;
  }
  bool operator != (const SlaveController_scan_result &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const SlaveController_scan_result & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};


class SlaveController_scan_presult {
 public:


  virtual ~SlaveController_scan_presult() noexcept;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);

};

class SlaveControllerClient : virtual public SlaveControllerIf {
 public:
  SlaveControllerClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
    setProtocol(prot);
  }
  SlaveControllerClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void scanner_status(const ScannerStatus::type status);
  void send_scanner_status(const ScannerStatus::type status);
  void recv_scanner_status();
  void scan(const std::string& scan);
  void send_scan(const std::string& scan);
  void recv_scan();
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
};

class SlaveControllerProcessor : public ::apache::thrift::TDispatchProcessor {
 protected:
  ::std::shared_ptr<SlaveControllerIf> iface_;
  virtual bool dispatchCall(::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, const std::string& fname, int32_t seqid, void* callContext);
 private:
  typedef  void (SlaveControllerProcessor::*ProcessFunction)(int32_t, ::apache::thrift::protocol::TProtocol*, ::apache::thrift::protocol::TProtocol*, void*);
  typedef std::map<std::string, ProcessFunction> ProcessMap;
  ProcessMap processMap_;
  void process_scanner_status(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
  void process_scan(int32_t seqid, ::apache::thrift::protocol::TProtocol* iprot, ::apache::thrift::protocol::TProtocol* oprot, void* callContext);
 public:
  SlaveControllerProcessor(::std::shared_ptr<SlaveControllerIf> iface) :
    iface_(iface) {
    processMap_["scanner_status"] = &SlaveControllerProcessor::process_scanner_status;
    processMap_["scan"] = &SlaveControllerProcessor::process_scan;
  }

  virtual ~SlaveControllerProcessor() {}
};

class SlaveControllerProcessorFactory : public ::apache::thrift::TProcessorFactory {
 public:
  SlaveControllerProcessorFactory(const ::std::shared_ptr< SlaveControllerIfFactory >& handlerFactory) :
      handlerFactory_(handlerFactory) {}

  ::std::shared_ptr< ::apache::thrift::TProcessor > getProcessor(const ::apache::thrift::TConnectionInfo& connInfo);

 protected:
  ::std::shared_ptr< SlaveControllerIfFactory > handlerFactory_;
};

class SlaveControllerMultiface : virtual public SlaveControllerIf {
 public:
  SlaveControllerMultiface(std::vector<std::shared_ptr<SlaveControllerIf> >& ifaces) : ifaces_(ifaces) {
  }
  virtual ~SlaveControllerMultiface() {}
 protected:
  std::vector<std::shared_ptr<SlaveControllerIf> > ifaces_;
  SlaveControllerMultiface() {}
  void add(::std::shared_ptr<SlaveControllerIf> iface) {
    ifaces_.push_back(iface);
  }
 public:
  void scanner_status(const ScannerStatus::type status) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->scanner_status(status);
    }
    ifaces_[i]->scanner_status(status);
  }

  void scan(const std::string& scan) {
    size_t sz = ifaces_.size();
    size_t i = 0;
    for (; i < (sz - 1); ++i) {
      ifaces_[i]->scan(scan);
    }
    ifaces_[i]->scan(scan);
  }

};

// The 'concurrent' client is a thread safe client that correctly handles
// out of order responses.  It is slower than the regular client, so should
// only be used when you need to share a connection among multiple threads
class SlaveControllerConcurrentClient : virtual public SlaveControllerIf {
 public:
  SlaveControllerConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(prot);
  }
  SlaveControllerConcurrentClient(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot, std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync) : sync_(sync)
{
    setProtocol(iprot,oprot);
  }
 private:
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> prot) {
  setProtocol(prot,prot);
  }
  void setProtocol(std::shared_ptr< ::apache::thrift::protocol::TProtocol> iprot, std::shared_ptr< ::apache::thrift::protocol::TProtocol> oprot) {
    piprot_=iprot;
    poprot_=oprot;
    iprot_ = iprot.get();
    oprot_ = oprot.get();
  }
 public:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getInputProtocol() {
    return piprot_;
  }
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> getOutputProtocol() {
    return poprot_;
  }
  void scanner_status(const ScannerStatus::type status);
  int32_t send_scanner_status(const ScannerStatus::type status);
  void recv_scanner_status(const int32_t seqid);
  void scan(const std::string& scan);
  int32_t send_scan(const std::string& scan);
  void recv_scan(const int32_t seqid);
 protected:
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> piprot_;
  std::shared_ptr< ::apache::thrift::protocol::TProtocol> poprot_;
  ::apache::thrift::protocol::TProtocol* iprot_;
  ::apache::thrift::protocol::TProtocol* oprot_;
  std::shared_ptr<::apache::thrift::async::TConcurrentClientSyncInfo> sync_;
};

#ifdef _MSC_VER
  #pragma warning( pop )
#endif

} // namespace

#endif