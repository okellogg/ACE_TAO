// -*- C++ -*-
//
// $Id$

// ****  Code generated by the The ACE ORB (TAO) IDL Compiler ****
// TAO and the TAO IDL Compiler have been developed by:
//       Center for Distributed Object Computing
//       Washington University
//       St. Louis, MO
//       USA
//       http://www.cs.wustl.edu/~schmidt/doc-center.html
// and
//       Distributed Object Computing Laboratory
//       University of California at Irvine
//       Irvine, CA
//       USA
//       http://doc.ece.uci.edu/
// and
//       Institute for Software Integrated Systems
//       Vanderbilt University
//       Nashville, TN
//       USA
//       http://www.isis.vanderbilt.edu/
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html


// TAO_IDL - Generated from
// be/be_visitor_interface/interface_ci.cpp:63

#if !defined (_RTSCHEDULING_THREADACTION___CI_)
#define _RTSCHEDULING_THREADACTION___CI_

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::ThreadAction>::to_object (
    CORBA::Object_ptr &_tao_elem
  ) const
{
  _tao_elem = CORBA::Object::_duplicate (this->value_);
  return 1;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::ThreadAction>::marshal_value (TAO_OutputCDR &)
{
  return 0;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::ThreadAction>::demarshal_value (TAO_InputCDR &)
{
  return 0;
}

#endif /* end #if !defined */

// TAO_IDL - Generated from
// be/be_visitor_interface/interface_ci.cpp:63

#if !defined (_RTSCHEDULING_DISTRIBUTABLETHREAD___CI_)
#define _RTSCHEDULING_DISTRIBUTABLETHREAD___CI_

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::DistributableThread>::to_object (
    CORBA::Object_ptr &_tao_elem
  ) const
{
  _tao_elem = CORBA::Object::_duplicate (this->value_);
  return 1;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::DistributableThread>::marshal_value (TAO_OutputCDR &)
{
  return 0;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::DistributableThread>::demarshal_value (TAO_InputCDR &)
{
  return 0;
}

#endif /* end #if !defined */

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Dual_Impl_T<RTScheduling::Current::UNSUPPORTED_SCHEDULING_DISCIPLINE>::marshal_value (TAO_OutputCDR &)
{
  return 0;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Dual_Impl_T<RTScheduling::Current::UNSUPPORTED_SCHEDULING_DISCIPLINE>::demarshal_value (TAO_InputCDR &)
{
  return 0;
}

// TAO_IDL - Generated from
// be/be_visitor_interface/interface_ci.cpp:63

#if !defined (_RTSCHEDULING_CURRENT___CI_)
#define _RTSCHEDULING_CURRENT___CI_

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::Current>::to_object (
    CORBA::Object_ptr &_tao_elem
  ) const
{
  _tao_elem = CORBA::Object::_duplicate (this->value_);
  return 1;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::Current>::marshal_value (TAO_OutputCDR &)
{
  return 0;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::Current>::demarshal_value (TAO_InputCDR &)
{
  return 0;
}

#endif /* end #if !defined */

// TAO_IDL - Generated from
// be/be_visitor_interface/interface_ci.cpp:63

#if !defined (_RTSCHEDULING_RESOURCEMANAGER___CI_)
#define _RTSCHEDULING_RESOURCEMANAGER___CI_

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::ResourceManager>::to_object (
    CORBA::Object_ptr &_tao_elem
  ) const
{
  _tao_elem = CORBA::Object::_duplicate (this->value_);
  return 1;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::ResourceManager>::marshal_value (TAO_OutputCDR &)
{
  return 0;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::ResourceManager>::demarshal_value (TAO_InputCDR &)
{
  return 0;
}

#endif /* end #if !defined */

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Dual_Impl_T<RTScheduling::Scheduler::INCOMPATIBLE_SCHEDULING_DISCIPLINES>::marshal_value (TAO_OutputCDR &)
{
  return 0;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Dual_Impl_T<RTScheduling::Scheduler::INCOMPATIBLE_SCHEDULING_DISCIPLINES>::demarshal_value (TAO_InputCDR &)
{
  return 0;
}

// TAO_IDL - Generated from
// be/be_visitor_interface/interface_ci.cpp:63

#if !defined (_RTSCHEDULING_SCHEDULER___CI_)
#define _RTSCHEDULING_SCHEDULER___CI_

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::Scheduler>::to_object (
    CORBA::Object_ptr &_tao_elem
  ) const
{
  _tao_elem = CORBA::Object::_duplicate (this->value_);
  return 1;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::Scheduler>::marshal_value (TAO_OutputCDR &)
{
  return 0;
}

template<>
ACE_INLINE
CORBA::Boolean
TAO::Any_Impl_T<RTScheduling::Scheduler>::demarshal_value (TAO_InputCDR &)
{
  return 0;
}

#endif /* end #if !defined */

