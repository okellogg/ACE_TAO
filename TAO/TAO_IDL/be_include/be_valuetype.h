/* -*- c++ -*- */
// $Id$

// ============================================================================
//
// = LIBRARY
//    TAO IDL
//
// = FILENAME
//    be_valuetype.h
//
// = DESCRIPTION
//    Extension of class AST_Interface and be_interface that provides
//    additional means for C++ mapping of an valuetype.
//
// ============================================================================

#ifndef TAO_BE_VALUETYPE_H
#define TAO_BE_VALUETYPE_H

#include "be_interface.h"
#include "ast_valuetype.h"
#include "ast_field.h"

class TAO_OutStream;

class be_valuetype : public virtual be_interface,
                     public virtual AST_ValueType
{
  // = TITLE
  //    Backend-class for valuetypes
  //
  // = DESCRIPTION
  //    Extends be_interface and overrides member functions for valuetype
  //    mapping.
  //
public:
  be_valuetype (void);
  // Default constructor.

  be_valuetype (UTL_ScopedName *n,
                AST_Interface **inherits,
                long n_inherits,
                AST_ValueType *inherits_concrete,
                AST_Interface **inherits_flat,
                long n_inherits_flat,
                AST_Interface **supports,
                long n_supports,
                AST_Interface *supports_concrete,
                idl_bool abstract,
                idl_bool truncatable);
  // Constructor that sets its scoped name <n>, a list of inherited valuetypes
  // and supported interfaces <ih>, and the number of inherited interfaces <nih>

  ~be_valuetype (void);
  // Destructor.

  virtual void redefine (AST_ValueType *from);

  idl_bool opt_accessor (void);
  // Should generate optimized form?

  virtual int gen_var_defn (char *local_name = 0);
  // Generate the _var class definition.

  virtual int gen_var_impl (char *local_name = 0,
                            char *full_name = 0);
  // Generate the implementation for the _var class.

  virtual int gen_out_defn (char *local_name = 0);
  // Generate the _out class definition.

  virtual int gen_out_impl (char *local_name = 0,
                            char *full_name = 0);
  // Generate the _out implementation.

  virtual int gen_helper_header (char *local_name = 0,
                                 char *full_name = 0);
  // Generate the helper functions definition.

  virtual int gen_helper_inline (char *local_name = 0,
                                 char *full_name = 0);
  // Generate the helper functions inline implementation.

  virtual int gen_helper_stubs (char *local_name = 0,
                                char *full_name = 0);
  // Generate the helper functions implementation.

  const char *full_obv_skel_name (void);
  // Retrieve the fully scoped skel class name.

  const char *field_pd_prefix (void);

  const char *field_pd_postfix (void);

  // For building the name for private data fields.
  be_valuetype *statefull_inherit (void);

  // Visiting.
  virtual int accept (be_visitor *visitor);

  // Cleanup.
  virtual void destroy (void);

 // Narrowing.
  DEF_NARROW_METHODS2 (be_valuetype, be_interface, AST_ValueType);
  DEF_NARROW_FROM_DECL (be_valuetype);
  DEF_NARROW_FROM_SCOPE (be_valuetype);

  void compute_fullobvskelname (void);
  // Compute the fully scoped skel class name.

  ACE_CDR::ULong data_members_count (
      AST_Field::Visibility vis = AST_Field::vis_NA
    );
  // Compute the count of private/public/all data members.

  virtual idl_bool in_recursion (AST_Type *node = 0);
  // Check if we are in recursion.

private:
  char *full_obv_skel_name_;
};

#endif  // if !defined
