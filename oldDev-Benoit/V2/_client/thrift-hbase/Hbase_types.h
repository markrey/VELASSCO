/**
 * Autogenerated by Thrift Compiler (1.0.0-dev)
 *
 * DO NOT EDIT UNLESS YOU ARE SURE THAT YOU KNOW WHAT YOU ARE DOING
 *  @generated
 */
#ifndef Hbase_TYPES_H
#define Hbase_TYPES_H

#include <thrift/Thrift.h>
#include <thrift/TApplicationException.h>
#include <thrift/protocol/TProtocol.h>
#include <thrift/transport/TTransport.h>

#include <thrift/cxxfunctional.h>


namespace apache { namespace hadoop { namespace hbase { namespace thrift {

typedef std::string Text;

typedef std::string Bytes;

typedef int32_t ScannerID;

class TCell;

class ColumnDescriptor;

class TRegionInfo;

class Mutation;

class BatchMutation;

class TRowResult;

class IOError;

class IllegalArgument;

class AlreadyExists;

typedef struct _TCell__isset {
  _TCell__isset() : value(false), timestamp(false) {}
  bool value :1;
  bool timestamp :1;
} _TCell__isset;

class TCell {
 public:

  static const char* ascii_fingerprint; // = "1CCCF6FC31CFD1D61BBBB1BAF3590620";
  static const uint8_t binary_fingerprint[16]; // = {0x1C,0xCC,0xF6,0xFC,0x31,0xCF,0xD1,0xD6,0x1B,0xBB,0xB1,0xBA,0xF3,0x59,0x06,0x20};

  TCell(const TCell&);
  TCell& operator=(const TCell&);
  TCell() : value(), timestamp(0) {
  }

  virtual ~TCell() throw();
  Bytes value;
  int64_t timestamp;

  _TCell__isset __isset;

  void __set_value(const Bytes& val);

  void __set_timestamp(const int64_t val);

  bool operator == (const TCell & rhs) const
  {
    if (!(value == rhs.value))
      return false;
    if (!(timestamp == rhs.timestamp))
      return false;
    return true;
  }
  bool operator != (const TCell &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TCell & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(TCell &a, TCell &b);

typedef struct _ColumnDescriptor__isset {
  _ColumnDescriptor__isset() : name(false), maxVersions(true), compression(true), inMemory(true), bloomFilterType(true), bloomFilterVectorSize(true), bloomFilterNbHashes(true), blockCacheEnabled(true), timeToLive(true) {}
  bool name :1;
  bool maxVersions :1;
  bool compression :1;
  bool inMemory :1;
  bool bloomFilterType :1;
  bool bloomFilterVectorSize :1;
  bool bloomFilterNbHashes :1;
  bool blockCacheEnabled :1;
  bool timeToLive :1;
} _ColumnDescriptor__isset;

class ColumnDescriptor {
 public:

  static const char* ascii_fingerprint; // = "3B18638852FDF9DD911BC1174265F92E";
  static const uint8_t binary_fingerprint[16]; // = {0x3B,0x18,0x63,0x88,0x52,0xFD,0xF9,0xDD,0x91,0x1B,0xC1,0x17,0x42,0x65,0xF9,0x2E};

  ColumnDescriptor(const ColumnDescriptor&);
  ColumnDescriptor& operator=(const ColumnDescriptor&);
  ColumnDescriptor() : name(), maxVersions(3), compression("NONE"), inMemory(false), bloomFilterType("NONE"), bloomFilterVectorSize(0), bloomFilterNbHashes(0), blockCacheEnabled(false), timeToLive(-1) {
  }

  virtual ~ColumnDescriptor() throw();
  Text name;
  int32_t maxVersions;
  std::string compression;
  bool inMemory;
  std::string bloomFilterType;
  int32_t bloomFilterVectorSize;
  int32_t bloomFilterNbHashes;
  bool blockCacheEnabled;
  int32_t timeToLive;

  _ColumnDescriptor__isset __isset;

  void __set_name(const Text& val);

  void __set_maxVersions(const int32_t val);

  void __set_compression(const std::string& val);

  void __set_inMemory(const bool val);

  void __set_bloomFilterType(const std::string& val);

  void __set_bloomFilterVectorSize(const int32_t val);

  void __set_bloomFilterNbHashes(const int32_t val);

  void __set_blockCacheEnabled(const bool val);

  void __set_timeToLive(const int32_t val);

  bool operator == (const ColumnDescriptor & rhs) const
  {
    if (!(name == rhs.name))
      return false;
    if (!(maxVersions == rhs.maxVersions))
      return false;
    if (!(compression == rhs.compression))
      return false;
    if (!(inMemory == rhs.inMemory))
      return false;
    if (!(bloomFilterType == rhs.bloomFilterType))
      return false;
    if (!(bloomFilterVectorSize == rhs.bloomFilterVectorSize))
      return false;
    if (!(bloomFilterNbHashes == rhs.bloomFilterNbHashes))
      return false;
    if (!(blockCacheEnabled == rhs.blockCacheEnabled))
      return false;
    if (!(timeToLive == rhs.timeToLive))
      return false;
    return true;
  }
  bool operator != (const ColumnDescriptor &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const ColumnDescriptor & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(ColumnDescriptor &a, ColumnDescriptor &b);

typedef struct _TRegionInfo__isset {
  _TRegionInfo__isset() : startKey(false), endKey(false), id(false), name(false), version(false) {}
  bool startKey :1;
  bool endKey :1;
  bool id :1;
  bool name :1;
  bool version :1;
} _TRegionInfo__isset;

class TRegionInfo {
 public:

  static const char* ascii_fingerprint; // = "A62468FDF7B959CEE277FA7367D1A4C6";
  static const uint8_t binary_fingerprint[16]; // = {0xA6,0x24,0x68,0xFD,0xF7,0xB9,0x59,0xCE,0xE2,0x77,0xFA,0x73,0x67,0xD1,0xA4,0xC6};

  TRegionInfo(const TRegionInfo&);
  TRegionInfo& operator=(const TRegionInfo&);
  TRegionInfo() : startKey(), endKey(), id(0), name(), version(0) {
  }

  virtual ~TRegionInfo() throw();
  Text startKey;
  Text endKey;
  int64_t id;
  Text name;
  int8_t version;

  _TRegionInfo__isset __isset;

  void __set_startKey(const Text& val);

  void __set_endKey(const Text& val);

  void __set_id(const int64_t val);

  void __set_name(const Text& val);

  void __set_version(const int8_t val);

  bool operator == (const TRegionInfo & rhs) const
  {
    if (!(startKey == rhs.startKey))
      return false;
    if (!(endKey == rhs.endKey))
      return false;
    if (!(id == rhs.id))
      return false;
    if (!(name == rhs.name))
      return false;
    if (!(version == rhs.version))
      return false;
    return true;
  }
  bool operator != (const TRegionInfo &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TRegionInfo & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(TRegionInfo &a, TRegionInfo &b);

typedef struct _Mutation__isset {
  _Mutation__isset() : isDelete(true), column(false), value(false) {}
  bool isDelete :1;
  bool column :1;
  bool value :1;
} _Mutation__isset;

class Mutation {
 public:

  static const char* ascii_fingerprint; // = "DC8F62AF23854A1A6849A2A157CCCA65";
  static const uint8_t binary_fingerprint[16]; // = {0xDC,0x8F,0x62,0xAF,0x23,0x85,0x4A,0x1A,0x68,0x49,0xA2,0xA1,0x57,0xCC,0xCA,0x65};

  Mutation(const Mutation&);
  Mutation& operator=(const Mutation&);
  Mutation() : isDelete(false), column(), value() {
  }

  virtual ~Mutation() throw();
  bool isDelete;
  Text column;
  Text value;

  _Mutation__isset __isset;

  void __set_isDelete(const bool val);

  void __set_column(const Text& val);

  void __set_value(const Text& val);

  bool operator == (const Mutation & rhs) const
  {
    if (!(isDelete == rhs.isDelete))
      return false;
    if (!(column == rhs.column))
      return false;
    if (!(value == rhs.value))
      return false;
    return true;
  }
  bool operator != (const Mutation &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const Mutation & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(Mutation &a, Mutation &b);

typedef struct _BatchMutation__isset {
  _BatchMutation__isset() : row(false), mutations(false) {}
  bool row :1;
  bool mutations :1;
} _BatchMutation__isset;

class BatchMutation {
 public:

  static const char* ascii_fingerprint; // = "7849EEBF8BB50169F3D2F0DD635BD8ED";
  static const uint8_t binary_fingerprint[16]; // = {0x78,0x49,0xEE,0xBF,0x8B,0xB5,0x01,0x69,0xF3,0xD2,0xF0,0xDD,0x63,0x5B,0xD8,0xED};

  BatchMutation(const BatchMutation&);
  BatchMutation& operator=(const BatchMutation&);
  BatchMutation() : row() {
  }

  virtual ~BatchMutation() throw();
  Text row;
  std::vector<Mutation>  mutations;

  _BatchMutation__isset __isset;

  void __set_row(const Text& val);

  void __set_mutations(const std::vector<Mutation> & val);

  bool operator == (const BatchMutation & rhs) const
  {
    if (!(row == rhs.row))
      return false;
    if (!(mutations == rhs.mutations))
      return false;
    return true;
  }
  bool operator != (const BatchMutation &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const BatchMutation & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(BatchMutation &a, BatchMutation &b);

typedef struct _TRowResult__isset {
  _TRowResult__isset() : row(false), columns(false) {}
  bool row :1;
  bool columns :1;
} _TRowResult__isset;

class TRowResult {
 public:

  static const char* ascii_fingerprint; // = "AE98EA4F344566FAFE04FA5E5823D1ED";
  static const uint8_t binary_fingerprint[16]; // = {0xAE,0x98,0xEA,0x4F,0x34,0x45,0x66,0xFA,0xFE,0x04,0xFA,0x5E,0x58,0x23,0xD1,0xED};

  TRowResult(const TRowResult&);
  TRowResult& operator=(const TRowResult&);
  TRowResult() : row() {
  }

  virtual ~TRowResult() throw();
  Text row;
  std::map<Text, TCell>  columns;

  _TRowResult__isset __isset;

  void __set_row(const Text& val);

  void __set_columns(const std::map<Text, TCell> & val);

  bool operator == (const TRowResult & rhs) const
  {
    if (!(row == rhs.row))
      return false;
    if (!(columns == rhs.columns))
      return false;
    return true;
  }
  bool operator != (const TRowResult &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const TRowResult & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(TRowResult &a, TRowResult &b);

typedef struct _IOError__isset {
  _IOError__isset() : message(false) {}
  bool message :1;
} _IOError__isset;

class IOError : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

  IOError(const IOError&);
  IOError& operator=(const IOError&);
  IOError() : message() {
  }

  virtual ~IOError() throw();
  std::string message;

  _IOError__isset __isset;

  void __set_message(const std::string& val);

  bool operator == (const IOError & rhs) const
  {
    if (!(message == rhs.message))
      return false;
    return true;
  }
  bool operator != (const IOError &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const IOError & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(IOError &a, IOError &b);

typedef struct _IllegalArgument__isset {
  _IllegalArgument__isset() : message(false) {}
  bool message :1;
} _IllegalArgument__isset;

class IllegalArgument : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

  IllegalArgument(const IllegalArgument&);
  IllegalArgument& operator=(const IllegalArgument&);
  IllegalArgument() : message() {
  }

  virtual ~IllegalArgument() throw();
  std::string message;

  _IllegalArgument__isset __isset;

  void __set_message(const std::string& val);

  bool operator == (const IllegalArgument & rhs) const
  {
    if (!(message == rhs.message))
      return false;
    return true;
  }
  bool operator != (const IllegalArgument &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const IllegalArgument & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(IllegalArgument &a, IllegalArgument &b);

typedef struct _AlreadyExists__isset {
  _AlreadyExists__isset() : message(false) {}
  bool message :1;
} _AlreadyExists__isset;

class AlreadyExists : public ::apache::thrift::TException {
 public:

  static const char* ascii_fingerprint; // = "EFB929595D312AC8F305D5A794CFEDA1";
  static const uint8_t binary_fingerprint[16]; // = {0xEF,0xB9,0x29,0x59,0x5D,0x31,0x2A,0xC8,0xF3,0x05,0xD5,0xA7,0x94,0xCF,0xED,0xA1};

  AlreadyExists(const AlreadyExists&);
  AlreadyExists& operator=(const AlreadyExists&);
  AlreadyExists() : message() {
  }

  virtual ~AlreadyExists() throw();
  std::string message;

  _AlreadyExists__isset __isset;

  void __set_message(const std::string& val);

  bool operator == (const AlreadyExists & rhs) const
  {
    if (!(message == rhs.message))
      return false;
    return true;
  }
  bool operator != (const AlreadyExists &rhs) const {
    return !(*this == rhs);
  }

  bool operator < (const AlreadyExists & ) const;

  uint32_t read(::apache::thrift::protocol::TProtocol* iprot);
  uint32_t write(::apache::thrift::protocol::TProtocol* oprot) const;

};

void swap(AlreadyExists &a, AlreadyExists &b);

}}}} // namespace

#endif
