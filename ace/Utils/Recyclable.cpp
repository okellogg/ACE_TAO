//$Id$
#include "ace/Utils/Recyclable.h"


#if !defined (__ACE_INLINE__)
#include "ace/Utils/Recyclable.inl"
#endif /* __ACE_INLINE __ */

ACE_RCSID(ace, Recyclable, "$Id$")


ACE_Recyclable::ACE_Recyclable (ACE_Recyclable_State initial_state)
  : recycle_state_ (initial_state)
{
}

ACE_Recyclable::~ACE_Recyclable (void)
{
}
