// Generated by the protocol buffer compiler.  DO NOT EDIT!
// NO CHECKED-IN PROTOBUF GENCODE
// source: Protocol.proto
// Protobuf C++ Version: 5.29.3

#ifndef Protocol_2eproto_2epb_2eh
#define Protocol_2eproto_2epb_2eh
#include <limits>
#include <string>
#include <type_traits>
#include <utility>

#include "google/protobuf/runtime_version.h"
#if PROTOBUF_VERSION != 5029003
#error "Protobuf C++ gencode is built with an incompatible version of"
#error "Protobuf C++ headers/runtime. See"
#error "https://protobuf.dev/support/cross-version-runtime-guarantee/#cpp"
#endif
#include "google/protobuf/io/coded_stream.h"
#include "google/protobuf/arena.h"
#include "google/protobuf/arenastring.h"
#include "google/protobuf/generated_message_tctable_decl.h"
#include "google/protobuf/generated_message_util.h"
#include "google/protobuf/metadata_lite.h"
#include "google/protobuf/generated_message_reflection.h"
#include "google/protobuf/message.h"
#include "google/protobuf/message_lite.h"
#include "google/protobuf/repeated_field.h"  // IWYU pragma: export
#include "google/protobuf/extension_set.h"  // IWYU pragma: export
#include "google/protobuf/unknown_field_set.h"
// @@protoc_insertion_point(includes)

// Must be included last.
#include "google/protobuf/port_def.inc"

#define PROTOBUF_INTERNAL_EXPORT_Protocol_2eproto

namespace google {
namespace protobuf {
namespace internal {
template <typename T>
::absl::string_view GetAnyMessageName();
}  // namespace internal
}  // namespace protobuf
}  // namespace google

// Internal implementation detail -- do not use these members.
struct TableStruct_Protocol_2eproto {
  static const ::uint32_t offsets[];
};
extern const ::google::protobuf::internal::DescriptorTable
    descriptor_table_Protocol_2eproto;
namespace Protocol {
class BuffData;
struct BuffDataDefaultTypeInternal;
extern BuffDataDefaultTypeInternal _BuffData_default_instance_;
class dummyMessage;
struct dummyMessageDefaultTypeInternal;
extern dummyMessageDefaultTypeInternal _dummyMessage_default_instance_;
}  // namespace Protocol
namespace google {
namespace protobuf {
}  // namespace protobuf
}  // namespace google

namespace Protocol {

// ===================================================================


// -------------------------------------------------------------------

class BuffData final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:Protocol.BuffData) */ {
 public:
  inline BuffData() : BuffData(nullptr) {}
  ~BuffData() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(BuffData* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(BuffData));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR BuffData(
      ::google::protobuf::internal::ConstantInitialized);

  inline BuffData(const BuffData& from) : BuffData(nullptr, from) {}
  inline BuffData(BuffData&& from) noexcept
      : BuffData(nullptr, std::move(from)) {}
  inline BuffData& operator=(const BuffData& from) {
    CopyFrom(from);
    return *this;
  }
  inline BuffData& operator=(BuffData&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const BuffData& default_instance() {
    return *internal_default_instance();
  }
  static inline const BuffData* internal_default_instance() {
    return reinterpret_cast<const BuffData*>(
        &_BuffData_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 0;
  friend void swap(BuffData& a, BuffData& b) { a.Swap(&b); }
  inline void Swap(BuffData* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(BuffData* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  BuffData* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<BuffData>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const BuffData& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const BuffData& from) { BuffData::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(BuffData* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "Protocol.BuffData"; }

 protected:
  explicit BuffData(::google::protobuf::Arena* arena);
  BuffData(::google::protobuf::Arena* arena, const BuffData& from);
  BuffData(::google::protobuf::Arena* arena, BuffData&& from) noexcept
      : BuffData(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kVictimsFieldNumber = 3,
    kBuffidFieldNumber = 1,
    kRemainTimeFieldNumber = 2,
  };
  // repeated int64 victims = 3;
  int victims_size() const;
  private:
  int _internal_victims_size() const;

  public:
  void clear_victims() ;
  ::int64_t victims(int index) const;
  void set_victims(int index, ::int64_t value);
  void add_victims(::int64_t value);
  const ::google::protobuf::RepeatedField<::int64_t>& victims() const;
  ::google::protobuf::RepeatedField<::int64_t>* mutable_victims();

  private:
  const ::google::protobuf::RepeatedField<::int64_t>& _internal_victims() const;
  ::google::protobuf::RepeatedField<::int64_t>* _internal_mutable_victims();

  public:
  // int64 buffid = 1;
  void clear_buffid() ;
  ::int64_t buffid() const;
  void set_buffid(::int64_t value);

  private:
  ::int64_t _internal_buffid() const;
  void _internal_set_buffid(::int64_t value);

  public:
  // float remainTime = 2;
  void clear_remaintime() ;
  float remaintime() const;
  void set_remaintime(float value);

  private:
  float _internal_remaintime() const;
  void _internal_set_remaintime(float value);

  public:
  // @@protoc_insertion_point(class_scope:Protocol.BuffData)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 3, 0,
      0, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const BuffData& from_msg);
    ::google::protobuf::RepeatedField<::int64_t> victims_;
    ::google::protobuf::internal::CachedSize _victims_cached_byte_size_;
    ::int64_t buffid_;
    float remaintime_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_Protocol_2eproto;
};
// -------------------------------------------------------------------

class dummyMessage final : public ::google::protobuf::Message
/* @@protoc_insertion_point(class_definition:Protocol.dummyMessage) */ {
 public:
  inline dummyMessage() : dummyMessage(nullptr) {}
  ~dummyMessage() PROTOBUF_FINAL;

#if defined(PROTOBUF_CUSTOM_VTABLE)
  void operator delete(dummyMessage* msg, std::destroying_delete_t) {
    SharedDtor(*msg);
    ::google::protobuf::internal::SizedDelete(msg, sizeof(dummyMessage));
  }
#endif

  template <typename = void>
  explicit PROTOBUF_CONSTEXPR dummyMessage(
      ::google::protobuf::internal::ConstantInitialized);

  inline dummyMessage(const dummyMessage& from) : dummyMessage(nullptr, from) {}
  inline dummyMessage(dummyMessage&& from) noexcept
      : dummyMessage(nullptr, std::move(from)) {}
  inline dummyMessage& operator=(const dummyMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline dummyMessage& operator=(dummyMessage&& from) noexcept {
    if (this == &from) return *this;
    if (::google::protobuf::internal::CanMoveWithInternalSwap(GetArena(), from.GetArena())) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.unknown_fields<::google::protobuf::UnknownFieldSet>(::google::protobuf::UnknownFieldSet::default_instance);
  }
  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields()
      ABSL_ATTRIBUTE_LIFETIME_BOUND {
    return _internal_metadata_.mutable_unknown_fields<::google::protobuf::UnknownFieldSet>();
  }

  static const ::google::protobuf::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::google::protobuf::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::google::protobuf::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const dummyMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const dummyMessage* internal_default_instance() {
    return reinterpret_cast<const dummyMessage*>(
        &_dummyMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages = 1;
  friend void swap(dummyMessage& a, dummyMessage& b) { a.Swap(&b); }
  inline void Swap(dummyMessage* other) {
    if (other == this) return;
    if (::google::protobuf::internal::CanUseInternalSwap(GetArena(), other->GetArena())) {
      InternalSwap(other);
    } else {
      ::google::protobuf::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(dummyMessage* other) {
    if (other == this) return;
    ABSL_DCHECK(GetArena() == other->GetArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  dummyMessage* New(::google::protobuf::Arena* arena = nullptr) const {
    return ::google::protobuf::Message::DefaultConstruct<dummyMessage>(arena);
  }
  using ::google::protobuf::Message::CopyFrom;
  void CopyFrom(const dummyMessage& from);
  using ::google::protobuf::Message::MergeFrom;
  void MergeFrom(const dummyMessage& from) { dummyMessage::MergeImpl(*this, from); }

  private:
  static void MergeImpl(
      ::google::protobuf::MessageLite& to_msg,
      const ::google::protobuf::MessageLite& from_msg);

  public:
  bool IsInitialized() const {
    return true;
  }
  ABSL_ATTRIBUTE_REINITIALIZES void Clear() PROTOBUF_FINAL;
  #if defined(PROTOBUF_CUSTOM_VTABLE)
  private:
  static ::size_t ByteSizeLong(const ::google::protobuf::MessageLite& msg);
  static ::uint8_t* _InternalSerialize(
      const MessageLite& msg, ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream);

  public:
  ::size_t ByteSizeLong() const { return ByteSizeLong(*this); }
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const {
    return _InternalSerialize(*this, target, stream);
  }
  #else   // PROTOBUF_CUSTOM_VTABLE
  ::size_t ByteSizeLong() const final;
  ::uint8_t* _InternalSerialize(
      ::uint8_t* target,
      ::google::protobuf::io::EpsCopyOutputStream* stream) const final;
  #endif  // PROTOBUF_CUSTOM_VTABLE
  int GetCachedSize() const { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::google::protobuf::Arena* arena);
  static void SharedDtor(MessageLite& self);
  void InternalSwap(dummyMessage* other);
 private:
  template <typename T>
  friend ::absl::string_view(
      ::google::protobuf::internal::GetAnyMessageName)();
  static ::absl::string_view FullMessageName() { return "Protocol.dummyMessage"; }

 protected:
  explicit dummyMessage(::google::protobuf::Arena* arena);
  dummyMessage(::google::protobuf::Arena* arena, const dummyMessage& from);
  dummyMessage(::google::protobuf::Arena* arena, dummyMessage&& from) noexcept
      : dummyMessage(arena) {
    *this = ::std::move(from);
  }
  const ::google::protobuf::internal::ClassData* GetClassData() const PROTOBUF_FINAL;
  static void* PlacementNew_(const void*, void* mem,
                             ::google::protobuf::Arena* arena);
  static constexpr auto InternalNewImpl_();
  static const ::google::protobuf::internal::ClassDataFull _class_data_;

 public:
  ::google::protobuf::Metadata GetMetadata() const;
  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------
  enum : int {
    kBuffsFieldNumber = 4,
    kIdFieldNumber = 1,
    kHpFieldNumber = 2,
    kAttackFieldNumber = 3,
  };
  // repeated .Protocol.BuffData buffs = 4;
  int buffs_size() const;
  private:
  int _internal_buffs_size() const;

  public:
  void clear_buffs() ;
  ::Protocol::BuffData* mutable_buffs(int index);
  ::google::protobuf::RepeatedPtrField<::Protocol::BuffData>* mutable_buffs();

  private:
  const ::google::protobuf::RepeatedPtrField<::Protocol::BuffData>& _internal_buffs() const;
  ::google::protobuf::RepeatedPtrField<::Protocol::BuffData>* _internal_mutable_buffs();
  public:
  const ::Protocol::BuffData& buffs(int index) const;
  ::Protocol::BuffData* add_buffs();
  const ::google::protobuf::RepeatedPtrField<::Protocol::BuffData>& buffs() const;
  // int64 id = 1;
  void clear_id() ;
  ::int64_t id() const;
  void set_id(::int64_t value);

  private:
  ::int64_t _internal_id() const;
  void _internal_set_id(::int64_t value);

  public:
  // int32 hp = 2;
  void clear_hp() ;
  ::int32_t hp() const;
  void set_hp(::int32_t value);

  private:
  ::int32_t _internal_hp() const;
  void _internal_set_hp(::int32_t value);

  public:
  // int32 attack = 3;
  void clear_attack() ;
  ::int32_t attack() const;
  void set_attack(::int32_t value);

  private:
  ::int32_t _internal_attack() const;
  void _internal_set_attack(::int32_t value);

  public:
  // @@protoc_insertion_point(class_scope:Protocol.dummyMessage)
 private:
  class _Internal;
  friend class ::google::protobuf::internal::TcParser;
  static const ::google::protobuf::internal::TcParseTable<
      2, 4, 1,
      0, 2>
      _table_;

  friend class ::google::protobuf::MessageLite;
  friend class ::google::protobuf::Arena;
  template <typename T>
  friend class ::google::protobuf::Arena::InternalHelper;
  using InternalArenaConstructable_ = void;
  using DestructorSkippable_ = void;
  struct Impl_ {
    inline explicit constexpr Impl_(
        ::google::protobuf::internal::ConstantInitialized) noexcept;
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena);
    inline explicit Impl_(::google::protobuf::internal::InternalVisibility visibility,
                          ::google::protobuf::Arena* arena, const Impl_& from,
                          const dummyMessage& from_msg);
    ::google::protobuf::RepeatedPtrField< ::Protocol::BuffData > buffs_;
    ::int64_t id_;
    ::int32_t hp_;
    ::int32_t attack_;
    ::google::protobuf::internal::CachedSize _cached_size_;
    PROTOBUF_TSAN_DECLARE_MEMBER
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_Protocol_2eproto;
};

// ===================================================================




// ===================================================================


#ifdef __GNUC__
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// -------------------------------------------------------------------

// BuffData

// int64 buffid = 1;
inline void BuffData::clear_buffid() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.buffid_ = ::int64_t{0};
}
inline ::int64_t BuffData::buffid() const {
  // @@protoc_insertion_point(field_get:Protocol.BuffData.buffid)
  return _internal_buffid();
}
inline void BuffData::set_buffid(::int64_t value) {
  _internal_set_buffid(value);
  // @@protoc_insertion_point(field_set:Protocol.BuffData.buffid)
}
inline ::int64_t BuffData::_internal_buffid() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.buffid_;
}
inline void BuffData::_internal_set_buffid(::int64_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.buffid_ = value;
}

// float remainTime = 2;
inline void BuffData::clear_remaintime() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.remaintime_ = 0;
}
inline float BuffData::remaintime() const {
  // @@protoc_insertion_point(field_get:Protocol.BuffData.remainTime)
  return _internal_remaintime();
}
inline void BuffData::set_remaintime(float value) {
  _internal_set_remaintime(value);
  // @@protoc_insertion_point(field_set:Protocol.BuffData.remainTime)
}
inline float BuffData::_internal_remaintime() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.remaintime_;
}
inline void BuffData::_internal_set_remaintime(float value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.remaintime_ = value;
}

// repeated int64 victims = 3;
inline int BuffData::_internal_victims_size() const {
  return _internal_victims().size();
}
inline int BuffData::victims_size() const {
  return _internal_victims_size();
}
inline void BuffData::clear_victims() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.victims_.Clear();
}
inline ::int64_t BuffData::victims(int index) const {
  // @@protoc_insertion_point(field_get:Protocol.BuffData.victims)
  return _internal_victims().Get(index);
}
inline void BuffData::set_victims(int index, ::int64_t value) {
  _internal_mutable_victims()->Set(index, value);
  // @@protoc_insertion_point(field_set:Protocol.BuffData.victims)
}
inline void BuffData::add_victims(::int64_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _internal_mutable_victims()->Add(value);
  // @@protoc_insertion_point(field_add:Protocol.BuffData.victims)
}
inline const ::google::protobuf::RepeatedField<::int64_t>& BuffData::victims() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:Protocol.BuffData.victims)
  return _internal_victims();
}
inline ::google::protobuf::RepeatedField<::int64_t>* BuffData::mutable_victims()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:Protocol.BuffData.victims)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _internal_mutable_victims();
}
inline const ::google::protobuf::RepeatedField<::int64_t>&
BuffData::_internal_victims() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.victims_;
}
inline ::google::protobuf::RepeatedField<::int64_t>* BuffData::_internal_mutable_victims() {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return &_impl_.victims_;
}

// -------------------------------------------------------------------

// dummyMessage

// int64 id = 1;
inline void dummyMessage::clear_id() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.id_ = ::int64_t{0};
}
inline ::int64_t dummyMessage::id() const {
  // @@protoc_insertion_point(field_get:Protocol.dummyMessage.id)
  return _internal_id();
}
inline void dummyMessage::set_id(::int64_t value) {
  _internal_set_id(value);
  // @@protoc_insertion_point(field_set:Protocol.dummyMessage.id)
}
inline ::int64_t dummyMessage::_internal_id() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.id_;
}
inline void dummyMessage::_internal_set_id(::int64_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.id_ = value;
}

// int32 hp = 2;
inline void dummyMessage::clear_hp() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.hp_ = 0;
}
inline ::int32_t dummyMessage::hp() const {
  // @@protoc_insertion_point(field_get:Protocol.dummyMessage.hp)
  return _internal_hp();
}
inline void dummyMessage::set_hp(::int32_t value) {
  _internal_set_hp(value);
  // @@protoc_insertion_point(field_set:Protocol.dummyMessage.hp)
}
inline ::int32_t dummyMessage::_internal_hp() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.hp_;
}
inline void dummyMessage::_internal_set_hp(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.hp_ = value;
}

// int32 attack = 3;
inline void dummyMessage::clear_attack() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.attack_ = 0;
}
inline ::int32_t dummyMessage::attack() const {
  // @@protoc_insertion_point(field_get:Protocol.dummyMessage.attack)
  return _internal_attack();
}
inline void dummyMessage::set_attack(::int32_t value) {
  _internal_set_attack(value);
  // @@protoc_insertion_point(field_set:Protocol.dummyMessage.attack)
}
inline ::int32_t dummyMessage::_internal_attack() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.attack_;
}
inline void dummyMessage::_internal_set_attack(::int32_t value) {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.attack_ = value;
}

// repeated .Protocol.BuffData buffs = 4;
inline int dummyMessage::_internal_buffs_size() const {
  return _internal_buffs().size();
}
inline int dummyMessage::buffs_size() const {
  return _internal_buffs_size();
}
inline void dummyMessage::clear_buffs() {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  _impl_.buffs_.Clear();
}
inline ::Protocol::BuffData* dummyMessage::mutable_buffs(int index)
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable:Protocol.dummyMessage.buffs)
  return _internal_mutable_buffs()->Mutable(index);
}
inline ::google::protobuf::RepeatedPtrField<::Protocol::BuffData>* dummyMessage::mutable_buffs()
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_mutable_list:Protocol.dummyMessage.buffs)
  ::google::protobuf::internal::TSanWrite(&_impl_);
  return _internal_mutable_buffs();
}
inline const ::Protocol::BuffData& dummyMessage::buffs(int index) const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_get:Protocol.dummyMessage.buffs)
  return _internal_buffs().Get(index);
}
inline ::Protocol::BuffData* dummyMessage::add_buffs() ABSL_ATTRIBUTE_LIFETIME_BOUND {
  ::google::protobuf::internal::TSanWrite(&_impl_);
  ::Protocol::BuffData* _add = _internal_mutable_buffs()->Add();
  // @@protoc_insertion_point(field_add:Protocol.dummyMessage.buffs)
  return _add;
}
inline const ::google::protobuf::RepeatedPtrField<::Protocol::BuffData>& dummyMessage::buffs() const
    ABSL_ATTRIBUTE_LIFETIME_BOUND {
  // @@protoc_insertion_point(field_list:Protocol.dummyMessage.buffs)
  return _internal_buffs();
}
inline const ::google::protobuf::RepeatedPtrField<::Protocol::BuffData>&
dummyMessage::_internal_buffs() const {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return _impl_.buffs_;
}
inline ::google::protobuf::RepeatedPtrField<::Protocol::BuffData>*
dummyMessage::_internal_mutable_buffs() {
  ::google::protobuf::internal::TSanRead(&_impl_);
  return &_impl_.buffs_;
}

#ifdef __GNUC__
#pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol


// @@protoc_insertion_point(global_scope)

#include "google/protobuf/port_undef.inc"

#endif  // Protocol_2eproto_2epb_2eh
