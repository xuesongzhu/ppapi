// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef PPAPI_C_PPB_URL_REQUEST_INFO_H_
#define PPAPI_C_PPB_URL_REQUEST_INFO_H_

#include "ppapi/c/pp_module.h"
#include "ppapi/c/pp_resource.h"
#include "ppapi/c/pp_stdint.h"
#include "ppapi/c/pp_time.h"

typedef struct _pp_Var PP_Var;

enum PP_URLRequestProperty {
  PP_URLREQUESTPROPERTY_URL,                   // string
  PP_URLREQUESTPROPERTY_METHOD,                // string
  PP_URLREQUESTPROPERTY_HEADERS,               // string, \n-delim
  PP_URLREQUESTPROPERTY_STREAMTOFILE,          // bool
  PP_URLREQUESTPROPERTY_FOLLOWREDIRECTS,       // bool
  PP_URLREQUESTPROPERTY_RECORDUPLOADPROGRESS,  // bool
  PP_URLREQUESTPROPERTY_ALLOWAUTHENTICATION,   // bool
  PP_URLREQUESTPROPERTY_ALLOWCOOKIES,          // bool
  PP_URLREQUESTPROPERTY_ALLOWREFERRER          // bool
  // TODO(darin): add an option to suppress the Origin header?  Consider
  // dropping support for CORS in favor of UMP.
};

#define PPB_URLREQUESTINFO_INTERFACE "PPB_URLRequestInfo;1"

typedef struct _ppb_URLRequestInfo {
  // Create a new URLRequestInfo object.  Returns 0 if the module is invalid.
  PP_Resource (*Create)(PP_Module module);

  // Returns true if the given resource is an URLRequestInfo. Returns false if
  // the resource is invalid or some type other than an URLRequestInfo.
  bool (*IsURLRequestInfo)(PP_Resource resource);

  // Sets a request property.  Returns false if any of the parameters are
  // invalid.  The value property must be the correct type according to the
  // property being set.
  bool (*SetProperty)(PP_Resource request,
                      PP_URLRequestProperty property,
                      PP_Var value);

  // Append data to the request body.  Returns false if any of the parameters
  // are invalid.  The data parameter must be of type PP_VarType_String.
  bool (*AppendDataToBody)(PP_Resource request, PP_Var data);

  // Append a file reference to be uploaded.
  //
  // A sub-range of the file starting from start_offset may be specified.  If
  // number_of_bytes is -1, then the sub-range to upload extends to the end of
  // the file.
  //
  // An optional (non-zero) last modified time stamp may be provided, which
  // will be used to validate that the file was not modified since the given
  // time before it is uploaded.  The upload will fail with an error code of
  // PP_Error_FileChanged if the file has been modified since the given time.
  // If expected_last_modified_time is 0, then no validation is performed.
  //
  // Returns false if any of the parameters are invalid.
  bool (*AppendFileToBody)(PP_Resource request,
                           PP_Resource file_ref,
                           int64_t start_offset,
                           int64_t number_of_bytes,
                           PP_Time expected_last_modified_time);
} PPB_URLRequestInfo;

#endif  // PPAPI_C_PPB_URL_REQUEST_INFO_H_