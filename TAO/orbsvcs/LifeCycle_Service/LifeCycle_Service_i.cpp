// $Id$

// ============================================================================
//
// = FILENAME
//    Life_Cycle_Service_i.cpp
//
// = DESCRIPTION
//    The implementation of a LifeCycle Service GenericFactory.
//
// = AUTHOR
//    Michael Kircher (mk1@cs.wustl.edu)
//
// ============================================================================

#include "ace/Get_Opt.h"
#include "tao/corba.h"
#include "orbsvcs/LifeCycleServiceC.h"
#include "LifeCycle_Service_i.h"

ACE_RCSID(LifeCycle_Service, LifeCycle_Service_i, "$Id$")

// Constructor
Life_Cycle_Service_i::Life_Cycle_Service_i (int debug_level)
  : factory_trader_ptr_ (0),
    debug_level_ (debug_level)
{
}

// Destructor.
Life_Cycle_Service_i::~Life_Cycle_Service_i (void)
{
}


CORBA::Boolean
Life_Cycle_Service_i::supports (const CosLifeCycle::Key &
                                ACE_ENV_ARG_DECL_NOT_USED)
  ACE_THROW_SPEC ((CORBA::SystemException))
{
  return 0;
}

CORBA::Object_ptr
Life_Cycle_Service_i::create_object (const CosLifeCycle::Key &factory_key,
                                     const CosLifeCycle::Criteria &the_criteria
                                     ACE_ENV_ARG_DECL)
  ACE_THROW_SPEC ((CORBA::SystemException,
                   CosLifeCycle::NoFactory,
                   CosLifeCycle::InvalidCriteria,
                   CosLifeCycle::CannotMeetCriteria))
{
  if (this->debug_level_ >= 2)
    ACE_DEBUG ((LM_DEBUG, "Life_Cycle_Service_i:create_object: called.\n"));
    // Exceptions are forwarded, not handled !!

  if (factory_trader_ptr_ != 0)
    {
      Criteria_Evaluator criteria_Evaluator(the_criteria);

      if (this->debug_level_ >= 2)
        ACE_DEBUG ((LM_DEBUG, "Life_Cycle_Service_i:create_object: new evaluator.\n"));

      if (this->debug_level_ >= 2)
        ACE_DEBUG ((LM_DEBUG, "Life_Cycle_Service_i:create_object: getFilter will be called.\n"));

      char* filter = criteria_Evaluator.getFilter (ACE_ENV_SINGLE_ARG_PARAMETER);
      ACE_CHECK_RETURN (0);

      if (this->debug_level_ >= 2)
        ACE_DEBUG ((LM_DEBUG, "Life_Cycle_Service_i:create_object: query(%s) will be called.\n",filter));

      CORBA::Object_ptr genericFactoryObj_ptr = factory_trader_ptr_->query (filter);

      if (this->debug_level_ >= 2)
        ACE_DEBUG ((LM_DEBUG, "Life_Cycle_Service_i:create_object: query was called.\n"));

      if (CORBA::is_nil (genericFactoryObj_ptr))
        ACE_ERROR_RETURN ((LM_ERROR,
                           "Life_Cycle_Service_i::create_object: Factory is nil!\n"),
                          0);
      else // everyting is ok
        if (this->debug_level_ >= 2)
          ACE_DEBUG ((LM_DEBUG, "Life_Cycle_Service_i::create_object: Object reference OK.\n"));

      // Now we have a proper reference to a Generic Factory
      // the create_object call will be forwarded to this factory


      // Check if it is a valid Generic Factory reference
      if (CORBA::is_nil (genericFactoryObj_ptr))
        ACE_THROW_RETURN (CosLifeCycle::NoFactory (factory_key), 0);
      else
        {
          CosLifeCycle::GenericFactory_var genericFactory_var;
          ACE_TRY
            {
              genericFactory_var =
                CosLifeCycle::GenericFactory::_narrow (genericFactoryObj_ptr
                                                       ACE_ENV_ARG_PARAMETER);
              // ACE_TRY_CHECK;
            }
          ACE_CATCHANY
            {
              // see if there is an exception, if yes then throw the
              // NoFactory exception throw a NoFactory exception
              ACE_TRY_THROW (CosLifeCycle::NoFactory (factory_key));
            }
          ACE_ENDTRY;
          ACE_CHECK_RETURN (0);

          if (CORBA::is_nil (genericFactory_var.in()))
            ACE_ERROR_RETURN ((LM_ERROR,
                               "Life_Cycle_Service_i::create_object: Invalid Generic Factory.\n"),
                              0);

          if (this->debug_level_ >= 2)
            ACE_DEBUG ((LM_DEBUG, "Life_Cycle_Service_i::create_object: Generic Factory reference OK.\n"));

          // Now retrieve the Object obj ref corresponding to the key.
          CORBA::Object_var object_var = genericFactory_var->create_object (factory_key,
                                                                            the_criteria
                                                                            ACE_ENV_ARG_PARAMETER);
          ACE_CHECK_RETURN (0);

          if (this->debug_level_ >= 2)
            ACE_DEBUG ((LM_DEBUG,
                        "Life_Cycle_Service_i::create_object: Forwarded request.\n"));

          if (CORBA::is_nil (object_var.in()))
            ACE_ERROR_RETURN ((LM_ERROR,
                               "Life_Cycle_Service_i::create_object: Null object refeference returned by factory.\n"),
                              0);

          if (this->debug_level_ >= 2)
            ACE_DEBUG ((LM_DEBUG,
                       "Life_Cycle_Service_i::create_object: Return a object reference to a new object.\n"));

          return CORBA::Object::_duplicate (object_var.in());
        }
    }
  else
    {
      return 0;
    }
}

void
Life_Cycle_Service_i::register_factory (const char * name,
                                        const char * location,
                                        const char * description,
                                        CORBA::Object_ptr object
                                        ACE_ENV_ARG_DECL_NOT_USED)
  ACE_THROW_SPEC (( CORBA::SystemException))
{
  if (factory_trader_ptr_ == 0)
    ACE_NEW (factory_trader_ptr_, Factory_Trader(this->debug_level_));
  // we have an proper reference to the Factory Trader

  // Just forward the call to the factory trader
  // Exceptions are not handled here, they are returned
  factory_trader_ptr_->_cxx_export (name, location, description, object);

  if (this->debug_level_ >= 1)
    ACE_DEBUG ((LM_DEBUG, "LifeCycle Server: Registered %s\n"
                          "                  Location: %s\n"
                          "                  Description: %s\n",
                name, location, description));
}
