// Protocol Buffers - Google's data interchange format
// Copyright 2023 Google LLC.  All rights reserved.
//
// Use of this source code is governed by a BSD-style
// license that can be found in the LICENSE file or at
// https://developers.google.com/open-source/licenses/bsd

#include "google/protobuf/compiler/hpb/output.h"

#include <string>

#include "upb_generator/c/names.h"
#include "upb_generator/minitable/names.h"

namespace google::protobuf::hpb_generator {
namespace {

namespace protobuf = ::proto2;

}  // namespace

std::string ToCIdent(absl::string_view str) {
  return absl::StrReplaceAll(str, {{".", "_"}, {"/", "_"}, {"-", "_"}});
}

std::string ToPreproc(absl::string_view str) {
  return absl::AsciiStrToUpper(ToCIdent(str));
}

void EmitFileWarning(const protobuf::FileDescriptor* file, Output& output) {
  output(
      R"cc(
        /* This file was generated by hpb_generator (Handle Protobuf) "
        from the input
         * file:
         *
         *     $0
         *
         * Do not edit -- your changes will be discarded when the file is
         * regenerated. */
      )cc",
      file->name());
  output("\n");
}

std::string MessageName(const protobuf::Descriptor* descriptor) {
  return upb::generator::CApiMessageType(descriptor->full_name());
}

std::string FileLayoutName(const google::protobuf::FileDescriptor* file) {
  return upb::generator::MiniTableFileVarName(file->name());
}

std::string CHeaderFilename(const google::protobuf::FileDescriptor* file) {
  return upb::generator::CApiHeaderFilename(file->name());
}

}  // namespace protobuf
}  // namespace google::hpb_generator
