// -*- C++ -*-
//
// $Id$

#include "RequestInfo_Util.h"
#include "Any.h"
#include "StringSeqC.h"

ACE_RCSID (tao, RequestInfo_Util, "$Id$")

Dynamic::ParameterList *
TAO_RequestInfo_Util::make_parameter_list (ACE_ENV_SINGLE_ARG_DECL)
{
  Dynamic::ParameterList *parameter_list = 0;
  ACE_NEW_THROW_EX (parameter_list,
                    Dynamic::ParameterList,
                    CORBA::NO_MEMORY (
                      CORBA::SystemException::_tao_minor_code (
                        TAO_DEFAULT_MINOR_CODE,
                        ENOMEM),
                      CORBA::COMPLETED_NO));

  // No need to do an ACE_CHECK_RETURN.  The caller should do that.

  return parameter_list;
}

Dynamic::ExceptionList *
TAO_RequestInfo_Util::make_exception_list (ACE_ENV_SINGLE_ARG_DECL)
{
  Dynamic::ExceptionList *exception_list = 0;
  ACE_NEW_THROW_EX (exception_list,
                    Dynamic::ExceptionList,
                    CORBA::NO_MEMORY (
                      CORBA::SystemException::_tao_minor_code (
                        TAO_DEFAULT_MINOR_CODE,
                        ENOMEM),
                      CORBA::COMPLETED_NO));

  // No need to do an ACE_CHECK_RETURN.  The caller should do that.

  return exception_list;
}

Dynamic::ContextList *
TAO_RequestInfo_Util::make_context_list (ACE_ENV_SINGLE_ARG_DECL)
{
  Dynamic::ContextList *context_list = 0;
  ACE_NEW_THROW_EX (context_list,
                    Dynamic::ContextList,
                    CORBA::NO_MEMORY (
                      CORBA::SystemException::_tao_minor_code (
                        TAO_DEFAULT_MINOR_CODE,
                        ENOMEM),
                      CORBA::COMPLETED_NO));

  // No need to do an ACE_CHECK_RETURN.  The caller should do that.

  return context_list;
}

Dynamic::RequestContext *
TAO_RequestInfo_Util::make_request_context (ACE_ENV_SINGLE_ARG_DECL)
{
  Dynamic::RequestContext *request_context = 0;
  ACE_NEW_THROW_EX (request_context,
                    Dynamic::RequestContext,
                    CORBA::NO_MEMORY (
                      CORBA::SystemException::_tao_minor_code (
                        TAO_DEFAULT_MINOR_CODE,
                        ENOMEM),
                      CORBA::COMPLETED_NO));

  // No need to do an ACE_CHECK_RETURN.  The caller should do that.

  return request_context;
}

CORBA::Any *
TAO_RequestInfo_Util::make_any (CORBA::Boolean tk_void_any
                                ACE_ENV_ARG_DECL)
{
  CORBA::Any *any = 0;
  ACE_NEW_THROW_EX (any,
                    CORBA::Any,
                    CORBA::NO_MEMORY (
                      CORBA::SystemException::_tao_minor_code (
                        TAO_DEFAULT_MINOR_CODE,
                        ENOMEM),
                      CORBA::COMPLETED_NO));

  if (tk_void_any)
    {
      any->_tao_set_typecode (CORBA::_tc_void);
    }

  // No need to do an ACE_CHECK_RETURN.  The caller should do that.

  return any;
}
