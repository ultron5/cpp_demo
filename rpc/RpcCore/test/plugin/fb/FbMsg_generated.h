// automatically generated by the FlatBuffers compiler, do not modify


#ifndef FLATBUFFERS_GENERATED_FBMSG_MSG_H_
#define FLATBUFFERS_GENERATED_FBMSG_MSG_H_

#include "flatbuffers/flatbuffers.h"

// Ensure the included flatbuffers.h is the same version as when this file was
// generated, otherwise it may not be compatible.
static_assert(FLATBUFFERS_VERSION_MAJOR == 23 &&
              FLATBUFFERS_VERSION_MINOR == 1 &&
              FLATBUFFERS_VERSION_REVISION == 21,
             "Non-compatible flatbuffers version included");

namespace msg {

struct FbMsg;
struct FbMsgBuilder;
struct FbMsgT;

struct FbMsgT : public ::flatbuffers::NativeTable {
  typedef FbMsg TableType;
  int32_t id = 0;
  uint8_t age = 0;
  std::string name{};
};

struct FbMsg FLATBUFFERS_FINAL_CLASS : private ::flatbuffers::Table {
  typedef FbMsgT NativeTableType;
  typedef FbMsgBuilder Builder;
  enum FlatBuffersVTableOffset FLATBUFFERS_VTABLE_UNDERLYING_TYPE {
    VT_ID = 4,
    VT_AGE = 6,
    VT_NAME = 8
  };
  int32_t id() const {
    return GetField<int32_t>(VT_ID, 0);
  }
  uint8_t age() const {
    return GetField<uint8_t>(VT_AGE, 0);
  }
  const ::flatbuffers::String *name() const {
    return GetPointer<const ::flatbuffers::String *>(VT_NAME);
  }
  bool Verify(::flatbuffers::Verifier &verifier) const {
    return VerifyTableStart(verifier) &&
           VerifyField<int32_t>(verifier, VT_ID, 4) &&
           VerifyField<uint8_t>(verifier, VT_AGE, 1) &&
           VerifyOffset(verifier, VT_NAME) &&
           verifier.VerifyString(name()) &&
           verifier.EndTable();
  }
  FbMsgT *UnPack(const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  void UnPackTo(FbMsgT *_o, const ::flatbuffers::resolver_function_t *_resolver = nullptr) const;
  static ::flatbuffers::Offset<FbMsg> Pack(::flatbuffers::FlatBufferBuilder &_fbb, const FbMsgT* _o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);
};

struct FbMsgBuilder {
  typedef FbMsg Table;
  ::flatbuffers::FlatBufferBuilder &fbb_;
  ::flatbuffers::uoffset_t start_;
  void add_id(int32_t id) {
    fbb_.AddElement<int32_t>(FbMsg::VT_ID, id, 0);
  }
  void add_age(uint8_t age) {
    fbb_.AddElement<uint8_t>(FbMsg::VT_AGE, age, 0);
  }
  void add_name(::flatbuffers::Offset<::flatbuffers::String> name) {
    fbb_.AddOffset(FbMsg::VT_NAME, name);
  }
  explicit FbMsgBuilder(::flatbuffers::FlatBufferBuilder &_fbb)
        : fbb_(_fbb) {
    start_ = fbb_.StartTable();
  }
  ::flatbuffers::Offset<FbMsg> Finish() {
    const auto end = fbb_.EndTable(start_);
    auto o = ::flatbuffers::Offset<FbMsg>(end);
    return o;
  }
};

inline ::flatbuffers::Offset<FbMsg> CreateFbMsg(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    int32_t id = 0,
    uint8_t age = 0,
    ::flatbuffers::Offset<::flatbuffers::String> name = 0) {
  FbMsgBuilder builder_(_fbb);
  builder_.add_name(name);
  builder_.add_id(id);
  builder_.add_age(age);
  return builder_.Finish();
}

inline ::flatbuffers::Offset<FbMsg> CreateFbMsgDirect(
    ::flatbuffers::FlatBufferBuilder &_fbb,
    int32_t id = 0,
    uint8_t age = 0,
    const char *name = nullptr) {
  auto name__ = name ? _fbb.CreateString(name) : 0;
  return msg::CreateFbMsg(
      _fbb,
      id,
      age,
      name__);
}

::flatbuffers::Offset<FbMsg> CreateFbMsg(::flatbuffers::FlatBufferBuilder &_fbb, const FbMsgT *_o, const ::flatbuffers::rehasher_function_t *_rehasher = nullptr);

inline FbMsgT *FbMsg::UnPack(const ::flatbuffers::resolver_function_t *_resolver) const {
  auto _o = std::unique_ptr<FbMsgT>(new FbMsgT());
  UnPackTo(_o.get(), _resolver);
  return _o.release();
}

inline void FbMsg::UnPackTo(FbMsgT *_o, const ::flatbuffers::resolver_function_t *_resolver) const {
  (void)_o;
  (void)_resolver;
  { auto _e = id(); _o->id = _e; }
  { auto _e = age(); _o->age = _e; }
  { auto _e = name(); if (_e) _o->name = _e->str(); }
}

inline ::flatbuffers::Offset<FbMsg> FbMsg::Pack(::flatbuffers::FlatBufferBuilder &_fbb, const FbMsgT* _o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  return CreateFbMsg(_fbb, _o, _rehasher);
}

inline ::flatbuffers::Offset<FbMsg> CreateFbMsg(::flatbuffers::FlatBufferBuilder &_fbb, const FbMsgT *_o, const ::flatbuffers::rehasher_function_t *_rehasher) {
  (void)_rehasher;
  (void)_o;
  struct _VectorArgs { ::flatbuffers::FlatBufferBuilder *__fbb; const FbMsgT* __o; const ::flatbuffers::rehasher_function_t *__rehasher; } _va = { &_fbb, _o, _rehasher}; (void)_va;
  auto _id = _o->id;
  auto _age = _o->age;
  auto _name = _o->name.empty() ? 0 : _fbb.CreateString(_o->name);
  return msg::CreateFbMsg(
      _fbb,
      _id,
      _age,
      _name);
}

inline const msg::FbMsg *GetFbMsg(const void *buf) {
  return ::flatbuffers::GetRoot<msg::FbMsg>(buf);
}

inline const msg::FbMsg *GetSizePrefixedFbMsg(const void *buf) {
  return ::flatbuffers::GetSizePrefixedRoot<msg::FbMsg>(buf);
}

inline bool VerifyFbMsgBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifyBuffer<msg::FbMsg>(nullptr);
}

inline bool VerifySizePrefixedFbMsgBuffer(
    ::flatbuffers::Verifier &verifier) {
  return verifier.VerifySizePrefixedBuffer<msg::FbMsg>(nullptr);
}

inline void FinishFbMsgBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<msg::FbMsg> root) {
  fbb.Finish(root);
}

inline void FinishSizePrefixedFbMsgBuffer(
    ::flatbuffers::FlatBufferBuilder &fbb,
    ::flatbuffers::Offset<msg::FbMsg> root) {
  fbb.FinishSizePrefixed(root);
}

inline std::unique_ptr<msg::FbMsgT> UnPackFbMsg(
    const void *buf,
    const ::flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<msg::FbMsgT>(GetFbMsg(buf)->UnPack(res));
}

inline std::unique_ptr<msg::FbMsgT> UnPackSizePrefixedFbMsg(
    const void *buf,
    const ::flatbuffers::resolver_function_t *res = nullptr) {
  return std::unique_ptr<msg::FbMsgT>(GetSizePrefixedFbMsg(buf)->UnPack(res));
}

}  // namespace msg

#endif  // FLATBUFFERS_GENERATED_FBMSG_MSG_H_
