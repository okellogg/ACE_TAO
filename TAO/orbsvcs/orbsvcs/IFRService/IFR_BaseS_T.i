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
//
// Information about TAO is available at:
//     http://www.cs.wustl.edu/~schmidt/TAO.html


// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_interface/tie_si.cpp:96

#if defined (ACE_HAS_USING_KEYWORD)

template <class T> ACE_INLINE
POA_CORBA::IRObject_tie<T>::IRObject_tie (T &t)
	: ptr_ (&t),
	  poa_ (PortableServer::POA::_nil ()),
	  rel_ (0)
{}

template <class T> ACE_INLINE
POA_CORBA::IRObject_tie<T>::IRObject_tie (T &t, PortableServer::POA_ptr poa)
	: ptr_ (&t),
	  poa_ (PortableServer::POA::_duplicate (poa)),
	  rel_ (0)
{}

template <class T> ACE_INLINE
POA_CORBA::IRObject_tie<T>::IRObject_tie (T *tp, CORBA::Boolean release)
	: ptr_ (tp),
	  poa_ (PortableServer::POA::_nil ()),
	  rel_ (release)
{}

template <class T> ACE_INLINE
POA_CORBA::IRObject_tie<T>::IRObject_tie (T *tp, PortableServer::POA_ptr poa, CORBA::Boolean release)
	: ptr_ (tp),
	  poa_ (PortableServer::POA::_duplicate (poa)),
	  rel_ (release)
{}

template <class T> ACE_INLINE
POA_CORBA::IRObject_tie<T>::~IRObject_tie (void)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
}

template <class T> ACE_INLINE T *
POA_CORBA::IRObject_tie<T>::_tied_object (void)
{
  return this->ptr_;
}

template <class T> ACE_INLINE void
POA_CORBA::IRObject_tie<T>::_tied_object (T &obj)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
  
  this->ptr_ = &obj;
  this->rel_ = 0;
}

template <class T> ACE_INLINE void
POA_CORBA::IRObject_tie<T>::_tied_object (T *obj, CORBA::Boolean release)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
  
  this->ptr_ = obj;
  this->rel_ = release;
}

template <class T> ACE_INLINE CORBA::Boolean
POA_CORBA::IRObject_tie<T>::_is_owner (void)
{
  return this->rel_;
}

template <class T> ACE_INLINE void
POA_CORBA::IRObject_tie<T>::_is_owner (CORBA::Boolean b)
{
  this->rel_ = b;
}

template <class T> ACE_INLINE PortableServer::POA_ptr
POA_CORBA::IRObject_tie<T>::_default_POA (ACE_ENV_SINGLE_ARG_DECL)
{
  if (!CORBA::is_nil (this->poa_.in ()))
    {
      return PortableServer::POA::_duplicate (this->poa_.in ());
    }
  
  return this->IRObject::_default_POA (ACE_ENV_SINGLE_ARG_PARAMETER);
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::DefinitionKind POA_CORBA::IRObject_tie<T>::def_kind  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->def_kind (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::IRObject_tie<T>::destroy  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->destroy (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

#endif /* ACE_HAS_USING_KEYWORD */

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_interface/tie_si.cpp:96

#if defined (ACE_HAS_USING_KEYWORD)

template <class T> ACE_INLINE
POA_CORBA::Contained_tie<T>::Contained_tie (T &t)
	: ptr_ (&t),
	  poa_ (PortableServer::POA::_nil ()),
	  rel_ (0)
{}

template <class T> ACE_INLINE
POA_CORBA::Contained_tie<T>::Contained_tie (T &t, PortableServer::POA_ptr poa)
	: ptr_ (&t),
	  poa_ (PortableServer::POA::_duplicate (poa)),
	  rel_ (0)
{}

template <class T> ACE_INLINE
POA_CORBA::Contained_tie<T>::Contained_tie (T *tp, CORBA::Boolean release)
	: ptr_ (tp),
	  poa_ (PortableServer::POA::_nil ()),
	  rel_ (release)
{}

template <class T> ACE_INLINE
POA_CORBA::Contained_tie<T>::Contained_tie (T *tp, PortableServer::POA_ptr poa, CORBA::Boolean release)
	: ptr_ (tp),
	  poa_ (PortableServer::POA::_duplicate (poa)),
	  rel_ (release)
{}

template <class T> ACE_INLINE
POA_CORBA::Contained_tie<T>::~Contained_tie (void)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
}

template <class T> ACE_INLINE T *
POA_CORBA::Contained_tie<T>::_tied_object (void)
{
  return this->ptr_;
}

template <class T> ACE_INLINE void
POA_CORBA::Contained_tie<T>::_tied_object (T &obj)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
  
  this->ptr_ = &obj;
  this->rel_ = 0;
}

template <class T> ACE_INLINE void
POA_CORBA::Contained_tie<T>::_tied_object (T *obj, CORBA::Boolean release)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
  
  this->ptr_ = obj;
  this->rel_ = release;
}

template <class T> ACE_INLINE CORBA::Boolean
POA_CORBA::Contained_tie<T>::_is_owner (void)
{
  return this->rel_;
}

template <class T> ACE_INLINE void
POA_CORBA::Contained_tie<T>::_is_owner (CORBA::Boolean b)
{
  this->rel_ = b;
}

template <class T> ACE_INLINE PortableServer::POA_ptr
POA_CORBA::Contained_tie<T>::_default_POA (ACE_ENV_SINGLE_ARG_DECL)
{
  if (!CORBA::is_nil (this->poa_.in ()))
    {
      return PortableServer::POA::_duplicate (this->poa_.in ());
    }
  
  return this->Contained::_default_POA (ACE_ENV_SINGLE_ARG_PARAMETER);
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
char * POA_CORBA::Contained_tie<T>::id  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->id (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::Contained_tie<T>::id  (
    const char * id
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->id (
    id
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
char * POA_CORBA::Contained_tie<T>::name  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->name (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::Contained_tie<T>::name  (
    const char * name
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->name (
    name
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
char * POA_CORBA::Contained_tie<T>::version  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->version (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::Contained_tie<T>::version  (
    const char * version
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->version (
    version
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::Container_ptr POA_CORBA::Contained_tie<T>::defined_in  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->defined_in (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
char * POA_CORBA::Contained_tie<T>::absolute_name  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->absolute_name (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::Repository_ptr POA_CORBA::Contained_tie<T>::containing_repository  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->containing_repository (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::Contained::Description * POA_CORBA::Contained_tie<T>::describe  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->describe (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::Contained_tie<T>::move  (
    CORBA::Container_ptr new_container,
    const char * new_name,
    const char * new_version
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->move (
    new_container,
    new_name,
    new_version
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::DefinitionKind POA_CORBA::Contained_tie<T>::def_kind  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->def_kind (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::Contained_tie<T>::destroy  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->destroy (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

#endif /* ACE_HAS_USING_KEYWORD */

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_interface/tie_si.cpp:96

#if defined (ACE_HAS_USING_KEYWORD)

template <class T> ACE_INLINE
POA_CORBA::Container_tie<T>::Container_tie (T &t)
	: ptr_ (&t),
	  poa_ (PortableServer::POA::_nil ()),
	  rel_ (0)
{}

template <class T> ACE_INLINE
POA_CORBA::Container_tie<T>::Container_tie (T &t, PortableServer::POA_ptr poa)
	: ptr_ (&t),
	  poa_ (PortableServer::POA::_duplicate (poa)),
	  rel_ (0)
{}

template <class T> ACE_INLINE
POA_CORBA::Container_tie<T>::Container_tie (T *tp, CORBA::Boolean release)
	: ptr_ (tp),
	  poa_ (PortableServer::POA::_nil ()),
	  rel_ (release)
{}

template <class T> ACE_INLINE
POA_CORBA::Container_tie<T>::Container_tie (T *tp, PortableServer::POA_ptr poa, CORBA::Boolean release)
	: ptr_ (tp),
	  poa_ (PortableServer::POA::_duplicate (poa)),
	  rel_ (release)
{}

template <class T> ACE_INLINE
POA_CORBA::Container_tie<T>::~Container_tie (void)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
}

template <class T> ACE_INLINE T *
POA_CORBA::Container_tie<T>::_tied_object (void)
{
  return this->ptr_;
}

template <class T> ACE_INLINE void
POA_CORBA::Container_tie<T>::_tied_object (T &obj)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
  
  this->ptr_ = &obj;
  this->rel_ = 0;
}

template <class T> ACE_INLINE void
POA_CORBA::Container_tie<T>::_tied_object (T *obj, CORBA::Boolean release)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
  
  this->ptr_ = obj;
  this->rel_ = release;
}

template <class T> ACE_INLINE CORBA::Boolean
POA_CORBA::Container_tie<T>::_is_owner (void)
{
  return this->rel_;
}

template <class T> ACE_INLINE void
POA_CORBA::Container_tie<T>::_is_owner (CORBA::Boolean b)
{
  this->rel_ = b;
}

template <class T> ACE_INLINE PortableServer::POA_ptr
POA_CORBA::Container_tie<T>::_default_POA (ACE_ENV_SINGLE_ARG_DECL)
{
  if (!CORBA::is_nil (this->poa_.in ()))
    {
      return PortableServer::POA::_duplicate (this->poa_.in ());
    }
  
  return this->Container::_default_POA (ACE_ENV_SINGLE_ARG_PARAMETER);
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::Contained_ptr POA_CORBA::Container_tie<T>::lookup  (
    const char * search_name
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->lookup (
    search_name
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::ContainedSeq * POA_CORBA::Container_tie<T>::contents  (
    CORBA::DefinitionKind limit_type,
    CORBA::Boolean exclude_inherited
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->contents (
    limit_type,
    exclude_inherited
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::ContainedSeq * POA_CORBA::Container_tie<T>::lookup_name  (
    const char * search_name,
    CORBA::Long levels_to_search,
    CORBA::DefinitionKind limit_type,
    CORBA::Boolean exclude_inherited
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->lookup_name (
    search_name,
    levels_to_search,
    limit_type,
    exclude_inherited
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::Container::DescriptionSeq * POA_CORBA::Container_tie<T>::describe_contents  (
    CORBA::DefinitionKind limit_type,
    CORBA::Boolean exclude_inherited,
    CORBA::Long max_returned_objs
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->describe_contents (
    limit_type,
    exclude_inherited,
    max_returned_objs
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::ModuleDef_ptr POA_CORBA::Container_tie<T>::create_module  (
    const char * id,
    const char * name,
    const char * version
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_module (
    id,
    name,
    version
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::ConstantDef_ptr POA_CORBA::Container_tie<T>::create_constant  (
    const char * id,
    const char * name,
    const char * version,
    CORBA::IDLType_ptr type,
    const CORBA::Any & value
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_constant (
    id,
    name,
    version,
    type,
    value
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::StructDef_ptr POA_CORBA::Container_tie<T>::create_struct  (
    const char * id,
    const char * name,
    const char * version,
    const CORBA::StructMemberSeq & members
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_struct (
    id,
    name,
    version,
    members
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::UnionDef_ptr POA_CORBA::Container_tie<T>::create_union  (
    const char * id,
    const char * name,
    const char * version,
    CORBA::IDLType_ptr discriminator_type,
    const CORBA::UnionMemberSeq & members
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_union (
    id,
    name,
    version,
    discriminator_type,
    members
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::EnumDef_ptr POA_CORBA::Container_tie<T>::create_enum  (
    const char * id,
    const char * name,
    const char * version,
    const CORBA::EnumMemberSeq & members
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_enum (
    id,
    name,
    version,
    members
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::AliasDef_ptr POA_CORBA::Container_tie<T>::create_alias  (
    const char * id,
    const char * name,
    const char * version,
    CORBA::IDLType_ptr original_type
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_alias (
    id,
    name,
    version,
    original_type
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::InterfaceDef_ptr POA_CORBA::Container_tie<T>::create_interface  (
    const char * id,
    const char * name,
    const char * version,
    const CORBA::InterfaceDefSeq & base_interfaces
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_interface (
    id,
    name,
    version,
    base_interfaces
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::ValueDef_ptr POA_CORBA::Container_tie<T>::create_value  (
    const char * id,
    const char * name,
    const char * version,
    CORBA::Boolean is_custom,
    CORBA::Boolean is_abstract,
    CORBA::ValueDef_ptr base_value,
    CORBA::Boolean is_truncatable,
    const CORBA::ValueDefSeq & abstract_base_values,
    const CORBA::InterfaceDefSeq & supported_interfaces,
    const CORBA::InitializerSeq & initializers
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_value (
    id,
    name,
    version,
    is_custom,
    is_abstract,
    base_value,
    is_truncatable,
    abstract_base_values,
    supported_interfaces,
    initializers
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::ValueBoxDef_ptr POA_CORBA::Container_tie<T>::create_value_box  (
    const char * id,
    const char * name,
    const char * version,
    CORBA::IDLType_ptr original_type_def
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_value_box (
    id,
    name,
    version,
    original_type_def
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::ExceptionDef_ptr POA_CORBA::Container_tie<T>::create_exception  (
    const char * id,
    const char * name,
    const char * version,
    const CORBA::StructMemberSeq & members
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_exception (
    id,
    name,
    version,
    members
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::NativeDef_ptr POA_CORBA::Container_tie<T>::create_native  (
    const char * id,
    const char * name,
    const char * version
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_native (
    id,
    name,
    version
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::AbstractInterfaceDef_ptr POA_CORBA::Container_tie<T>::create_abstract_interface  (
    const char * id,
    const char * name,
    const char * version,
    const CORBA::AbstractInterfaceDefSeq & base_interfaces
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_abstract_interface (
    id,
    name,
    version,
    base_interfaces
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::LocalInterfaceDef_ptr POA_CORBA::Container_tie<T>::create_local_interface  (
    const char * id,
    const char * name,
    const char * version,
    const CORBA::InterfaceDefSeq & base_interfaces
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_local_interface (
    id,
    name,
    version,
    base_interfaces
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::ExtValueDef_ptr POA_CORBA::Container_tie<T>::create_ext_value  (
    const char * id,
    const char * name,
    const char * version,
    CORBA::Boolean is_custom,
    CORBA::Boolean is_abstract,
    CORBA::ValueDef_ptr base_value,
    CORBA::Boolean is_truncatable,
    const CORBA::ValueDefSeq & abstract_base_values,
    const CORBA::InterfaceDefSeq & supported_interfaces,
    const CORBA::ExtInitializerSeq & initializers
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->create_ext_value (
    id,
    name,
    version,
    is_custom,
    is_abstract,
    base_value,
    is_truncatable,
    abstract_base_values,
    supported_interfaces,
    initializers
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::DefinitionKind POA_CORBA::Container_tie<T>::def_kind  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->def_kind (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::Container_tie<T>::destroy  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->destroy (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

#endif /* ACE_HAS_USING_KEYWORD */

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_interface/tie_si.cpp:96

#if defined (ACE_HAS_USING_KEYWORD)

template <class T> ACE_INLINE
POA_CORBA::IDLType_tie<T>::IDLType_tie (T &t)
	: ptr_ (&t),
	  poa_ (PortableServer::POA::_nil ()),
	  rel_ (0)
{}

template <class T> ACE_INLINE
POA_CORBA::IDLType_tie<T>::IDLType_tie (T &t, PortableServer::POA_ptr poa)
	: ptr_ (&t),
	  poa_ (PortableServer::POA::_duplicate (poa)),
	  rel_ (0)
{}

template <class T> ACE_INLINE
POA_CORBA::IDLType_tie<T>::IDLType_tie (T *tp, CORBA::Boolean release)
	: ptr_ (tp),
	  poa_ (PortableServer::POA::_nil ()),
	  rel_ (release)
{}

template <class T> ACE_INLINE
POA_CORBA::IDLType_tie<T>::IDLType_tie (T *tp, PortableServer::POA_ptr poa, CORBA::Boolean release)
	: ptr_ (tp),
	  poa_ (PortableServer::POA::_duplicate (poa)),
	  rel_ (release)
{}

template <class T> ACE_INLINE
POA_CORBA::IDLType_tie<T>::~IDLType_tie (void)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
}

template <class T> ACE_INLINE T *
POA_CORBA::IDLType_tie<T>::_tied_object (void)
{
  return this->ptr_;
}

template <class T> ACE_INLINE void
POA_CORBA::IDLType_tie<T>::_tied_object (T &obj)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
  
  this->ptr_ = &obj;
  this->rel_ = 0;
}

template <class T> ACE_INLINE void
POA_CORBA::IDLType_tie<T>::_tied_object (T *obj, CORBA::Boolean release)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
  
  this->ptr_ = obj;
  this->rel_ = release;
}

template <class T> ACE_INLINE CORBA::Boolean
POA_CORBA::IDLType_tie<T>::_is_owner (void)
{
  return this->rel_;
}

template <class T> ACE_INLINE void
POA_CORBA::IDLType_tie<T>::_is_owner (CORBA::Boolean b)
{
  this->rel_ = b;
}

template <class T> ACE_INLINE PortableServer::POA_ptr
POA_CORBA::IDLType_tie<T>::_default_POA (ACE_ENV_SINGLE_ARG_DECL)
{
  if (!CORBA::is_nil (this->poa_.in ()))
    {
      return PortableServer::POA::_duplicate (this->poa_.in ());
    }
  
  return this->IDLType::_default_POA (ACE_ENV_SINGLE_ARG_PARAMETER);
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
CORBA::TypeCode_ptr POA_CORBA::IDLType_tie<T>::type  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->type (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::DefinitionKind POA_CORBA::IDLType_tie<T>::def_kind  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->def_kind (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::IDLType_tie<T>::destroy  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->destroy (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

#endif /* ACE_HAS_USING_KEYWORD */

// TAO_IDL - Generated from
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_interface/tie_si.cpp:96

#if defined (ACE_HAS_USING_KEYWORD)

template <class T> ACE_INLINE
POA_CORBA::TypedefDef_tie<T>::TypedefDef_tie (T &t)
	: ptr_ (&t),
	  poa_ (PortableServer::POA::_nil ()),
	  rel_ (0)
{}

template <class T> ACE_INLINE
POA_CORBA::TypedefDef_tie<T>::TypedefDef_tie (T &t, PortableServer::POA_ptr poa)
	: ptr_ (&t),
	  poa_ (PortableServer::POA::_duplicate (poa)),
	  rel_ (0)
{}

template <class T> ACE_INLINE
POA_CORBA::TypedefDef_tie<T>::TypedefDef_tie (T *tp, CORBA::Boolean release)
	: ptr_ (tp),
	  poa_ (PortableServer::POA::_nil ()),
	  rel_ (release)
{}

template <class T> ACE_INLINE
POA_CORBA::TypedefDef_tie<T>::TypedefDef_tie (T *tp, PortableServer::POA_ptr poa, CORBA::Boolean release)
	: ptr_ (tp),
	  poa_ (PortableServer::POA::_duplicate (poa)),
	  rel_ (release)
{}

template <class T> ACE_INLINE
POA_CORBA::TypedefDef_tie<T>::~TypedefDef_tie (void)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
}

template <class T> ACE_INLINE T *
POA_CORBA::TypedefDef_tie<T>::_tied_object (void)
{
  return this->ptr_;
}

template <class T> ACE_INLINE void
POA_CORBA::TypedefDef_tie<T>::_tied_object (T &obj)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
  
  this->ptr_ = &obj;
  this->rel_ = 0;
}

template <class T> ACE_INLINE void
POA_CORBA::TypedefDef_tie<T>::_tied_object (T *obj, CORBA::Boolean release)
{
  if (this->rel_)
    {
      delete this->ptr_;
    }
  
  this->ptr_ = obj;
  this->rel_ = release;
}

template <class T> ACE_INLINE CORBA::Boolean
POA_CORBA::TypedefDef_tie<T>::_is_owner (void)
{
  return this->rel_;
}

template <class T> ACE_INLINE void
POA_CORBA::TypedefDef_tie<T>::_is_owner (CORBA::Boolean b)
{
  this->rel_ = b;
}

template <class T> ACE_INLINE PortableServer::POA_ptr
POA_CORBA::TypedefDef_tie<T>::_default_POA (ACE_ENV_SINGLE_ARG_DECL)
{
  if (!CORBA::is_nil (this->poa_.in ()))
    {
      return PortableServer::POA::_duplicate (this->poa_.in ());
    }
  
  return this->TypedefDef::_default_POA (ACE_ENV_SINGLE_ARG_PARAMETER);
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
char * POA_CORBA::TypedefDef_tie<T>::id  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->id (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::TypedefDef_tie<T>::id  (
    const char * id
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->id (
    id
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
char * POA_CORBA::TypedefDef_tie<T>::name  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->name (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::TypedefDef_tie<T>::name  (
    const char * name
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->name (
    name
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
char * POA_CORBA::TypedefDef_tie<T>::version  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->version (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::TypedefDef_tie<T>::version  (
    const char * version
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->version (
    version
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::Container_ptr POA_CORBA::TypedefDef_tie<T>::defined_in  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->defined_in (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
char * POA_CORBA::TypedefDef_tie<T>::absolute_name  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->absolute_name (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::Repository_ptr POA_CORBA::TypedefDef_tie<T>::containing_repository  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->containing_repository (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::Contained::Description * POA_CORBA::TypedefDef_tie<T>::describe  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->describe (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::TypedefDef_tie<T>::move  (
    CORBA::Container_ptr new_container,
    const char * new_name,
    const char * new_version
    ACE_ENV_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->move (
    new_container,
    new_name,
    new_version
    ACE_ENV_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
CORBA::TypeCode_ptr POA_CORBA::TypedefDef_tie<T>::type  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->type (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
::CORBA::DefinitionKind POA_CORBA::TypedefDef_tie<T>::def_kind  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  return this->ptr_->def_kind (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

// TAO_IDL - Generated from 
// W:\ACE_wrappers\TAO\TAO_IDL\be\be_visitor_operation/tie_si.cpp:68

template <class T> ACE_INLINE
void POA_CORBA::TypedefDef_tie<T>::destroy  (
    ACE_ENV_SINGLE_ARG_DECL
  )
  ACE_THROW_SPEC ((
    CORBA::SystemException
  ))
{
  this->ptr_->destroy (
    ACE_ENV_SINGLE_ARG_PARAMETER
  );
}

#endif /* ACE_HAS_USING_KEYWORD */


